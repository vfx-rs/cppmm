#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <unistd.h>
#include <unordered_map>

#include "clang/AST/ASTContext.h"
#include "clang/AST/Decl.h"
#include "clang/AST/DeclBase.h"
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

#include "base64.hpp"
#include "filesystem.hpp"
#include "pystring.h"
#include "resources.hpp"

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
    TemplateTypeParmType,
    TypedefNameDecl,
    TypedefType,
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
    case NodeKind::TemplateTypeParmType:
        os << "TemplateTypeParmType";
        break;
    case NodeKind::TypedefNameDecl:
        os << "TypedefNameDecl";
        break;
    case NodeKind::TypedefType:
        os << "TypedefType";
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

    virtual void write(std::ostream& os, int depth) const = 0;
};

using NodePtr = std::unique_ptr<Node>;

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

std::string TARGET_NAMESPACE;
std::string TARGET_NAMESPACE_INTERNAL;
std::string TARGET_NAMESPACE_PUBLIC;

std::string CURRENT_FILENAME;

class NodeRecord;
std::vector<const NodeRecord*> TEMPLATE_RECORDS;

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

    virtual void write(std::ostream& os, int depth) const override;

    NodeTranslationUnit(std::string qualified_name, NodeId id, NodeId context,
                        std::vector<std::string> source_includes,
                        std::vector<std::string> project_includes)
        : Node(qualified_name, id, context), source_includes(source_includes),
          project_includes(project_includes) {}
};

/// Namespace node. Stores a set of its children
struct NodeNamespace : public Node {
    std::string short_name;
    std::set<NodeId> children;

    static NodeKind _kind;
    virtual NodeKind node_kind() const override { return _kind; }

    NodeNamespace(std::string qualified_name, NodeId id, NodeId context,
                  std::string short_name, std::set<NodeId> children)
        : Node(std::move(qualified_name), id, context),
          short_name(std::move(short_name)), children(std::move(children)) {}

    virtual void write(std::ostream& os, int depth) const override {
        auto name = short_name;
        bool write_inner_namespace = false;
        if (short_name == TARGET_NAMESPACE &&
            !TARGET_NAMESPACE_INTERNAL.empty()) {
            name = TARGET_NAMESPACE_INTERNAL;

            if (!TARGET_NAMESPACE_PUBLIC.empty()) {
                write_inner_namespace = true;
            }
        }

        os << indent{depth} << "namespace " << name << " {\n\n";
        if (write_inner_namespace) {
            os << indent{depth} << "namespace " << TARGET_NAMESPACE_PUBLIC
               << " = ::" << TARGET_NAMESPACE_INTERNAL << ";\n\n";
        }
        for (const NodeId child : children) {
            auto* node = NODES[child].get();
            node->write(os, depth);
            os << "\n\n";
        }
        os << indent{depth} << "} // namespace " << name;
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

    virtual void write(std::ostream& os, int depth) const override {
        os << indent{depth};
        if (type_name == "_Bool") {
            os << "bool";
        } else {
            os << type_name;
        }
    }
};

struct NodeTemplateTypeParmType : public NodeType {
    NodeTemplateTypeParmType(std::string qualified_name, NodeId id,
                             NodeId context, std::string type_name)
        : NodeType(qualified_name, id, context, type_name) {}

    static NodeKind _kind;
    virtual NodeKind node_kind() const override { return _kind; }

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
};

/// QType is the equivalent of clang's QualType. Currently just defines the
/// constness of the wrapped type node. These are stored on the AST nodes
/// anywhere a type is needed.
struct QType {
    /// Type we're constifying
    NodeId ty;
    bool is_const;

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

struct NodeRecord;
void write_namespaces(std::ostream& os, const std::vector<NodeId>& namespaces);

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

