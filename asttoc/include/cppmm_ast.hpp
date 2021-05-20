//------------------------------------------------------------------------------
// vfx-rs
//------------------------------------------------------------------------------
#pragma once
#include <cstdint>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

namespace cppmm {

struct Type;

using Id = uint64_t;

//------------------------------------------------------------------------------
// NodeKind
//------------------------------------------------------------------------------
enum class NodeKind : uint32_t {
    Node = 0,
    TranslationUnit,
    Namespace,
    ArrayType,
    BuiltinType,
    PointerType,
    RecordType,
    EnumType,
    FunctionProtoType,
    TypedefType,
    UnknownType,
    Parm,
    Function,
    AssignExpr,
    BlockExpr,
    FunctionCallExpr,
    MethodCallExpr,
    VarRefExpr,
    VarDeclExpr,
    DerefExpr,
    RefExpr,
    CastExpr,
    PlacementNewExpr,
    NewExpr,
    DeleteExpr,
    ReturnExpr,
    Enum,
    Method,
    Record,
    Typedef,
    FunctionPointerTypedef,
    InfixOperatorExpr,
    Sentinal, // A sentinal entry to keep track of how many there are
};

//------------------------------------------------------------------------------
// PointerKind
//------------------------------------------------------------------------------
enum class PointerKind : uint32_t {
    Pointer,
    Reference,
    RValueReference,
};

using NodeId = uint64_t;

//------------------------------------------------------------------------------
// Node
//------------------------------------------------------------------------------
struct Node {
    std::string name;
    NodeId id;
    NodeKind kind;
    bool private_;

    Node(std::string name, NodeId id, NodeKind kind)
        : name(name), id(id), kind(kind), private_(false) {}

    virtual ~Node() {}
};
// Shared so the node can be stored in a tree and also in mapping.
using NodePtr = std::shared_ptr<Node>;

//------------------------------------------------------------------------------
// TranslationUnit
//------------------------------------------------------------------------------
struct TranslationUnit {
    std::string filename;
    std::vector<NodePtr> decls;
    std::set<NodePtr> forward_decls;

    std::string header_filename;
    std::string private_header_filename;
    std::set<std::string> source_includes;
    std::set<std::string> private_includes;
    std::set<std::string> header_includes;

    std::vector<std::string> include_paths;

    using Self = TranslationUnit;
    using Ptr = std::shared_ptr<Self>;
    using WPtr = std::weak_ptr<Self>;

    TranslationUnit(std::string filename) : filename(filename) {}

    TranslationUnit(Self&& rhs)
        : filename(std::move(rhs.filename)), decls(std::move(rhs.decls)),
          header_filename(std::move(rhs.header_filename)),
          private_header_filename(std::move(rhs.private_header_filename)),
          source_includes(std::move(rhs.source_includes)) {}

    void operator==(Self&& rhs) {
        filename = std::move(rhs.filename);
        decls = std::move(rhs.decls);
        header_filename = std::move(rhs.header_filename);
        private_header_filename = std::move(rhs.private_header_filename);
        source_includes = std::move(rhs.source_includes);
    }

    static Ptr new_(std::string filename) {
        return std::make_shared<Self>(filename);
    }
};

//------------------------------------------------------------------------------
// NodeNamespace
//------------------------------------------------------------------------------
struct NodeNamespace : public Node {
    std::string short_name;
    std::string alias;
    bool collapse;

    NodeNamespace(std::string name, NodeId id, std::string short_name,
                  std::string alias, bool collapse)
        : Node(name, id, NodeKind::Namespace), short_name(short_name),
          alias(alias), collapse(collapse) {}

    // A static method for creating this as a shared pointer
    using This = NodeNamespace;
    template <typename... Args> static std::shared_ptr<This> n(Args&&... args) {
        return std::make_shared<This>(std::forward<Args>(args)...);
    }
};

//------------------------------------------------------------------------------
// NodeType
//------------------------------------------------------------------------------
struct NodeType : public Node {
    bool const_;
    std::string type_name;

    NodeType(std::string qualified_name, NodeId id, NodeKind node_kind,
             std::string type_name, bool const_)
        : Node(qualified_name, id, node_kind), const_(const_),
          type_name(type_name) {}
};
using NodeTypePtr = std::shared_ptr<NodeType>;

//------------------------------------------------------------------------------
// NodeBuiltinType
//------------------------------------------------------------------------------
struct NodeBuiltinType : public NodeType {

