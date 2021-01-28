#include "process_binding.hpp"
/* #include "attributes.hpp" */
/* #include "namespaces.hpp" */
#include "pystring.h"
/* #include "type.hpp" */
#include "clang/AST/ASTContext.h"
#include "clang/AST/Decl.h"
#include "clang/AST/DeclCXX.h"
#include "clang/AST/DeclTemplate.h"
#include "clang/AST/Type.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/Basic/LLVM.h"
#include "llvm/Support/Casting.h"
#include <bits/stdint-uintn.h>
#include <cassert>
#include <memory>
#include <unordered_map>

#define SPDLOG_ACTIVE_LEVEL TRACE
#include <spdlog/fmt/fmt.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>

#include <iostream>

using namespace clang;
using namespace clang::ast_matchers;
namespace ps = pystring;

namespace cppmm {

namespace {

/* std::vector<AttrDesc> get_attrs(const clang::Decl* decl) { */
/*     std::vector<AttrDesc> attrs; */
/*     if (decl->hasAttrs()) { */
/*         clang::ASTContext& ctx = decl->getASTContext(); */
/*         for (const auto& attr : decl->attrs()) { */
/*             const clang::AnnotateAttr* ann = */
/*                 clang::cast<const clang::AnnotateAttr>(attr); */
/*             if (ann) { */
/*                 if (auto opt = parse_attributes(ann->getAnnotation().str()))
 * { */
/*                     attrs.push_back(*opt); */
/*                 } */
/*             } */
/*         } */
/*     } */

/*     return attrs; */
/* } */

struct indent {
    indent(int level) : level(level) {}

private:
    friend std::ostream& operator<<(std::ostream& stream, const indent& val);

    int level;
};

std::ostream& operator<<(std::ostream& stream, const indent& val) {
    for (int i = 0; i < val.level * 4; i++) {
        stream << " ";
    }
    return stream;
}

} // namespace

// enum RecordKind { RK_OpaquePtr = 0, RK_OpaqueBytes, RK_ValueType };

enum class NodeKind : uint32_t {
    Node = 0,
    TranslationUnit,
    Namespace,
    BuiltinType,
    PointerType,
    RecordType,
    Parm,
    Function,
    Method,
    Record,
};

std::ostream& operator<<(std::ostream& os, NodeKind k) {
    switch (k) {
    case NodeKind::Node:
        os << "Node";
        break;
    case NodeKind::TranslationUnit:
        os << "TranslationUnit";
        break;
    case NodeKind::Namespace:
        os << "Namespace";
        break;
    case NodeKind::BuiltinType:
        os << "BuiltinType";
        break;
    case NodeKind::PointerType:
        os << "PointerType";
        break;
    case NodeKind::RecordType:
        os << "RecordType";
        break;
    case NodeKind::Parm:
        os << "Parm";
        break;
    case NodeKind::Function:
        os << "Function";
        break;
    case NodeKind::Method:
        os << "Method";
        break;
    case NodeKind::Record:
        os << "Record";
        break;
    }
    return os;
}

enum class PointerKind : uint32_t {
    Pointer,
    Reference,
};

enum class RecordKind : uint32_t { OpaquePtr = 0, OpaqueBytes, ValueType };

using NodeId = uint64_t;

struct sanitize {
    const std::string& s;

    sanitize(const std::string& s) : s(s) {}
};

std::ostream& operator<<(std::ostream& os, const sanitize& s) {
    std::string r = s.s;
    r = pystring::replace(r, "&", "&amp;");
    r = pystring::replace(r, "<", "&lt;");
    r = pystring::replace(r, ">", "&gt;");
    r = pystring::replace(r, "\"", "&quot;");
    return os << r;
}

struct Node {
    std::string qualified_name;
    NodeId id;
    NodeId context; //< parent context (e.g. record, namespce, TU)
    NodeKind node_kind;

    Node(std::string qualified_name, NodeId id, NodeId context,
         NodeKind node_kind)
        : qualified_name(qualified_name), id(id), context(context),
          node_kind(node_kind) {}