    virtual void write(std::ostream& os, int depth) const override {
        os << indent{depth};
        pointee_type.write(os, 0);
        if (pointer_kind == PointerKind::Pointer) {
            os << "*";
        } else if (pointer_kind == PointerKind::Reference) {
            os << "&";
        } else if (pointer_kind == PointerKind::RValueReference) {
            os << "&&";
        }
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

    virtual void write(std::ostream& os, int depth) const override {
        os << indent{depth};
        element_type.write(os, 0);
        os << "[" << size << "]";
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

    virtual void write(std::ostream& os, int depth) const override {
        os << indent{depth} << type_name;
    }
};

struct NodeTypedefType : public NodeType {
    std::string short_name;
    std::vector<std::string> namespaces;

    static NodeKind _kind;
    virtual NodeKind node_kind() const override { return _kind; }

    NodeTypedefType(std::string qualified_name, NodeId id, NodeId context,
                          std::string type_name, std::string short_name, std::vector<std::string> namespaces)
        : NodeType(qualified_name, id, context, type_name),
          short_name(short_name), namespaces(namespaces) {}

    virtual void write(std::ostream& os, int depth) const override {
        os << indent{depth};
        for (const auto& ns: namespaces) {
            if (ns == TARGET_NAMESPACE) {
                os << TARGET_NAMESPACE_PUBLIC;
            } else {
                os << ns;
            }

            os << "::";
        }
        os << short_name;
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

bool operator==(const Param& a, const Param& b) {
    if (a.name != b.name) {
        return false;
    }

    if (a.qty != b.qty) {
        return false;
    }

    return true;
}

bool operator!=(const Param& a, const Param& b) { return !(a == b); }

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

    virtual void write(std::ostream& os, int depth) const override {
        os << indent{depth};
        qtype.write(os, 0);
        os << " " << short_name;
    }
};

void write_comment(std::ostream& os, const std::string& s, int depth) {
    std::stringstream ss(s);
    std::string line;
    while (std::getline(ss, line)) {
        os << indent{depth} << "/// " << line << "\n";
    }
}

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
    // template parameters
    std::vector<std::string> template_parameters;
    /// Comment on the decl
    std::string comment;

    static NodeKind _kind;
    virtual NodeKind node_kind() const override { return _kind; }

    NodeFunction(std::string qualified_name, NodeId id, NodeId context,
                 std::vector<std::string> attrs, std::string short_name,
                 QType return_type, std::vector<Param> params,
                 std::vector<std::string> template_parameters)
        : NodeAttributeHolder(qualified_name, id, context, attrs),
          short_name(short_name), return_type(return_type), params(params),
          template_parameters(std::move(template_parameters)) {}

    virtual void write(std::ostream& os, int depth) const override {
        write_comment(os, comment, depth);

        if (template_parameters.size() != 0) {
            os << indent{depth};
            bool first = true;
            os << "template <";
            for (const auto& t : template_parameters) {
                if (!first) {
                    os << ", ";
                }
                first = false;
                os << "typename " << t;
            }
            os << ">\n";
        }

        os << indent{depth};
        return_type.write(os, 0);
        os << " " << short_name << "(";
        bool first = true;
        for (const auto& p : params) {
            if (!first) {
                os << ", ";
            }
            first = false;
            p.write(os, 0);
        }
        os << ");\n";
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
               QType return_type, std::vector<Param> params, bool is_static,
               std::vector<std::string> template_parameters)
        : NodeFunction(qualified_name, id, context, attrs, short_name,
                       return_type, params, std::move(template_parameters)),
          is_static(is_static) {}

    virtual void write(std::ostream& os, int depth) const override {
        write_comment(os, comment, depth);

        if (template_parameters.size() != 0) {
            os << indent{depth};
            bool first = true;
            os << "template <";
            for (const auto& t : template_parameters) {
                if (!first) {
                    os << ", ";
                }
                first = false;
                os << "typename " << t;
            }
            os << ">\n";
        }

        os << indent{depth};
        if (is_static) {
            os << "static ";
        }
        if (!is_constructor && !is_destructor && !is_conversion_decl) {
            return_type.write(os, 0);
            os << " ";
        }
        os << short_name << "(";
        bool first = true;
        for (const auto& p : params) {
            if (!first) {
                os << ", ";
            }
            first = false;
            p.write(os, 0);
        }
        os << ")";
        if (is_const) {
            os << " const";
        }
        if (is_move_assignment_operator || is_move_constructor) {
            os << " CPPMM_IGNORE";
        }
        os << ";\n";
    }
};

bool operator==(const NodeMethod& a, const NodeMethod& b) {
    if (a.short_name != b.short_name) {
        return false;
    }

    if (a.is_static != b.is_static) {
        return false;
    }

    if (a.is_const != b.is_const) {
        return false;
    }

    if (a.return_type != b.return_type) {
        return false;
    }

    if (a.params.size() != b.params.size()) {
        return false;
    }

    for (int i = 0; i < a.params.size(); ++i) {
        if (a.params[i] != b.params[i]) {
            return false;
        }
    }

    return true;
}

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
    bool is_abstract = false;
    /// Does this class have any public constructors?
    bool has_public_ctor = true;
    /// Any template parameters. If this is empty, this is not a template class
    std::vector<std::string> template_parameters;
    std::set<NodeId> children;
    /// Comment on the decl
    std::string comment;

    static NodeKind _kind;
    virtual NodeKind node_kind() const override { return _kind; }

    NodeRecord(std::string qualified_name, NodeId id, NodeId context,
               std::vector<std::string> attrs, std::string short_name,
               std::vector<NodeId> namespaces,
               std::vector<std::string> template_parameters)
        : NodeAttributeHolder(qualified_name, id, context, attrs),
          short_name(std::move(short_name)), namespaces(std::move(namespaces)),
          template_parameters(std::move(template_parameters)) {}

    virtual void write(std::ostream& os, int depth) const override {
        write_comment(os, comment, depth);

        if (template_parameters.size() > 0) {
            os << indent{depth} << "template <class ";
            os << ps::join(", class ", template_parameters);
            os << ">\n";
        }
        os << indent{depth} << "struct " << short_name << " {\n";

        os << indent{depth + 1} << "using BoundType = ";
        write_namespaces(os, namespaces);
        os << short_name;
        if (template_parameters.size() > 0) {
            os << "<" << ps::join(", ", template_parameters) << ">";
        }
        os << ";\n\n";

        for (const auto mid : methods) {
            NODES[mid]->write(os, depth + 1);
            os << "\n";
        }

        for (const auto& child : children) {
            os << "\n";
            NODES[child]->write(os, depth + 1);
            os << "\n";
        }

        os << indent{depth} << "}";

        // if the record is abstract, or has no public constructors then
        // it has to be opaqueptr. Otherwise we'll assume opaquebytes
        /* if (is_abstract || !has_public_ctor) { */
        os << " CPPMM_OPAQUEPTR";
        /* } else { */
        /* os << " CPPMM_OPAQUEBYTES"; */
        /* } */

        os << "; // struct " << short_name << "\n";

        // finally, if we're a template record, write commented example
        // explicit instantiation code for the user to fill in
        if (!template_parameters.empty()) {
            os << "\n";
            std::vector<std::string> dummy_parms;
            for (const auto& t : template_parameters) {
                dummy_parms.push_back("int");
            }

            os << indent{depth}
               << "// TODO: fill in explicit instantiations, e.g.:\n";
            os << indent{depth} << "// template class " << short_name;
            os << "<" << ps::join(", ", dummy_parms) << ">;\n";
            os << "// using " << short_name << "Int = ";
            write_namespaces(os, namespaces);
            os << short_name << "<" << ps::join(", ", dummy_parms) << ">;\n";

            TEMPLATE_RECORDS.push_back(this);
        }
    }
};

/// A record is a class or struct declaration containing fields and methods
struct NodeTypedefNameDecl : public NodeAttributeHolder {
    /// The 'leaf' of the qualified name
    std::string short_name;
    /// The full path of namespaces leading to this decl
    std::vector<NodeId> namespaces;
    /// The underlying type name
    std::string underlying_type;

    static NodeKind _kind;
    virtual NodeKind node_kind() const override { return _kind; }

    NodeTypedefNameDecl(std::string qualified_name, NodeId id, NodeId context,
                        std::vector<std::string> attrs, std::string short_name,
                        std::vector<NodeId> namespaces,
                        std::string underlying_type)
        : NodeAttributeHolder(qualified_name, id, context, attrs),
          short_name(std::move(short_name)), namespaces(std::move(namespaces)),
          underlying_type(underlying_type) {}