    NodeBuiltinType(std::string qualified_name, NodeId id,
                    std::string type_name, bool const_)
        : NodeType(qualified_name, id, NodeKind::BuiltinType, type_name,
                   const_) {}

    // A static method for creating this as a shared pointer
    using This = NodeBuiltinType;
    template <typename... Args> static std::shared_ptr<This> n(Args&&... args) {
        return std::make_shared<This>(std::forward<Args>(args)...);
    }
};

//------------------------------------------------------------------------------
// NodePointerType
//------------------------------------------------------------------------------
/// pointer or reference type - check type_kind
struct NodePointerType : public NodeType {
    NodeTypePtr pointee_type;
    PointerKind pointer_kind;
    NodePointerType(PointerKind pointer_kind, NodeTypePtr&& pointee_type,
                    bool const_)
        : NodeType("", 0, NodeKind::PointerType, "", const_),
          pointer_kind(pointer_kind), pointee_type(std::move(pointee_type)) {}

    // A static method for creating this as a shared pointer
    using This = NodePointerType;
    template <typename... Args> static std::shared_ptr<This> n(Args&&... args) {
        return std::make_shared<This>(std::forward<Args>(args)...);
    }
};

//------------------------------------------------------------------------------
// NodeFunctionProtoType
//------------------------------------------------------------------------------
struct NodeFunctionProtoType : public NodeType {
    NodeTypePtr return_type;
    std::vector<NodeTypePtr> params;
    std::string type;
    NodeId function_pointer_typedef;

    NodeFunctionProtoType(const NodeTypePtr& return_type,
                          std::vector<NodeTypePtr>&& params,
                          const std::string& type,
                          NodeId function_pointer_typedef)
        : NodeType("", 0, NodeKind::FunctionProtoType, "", false),
          return_type(return_type), params(std::move(params)), type(type),
          function_pointer_typedef(function_pointer_typedef) {}

    // A static method for creating this as a shared pointer
    using This = NodeFunctionProtoType;
    template <typename... Args> static std::shared_ptr<This> n(Args&&... args) {
        return std::make_shared<This>(std::forward<Args>(args)...);
    }
};

//------------------------------------------------------------------------------
// NodeRecordType
//------------------------------------------------------------------------------
struct NodeRecordType : public NodeType {
    NodeId record;
    NodeRecordType(std::string qualified_name, NodeId id, std::string type_name,
                   NodeId record, bool const_)
        : NodeType(qualified_name, id, NodeKind::RecordType, type_name, const_),
          record(record) {}

    // A static method for creating this as a shared pointer
    using This = NodeRecordType;
    template <typename... Args> static std::shared_ptr<This> n(Args&&... args) {
        return std::make_shared<This>(std::forward<Args>(args)...);
    }
};

//------------------------------------------------------------------------------
// NodeEnumType
//------------------------------------------------------------------------------
struct NodeEnumType : public NodeType {
    NodeId enm;
    NodeEnumType(std::string qualified_name, NodeId id, std::string type_name,
                 NodeId enm, bool const_) // TODO LT: Hook up const later
        : NodeType(qualified_name, id, NodeKind::EnumType, type_name, const_),
          enm(enm) {}

    // A static method for creating this as a shared pointer
    using This = NodeEnumType;
    template <typename... Args> static std::shared_ptr<This> n(Args&&... args) {
        return std::make_shared<This>(std::forward<Args>(args)...);
    }
};

//------------------------------------------------------------------------------
// NodeTypedefType
//------------------------------------------------------------------------------
struct NodeTypedefType : public NodeType {
    NodeId typedef_;
    NodeTypedefType(std::string qualified_name, NodeId id,
                    std::string type_name, NodeId typedef_,
                    bool const_) // TODO LT: Hook up const later
        : NodeType(qualified_name, id, NodeKind::TypedefType, type_name,
                   const_),
          typedef_(typedef_) {}

    // A static method for creating this as a shared pointer
    using This = NodeTypedefType;
    template <typename... Args> static std::shared_ptr<This> n(Args&&... args) {
        return std::make_shared<This>(std::forward<Args>(args)...);
    }
};

//------------------------------------------------------------------------------
// NodeArrayType
//------------------------------------------------------------------------------
struct NodeArrayType : public NodeType { // TODO LT: Rename to ConstantArray
    uint64_t size;
    NodeTypePtr element_type;

