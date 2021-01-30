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
#include <iomanip>

#include "filesystem.hpp"
namespace fs = ghc::filesystem;

#include <nlohmann/json.hpp>
using json = nlohmann::ordered_json;

using namespace clang;
using namespace clang::ast_matchers;
namespace ps = pystring;

namespace cppmm {

namespace {

std::vector<std::string> get_attrs(const clang::Decl* decl) {
    std::vector<std::string> attrs;
    if (decl->hasAttrs()) {
        clang::ASTContext& ctx = decl->getASTContext();
        for (const auto& attr : decl->attrs()) {
            const clang::AnnotateAttr* ann =
                clang::cast<const clang::AnnotateAttr>(attr);
            if (ann) {
                attrs.push_back(ann->getAnnotation().str());
            }
        }
    }
    return attrs;
}

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

std::string strip_name_kinds(std::string s) {
    s = pystring::replace(s, "class ", "");
    s = pystring::replace(s, "struct ", "");
    s = pystring::replace(s, "enum ", "");
    s = pystring::replace(s, "union ", "");
    return s;
}

} // namespace

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

using NodeId = int32_t;

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

    virtual void write_json_attrs(json& o) const {
        /* o["name"] = qualified_name; */
        if (id >= 0) {
            o["id"] = id;
        } else {
            o["id"] = nullptr;
        }
    }

    virtual void write_json(json& o) const = 0;
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

    virtual void write_json(json& o) const override {
        o["kind"] = "TranslationUnit";
        o["filename"] = qualified_name;
        write_json_attrs(o);

        o["decls"] = {};
        for (NodeId id : children) {
            const Node* node = NODES[id].get();
            auto child = json::object();
            node->write_json(child);
            o["decls"].emplace_back(std::move(child));
        }
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

    virtual void write_json_attrs(json& o) const override {
        Node::write_json_attrs(o);
        o["type"] = type_name;
    }
};

struct NodeBuiltinType : public NodeType {
    NodeBuiltinType(std::string qualified_name, NodeId id, NodeId context,
                    std::string type_name)
        : NodeType(qualified_name, id, context, NodeKind::BuiltinType,
                   type_name) {}

    virtual void write_xml(std::ostream& os, int depth) const override {
        os << indent(depth) << "<BuiltinType";
        write_xml_attrs(os);
        os << " />";
    }

    virtual void write_json(json& o) const override {
        o["kind"] = "BuiltinType";
        write_json_attrs(o);
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

    void write_json(json& o) const {
        NODES[ty]->write_json(o);
        o["const"] = is_const;
    }

    bool operator==(const QType& rhs) const {
        return ty == rhs.ty && is_const == rhs.is_const;
    }

    bool operator!=(const QType& rhs) const { return !(*this == rhs); }
};

// pointer or reference type - check type_kind
struct NodePointerType : public NodeType {
    QType pointee_type;
    PointerKind pointer_kind;
    NodePointerType(std::string qualified_name, NodeId id, NodeId context,
                    std::string type_name, PointerKind pointer_kind,
                    QType pointee_type)
        : NodeType(qualified_name, id, context, NodeKind::PointerType,
                   type_name),
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

    virtual void write_json(json& o) const override {
        if (pointer_kind == PointerKind::Pointer) {
            o["kind"] = "Pointer";
        } else {
            o["kind"] = "Reference";
        }
        write_json_attrs(o);

        o["pointee"] = {};
        pointee_type.write_json(o["pointee"]);
    }

};

struct NodeRecordType : public NodeType {
    NodeId record;
    NodeRecordType(std::string qualified_name, NodeId id, NodeId context,
                   std::string type_name, NodeId record)
        : NodeType(qualified_name, id, context, NodeKind::RecordType,
                   type_name),
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

    virtual void write_json_attrs(json& o) const override {
        NodeType::write_json_attrs(o);
        o["record"] = record;
    }

    virtual void write_json(json& o) const override {
        o["kind"] = "RecordType";
        write_json_attrs(o);
    }

};

struct Param {
    std::string name;
    QType qty;
    int index;
};

struct NodeAttributeHolder : public Node {
    std::vector<std::string> attrs;

    NodeAttributeHolder(std::string qualified_name, NodeId id, NodeId context,
                        NodeKind node_kind, std::vector<std::string> attrs)
        : Node(qualified_name, id, context, node_kind), attrs(attrs) {}

    void write_attrs(std::ostream& os, int depth) const {
        for (const auto& a : attrs) {
            os << indent(depth) << "<Attribute>" << a << "</Attribute>\n";
        }
    }

    virtual void write_xml(std::ostream& os, int depth) const override = 0;
    virtual void write_json(json& o) const override = 0;