    virtual void write_xml_attrs(std::ostream& os) const {
        os << " name=\"" << sanitize(qualified_name) << "\"";
        os << " id=\"" << id << "\"";
    }

    virtual void write_xml(std::ostream& os, int depth) const = 0;
};

using NodePtr = std::unique_ptr<Node>;

std::vector<NodePtr> NODES;
std::unordered_map<std::string, NodeId> NODE_MAP;
std::vector<NodeId> ROOT;

struct NodeTranslationUnit : public Node {
    std::vector<NodeId> children;

    virtual void write_xml(std::ostream& os, int depth) const override {
        os << indent(depth) << "<TranslationUnit";
        write_xml_attrs(os);
        os << ">\n";

        for (NodeId id : children) {
            const Node* node = NODES[id].get();
            node->write_xml(os, depth + 1);
        }

        os << "</TranslationUnit>\n";
    }

    NodeTranslationUnit(std::string qualified_name, NodeId id, NodeId context)
        : Node(qualified_name, id, context, NodeKind::TranslationUnit) {}
};

struct NodeNamespace : public Node {
    virtual void write_xml(std::ostream& os, int depth) const override {
        os << indent(depth) << "<Namespace";
        write_xml_attrs(os);
        os << " />\n";
    }
};

struct NodeType : public Node {
    std::string type_name;
    NodeType(std::string qualified_name, NodeId id, NodeId context,
             NodeKind node_kind, std::string type_name)
        : Node(qualified_name, id, context, node_kind), type_name(type_name) {}

    virtual void write_xml_attrs(std::ostream& os) const override {
        Node::write_xml_attrs(os);
        os << " type=\"" << sanitize(type_name) << "\"";
    }
};

struct NodeBuiltinType : public NodeType {
    NodeBuiltinType(std::string qualified_name, NodeId id, NodeId context, std::string type_name)
        : NodeType(qualified_name, id, context, NodeKind::BuiltinType, type_name) {}

    virtual void write_xml(std::ostream& os, int depth) const override {
        os << indent(depth) << "<BuiltinType";
        write_xml_attrs(os);
        os << " />";
    }
};

struct QType {
    NodeId ty;
    bool is_const;

    void write_xml(std::ostream& os, int depth) const {
        os << indent(depth) << "<QType const=\"" << is_const << "\">";

        NODES[ty]->write_xml(os, 0);

        os << "</QType>";
    }
};

// pointer or reference type - check type_kind
struct NodePointerType : public NodeType {
    QType pointee_type;
    PointerKind pointer_kind;
    NodePointerType(std::string qualified_name, NodeId id, NodeId context, std::string type_name,
                    PointerKind pointer_kind, QType pointee_type)
        : NodeType(qualified_name, id, context, NodeKind::PointerType, type_name),
          pointer_kind(pointer_kind), pointee_type(pointee_type) {}

    virtual void write_xml_attrs(std::ostream& os) const override {
        NodeType::write_xml_attrs(os);
        os << " pointer_kind=\"";
        pointer_kind == PointerKind::Pointer ? os << "pointer"
                                             : os << "reference";
        os << "\"";
    }

    virtual void write_xml(std::ostream& os, int depth) const override {
        os << indent(depth) << "<PointerType";
        write_xml_attrs(os);
        os << ">";

        pointee_type.write_xml(os, depth);

        os << "</PointerType>";
    }
};

struct NodeRecordType : public NodeType {
    NodeId record;
    NodeRecordType(std::string qualified_name, NodeId id, NodeId context, std::string type_name,
                   NodeId record)
        : NodeType(qualified_name, id, context, NodeKind::RecordType, type_name),
          record(record) {}

    virtual void write_xml_attrs(std::ostream& os) const override {
        NodeType::write_xml_attrs(os);
        os << " record=\"" << record << "\"";
    }

    virtual void write_xml(std::ostream& os, int depth) const override {
        os << indent(depth) << "<RecordType";
        write_xml_attrs(os);
        os << " />\n";
    }
};

struct Param {
    std::string name;
    QType qty;
    int index;
};

struct NodeFunction : public Node {
    QType return_type;
    std::vector<Param> params;
    bool in_binding = false;
    bool in_library = false;