    NodeArrayType(std::string qualified_name, NodeId id, std::string type_name,
                  NodeTypePtr&& element_type, uint64_t size, bool const_)
        : NodeType(qualified_name, id, NodeKind::ArrayType, type_name, const_),
          size(size), element_type(std::move(element_type)) {}

    // A static method for creating this as a shared pointer
    using This = NodeArrayType;
    template <typename... Args> static std::shared_ptr<This> n(Args&&... args) {
        return std::make_shared<This>(std::forward<Args>(args)...);
    }
};

//------------------------------------------------------------------------------
// NodeUnknownType
//------------------------------------------------------------------------------
struct NodeUnknownType : public NodeType { // TODO LT: Rename to ConstantArray
    NodeUnknownType(bool const_)
        : NodeType("", 0, NodeKind::UnknownType, "", const_) {}

    // A static method for creating this as a shared pointer
    using This = NodeUnknownType;
    template <typename... Args> static std::shared_ptr<This> n(Args&&... args) {
        return std::make_shared<This>(std::forward<Args>(args)...);
    }
};

//------------------------------------------------------------------------------
// Param
//------------------------------------------------------------------------------
struct Param {
    std::string name;
    NodeTypePtr type;
    int index;

    Param(std::string&& name, NodeTypePtr&& type, int index)
        : name(name), type(std::move(type)), index(index) {}

    Param(Param&& rhs)
        : name(std::move(rhs.name)), type(std::move(rhs.type)),
          index(rhs.index) {}

    Param(const Param& rhs)
        : name(rhs.name), type(rhs.type), index(rhs.index) {}
};

//------------------------------------------------------------------------------
// NodeAttributeHolder
//------------------------------------------------------------------------------
struct NodeAttributeHolder : public Node {
    std::vector<std::string> attrs;
    /// doc comment, decoded
    std::string comment;

    NodeAttributeHolder(std::string name, NodeId id, NodeKind node_kind,
                        std::vector<std::string> attrs, std::string comment)
        : Node(name, id, node_kind), attrs(attrs), comment(std::move(comment)) {
    }
};

//------------------------------------------------------------------------------
// NodeExpr
//------------------------------------------------------------------------------
struct NodeExpr : public Node { // TODO LT: Added by luke

    NodeExpr(NodeKind kind, std::string name = "") : Node(name, 0, kind) {}
};
using NodeExprPtr = std::shared_ptr<NodeExpr>;

//------------------------------------------------------------------------------
// NodeFunctionCallExpr
//------------------------------------------------------------------------------
struct NodeFunctionCallExpr
    : public NodeExpr { // TODO LT: Added by luke, like CallExpr
    std::vector<NodeExprPtr> args;
    std::vector<NodeTypePtr> template_args;

    NodeFunctionCallExpr(std::string name, std::vector<NodeExprPtr> args,
                         std::vector<NodeTypePtr> template_args,
                         NodeKind kind = NodeKind::FunctionCallExpr)
        : NodeExpr(kind, name), args(args), template_args(template_args) {}

    // A static method for creating this as a shared pointer
    using This = NodeFunctionCallExpr;
    template <typename... Args> static std::shared_ptr<This> n(Args&&... args) {
        return std::make_shared<This>(std::forward<Args>(args)...);
    }
};

//------------------------------------------------------------------------------
// NodeInfixOperatorExpr
//------------------------------------------------------------------------------
struct NodeInfixOperatorExpr : public NodeExpr { // TODO LT: Added by Anders.
                                                 // specialization for e.g. '=='
    std::vector<NodeExprPtr> args;
    std::vector<NodeTypePtr> template_args;

    NodeInfixOperatorExpr(std::string name, std::vector<NodeExprPtr> args,
                          std::vector<NodeTypePtr> template_args,
                          NodeKind kind = NodeKind::InfixOperatorExpr)
        : NodeExpr(kind, name), args(args), template_args(template_args) {}

