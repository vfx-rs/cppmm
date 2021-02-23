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
#include <cassert>
#include <cstdint>
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

/// Get any annotation attributes on the given Decl and return their values as
/// a vector of strings
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

/// Strip the type kinds off the front of a type name in the given string
std::string strip_name_kinds(std::string s) {
    s = pystring::replace(s, "class ", "");
    s = pystring::replace(s, "struct ", "");
    s = pystring::replace(s, "enum ", "");
    s = pystring::replace(s, "union ", "");
    return s;
}

} // namespace

/// Enumerates the kinds of nodes in the output AST
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
    ConstantArrayType,
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

/// Enumerates the different kinds of pointers and references
enum class PointerKind : uint32_t {
    Pointer,
    Reference,
    RValueReference,
};

/// Enumerates the different kinds of records.
/// OpaquePtr = opaque pointer to a C++ library type
/// OpaqueBytes = opaque bag of bytes containing a C++ library type
/// ValueType = C++ library type that is C-compatible (POD only)
enum class RecordKind : uint32_t { OpaquePtr = 0, OpaqueBytes, ValueType };

/// Typedef for representing a node in the AST. Signed int because we're
/// outputting to json
using NodeId = int32_t;

/// Abstract base struct for a node in the AST
struct Node {
    std::string qualified_name;
    NodeId id;
    NodeId context; //< parent context (e.g. record, namespce, TU)
    NodeKind node_kind;

    Node(std::string qualified_name, NodeId id, NodeId context,
         NodeKind node_kind)
        : qualified_name(qualified_name), id(id), context(context),
          node_kind(node_kind) {}

    virtual ~Node() {}

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

/// Flat storage for nodes in the AST
std::vector<NodePtr> NODES;
/// Map for name-lookup of nodes (keys should match Node::qualified_name)
std::unordered_map<std::string, NodeId> NODE_MAP;
/// Root of the AST - will contain NodeTranslationUnits, which will themselves
/// contain the rest of the tree
std::vector<NodeId> ROOT;

/// Represents one translation unit (TU), i.e. one binding source file.
/// NodeTranslationUnit::qualified_name contains the filename
struct NodeTranslationUnit : public Node {
    /// Other nodes bound in this TU
    std::vector<NodeId> children;
    /// Include statements from the binding file
    std::vector<std::string> source_includes;
    /// Include paths specified on the cppmm command line
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

/// Namespace node. Currently not used
struct NodeNamespace : public Node {
    std::string short_name;

    NodeNamespace(std::string qualified_name, NodeId id, NodeId context,
                  std::string short_name)
        : Node(std::move(qualified_name), id, context, NodeKind::Namespace),
          short_name(std::move(short_name)) {}

    virtual void write_json_attrs(json& o) const override {
        Node::write_json_attrs(o);
        o["short_name"] = short_name;
    }

    virtual void write_json(json& o) const override {
        o["kind"] = "Namespace";
        o["name"] = qualified_name;
        write_json_attrs(o);
    }
};

/// Base struct represent a node that stores a type.
/// Types are references to the actual record and enum declarations that
/// describe those objects' structure. They are stored in the graph so that
/// types and the objects they reference can be processed out-of-order and then
/// the references fixed up later.
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

/// A builtin, e.g. int, bool, char etc.
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

/// QType is the equivalent of clang's QualType. Currently just defines the
/// constness of the wrapped type node. These are stored on the AST nodes
/// anywhere a type is needed.
struct QType {
    /// Type we're constifying
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

/// A pointer or reference type. The pointee is stored in pointee_type
struct NodePointerType : public NodeType {
    /// Type we're pointing to
    QType pointee_type;
    /// Is this a pointer, reference or r-value reference?
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

/// A C-style array, e.g. float[3]
struct NodeConstantArrayType : public NodeType {
    QType element_type;
    uint64_t size;

    NodeConstantArrayType(std::string qualified_name, NodeId id, NodeId context,
                          std::string type_name, QType element_type,
                          uint64_t size)
        : NodeType(std::move(qualified_name), id, context,
                   NodeKind::ConstantArrayType, std::move(type_name)),
          element_type(element_type), size(size) {}

