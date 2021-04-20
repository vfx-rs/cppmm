#pragma once

#include <ostream>

#include <nlohmann/json.hpp>
using json = nlohmann::ordered_json;

namespace cppmm {
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
    Var,
    FunctionPointerTypedef,
};

std::ostream& operator<<(std::ostream& os, NodeKind k);

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

    virtual void write_json_attrs(json& o) const;
    virtual void write_json(json& o) const = 0;
};

using NodePtr = std::unique_ptr<Node>;

/// Represents one translation unit (TU), i.e. one binding source file.
/// NodeTranslationUnit::qualified_name contains the filename
struct NodeTranslationUnit : public Node {
    /// Other nodes bound in this TU
    std::vector<NodeId> children;
    /// Include statements from the binding file
    std::vector<std::string> source_includes;
    /// Include paths specified on the cppmm command line
    std::vector<std::string> project_includes;

    virtual void write_json(json& o) const override;

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
    std::string alias;
    bool collapse = false;

    NodeNamespace(std::string qualified_name, NodeId id, NodeId context,
                  std::string short_name, std::string alias)
        : Node(std::move(qualified_name), id, context, NodeKind::Namespace),
          short_name(std::move(short_name)), alias(std::move(alias)) {}

    virtual void write_json_attrs(json& o) const override;
    virtual void write_json(json& o) const override;
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

    virtual void write_json_attrs(json& o) const override;
};

/// A builtin, e.g. int, bool, char etc.
struct NodeBuiltinType : public NodeType {
    NodeBuiltinType(std::string qualified_name, NodeId id, NodeId context,
                    std::string type_name)
        : NodeType(qualified_name, id, context, NodeKind::BuiltinType,
                   type_name) {}

    virtual void write_json(json& o) const override;
};

/// QType is the equivalent of clang's QualType. Currently just defines the
/// constness of the wrapped type node. These are stored on the AST nodes
/// anywhere a type is needed.
struct QType {
    /// Type we're constifying
    NodeId ty;
    bool is_const;

    void write_json(json& o) const;

    bool operator==(const QType& rhs) const {
        return ty == rhs.ty && is_const == rhs.is_const;
    }

    bool operator!=(const QType& rhs) const { return !(*this == rhs); }
};

std::ostream& operator<<(std::ostream& os, const QType& q);

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

    virtual void write_json(json& o) const override;
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

    virtual void write_json(json& o) const override;
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

    virtual void write_json_attrs(json& o) const override;
    virtual void write_json(json& o) const override;
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

    virtual void write_json_attrs(json& o) const override;
    virtual void write_json(json& o) const override;
};

/// A function prototype (a pointer to which can be passed as callbacks etc).
/// This sits in an awkward spot because there isn't a corresponding decl so all
/// the structure is packed onto the type node here
struct NodeFunctionProtoType : public NodeType {
    /// Return type of the function
    QType return_type;
    /// Function parameters
    std::vector<QType> params;
    NodeId function_pointer_typedef;

    NodeFunctionProtoType(std::string qualified_name, NodeId id, NodeId context,
                          std::string type_name, QType return_type,
                          std::vector<QType> params,
                          NodeId function_pointer_typedef)
        : NodeType(qualified_name, id, context, NodeKind::FunctionProtoType,
                   type_name),
          return_type(std::move(return_type)), params(std::move(params)),
          function_pointer_typedef(function_pointer_typedef) {}

    virtual void write_json_attrs(json& o) const override;
    virtual void write_json(json& o) const override;
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

std::ostream& operator<<(std::ostream& os, const Param& p);

/// Base struct representing a node that has annotation attributes attached
struct NodeAttributeHolder : public Node {
    /// The annotation attributes
    std::vector<std::string> attrs;
    /// Doc comments, stored as base64
    std::string comment;

    NodeAttributeHolder(std::string qualified_name, NodeId id, NodeId context,
                        NodeKind node_kind, std::vector<std::string> attrs,
                        std::string comment)
        : Node(qualified_name, id, context, node_kind), attrs(attrs),
          comment(std::move(comment)) {}

    virtual void write_json(json& o) const override = 0;

    // FIXME: worst naming ever
    virtual void write_attrs_json(json& o) const;
};

struct NodeVar : public NodeAttributeHolder {
    std::string short_name;
    QType qtype;

    NodeVar(std::string qualified_name, NodeId id, NodeId context,
            std::vector<std::string> attrs, std::string short_name, QType qtype,
            std::string comment)
        : NodeAttributeHolder(std::move(qualified_name), id, context,
                              NodeKind::Var, std::move(attrs),
                              std::move(comment)),
          qtype(qtype), short_name(std::move(short_name)) {}

    virtual void write_json_attrs(json& o) const override;
    virtual void write_json(json& o) const override;
};

/// A function node
struct NodeFunction : public NodeAttributeHolder {
    /// What you think of as the function name without any qualifications
    std::string short_name;
    /// The function's return type
    QType return_type;
    /// The function's parameters
    std::vector<Param> params;
    /// The full path of namespaces leading to this function
    std::vector<NodeId> namespaces;
    /// Is this function declared in the binding?
    bool in_binding = false;
    /// Is this function declared in the library?
    bool in_library = false;
    /// Have we already processed this library function?
    bool processed = false;
    /// Is this function noexcept?
    bool is_noexcept = false;