    // A static method for creating this as a shared pointer
    using This = NodeInfixOperatorExpr;
    template <typename... Args> static std::shared_ptr<This> n(Args&&... args) {
        return std::make_shared<This>(std::forward<Args>(args)...);
    }
};

//------------------------------------------------------------------------------
// NodeMethodCallExpr
//------------------------------------------------------------------------------
struct NodeMethodCallExpr
    : public NodeFunctionCallExpr { // TODO LT: Added by luke, like clang
                                    // MemberCallExpr
    NodeExprPtr this_;

    NodeMethodCallExpr(NodeExprPtr&& this_, std::string name,
                       std::vector<NodeExprPtr> args,
                       std::vector<NodeTypePtr> template_args)
        : NodeFunctionCallExpr(name, args, template_args,
                               NodeKind::MethodCallExpr),
          this_(std::move(this_)) {}

    // A static method for creating this as a shared pointer
    using This = NodeMethodCallExpr;
    template <typename... Args> static std::shared_ptr<This> n(Args&&... args) {
        return std::make_shared<This>(std::forward<Args>(args)...);
    }
};

//------------------------------------------------------------------------------
// NodeVarRefExpr
//------------------------------------------------------------------------------
struct NodeVarRefExpr
    : public NodeExpr { // TODO LT: Added by luke, like clang DeclRef
    std::string var_name;

    NodeVarRefExpr(std::string var_name)
        : NodeExpr(NodeKind::VarRefExpr), var_name(var_name) {}

    // A static method for creating this as a shared pointer
    using This = NodeVarRefExpr;
    template <typename... Args> static std::shared_ptr<This> n(Args&&... args) {
        return std::make_shared<This>(std::forward<Args>(args)...);
    }
};

//------------------------------------------------------------------------------
// NodeVarDeclExpr
//------------------------------------------------------------------------------
struct NodeVarDeclExpr : public NodeExpr { // TODO LT: Added by luke
    NodeTypePtr var_type;
    std::string var_name;

    NodeVarDeclExpr(NodeTypePtr var_type, std::string var_name)
        : NodeExpr(NodeKind::VarDeclExpr), var_type(var_type),
          var_name(var_name) {}

    // A static method for creating this as a shared pointer
    using This = NodeVarDeclExpr;
    template <typename... Args> static std::shared_ptr<This> n(Args&&... args) {
        return std::make_shared<This>(std::forward<Args>(args)...);
    }
};

//------------------------------------------------------------------------------
// NodeAssignExpr
//------------------------------------------------------------------------------
struct NodeAssignExpr : public NodeExpr { // TODO LT: Added by luke
    NodeExprPtr lhs;
    NodeExprPtr rhs;

    NodeAssignExpr(NodeExprPtr lhs, NodeExprPtr rhs)
        : NodeExpr(NodeKind::AssignExpr), lhs(lhs), rhs(rhs) {}

    // A static method for creating this as a shared pointer
    using This = NodeAssignExpr;
    template <typename... Args> static std::shared_ptr<This> n(Args&&... args) {
        return std::make_shared<This>(std::forward<Args>(args)...);
    }
};

//------------------------------------------------------------------------------
// NodeRefExpr
//------------------------------------------------------------------------------
struct NodeRefExpr : public NodeExpr { // TODO LT: Added by luke = &()
    NodeExprPtr inner;

    NodeRefExpr(NodeExprPtr&& inner)
        : NodeExpr(NodeKind::RefExpr), inner(std::move(inner)) {}

    // A static method for creating this as a shared pointer
    using This = NodeRefExpr;
    template <typename... Args> static std::shared_ptr<This> n(Args&&... args) {
        return std::make_shared<This>(std::forward<Args>(args)...);
    }
};

//------------------------------------------------------------------------------
// NodeDerefExpr
//------------------------------------------------------------------------------
struct NodeDerefExpr : public NodeExpr { // TODO LT: Added by luke = *()
    NodeExprPtr inner;

    NodeDerefExpr(NodeExprPtr&& inner)
        : NodeExpr(NodeKind::DerefExpr), inner(std::move(inner)) {}

    // A static method for creating this as a shared pointer
    using This = NodeDerefExpr;
    template <typename... Args> static std::shared_ptr<This> n(Args&&... args) {
        return std::make_shared<This>(std::forward<Args>(args)...);
    }
};

//------------------------------------------------------------------------------
// NodeReturnExpr
//------------------------------------------------------------------------------
struct NodeReturnExpr : public NodeExpr { // TODO LT: Added by luke = *()
    NodeExprPtr inner;

