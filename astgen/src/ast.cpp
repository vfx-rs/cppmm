#include "ast.hpp"

#include <iomanip>

#define SPDLOG_ACTIVE_LEVEL TRACE
#include <spdlog/fmt/fmt.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>

#include "filesystem.hpp"
namespace fs = ghc::filesystem;

#include "pystring.h"

namespace cppmm {

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
    case NodeKind::FunctionPointerTypedef:
        os << "FunctionPointerTypedef";
        break;
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
/// Namespace aliases
std::unordered_map<std::string, std::pair<std::string, bool>> NAMESPACE_ALIASES;
/// Function prototype typedefs
std::unordered_map<std::string, std::string> FPT_TYPEDEFS;

void Node::write_json_attrs(json& o) const {
    if (id >= 0) {
        o["id"] = id;
    } else {
        o["id"] = nullptr;
    }
}

void NodeTranslationUnit::write_json(json& o) const {
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

void NodeNamespace::write_json_attrs(json& o) const {
    Node::write_json_attrs(o);
    o["short_name"] = short_name;
    if (alias.empty()) {
        o["alias"] = short_name;
    } else {
        o["alias"] = alias;
    }
    o["collapse"] = collapse;
}

void NodeNamespace::write_json(json& o) const {
    o["kind"] = "Namespace";
    o["name"] = qualified_name;
    write_json_attrs(o);
}

void NodeType::write_json_attrs(json& o) const {
    Node::write_json_attrs(o);
    o["type"] = type_name;
}

void NodeBuiltinType::write_json(json& o) const {
    o["kind"] = "BuiltinType";
    write_json_attrs(o);
}

void QType::write_json(json& o) const {
    if (ty >= 0) {
        NODES.at(ty)->write_json(o);
    } else {
        o["type"] = "UNKNOWN";
    }
    o["const"] = is_const;
}

std::ostream& operator<<(std::ostream& os, const QType& q) {
    if (q.is_const) {
        os << "const ";
    }
    os << ((NodeType*)NODES.at(q.ty).get())->type_name;
    return os;
}

void NodePointerType::write_json(json& o) const {
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

void NodeConstantArrayType::write_json(json& o) const {
    o["kind"] = "ConstantArrayType";
    write_json_attrs(o);

    o["size"] = size;
    o["element_type"] = {};
    element_type.write_json(o["element_type"]);
}

void NodeRecordType::write_json_attrs(json& o) const {
    NodeType::write_json_attrs(o);
    o["record"] = record;
}

void NodeRecordType::write_json(json& o) const {
    o["kind"] = "RecordType";
    write_json_attrs(o);
}

void NodeEnumType::write_json_attrs(json& o) const {
    NodeType::write_json_attrs(o);
    o["enum"] = enm;
}

void NodeEnumType::write_json(json& o) const {
    o["kind"] = "EnumType";
    write_json_attrs(o);
}

void NodeFunctionProtoType::write_json_attrs(json& o) const {
    NodeType::write_json_attrs(o);
}

void NodeFunctionProtoType::write_json(json& o) const {
    o["kind"] = "FunctionProtoType";

    write_json_attrs(o);

    o["return"] = {};
    return_type.write_json(o["return"]);

    o["params"] = {};
    int index = 0;
    for (const auto& param : params) {
        auto p = json::object();
        p["type"] = json::object();
        p["name"] = "";
        p["index"] = index++;
        param.write_json(p["type"]);
        o["params"].emplace_back(p);
    }

    o["function_pointer_typedef"] = function_pointer_typedef;
}

std::ostream& operator<<(std::ostream& os, const Param& p) {
    return os << p.qty << " " << p.name;
}

void NodeAttributeHolder::write_attrs_json(json& o) const {
    o["attributes"] = {};
    for (const auto& a : attrs) {
        o["attributes"].emplace_back(a);
    }
    o["comment"] = comment;
}

void NodeVar::write_json_attrs(json& o) const {
    NodeAttributeHolder::write_json_attrs(o);
}

void NodeVar::write_json(json& o) const {
    o["kind"] = "Var";
    o["qualified_name"] = qualified_name;
    o["short_name"] = short_name;
    o["type"] = {};
    qtype.write_json(o["type"]);
    write_json_attrs(o);
    write_attrs_json(o);
}

void Exception::write_json(json& o) const {
    o["cpp_name"] = cpp_name;
    o["c_name"] = c_name;
    o["error_code"] = error_code;
}

void NodeFunction::write_json_attrs(json& o) const {
    NodeAttributeHolder::write_json_attrs(o);
    o["short_name"] = short_name;
    o["qualified_name"] = qualified_name;
    o["in_binding"] = in_binding;
    o["in_library"] = in_library;
    o["noexcept"] = is_noexcept;
}

void NodeFunction::write_parameters_json(json& o) const {
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

    o["template_args"] = {};
    int i = 0;
    for (const auto& a : template_args) {
        auto p = json::object();
        p["index"] = i;
        p["type"] = json::object();
        a.write_json(p["type"]);
        o["template_args"].push_back(p);
        i++;
    }
}

void NodeFunction::write_json(json& o) const {
    o["kind"] = "Function";
    write_json_attrs(o);
    write_attrs_json(o);
    o["namespaces"] = namespaces;
    write_parameters_json(o);

    o["exceptions"] = {};
    for (const auto& ex : exceptions) {
        auto e = json::object();
        ex.write_json(e);
        o["exceptions"].push_back(e);
    }
}

std::ostream& operator<<(std::ostream& os, const NodeFunction& f) {
    os << f.qualified_name << "(";
    for (const Param& p : f.params) {
        os << p << ", ";
    }
    os << ") -> " << f.return_type;
    return os;
}

void NodeMethod::write_json_attrs(json& o) const {
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

void NodeMethod::write_json(json& o) const {
    o["kind"] = "Method";
    write_json_attrs(o);
    write_attrs_json(o);
    write_parameters_json(o);
    o["exceptions"] = {};
    for (const auto& ex : exceptions) {
        auto e = json::object();
        ex.write_json(e);
        o["exceptions"].push_back(e);
    }
}

std::ostream& operator<<(std::ostream& os, const NodeMethod& f) {
    if (f.is_static) {
        os << "static ";
    }
    if (f.is_virtual) {
        os << "virtual ";
    }

    std::vector<std::string> params;
    for (const Param& p : f.params) {
        params.push_back(fmt::format("{}", p));
    }

    os << f.return_type << " " << f.qualified_name << "("
       << pystring::join(", ", params) << ")";

    if (f.is_const) {
        os << " const";
    }
    os << " [[";
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

void NodeRecord::write_json_attrs(json& o) const {
    NodeAttributeHolder::write_json_attrs(o);
    o["abstract"] = is_abstract;
    o["trivially_copyable"] = is_trivially_copyable;
    o["trivially_movable"] = is_trivially_movable;
    o["opaque_type"] = is_opaque_type;
    o["size"] = size;
    o["align"] = align;
    if (!alias.empty()) {
        o["alias"] = alias;
    } else {
        o["alias"] = short_name;
    }
}

void NodeRecord::write_json(json& o) const {
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

void NodeEnum::write_json_attrs(json& o) const {
    NodeAttributeHolder::write_json_attrs(o);
    o["size"] = size;
    o["align"] = align;
}

void NodeEnum::write_json(json& o) const {
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

void NodeFunctionPointerTypedef::write_json_attrs(json& o) const {
    NodeAttributeHolder::write_json_attrs(o);
}

void NodeFunctionPointerTypedef::write_json(json& o) const {
    o["kind"] = "FunctionPointerTypedef";
    o["name"] = qualified_name;
    o["alias"] = alias;
    o["namespaces"] = namespaces;

    o["return"] = {};
    return_type.write_json(o["return"]);

    o["params"] = {};
    int index = 0;
    for (const auto& param : params) {
        auto p = json::object();
        p["type"] = json::object();
        p["name"] = "";
        p["index"] = index++;
        param.write_json(p["type"]);
        o["params"].emplace_back(p);
    }

    write_json_attrs(o);
    write_attrs_json(o);
}

/// Write out the AST to json output files. Each NodeTranslationUnit which
/// is a child of the ROOT is written to its own json file and all decls in
/// that TU are written recursively
void write_tus(std::string output_dir, const std::string& src_path) {
    for (const auto& id : ROOT) {
        NodeTranslationUnit* tu = (NodeTranslationUnit*)NODES.at(id).get();
        SPDLOG_DEBUG("Writing TU {}", tu->qualified_name);
        auto tu_path = fs::path(tu->qualified_name);
        auto prox = fs::proximate(tu_path, src_path);
        SPDLOG_DEBUG("prox: {}", prox.string());
        // auto stem = tu_path.stem();
        // auto parent = tu_path.parent_path();
        // auto out_path = output_dir / stem;
        auto out_path = output_dir / prox;
        // replace TU path with proximate path
        tu->qualified_name = prox;
        out_path.replace_extension(".json");
        SPDLOG_DEBUG("out_path: {}", out_path);
        fs::create_directories(out_path.parent_path());
        std::ofstream os;
        os.open(out_path.string(), std::ios::out | std::ios::trunc);
        auto j = json::object();
        tu->write_json(j);
        os << std::setw(4) << j;
    }
}

std::unordered_map<std::string, std::vector<std::string>> SOURCE_INCLUDES;
std::vector<std::string> PROJECT_INCLUDES;
/// Parse the include statements from the given C++ file
std::vector<std::string> get_source_includes(std::string filename) {
    auto it = SOURCE_INCLUDES.find(filename);
    if (it != SOURCE_INCLUDES.end()) {
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
        filename, id, 0, get_source_includes(filename), PROJECT_INCLUDES);
    ROOT.push_back(id);
    auto* node_ptr = node.get();
    NODES.emplace_back(std::move(node));
    NODE_MAP[filename] = id;
    return node_ptr;
}

} // namespace cppmm