    virtual void write_json(json& o) const override {
        o["kind"] = "ConstantArrayType";
        write_json_attrs(o);

        o["size"] = size;
        o["element_type"] = {};
        element_type.write_json(o["element_type"]);
    }
};

/// A reference to a record (i.e. a class or struct)
struct NodeRecordType : public NodeType {
    /// The record declaration node, i.e. the actual type declaration. If the
    /// record referred to hasn't been processed yet, then this will be -1 until
    /// such a time as the record is processed
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

/// An enum type reference
struct NodeEnumType : public NodeType {
    /// The enum declaration node, i.e. the actual type declaration. If the
    /// enum referred to hasn't been processed yet, then this will be -1 until
    /// such a time as the enum is processed
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

/// A function prototype (a pointer to which can be passed as callbacks etc).
/// This sits in an awkward spot because there isn't a corresponding decl so all
/// the structure is packed onto the type node here
struct NodeFunctionProtoType : public NodeType {
    /// Return type of the function
    QType return_type;
    /// Function parameters
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

/// Param is essentially just a (name, type) pair forming a function parameter.
struct Param {
    /// parameter name
    std::string name;
    /// parameter type
    QType qty;
    /// index of the parameter in the function's parameter list
    int index;
    /// Any annnotation attributes on the parameter
    std::vector<std::string> attrs;
};

std::ostream& operator<<(std::ostream& os, const Param& p) {
    return os << p.name << ": " << p.qty;
}

/// Base struct representing a node that has annotation attributes attached
struct NodeAttributeHolder : public Node {
    /// The annotation attributes
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

/// A function node
struct NodeFunction : public NodeAttributeHolder {
    /// What you think of as the function name without any qualifications
    std::string short_name;
    /// The function's return type
    QType return_type;
    /// The function's parameters
    std::vector<Param> params;
    /// Is this function declared in the binding? NOT USED
    bool in_binding = false;
    /// Is this function declared in the library? NOT USED
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

/// A method on a class or struct.
struct NodeMethod : public NodeFunction {
    bool is_static = false;
    /// Is the method user-provided (i.e. !default)
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
    /// Is the method a conversion decl, e.g. "operator bool()"
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

/// A field of a class or struct as a (name, type) pair
struct Field {
    std::string name;
    QType qtype;
};

/// A record is a class or struct declaration containing fields and methods
struct NodeRecord : public NodeAttributeHolder {
    std::vector<Field> fields;
    std::vector<NodeId> methods;
    /// The 'leaf' of the qualified name
    std::string short_name;
    /// The full path of namespaces leading to this record
    std::vector<NodeId> namespaces;
    /// Alias for the record, set by e.g.:
    /// using V3f = Imath::Vec3<float>;
    std::string alias;
    /// The kind of the record, i.e. how we want it to be represented in C.
    /// See the RecordKind enum for more info
    RecordKind record_kind;

    /// Size of the record, in bits
    uint32_t size;
    /// Alignment of the record, in bits
    uint32_t align;

    NodeRecord(std::string qualified_name, NodeId id, NodeId context,
               std::vector<std::string> attrs, std::string short_name,
               std::vector<NodeId> namespaces, RecordKind record_kind,
               uint32_t size, uint32_t align)
        : NodeAttributeHolder(qualified_name, id, context, NodeKind::Record,
                              attrs),
          short_name(std::move(short_name)), namespaces(std::move(namespaces)),
          record_kind(record_kind), size(size), align(align) {}

    virtual void write_json_attrs(json& o) const override {
        NodeAttributeHolder::write_json_attrs(o);
        o["size"] = size;
        o["align"] = align;
        if (!alias.empty()) {
            o["alias"] = alias;
        } else {
            o["alias"] = short_name;
        }
    }