    NodeReturnExpr(NodeExprPtr&& inner)
        : NodeExpr(NodeKind::ReturnExpr), inner(std::move(inner)) {}

    // A static method for creating this as a shared pointer
    using This = NodeReturnExpr;
    template <typename... Args> static std::shared_ptr<This> n(Args&&... args) {
        return std::make_shared<This>(std::forward<Args>(args)...);
    }
};

//------------------------------------------------------------------------------
// NodeCastExpr
//------------------------------------------------------------------------------
struct NodeCastExpr : public NodeExpr { // TODO LT: Added by luke
    NodeExprPtr inner;
    NodeTypePtr type;
    std::string cast_kind;

    NodeCastExpr(NodeExprPtr&& inner, NodeTypePtr&& type, std::string cast_kind)
        : NodeExpr(NodeKind::CastExpr), inner(std::move(inner)),
          type(std::move(type)), cast_kind(cast_kind) {}

    // A static method for creating this as a shared pointer
    using This = NodeCastExpr;
    template <typename... Args> static std::shared_ptr<This> n(Args&&... args) {
        return std::make_shared<This>(std::forward<Args>(args)...);
    }
};

//------------------------------------------------------------------------------
// NodeBlockExpr
//------------------------------------------------------------------------------
struct NodeBlockExpr : public NodeExpr { // TODO LT: Added by luke new () ();
    std::vector<NodeExprPtr> expressions;

    NodeBlockExpr(std::vector<NodeExprPtr>&& expressions)
        : NodeExpr(NodeKind::BlockExpr), expressions(expressions) {}

    // A static method for creating this as a shared pointer
    using This = NodeBlockExpr;
    template <typename... Args> static std::shared_ptr<This> n(Args&&... args) {
        return std::make_shared<This>(std::forward<Args>(args)...);
    }
};

//------------------------------------------------------------------------------
// NodePlacementNewExpr
//------------------------------------------------------------------------------
struct NodePlacementNewExpr
    : public NodeExpr { // TODO LT: Added by luke new () ();
    NodeExprPtr address;
    NodeExprPtr constructor;

    NodePlacementNewExpr(NodeExprPtr&& address, NodeExprPtr&& constructor)
        : NodeExpr(NodeKind::PlacementNewExpr), address(std::move(address)),
          constructor(std::move(constructor)) {}

    // A static method for creating this as a shared pointer
    using This = NodePlacementNewExpr;
    template <typename... Args> static std::shared_ptr<This> n(Args&&... args) {
        return std::make_shared<This>(std::forward<Args>(args)...);
    }
};

//------------------------------------------------------------------------------
// NodeNewExpr
//------------------------------------------------------------------------------
struct NodeNewExpr : public NodeExpr {
    NodeExprPtr constructor;

    NodeNewExpr(NodeExprPtr&& constructor)
        : NodeExpr(NodeKind::NewExpr), constructor(std::move(constructor)) {}

    // A static method for creating this as a shared pointer
    using This = NodeNewExpr;
    template <typename... Args> static std::shared_ptr<This> n(Args&&... args) {
        return std::make_shared<This>(std::forward<Args>(args)...);
    }
};

//------------------------------------------------------------------------------
// NodeDeleteExpr
//------------------------------------------------------------------------------
struct NodeDeleteExpr : public NodeExpr {
    NodeExprPtr pointer;

    NodeDeleteExpr(NodeExprPtr&& pointer)
        : NodeExpr(NodeKind::DeleteExpr), pointer(pointer) {}

    // A static method for creating this as a shared pointer
    using This = NodeDeleteExpr;
    template <typename... Args> static std::shared_ptr<This> n(Args&&... args) {
        return std::make_shared<This>(std::forward<Args>(args)...);
    }
};

//------------------------------------------------------------------------------
// Exception
//------------------------------------------------------------------------------
struct Exception {
    std::string cpp_name;
    std::string c_name;
    unsigned int error_code;
};

extern std::map<unsigned int, std::string> EXCEPTION_MAP;

//------------------------------------------------------------------------------
// NodeFunction
//------------------------------------------------------------------------------
struct NodeFunction : public NodeAttributeHolder {
    std::string short_name;
    std::string nice_name;
    NodeTypePtr return_type;
    std::vector<Param> params;
    bool in_binding = false;
    bool in_library = false;
    bool inline_ = false;