    // FIXME: worst naming ever
    virtual void write_attrs_json(json& o) const {
        o["attributes"] = {};
        for (const auto& a: attrs) {
            o["attributes"].emplace_back(a);
        }
    }

};

struct NodeFunction : public NodeAttributeHolder {
    std::string short_name;
    QType return_type;
    std::vector<Param> params;
    bool in_binding = false;
    bool in_library = false;

    NodeFunction(std::string qualified_name, NodeId id, NodeId context,
                 std::vector<std::string> attrs, std::string short_name,
                 QType return_type, std::vector<Param> params)
        : NodeAttributeHolder(qualified_name, id, context, NodeKind::Function,
                              attrs),
          short_name(short_name), return_type(return_type), params(params) {}

    virtual void write_xml_attrs(std::ostream& os) const override {
        Node::write_xml_attrs(os);
        os << " short_name=\"" << sanitize(short_name) << "\"";
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
        os << indent(depth) << "<Function";
        write_xml_attrs(os);
        os << ">\n";

        write_attrs(os, depth + 1);
        write_parameters(os, depth + 1);

        os << indent(depth) << "</Function>";
    }

    virtual void write_json_attrs(json& o) const override {
        NodeAttributeHolder::write_json_attrs(o);
        o["short_name"] = short_name;
        o["qualified_name"] = qualified_name;
        o["in_binding"] = in_binding;
        o["in_library"] = in_library;
    }

    virtual void write_parameters_json(json& o) const {
        o["return"] = {};
        return_type.write_json(o["return"]);

        o["params"] = {};
        for (const auto& param: params) {
            auto p = json::object();
            p["index"] = param.index;
            p["name"] = param.name;
            p["type"] = json::object();
            param.qty.write_json(p["type"]);
            o["params"].emplace_back(p);

        }
    }

    virtual void write_json(json& o) const override {
        o["kind"] = "Function";
        write_json_attrs(o);
        write_attrs_json(o);
        write_parameters_json(o);
    }

};

struct NodeMethod : public NodeFunction {
    bool is_static = false;

    NodeMethod(std::string qualified_name, NodeId id, NodeId context,
               std::vector<std::string> attrs, std::string short_name,
               QType return_type, std::vector<Param> params, bool is_static)
        : NodeFunction(qualified_name, id, context, attrs, short_name,
                       return_type, params),
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

        write_attrs(os, depth + 1);
        write_parameters(os, depth + 1);

        os << indent(depth) << "</Method>";
    }

    virtual void write_json_attrs(json& o) const override {
        NodeFunction::write_json_attrs(o);
        o["static"] = is_static;
    }

    virtual void write_json(json& o) const override {
        o["kind"] = "Method";
        write_json_attrs(o);
        write_attrs_json(o);
        write_parameters_json(o);
    }
};

struct Field {
    std::string name;
    QType qtype;
};

struct NodeRecord : public NodeAttributeHolder {
    std::vector<Field> fields;
    std::vector<NodeId> methods;
    RecordKind record_kind;

    uint32_t size;
    uint32_t align;

    NodeRecord(std::string qualified_name, NodeId id, NodeId context,
               std::vector<std::string> attrs, RecordKind record_kind,
               uint32_t size, uint32_t align)
        : NodeAttributeHolder(qualified_name, id, context, NodeKind::Record,
                              attrs),
          record_kind(record_kind), size(size), align(align) {}

    virtual void write_xml_attrs(std::ostream& os) const override {
        Node::write_xml_attrs(os);
        os << " size=\"" << size << "\"";
        os << " align=\"" << align << "\"";
    }