    NodeFunction(std::string qualified_name, NodeId id, NodeId context,
                 QType return_type, std::vector<Param> params)
        : Node(qualified_name, id, context, NodeKind::Function),
          return_type(return_type), params(params) {}

    virtual void write_xml_attrs(std::ostream& os) const override {
        Node::write_xml_attrs(os);
        os << " in_binding=\"" << in_binding << "\"";
        os << " in_library=\"" << in_library << "\"";
    }

    virtual void write_parameters(std::ostream& os, int depth) const {
        os << indent(depth) << "<Return>";
        return_type.write_xml(os, 0);
        os << "</Return>\n";

        for (const auto& param : params) {
            os << indent(depth) << "<Param name=\"" << param.name << "\" "
               << "index=\"" << param.index << "\">";
            param.qty.write_xml(os, 0);
            os << "</Param>\n";
        }
    }

    virtual void write_xml(std::ostream& os, int depth) const override {
        os << "<Function";
        write_xml_attrs(os);
        os << " />\n";
    }
};

struct NodeMethod : public NodeFunction {
    bool is_static = false;

    NodeMethod(std::string qualified_name, NodeId id, NodeId context,
               QType return_type, std::vector<Param> params, bool is_static)
        : NodeFunction(qualified_name, id, context, return_type, params),
          is_static(is_static) {
        node_kind = NodeKind::Method;
    }

    virtual void write_xml_attrs(std::ostream& os) const override {
        NodeFunction::write_xml_attrs(os);
        os << " is_static=\"" << is_static << "\"";
    }

    virtual void write_xml(std::ostream& os, int depth) const override {
        os << indent(depth) << "<Method";
        write_xml_attrs(os);
        os << ">\n";

        write_parameters(os, depth + 1);

        os << indent(depth) << "</Method>";
    }
};

struct Field {
    std::string name;
    QType qtype;
};

struct NodeRecord : public Node {
    std::vector<Field> fields;
    std::vector<NodeId> methods;
    RecordKind record_kind;

    uint32_t width;
    uint32_t align;

    NodeRecord(std::string qualified_name, NodeId id, NodeId context,
               RecordKind record_kind, uint32_t width, uint32_t align)
        : Node(qualified_name, id, context, NodeKind::Record),
          record_kind(record_kind), width(width), align(align) {}

    virtual void write_xml_attrs(std::ostream& os) const override {
        Node::write_xml_attrs(os);
        os << " width=\"" << width << "\"";
        os << " align=\"" << align << "\"";
    }