    NodeExprPtr body;
    std::vector<NodeId> namespaces;
    std::vector<NodeTypePtr> template_args;
    std::vector<Exception> exceptions;
    bool is_noexcept = false;

    NodeFunction(std::string qualified_name, NodeId id,
                 std::vector<std::string> attrs, std::string short_name,
                 NodeTypePtr&& return_type, std::vector<Param>&& params,
                 std::string nice_name, std::string comment,
                 std::vector<NodeTypePtr>&& template_args,
                 std::vector<Exception> exceptions, bool is_noexcept)
        : NodeAttributeHolder(qualified_name, id, NodeKind::Function, attrs,
                              std::move(comment)),
          short_name(short_name), return_type(std::move(return_type)),
          params(std::move(params)), nice_name(std::move(nice_name)),
          template_args(std::move(template_args)),
          exceptions(std::move(exceptions)), is_noexcept(is_noexcept) {}

    // A static method for creating this as a shared pointer
    using This = NodeFunction;
    template <typename... Args> static std::shared_ptr<This> n(Args&&... args) {
        return std::make_shared<This>(std::forward<Args>(args)...);
    }
};

//------------------------------------------------------------------------------
// NodeMethod
//------------------------------------------------------------------------------
struct NodeMethod : public NodeFunction {
    bool is_static;
    bool is_destructor;
    bool is_constructor;
    bool is_copy_constructor;
    bool is_move_constructor;
    bool is_const;

    NodeMethod(std::string qualified_name, NodeId id,
               std::vector<std::string> attrs, std::string short_name,
               NodeTypePtr&& return_type, std::vector<Param>&& params,
               bool is_static, bool is_constructor, bool is_copy_constructor,
               bool is_move_constructor,
               bool is_destructor, bool is_const, std::string comment,
               std::vector<NodeTypePtr>&& template_args,
               std::vector<Exception> exceptions, bool is_noexcept)
        : NodeFunction(
              qualified_name, id, attrs, short_name, std::move(return_type),
              std::move(params), qualified_name, std::move(comment),
              std::move(template_args), std::move(exceptions), is_noexcept),
          is_static(is_static), is_constructor(is_constructor),
          is_copy_constructor(is_copy_constructor),
          is_move_constructor(is_move_constructor),
          is_destructor(is_destructor), is_const(is_const) {
        kind = NodeKind::Method;
    }

    // A static method for creating this as a shared pointer
    using This = NodeMethod;
    template <typename... Args> static std::shared_ptr<This> n(Args&&... args) {
        return std::make_shared<This>(std::forward<Args>(args)...);
    }
};

//------------------------------------------------------------------------------
// Field
//------------------------------------------------------------------------------
struct Field {
    std::string name;
    NodeTypePtr type;
};

//------------------------------------------------------------------------------
// NodeRecord
//------------------------------------------------------------------------------
struct NodeRecord : public NodeAttributeHolder {
    std::vector<Field> fields;
    std::vector<NodeMethod> methods;
    TranslationUnit::WPtr tu;

    uint32_t size;
    uint32_t align;
    bool force_alignment;

    std::string alias;
    std::vector<NodeId> namespaces;

    bool abstract;
    bool trivially_copyable;
    bool trivially_movable;
    bool opaque_type;

    std::string nice_name;

    NodeRecord(const TranslationUnit::Ptr& tu, std::string qualified_name,
               NodeId id, std::vector<std::string> attrs, uint32_t size,
               uint32_t align, const std::string& alias,
               const std::vector<NodeId>& namespaces, bool abstract,
               bool trivially_copyable, bool trivially_movable,
               bool opaque_type, std::string comment)
        : NodeAttributeHolder(qualified_name, id, NodeKind::Record, attrs,
                              std::move(comment)),
          tu(tu), size(size), align(align), force_alignment(false),
          alias(alias), namespaces(namespaces), abstract(abstract),
          trivially_copyable(trivially_copyable),
          trivially_movable(trivially_movable), opaque_type(opaque_type) {}

