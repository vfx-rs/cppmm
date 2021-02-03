#include "process_binding.hpp"
#include "pystring.h"
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

#include <iomanip>
#include <iostream>

#include "filesystem.hpp"
namespace fs = ghc::filesystem;

#include <nlohmann/json.hpp>
using json = nlohmann::ordered_json;

using namespace clang;
using namespace clang::ast_matchers;
namespace ps = pystring;

extern std::unordered_map<std::string, std::vector<std::string>>
    source_includes;
extern std::vector<std::string> project_includes;

namespace cppmm {

namespace {

std::vector<std::string> get_attrs(const clang::Decl* decl) {
    std::vector<std::string> attrs;
    if (decl->hasAttrs()) {
        clang::ASTContext& ctx = decl->getASTContext();
        for (const auto& attr : decl->attrs()) {
            const clang::AnnotateAttr* ann =
                clang::dyn_cast<const clang::AnnotateAttr>(attr);
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
    EnumType,
    FunctionProtoType,
    Parm,
    Function,
    Method,
    Record,
    Enum,
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
    case NodeKind::EnumType:
        os << "EnumType";
        break;
    case NodeKind::FunctionProtoType:
        os << "FunctionProtoType";
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
    case NodeKind::Enum:
        os << "Enum";
        break;
    }
    return os;
}

enum class PointerKind : uint32_t {
    Pointer,
    Reference,
    RValueReference,
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

    virtual void write_json_attrs(json& o) const {
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
    std::vector<std::string> source_includes;
    std::vector<std::string> project_includes;

    virtual void write_json(json& o) const override {
        o["kind"] = "TranslationUnit";
        o["filename"] = qualified_name;
        o["source_includes"] = source_includes;
        o["include_paths"] = project_includes;
        write_json_attrs(o);

        o["decls"] = {};
        for (NodeId id : children) {
            const Node* node = NODES.at(id).get();
            auto child = json::object();
            node->write_json(child);
            o["decls"].emplace_back(std::move(child));
        }
    }

    NodeTranslationUnit(std::string qualified_name, NodeId id, NodeId context,
                        std::vector<std::string> source_includes,
                        std::vector<std::string> project_includes)
        : Node(qualified_name, id, context, NodeKind::TranslationUnit),
          source_includes(source_includes), project_includes(project_includes) {
    }
};

struct NodeNamespace : public Node {};

struct NodeType : public Node {
    std::string type_name;
    NodeType(std::string qualified_name, NodeId id, NodeId context,
             NodeKind node_kind, std::string type_name)
        : Node(qualified_name, id, context, node_kind), type_name(type_name) {}

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

    virtual void write_json(json& o) const override {
        o["kind"] = "BuiltinType";
        write_json_attrs(o);
    }
};

struct QType {
    NodeId ty;
    bool is_const;

    void write_json(json& o) const {
        if (ty >= 0) {
            NODES.at(ty)->write_json(o);
        } else {
            o["type"] = "UNKNOWN";
        }
        o["const"] = is_const;
    }

    bool operator==(const QType& rhs) const {
        return ty == rhs.ty && is_const == rhs.is_const;
    }

    bool operator!=(const QType& rhs) const { return !(*this == rhs); }
};

std::ostream& operator<<(std::ostream& os, const QType& q) {
    if (q.is_const) {
        os << "const ";
    }
    os << ((NodeType*)NODES.at(q.ty).get())->type_name;
    return os;
}

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

    virtual void write_json(json& o) const override {
        if (pointer_kind == PointerKind::Pointer) {
            o["kind"] = "Pointer";
        } else if (pointer_kind == PointerKind::RValueReference) {
            o["kind"] = "RValueReference";
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

    virtual void write_json_attrs(json& o) const override {
        NodeType::write_json_attrs(o);
        o["record"] = record;
    }

    virtual void write_json(json& o) const override {
        o["kind"] = "RecordType";
        write_json_attrs(o);
    }
};

struct NodeEnumType : public NodeType {
    NodeId enm;
    NodeEnumType(std::string qualified_name, NodeId id, NodeId context,
                 std::string type_name, NodeId enm)
        : NodeType(qualified_name, id, context, NodeKind::EnumType, type_name),
          enm(enm) {}

    virtual void write_json_attrs(json& o) const override {
        NodeType::write_json_attrs(o);
        o["enum"] = enm;
    }

    virtual void write_json(json& o) const override {
        o["kind"] = "EnumType";
        write_json_attrs(o);
    }
};

struct NodeFunctionProtoType : public NodeType {
    QType return_type;
    std::vector<QType> params;
    NodeFunctionProtoType(std::string qualified_name, NodeId id, NodeId context,
                          std::string type_name, QType return_type,
                          std::vector<QType> params)
        : NodeType(qualified_name, id, context, NodeKind::FunctionProtoType,
                   type_name),
          return_type(std::move(return_type)), params(std::move(params)) {}

    virtual void write_json_attrs(json& o) const override {
        NodeType::write_json_attrs(o);
    }

    virtual void write_json(json& o) const override {
        o["kind"] = "FunctionProtoType";

        write_json_attrs(o);

        o["return"] = {};
        return_type.write_json(o["return"]);

        o["params"] = {};
        for (const auto& param : params) {
            auto p = json::object();
            p["type"] = json::object();
            param.write_json(p["type"]);
            o["params"].emplace_back(p);
        }
    }
};

struct Param {
    std::string name;
    QType qty;
    int index;
    std::vector<std::string> attrs;
};

std::ostream& operator<<(std::ostream& os, const Param& p) {
    return os << p.name << ": " << p.qty;
}

struct NodeAttributeHolder : public Node {
    std::vector<std::string> attrs;

    NodeAttributeHolder(std::string qualified_name, NodeId id, NodeId context,
                        NodeKind node_kind, std::vector<std::string> attrs)
        : Node(qualified_name, id, context, node_kind), attrs(attrs) {}

    virtual void write_json(json& o) const override = 0;

    // FIXME: worst naming ever
    virtual void write_attrs_json(json& o) const {
        o["attributes"] = {};
        for (const auto& a : attrs) {
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
        for (const auto& param : params) {
            auto p = json::object();
            p["index"] = param.index;
            p["name"] = param.name;
            p["type"] = json::object();
            p["attrs"] = param.attrs;
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

std::ostream& operator<<(std::ostream& os, const NodeFunction& f) {
    os << f.qualified_name << "(";
    for (const Param& p : f.params) {
        os << p << ", ";
    }
    os << ") -> " << f.return_type;
    return os;
}

struct NodeMethod : public NodeFunction {
    bool is_static = false;
    bool is_user_provided = false;
    bool is_const = false;
    bool is_virtual = false;
    bool is_overloaded_operator = false;
    bool is_copy_assignment_operator = false;
    bool is_move_assignment_operator = false;
    bool is_constructor = false;
    bool is_default_constructor = false;
    bool is_copy_constructor = false;
    bool is_move_constructor = false;
    bool is_conversion_decl = false;
    bool is_destructor = false;

    NodeMethod(std::string qualified_name, NodeId id, NodeId context,
               std::vector<std::string> attrs, std::string short_name,
               QType return_type, std::vector<Param> params, bool is_static)
        : NodeFunction(qualified_name, id, context, attrs, short_name,
                       return_type, params),
          is_static(is_static) {
        node_kind = NodeKind::Method;
    }

    virtual void write_json_attrs(json& o) const override {
        NodeFunction::write_json_attrs(o);
        o["static"] = is_static;
        o["user_provided"] = is_user_provided;
        o["const"] = is_const;
        o["virtual"] = is_virtual;
        o["overloaded_operator"] = is_overloaded_operator;
        o["copy_assignment_operator"] = is_copy_assignment_operator;
        o["move_assignment_operator"] = is_move_assignment_operator;
        o["constructor"] = is_constructor;
        o["copy_constructor"] = is_copy_constructor;
        o["move_constructor"] = is_move_constructor;
        o["conversion_decl"] = is_conversion_decl;
        o["destructor"] = is_destructor;
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

    virtual void write_json_attrs(json& o) const override {
        NodeAttributeHolder::write_json_attrs(o);
        o["size"] = size;
        o["align"] = align;
    }

    virtual void write_json(json& o) const override {
        o["kind"] = "Record";
        o["name"] = qualified_name;
        write_json_attrs(o);
        write_attrs_json(o);

        o["fields"] = {};
        for (const auto& field : fields) {
            auto f = json::object();
            f["kind"] = "Field";
            f["name"] = field.name;
            f["type"] = json::object();
            field.qtype.write_json(f["type"]);
            o["fields"].emplace_back(f);
        }

        o["methods"] = {};
        for (const auto& method_id : methods) {
            auto m = json::object();
            NODES.at(method_id)->write_json(m);
            o["methods"].emplace_back(m);
        }
    }
};

struct NodeEnum : public NodeAttributeHolder {
    std::vector<std::pair<std::string, std::string>> variants;
    std::string short_name;
    uint32_t size;
    uint32_t align;

    NodeEnum(std::string qualified_name, NodeId id, NodeId context,
             std::vector<std::string> attrs, std::string short_name,
             std::vector<std::pair<std::string, std::string>> variants,
             uint32_t size, uint32_t align)
        : NodeAttributeHolder(qualified_name, id, context, NodeKind::Enum,
                              attrs),
          short_name(short_name), variants(variants), size(size), align(align) {
    }

    virtual void write_json_attrs(json& o) const override {
        NodeAttributeHolder::write_json_attrs(o);
        o["size"] = size;
        o["align"] = align;
    }

    virtual void write_json(json& o) const override {
        o["kind"] = "Enum";
        o["name"] = qualified_name;
        write_json_attrs(o);
        write_attrs_json(o);

        o["variants"] = json::object();
        for (const auto& var : variants) {
            o["variants"][var.first] = var.second;
        }
    }
};

void write_tus(std::string output_dir) {
    for (const auto& id : ROOT) {
        NodeTranslationUnit* tu = (NodeTranslationUnit*)NODES.at(id).get();
        auto tu_path = fs::path(tu->qualified_name);
        auto stem = tu_path.stem();
        auto parent = tu_path.parent_path();
        auto out_path = output_dir / stem;
        out_path += fs::path(".json");
        std::ofstream os;
        os.open(out_path.string(), std::ios::out | std::ios::trunc);
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
            SPDLOG_TRACE("    size: {}", ti.Width);
            SPDLOG_TRACE("    align: {}", ti.Align);
            size = ti.Width;
            align = ti.Align;
            return true;
        } else {
            SPDLOG_TRACE("    is incomplete type");
        }
    } else {
        SPDLOG_TRACE("    is not a TypeDecl");
    }

    return false;
}

std::vector<std::string> get_source_includes(std::string filename) {
    auto it = source_includes.find(filename);
    if (it != source_includes.end()) {
        return it->second;
    } else {
        SPDLOG_WARN("No includes found for source file {}", filename);
        return {};
    }
}

// Get a NodeTranslationUnit for the given filename, creating one if it doesn't
// exist
NodeTranslationUnit* get_translation_unit(const std::string& filename) {
    auto it = NODE_MAP.find(filename);
    if (it != NODE_MAP.end()) {
        const auto& node = NODES.at(it->second);
        assert(node->node_kind == NodeKind::TranslationUnit &&
               "node is wrong type");
        return (NodeTranslationUnit*)node.get();
    }

    NodeId id = NODES.size();
    auto node = std::make_unique<NodeTranslationUnit>(
        filename, id, 0, get_source_includes(filename), project_includes);
    ROOT.push_back(id);
    auto* node_ptr = node.get();
    NODES.emplace_back(std::move(node));
    NODE_MAP[filename] = id;
    return node_ptr;
}

void handle_class_template_decl(const ClassTemplateDecl* ctd) {
    ASTContext& ctx = ctd->getASTContext();
    SourceManager& sm = ctx.getSourceManager();
    const auto& loc = ctd->getLocation();

    SPDLOG_TRACE("ClassTemplateDecl {:p} {} ({}:{})", (void*)ctd,
                 ctd->getQualifiedNameAsString(), sm.getFilename(loc).str(),
                 sm.getSpellingLineNumber(loc));

    const TemplateParameterList* tpl = ctd->getTemplateParameters();
    for (const NamedDecl* nd : *tpl) {
        SPDLOG_TRACE("        {}", nd->getQualifiedNameAsString());
    }
}

QType process_qtype(const QualType& qt);

NodeId process_function_proto_type(const FunctionProtoType* fpt,
                                   std::string type_name,
                                   std::string type_node_name) {
    auto it = NODE_MAP.find(type_node_name);
    if (it != NODE_MAP.end()) {
        // already have an entry for this
        return it->second;
    } else {
        QType return_type = process_qtype(fpt->getReturnType());
        std::vector<QType> params;
        for (const QualType& pqt : fpt->param_types()) {
            params.push_back(process_qtype(pqt));
        }

        NodeId id = NODES.size();
        auto node_ptr = std::make_unique<NodeFunctionProtoType>(
            type_node_name, id, 0, std::move(type_name), std::move(return_type),
            std::move(params));
        NODES.emplace_back(std::move(node_ptr));
        NODE_MAP[type_node_name] = id;
        return id;
    }
}

QType process_qtype(const QualType& qt) {
    if (qt->isPointerType() || qt->isReferenceType()) {
        auto pointer_kind = PointerKind::Pointer;
        if (qt->isRValueReferenceType()) {
            pointer_kind = PointerKind::RValueReference;
        } else if (qt->isReferenceType()) {
            pointer_kind = PointerKind::Reference;
        }

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
            } else if (qt->isEnumeralType()) {
                const auto* et = qt->getAs<EnumType>();
                assert(et && "Could not get EnumType from Type");
                const auto* ed = et->getDecl();
                assert(ed && "Could not get EnumDecl from EnumType");
                ed = ed->getCanonicalDecl();
                assert(ed && "Could not get canonical EnumDecl from EnumType");

                // see if we've already processed an enum matching this type
                // and get its id if we have
                const std::string enum_qual_name =
                    ed->getQualifiedNameAsString();
                NodeId id_enum = -1;
                auto it_enum = NODE_MAP.find(enum_qual_name);
                if (it_enum != NODE_MAP.end()) {
                    id_enum = it_enum->second;
                }

                auto node_enum_type = std::make_unique<NodeEnumType>(
                    type_node_name, id, 0, type_name, id_enum);
                NODES.emplace_back(std::move(node_enum_type));
                NODE_MAP[type_node_name] = id;
            } else if (qt->isFunctionProtoType()) {
                const auto* fpt = qt->getAs<FunctionProtoType>();
                assert(fpt && "Could not get FunctionProtoType from QualType");

                id =
                    process_function_proto_type(fpt, type_name, type_node_name);
            } else {
                SPDLOG_WARN("Unhandled type {}", type_node_name);
                qt->dump();
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
    SPDLOG_TRACE("    -> {}", fd->getReturnType().getAsString());
    return_qtype = process_qtype(fd->getReturnType());

    for (const ParmVarDecl* pvd : fd->parameters()) {
        int index = pvd->getFunctionScopeIndex();
        SPDLOG_TRACE("        {}: {}", pvd->getQualifiedNameAsString(),
                     pvd->getType().getCanonicalType().getAsString());
        QType qtype = process_qtype(pvd->getType());

        params.emplace_back(
            Param{pvd->getNameAsString(), qtype, index, get_attrs(pvd)});

        if (const auto* vtd = pvd->getDescribedVarTemplate()) {
            SPDLOG_TRACE("            GOT VTD");
        }
        if (const auto* td = pvd->getDescribedTemplate()) {
            SPDLOG_TRACE("            GOT TD");
        }
    }
}

std::string get_record_name(const CXXRecordDecl* crd) {
    // we have to do this dance to get the template parameters in the name,
    // otherwise they're omitted
    return strip_name_kinds(
        crd->getTypeForDecl()->getCanonicalTypeInternal().getAsString());
}

NodePtr process_method_decl(const CXXMethodDecl* cmd,
                            std::vector<std::string> attrs) {
    const std::string method_name = cmd->getQualifiedNameAsString();
    const std::string method_short_name = cmd->getNameAsString();
    SPDLOG_TRACE("    METHOD {}", method_name);

    QType return_qtype;
    std::vector<Param> params;
    process_function_parameters(cmd, return_qtype, params);

    auto node_function = std::make_unique<NodeMethod>(
        method_name, 0, 0, std::move(attrs), method_short_name, return_qtype,
        std::move(params), cmd->isStatic());

    NodeMethod* m = (NodeMethod*)node_function.get();
    m->is_user_provided = cmd->isUserProvided();
    m->is_const = cmd->isConst();
    m->is_virtual = cmd->isVirtual();
    m->is_overloaded_operator = cmd->isOverloadedOperator();
    m->is_copy_assignment_operator = cmd->isCopyAssignmentOperator();
    m->is_move_assignment_operator = cmd->isMoveAssignmentOperator();

    if (const auto* ccd = dyn_cast<CXXConstructorDecl>(cmd)) {
        m->is_constructor = true;
        m->is_copy_constructor = ccd->isCopyConstructor();
        m->is_move_constructor = ccd->isMoveConstructor();
    } else if (const auto* cdd = dyn_cast<CXXDestructorDecl>(cmd)) {
        m->is_destructor = true;
    } else if (const auto* ccd = dyn_cast<CXXConversionDecl>(cmd)) {
        m->is_conversion_decl = true;
    }

    return node_function;
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
        // A FunctionTemplateDecl represents methods that are dependent on
        // their own template parameters (aside from the Record template
        // parameter list).
        if (const FunctionTemplateDecl* ftd =
                dyn_cast<FunctionTemplateDecl>(d)) {
            for (const FunctionDecl* fd : ftd->specializations()) {
                std::vector<std::string> attrs = get_attrs(fd);
                if (const auto* cmd = dyn_cast<CXXMethodDecl>(fd)) {
                    auto node_function = process_method_decl(cmd, attrs);
                    result.emplace_back(std::move(node_function));
                } else {
                    // shouldn't get here
                    assert(false && "method spec couldn't be converted to CMD");
                    const std::string function_name =
                        ftd->getQualifiedNameAsString();
                    const std::string method_short_name = fd->getNameAsString();
                    QType return_qtype;
                    std::vector<Param> params;
                    process_function_parameters(fd, return_qtype, params);

                    auto node_function = std::make_unique<NodeMethod>(
                        function_name, -1, -1, std::move(attrs),
                        method_short_name, return_qtype, std::move(params),
                        fd->isStatic());
                    result.emplace_back(std::move(node_function));
                }
            }
        } else if (const auto* cmd = dyn_cast<CXXMethodDecl>(d)) {
            std::vector<std::string> attrs = get_attrs(d);
            auto node_function = process_method_decl(cmd, attrs);
            result.emplace_back(std::move(node_function));
        }
    }

    return result;
}

bool match_function(const NodeFunction* a, const NodeFunction* b) {
    SPDLOG_TRACE("        matching {} with {}", a->qualified_name,
                 b->qualified_name);
    if (a->short_name != b->short_name) {
        return false;
    }

    if (a->return_type != b->return_type) {
        SPDLOG_TRACE("        match failed because return types do not match");
        return false;
    }

    if (a->params.size() != b->params.size()) {
        SPDLOG_TRACE(
            "        match failed because number of params do not match");
        return false;
    }

    for (int i = 0; i < a->params.size(); ++i) {
        if (a->params[i].qty != b->params[i].qty) {
            Node* n_a = NODES.at(a->params[i].qty.ty).get();
            Node* n_b = NODES.at(b->params[i].qty.ty).get();
            SPDLOG_TRACE("        match failed because param {} does "
                         "not match. {} {} != {} {}",
                         i, a->params[i].qty.ty, n_a->qualified_name,
                         b->params[i].qty.ty, n_b->qualified_name);
            return false;
        }
    }

    return true;
}

bool match_method(const NodeMethod* a, const NodeMethod* b) {

    if (a->is_const != b->is_const) {
        return false;
    }

    if (!match_function(a, b)) {
        return false;
    }

    return true;
}

bool method_in_list(NodeMethod* m, const std::vector<NodePtr>& binding_methods,
                    std::vector<std::string>& attrs) {
    for (const auto& n : binding_methods) {
        const auto* b = (NodeMethod*)n.get();
        if (match_method(m, b)) {
            attrs = b->attrs;
            m->params = b->params;
            return true;
        }
    }
    SPDLOG_TRACE("Method {} did not match", m->qualified_name);
    return false;
}

void process_enum_decl(const EnumDecl* ed, std::string filename) {
    ed = ed->getCanonicalDecl();
    const std::string enum_name = ed->getQualifiedNameAsString();
    const std::string enum_short_name = ed->getNameAsString();
    ASTContext& ctx = ed->getASTContext();
    uint32_t size, align;
    if (!get_abi_info(dyn_cast<TypeDecl>(ed), ctx, size, align)) {
        SPDLOG_CRITICAL("Could not get ABI info for {}", enum_name);
    }

    std::vector<std::pair<std::string, std::string>> variants;
    for (const auto& ecd : ed->enumerators()) {
        SPDLOG_DEBUG("        {}", ecd->getNameAsString());
        variants.push_back(std::make_pair(ecd->getNameAsString(),
                                          ecd->getInitVal().toString(10)));
    }

    // Get the translation unit node we're going to add this Enum to
    auto* node_tu = get_translation_unit(filename);

    std::vector<std::string> attrs = get_attrs(ed);

    NodeId new_id = NODES.size();
    auto node_enum =
        std::make_unique<NodeEnum>(enum_name, new_id, 0, std::move(attrs),
                                   enum_short_name, variants, size, align);
    NODES.emplace_back(std::move(node_enum));
    NODE_MAP[enum_name] = new_id;
    // add this record to the TU
    node_tu->children.push_back(new_id);

    // Find any EnumType nodes that need the new id
    auto it_enum_type = NODE_MAP.find("TYPE:" + enum_name);
    if (it_enum_type != NODE_MAP.end()) {
        auto* node_enum_type =
            (NodeEnumType*)NODES.at(it_enum_type->second).get();
        node_enum_type->enm = new_id;
    }
}

// Generate the AST output for a Record which we've decided represents a
// concrete type (in the sense that all template parameters have been
// specialized)
void process_concrete_record(const CXXRecordDecl* crd, std::string filename,
                             std::vector<std::string> attrs,
                             std::vector<NodePtr> binding_methods,
                             std::vector<std::string> child_enums) {
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
    auto node_record = std::make_unique<NodeRecord>(
        record_name, new_id, node_tu->id, std::move(attrs),
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
        } else {
            // TODO: decide what we really want to do here.
            // For now, ignoring unmatched methods makes dev easier by cutting
            // out noise
            continue;
        }

        NodeId id = NODES.size();
        NODE_MAP[method->qualified_name] = id;
        NODES.emplace_back(std::move(method));
        node_record_ptr->methods.push_back(id);
    }

    for (const Decl* d : crd->decls()) {
        if (const auto* fd = dyn_cast<FieldDecl>(d)) {
            const std::string field_name = fd->getNameAsString();
            SPDLOG_TRACE("    FIELD {}", field_name);
            QType qtype = process_qtype(fd->getType());
            node_record_ptr->fields.push_back(Field{field_name, qtype.ty});
        } else if (const auto* md = dyn_cast<CXXMethodDecl>(d)) {
            // pass
        } else if (const auto* fd = dyn_cast<FunctionDecl>(d)) {
            // SPDLOG_DEBUG(" FUNCTION {}", fd->getQualifiedNameAsString());
        } else if (const auto* ed = dyn_cast<EnumDecl>(d)) {
            // SPDLOG_DEBUG("Got enum decl {}", ed->getNameAsString());
            if (std::find(child_enums.begin(), child_enums.end(),
                          ed->getNameAsString()) != child_enums.end()) {
                process_enum_decl(ed, filename);
            }
        }
    }

    // Finally...
    // if there's an existing RecordType node referring to this Record, then
    // set its record id to our new id
    auto it_record_type = NODE_MAP.find("TYPE:" + record_name);
    if (it_record_type != NODE_MAP.end()) {
        auto* node_record_type =
            (NodeRecordType*)NODES.at(it_record_type->second).get();
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
    for (const auto& n : methods) {
        const auto& m = *(NodeMethod*)n.get();
        SPDLOG_DEBUG("Adding binding method {}", m);
    }

    // see if there's a BoundType typedef, and if so process the type that it
    // points to instead
    std::vector<std::string> child_enums;
    const CXXRecordDecl* bound_rd = nullptr;
    for (const auto* decl : crd->decls()) {
        if (const auto* tad = dyn_cast<TypeAliasDecl>(decl)) {
            SPDLOG_DEBUG("TAD {}", tad->getNameAsString());
            const auto* bound_nd = tad->getUnderlyingDecl();
            if (tad->getNameAsString() == "BoundType") {
                SPDLOG_TRACE(
                    "Found BoundType {}",
                    tad->getUnderlyingDecl()->getQualifiedNameAsString());

                bound_rd = tad->getUnderlyingType()->getAsCXXRecordDecl();
            }
        } else if (const auto* ed = dyn_cast<EnumDecl>(decl)) {
            // this gets `using Enum = Library::Class::Enum`
            SPDLOG_DEBUG("got bound enum decl {}",
                         ed->getQualifiedNameAsString());
            child_enums.push_back(ed->getNameAsString());
        }
    }

    if (bound_rd) {
        process_concrete_record(bound_rd, filename, std::move(attrs),
                                std::move(methods), std::move(child_enums));
    }

    // // otherwise process this type (no real use in doing this - probably want
    // // to remove this)
    // process_concrete_record(crd, filename, std::move(attrs));
}

std::unordered_map<std::string, std::vector<NodeFunction>> binding_functions;
std::unordered_map<std::string, NodeEnum> binding_enums;

void handle_binding_function(const FunctionDecl* fd) {
    const std::string function_qual_name =
        pystring::replace(fd->getQualifiedNameAsString(), "cppmm_bind::", "");
    const std::string function_short_name = fd->getNameAsString();
    SPDLOG_DEBUG("    BIND FUNCTION {}", function_qual_name);

    ASTContext& ctx = fd->getASTContext();
    SourceManager& sm = ctx.getSourceManager();
    const auto& loc = fd->getLocation();
    std::string filename = sm.getFilename(loc).str();

    // Get the translation unit node we're going to add this Function to
    auto* node_tu = get_translation_unit(filename);

    auto attrs = get_attrs(fd);

    QType return_qtype;
    std::vector<Param> params;
    process_function_parameters(fd, return_qtype, params);
    // NodeId id = NODES.size();

    auto it = binding_functions.find(function_qual_name);
    auto node_function =
        NodeFunction(function_qual_name, 0, node_tu->id, std::move(attrs),
                     function_short_name, return_qtype, std::move(params));

    SPDLOG_DEBUG("Adding binding function {}", node_function);

    if (it != binding_functions.end()) {
        it->second.emplace_back(std::move(node_function));
    } else {
        binding_functions[function_qual_name] = {node_function};
    }
}

void handle_binding_enum(const EnumDecl* ed) {
    const std::string enum_qual_name =
        pystring::replace(ed->getQualifiedNameAsString(), "cppmm_bind::", "");
    const std::string enum_short_name = ed->getNameAsString();
    SPDLOG_DEBUG("    BIND ENUM {}", enum_qual_name);

    ASTContext& ctx = ed->getASTContext();
    SourceManager& sm = ctx.getSourceManager();
    const auto& loc = ed->getLocation();
    std::string filename = sm.getFilename(loc).str();

    // Get the translation unit node we're going to add this Enum to
    auto* node_tu = get_translation_unit(filename);

    auto attrs = get_attrs(ed);

    auto node_enum = NodeEnum(enum_qual_name, -1, node_tu->id, std::move(attrs),
                              enum_short_name, {}, 0, 0);
    binding_enums.insert(std::make_pair(enum_qual_name, std::move(node_enum)));
}

void handle_function(const FunctionDecl* fd) {

    const std::string function_qual_name = fd->getQualifiedNameAsString();
    const std::string function_short_name = fd->getNameAsString();

    auto it = binding_functions.find(function_qual_name);
    if (it == binding_functions.end()) {
        SPDLOG_CRITICAL(
            "function {} matched but is not present in binding functions table",
            function_qual_name);
        return;
    }

    QType return_qtype;
    std::vector<Param> params;
    process_function_parameters(fd, return_qtype, params);
    auto node_function =
        NodeFunction(function_qual_name, 0, 0, {}, function_short_name,
                     return_qtype, std::move(params));

    // find a match in the overloads
    for (const auto& binding_fn : it->second) {
        if (match_function(&node_function, &binding_fn)) {
            // we have a match. copy over the attributes and store this function
            node_function.attrs = binding_fn.attrs;
            node_function.context = binding_fn.context;
            auto fnptr =
                std::make_unique<NodeFunction>(std::move(node_function));
            NodeId id = NODES.size();
            fnptr->id = id;
            // add the function to its TU
            SPDLOG_DEBUG("MATCHED {}", function_qual_name);
            auto* node_tu =
                (NodeTranslationUnit*)NODES.at(node_function.context).get();
            fnptr->context = node_tu->id;
            node_tu->children.push_back(id);
            NODES.emplace_back(std::move(fnptr));
        }
    }
}

void handle_enum(const EnumDecl* ed) {
    const std::string enum_qual_name = ed->getQualifiedNameAsString();
    auto it = binding_enums.find(enum_qual_name);
    if (it == binding_enums.end()) {
        return;
    }

    const std::string filename =
        ((NodeTranslationUnit*)NODES.at(it->second.context).get())
            ->qualified_name;

    process_enum_decl(ed, std::move(filename));
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
    } else if (const TypeAliasDecl* tdecl =
                   result.Nodes.getNodeAs<TypeAliasDecl>("typeAliasDecl")) {
        if (const auto* crd =
                tdecl->getUnderlyingType()->getAsCXXRecordDecl()) {
            SPDLOG_TRACE("GOT CXXRECORDTTYPE from TAD");
        }
    } else if (const FunctionDecl* function =
                   result.Nodes.getNodeAs<FunctionDecl>("functionDecl")) {
        handle_binding_function(function);
    } else if (const EnumDecl* enum_decl =
                   result.Nodes.getNodeAs<EnumDecl>("enumDecl")) {
        handle_binding_enum(enum_decl);
    }
}

void ProcessLibraryCallback::run(const MatchFinder::MatchResult& result) {
    if (const FunctionDecl* fd =
            result.Nodes.getNodeAs<FunctionDecl>("libraryFunctionDecl")) {
        handle_function(fd);
    } else if (const EnumDecl* ed =
                   result.Nodes.getNodeAs<EnumDecl>("libraryEnumDecl")) {
        handle_enum(ed);
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

    // match all function declarations
    DeclarationMatcher function_decl_matcher =
        functionDecl(hasAncestor(namespaceDecl(hasName("cppmm_bind"))),
                     unless(hasAncestor(recordDecl())))
            .bind("functionDecl");
    _match_finder.addMatcher(function_decl_matcher, &_handler);

    // match all enum declrations in the cppmm_bind namespace
    DeclarationMatcher enum_decl_matcher =
        enumDecl(hasAncestor(namespaceDecl(hasName("cppmm_bind"))),
                 unless(isImplicit()))
            .bind("enumDecl");
    _match_finder.addMatcher(enum_decl_matcher, &_handler);
}

void ProcessBindingConsumer::HandleTranslationUnit(ASTContext& context) {
    _match_finder.matchAST(context);
    SPDLOG_DEBUG("--- finished matching");
    for (const auto& fn : binding_functions) {
        SPDLOG_DEBUG("    {}", fn.first);
    }

    // add a matcher for each function we found in the binding
    for (const auto& kv : binding_functions) {
        for (const auto& fn : kv.second) {
            SPDLOG_DEBUG("Adding matcher for function {}", fn.short_name);
            DeclarationMatcher function_decl_matcher =
                functionDecl(
                    hasName(fn.short_name),
                    unless(hasAncestor(namespaceDecl(hasName("cppmm_bind")))),
                    unless(hasAncestor(recordDecl())))
                    .bind("libraryFunctionDecl");
            _library_finder.addMatcher(function_decl_matcher,
                                       &_library_handler);
        }
    }

    // and a matcher for each enum
    for (const auto& kv : binding_enums) {
        SPDLOG_DEBUG("Adding matcher for enum {}", kv.first);
        DeclarationMatcher function_decl_matcher =
            functionDecl(
                hasName(kv.second.short_name),
                unless(hasAncestor(namespaceDecl(hasName("cppmm_bind")))),
                unless(hasAncestor(recordDecl())))
                .bind("libraryEnumDecl");
        _library_finder.addMatcher(function_decl_matcher, &_library_handler);
    }

    _library_finder.matchAST(context);
}

} // namespace cppmm