    virtual void write_xml(std::ostream& os, int depth) const override {
        os << indent(depth) << "<Record";
        write_xml_attrs(os);
        os << ">\n";

        write_attrs(os, depth + 1);

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

    virtual void write_json_attrs(json& o) const override {
        NodeAttributeHolder::write_json_attrs(o);
        o["size"] = size;
        o["align"] = align;
    }

    virtual void write_json(json& o) const override {
        o["kind"] = "Record";
        write_json_attrs(o);
        write_attrs_json(o);

        o["fields"] = {};
        for (const auto& field: fields) {
            auto f = json::object();
            f["kind"] = "Field";
            f["name"] = field.name;
            f["type"] = json::object();
            field.qtype.write_json(f["type"]);
            o["fields"].emplace_back(f);
        }

        o["methods"] = {};
        for (const auto& method_id: methods) {
            auto m = json::object();
            NODES[method_id]->write_json(m);
            o["methods"].emplace_back(m);
        }
    }
};

void dump_nodes(std::ostream& os) {
    os << "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n";
    // ROOT here just contains all the NodeTranslationUnits, which themselves
    // contain all the Records and Functions
    for (const auto& id : ROOT) {
        NODES[id]->write_xml(os, 0);
    }
}

void write_tus() {
    for (const auto& id : ROOT) {
        NodeTranslationUnit* tu = (NodeTranslationUnit*)NODES[id].get();
        auto tu_path = fs::path(tu->qualified_name);
        auto stem = tu_path.stem();
        auto parent = tu_path.parent_path();
        auto out_path = fs::current_path() / stem;
        out_path += fs::path(".json");
        std::ofstream os;
        os.open(out_path.string(), std::ios::out | std::ios::trunc);
        /* tu->write_xml(os, 0); */
        auto j = json::object();
        tu->write_json(j);
        os << std::setw(4) << j;
    }
}

bool get_abi_info(const TypeDecl* td, ASTContext& ctx, uint32_t& size,
                  uint32_t& align) {
    if (td) {
        const clang::Type* ty = td->getTypeForDecl();
        if (!ty->isIncompleteType()) {
            const clang::TypeInfo& ti = ctx.getTypeInfo(ty);
            SPDLOG_DEBUG("    size: {}", ti.Width);
            SPDLOG_DEBUG("    align: {}", ti.Align);
            size = ti.Width;
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

// Get a NodeTranslationUnit for the given filename, creating one if it doesn't
// exist
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
                pointer_type_node_name, id, 0, pointer_type_name, pointer_kind,
                pointee_qtype);
            NODES.emplace_back(std::move(node_pointer_type));
            NODE_MAP[pointer_type_name] = id;
        } else {
            id = it->second;
        }

        return QType{id, qt.isConstQualified()};
    } else {
        std::string type_name = strip_name_kinds(
            qt.getCanonicalType().getUnqualifiedType().getAsString());
        std::string type_node_name = "TYPE:" + type_name;

        auto it = NODE_MAP.find(type_node_name);
        NodeId id;
        if (it == NODE_MAP.end()) {
            id = NODES.size();
            if (qt->isBuiltinType()) {
                auto node_type = std::make_unique<NodeBuiltinType>(
                    type_node_name, id, 0, type_name);
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

// Create Nodes for the function return type and parameters
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
    return strip_name_kinds(
        crd->getTypeForDecl()->getCanonicalTypeInternal().getAsString());
}

// extract all the methods on a decl and store them for later use. The resulting
// methods are NOT inserted in the AST or stored in the global node tables.
std::vector<NodePtr> process_methods(const CXXRecordDecl* crd) {
    std::vector<NodePtr> result;
    for (const Decl* d : crd->decls()) {
        // we want to ignore anything that's not public for obvious reasons
        // since we're using this function for getting methods both from the
        // library type and the binding type, this does mean we need to add a
        // "public" specifier to the binding type, but eh...
        if (d->getAccess() != AS_public) {
            continue;
        }
        std::vector<std::string> attrs = get_attrs(d);
        // A FunctionTemplateDecl represents methods that are dependent on
        // their own template parameters (aside from the Record template
        // parameter list).
        if (const FunctionTemplateDecl* ftd =
                dyn_cast<FunctionTemplateDecl>(d)) {
            for (const FunctionDecl* fd : ftd->specializations()) {
                const std::string function_name =
                    ftd->getQualifiedNameAsString();
                const std::string method_short_name = fd->getNameAsString();
                SPDLOG_DEBUG("    SPEC {}", function_name);
                QType return_qtype;
                std::vector<Param> params;
                process_function_parameters(fd, return_qtype, params);
                NodeId id = NODES.size();

                auto node_function = std::make_unique<NodeMethod>(
                    function_name, id, 0, std::move(attrs), method_short_name,
                    return_qtype, std::move(params), fd->isStatic());
                result.emplace_back(std::move(node_function));
            }
        } else if (const auto* cmd = dyn_cast<CXXMethodDecl>(d)) {
            if (!cmd->isUserProvided()) {
                // we only want methods that are explicitly declared in the
                // binding file
                continue;
            }
            const std::string method_name = cmd->getQualifiedNameAsString();
            const std::string method_short_name = cmd->getNameAsString();
            SPDLOG_DEBUG("    METHOD {}", method_name);

            QType return_qtype;
            std::vector<Param> params;
            process_function_parameters(cmd, return_qtype, params);
            NodeId id = NODES.size();

            auto node_function = std::make_unique<NodeMethod>(
                method_name, id, 0, std::move(attrs), method_short_name,
                return_qtype, std::move(params), cmd->isStatic());
            result.emplace_back(std::move(node_function));
        }
    }

    return result;
}

bool match_method(const NodeMethod* a, const NodeMethod* b) {
    if (a->short_name != b->short_name) {
        return false;
    }

    if (a->return_type != b->return_type) {
        return false;
    }

    if (a->params.size() != b->params.size()) {
        return false;
    }

    for (int i = 0; i < a->params.size(); ++i) {
        if (a->params[i].qty != b->params[i].qty) {
            return false;
        }
    }

    return true;
}

bool method_in_list(NodeMethod* m, const std::vector<NodePtr>& binding_methods,
                    std::vector<std::string>& attrs) {
    for (const auto& n : binding_methods) {
        const auto* b = (NodeMethod*)n.get();
        if (match_method(m, b)) {
            attrs = b->attrs;
            return true;
        }
    }
    return false;
}

// Generate the AST output for a Record which we've decided represents a
// concrete type (in the sense that all template parameters have been
// specialized)
void process_concrete_record(const CXXRecordDecl* crd, std::string filename,
                             std::vector<std::string> attrs,
                             std::vector<NodePtr> binding_methods) {
    ASTContext& ctx = crd->getASTContext();
    SourceManager& sm = ctx.getSourceManager();
    const auto& loc = crd->getLocation();

    crd = crd->getCanonicalDecl();
    const std::string record_name = get_record_name(crd);

    // Get the translation unit node we're going to add this Record to
    auto* node_tu = get_translation_unit(filename);

    // Get the size and alignment of the Record
    uint32_t size, align;
    if (!get_abi_info(dyn_cast<TypeDecl>(crd), ctx, size, align)) {
        SPDLOG_CRITICAL("Could not get ABI info for {}", record_name);
    }

    // Add the new Record node
    NodeId new_id = NODES.size();
    auto node_record =
        std::make_unique<NodeRecord>(record_name, new_id, 0, std::move(attrs),
                                     RecordKind::OpaquePtr, size, align);
    auto* node_record_ptr = node_record.get();
    NODES.emplace_back(std::move(node_record));
    NODE_MAP[record_name] = new_id;

    // add this record to the TU
    node_tu->children.push_back(new_id);

    std::vector<NodePtr> methods = process_methods(crd);
    for (NodePtr& method : methods) {
        NodeMethod* mptr = (NodeMethod*)method.get();
        if (method_in_list(mptr, binding_methods, attrs)) {
            mptr->attrs = std::move(attrs);
            mptr->in_binding = true;
        }

        NodeId id = NODES.size();
        NODE_MAP[method->qualified_name] = id;
        NODES.emplace_back(std::move(method));
        node_record_ptr->methods.push_back(id);
    }

    for (const Decl* d : crd->decls()) {
        if (const auto* fd = dyn_cast<FieldDecl>(d)) {
            const std::string field_name = fd->getNameAsString();
            SPDLOG_DEBUG("    FIELD {}", field_name);
            QType qtype = process_qtype(fd->getType());
            node_record_ptr->fields.push_back(Field{field_name, qtype.ty});
        }
    }

    // Finally...
    // if there's an existing RecordType node referring to this Record, then
    // set its record id to our new id
    auto it_record_type = NODE_MAP.find("TYPE:" + record_name);
    if (it_record_type != NODE_MAP.end()) {
        auto* node_record_type =
            (NodeRecordType*)NODES[it_record_type->second].get();
        node_record_type->record = new_id;
    }
}

// This function handles a CXXRecordDecl match. This will be called with the
// Record from the binding file, so we need to do a bit of preprocessing to make
// sure it's the right match, then get the actual type we're interested in from
// the library by inspecting the `using BoundType = XXX` decl on this Record.
// We'll also need to get any attributes from here, as well as pre-generating a
// list of matched methods
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

    // if we get down here then we have a concrete, sized type we can
    // process

    // first get the attrs
    std::vector<std::string> attrs = get_attrs(crd);

    // now get the methods so we can match
    std::vector<NodePtr> methods = process_methods(crd);

    // see if there's a BoundType typedef, and if so process the type that it
    // points to instead
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

            process_concrete_record(bound_rd, filename, std::move(attrs),
                                    std::move(methods));
            return;
        }
    }

    // // otherwise process this type (no real use in doing this - probably want
    // // to remove this)
    // process_concrete_record(crd, filename, std::move(attrs));
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

    if (const CXXRecordDecl* rec_decl =
            result.Nodes.getNodeAs<CXXRecordDecl>("recordDecl")) {
        handle_cxx_record_decl(rec_decl);
    }

    if (const TypeAliasDecl* tdecl =
            result.Nodes.getNodeAs<TypeAliasDecl>("typeAliasDecl")) {
        // tdecl->dump();
        if (const auto* crd =
                tdecl->getUnderlyingType()->getAsCXXRecordDecl()) {
            SPDLOG_DEBUG("GOT CXXRECORDTTYPE from TAD");
        }
    }
}

ProcessBindingConsumer::ProcessBindingConsumer(ASTContext* context) {
    // match all record declrations in the cppmm_bind namespace
    DeclarationMatcher record_decl_matcher =
        cxxRecordDecl(hasAncestor(namespaceDecl(hasName("cppmm_bind"))),
                      unless(isImplicit()))
            .bind("recordDecl");
    _match_finder.addMatcher(record_decl_matcher, &_handler);

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