    virtual void write_json(json& o) const override {
        o["kind"] = "Record";
        o["name"] = qualified_name;
        o["short_name"] = short_name;
        o["namespaces"] = namespaces;
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

/// An enum declaration, just a list of (name, value) pairs of the variants
struct NodeEnum : public NodeAttributeHolder {
    /// C++ allows variant values larger than an int, while C only allows ints.
    /// Without knowing what the values are, it's impossible to say what type
    /// we'll need to store the values here. Most likely an int would be fine,
    /// but we can't rely on people not using crazy sentinel values, so we
    /// store it as a string and kick the can down the road to the generator
    std::vector<std::pair<std::string, std::string>> variants;
    /// Name of the enum without any qualifiers
    std::string short_name;
    /// Full namespace path
    std::vector<NodeId> namespaces;
    /// Size of the enum in bits
    uint32_t size;
    /// Alignment of the enum in bits
    uint32_t align;

    NodeEnum(std::string qualified_name, NodeId id, NodeId context,
             std::vector<std::string> attrs, std::string short_name,
             std::vector<NodeId> namespaces,
             std::vector<std::pair<std::string, std::string>> variants,
             uint32_t size, uint32_t align)
        : NodeAttributeHolder(qualified_name, id, context, NodeKind::Enum,
                              attrs),
          short_name(std::move(short_name)), namespaces(std::move(namespaces)),
          variants(variants), size(size), align(align) {}

    virtual void write_json_attrs(json& o) const override {
        NodeAttributeHolder::write_json_attrs(o);
        o["size"] = size;
        o["align"] = align;
    }

    virtual void write_json(json& o) const override {
        o["kind"] = "Enum";
        o["name"] = qualified_name;
        o["short_name"] = short_name;
        o["namespaces"] = namespaces;
        write_json_attrs(o);
        write_attrs_json(o);

        o["variants"] = json::object();
        for (const auto& var : variants) {
            o["variants"][var.first] = var.second;
        }
    }
};

/// Write out the AST to json output files. Each NodeTranslationUnit which
/// is a child of the ROOT is written to its own json file and all decls in
/// that TU are written recursively
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

/// Get the size and alignment for the given decl. Returns true if the info
/// could be ascertained, false otherwise.
bool get_abi_info(const TypeDecl* td, ASTContext& ctx, uint32_t& size,
                  uint32_t& align) {
    if (td) {
        const clang::Type* ty = td->getTypeForDecl();
        if (!ty->isIncompleteType()) {
            const clang::TypeInfo& ti = ctx.getTypeInfo(ty);
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

/// Parse the include statements from the given C++ file
std::vector<std::string> get_source_includes(std::string filename) {
    auto it = source_includes.find(filename);
    if (it != source_includes.end()) {
        return it->second;
    } else {
        SPDLOG_WARN("No includes found for source file {}", filename);
        return {};
    }
}

/// Find the node corresponding to the given TU filename, creating one if
/// none exists
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

QType process_qtype(const QualType& qt);

/// Create a new NodeFunctionProtoType from the given FunctionProtoType and
/// return its id.
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

/// Create a QType from the given QualType. Recursively processes the contained
/// types.
QType process_qtype(const QualType& qt) {
    if (qt->isPointerType() || qt->isReferenceType()) {
        // first, figure out what kind of pointer we have
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
            // already done this type
            id = it->second;
        }

        return QType{id, qt.isConstQualified()};
    } else if (qt->isConstantArrayType()) {
        // e.g. float[3]
        const std::string type_name = qt.getCanonicalType().getAsString();
        const std::string type_node_name = "TYPE:" + type_name;
        auto it = NODE_MAP.find(type_node_name);
        NodeId id;
        if (it == NODE_MAP.end()) {
            const ConstantArrayType* cat =
                dyn_cast<ConstantArrayType>(qt.getTypePtr());
            QType element_type = process_qtype(cat->getElementType());
            id = NODES.size();
            auto node_type = std::make_unique<NodeConstantArrayType>(
                type_node_name, id, 0, type_name, element_type,
                cat->getSize().getLimitedValue());
            NODES.emplace_back(std::move(node_type));
            NODE_MAP[type_node_name] = id;
        } else {
            id = it->second;
        }

        return QType{id, qt.isConstQualified()};
    } else {
        // regular type, let's get a nice name for it by removing the
        // class/struct/enum/union qualifier clang adds
        std::string type_name = strip_name_kinds(
            qt.getCanonicalType().getUnqualifiedType().getAsString());
        // We need to store type nodes for later access, since we might process
        // the corresponding record decl after processing this type node, and
        // will need to look it up later to set the appropriate id.
        // to get around the fact that the type and the record it refers to will
        // have the same name, we just prepend "TYPE:" to the type node name
        // here.
        // FIXME: we might want to stores types in a completely separate data
        // structure
        std::string type_node_name = "TYPE:" + type_name;

        // see if we've proessed this type already
        auto it = NODE_MAP.find(type_node_name);
        NodeId id;
        if (it == NODE_MAP.end()) {
            // haven't done this type yet we'll need to create a new node for it
            id = NODES.size();
            if (qt->isBuiltinType()) {
                // It's just a builtin. We store its name
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
                // and get its id if we have. If not we'll store -1 until we
                // come back and process the decl later.
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
                // and get its id if we have. If not we'll store -1 until we
                // come back and process the decl later.
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

/// Create nodes for the function return type and parameters
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

/// Get a nice, qualified name for the given record
std::string get_record_name(const CXXRecordDecl* crd) {
    // we have to do this dance to get the template parameters in the name,
    // otherwise they're omitted
    return strip_name_kinds(
        crd->getTypeForDecl()->getCanonicalTypeInternal().getAsString());
}

/// Create a new node for the given method decl and return it
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
//
/// Determine if two functions are equivalent. Equivalent in this case means
/// that their return types and parameters are the same and they have the
/// same short (not qualified) name
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

/// Determine if two methods are equivalent. In addition to function equivalence
/// this also checks whether the methods have the same const-ness and
/// static-ness
bool match_method(const NodeMethod* a, const NodeMethod* b) {

    if (a->is_const != b->is_const) {
        return false;
    }

    if (a->is_static != b->is_static) {
        return false;
    }

    if (!match_function(a, b)) {
        return false;
    }

    return true;
}

void add_method_to_list(NodePtr method,
                        std::vector<NodePtr>& existing_methods) {
    auto it = std::find_if(existing_methods.begin(), existing_methods.end(),
                           [&](const NodePtr& em) {
                               return match_method((NodeMethod*)method.get(),
                                                   (NodeMethod*)em.get());
                           });
    if (it == existing_methods.end()) {
        existing_methods.emplace_back(std::move(method));
    } else {
        *it = std::move(method);
    }
}

/// Extract all the public methods on a decl and return them for later use.
/// The resulting methods are NOT inserted in the AST or stored in the global
/// node tables.
std::vector<NodePtr> process_methods(const CXXRecordDecl* crd) {
    std::vector<NodePtr> result;
    SPDLOG_TRACE("process_methods({})", get_record_name(crd));

    // get all the public base classes of this record, and process those methods
    SPDLOG_TRACE("class has {} bases", crd->getNumBases());
    for (const auto base : crd->bases()) {
        if (const CXXRecordDecl* base_crd =
                base.getType()->getAsCXXRecordDecl()) {
            SPDLOG_TRACE("found base {}", get_record_name(crd));
            auto base_methods = process_methods(base_crd);
            for (auto&& m : base_methods) {
                result.emplace_back(std::move(m));
            }
        }
    }

    // FIXME: need to replace existing methods from the base class
    // for overrides
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
                    add_method_to_list(std::move(node_function), result);
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
                    add_method_to_list(std::move(node_function), result);
                }
            }
        } else if (const auto* cmd = dyn_cast<CXXMethodDecl>(d)) {
            // just a regular boring old method
            std::vector<std::string> attrs = get_attrs(d);
            auto node_function = process_method_decl(cmd, attrs);
            add_method_to_list(std::move(node_function), result);
        }
    }

    return result;
}

/// Check if the given method, `m`, has an equivalent method in
/// `binding_methods` If `m` does match, its attrs field is set to `attrs`
/// FIXME: modifying m here is a bit nasty
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

/// Get the full set of namespaces (including parent records) that lead to
/// a given decl. The decl passed here is expected to be the *parent* of the
/// decl we care about, as in `get_namespaces(target_decl->getParent())`
std::vector<NodeId> get_namespaces(const clang::DeclContext* parent,
                                   NodeTranslationUnit* node_tu) {
    std::vector<NodeId> result;

    while (parent) {
        if (parent->isNamespace()) {
            const clang::NamespaceDecl* ns =
                static_cast<const clang::NamespaceDecl*>(parent);

            auto qualified_name = ns->getQualifiedNameAsString();
            auto short_name = ns->getNameAsString();
            if (short_name == "cppmm_bind") {
                break;
            }

            // Add the id of this namespace to our list of namespaces, creating
            // a new NodeNamespace if it doesn't exist yet
            auto it = NODE_MAP.find(qualified_name);
            NodeId id;
            if (it == NODE_MAP.end()) {
                id = NODES.size();
                auto node = std::make_unique<NodeNamespace>(qualified_name, id,
                                                            0, short_name);
                NODES.emplace_back(std::move(node));
                NODE_MAP[qualified_name] = id;

            } else {
                id = it->second;
            }

            // add this node to the TU if it's not there already
            if (std::find(node_tu->children.begin(), node_tu->children.end(),
                          id) == node_tu->children.end()) {
                node_tu->children.push_back(id);
            }
            result.push_back(id);

            parent = parent->getParent();
        } else if (parent->isRecord()) {
            // Parent is a Record type. We should have created the record
            // already by the time we get here...
            const clang::CXXRecordDecl* crd =
                static_cast<const clang::CXXRecordDecl*>(parent);

            auto record_name = get_record_name(crd);
            auto it = NODE_MAP.find(record_name);
            if (it == NODE_MAP.end()) {
                SPDLOG_CRITICAL(
                    "Could not find record {} when processing namespaces",
                    record_name);
            } else {
                result.push_back(it->second);
            }

            parent = parent->getParent();
        } else {
            break;
        }
    }

    std::reverse(result.begin(), result.end());
    return result;
}

/// Create a NodeEnum for the given EnumDecl contained in the given file and
/// store it in the AST.
void process_enum_decl(const EnumDecl* ed, std::string filename) {
    ed = ed->getCanonicalDecl();
    assert(ed && "canonical decl is null");
    const std::string enum_name = ed->getQualifiedNameAsString();
    const std::string enum_short_name = ed->getNameAsString();

    if (NODE_MAP.find(enum_name) != NODE_MAP.end()) {
        // already done this one
        return;
    }

    // Get the translation unit node we're going to add this Enum to
    auto* node_tu = get_translation_unit(filename);
    const std::vector<NodeId> namespaces =
        get_namespaces(ed->getParent(), node_tu);
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

    std::vector<std::string> attrs = get_attrs(ed);

    NodeId new_id = NODES.size();
    auto node_enum = std::make_unique<NodeEnum>(
        enum_name, new_id, 0, std::move(attrs), std::move(enum_short_name),
        std::move(namespaces), variants, size, align);
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

void process_fields(const CXXRecordDecl* crd, NodeRecord* node_record_ptr) {
    // recurse through all bases and grab their fields
    for (const auto& base : crd->bases()) {
        if (const auto* base_crd = base.getType()->getAsCXXRecordDecl()) {
            process_fields(base_crd, node_record_ptr);
        }
    }

    // Now grab the fields for this decl
    for (const Decl* d : crd->decls()) {
        const auto record_name = get_record_name(crd);
        if (const auto* fd = dyn_cast<FieldDecl>(d)) {
            const std::string field_name = fd->getNameAsString();
            SPDLOG_TRACE("    FIELD {}::{}", record_name, field_name);
            QType qtype = process_qtype(fd->getType());
            node_record_ptr->fields.push_back(Field{field_name, qtype.ty});
        }
    }
}

/// Create a new NodeRecord for the given record decl and store it in the AST.
/// `crd` must represent a "concrete" record - i.e. it must not be dependent
/// on any template parameters. This is done in the binding file by explicitly
/// instantiating a template decl with the desired parameters.
void process_concrete_record(const CXXRecordDecl* crd, std::string filename,
                             std::vector<std::string> attrs,
                             std::vector<NodePtr> binding_methods,
                             std::vector<std::string> child_enums) {
    ASTContext& ctx = crd->getASTContext();
    SourceManager& sm = ctx.getSourceManager();
    const auto& loc = crd->getLocation();

    crd = crd->getCanonicalDecl()
              ->getDefinition(); // TODO: this seems to do what we want... but
                                 // does it? Can you imagine a world in which
                                 // Clang was actually documented?
    const std::string record_name = get_record_name(crd);
    const std::string short_name = crd->getNameAsString();

    SPDLOG_TRACE("Processing concrete record {}", record_name);
    //
    // Get the translation unit node we're going to add this Record to
    auto* node_tu = get_translation_unit(filename);
    std::vector<NodeId> namespaces = get_namespaces(crd->getParent(), node_tu);

    // Get the size and alignment of the Record
    uint32_t size, align;
    if (!get_abi_info(dyn_cast<TypeDecl>(crd), ctx, size, align)) {
        SPDLOG_CRITICAL("Could not get ABI info for {}", record_name);
    }

    // Add the new Record node
    NodeId new_id = NODES.size();
    auto node_record = std::make_unique<NodeRecord>(
        record_name, new_id, node_tu->id, std::move(attrs),
        std::move(short_name), std::move(namespaces), RecordKind::OpaquePtr,
        size, align);
    auto* node_record_ptr = node_record.get();
    NODES.emplace_back(std::move(node_record));
    NODE_MAP[record_name] = new_id;

    // add this record to the TU
    node_tu->children.push_back(new_id);

    // grab all the methods that are specified in the binding
    std::vector<NodePtr> methods = process_methods(crd);
    SPDLOG_TRACE("record {} has {} methods", record_name, methods.size());
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

    // process remaining children
    // first process (recursively) the fields from this decl and all bases
    process_fields(crd, node_record_ptr);

    // now get other child decls
    for (const Decl* d : crd->decls()) {
        if (const auto* md = dyn_cast<CXXMethodDecl>(d)) {
            // pass
        } else if (const auto* fd = dyn_cast<FunctionDecl>(d)) {
            SPDLOG_TRACE(" FUNCTION {}", fd->getQualifiedNameAsString());
        } else if (const auto* ed = dyn_cast<EnumDecl>(d)) {
            SPDLOG_TRACE("Got enum decl {}", ed->getNameAsString());
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

/// This function handles a CXXRecordDecl match. This will be called with the
/// Record from the binding file, so we need to do a bit of preprocessing to
/// make sure it's the right kind, then get the actual type we're interested in
/// from the library by inspecting the `using BoundType = XXX` decl on this
/// Record. We'll also need to get any attributes from here, as well as
/// pre-generating a list of matched methods
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
        // We can't process an incomplete type
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
        return;
    }

    // Don't *think* we should ever get here, but we'll leave this log in in
    // case we do because we'll want to figure out what case we didn't consider
    SPDLOG_CRITICAL("Fell through on handle_cxx_record");
    crd->dump();
}

void handle_typealias_decl(const TypeAliasDecl* tad, const CXXRecordDecl* crd) {
    auto record_qualified_name = get_record_name(crd);
    auto alias_name = tad->getNameAsString();
    if (alias_name == "BoundType") {
        // skip this because it's the type "pointer" we use on the class
        // TODO AL - there's got to be a cleaner way of not getting this
        // in the first place - on the matcher?
        return;
    }

    // First of all, make sure we have already processed the Record that this
    // alias refers to. I *think* this should always have happened, but not sure
    // yet
    auto it = NODE_MAP.find(record_qualified_name);
    if (it == NODE_MAP.end()) {
        SPDLOG_ERROR(
            "TypeAlias {0} renames {1} but {1} hasn't been processed yet",
            alias_name, record_qualified_name);
        return;
    }

    NodeId id_rec = it->second;
    NodeRecord* node_rec = (NodeRecord*)NODES[id_rec].get();
    node_rec->alias = alias_name;
}

std::unordered_map<std::string, std::vector<NodeFunction>> binding_functions;
std::unordered_map<std::string, NodeEnum> binding_enums;

/// This function is responsible for storing the description of the given
/// FunctionDecl so that we can match against it later. Only functions that
/// are explicitly declared in the bindings have AST output for them.
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

/// Store a description of the given EnumDecl so we can match it against a
/// corresponding decl in the library later to decide whether we want to
/// process said library decl
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
                              enum_short_name, {}, {}, 0, 0);
    binding_enums.insert(std::make_pair(enum_qual_name, std::move(node_enum)));
}

/// Decide if we want to store the given library FunctionDecl in the AST by
/// matching it against a decl from the bindings. If so, create the new
/// NodeFunction and store it in the AST
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

/// Decide if we want to store the given library EnumDecl in the AST by
/// matching it against a decl from the bindings. If so, create the new NodeEnum
/// and store it in the AST
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

/// Clang AST matcher that matches on the decls we're interested in in the
/// bindings and dispatches to our handling functions
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
            SPDLOG_INFO("GOT CXXRECORDTTYPE {} from TAD {}",
                        crd->getQualifiedNameAsString(),
                        tdecl->getNameAsString());
            handle_typealias_decl(tdecl, crd);
        }
    } else if (const FunctionDecl* function =
                   result.Nodes.getNodeAs<FunctionDecl>("functionDecl")) {
        handle_binding_function(function);
    } else if (const EnumDecl* enum_decl =
                   result.Nodes.getNodeAs<EnumDecl>("enumDecl")) {
        handle_binding_enum(enum_decl);
    }
}

/// Clang AST matcher that matches on the decls we're interested in in the
/// library and dispatches to our handling functions
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
                      unless(hasAncestor(recordDecl())), unless(isImplicit()))
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

/// Run the binding AST matcher, then run secondary matchers to find functions
/// and enums we're interested in from the bindings (stored in the first pass)
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
        DeclarationMatcher enum_decl_matcher =
            enumDecl(hasName(kv.second.short_name),
                     unless(hasAncestor(namespaceDecl(hasName("cppmm_bind")))),
                     unless(hasAncestor(recordDecl())))
                .bind("libraryEnumDecl");
        _library_finder.addMatcher(enum_decl_matcher, &_library_handler);
    }

    _library_finder.matchAST(context);
}

} // namespace cppmm