    virtual void write(std::ostream& os, int depth) const override {
        os << indent{depth + 1} << "using " << short_name << " = ";
        write_namespaces(os, namespaces);
        os << short_name << ";\n";
    }
};

void NodeTranslationUnit::write(std::ostream& os, int depth) const {
    os << "#include <" << source_includes[0] << ">\n";
    os << "#include <cppmm_bind.hpp>\n\n";
    os << "namespace cppmm_bind {\n\n";
    for (const NodeId child : children) {
        auto* node = NODES[child].get();
        node->write(os, depth);
        os << "\n\n";
    }
    os << "} // namespace cppmm_bind\n";

    if (!TEMPLATE_RECORDS.empty()) {
        os << "\n";
        os << "// TODO: fill in explicit instantiations\n";
        for (const auto* rec : TEMPLATE_RECORDS) {
            std::vector<std::string> dummy_parms;
            for (const auto& t : rec->template_parameters) {
                dummy_parms.push_back("int");
            }

            os << "// template class ";
            write_namespaces(os, rec->namespaces);
            os << rec->short_name << "<" << ps::join(", ", dummy_parms)
               << ">;\n";
        }
    }
}

std::string get_comment(const clang::Decl* decl) {
    ASTContext& ctx = decl->getASTContext();
    SourceManager& sm = ctx.getSourceManager();

    const RawComment* rc = ctx.getRawCommentForDeclNoCache(decl);
    if (rc) {
        // Found comment!
        SourceRange range = rc->getSourceRange();

        PresumedLoc startPos = sm.getPresumedLoc(range.getBegin());
        PresumedLoc endPos = sm.getPresumedLoc(range.getEnd());

        return rc->getFormattedText(sm, sm.getDiagnostics());
    }
    return "";
}

void write_namespaces(std::ostream& os, const std::vector<NodeId>& namespaces) {
    for (auto id : namespaces) {
        auto kind = NODES.at(id)->node_kind();
        if (kind == NodeKind::Namespace) {
            auto node_ns = node_cast<NodeNamespace>(NODES.at(id).get());
            if (node_ns->short_name == TARGET_NAMESPACE &&
                !TARGET_NAMESPACE_PUBLIC.empty()) {
                os << TARGET_NAMESPACE_PUBLIC << "::";
            } else {
                os << node_ns->short_name << "::";
            }
        } else if (kind == NodeKind::Record) {
            auto node_par = node_cast<NodeRecord>(NODES.at(id).get());
            os << node_par->short_name << "::";
        } else {
            SPDLOG_CRITICAL("Unexpected NodeKind {} on node {} while "
                            "traversing parents",
                            NODES[id]->node_kind(), NODES[id]->qualified_name);
        }
    }
}

/// A reference to a record (i.e. a class or struct)
struct NodeRecordType : public NodeType {
    /// The record declaration node, i.e. the actual type declaration. If the
    /// record referred to hasn't been processed yet, then this will be -1 until
    /// such a time as the record is processed
    NodeId record;
    std::vector<std::string> template_parameters;

    static NodeKind _kind;
    virtual NodeKind node_kind() const override { return _kind; }

    NodeRecordType(std::string qualified_name, NodeId id, NodeId context,
                   std::string type_name, NodeId record,
                   std::vector<std::string> template_parameters)
        : NodeType(qualified_name, id, context, type_name), record(record),
          template_parameters(std::move(template_parameters)) {}

