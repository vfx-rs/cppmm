#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <unordered_map>

#include "clang/AST/ASTContext.h"
#include "clang/AST/Decl.h"
#include "clang/AST/DeclCXX.h"
#include "clang/AST/DeclTemplate.h"
#include "clang/AST/Type.h"
#include "clang/Basic/LLVM.h"
#include "llvm/Support/Casting.h"
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/ASTMatchers/ASTMatchFinder.h>
#include <clang/ASTMatchers/ASTMatchers.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendAction.h>

#include "clang/Frontend/FrontendAction.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/Support/CommandLine.h"

#include "filesystem.hpp"
#include "pystring.h"

#define SPDLOG_ACTIVE_LEVEL TRACE

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <cassert>

using namespace clang::tooling;
using namespace llvm;
using namespace clang;
using namespace clang::ast_matchers;

namespace ps = pystring;
namespace fs = ghc::filesystem;

#include <nlohmann/json.hpp>
using json = nlohmann::ordered_json;

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
    case NodeKind::ConstantArrayType:
        os << "ConstantArrayType";
        break;
    case NodeKind::Var:
        os << "Var";
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

    virtual NodeKind node_kind() const = 0;

    Node(std::string qualified_name, NodeId id, NodeId context)
        : qualified_name(qualified_name), id(id), context(context) {}

    virtual ~Node() {}

    virtual void write_json_attrs(json& o) const {
        if (id >= 0) {
            o["id"] = id;
        } else {
            o["id"] = nullptr;
        }
    }

    virtual void write_json(json& o) const = 0;

    virtual void write(std::ostream& os, int depth) const = 0;
};

using NodePtr = std::unique_ptr<Node>;

struct indent {
    int i;
};

std::ostream& operator<<(std::ostream& os, const indent& id) {
    for (int i = 0; i < id.i; ++i) {
        os << "    ";
    }
    return os;
}

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
    std::set<NodeId> children;
    /// Include statements from the binding file
    std::vector<std::string> source_includes;
    /// Include paths specified on the cppmm command line
    std::vector<std::string> project_includes;

    static NodeKind _kind;
    virtual NodeKind node_kind() const override { return _kind; }

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

    virtual void write(std::ostream& os, int depth) const override {
        for (const NodeId child : children) {
            auto* node = NODES[child].get();
            node->write(os, depth);
            os << "\n\n";
        }
    }

    NodeTranslationUnit(std::string qualified_name, NodeId id, NodeId context,
                        std::vector<std::string> source_includes,
                        std::vector<std::string> project_includes)
        : Node(qualified_name, id, context), source_includes(source_includes),
          project_includes(project_includes) {}
};

/// Namespace node. Currently not used
struct NodeNamespace : public Node {
    std::string short_name;
    std::set<NodeId> children;

    static NodeKind _kind;
    virtual NodeKind node_kind() const override { return _kind; }

    NodeNamespace(std::string qualified_name, NodeId id, NodeId context,
                  std::string short_name, std::set<NodeId> children)
        : Node(std::move(qualified_name), id, context),
          short_name(std::move(short_name)), children(std::move(children)) {}

    virtual void write_json_attrs(json& o) const override {
        Node::write_json_attrs(o);
        o["short_name"] = short_name;
    }

    virtual void write_json(json& o) const override {
        o["kind"] = "Namespace";
        o["name"] = qualified_name;
        write_json_attrs(o);
    }

    virtual void write(std::ostream& os, int depth) const override {
        os << indent{depth} << "namespace " << short_name << " {\n";
        for (const NodeId child : children) {
            auto* node = NODES[child].get();
            node->write(os, depth);
            os << "\n\n";
        }
        os << indent{depth} << "} // namespace " << short_name;
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
             std::string type_name)
        : Node(qualified_name, id, context), type_name(type_name) {}

    virtual void write_json_attrs(json& o) const override {
        Node::write_json_attrs(o);
        o["type"] = type_name;
    }

    virtual void write(std::ostream& os, int depth) const override {
        os << indent{depth} << type_name;
    }
};

/// A builtin, e.g. int, bool, char etc.
struct NodeBuiltinType : public NodeType {

    static NodeKind _kind;
    virtual NodeKind node_kind() const override { return _kind; }

    NodeBuiltinType(std::string qualified_name, NodeId id, NodeId context,
                    std::string type_name)
        : NodeType(qualified_name, id, context, type_name) {}

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