    NodeFunction(std::string qualified_name, NodeId id, NodeId context,
                 std::vector<std::string> attrs, std::string short_name,
                 QType return_type, std::vector<Param> params,
                 std::vector<NodeId> namespaces, std::string comment)
        : NodeAttributeHolder(qualified_name, id, context, NodeKind::Function,
                              std::move(attrs), std::move(comment)),
          short_name(std::move(short_name)), return_type(return_type),
          params(std::move(params)), namespaces(std::move(namespaces)) {}

    virtual void write_json_attrs(json& o) const override;
    virtual void write_parameters_json(json& o) const;
    virtual void write_json(json& o) const override;
};

std::ostream& operator<<(std::ostream& os, const NodeFunction& f);

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
    /// Is this method the result of a FunctionTemplateDecl specialization
    /// We use this to differentiate `foo(int)` from `foo<T>(T)` with `T=int`.
    bool is_specialization = false;

    NodeMethod(std::string qualified_name, NodeId id, NodeId context,
               std::vector<std::string> attrs, std::string short_name,
               QType return_type, std::vector<Param> params, bool is_static,
               std::string comment)
        : NodeFunction(qualified_name, id, context, attrs, short_name,
                       return_type, params, {}, std::move(comment)),
          is_static(is_static) {
        node_kind = NodeKind::Method;
    }

    virtual void write_json_attrs(json& o) const override;
    virtual void write_json(json& o) const override;
};

std::ostream& operator<<(std::ostream& os, const NodeMethod& f);

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
    /// Does the class have any pure virtual functions?
    bool is_abstract;
    /// Is a bitwise copy safe?
    bool is_trivially_copyable;

    /// Size of the record, in bits
    uint32_t size;
    /// Alignment of the record, in bits
    uint32_t align;

    NodeRecord(std::string qualified_name, NodeId id, NodeId context,
               std::vector<std::string> attrs, std::string short_name,
               std::vector<NodeId> namespaces, RecordKind record_kind,
               bool is_abstract, bool is_trivially_copyable, uint32_t size,
               uint32_t align, std::string comment)
        : NodeAttributeHolder(qualified_name, id, context, NodeKind::Record,
                              std::move(attrs), std::move(comment)),
          short_name(std::move(short_name)), namespaces(std::move(namespaces)),
          record_kind(record_kind), is_abstract(is_abstract),
          is_trivially_copyable(is_trivially_copyable), size(size),
          align(align) {}

    virtual void write_json_attrs(json& o) const override;
    virtual void write_json(json& o) const override;
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
             uint32_t size, uint32_t align, std::string comment)
        : NodeAttributeHolder(qualified_name, id, context, NodeKind::Enum,
                              std::move(attrs), std::move(comment)),
          short_name(std::move(short_name)), namespaces(std::move(namespaces)),
          variants(variants), size(size), align(align) {}

    virtual void write_json_attrs(json& o) const override;
    virtual void write_json(json& o) const override;
};

/// An function pointer typedef declaration. Used to name function pointer
/// types so that they can be used as parameters
struct NodeFunctionPointerTypedef : public NodeAttributeHolder {
    /// Name of the typedef without any qualifiers
    std::string alias;
    /// Full namespace path
    std::vector<NodeId> namespaces;

    /// Return type of the function
    QType return_type;
    /// Function parameters
    std::vector<QType> params;

    NodeFunctionPointerTypedef(std::string qualified_name, NodeId id,
                               NodeId context, std::vector<std::string> attrs,
                               std::string alias,
                               std::vector<NodeId> namespaces,
                               std::string comment, QType return_type,
                               std::vector<QType> params)
        : NodeAttributeHolder(qualified_name, id, context, NodeKind::Enum,
                              std::move(attrs), std::move(comment)),
          alias(std::move(alias)), namespaces(std::move(namespaces)),
          return_type(return_type), params(std::move(params)) {}

    virtual void write_json_attrs(json& o) const override;
    virtual void write_json(json& o) const override;
};

/// Write out the AST to json output files. Each NodeTranslationUnit which
/// is a child of the ROOT is written to its own json file and all decls in
/// that TU are written recursively
void write_tus(std::string output_dir);

/// Find the node corresponding to the given TU filename, creating one if
/// none exists
NodeTranslationUnit* get_translation_unit(const std::string& filename);

/// Flat storage for nodes in the AST
extern std::vector<NodePtr> NODES;
/// Map for name-lookup of nodes (keys should match Node::qualified_name)
extern std::unordered_map<std::string, NodeId> NODE_MAP;
/// Root of the AST - will contain NodeTranslationUnits, which will themselves
/// contain the rest of the tree
extern std::vector<NodeId> ROOT;
/// Namespace aliases
extern std::unordered_map<std::string, std::pair<std::string, bool>>
    NAMESPACE_ALIASES;
/// Function prototype typedefs
extern std::unordered_map<std::string, std::string> FPT_TYPEDEFS;

extern std::unordered_map<std::string, std::vector<std::string>>
    SOURCE_INCLUDES;
extern std::vector<std::string> PROJECT_INCLUDES;
} // namespace cppmm
