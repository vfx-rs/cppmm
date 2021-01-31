//------------------------------------------------------------------------------
// vfx-rs
//------------------------------------------------------------------------------
#pragma once
#include "mapbox/variant.hpp"

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
    Type pointee_type;
    PointerKind pointer_kind;
    NodePointerType(std::string qualified_name, NodeId id, NodeId context,
                    std::string type_name, PointerKind pointer_kind,
                    Type pointee_type)
        : NodeType(qualified_name, id, context, NodeKind::PointerType,
                   type_name),
          pointer_kind(pointer_kind), pointee_type(pointee_type) {}
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
    Type type;
    int index;
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
    Type return_type;
    std::vector<Param> params;
    bool in_binding = false;
    bool in_library = false;

    NodeFunction(std::string qualified_name, NodeId id,
                 std::vector<std::string> attrs, std::string short_name,
                 Type return_type, std::vector<Param> params)
        : NodeAttributeHolder(qualified_name, id, NodeKind::Function,
                              attrs),
          short_name(short_name), return_type(return_type), params(params) {}
};

//------------------------------------------------------------------------------
// NodeMethod
//------------------------------------------------------------------------------
struct NodeMethod : public NodeFunction {
    bool is_static = false;

    NodeMethod(std::string qualified_name, NodeId id,
               std::vector<std::string> attrs, std::string short_name,
               Type return_type, std::vector<Param> params, bool is_static)
        : NodeFunction(qualified_name, id, attrs, short_name,
                       return_type, params),
          is_static(is_static) {
        kind = NodeKind::Method;
    }
};

//------------------------------------------------------------------------------
// Field
//------------------------------------------------------------------------------
struct Field {
    std::string name;
    Type qtype;
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
// Type
//------------------------------------------------------------------------------
using TypeVariant = mapbox::util::variant<NodeBuiltinType, NodeRecordType,
                                          NodePointerType>;
struct Type : public TypeVariant {
    Type(NodeBuiltinType && t) : TypeVariant(t) {}
    Type(NodeRecordType && t) : TypeVariant(t) {}
    Type(NodePointerType && t) : TypeVariant(t) {}
}

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