    void write(std::ostream& os, int depth) const {
        os << indent{depth};
        if (is_const) {
            os << "const ";
        }
        if (ty >= 0) {
            NODES.at(ty)->write(os, 0);
        } else {
            os << "UNKNOWN";
        }
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

    static NodeKind _kind;
    virtual NodeKind node_kind() const override { return _kind; }

    NodePointerType(std::string qualified_name, NodeId id, NodeId context,
                    std::string type_name, PointerKind pointer_kind,
                    QType pointee_type)
        : NodeType(qualified_name, id, context, type_name),
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

    virtual void write(std::ostream& os, int depth) const override {
        os << indent{depth};
        pointee_type.write(os, 0);
    }
};

/// A C-style array, e.g. float[3]
struct NodeConstantArrayType : public NodeType {
    QType element_type;
    uint64_t size;

    static NodeKind _kind;
    virtual NodeKind node_kind() const override { return _kind; }

    NodeConstantArrayType(std::string qualified_name, NodeId id, NodeId context,
                          std::string type_name, QType element_type,
                          uint64_t size)
        : NodeType(std::move(qualified_name), id, context,
                   std::move(type_name)),
          element_type(element_type), size(size) {}

    virtual void write_json(json& o) const override {
        o["kind"] = "ConstantArrayType";
        write_json_attrs(o);

        o["size"] = size;
        o["element_type"] = {};
        element_type.write_json(o["element_type"]);
    }

    virtual void write(std::ostream& os, int depth) const override {
        os << indent{depth};
        element_type.write(os, 0);
        os << "[" << size << "]";
    }
};

/// A reference to a record (i.e. a class or struct)
struct NodeRecordType : public NodeType {
    /// The record declaration node, i.e. the actual type declaration. If the
    /// record referred to hasn't been processed yet, then this will be -1 until
    /// such a time as the record is processed
    NodeId record;

    static NodeKind _kind;
    virtual NodeKind node_kind() const override { return _kind; }

    NodeRecordType(std::string qualified_name, NodeId id, NodeId context,
                   std::string type_name, NodeId record)
        : NodeType(qualified_name, id, context, type_name), record(record) {}

    virtual void write_json_attrs(json& o) const override {
        NodeType::write_json_attrs(o);
        o["record"] = record;
    }

    virtual void write_json(json& o) const override {
        o["kind"] = "RecordType";
        write_json_attrs(o);
    }

    virtual void write(std::ostream& os, int depth) const override {
        os << indent{depth} << type_name;
    }
};

/// An enum type reference
struct NodeEnumType : public NodeType {
    /// The enum declaration node, i.e. the actual type declaration. If the
    /// enum referred to hasn't been processed yet, then this will be -1 until
    /// such a time as the enum is processed
    NodeId enm;

    static NodeKind _kind;
    virtual NodeKind node_kind() const override { return _kind; }

    NodeEnumType(std::string qualified_name, NodeId id, NodeId context,
                 std::string type_name, NodeId enm)
        : NodeType(qualified_name, id, context, type_name), enm(enm) {}

    virtual void write_json_attrs(json& o) const override {
        NodeType::write_json_attrs(o);
        o["enum"] = enm;
    }

    virtual void write_json(json& o) const override {
        o["kind"] = "EnumType";
        write_json_attrs(o);
    }