    virtual void write(std::ostream& os, int depth) const override {

        auto output_type_name = type_name;
        // do a little cleanup of common types here to make the output
        // more readable
        if (type_name == "std::__cxx11::basic_string<char>") {
            output_type_name = "std::string";
        }

        os << indent{depth};
        if (record != -1) {
            auto node_rec = node_cast<NodeRecord>(NODES.at(record).get());
            write_namespaces(os, node_rec->namespaces);
            os << node_rec->short_name;
        } else {
            if (type_name.find(TARGET_NAMESPACE) == 0 &&
                !TARGET_NAMESPACE_PUBLIC.empty()) {
                os << ps::replace(output_type_name, TARGET_NAMESPACE,
                                  TARGET_NAMESPACE_PUBLIC);
            } else {
                os << output_type_name;
            }
        }
        if (!template_parameters.empty()) {
            os << "<" << ps::join(", ", template_parameters) << ">";
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

    virtual void write(std::ostream& os, int depth) const override {
        os << indent{depth} << "enum " << short_name << " {\n";
        for (const auto& p : variants) {
            os << indent{depth + 1} << p.first << " = " << p.second << ",\n";
        }
        os << indent{depth} << "};";
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

    virtual void write(std::ostream& os, int depth) const override {
        os << indent{depth};
        if (enm != -1) {
            auto node_enum = node_cast<NodeEnum>(NODES.at(enm).get());
            write_namespaces(os, node_enum->namespaces);
            os << node_enum->short_name;
        } else {
            if (type_name.find(TARGET_NAMESPACE) == 0 &&
                !TARGET_NAMESPACE_PUBLIC.empty()) {
                os << ps::replace(type_name, TARGET_NAMESPACE,
                                  TARGET_NAMESPACE_PUBLIC);
            } else {
                os << type_name;
            }
        }
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
NodeKind NodeTemplateTypeParmType::_kind = NodeKind::TemplateTypeParmType;
NodeKind NodeTypedefNameDecl::_kind = NodeKind::TypedefNameDecl;
NodeKind NodeTypedefType::_kind = NodeKind::TypedefType;

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

bool is_in_target_namespace(const DeclContext* ctx) {
    auto* parent = ctx;
    while (parent) {
        if (parent->isNamespace()) {
            const clang::NamespaceDecl* ns =
                static_cast<const clang::NamespaceDecl*>(parent);

            auto qualified_name = ns->getQualifiedNameAsString();
            SPDLOG_INFO("Parent is namespace {}", qualified_name);
            auto short_name = ns->getNameAsString();

            if (short_name == TARGET_NAMESPACE) {
                return true;
            }
        }

        parent = parent->getParent();
    }

    return false;
}

/// Get the full set of namespaces (including parent records) that lead to
/// a given decl. The decl passed here is expected to be the *parent* of the
/// decl we care about, as in `get_namespaces(target_decl->getParent())`
std::vector<NodeId> get_namespaces(NodeId child,
                                   const clang::DeclContext* parent,
                                   NodeTranslationUnit* node_tu) {
    std::vector<NodeId> result;

    NodeId id = child;
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
            SPDLOG_TRACE("Inserting {} in {}", child, id);
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
                SPDLOG_CRITICAL("Could not find record {} when processing "
                                "namespaces for {}",
                                record_name, NODES[child]->qualified_name);
            } else {
                id = it->second;
                result.push_back(id);
                auto* node_rec = node_cast<NodeRecord>(NODES[id].get());
                node_rec->children.insert(child);
            }

            parent = parent->getParent();
            child = id;
        } else if (parent->isTranslationUnit()) {
            break;
        } else if (parent->isExternCContext()) {
            parent = parent->getParent();
        } else {
            SPDLOG_CRITICAL("Unhandled parent kind {}",
                            parent->getDeclKindName());
            exit(17);
        }
    }

    assert(id >= 0 && id < NODES.size() && "out of range id");
    node_tu->children.insert(id);

    std::reverse(result.begin(), result.end());
    return result;
}

// Get just the names of the enclosing namespaces, without doing any TU creation
std::vector<std::string> get_namespace_names(const clang::DeclContext* parent) {
    std::vector<std::string> result;

    while (parent) {
        if (parent->isNamespace()) {
            const clang::NamespaceDecl* ns =
                static_cast<const clang::NamespaceDecl*>(parent);

            auto qualified_name = ns->getQualifiedNameAsString();
            auto short_name = ns->getNameAsString();

            result.push_back(short_name);

            parent = parent->getParent();
        } else if (parent->isRecord()) {
            // Parent is a Record type. We should have created the record
            // already by the time we get here...
            const clang::CXXRecordDecl* crd =
                static_cast<const clang::CXXRecordDecl*>(parent);

            auto short_name = crd->getNameAsString();
            result.push_back(short_name);

            parent = parent->getParent();
        } else if (parent->isTranslationUnit()) {
            break;
        } else if (parent->isExternCContext()) {
            parent = parent->getParent();
        } else {
            SPDLOG_CRITICAL("Unhandled parent kind {}",
                            parent->getDeclKindName());
            exit(17);
        }
    }

    std::reverse(result.begin(), result.end());
    return result;
}

// Get the canonical definition from a crd
const CXXRecordDecl* get_canonical_def_from_crd(const CXXRecordDecl* crd) {
    if (const CXXRecordDecl* can = crd->getCanonicalDecl()) {
        /* SPDLOG_INFO("Got can {} from crd {}",
         * can->getQualifiedNameAsString(), crd->getQualifiedNameAsString()); */
        return can->getDefinition();
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

std::vector<std::string> get_template_parameters(const TemplateDecl* ctd) {
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

QType process_qtype(
    const QualType& qt,
    const std::vector<std::vector<std::string>>& template_parameters);

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
        std::vector<std::vector<std::string>> template_parameters;
        QType return_type =
            process_qtype(fpt->getReturnType(), template_parameters);
        std::vector<QType> params;
        for (const QualType& pqt : fpt->param_types()) {
            params.push_back(process_qtype(pqt, template_parameters));
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
QType process_qtype(
    const QualType& qt,
    const std::vector<std::vector<std::string>>& template_parameters) {
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
            QType pointee_qtype = process_qtype(
                qt->getPointeeType(), template_parameters);
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
    } else if (const auto* tdt = qt->getAs<TypedefType>()) {
        const TypedefNameDecl* tnd = tdt->getDecl();

        const std::string qualified_name = tnd->getQualifiedNameAsString();
        const std::string short_name = tnd->getNameAsString();
        std::vector<std::string> namespaces = get_namespace_names(tnd->getDeclContext());

        const std::string type_node_name = "TYPE:" + qualified_name;
        auto it = NODE_MAP.find(type_node_name);
        NodeId id;
        if (it == NODE_MAP.end()) {
            id = NODES.size();
            auto node_type = std::make_unique<NodeTypedefType>(
                type_node_name, id, 0, qualified_name, short_name, namespaces);
            NODES.emplace_back(std::move(node_type));
            NODE_MAP[type_node_name] = id;
        } else {
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
            QType element_type =
                process_qtype(cat->getElementType(), template_parameters);
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
    } else if (qt->isTemplateTypeParmType()) {
        const auto* ttpt = qt->getAs<TemplateTypeParmType>();
        int depth = ttpt->getDepth();
        int index = ttpt->getIndex();
        assert(template_parameters.size() > depth &&
               "template parameters is not deep enough");
        assert(template_parameters[depth].size() > index &&
               "template parameters is not long enough");
        const std::string type_name = template_parameters[depth][index];
        const std::string type_node_name = "TYPE:" + type_name;

        auto it = NODE_MAP.find(type_node_name);
        NodeId id;
        if (it == NODE_MAP.end()) {
            id = NODES.size();
            auto tp =
                std::vector<std::vector<std::string>>{template_parameters};
            auto node_type = std::make_unique<NodeTemplateTypeParmType>(
                type_node_name, id, 0, type_name);
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

        if (qt->isBuiltinType() && type_name == "unsigned long") {
            const auto* tdt = qt->getAs<TypedefType>();
            if (tdt && tdt->getDecl()->getNameAsString() == "uint64_t") {
                type_name = "uint64_t";
                type_node_name = "TYPE:uint64_t";
            } else if (tdt && tdt->getDecl()->getNameAsString() == "size_t") {
                type_name = "size_t";
                type_node_name = "TYPE:size_t";
            } else if (tdt &&
                       tdt->getDecl()->getNameAsString() == "size_type") {
                // FIXME: Nasty hack here to get e.g. std::string::size_type
                // will this bite us?
                type_name = "size_t";
                type_node_name = "TYPE:size_t";
            } else if (tdt) {
                /* SPDLOG_WARN("Unhandled unsigned long typedef {}",
                 * tdt->getDecl()->getNameAsString()); */
                // If we're some other typedef of unsigned long, try desugaring
                // recursively until we get to a typedef we can handle
                QualType ds_type = tdt->desugar();
                return process_qtype(ds_type, {});
            }
        } else if (qt->isBuiltinType() && type_name == "long") {
            const auto* tdt = qt->getAs<TypedefType>();
            if (tdt && tdt->getDecl()->getNameAsString() == "int64_t") {
                type_name = "int64_t";
                type_node_name = "TYPE:int64_t";
            } else if (tdt &&
                       tdt->getDecl()->getNameAsString() == "ptrdiff_t") {
                type_name = "ptrdiff_t";
                type_node_name = "TYPE:ptrdiff_t";
            }
        }

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
                    type_node_name, id, 0, type_name, id_rec,
                    std::vector<std::string>{});
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
            } else if (qt->isDependentType()) {
                qt->dump();
                const auto* crd = qt->getAsCXXRecordDecl();
                if (crd) {
                    // See if we've already processed a record matching this
                    // type and get its id if we have. If not we'll store -1
                    // until we come back and process the decl later.
                    const std::string record_name =
                        crd->getQualifiedNameAsString();
                    NodeId id_rec = -1;
                    auto it_rec = NODE_MAP.find(record_name);
                    if (it_rec != NODE_MAP.end()) {
                        id_rec = it_rec->second;
                    }

                    std::vector<std::string> t_parms;
                    // InjectedClassNameType represents the situation where
                    // the class name can be referred to without the template
                    // parameters inside the class delcaration
                    if (const auto* icnt =
                            dyn_cast<InjectedClassNameType>(qt.getTypePtr())) {
                        const auto* td =
                            icnt->getTemplateName().getAsTemplateDecl();
                        if (td) {
                            const auto* ctd = dyn_cast<ClassTemplateDecl>(td);
                            if (ctd) {
                                t_parms = get_template_parameters(ctd);
                            }
                        }
                    }

                    auto node_record_type = std::make_unique<NodeRecordType>(
                        type_node_name, id, 0, type_name, id_rec, t_parms);
                    NODES.emplace_back(std::move(node_record_type));
                    NODE_MAP[type_node_name] = id;
                } else if (const auto* tst =
                               dyn_cast<TemplateSpecializationType>(
                                   qt.getTypePtr())) {
                    const auto* td = tst->getTemplateName().getAsTemplateDecl();
                    if (td) {
                        const auto* ctd = dyn_cast<ClassTemplateDecl>(td);
                        if (ctd) {
                            std::string record_name =
                                ctd->getQualifiedNameAsString();
                            SPDLOG_TRACE("GOT CTD {}", record_name);

                            // remove any template guff from the type name
                            // since we'll reconstruct it
                            type_name =
                                type_name.substr(0, type_name.find("<"));

                            NodeId id_rec = -1;
                            auto it_rec = NODE_MAP.find(record_name);
                            if (it_rec != NODE_MAP.end()) {
                                id_rec = it_rec->second;
                            }

                            auto template_parameters =
                                get_template_parameters(ctd);
                            if (template_parameters.empty()) {
                                SPDLOG_WARN("Class template {} had no template "
                                            "parameters",
                                            record_name);
                            }

                            auto node_record_type =
                                std::make_unique<NodeRecordType>(
                                    type_node_name, id, 0, type_name, id_rec,
                                    template_parameters);
                            NODES.emplace_back(std::move(node_record_type));
                            NODE_MAP[type_node_name] = id;
                        }
                    } else {
                        SPDLOG_CRITICAL("UNHANDLED DEPENDENT TYPE");
                        qt->dump();
                        id = NodeId(-1);
                    }
                } else {
                    SPDLOG_CRITICAL("Unhandled type {}", type_name);
                    qt->dump();
                    id = NodeId(-1);
                }
            } else {
                SPDLOG_CRITICAL("Unhandled type {}", type_node_name);
                qt->dump();
                id = NodeId(-1);
            }
        } else {
            id = it->second;
            if (id == -1) {
                SPDLOG_CRITICAL("-1 id in map");
            }
        }

        return QType{id, qt.isConstQualified()};
    }
}

void process_function_parameters(
    const FunctionDecl* fd, QType& return_qtype, std::vector<Param>& params,
    const std::vector<std::vector<std::string>>& template_parameters) {
    SPDLOG_TRACE("    -> {}", fd->getReturnType().getAsString());
    return_qtype = process_qtype(fd->getReturnType(), template_parameters);

    for (const ParmVarDecl* pvd : fd->parameters()) {
        int index = pvd->getFunctionScopeIndex();
        SPDLOG_TRACE("        {}: {}", pvd->getQualifiedNameAsString(),
                     pvd->getType().getCanonicalType().getAsString());
        QType qtype = process_qtype(pvd->getType(), template_parameters);

        params.emplace_back(Param{pvd->getNameAsString(), qtype, index, {}});

        if (const auto* vtd = pvd->getDescribedVarTemplate()) {
            SPDLOG_TRACE("            GOT VTD");
        }
        if (const auto* td = pvd->getDescribedTemplate()) {
            SPDLOG_TRACE("            GOT TD");
        }
    }
}

/// Create a new node for the given method decl and return it
NodePtr process_method_decl(
    const CXXMethodDecl* cmd, std::vector<std::string> attrs,
    const std::vector<std::vector<std::string>>& template_parameters,
    bool is_specialization = false) {
    const std::string method_name = cmd->getQualifiedNameAsString();
    const std::string method_short_name = cmd->getNameAsString();

    QType return_qtype;
    std::vector<Param> params;
    process_function_parameters(cmd, return_qtype, params, template_parameters);

    auto node_function = std::make_unique<NodeMethod>(
        method_name, 0, 0, std::move(attrs), method_short_name, return_qtype,
        std::move(params), cmd->isStatic(), std::vector<std::string>{});

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

    m->is_specialization = is_specialization;

    m->comment = get_comment(cmd);

    SPDLOG_DEBUG("Processed method {}", m->qualified_name);

    return node_function;
}

void process_methods(const CXXRecordDecl* crd,
                     std::vector<std::vector<std::string>> template_parameters,
                     bool is_base, std::vector<NodePtr>& result,
                     bool& has_public_ctor) {
    SPDLOG_TRACE("process_methods({})", get_record_name(crd));

    // get all the public base classes of this record, and process those methods
    SPDLOG_TRACE("class has {} bases", crd->getNumBases());
    for (const auto base : crd->bases()) {
        if (const CXXRecordDecl* base_crd =
                base.getType()->getAsCXXRecordDecl()) {
            SPDLOG_TRACE("found base {}", get_record_name(crd));
            bool _dummy;
            process_methods(base_crd, template_parameters, true, result,
                            _dummy);
        }
    }

    // FIXME: need to replace existing methods from the base class
    // for overrides
    for (const Decl* d : crd->decls()) {
        if (const NamedDecl* nd = dyn_cast<NamedDecl>(d)) {
            SPDLOG_TRACE(nd->getQualifiedNameAsString());
        }
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
            SPDLOG_TRACE("GOT FTD {}", ftd->getNameAsString());
            std::vector<std::vector<std::string>> template_parameters_stack;
            if (!template_parameters.empty()) {
                template_parameters_stack = template_parameters;
            }
            auto f_template_parameters = get_template_parameters(ftd);
            template_parameters_stack.push_back(f_template_parameters);

            const std::string function_name = ftd->getQualifiedNameAsString();
            const std::string method_short_name = ftd->getNameAsString();
            QType return_qtype;
            std::vector<Param> params;
            const auto* fd = ftd->getTemplatedDecl();
            process_function_parameters(fd, return_qtype, params,
                                        template_parameters_stack);

            std::vector<std::string> attrs{};
            auto node_function = std::make_unique<NodeMethod>(
                function_name, -1, -1, std::move(attrs), method_short_name,
                return_qtype, std::move(params), fd->isStatic(),
                f_template_parameters);
            const auto* cmd = dyn_cast<CXXMethodDecl>(fd);
            if (!cmd) {
                SPDLOG_ERROR("Failed to cast FTD to CMD");
            } else {
                node_function->is_const = cmd->isConst();
            }
            result.emplace_back(std::move(node_function));
        } else if (const auto* cmd = dyn_cast<CXXMethodDecl>(d)) {
            // just a regular boring old method
            // Skip ctor/dtor for base classes
            if ((dyn_cast<CXXConstructorDecl>(cmd) != 0 ||
                 dyn_cast<CXXDestructorDecl>(cmd) != 0) ||
                cmd->isCopyAssignmentOperator() ||
                cmd->isMoveAssignmentOperator()) {

                if (is_base)
                    continue;

                has_public_ctor = true;
            }

            std::vector<std::string> attrs{};
            auto node_function =
                process_method_decl(cmd, attrs, template_parameters);

            // if this method is on any of the bases, then we'll already
            // have declared it, so don't need to redeclare
            bool found = false;
            for (const auto& m : result) {
                const NodeMethod& a = *node_cast<NodeMethod>(m.get());
                const NodeMethod& b =
                    *node_cast<NodeMethod>(node_function.get());
                if (a == b) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                result.emplace_back(std::move(node_function));
            }
        }
    }
}

bool is_in_valid_context(const DeclContext* parent) {
    while (parent) {
        if (parent->isTranslationUnit()) {
            return true;
        }
        if (parent->isNamespace() || parent->isRecord() ||
            parent->isExternCContext()) {
            parent = parent->getParent();
        } else {
            return false;
        }
    }

    return false;
}

void process_tnd(const TypedefNameDecl* tnd) {
    ASTContext& ctx = tnd->getASTContext();
    SourceManager& sm = ctx.getSourceManager();
    const auto& loc = tnd->getLocation();
    std::string filename = sm.getFilename(loc).str();

    auto qualified_name = tnd->getQualifiedNameAsString();
    auto short_name = tnd->getNameAsString();
    SPDLOG_DEBUG("process {} at {}:{}", qualified_name, filename,
                 sm.getExpansionLineNumber(loc));

    if (!is_in_valid_context(tnd->getDeclContext())) {
        SPDLOG_DEBUG("{} is not in a valid context. skipping", qualified_name);
        return;
    }

    auto* node_tu = get_translation_unit(filename);
    node_tu->source_includes.push_back(filename);

    auto it = NODE_MAP.find(qualified_name);
    if (it == NODE_MAP.end()) {
        NodeId id = NODES.size();

        auto node_tnd = std::make_unique<NodeTypedefNameDecl>(
            qualified_name, id, 0, std::vector<std::string>{},
            std::move(short_name), std::vector<NodeId>{}, tnd->getUnderlyingType().getAsString());

        NODES.emplace_back(std::move(node_tnd));
        SPDLOG_TRACE("Inserting NodeTypedefNameDecl {} with id {}",
                     qualified_name, id);
        NODE_MAP[qualified_name] = id;

        auto namespaces = get_namespaces(id, tnd->getDeclContext(), node_tu);
        auto* node_rec = node_cast<NodeTypedefNameDecl>(NODES[id].get());
        node_rec->namespaces = std::move(namespaces);
    }
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

    if (!is_in_valid_context(crd->getParent())) {
        SPDLOG_DEBUG("{} is not in a valid context. skipping", qualified_name);
        return;
    }

    auto* node_tu = get_translation_unit(filename);
    node_tu->source_includes.push_back(filename);

    auto it = NODE_MAP.find(qualified_name);
    if (it == NODE_MAP.end()) {
        NodeId id = NODES.size();
        auto node_record = std::make_unique<NodeRecord>(
            qualified_name, id, 0, std::vector<std::string>{},
            std::move(short_name), std::vector<NodeId>{}, template_parameters);

        NODES.emplace_back(std::move(node_record));
        SPDLOG_TRACE("Inserting NodeRecord {} with id {}", qualified_name, id);
        NODE_MAP[qualified_name] = id;

        auto namespaces = get_namespaces(id, crd->getParent(), node_tu);
        auto* node_rec = node_cast<NodeRecord>(NODES[id].get());
        node_rec->namespaces = std::move(namespaces);

        node_rec->is_abstract = crd->isAbstract();

        node_rec->comment = get_comment(crd);

        std::vector<NodePtr> method_ptrs;
        std::vector<std::vector<std::string>> template_parameters_stack;
        if (!template_parameters.empty()) {
            template_parameters_stack.push_back(template_parameters);
        }
        process_methods(crd, template_parameters_stack, false, method_ptrs,
                        node_rec->has_public_ctor);

        node_rec->methods.reserve(method_ptrs.size());

        for (auto&& m : method_ptrs) {
            NodeId id = NODES.size();
            NODE_MAP[m->qualified_name] = id;
            NODES.emplace_back(std::move(m));
            node_rec->methods.push_back(id);
        }

        // fix up any record type references
        auto it_record_type = NODE_MAP.find("TYPE:" + qualified_name);
        if (it_record_type != NODE_MAP.end()) {
            auto* node_record_type =
                (NodeRecordType*)NODES.at(it_record_type->second).get();
            node_record_type->record = id;
        }
    } else {
        SPDLOG_DEBUG("{} at {}:{} already in node map", qualified_name,
                     filename, sm.getExpansionLineNumber(loc));
    }

    SPDLOG_DEBUG("Finished procesing {} at {}:{}", qualified_name, filename,
                 sm.getExpansionLineNumber(loc));
}

void handle_ctd(const ClassTemplateDecl* ctd) {
    ASTContext& ctx = ctd->getASTContext();
    SourceManager& sm = ctx.getSourceManager();
    const auto& loc = ctd->getLocation();
    std::string filename = sm.getFilename(loc).str();

    ctd = ctd->getCanonicalDecl();

    std::string qualified_name = ctd->getQualifiedNameAsString();

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
    ASTContext& ctx = ed->getASTContext();
    uint32_t size, align;
    if (!get_abi_info(dyn_cast<TypeDecl>(ed), ctx, size, align)) {
        SPDLOG_CRITICAL("Could not get ABI info for {}", enum_name);
    }

    std::vector<std::pair<std::string, std::string>> variants;
    for (const auto& ecd : ed->enumerators()) {
        SPDLOG_DEBUG("        {}", ecd->getNameAsString());
        variants.push_back(std::make_pair(ecd->getNameAsString(),
                                          std::to_string(ecd->getInitVal().getExtValue())));
    }

    NodeId new_id = NODES.size();
    auto node_enum = std::make_unique<NodeEnum>(
        enum_name, new_id, 0, std::vector<std::string>{},
        std::move(enum_short_name), std::vector<NodeId>{}, variants, size,
        align);
    auto* node_enum_ptr = node_enum.get();
    NODES.emplace_back(std::move(node_enum));
    NODE_MAP[enum_name] = new_id;

    const std::vector<NodeId> namespaces =
        get_namespaces(new_id, ed->getParent(), node_tu);
    node_enum_ptr->namespaces = namespaces;

    // Find any EnumType nodes that need the new id
    auto it_enum_type = NODE_MAP.find("TYPE:" + enum_name);
    if (it_enum_type != NODE_MAP.end()) {
        auto* node_enum_type =
            (NodeEnumType*)NODES.at(it_enum_type->second).get();
        node_enum_type->enm = new_id;
    }
}

void process_fd(const FunctionDecl* fd) {
    ASTContext& ctx = fd->getASTContext();
    SourceManager& sm = ctx.getSourceManager();
    const auto& loc = fd->getLocation();
    std::string filename = sm.getFilename(loc).str();

    // methods should be excluded by the matcher, but they don't seem to be
    if (dyn_cast<CXXMethodDecl>(fd)) {
        return;
    }

    if (filename == CURRENT_FILENAME) {
        auto qname = fd->getQualifiedNameAsString();
        auto short_name = fd->getNameAsString();
        auto* node_tu = get_translation_unit(filename);

        std::vector<std::string> template_parameters;
        if (const auto* ftd = fd->getDescribedFunctionTemplate()) {
            template_parameters = get_template_parameters(ftd);
        }

        cppmm::QType return_qtype;
        std::vector<cppmm::Param> params;
        cppmm::process_function_parameters(fd, return_qtype, params,
                                           {template_parameters});

        NodeId id = NODES.size();
        auto node_fn = std::make_unique<NodeFunction>(
            qname, id, 0, std::vector<std::string>{}, short_name, return_qtype,
            std::move(params), template_parameters);
        node_fn->comment = get_comment(fd);
        auto* node_fn_ptr = node_fn.get();
        NODES.emplace_back(std::move(node_fn));
        NODE_MAP[qname] = id;
        auto namespaces = get_namespaces(id, fd->getParent(), node_tu);
    }
}

} // namespace cppmm

class GenBindingCallback
    : public clang::ast_matchers::MatchFinder::MatchCallback {
public:
    virtual void
    run(const clang::ast_matchers::MatchFinder::MatchResult& result);
};

void GenBindingCallback::run(const MatchFinder::MatchResult& result) {
    if (const CXXRecordDecl* crd =
            result.Nodes.getNodeAs<CXXRecordDecl>("recordDecl")) {

        auto qname = crd->getQualifiedNameAsString();
        crd = cppmm::get_canonical_def_from_crd(crd);
        if (crd != nullptr) {
            ASTContext& ctx = crd->getASTContext();
            SourceManager& sm = ctx.getSourceManager();
            const auto& loc = crd->getLocation();
            std::string filename = sm.getFilename(loc).str();
            if (filename == cppmm::CURRENT_FILENAME) {
                SPDLOG_DEBUG("Got CRD {}", qname);
                std::vector<std::string> template_parameters;
                if (const auto* ctd = crd->getDescribedClassTemplate()) {
                    template_parameters = cppmm::get_template_parameters(ctd);
                    if (template_parameters.empty()) {
                        SPDLOG_WARN(
                            "Class template {} had no template parameters",
                            qname);
                    }
                }
                cppmm::process_crd(crd, template_parameters);
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
    } else if (const FunctionDecl* fd =
                   result.Nodes.getNodeAs<FunctionDecl>("functionDecl")) {
        cppmm::process_fd(fd);
    } else if (const EnumDecl* ed =
                   result.Nodes.getNodeAs<EnumDecl>("enumDecl")) {
        ASTContext& ctx = ed->getASTContext();
        SourceManager& sm = ctx.getSourceManager();
        const auto& loc = ed->getLocation();
        std::string filename = sm.getFilename(loc).str();

        if (filename == cppmm::CURRENT_FILENAME) {
            auto qname = ed->getQualifiedNameAsString();
            SPDLOG_DEBUG("Got enum {}", qname);
            cppmm::process_enum_decl(ed, filename);
        }

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
        if (filename == cppmm::CURRENT_FILENAME) {
            cppmm::handle_ctd(ctd);
        }
    } else if (const TypedefNameDecl* tnd =
                   result.Nodes.getNodeAs<TypedefNameDecl>("typedefNameDecl")) {
        ASTContext& ctx = tnd->getASTContext();
        SourceManager& sm = ctx.getSourceManager();
        const auto& loc = tnd->getLocation();
        std::string filename = sm.getFilename(loc).str();
        if (filename == cppmm::CURRENT_FILENAME) {
            SPDLOG_INFO("Got TND {}", tnd->getQualifiedNameAsString());
            cppmm::process_tnd(tnd);
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

    if (!cppmm::TARGET_NAMESPACE.empty()) {
        DeclarationMatcher record_decl_matcher =
            cxxRecordDecl(
                hasAncestor(namespaceDecl(hasName(cppmm::TARGET_NAMESPACE))),
                unless(isImplicit()))
                .bind("recordDecl");
        _match_finder.addMatcher(record_decl_matcher, &_handler);

        DeclarationMatcher ctd_matcher =
            classTemplateDecl(
                hasAncestor(namespaceDecl(hasName(cppmm::TARGET_NAMESPACE))),
                unless(isImplicit()))
                .bind("classTemplateDecl");
        _match_finder.addMatcher(ctd_matcher, &_handler);

        DeclarationMatcher enum_decl_matcher =
            enumDecl(
                hasAncestor(namespaceDecl(hasName(cppmm::TARGET_NAMESPACE))),
                unless(isImplicit()))
                .bind("enumDecl");
        _match_finder.addMatcher(enum_decl_matcher, &_handler);

        DeclarationMatcher function_decl_matcher =
            functionDecl(
                hasAncestor(namespaceDecl(hasName(cppmm::TARGET_NAMESPACE))),
                unless(anyOf(hasAncestor(recordDecl()),
                             hasAncestor(classTemplateDecl()))))
                .bind("functionDecl");
        _match_finder.addMatcher(function_decl_matcher, &_handler);

        DeclarationMatcher typedef_decl_matcher =
            typedefNameDecl(
                hasDeclContext(namedDecl(hasName(cppmm::TARGET_NAMESPACE))))
                .bind("typedefNameDecl");
        _match_finder.addMatcher(typedef_decl_matcher, &_handler);
    } else {

        DeclarationMatcher record_decl_matcher =
            cxxRecordDecl(unless(isImplicit())).bind("recordDecl");
        _match_finder.addMatcher(record_decl_matcher, &_handler);

        DeclarationMatcher ctd_matcher =
            classTemplateDecl(unless(isImplicit())).bind("classTemplateDecl");
        _match_finder.addMatcher(ctd_matcher, &_handler);

        DeclarationMatcher enum_decl_matcher =
            enumDecl(unless(isImplicit())).bind("enumDecl");
        _match_finder.addMatcher(enum_decl_matcher, &_handler);

        DeclarationMatcher function_decl_matcher =
            functionDecl(unless(anyOf(hasAncestor(recordDecl()),
                                      hasAncestor(classTemplateDecl()))))
                .bind("functionDecl");
        _match_finder.addMatcher(function_decl_matcher, &_handler);

        DeclarationMatcher typedef_decl_matcher =
            typedefNameDecl().bind("typedefNameDecl");
        _match_finder.addMatcher(typedef_decl_matcher, &_handler);
    }

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
}

std::vector<std::string> parse_project_includes(int argc, const char** argv) {
    std::vector<std::string> result;
    for (int i = 0; i < argc; ++i) {
        std::string a(argv[i]);
        if (a.find("-I") == 0) {
            result.push_back(a.substr(2, std::string::npos));
        }
    }
    return result;
}

// https://gist.github.com/rodamber/2558e25d4d8f6b9f2ffdf7bd49471340
// FIXME: Handle multiple uppers by inserting an underscore before the last
// upper. So IMFVersion becomes imf_version not imfversion
std::string to_snake_case(std::string camel_case) {
    std::string str(1, tolower(camel_case[0]));

    // First place underscores between contiguous lower and upper case letters.
    // For example, `_LowerCamelCase` becomes `_Lower_Camel_Case`.
    for (auto it = camel_case.begin() + 1; it != camel_case.end(); ++it) {
        if (isupper(*it) && *(it - 1) != '_' && islower(*(it - 1))) {
            str += "_";
        }
        str += *it;
    }

    // Then convert it to lower case.
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);

    return str;
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

static cl::opt<std::string> opt_relative_to(
    "r", cl::desc("Path to which the target headers are relative, and from "
                  "which the hierarchy will be preserved in the bindings"));

static cl::list<std::string>
    opt_rename_namespace("n", cl::desc("Rename namespace <to>=<from>"));
static cl::opt<std::string> opt_rust_sys_directory(
    "rust-sys",
    cl::desc("Directory under which rust-sys project will be written"));

static cl::list<std::string>
    opt_includes("i", cl::desc("Extra includes for the project"));
static cl::list<std::string>
    opt_libraries("l", cl::desc("Libraries to link against"));

static cl::opt<std::string>
    opt_namespace("namespace",
                  cl::desc("Target namespace containing stuff to bind"));

static cl::opt<std::string> opt_namespace_internal(
    "namespace-internal",
    cl::desc("Target library's internal macro for the namespace"));

static cl::opt<std::string> opt_namespace_public(
    "namespace-public",
    cl::desc("Target library's public macro for the namespace"));

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
    argv[i++] = "/CPPMM_VIRTUAL_INCLUDES";

    project_includes = parse_project_includes(argc, argv);

    ExitOnError eoe;
    CommonOptionsParser OptionsParser = eoe(CommonOptionsParser::create(argc, argv, CppmmCategory));

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

    if (src_path.size() != 1) {
        SPDLOG_CRITICAL("Expected 1 header file to parse, got {}",
                        src_path.size());
        return 1;
    }

    if (!fs::is_regular_file(src_path[0])) {
        SPDLOG_CRITICAL("Header path \"{}\" is not a regular file",
                        src_path[0]);
        return 1;
    }

    std::vector<std::string> header_paths;
    std::vector<std::string> vtu;
    std::vector<std::string> vtu_paths;

    cppmm::TARGET_NAMESPACE = opt_namespace;
    cppmm::TARGET_NAMESPACE_INTERNAL = opt_namespace_internal;
    cppmm::TARGET_NAMESPACE_PUBLIC = opt_namespace_public;

    auto header_path = ps::os::path::abspath(src_path[0], cwd);
    header_paths.push_back(header_path);
    SPDLOG_DEBUG("Found header file {}", header_path);
    vtu.push_back(fmt::format("#include \"{}\"", header_path));
    vtu_paths.push_back(
        fmt::format("/tmp/{}.cpp", fs::path(header_path).stem().string()));

    auto& compdb = OptionsParser.getCompilations();

    std::string output_dir = cwd;
    if (opt_output_directory != "") {
        output_dir = opt_output_directory;
    }

    std::string relative_dir = "";
    if (opt_relative_to != "") {
        relative_dir = opt_relative_to;
    }

    if (!fs::exists(output_dir) && !fs::create_directories(output_dir)) {
        SPDLOG_ERROR("Could not create output directory '{}'", output_dir);
        return -2;
    }

    // Expose the clang headers (e.g. stddef.h) as virtual headers. These are
    // compiled into the binary as base64 using the source files generated by
    // the bake_resources.py script.
    std::vector<std::string> decoded_headers;
    decoded_headers.reserve(num_files());
    std::vector<std::string> virtual_filenames;
    virtual_filenames.reserve(num_files());

    for (int i = 0; i < num_files(); ++i) {
        virtual_filenames.push_back(std::string("/CPPMM_VIRTUAL_INCLUDES/") +
                                    cppmm_resource_filename(i));
        decoded_headers.push_back(base64::decode(cppmm_resource_array(i)));
    }

    for (int i = 0; i < vtu.size(); ++i) {
        SPDLOG_INFO("Processing {} ({}/{})", header_paths[i], i + 1,
                    vtu.size());
        cppmm::CURRENT_FILENAME = header_paths[i];
        ClangTool Tool(compdb, ArrayRef<std::string>(vtu_paths[i]));
        Tool.mapVirtualFile(vtu_paths[i], vtu[i]);

        for (int i = 0; i < num_files(); ++i) {
            Tool.mapVirtualFile(virtual_filenames[i], decoded_headers[i]);
        }

        auto process_binding_action =
            newFrontendActionFactory<GenBindingAction>();
        int result = Tool.run(process_binding_action.get());
    }

    using namespace cppmm;
    SPDLOG_DEBUG("output path is {}", output_dir);
    if (ROOT.empty()) {
        SPDLOG_WARN("Header {} generated no bindings", header_path);
    } else {
        for (const NodeId id : ROOT) {
            auto* node_tu = node_cast<NodeTranslationUnit>(NODES[id].get());
            std::string relative_header = node_tu->qualified_name;
            // generate relative header path by matching against provided
            // include paths and stripping any match from the front.
            node_tu->source_includes.push_back(relative_header);
            for (const auto& p : project_includes) {
                if (ps::find(node_tu->qualified_name, p) == 0) {
                    // we have a match
                    relative_header =
                        ps::lstrip(ps::replace(relative_header, p, ""), "/");
                    node_tu->source_includes[0] = relative_header;
                    break;
                }
            }

            // generate output filename by snake_casing the header filename
            auto filename = to_snake_case(
                fs::path(relative_header).replace_extension(".cpp").string());

            auto output_path = output_dir / fs::path(filename);
            SPDLOG_INFO("Writing {}", output_path.string());
            fs::create_directories(output_path.parent_path());
            std::ofstream of;
            of.open(output_path);
            // write output file
            node_tu->write(of, 0);
            of.close();
        }
    }

    for (const auto& n : NODES) {
        if (n->node_kind() == NodeKind::Record) {
            const auto* node_rec = node_cast<NodeRecord>(n.get());
            SPDLOG_DEBUG("NodeRecord {}", node_rec->qualified_name);
        } else if (n->node_kind() == NodeKind::RecordType) {
            const auto* node_rec = node_cast<NodeRecordType>(n.get());
            SPDLOG_DEBUG("NodeRecordType {}", node_rec->qualified_name);
        }
    }

    // return result;
}