    // A static method for creating this as a shared pointer
    using This = NodeRecord;
    template <typename... Args> static std::shared_ptr<This> n(Args&&... args) {
        return std::make_shared<This>(std::forward<Args>(args)...);
    }
};

//------------------------------------------------------------------------------
// NodeEnum
//------------------------------------------------------------------------------
struct NodeEnum : public NodeAttributeHolder {
    std::vector<std::pair<std::string, std::string>> variants;
    std::vector<std::pair<std::string, std::string>> cpp_variants;
    uint32_t size;
    uint32_t align;
    TranslationUnit::WPtr tu;
    std::string nice_name;
    std::string short_name;

    std::vector<NodeId> namespaces;

    NodeEnum(const TranslationUnit::Ptr& tu, std::string qualified_name,
             std::string nice_name, std::string short_name, NodeId id,
             std::vector<std::string> attrs,
             std::vector<std::pair<std::string, std::string>> variants,
             uint32_t size, uint32_t align,
             const std::vector<NodeId>& namespaces, std::string comment)
        : NodeAttributeHolder(qualified_name, id, NodeKind::Enum, attrs,
                              std::move(comment)),
          tu(tu), variants(variants), size(size), align(align),
          namespaces(namespaces), nice_name(nice_name), short_name(short_name) {
    }

    using This = NodeEnum;
    template <typename... Args> static std::shared_ptr<This> n(Args&&... args) {
        return std::make_shared<This>(std::forward<Args>(args)...);
    }
};

//------------------------------------------------------------------------------
// NodeTypedef
//------------------------------------------------------------------------------
struct NodeTypedef : public NodeAttributeHolder {
    NodeTypePtr type;
    TranslationUnit::WPtr tu;

    NodeTypedef(const TranslationUnit::Ptr& tu, std::string qualified_name,
                const NodeTypePtr& type, std::string comment)
        : NodeAttributeHolder(qualified_name, 0, NodeKind::Typedef,
                              std::vector<std::string>(), std::move(comment)),
          tu(tu), type(type) {}

    using This = NodeTypedef;
    template <typename... Args> static std::shared_ptr<This> n(Args&&... args) {
        return std::make_shared<This>(std::forward<Args>(args)...);
    }
};

//------------------------------------------------------------------------------
// NodeFunctionPointerTypedef
//------------------------------------------------------------------------------
struct NodeFunctionPointerTypedef : public NodeAttributeHolder {
    NodeTypePtr type;
    TranslationUnit::WPtr tu;
    std::string alias;
    std::vector<NodeId> namespaces;
    std::string nice_name;
    NodeTypePtr return_type;
    std::vector<Param> params;

    NodeFunctionPointerTypedef(const TranslationUnit::Ptr& tu,
                               std::string qualified_name, NodeId id,
                               std::string alias,
                               std::vector<NodeId> namespaces,
                               std::string comment, NodeTypePtr&& return_type,
                               std::vector<Param>&& params)
        : NodeAttributeHolder(qualified_name, id,
                              NodeKind::FunctionPointerTypedef,
                              std::vector<std::string>(), std::move(comment)),
          tu(tu), alias(alias), namespaces(namespaces),
          return_type(std::move(return_type)), params(std::move(params)) {}

    using This = NodeFunctionPointerTypedef;
    template <typename... Args> static std::shared_ptr<This> n(Args&&... args) {
        return std::make_shared<This>(std::forward<Args>(args)...);
    }
};

//------------------------------------------------------------------------------
// Root
//------------------------------------------------------------------------------
struct Root {
    std::vector<TranslationUnit::Ptr> tus;

    Root(std::vector<TranslationUnit::Ptr>&& tus) : tus(std::move(tus)) {}

    Root(Root&& rhs) : tus(std::move(rhs.tus)) {}

    void operator==(Root&& rhs) { tus = std::move(rhs.tus); }
};

//------------------------------------------------------------------------------
// BindType
//------------------------------------------------------------------------------
enum class BindType : uint32_t {
    OpaquePtr = 0,
    OpaqueBytes = 1,
    ValueType = 2,
};

//------------------------------------------------------------------------------
inline BindType bind_type(const NodeRecord& cpp_record) {
    BindType bind_type = BindType::OpaquePtr;

    if (!cpp_record.opaque_type) {
        for (auto i : cpp_record.attrs) {
            if (i == "cppmm|opaquebytes") {
                return BindType::OpaqueBytes;
            } else if (i == "cppmm|valuetype") {
                return BindType::ValueType;
            }
        }
    }

    return bind_type;
}

} // namespace cppmm