    virtual void write_xml(std::ostream& os, int depth) const override {
        os << indent(depth) << "<Record";
        write_xml_attrs(os);
        os << ">\n";

        for (const auto field : fields) {
            os << indent(depth + 1) << "<Field name=\"" << field.name << "\">";
            field.qtype.write_xml(os, 0);
            os << "</Field>\n";
        }

        for (const auto method_id : methods) {
            NODES[method_id]->write_xml(os, depth + 1);
            os << "\n";
        }

        os << indent(depth) << "</Record>\n";
    }
};

void dump_nodes(std::ostream& os) {
    os << "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n";
    for (const auto& id : ROOT) {
        /* if (node->node_kind == NodeKind::Method || */
        /*     node->node_kind == NodeKind::BuiltinType) { */
        /*     // we'll inline these in their records */
        /*     continue; */
        /* } */
        NODES[id]->write_xml(os, 0);
    }

    /* for (const auto& kv: NODE_MAP) { */
    /*     NodeId id = kv.second; */
    /*     auto kind = NODES[id]->node_kind; */
    /*     std::cout << kv.first << " -- " << kind << " -- " <<
     * NODES[id]->qualified_name << "\n"; */
    /* } */
}

bool get_abi_info(const TypeDecl* td, ASTContext& ctx, uint32_t& width,
                  uint32_t& align) {
    if (td) {
        const clang::Type* ty = td->getTypeForDecl();
        if (!ty->isIncompleteType()) {
            const clang::TypeInfo& ti = ctx.getTypeInfo(ty);
            SPDLOG_DEBUG("    width: {}", ti.Width);
            SPDLOG_DEBUG("    align: {}", ti.Align);
            width = ti.Width;
            align = ti.Align;
            return true;
        } else {
            SPDLOG_DEBUG("    is incomplete type");
        }
    } else {
        SPDLOG_DEBUG("    is not a TypeDecl");
    }

    return false;
}

NodeTranslationUnit* get_translation_unit(const std::string& filename) {
    auto it = NODE_MAP.find(filename);
    if (it != NODE_MAP.end()) {
        const auto& node = NODES[it->second];
        assert(node->node_kind == NodeKind::TranslationUnit &&
               "node is wrong type");
        return (NodeTranslationUnit*)node.get();
    }

    NodeId id = NODES.size();
    auto node = std::make_unique<NodeTranslationUnit>(filename, id, 0);
    ROOT.push_back(id);
    auto* node_ptr = node.get();
    NODES.emplace_back(std::move(node));
    return node_ptr;
}

void handle_class_template_decl(const ClassTemplateDecl* ctd) {
    ASTContext& ctx = ctd->getASTContext();
    SourceManager& sm = ctx.getSourceManager();
    const auto& loc = ctd->getLocation();

    SPDLOG_DEBUG("ClassTemplateDecl {:p} {} ({}:{})", (void*)ctd,
                 ctd->getQualifiedNameAsString(), sm.getFilename(loc).str(),
                 sm.getSpellingLineNumber(loc));

    const TemplateParameterList* tpl = ctd->getTemplateParameters();
    for (const NamedDecl* nd : *tpl) {
        SPDLOG_DEBUG("        {}", nd->getQualifiedNameAsString());
    }
}

QType process_qtype(const QualType& qt) {
    if (qt->isPointerType() || qt->isReferenceType()) {
        auto pointer_kind =
            qt->isPointerType() ? PointerKind::Pointer : PointerKind::Reference;

        // first check if we've got the pointer type already
        const std::string pointer_type_name =
            qt.getCanonicalType().getAsString();
        const std::string pointer_type_node_name = "TYPE:" + pointer_type_name;

        auto it = NODE_MAP.find(pointer_type_name);
        NodeId id;
        if (it == NODE_MAP.end()) {

            // need to create the pointer type, create the pointee type first
            QType pointee_qtype =
                process_qtype(qt->getPointeeType().getCanonicalType());
            // now create the pointer type
            id = NODES.size();
            auto node_pointer_type = std::make_unique<NodePointerType>(
                pointer_type_node_name, id, 0, pointer_type_name, pointer_kind, pointee_qtype);
            NODES.emplace_back(std::move(node_pointer_type));
            NODE_MAP[pointer_type_name] = id;
        } else {
            id = it->second;
        }

        return QType{id, qt.isConstQualified()};
    } else {
        std::string type_name =
            pystring::replace(
                qt.getCanonicalType().getUnqualifiedType().getAsString(),
                "class ", "");
        std::string type_node_name = "TYPE:" + type_name;

        auto it = NODE_MAP.find(type_node_name);
        NodeId id;
        if (it == NODE_MAP.end()) {
            id = NODES.size();
            if (qt->isBuiltinType()) {
                auto node_type =
                    std::make_unique<NodeBuiltinType>(type_node_name, id, 0, type_name);
                NODES.emplace_back(std::move(node_type));
                NODE_MAP[type_node_name] = id;
            } else if (qt->isRecordType()) {
                auto crd = qt->getAsCXXRecordDecl();
                assert(crd && "CRD from Type is null");
                crd = crd->getCanonicalDecl();
                assert(crd && "CRD canonical decl is null");

                // See if we've already processed a record matching this type
                // and get its id if we have
                const std::string record_name = crd->getQualifiedNameAsString();
                NodeId id_rec = -1;
                auto it_rec = NODE_MAP.find(record_name);
                if (it_rec != NODE_MAP.end()) {
                    id_rec = it_rec->second;
                }

                auto node_record_type = std::make_unique<NodeRecordType>(
                    type_node_name, id, 0, type_name, id_rec);
                NODES.emplace_back(std::move(node_record_type));
                NODE_MAP[type_node_name] = id;
            } else {
                SPDLOG_WARN("Unhandled type {}", type_node_name);
                id = NodeId(-1);
            }
        } else {
            id = it->second;
        }

        return QType{id, qt.isConstQualified()};
    }
}

void process_function_parameters(const FunctionDecl* fd, QType& return_qtype,
                                 std::vector<Param>& params) {
    SPDLOG_DEBUG("    -> {}", fd->getReturnType().getAsString());
    return_qtype = process_qtype(fd->getReturnType());

    for (const ParmVarDecl* pvd : fd->parameters()) {
        int index = pvd->getFunctionScopeIndex();
        SPDLOG_DEBUG("        {}: {}", pvd->getQualifiedNameAsString(),
                     pvd->getType().getCanonicalType().getAsString());
        QType qtype = process_qtype(pvd->getType());

        params.emplace_back(Param{pvd->getNameAsString(), qtype, index});

        if (const auto* vtd = pvd->getDescribedVarTemplate()) {
            SPDLOG_DEBUG("            GOT VTD");
        }
        if (const auto* td = pvd->getDescribedTemplate()) {
            SPDLOG_DEBUG("            GOT TD");
        }
    }
}

std::string get_record_name(const CXXRecordDecl* crd) {
    // we have to do this dance to get the template parameters in the name,
    // otherwise they're omitted
    std::string s = crd->getTypeForDecl()->getCanonicalTypeInternal().getAsString();
    s = pystring::replace( s, "class ", "");
    s = pystring::replace( s, "struct ", "");
    return s;
}

void process_concrete_record(const CXXRecordDecl* crd, std::string filename) {
    ASTContext& ctx = crd->getASTContext();
    SourceManager& sm = ctx.getSourceManager();
    const auto& loc = crd->getLocation();

    crd = crd->getCanonicalDecl();
    const std::string record_name = get_record_name(crd);

    auto* node_tu = get_translation_unit(filename);

    uint32_t width, align;
    if (!get_abi_info(dyn_cast<TypeDecl>(crd), ctx, width, align)) {
        SPDLOG_CRITICAL("Could not get ABI info for {}", record_name);
    }

    // Add the new Record node
    NodeId new_id = NODES.size();
    auto node_record = std::make_unique<NodeRecord>(
        record_name, new_id, 0, RecordKind::OpaquePtr, width, align);
    auto* node_record_ptr = node_record.get();
    NODES.emplace_back(std::move(node_record));
    NODE_MAP[record_name] = new_id;

    // if there's an existing RecordType node referring to this Record, then
    // set its record id to our new id
    auto it_record_type = NODE_MAP.find("TYPE:" + record_name);
    if (it_record_type != NODE_MAP.end()) {
        auto* node_record_type =
            (NodeRecordType*)NODES[it_record_type->second].get();
        node_record_type->record = new_id;
    }

    // add this record to the TU
    node_tu->children.push_back(new_id);

    for (const Decl* d : crd->decls()) {
        if (const FunctionTemplateDecl* ftd =
                dyn_cast<FunctionTemplateDecl>(d)) {
            // SPDLOG_DEBUG("        FunctionTemplateDecl");
            for (const FunctionDecl* fd : ftd->specializations()) {
                const std::string function_name =
                    ftd->getQualifiedNameAsString();
                SPDLOG_DEBUG("    SPEC {}", function_name);
                QType return_qtype;
                std::vector<Param> params;
                process_function_parameters(fd, return_qtype, params);
                NodeId id = NODES.size();
                /* auto node_function =
                 * std::make_unique<NodeMethod>(function_name, id, 0,
                 * return_qtype, params, ); */
            }
        } else if (const auto* cmd = dyn_cast<CXXMethodDecl>(d)) {
            if (!cmd->isUserProvided()) {
                // we only want methods that are explicitly declared in the
                // binding file
                continue;
            }
            const std::string method_name = cmd->getQualifiedNameAsString();
            SPDLOG_DEBUG("    METHOD {}", method_name);

            QType return_qtype;
            std::vector<Param> params;
            process_function_parameters(cmd, return_qtype, params);
            NodeId id = NODES.size();

            auto node_function = std::make_unique<NodeMethod>(
                method_name, id, 0, return_qtype, std::move(params),
                cmd->isStatic());
            NODES.emplace_back(std::move(node_function));
            NODE_MAP[method_name] = id;
            node_record_ptr->methods.push_back(id);

        } else if (const auto* fd = dyn_cast<FieldDecl>(d)) {
            const std::string field_name = fd->getNameAsString();
            SPDLOG_DEBUG("    FIELD {}", field_name);
            QType qtype = process_qtype(fd->getType());
            node_record_ptr->fields.push_back(Field{field_name, qtype.ty});
        } else if (const auto* tad = dyn_cast<TypeAliasDecl>(d)) {
            SPDLOG_DEBUG("    TYPEALIAS {}", tad->getQualifiedNameAsString());
            const auto* bound_nd = tad->getUnderlyingDecl();
            const auto* bound_rd =
                tad->getUnderlyingType().getCanonicalType()->getAsRecordDecl();
            SPDLOG_DEBUG("    RD: {}", bound_rd->getQualifiedNameAsString());
            if (const auto* bound_ctsd =
                    dyn_cast<ClassTemplateSpecializationDecl>(bound_rd)) {
                SPDLOG_DEBUG("    got bound CTSD");
            }
        }
    }
}

void handle_cxx_record_decl(const CXXRecordDecl* crd) {
    ASTContext& ctx = crd->getASTContext();
    SourceManager& sm = ctx.getSourceManager();
    const auto& loc = crd->getLocation();

    crd = dyn_cast<CXXRecordDecl>(crd->getCanonicalDecl());
    if (crd == nullptr) {
        SPDLOG_ERROR("Could not get canonical decl from CXRecordDecl");
    }

    std::string filename = sm.getFilename(loc).str();

    SPDLOG_DEBUG("CXXRecordDecl {:p} {} ({}:{})", (void*)crd,
                 crd->getQualifiedNameAsString(), filename,
                 sm.getSpellingLineNumber(loc));

    const clang::Type* ty = crd->getTypeForDecl();
    if (ty->isIncompleteType()) {
        // type cannot be sized
        SPDLOG_DEBUG("    incomplete");
        return;
    } else if (ty->isDependentType()) {
        // type is dependent on a template parameter
        // this probably means it's the template definition, which we want to
        // ignore and have the user explicitly instantiate the types they want
        if (const ClassTemplateDecl* ctd = crd->getDescribedClassTemplate()) {
            SPDLOG_DEBUG("    dependent on {:p}", (void*)ctd);
        } else {
            SPDLOG_DEBUG("    dependent on unknown?");
        }
        return;
    }

    if (const ClassTemplateSpecializationDecl* ctsd =
            dyn_cast<ClassTemplateSpecializationDecl>(crd)) {
        // this is the specialized version of a template class
        SPDLOG_DEBUG("    is ClassTemplateSpecializationDecl");
    }

    // if we get down here then we have a concrete, sized type we can
    // process
    // see if there's a BoundType typedef, and if so process that instead
    for (const auto* decl : crd->decls()) {
        if (const auto* tad = dyn_cast<TypeAliasDecl>(decl)) {
            if (tad->getNameAsString() == "BoundType") {
                SPDLOG_DEBUG(
                    "Found BoundType {}",
                    tad->getUnderlyingDecl()->getQualifiedNameAsString());
            }

            const auto* bound_nd = tad->getUnderlyingDecl();
            const auto* bound_rd =
                tad->getUnderlyingType()->getAsCXXRecordDecl();

            if (const ClassTemplateSpecializationDecl* ctsd =
                    dyn_cast<ClassTemplateSpecializationDecl>(crd)) {
                // this is the specialized version of a template class
                SPDLOG_DEBUG("    is ClassTemplateSpecializationDecl {}",
                             ctsd->getQualifiedNameAsString());
            }

            process_concrete_record(bound_rd, filename);
            return;
        }
    }

    // otherwise process this type
    process_concrete_record(crd, filename);
}

void ProcessBindingCallback::run(const MatchFinder::MatchResult& result) {
    // if (const TypeAliasDecl* tdecl =
    //         result.Nodes.getNodeAs<TypeAliasDecl>("typeAliasDecl")) {
    //     handle_typealias(tdecl);
    // } else if (const CXXRecordDecl* record =
    //                result.Nodes.getNodeAs<CXXRecordDecl>("recordDecl")) {
    //     handle_record(record);
    // } else if (const EnumDecl* enum_decl =
    //                result.Nodes.getNodeAs<EnumDecl>("enumDecl")) {
    //     handle_enum(enum_decl);
    // } else if (const FunctionDecl* function =
    //                result.Nodes.getNodeAs<FunctionDecl>("functionDecl")) {
    //     handle_function(function);
    // }
    if (const ClassTemplateDecl* class_template_decl =
            result.Nodes.getNodeAs<ClassTemplateDecl>("classTemplateDecl")) {
        handle_class_template_decl(class_template_decl);
    }
    if (const CXXRecordDecl* rec_decl =
            result.Nodes.getNodeAs<CXXRecordDecl>("recordDecl")) {
        handle_cxx_record_decl(rec_decl);
    }

    // if (const TypeAliasDecl* tdecl =
    //         result.Nodes.getNodeAs<TypeAliasDecl>("typeAliasDecl")) {
    //     std::cout << "TYPEALIASDECL\n";
    //     // tdecl->dump();
    //     if (const auto* crd =
    //     tdecl->getUnderlyingType()->getAsCXXRecordDecl()) {
    //         SPDLOG_DEBUG("GOT CXXRECORDTTYPE");
    //         process_concrete_decl(crd);
    //     }
    // }
}

ProcessBindingConsumer::ProcessBindingConsumer(ASTContext* context) {
    // match all record declrations in the cppmm_bind namespace
    DeclarationMatcher record_decl_matcher =
        cxxRecordDecl(hasAncestor(namespaceDecl(hasName("cppmm_bind"))),
                      unless(isImplicit()))
            .bind("recordDecl");
    _match_finder.addMatcher(record_decl_matcher, &_handler);

    // match all record declrations in the cppmm_bind namespace
    DeclarationMatcher class_template_decl_matcher =
        classTemplateDecl(hasAncestor(namespaceDecl(hasName("cppmm_bind"))))
            .bind("classTemplateDecl");
    _match_finder.addMatcher(class_template_decl_matcher, &_handler);

    // match all typedef declrations in the cppmm_bind namespace
    DeclarationMatcher typedef_decl_matcher =
        typeAliasDecl(hasAncestor(namespaceDecl(hasName("cppmm_bind"))),
                      unless(isImplicit()))
            .bind("typeAliasDecl");
    _match_finder.addMatcher(typedef_decl_matcher, &_handler);

    /*
    // match all record declrations in the cppmm_bind namespace
    DeclarationMatcher enum_decl_matcher =
        enumDecl(hasAncestor(namespaceDecl(hasName("cppmm_bind"))),
                 unless(isImplicit()))
            .bind("enumDecl");
    _match_finder.addMatcher(enum_decl_matcher, &_handler);

    // match all function declarations
    DeclarationMatcher function_decl_matcher =
        functionDecl(hasAncestor(namespaceDecl(hasName("cppmm_bind"))),
                     unless(hasAncestor(recordDecl())))
            .bind("functionDecl");
    _match_finder.addMatcher(function_decl_matcher, &_handler);
    */
}

void ProcessBindingConsumer::HandleTranslationUnit(ASTContext& context) {
    _match_finder.matchAST(context);
}

} // namespace cppmm
