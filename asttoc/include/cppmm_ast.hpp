//------------------------------------------------------------------------------
// vfx-rs
//------------------------------------------------------------------------------
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace cppmm {

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
    std::string qualified_name;
    NodeId id;
    NodeId context; //< parent context (e.g. record, namespce, TU)
    NodeKind node_kind;

    Node(std::string qualified_name, NodeId id, NodeId context,
         NodeKind node_kind)
        : qualified_name(qualified_name), id(id), context(context),
          node_kind(node_kind) {}

    virtual ~Node(){}
};
using NodePtr = std::unique_ptr<Node>;

//------------------------------------------------------------------------------
// NodeTranslationUnit
//------------------------------------------------------------------------------
struct NodeTranslationUnit : public Node {
    std::vector<NodePtr> children;

    NodeTranslationUnit(std::string qualified_name, NodeId id, NodeId context)
        : Node(qualified_name, id, context, NodeKind::TranslationUnit) {}
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
    NodeType(std::string qualified_name, NodeId id, NodeId context,
             NodeKind node_kind, std::string type_name)
        : Node(qualified_name, id, context, node_kind), type_name(type_name) {}
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
// QType
//------------------------------------------------------------------------------
struct QType {
    NodeId ty;
    bool is_const;

    bool operator==(const QType& rhs) const {
        return ty == rhs.ty && is_const == rhs.is_const;
    }
    bool operator!=(const QType& rhs) const { return !(*this == rhs); }
};

//------------------------------------------------------------------------------
// QType
//------------------------------------------------------------------------------
/// pointer or reference type - check type_kind
struct NodePointerType : public NodeType {
    QType pointee_type;
    PointerKind pointer_kind;
    NodePointerType(std::string qualified_name, NodeId id, NodeId context,
                    std::string type_name, PointerKind pointer_kind,
                    QType pointee_type)
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
    QType qty;
    int index;
};

//------------------------------------------------------------------------------
// NodeAttributeHolder
//------------------------------------------------------------------------------
struct NodeAttributeHolder : public Node {
    std::vector<std::string> attrs;

    NodeAttributeHolder(std::string qualified_name, NodeId id, NodeId context,
                        NodeKind node_kind, std::vector<std::string> attrs)
        : Node(qualified_name, id, context, node_kind), attrs(attrs) {}
};

//------------------------------------------------------------------------------
// NodeFunction
//------------------------------------------------------------------------------
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
};

//------------------------------------------------------------------------------
// NodeMethod
//------------------------------------------------------------------------------
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
};

//------------------------------------------------------------------------------
// Field
//------------------------------------------------------------------------------
struct Field {
    std::string name;
    QType qtype;
};

//------------------------------------------------------------------------------
// NodeRecord
//------------------------------------------------------------------------------
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
};

//------------------------------------------------------------------------------
// Root
//------------------------------------------------------------------------------
struct Root {
    std::vector<NodePtr> nodes;

    Root(std::vector<NodePtr> && nodes)
        : nodes(std::move(nodes))
    {}

    Root(Root && rhs)
        : nodes(std::move(rhs.nodes))
    {}

    void operator==(Root && rhs) {
        nodes = std::move(rhs.nodes);
    }
};

} // namespace cppmm