    virtual void write(std::ostream& os, int depth) const override {
        os << indent{depth} << type_name;
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

    static NodeKind _kind;
    virtual NodeKind node_kind() const override { return _kind; }

    NodeFunctionProtoType(std::string qualified_name, NodeId id, NodeId context,
                          std::string type_name, QType return_type,
                          std::vector<QType> params)
        : NodeType(qualified_name, id, context, type_name),
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

    virtual void write(std::ostream& os, int depth) const override {
        os << indent{depth} << type_name;
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

    void write(std::ostream& os, int depth) const {
        os << indent{depth};
        qty.write(os, 0);
        os << " " << name;
    }
};

std::ostream& operator<<(std::ostream& os, const Param& p) {
    return os << p.name << ": " << p.qty;
}

/// Base struct representing a node that has annotation attributes attached
struct NodeAttributeHolder : public Node {
    /// The annotation attributes
    std::vector<std::string> attrs;

    NodeAttributeHolder(std::string qualified_name, NodeId id, NodeId context,
                        std::vector<std::string> attrs)
        : Node(qualified_name, id, context), attrs(attrs) {}

    virtual void write_json(json& o) const override = 0;

    // FIXME: worst naming ever
    virtual void write_attrs_json(json& o) const {
        o["attributes"] = {};
        for (const auto& a : attrs) {
            o["attributes"].emplace_back(a);
        }
    }
};

struct NodeVar : public NodeAttributeHolder {
    std::string short_name;
    QType qtype;

    static NodeKind _kind;
    virtual NodeKind node_kind() const override { return _kind; }

    NodeVar(std::string qualified_name, NodeId id, NodeId context,
            std::vector<std::string> attrs, std::string short_name, QType qtype)
        : NodeAttributeHolder(std::move(qualified_name), id, context,
                              std::move(attrs)),
          qtype(qtype), short_name(std::move(short_name)) {}

    virtual void write_json_attrs(json& o) const override {
        NodeAttributeHolder::write_json_attrs(o);
    }

    virtual void write_json(json& o) const override {
        o["kind"] = "Var";
        o["qualified_name"] = qualified_name;
        o["short_name"] = short_name;
        o["type"] = {};
        qtype.write_json(o["type"]);
        write_json_attrs(o);
        write_attrs_json(o);
    }

    virtual void write(std::ostream& os, int depth) const override {
        os << indent{depth};
        qtype.write(os, 0);
        os << " " << short_name;
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
    static NodeKind _kind;
    virtual NodeKind node_kind() const override { return _kind; }

    NodeFunction(std::string qualified_name, NodeId id, NodeId context,
                 std::vector<std::string> attrs, std::string short_name,
                 QType return_type, std::vector<Param> params)
        : NodeAttributeHolder(qualified_name, id, context, attrs),
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

    virtual void write(std::ostream& os, int depth) const override {
        os << indent{depth} << qualified_name;
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
    /// Is this method the result of a FunctionTemplateDecl specialization
    /// We use this to differentiate `foo(int)` from `foo<T>(T)` with `T=int`.
    bool is_specialization = false;
    static NodeKind _kind;
    virtual NodeKind node_kind() const override { return _kind; }

    NodeMethod(std::string qualified_name, NodeId id, NodeId context,
               std::vector<std::string> attrs, std::string short_name,
               QType return_type, std::vector<Param> params, bool is_static)
        : NodeFunction(qualified_name, id, context, attrs, short_name,
                       return_type, params),
          is_static(is_static) {}

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

    virtual void write(std::ostream& os, int depth) const override {
        os << indent{depth} << qualified_name;
    }
};

std::ostream& operator<<(std::ostream& os, const NodeMethod& f) {
    if (f.is_static) {
        os << "static ";
    }
    if (f.is_virtual) {
        os << "virtual ";
    }
    os << f.qualified_name << "(";
    for (const Param& p : f.params) {
        os << p << ", ";
    }
    os << ") -> " << f.return_type;
    if (f.is_const) {
        os << " const";
    }
    os << "[[";
    if (f.is_user_provided) {
        os << "user_provided, ";
    }
    if (f.is_overloaded_operator) {
        os << "overloaded_operator, ";
    }
    if (f.is_copy_assignment_operator) {
        os << "copy_assignment_operator, ";
    }
    if (f.is_move_assignment_operator) {
        os << "move_assignment_operator, ";
    }
    if (f.is_constructor) {
        os << "constructor, ";
    }
    if (f.is_copy_constructor) {
        os << "copy_constructor, ";
    }
    if (f.is_move_constructor) {
        os << "move_constructor, ";
    }
    if (f.is_conversion_decl) {
        os << "conversion_decl, ";
    }
    if (f.is_destructor) {
        os << "destructor, ";
    }
    os << "]]";
    return os;
}

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
    /// Does the class have any pure virtual functions?
    bool is_abstract;
    /// Any template parameters. If this is empty, this is not a template class
    std::vector<std::string> template_parameters;
    std::set<std::string> children;

    static NodeKind _kind;
    virtual NodeKind node_kind() const override { return _kind; }

    NodeRecord(std::string qualified_name, NodeId id, NodeId context,
               std::vector<std::string> attrs, std::string short_name,
               std::vector<NodeId> namespaces,
               std::vector<std::string> template_parameters)
        : NodeAttributeHolder(qualified_name, id, context, attrs),
          short_name(std::move(short_name)), namespaces(std::move(namespaces)),
          template_parameters(std::move(template_parameters)) {}

    virtual void write_json_attrs(json& o) const override {
        NodeAttributeHolder::write_json_attrs(o);
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

    virtual void write(std::ostream& os, int depth) const override {
        if (template_parameters.size() > 0) {
            os << indent{depth} << "template <class ";
            os << ps::join(", class ", template_parameters);
            os << ">\n";
        }
        os << indent{depth} << "struct " << short_name << " {\n";

        os << indent{depth} << "}; // struct " << short_name;
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

    static NodeKind _kind;
    virtual NodeKind node_kind() const override { return _kind; }

    NodeEnum(std::string qualified_name, NodeId id, NodeId context,
             std::vector<std::string> attrs, std::string short_name,
             std::vector<NodeId> namespaces,
             std::vector<std::pair<std::string, std::string>> variants,
             uint32_t size, uint32_t align)
        : NodeAttributeHolder(qualified_name, id, context, attrs),
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

    virtual void write(std::ostream& os, int depth) const override {
        os << indent{depth} << qualified_name;
    }
};

NodeKind NodeNamespace::_kind = NodeKind::Namespace;
NodeKind NodeTranslationUnit::_kind = NodeKind::TranslationUnit;
NodeKind NodeBuiltinType::_kind = NodeKind::BuiltinType;
NodeKind NodePointerType::_kind = NodeKind::PointerType;
NodeKind NodeRecordType::_kind = NodeKind::RecordType;
NodeKind NodeEnumType::_kind = NodeKind::EnumType;
NodeKind NodeFunctionProtoType::_kind = NodeKind::FunctionProtoType;
NodeKind NodeFunction::_kind = NodeKind::Function;
NodeKind NodeMethod::_kind = NodeKind::Method;
NodeKind NodeRecord::_kind = NodeKind::Record;
NodeKind NodeEnum::_kind = NodeKind::Enum;
NodeKind NodeConstantArrayType::_kind = NodeKind::ConstantArrayType;
NodeKind NodeVar::_kind = NodeKind::Var;

class GenBindingCallback
    : public clang::ast_matchers::MatchFinder::MatchCallback {
public:
    virtual void
    run(const clang::ast_matchers::MatchFinder::MatchResult& result);
};

template <typename T> T* node_cast(Node* n) {
    assert(n->node_kind() == T::_kind && "incorrect node cast");
    if (n->node_kind() == T::_kind) {
        return reinterpret_cast<T*>(n);
    } else {
        return nullptr;
    }
}

template <typename T> const T* node_cast(const Node* n) {
    assert(n->node_kind() == T::_kind && "incorrect node cast");
    if (n->node_kind() == T::_kind) {
        return reinterpret_cast<T*>(n);
    } else {
        return nullptr;
    }
}

/// Strip the type kinds off the front of a type name in the given string
std::string strip_name_kinds(std::string s) {
    s = pystring::replace(s, "class ", "");
    s = pystring::replace(s, "struct ", "");
    s = pystring::replace(s, "enum ", "");
    s = pystring::replace(s, "union ", "");
    return s;
}

/// Get a nice, qualified name for the given record
std::string get_record_name(const CXXRecordDecl* crd) {
    // we have to do this dance to get the template parameters in the name,
    // otherwise they're omitted
    return strip_name_kinds(
        crd->getTypeForDecl()->getCanonicalTypeInternal().getAsString());
}

/// Find the node corresponding to the given TU filename, creating one if
/// none exists
NodeTranslationUnit* get_translation_unit(const std::string& filename) {
    auto it = NODE_MAP.find(filename);
    if (it != NODE_MAP.end()) {
        const auto& node = NODES.at(it->second);
        assert(node->node_kind() == NodeKind::TranslationUnit &&
               "node is wrong type");
        return (NodeTranslationUnit*)node.get();
    }

    NodeId id = NODES.size();
    auto node = std::make_unique<NodeTranslationUnit>(
        filename, id, 0, std::vector<std::string>{},
        std::vector<std::string>{});
    ROOT.push_back(id);
    auto* node_ptr = node.get();
    NODES.emplace_back(std::move(node));
    NODE_MAP[filename] = id;
    return node_ptr;
}

/// Get the full set of namespaces (including parent records) that lead to
/// a given decl. The decl passed here is expected to be the *parent* of the
/// decl we care about, as in `get_namespaces(target_decl->getParent())`
std::vector<NodeId> get_namespaces(NodeId child,
                                   const clang::DeclContext* parent,
                                   NodeTranslationUnit* node_tu) {
    std::vector<NodeId> result;

    NodeId id;
    SPDLOG_TRACE("Getting namespaces for {}", child);
    while (parent) {
        if (parent->isNamespace()) {
            const clang::NamespaceDecl* ns =
                static_cast<const clang::NamespaceDecl*>(parent);

            auto qualified_name = ns->getQualifiedNameAsString();
            auto short_name = ns->getNameAsString();

            SPDLOG_TRACE("Parent is namespace {}", qualified_name);

            // Add the id of this namespace to our list of namespaces, creating
            // a new NodeNamespace if it doesn't exist yet
            auto it = NODE_MAP.find(qualified_name);
            if (it == NODE_MAP.end()) {
                id = NODES.size();
                auto node = std::make_unique<NodeNamespace>(
                    qualified_name, id, 0, short_name, std::set<NodeId>{child});
                NODES.emplace_back(std::move(node));
                NODE_MAP[qualified_name] = id;

            } else {
                id = it->second;
            }

            SPDLOG_TRACE("Namespace id is {}", id);

            auto* node_ns = node_cast<NodeNamespace>(NODES[id].get());
            node_ns->children.insert(child);
            SPDLOG_TRACE("INserting {} in {}", child, id);
            result.push_back(id);

            parent = parent->getParent();
            child = id;
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
                id = it->second;
                result.push_back(id);
                auto* node_ns = node_cast<NodeNamespace>(NODES[id].get());
                node_ns->children.insert(child);
            }

            parent = parent->getParent();
            child = id;
        } else {
            break;
        }
    }

    node_tu->children.insert(id);

    std::reverse(result.begin(), result.end());
    return result;
}
// Get the canonical definition from a crd
const CXXRecordDecl* get_canonical_def_from_crd(const CXXRecordDecl* crd) {
    if ((crd = crd->getCanonicalDecl())) {
        return crd->getDefinition();
    }
    return nullptr;
}

// Get the templtaed canonical definition decl
const CXXRecordDecl* get_canonical_def_from_ctd(const ClassTemplateDecl* ctd) {
    if ((ctd = ctd->getCanonicalDecl())) {
        if (const auto* crd = ctd->getTemplatedDecl()) {
            return get_canonical_def_from_crd(crd);
        }
    }

    return nullptr;
}

std::vector<std::string> get_template_parameters(const ClassTemplateDecl* ctd) {
    const auto* tpl = ctd->getTemplateParameters();
    std::vector<std::string> result;

    if (tpl == nullptr) {
        SPDLOG_ERROR("Could not get template parameter list for {}",
                     ctd->getQualifiedNameAsString());
        return result;
    }

    for (const auto& nd : *tpl) {
        result.push_back(nd->getNameAsString());
    }

    return result;
}

void process_crd(const CXXRecordDecl* crd,
                 std::vector<std::string> template_parameters) {
    ASTContext& ctx = crd->getASTContext();
    SourceManager& sm = ctx.getSourceManager();
    const auto& loc = crd->getLocation();
    std::string filename = sm.getFilename(loc).str();

    auto qualified_name = crd->getQualifiedNameAsString();
    auto short_name = crd->getNameAsString();
    SPDLOG_DEBUG("process {} at {}:{}", qualified_name, filename,
                 sm.getExpansionLineNumber(loc));

    auto* node_tu = get_translation_unit(filename);

    auto it = NODE_MAP.find(qualified_name);
    if (it == NODE_MAP.end()) {
        SPDLOG_TRACE("Not found, adding");
        NodeId id = NODES.size();
        auto node_record = std::make_unique<NodeRecord>(
            qualified_name, id, 0, std::vector<std::string>{},
            std::move(short_name), std::vector<NodeId>{},
            std::move(template_parameters));

        NODES.emplace_back(std::move(node_record));
        SPDLOG_TRACE("inserting {} : {}", qualified_name, id);
        NODE_MAP[qualified_name] = id;

        auto namespaces = get_namespaces(id, crd->getParent(), node_tu);
        auto* node_rec = node_cast<NodeRecord>(NODES[id].get());
        node_rec->namespaces = std::move(namespaces);
    }
}

void handle_ctd(const ClassTemplateDecl* ctd) {
    ASTContext& ctx = ctd->getASTContext();
    SourceManager& sm = ctx.getSourceManager();
    const auto& loc = ctd->getLocation();
    std::string filename = sm.getFilename(loc).str();

    ctd = ctd->getCanonicalDecl();

    std::string qualified_name = ctd->getQualifiedNameAsString();

    // SPDLOG_TRACE("Got CTD {} at {}:{}", qualified_name, filename,
    //              sm.getExpansionLineNumber(loc));

    auto template_parameters = get_template_parameters(ctd);
    if (template_parameters.empty()) {
        SPDLOG_WARN("Class template {} had no template parameters",
                    qualified_name);
    }

    for (const auto& t : template_parameters) {
        SPDLOG_DEBUG("    {}", t);
    }

    const auto* crd = get_canonical_def_from_ctd(ctd);
    if (crd == nullptr) {
        SPDLOG_ERROR("Could not get CRD from CTD {}", qualified_name);
        return;
    }

    process_crd(crd, std::move(template_parameters));
}

std::string CURRENT_FILENAME;
void GenBindingCallback::run(const MatchFinder::MatchResult& result) {
    if (const CXXRecordDecl* crd =
            result.Nodes.getNodeAs<CXXRecordDecl>("recordDecl")) {
        ASTContext& ctx = crd->getASTContext();
        SourceManager& sm = ctx.getSourceManager();
        const auto& loc = crd->getLocation();
        std::string filename = sm.getFilename(loc).str();

        if (filename == CURRENT_FILENAME) {
            crd = crd->getCanonicalDecl();
            // SPDLOG_TRACE("Got CRD {} as {}:{}",
            // crd->getQualifiedNameAsString(),
            //              filename, sm.getExpansionLineNumber(loc));

            if (const auto* ctd = crd->getDescribedClassTemplate()) {
                // this represents a specialization, ignore it
                // SPDLOG_TRACE("    is a spec of {}",
                //              ctd->getQualifiedNameAsString());
            }
        }

    } else if (const TypeAliasDecl* tdecl =
                   result.Nodes.getNodeAs<TypeAliasDecl>("typeAliasDecl")) {
        if (const auto* crd =
                tdecl->getUnderlyingType()->getAsCXXRecordDecl()) {
            SPDLOG_INFO("GOT CXXRECORDTTYPE {} from TAD {}",
                        crd->getQualifiedNameAsString(),
                        tdecl->getNameAsString());
            // handle_typealias_decl(tdecl, crd);
        }
    } else if (const FunctionDecl* function =
                   result.Nodes.getNodeAs<FunctionDecl>("functionDecl")) {
        // handle_binding_function(function);
    } else if (const EnumDecl* enum_decl =
                   result.Nodes.getNodeAs<EnumDecl>("enumDecl")) {
        // handle_binding_enum(enum_decl);
    } else if (const VarDecl* var_decl =
                   result.Nodes.getNodeAs<VarDecl>("varDecl")) {
        // handle_binding_var(var_decl);
    } else if (const ClassTemplateDecl* ctd =
                   result.Nodes.getNodeAs<ClassTemplateDecl>(
                       "classTemplateDecl")) {
        ctd = ctd->getCanonicalDecl();
        ASTContext& ctx = ctd->getASTContext();
        SourceManager& sm = ctx.getSourceManager();
        const auto& loc = ctd->getLocation();
        std::string filename = sm.getFilename(loc).str();
        if (filename == CURRENT_FILENAME) {
            handle_ctd(ctd);
        }
    }
}

class GenBindingConsumer : public clang::ASTConsumer {
    clang::ast_matchers::MatchFinder _match_finder;
    GenBindingCallback _handler;
    std::string filename;

public:
    explicit GenBindingConsumer(clang::ASTContext* context);
    virtual void HandleTranslationUnit(clang::ASTContext& context);
};

class GenBindingAction : public clang::ASTFrontendAction {
    std::string filename;

public:
    GenBindingAction() {}

    virtual std::unique_ptr<clang::ASTConsumer>
    CreateASTConsumer(clang::CompilerInstance& compiler,
                      llvm::StringRef in_file) {
        return std::unique_ptr<clang::ASTConsumer>(
            new GenBindingConsumer(&compiler.getASTContext()));
    }
};

GenBindingConsumer::GenBindingConsumer(ASTContext* context) {
    // match all record declrations in the cppmm_bind namespace
    DeclarationMatcher record_decl_matcher =
        cxxRecordDecl(hasAncestor(namespaceDecl(hasName("Imath_2_5"))),
                      unless(isImplicit()))
            .bind("recordDecl");
    _match_finder.addMatcher(record_decl_matcher, &_handler);

    DeclarationMatcher ctd_matcher =
        classTemplateDecl(hasAncestor(namespaceDecl(hasName("Imath_2_5"))),
                          unless(isImplicit()))
            .bind("classTemplateDecl");
    _match_finder.addMatcher(ctd_matcher, &_handler);

    // // match all typedef declrations in the cppmm_bind namespace
    // DeclarationMatcher typedef_decl_matcher =
    //     typeAliasDecl(hasAncestor(namespaceDecl(hasName("cppmm_bind"))),
    //                   unless(hasAncestor(recordDecl())),
    //                   unless(isImplicit()))
    //         .bind("typeAliasDecl");
    // _match_finder.addMatcher(typedef_decl_matcher, &_handler);

    // // match all function declarations
    // DeclarationMatcher function_decl_matcher =
    //     functionDecl(hasAncestor(namespaceDecl(hasName("cppmm_bind"))),
    //                  unless(hasAncestor(recordDecl())))
    //         .bind("functionDecl");
    // _match_finder.addMatcher(function_decl_matcher, &_handler);

    // // match all enum declrations in the cppmm_bind namespace
    // DeclarationMatcher enum_decl_matcher =
    //     enumDecl(hasAncestor(namespaceDecl(hasName("cppmm_bind"))),
    //              unless(isImplicit()))
    //         .bind("enumDecl");
    // _match_finder.addMatcher(enum_decl_matcher, &_handler);

    // // match all variable declrations in the cppmm_bind namespace
    // DeclarationMatcher var_decl_matcher =
    //     varDecl(hasAncestor(namespaceDecl(hasName("cppmm_bind"))),
    //             unless(anyOf(isImplicit(), parmVarDecl())))
    //         .bind("varDecl");
    // _match_finder.addMatcher(var_decl_matcher, &_handler);
}

/// Run the binding AST matcher, then run secondary matchers to find functions
/// and enums we're interested in from the bindings (stored in the first pass)
void GenBindingConsumer::HandleTranslationUnit(ASTContext& context) {
    _match_finder.matchAST(context);

    /*
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

    // and a matcher for each var
    for (const auto& kv : binding_vars) {
        SPDLOG_DEBUG("Adding matcher for var {}", kv.first);
        DeclarationMatcher var_decl_matcher =
            varDecl(hasName(kv.second.short_name),
                    unless(hasAncestor(namespaceDecl(hasName("cppmm_bind")))))
                .bind("libraryVarDecl");
        _library_finder.addMatcher(var_decl_matcher, &_library_handler);
    }

    _library_finder.matchAST(context);
    */
}
//
// list of includes for each input source file
// this global is read in process_bindings.cpp
std::unordered_map<std::string, std::vector<std::string>> source_includes;
std::vector<std::string> project_includes;

// Apply a custom category to all command-line options so that they are the
// only ones displayed.
static llvm::cl::OptionCategory CppmmCategory("cppmm options");

// CommonOptionsParser declares HelpMessage with a description of the common
// command-line options related to the compilation database and input files.
// It's nice to have this help message in all tools.
static cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);

// A help message for this specific tool can be added afterwards.
static cl::extrahelp MoreHelp("\nMore help text...\n");

static cl::opt<bool> opt_warn_unbound("u", cl::desc("Warn on unbound methods"));

static cl::opt<int> opt_verbosity(
    "v", cl::desc("Verbosity. 0=errors, 1=warnings, 2=info, 3=debug, 4=trace"));

static cl::opt<std::string> opt_output_directory(
    "o",
    cl::desc(
        "Directory under which output project directories will be written"));
static cl::list<std::string>
    opt_rename_namespace("n", cl::desc("Rename namespace <to>=<from>"));
static cl::opt<std::string> opt_rust_sys_directory(
    "rust-sys",
    cl::desc("Directory under which rust-sys project will be written"));

static cl::list<std::string>
    opt_includes("i", cl::desc("Extra includes for the project"));
static cl::list<std::string>
    opt_libraries("l", cl::desc("Libraries to link against"));

int main(int argc_, const char** argv_) {
    // set up logging
    auto _console = spdlog::stdout_color_mt("console");
    std::string cwd = fs::current_path();

    // FIXME: there's got to be a more sensible way of doing this but I can't
    // figure it out...
    int argc = argc_ + 2;
    const char** argv = new const char*[argc + 1];
    int i;
    bool has_ddash = false;
    for (i = 0; i < argc_; ++i) {
        argv[i] = argv_[i];
        if (!strcmp(argv[i], "--")) {
            has_ddash = true;
        }
    }

    // get the path to the binary, assuming that the resources folder will be
    // stored alongside it
    // FIXME: this method will work only on linux...
    auto exe_path = cwd / fs::path(argv[0]);
    if (fs::is_symlink(exe_path)) {
        exe_path = fs::read_symlink(exe_path);
    }
    if (exe_path.empty()) {
        SPDLOG_CRITICAL("Could not get exe path");
        return -1;
    }

    std::string respath1 = (exe_path.parent_path() / "resources").string();
    if (!has_ddash) {
        argv[i++] = "--";
        argc++;
    }
    argv[i++] = "-isystem";
    argv[i++] = respath1.c_str();

    // project_includes = parse_project_includes(argc, argv);

    CommonOptionsParser OptionsParser(argc, argv, CppmmCategory);

    switch (opt_verbosity) {
    case 0:
        spdlog::set_level(spdlog::level::err);
        break;
    case 1:
        spdlog::set_level(spdlog::level::warn);
        break;
    case 2:
        spdlog::set_level(spdlog::level::info);
        break;
    case 3:
        spdlog::set_level(spdlog::level::debug);
        break;
    case 4:
        spdlog::set_level(spdlog::level::trace);
        break;
    default:
        spdlog::set_level(spdlog::level::warn);
        break;
    }
    spdlog::set_pattern("%20s:%4# %^[%5l]%$ %v");

    ArrayRef<std::string> src_path = OptionsParser.getSourcePathList();
    std::vector<std::string> header_paths;
    std::vector<std::string> vtu;
    std::vector<std::string> vtu_paths;
    if (src_path.size() == 1 && fs::is_directory(src_path[0])) {
        // we've been supplied a single directory to start from, find all the
        // cpp files under it to use as binding files
        // TODO: figure out a better directory structure, e.g.
        // /bind
        // /config.toml
        for (const auto& entry : fs::directory_iterator(src_path[0])) {
            if (entry.path().extension() == ".hpp" ||
                entry.path().extension() == ".h" ||
                entry.path().extension() == ".hxx") {
                auto header_path =
                    ps::os::path::abspath(entry.path().string(), cwd);
                header_paths.push_back(header_path);
                SPDLOG_DEBUG("Found header file {}", header_path);

                vtu.push_back(fmt::format("#include \"{}\"", header_path));
                vtu_paths.push_back(fmt::format(
                    "/tmp/{}.cpp", fs::path(header_path).stem().string()));
            }
        }
    } else {
        // otherwise we'll assume we've been given a list of header files to
        for (const auto& s : src_path) {
            auto header_path = ps::os::path::abspath(s, cwd);
            header_paths.push_back(header_path);
            SPDLOG_DEBUG("Found header file {}", header_path);

            vtu.push_back(fmt::format("#include \"{}\"", header_path));
            vtu_paths.push_back(fmt::format(
                "/tmp/{}.cpp", fs::path(header_path).stem().string()));
        }
    }
    auto& compdb = OptionsParser.getCompilations();

    for (int i = 0; i < vtu.size(); ++i) {
        SPDLOG_INFO("Processing {}", header_paths[i]);
        CURRENT_FILENAME = header_paths[i];
        ClangTool Tool(compdb, ArrayRef<std::string>(vtu_paths[i]));
        Tool.mapVirtualFile(vtu_paths[i], vtu[i]);
        std::string output_dir = cwd;
        if (opt_output_directory != "") {
            output_dir = opt_output_directory;
        }

        auto process_binding_action =
            newFrontendActionFactory<GenBindingAction>();
        int result = Tool.run(process_binding_action.get());

        if (!fs::exists(output_dir) && !fs::create_directories(output_dir)) {
            SPDLOG_ERROR("Could not create output directory '{}'", output_dir);
            return -2;
        }
    }

    for (const NodeId id : ROOT) {
        auto* node_tu = node_cast<NodeTranslationUnit>(NODES[id].get());
        std::cout << "writing tu " << std::endl;
        node_tu->write(std::cout, 0);
    }

    // return result;
}
