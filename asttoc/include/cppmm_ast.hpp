//------------------------------------------------------------------------------
// vfx-rs
//------------------------------------------------------------------------------
#pragma once
#include <cstdint>
#include <memory>
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
    BuiltinType,
    PointerType,
    RecordType,
    Parm,
    Function,
    Method,
    Record,
    Sentinal, // A sentinal entry to keep track of how many there are
};

//------------------------------------------------------------------------------
// PointerKind
//------------------------------------------------------------------------------
enum class PointerKind : uint32_t {
    Pointer,
    Reference,
};

//------------------------------------------------------------------------------
// RecordKind
//------------------------------------------------------------------------------
enum class RecordKind : uint32_t { OpaquePtr = 0, OpaqueBytes, ValueType };

using NodeId = uint64_t;

//------------------------------------------------------------------------------
// Node
//------------------------------------------------------------------------------
struct Node {
    std::string name;
    NodeId id;
    NodeKind kind;

    Node(std::string name, NodeId id, NodeKind kind)
        : name(name)
        , id(id)
        , kind(kind) {}

    virtual ~Node(){}
};
using NodePtr = std::unique_ptr<Node>;

//------------------------------------------------------------------------------
// TranslationUnit
//------------------------------------------------------------------------------
struct TranslationUnit {
    Id id;
    std::string filename;
    std::vector<NodePtr> decls;

    using Self = TranslationUnit;

    TranslationUnit(std::string filename, NodeId id)
        : id(id)
        , filename(filename)
    {}

    TranslationUnit(Self && rhs)
        : id(rhs.id)
        , filename(std::move(rhs.filename))
        , decls(std::move(rhs.decls))
    {}

    void operator==(Self && rhs) {
        id = rhs.id;
        filename = std::move(rhs.filename);
        decls = std::move(rhs.decls);
    }
};

//------------------------------------------------------------------------------
// NodeNamespace
//------------------------------------------------------------------------------
struct NodeNamespace : public Node {};

//------------------------------------------------------------------------------
// NodeType
//------------------------------------------------------------------------------
struct NodeType : public Node {
    std::string type_name;
    bool const_;

    NodeType(std::string qualified_name, NodeId id, NodeId context,
             NodeKind node_kind, std::string type_name)
        : Node(qualified_name, id, node_kind), type_name(type_name) {}
};
using NodeTypePtr = std::unique_ptr<NodeType>;

//------------------------------------------------------------------------------
// NodeBuiltinType
//------------------------------------------------------------------------------
struct NodeBuiltinType : public NodeType {
    NodeBuiltinType(std::string qualified_name, NodeId id, NodeId context,
                    std::string type_name)
        : NodeType(qualified_name, id, context, NodeKind::BuiltinType,
                   type_name) {}
};

//------------------------------------------------------------------------------
// NodePointerType
//------------------------------------------------------------------------------
/// pointer or reference type - check type_kind
struct NodePointerType : public NodeType {
    NodeTypePtr pointee_type;
    PointerKind pointer_kind;
    NodePointerType(std::string qualified_name, NodeId id, NodeId context,
                    std::string type_name, PointerKind pointer_kind,
                    NodeTypePtr && pointee_type)
        : NodeType(qualified_name, id, context, NodeKind::PointerType,
                   type_name),
          pointer_kind(pointer_kind), pointee_type(std::move(pointee_type)) {}
};

//------------------------------------------------------------------------------
// NodeRecordType
//------------------------------------------------------------------------------
struct NodeRecordType : public NodeType {
    NodeId record;
    NodeRecordType(std::string qualified_name, NodeId id, NodeId context,
                   std::string type_name, NodeId record)
        : NodeType(qualified_name, id, context, NodeKind::RecordType,
                   type_name),
          record(record) {}
};

//------------------------------------------------------------------------------
// Param
//------------------------------------------------------------------------------
struct Param {
    std::string name;
    NodeTypePtr type;
    int index;

    Param(std::string && name, NodeTypePtr && type, int index)
        : name(name)
        , type(std::move(type))
        , index(index)
    {}

    Param(Param && rhs)
        : name(rhs.name)
        , type(std::move(rhs.type))
        , index(rhs.index)
    {}
};

//------------------------------------------------------------------------------
// NodeAttributeHolder
//------------------------------------------------------------------------------
struct NodeAttributeHolder : public Node {
    std::vector<std::string> attrs;

    NodeAttributeHolder(std::string name, NodeId id,
                        NodeKind node_kind, std::vector<std::string> attrs)
        : Node(name, id, node_kind), attrs(attrs) {}
};

//------------------------------------------------------------------------------
// NodeFunction
//------------------------------------------------------------------------------
struct NodeFunction : public NodeAttributeHolder {
    std::string short_name;
    NodeTypePtr return_type;
    std::vector<Param> params;
    bool in_binding = false;
    bool in_library = false;

    NodeFunction(std::string qualified_name, NodeId id,
                 std::vector<std::string> attrs, std::string short_name,
                 NodeTypePtr && return_type, std::vector<Param> && params)
        : NodeAttributeHolder(qualified_name, id, NodeKind::Function,
                              attrs),
          short_name(short_name), return_type(std::move(return_type)),
          params(std::move(params)) {}
};

//------------------------------------------------------------------------------
// NodeMethod
//------------------------------------------------------------------------------
struct NodeMethod : public NodeFunction {
    bool is_static = false;

    NodeMethod(std::string qualified_name, NodeId id,
               std::vector<std::string> attrs, std::string short_name,
               NodeTypePtr && return_type, std::vector<Param> && params,
               bool is_static)
        : NodeFunction(qualified_name, id, attrs, short_name,
                       std::move(return_type), std::move(params)),
          is_static(is_static) {
        kind = NodeKind::Method;
    }
};

//------------------------------------------------------------------------------
// Field
//------------------------------------------------------------------------------
struct Field {
    std::string name;
    NodeTypePtr qtype;
};

//------------------------------------------------------------------------------
// NodeRecord
//------------------------------------------------------------------------------
struct NodeRecord : public NodeAttributeHolder {
    std::vector<Field> fields;
    std::vector<NodeMethod> methods;
    RecordKind record_kind;

    uint32_t size;
    uint32_t align;

    NodeRecord(NodeId id, std::vector<std::string> attrs,
               RecordKind record_kind, uint32_t size, uint32_t align)
        : NodeAttributeHolder("", id, NodeKind::Record, attrs),
          record_kind(record_kind), size(size), align(align) {}
};

//------------------------------------------------------------------------------
// Root
//------------------------------------------------------------------------------
struct Root {
    std::vector<TranslationUnit> tus;

    Root(std::vector<TranslationUnit> && tus)
        : tus(std::move(tus))
    {}

    Root(Root && rhs)
        : tus(std::move(rhs.tus))
    {}

    void operator==(Root && rhs) {
        tus = std::move(rhs.tus);
    }
};

} // namespace cppmm
