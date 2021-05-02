//------------------------------------------------------------------------------
// vfx-rs
//------------------------------------------------------------------------------
#include "cppmm_ast_add_c.hpp"
#include "cppmm_ast.hpp"
#include "pystring.h"
#include <iostream>
#include <unordered_map>

#include <cstdlib> // for exit function

#define SPDLOG_ACTIVE_LEVEL TRACE

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#define panic(...)                                                             \
    {                                                                          \
        SPDLOG_CRITICAL(__VA_ARGS__);                                          \
        abort();                                                               \
    }

#define expect(CONDITION, ...)                                                 \
    if (!(CONDITION)) {                                                        \
        SPDLOG_CRITICAL(__VA_ARGS__);                                          \
        abort();                                                               \
    }

namespace cppmm {
namespace transform {

static const char* THIS_ = "this_";

//------------------------------------------------------------------------------
// TypeRegistry
//------------------------------------------------------------------------------
class TypeRegistry {
    struct Records {
        NodePtr m_cpp;
        NodePtr m_c;
    };

    // The node entries are sparse, so store them in a map for the moment.
    using Mapping = std::unordered_map<NodeId, Records>;
    using Namespaces = std::unordered_map<NodeId, std::string>;
    using NamespaceAliases =
        std::unordered_map<NodeId, std::pair<std::string, bool>>;
    using SymbolCounts = std::unordered_map<std::string, size_t>;

    Mapping m_mapping;
    Namespaces m_namespaces;
    NamespaceAliases m_namespace_aliases;
    SymbolCounts m_symbol_counts;

public:
    void add(NodeId id, NodePtr cpp, NodePtr c) {
        // TODO LT: Assert for double entries
        // TODO LT: Assert for RecordKind/EnumKind in cpp and c
        m_mapping.insert(
            std::make_pair(id, Records{std::move(cpp), std::move(c)}));
    }

    void add_namespace(NodeId id, const std::string& ns) {
        // TODO LT: Assert for double entries
        m_namespaces[id] = ns;
    }

    void add_namespace_alias(NodeId id, const std::string& ns, bool collapse) {
        // TODO LT: Assert for double entries
        m_namespace_aliases[id] = std::make_pair(ns, collapse);
    }

    const char* find_namespace(NodeId id) const {
        auto result = m_namespaces.find(id);
        if (result == m_namespaces.end()) {
            SPDLOG_ERROR("Could not find namespace for id {}", id);
            return ""; // TODO LT: optional return with error would be better
        } else {
            return result->second.c_str();
        }
    }

    std::pair<std::string, bool> find_namespace_alias(NodeId id) const {
        auto result = m_namespace_aliases.find(id);
        if (result == m_namespace_aliases.end()) {
            SPDLOG_ERROR("Could not find namespace for id {}", id);
            return std::make_pair("", false);
        } else {
            return result->second;
        }
    }

    NodeRecord& edit_c(NodeId id) {
        auto& node =
            m_mapping[id].m_c; // TODO LT: Check existance + return optional
        // TODO LT: Assert kind is record

        return static_cast<NodeRecord&>(*node);
    }

    NodePtr find_enum_c(NodeId id) const {
        auto entry = m_mapping.find(id);

        if (entry == m_mapping.end()) {
            return NodePtr(); // TODO LT: Turn this into optional
        } else {
            expect(entry->second.m_cpp->kind == NodeKind::Enum,
                   "Incorrect return type ({}) for find_enum_c",
                   entry->second.m_cpp->kind);
            return entry->second.m_c;
        }
    }

    NodePtr find_record_c(NodeId id) const {
        auto entry = m_mapping.find(id);

        if (entry == m_mapping.end()) {
            return NodePtr(); // TODO LT: Turn this into optional
        } else {
            expect(entry->second.m_cpp->kind == NodeKind::Record,
                   "Incorrect return type ({}) for find_record_c",
                   entry->second.m_cpp->kind);
            return entry->second.m_c;
        }
    }

    NodePtr find_function_pointer_typedef_c(NodeId id) const {
        auto entry = m_mapping.find(id);

        if (entry == m_mapping.end()) {
            return NodePtr(); // TODO LT: Turn this into optional
        } else {
            expect(entry->second.m_cpp->kind ==
                       NodeKind::FunctionPointerTypedef,
                   "Incorrect return type ({}) for find_record_c",
                   entry->second.m_cpp->kind);
            return entry->second.m_c;
        }
    }

    std::string make_symbol_unique(const std::string& symbol) {
        auto item = m_symbol_counts.find(symbol);
        if (item == m_symbol_counts.end()) {
            // First time
            m_symbol_counts.insert(std::make_pair(symbol, 0));
            return symbol;
        } else {
            // Other times
            std::string result = symbol;
            result += "_";
            result += std::to_string(++item->second);
            return result;
        }
    }
};

//------------------------------------------------------------------------------
namespace generate {

const NodeId PLACEHOLDER_ID = 0;
const char* IGNORE = "cppmm|ignore";

//------------------------------------------------------------------------------
std::tuple<std::string, std::string, std::string>
compute_c_filepath(const std::string& outdir, const std::string& cpp_filepath) {
    std::string root;
    std::string _ext;
    pystring::os::path::splitext(root, _ext,
                                 pystring::os::path::basename(cpp_filepath));

    const auto abs_root = pystring::os::path::join(outdir, root);

    return {
        root + ".h",
        abs_root + ".cpp",
        root + "_private.h",
    };
}

//------------------------------------------------------------------------------
std::string remap_special_methods(const std::string& name) {
    if (name.empty()) {
        return "";
    }

    // Destructor
    if (name[0] == '~') {
        return std::string("dtor");
    }

    // Operators
    if (name == "operator=") {
        return std::string("_assign");
    }
    if (name == "operator==") {
        return std::string("_eq");
    }
    if (name == "operator!=") {
        return std::string("_ne");
    }
    if (name == "operator++") {
        return std::string("_op_inc");
    }
    if (name == "operator--") {
        return std::string("_op_dec");
    }
    if (name == "operator+") {
        return std::string("_op_add");
    }
    if (name == "operator-") {
        return std::string("_op_sub");
    }
    if (name == "operator/") {
        return std::string("_op_div");
    }
    if (name == "operator*") {
        return std::string("_op_mul");
    }
    if (name == "operator^") {
        return std::string("_op_xor");
    }
    if (name == "operator%") {
        return std::string("_op_mod");
    }
    if (name == "operator[]") {
        return std::string("_index");
    }
    if (name == "operator+=") {
        return std::string("_op_iadd");
    }
    if (name == "operator-=") {
        return std::string("_op_isub");
    }
    if (name == "operator/=") {
        return std::string("_op_idiv");
    }
    if (name == "operator*=") {
        return std::string("_op_imul");
    }
    if (name == "operator%=") {
        return std::string("_op_imod");
    }
    if (name == "operator^=") {
        return std::string("_op_ixor");
    }
    if (name == "operator()") {
        return std::string("_op_call");
    }

    // Just use the input name
    return name;
}

//------------------------------------------------------------------------------
std::string compute_c_name(const std::string& name) {
    std::string result;
    for (auto const& c : remap_special_methods(name)) {
        switch (c) {
        case ':':
        case ',':
        case '*':
        case '<':
        case '>':
        case '-':
            result.push_back('_');
            break;
        case ' ':
            break;
        default:
            result.push_back(c);
        }
    }
    return result;
}

//------------------------------------------------------------------------------
std::string compute_qualified_name(const TypeRegistry& type_registry,
                                   const std::vector<NodeId>& namespaces,
                                   const std::string& alias) {
    std::string result;
    for (const auto& ns : namespaces) {
        result += type_registry.find_namespace(ns);
        result += "_";
    }

    result += alias;

    result = pystring::replace(result, "-", "neg");

    return result;
}

//------------------------------------------------------------------------------
std::string compute_qualified_nice_name(const TypeRegistry& type_registry,
                                        const std::vector<NodeId>& namespaces,
                                        const std::string& alias) {
    std::string result;
    for (const auto& ns : namespaces) {
        auto p = type_registry.find_namespace_alias(ns);
        if (p.second) {
            // we want to collapse the head of the namespace path
            // into this single alias
            result = p.first + "_";
        } else {
            result += p.first;
            result += "_";
        }
    }

    result += alias;

    result = pystring::replace(result, "-", "neg");

    return result;
}

NodeTypePtr convert_type(TranslationUnit& c_tu, TypeRegistry& type_registry,
                         const NodeTypePtr& t, bool in_reference);

//------------------------------------------------------------------------------
NodeTypePtr convert_builtin_type(TranslationUnit& c_tu,
                                 TypeRegistry& type_registry,
                                 const NodeTypePtr& t, bool _in_refererence) {
    // TODO LT: Do mapping of c++ builtins to c builtins
    if (t->type_name == "_Bool") {
        c_tu.header_includes.insert("#include <stdbool.h>");
    }

    // For now just copy everything one to one.
    return NodeBuiltinType::n(t->name, 0, t->type_name, t->const_);
}

//------------------------------------------------------------------------------
std::string build_enum_to_cpp_name(const TypeRegistry& type_registry,
                                   const NodeTypePtr& t, const char* suffix) {
    expect(suffix[0] != '\0', "Suffix must not be empty");

    const auto& cpp_enum_type = *static_cast<const NodeEnumType*>(t.get());
    const auto& node_ptr = type_registry.find_enum_c(cpp_enum_type.enm);
    if (!node_ptr) {
        SPDLOG_ERROR("Found unsupported type: {}", t->type_name);
        return std::string();
    }

    std::string result = node_ptr->name;
    result += "_";
    result += suffix;

    return result;
}

//------------------------------------------------------------------------------
void add_record_declaration(TranslationUnit& c_tu, const NodePtr& node_ptr,
                            bool in_reference) {
    const auto& record = *static_cast<const NodeRecord*>(node_ptr.get());
    if (auto r_tu = record.tu.lock()) {
        if (r_tu.get() != &c_tu) {
            if (in_reference) // Forward declaration
            {
                c_tu.forward_decls.insert(node_ptr);
            } else // Header file
            {
                c_tu.header_includes.insert(r_tu->header_filename);
            }
            c_tu.source_includes.insert(r_tu->private_header_filename);
        }
    }
}

//------------------------------------------------------------------------------
void add_enum_declaration(TranslationUnit& c_tu, const NodePtr& node_ptr,
                          bool in_reference) {
    const auto& enum_ = *static_cast<const NodeTypedef*>(node_ptr.get());
    if (auto e_tu = enum_.tu.lock()) {
        if (e_tu.get() != &c_tu) {
            c_tu.header_includes.insert(e_tu->header_filename);
            c_tu.source_includes.insert(e_tu->private_header_filename);
        }
    }
}

//------------------------------------------------------------------------------
void add_function_pointer_typedef_declaration(TranslationUnit& c_tu,
                                              const NodePtr& node_ptr,
                                              bool in_reference) {
    const auto& fpt =
        *static_cast<const NodeFunctionPointerTypedef*>(node_ptr.get());
    if (auto e_tu = fpt.tu.lock()) {
        if (e_tu.get() != &c_tu) {
            c_tu.header_includes.insert(e_tu->header_filename);
            c_tu.source_includes.insert(e_tu->private_header_filename);
        }
    }
}

//------------------------------------------------------------------------------
NodeTypePtr convert_record_type(TranslationUnit& c_tu,
                                TypeRegistry& type_registry,
                                const NodeTypePtr& t, bool in_reference) {
    const auto& cpp_record_type = *static_cast<const NodeRecordType*>(t.get());

    const auto& node_ptr = type_registry.find_record_c(cpp_record_type.record);
    if (!node_ptr) {
        SPDLOG_ERROR("Found unsupported type: {}", t->type_name);
        return NodeTypePtr();
    }

    // Add the header file or forward declaration needed for this type
    // to be available.
    add_record_declaration(c_tu, node_ptr, in_reference);

    const auto& record = *static_cast<const NodeRecord*>(node_ptr.get());

    auto nrt =
        NodeRecordType::n(t->name, 0, record.nice_name, record.id, t->const_);
    return nrt;
}

//------------------------------------------------------------------------------
NodeTypePtr convert_enum_type(TranslationUnit& c_tu,
                              TypeRegistry& type_registry, const NodeTypePtr& t,
                              bool in_reference) {
    const auto& cpp_enum_type = *static_cast<const NodeEnumType*>(t.get());

    const auto& node_ptr = type_registry.find_enum_c(cpp_enum_type.enm);
    if (!node_ptr) {
        SPDLOG_ERROR("Found unsupported type: {}", t->type_name);
        return NodeTypePtr();
    }

    // Add the header file or forward declaration needed for this type
    // to be available.
    add_enum_declaration(c_tu, node_ptr, in_reference);

    const auto& enum_ = *static_cast<const NodeTypedef*>(node_ptr.get());

    return NodeRecordType::n(t->name, 0, enum_.name, enum_.id, t->const_);
}

//------------------------------------------------------------------------------
NodeTypePtr convert_array_type(TranslationUnit& c_tu,
                               TypeRegistry& type_registry,
                               const NodeTypePtr& t, bool in_reference) {
    auto a = static_cast<const NodeArrayType*>(t.get());

    auto element_type =
        convert_type(c_tu, type_registry, a->element_type, in_reference);

    // If we can't convert, then dont bother with this type either
    if (!element_type) {
        return NodeTypePtr();
    }

    return NodeArrayType::n("", 0, "", std::move(element_type), a->size,
                            a->const_);
}

//------------------------------------------------------------------------------
NodeTypePtr convert_pointer_type(TranslationUnit& c_tu,
                                 TypeRegistry& type_registry,
                                 const NodeTypePtr& t, bool in_reference) {
    auto p = static_cast<const NodePointerType*>(t.get());

    auto pointee_type =
        convert_type(c_tu, type_registry, p->pointee_type, true);

    // If we can't convert, then dont bother with this type either
    if (!pointee_type) {
        return NodeTypePtr();
    }

    // For now just copy everything one to one.
    return NodePointerType::n(PointerKind::Pointer, std::move(pointee_type),
                              p->const_);
}

//------------------------------------------------------------------------------
NodeTypePtr convert_function_proto_type(TranslationUnit& c_tu,
                                        TypeRegistry& type_registry,
                                        const NodeTypePtr& t,
                                        bool in_reference) {
    auto fpt = static_cast<const NodeFunctionProtoType*>(t.get());

    const auto& node_ptr = type_registry.find_function_pointer_typedef_c(
        fpt->function_pointer_typedef);
    if (!node_ptr) {
        SPDLOG_ERROR("Found unsupported type \"{}\" for id {}", t->type_name,
                     fpt->function_pointer_typedef);
        return NodeTypePtr();
    }

    // Add the header file or forward declaration needed for this type
    // to be available.
    add_function_pointer_typedef_declaration(c_tu, node_ptr, in_reference);

    const auto* c_fpt =
        static_cast<const NodeFunctionPointerTypedef*>(node_ptr.get());
    SPDLOG_TRACE("GOT C FPT {}", c_fpt->name);

    auto return_type =
        convert_type(c_tu, type_registry, fpt->return_type, false);

    std::vector<NodeTypePtr> params;
    for (const auto& p : fpt->params) {
        params.push_back(convert_type(c_tu, type_registry, p, false));
    }

    return NodeFunctionProtoType::n(return_type, std::move(params),
                                    c_fpt->nice_name, c_fpt->id);
}

//------------------------------------------------------------------------------
NodeTypePtr convert_type(TranslationUnit& c_tu, TypeRegistry& type_registry,
                         const NodeTypePtr& t, bool in_reference = false) {
    if (t->kind == NodeKind::PointerType) {
        const NodePointerType* p = static_cast<const NodePointerType*>(t.get());
        if (p->pointee_type->kind == NodeKind::FunctionProtoType) {
            // Function pointers come out in the AST as a pointer to a function
            // prototype. We actually want to pass them around as value types
            // (via a typedef) so intercept it here.
            return convert_function_proto_type(c_tu, type_registry,
                                               p->pointee_type, false);
        } else if (p->pointer_kind == PointerKind::Reference &&
                   p->pointee_type->kind == NodeKind::ArrayType) {
            // Array references want to desugar to just passing arrays around
            // "by value"
            return convert_array_type(c_tu, type_registry, p->pointee_type,
                                      false);
        }
    }

    switch (t->kind) {
    case NodeKind::BuiltinType:
        return convert_builtin_type(c_tu, type_registry, t, in_reference);
    case NodeKind::RecordType:
        return convert_record_type(c_tu, type_registry, t, in_reference);
    case NodeKind::PointerType:
        return convert_pointer_type(c_tu, type_registry, t, in_reference);
    case NodeKind::EnumType:
        return convert_enum_type(c_tu, type_registry, t, in_reference);
    case NodeKind::ArrayType:
        return convert_array_type(c_tu, type_registry, t, in_reference);
    case NodeKind::FunctionProtoType:
        return convert_function_proto_type(c_tu, type_registry, t,
                                           in_reference);
    default:
        break;
    }

    panic("convert_type: got unsupported kind {}",
          t->kind); // TODO LT: Clean this up
}

//------------------------------------------------------------------------------
bool parameter(TranslationUnit& c_tu, TypeRegistry& type_registry,
               std::vector<Param>& params, const Param& param) {
    auto param_type = convert_type(c_tu, type_registry, param.type);
    if (!param_type) {
        return false;
    }

    params.push_back(
        Param(std::string(param.name), std::move(param_type), params.size()));

    return true;
}

//------------------------------------------------------------------------------
void opaquebytes_record(NodeRecord& c_record) {
    constexpr auto sizeof_byte = 8;
    const auto size_in_bytes = c_record.size / sizeof_byte;

    auto is_const = false;
    auto array_type = std::make_unique<NodeArrayType>(
        "", PLACEHOLDER_ID, "",
        std::make_unique<NodeBuiltinType>("", PLACEHOLDER_ID, "char", is_const),
        size_in_bytes, is_const);

    c_record.force_alignment = true;
    c_record.fields.push_back(Field{"data", std::move(array_type)});
}

//------------------------------------------------------------------------------
void opaqueptr_record(NodeRecord& c_record) {
    auto unused = NodeBuiltinType::n("char", 0, "char", false);

    c_record.fields.push_back(Field{"_unused", std::move(data)});
}

//------------------------------------------------------------------------------
Param this_param(const NodeRecord& c_record, bool const_) {

    auto record =
        NodeRecordType::n("", 0, c_record.nice_name, c_record.id, const_);

    auto pointer = NodePointerType::n(
        PointerKind::Pointer, std::move(record),
        false // TODO LT: Maybe references should be const pointers
    );

    return Param(THIS_, std::move(pointer), 0);
}

//------------------------------------------------------------------------------
NodeExprPtr this_reference(const NodeRecord& cpp_record, bool const_) {
    return NodeFunctionCallExpr::n(
        "to_cpp", std::vector<NodeExprPtr>({NodeVarRefExpr::n(THIS_)}),
        std::vector<NodeTypePtr>{});
}

//------------------------------------------------------------------------------
bool should_wrap_function(const NodeFunction& cpp_function) {
    // Check its not ignored
    for (const auto& a : cpp_function.attrs) {
        if (a == IGNORE) {
            return false;
        }
    }

    return true;
}

//------------------------------------------------------------------------------
bool should_wrap(const NodeRecord& cpp_record, const NodeMethod& cpp_method) {
    // Skip static methods for now
    if (cpp_method.is_static) // TODO LT: Bring in support for static methods
    {
        //SPDLOG_WARN("Skipping static {}", cpp_method.name);
        return false;
    }

    // Check this is not a constructor for an abstract type
    if (cpp_method.is_constructor && cpp_record.abstract) {
        SPDLOG_WARN("Skipping abstract constructor {}", cpp_method.name);
        return false;
    }

    return should_wrap_function(cpp_method);
}

//------------------------------------------------------------------------------
NodeExprPtr convert_builtin_to(const TypeRegistry& type_registry,
                               const NodeTypePtr& t, const NodeExprPtr& name) {
    // TODO LT: Will make this smarter
    return NodeExprPtr(name);
}

//------------------------------------------------------------------------------
NodeExprPtr convert_record_to(const TypeRegistry& type_registry,
                              const NodeTypePtr& t, const NodeExprPtr& name) {
    // TODO LT: Assuming opaquebytes at the moment, opaqueptr will have a
    // different implementation.
    //
    auto reference = NodeRefExpr::n(NodeExprPtr(name));
    return NodeFunctionCallExpr::n("to_cpp_ref",
                                   std::vector<NodeExprPtr>({reference}),
                                   std::vector<NodeTypePtr>{});
}

//------------------------------------------------------------------------------
NodeExprPtr convert_enum_to(const TypeRegistry& type_registry,
                            const NodeTypePtr& t, const NodeExprPtr& name) {
    const auto to_cpp = build_enum_to_cpp_name(type_registry, t, "to_cpp_ref");

    auto reference = NodeRefExpr::n(NodeExprPtr(name));
    return NodeFunctionCallExpr::n(to_cpp,
                                   std::vector<NodeExprPtr>({reference}),
                                   std::vector<NodeTypePtr>{});
}

bool leaf_type_is(const NodeArrayType* p, NodeKind kind);

//------------------------------------------------------------------------------
bool leaf_type_is(const NodePointerType* p, NodeKind kind) {
    auto pointee_type = p->pointee_type.get();
    switch (pointee_type->kind) {
    case NodeKind::PointerType: {
        return leaf_type_is(static_cast<const NodePointerType*>(pointee_type),
                            NodeKind::BuiltinType);
    }
    case NodeKind::ArrayType: {
        return leaf_type_is(static_cast<const NodeArrayType*>(pointee_type),
                            NodeKind::BuiltinType);
    }
    default:
        return p->pointee_type->kind == kind;
    }
}

//------------------------------------------------------------------------------
bool leaf_type_is(const NodeArrayType* p, NodeKind kind) {
    auto element_type = p->element_type.get();
    switch (element_type->kind) {
    case NodeKind::PointerType: {
        return leaf_type_is(static_cast<const NodePointerType*>(element_type),
                            NodeKind::BuiltinType);
    }
    case NodeKind::ArrayType: {
        return leaf_type_is(static_cast<const NodeArrayType*>(element_type),
                            NodeKind::BuiltinType);
    }
    default:
        return p->element_type->kind == kind;
    }
}
/*
//------------------------------------------------------------------------------
std::string compute_to_cpp_name(const TypeRegistry& type_registry,
                                const NodePointerType* p, const char* suffix) {
    switch (p->pointee_type->kind) {
    case NodeKind::PointerType:
        return compute_to_cpp_name(
            type_registry,
            static_cast<const NodePointerType*>(p->pointee_type.get()), suffix);
    case NodeKind::ArrayType:
        return std::string(suffix); // TODO LT: Not sure if this is correct
    case NodeKind::RecordType:
        return std::string(suffix);
    case NodeKind::EnumType:
        return build_enum_to_cpp_name(type_registry, p->pointee_type, suffix);
    default:
        panic("compute_to_cpp_name unhandled pointee kind {}",
              p->pointee_type->kind); // TODO LT: Clean this up
        break;
    }
}
*/

//------------------------------------------------------------------------------
std::string compute_to_cpp_name(const TypeRegistry& type_registry,
                                const NodeTypePtr& node, const char* suffix) {
    switch (node->kind) {
    case NodeKind::PointerType:
        return compute_to_cpp_name(
            type_registry,
            static_cast<const NodePointerType*>(node.get())->pointee_type,
            suffix);
    case NodeKind::ArrayType:
        return compute_to_cpp_name(
            type_registry,
            static_cast<const NodeArrayType*>(node.get())->element_type,
            suffix);
    case NodeKind::RecordType:
        return std::string(suffix);
    case NodeKind::EnumType:
        return build_enum_to_cpp_name(type_registry, node, suffix);
    default:
        panic("unhandled node kind {}", node->kind); // TODO LT: Clean this up
        break;
    }
}

//------------------------------------------------------------------------------
NodeExprPtr convert_pointer_to(const TypeRegistry& type_registry,
                               const NodeTypePtr& t, const NodeExprPtr& name) {
    // TODO LT: Assuming opaquebytes at the moment, opaqueptr will have a
    // different implementation.
    //
    auto p = static_cast<const NodePointerType*>(t.get());

    // If we're using a pointer to a builtin type
    //
    if (leaf_type_is(p, NodeKind::BuiltinType)) {
        switch (p->pointer_kind) {
        case PointerKind::Pointer: {
            return name;
        }
        case PointerKind::RValueReference: // TODO LT: Add support for rvalue
                                           // reference
        case PointerKind::Reference: {
            return NodeDerefExpr::n(NodeExprPtr(name));
        }
        default:
            break;
        }
    }

    // Compute the correct conversion function name
    std::string to_cpp;
    switch (p->pointer_kind) {
    case PointerKind::Pointer:
        to_cpp = compute_to_cpp_name(type_registry, p->pointee_type, "to_cpp");
        break;
    case PointerKind::RValueReference: // TODO LT: Add support for rvalue
                                       // reference
    case PointerKind::Reference:
        to_cpp =
            compute_to_cpp_name(type_registry, p->pointee_type, "to_cpp_ref");
        break;
    }

    return NodeFunctionCallExpr::n(to_cpp, std::vector<NodeExprPtr>({name}),
                                   std::vector<NodeTypePtr>{});
}

//------------------------------------------------------------------------------
NodeExprPtr convert_array_to(const TypeRegistry& type_registry,
                             const NodeTypePtr& t, const NodeExprPtr& name) {
    // TODO LT: Assuming opaquebytes at the moment, opaqueptr will have a
    // different implementation.
    //
    auto a = static_cast<const NodeArrayType*>(t.get());

    // If we're using a pointer to a builtin type
    //
    if (leaf_type_is(a, NodeKind::BuiltinType)) {
        return name;
    }

    // Compute the correct conversion function name
    std::string to_cpp;
    to_cpp = compute_to_cpp_name(type_registry, a->element_type, "to_cpp");

    return NodeFunctionCallExpr::n(to_cpp, std::vector<NodeExprPtr>({name}),
                                   std::vector<NodeTypePtr>{});
}

//------------------------------------------------------------------------------
NodeExprPtr convert_to(const TypeRegistry& type_registry, const NodeTypePtr& t,
                       const NodeExprPtr& name) {

    if (t->kind == NodeKind::PointerType) {
        const NodePointerType* p = static_cast<const NodePointerType*>(t.get());
        if (p->pointee_type->kind == NodeKind::FunctionProtoType) {
            // Function pointers come out in the AST as a pointer to a function
            // prototype. We actually want to pass them around as value types
            // (via a typedef) so intercept it here.
            return NodeExprPtr(name);
        } else if (p->pointer_kind == PointerKind::Reference &&
                   p->pointee_type->kind == NodeKind::ArrayType) {
            // And array references want to be treated as values, but we need to
            // cast them back to the reference in order make the C++ compiler
            // happy
            const auto* a = static_cast<NodeArrayType*>(p->pointee_type.get());
            const auto* v = static_cast<NodeVarRefExpr*>(name.get());
            return NodeVarRefExpr::n(fmt::format("({} (&)[{}]){}",
                                                 a->element_type->type_name,
                                                 a->size, v->var_name));
        }
    }

    switch (t->kind) {
    case NodeKind::BuiltinType:
        return convert_builtin_to(type_registry, t, name);
    case NodeKind::RecordType:
        return convert_record_to(type_registry, t, name);
    case NodeKind::EnumType:
        return convert_enum_to(type_registry, t, name);
    case NodeKind::PointerType:
        return convert_pointer_to(type_registry, t, name);
    case NodeKind::ArrayType:
        return convert_array_to(type_registry, t, name);
    default:
        break;
    }

    panic("convert_to unhandled type kind {}",
          t->kind); // TODO LT: Clean this up
}

//------------------------------------------------------------------------------
NodeExprPtr convert_builtin_from(const NodeTypePtr& from_ptr,
                                 const NodeTypePtr& to_ptr,
                                 const NodeExprPtr& rhs,
                                 const NodeExprPtr& lhs) {
    // TODO LT: Be smarter
    return NodeAssignExpr::n(NodeDerefExpr::n(NodeExprPtr(lhs)),
                             NodeExprPtr(rhs));
}

//------------------------------------------------------------------------------
NodeExprPtr convert_record_from(const NodeTypePtr& from_ptr,
                                const NodeTypePtr& to_ptr,
                                const NodeExprPtr& rhs,
                                const NodeExprPtr& lhs) {
    return NodeFunctionCallExpr::n("to_c_copy",
                                   std::vector<NodeExprPtr>({lhs, rhs}),
                                   std::vector<NodeTypePtr>{}
    );
}

//------------------------------------------------------------------------------
NodeExprPtr convert_pointer_from(const NodeTypePtr& from_ptr,
                                 const NodeTypePtr& to_ptr,
                                 const NodeExprPtr& rhs,
                                 const NodeExprPtr& lhs
                                ) {
    auto from = static_cast<const NodePointerType*>(from_ptr.get());

    // If we're returning a pointer to a builtin type, then just return the
    // reference to the pointer. No need to convert it.
    //
    // TODO LT: Take into account pointers to pointers to builtin types
    if (from->pointee_type->kind == NodeKind::BuiltinType) {
        switch (from->pointer_kind) {
        case PointerKind::Pointer:
            return NodeAssignExpr::n(NodeDerefExpr::n(NodeExprPtr(lhs)), NodeExprPtr(rhs));
        case PointerKind::RValueReference: // TODO LT: Add support for rvalue
                                           // reference
        case PointerKind::Reference: {
            return NodeAssignExpr::n(NodeDerefExpr::n(NodeExprPtr(lhs)),
                                     NodeRefExpr::n(NodeExprPtr(rhs)));
        }
        default:
            break;
        }
    }

    switch (from->pointer_kind) {
    case PointerKind::RValueReference: // TODO LT: Add support for rvalue
                                       // reference
    case PointerKind::Pointer:
    case PointerKind::Reference: {
        return NodeFunctionCallExpr::n("to_c",
                                       std::vector<NodeExprPtr>({
                                            lhs,
                                            rhs
                                       }),
                                       std::vector<NodeTypePtr>{}
        );
    }
    default:
        break;
    }

    panic("convert_pointer_arg unhandled pointer kind {}",
          from->pointer_kind); // TODO LT: Clean this up
}

//------------------------------------------------------------------------------
NodeExprPtr convert_from(const NodeTypePtr& from, const NodeTypePtr& to,
                         const NodeExprPtr& rhs, const NodeExprPtr& lhs) {
    switch (to->kind) {
    case NodeKind::BuiltinType:
        return convert_builtin_from(from, to, rhs, lhs);
    case NodeKind::RecordType:
        return convert_record_from(from, to, rhs, lhs);
    case NodeKind::PointerType:
        return convert_pointer_from(from, to, rhs, lhs);
    default:
        break;
    }

    panic("convert_from unhanled type kind {}",
          to->kind); // TODO LT: Clean this up
}

//------------------------------------------------------------------------------
void argument(const TypeRegistry& type_registry, std::vector<NodeExprPtr>& args,
              const Param& param) {
    auto argument =
        convert_to(type_registry, param.type, NodeVarRefExpr::n(param.name));
    args.push_back(argument);
}

//------------------------------------------------------------------------------
NodeExprPtr opaquebytes_constructor_body(TypeRegistry& type_registry,
                                         TranslationUnit& c_tu,
                                         const NodeRecord& cpp_record,
                                         const NodeRecord& c_record,
                                         const NodeMethod& cpp_method) {
    // Loop over the parameters, creating arguments for the method call
    auto args = std::vector<NodeExprPtr>();
    for (const auto& p : cpp_method.params) {
        argument(type_registry, args, p);
    }

    // All constructors use placement new, so we need to make sure new is
    // included
    c_tu.source_includes.insert("#include <new>");

    // Create the method call expression
    return NodeBlockExpr::n(std::vector<NodeExprPtr>({NodePlacementNewExpr::n(
        NodeVarRefExpr::n(THIS_),
        NodeFunctionCallExpr::n(cpp_record.name, args,
                                std::vector<NodeTypePtr>{}))}));
}

//------------------------------------------------------------------------------
NodeExprPtr opaqueptr_constructor_body(TypeRegistry& type_registry,
                                       TranslationUnit& c_tu,
                                       const NodeRecord& cpp_record,
                                       const NodeRecord& c_record,
                                       const NodeMethod& cpp_method) {
    // Loop over the parameters, creating arguments for the method call
    auto args = std::vector<NodeExprPtr>();
    for (const auto& p : cpp_method.params) {
        argument(type_registry, args, p);
    }

    // All constructors use placement new, so we need to make sure new is
    // included
    c_tu.source_includes.insert("#include <new>");

    // Create the method call expression
    return NodeBlockExpr::n(std::vector<NodeExprPtr>({
        NodeAssignExpr::n(
            NodeDerefExpr::n(NodeVarRefExpr::n("this")),
            NodeNewExpr::n(
                NodeFunctionCallExpr::n(cpp_record.name, args,
                                        std::vector<NodeTypePtr>{}))
        )
    }));
}

//------------------------------------------------------------------------------
NodeExprPtr constructor_body(TypeRegistry& type_registry,
                             TranslationUnit& c_tu,
                             const NodeRecord& cpp_record,
                             const NodeRecord& c_record,
                             const NodeMethod& cpp_method) {
    switch(bind_type(cpp_record))
    {
        case BindType::OpaquePtr:
            return opaqueptr_constructor_body(type_registry, c_tu, cpp_record,
                                              c_record, cpp_method);
        case BindType::OpaqueBytes:
        case BindType::ValueType:
            return opaquebytes_constructor_body(type_registry, c_tu, cpp_record,
                                                c_record, cpp_method);
    }
}

//------------------------------------------------------------------------------
NodeExprPtr opaqueptr_destructor_body(TypeRegistry& type_registry,
                                      TranslationUnit& c_tu,
                                      const NodeRecord& cpp_record,
                                      const NodeRecord& c_record,
                                      const NodeMethod& cpp_method) {
    // Create the method call expression
    return NodeBlockExpr::n(
        std::vector<NodeExprPtr>({
            NodeDeleteExpr::n(
                NodeFunctionCallExpr::n("to_cpp",
                    std::vector<NodeExprPtr>{
                        NodeVarRefExpr::n("this_")
                    },
                    std::vector<NodeTypePtr>{}
                )
            )
        })
    );
}

//------------------------------------------------------------------------------
NodeExprPtr function_body(TypeRegistry& type_registry, TranslationUnit& c_tu,
                          const NodeTypePtr& c_return,
                          const NodeFunction& cpp_function) {
    // Loop over the parameters, creating arguments for the function call
    auto args = std::vector<NodeExprPtr>();
    for (const auto& p : cpp_function.params) {
        argument(type_registry, args, p);
    }

    // Obtain the function name
    auto cpp_function_name = cpp_function.name;

    // Create the function call expression
    auto function_call = NodeFunctionCallExpr::n(cpp_function_name, args,
                                                 cpp_function.template_args);

    // Convert the result
    auto is_void =
        c_return->kind == NodeKind::BuiltinType &&
        static_cast<const NodeBuiltinType*>(c_return.get())->type_name ==
            "void";

    if (is_void) {
        return NodeBlockExpr::n(std::vector<NodeExprPtr>({function_call}));
    }

    return NodeBlockExpr::n(std::vector<NodeExprPtr>({
        convert_from(cpp_function.return_type, c_return, function_call,
                     NodeVarRefExpr::n("return_"))}));
}

//------------------------------------------------------------------------------
NodeExprPtr method_body(TypeRegistry& type_registry,
                        TranslationUnit& c_tu,
                        const NodeRecord& cpp_record,
                        const NodeRecord& c_record,
                        const NodeTypePtr& c_return,
                        const NodeMethod& cpp_method) {
    // Create the reference to this
    auto this_ = this_reference(cpp_record, cpp_method.is_const);

    // Loop over the parameters, creating arguments for the method call
    auto args = std::vector<NodeExprPtr>();
    for (const auto& p : cpp_method.params) {
        argument(type_registry, args, p);
    }

    // Obtain the method name
    auto cpp_method_name = cpp_method.short_name;
    if (cpp_method.is_destructor) {
        cpp_method_name = cpp_method.name;
    }

    for (const auto& a : cpp_method.template_args) {
        SPDLOG_DEBUG("template args: {}", a->type_name);
    }

    // Create the method call expression
    auto method_call = NodeMethodCallExpr::n(std::move(this_), cpp_method_name,
                                             args, cpp_method.template_args);

    // Convert the result
    auto is_void =
        c_return->kind == NodeKind::BuiltinType &&
        static_cast<const NodeBuiltinType*>(c_return.get())->type_name ==
            "void";

    if (is_void) {
        return NodeBlockExpr::n(
                std::vector<NodeExprPtr>({
                    method_call,
                    NodeReturnExpr::n(NodeVarRefExpr::n("0"))
                })
        );
    }

    return NodeBlockExpr::n(std::vector<NodeExprPtr>({
                        convert_from(cpp_method.return_type, c_return,
                                     method_call, NodeVarRefExpr::n("return_")
                        ),
                    NodeReturnExpr::n(NodeVarRefExpr::n("0"))
    }));
}

//------------------------------------------------------------------------------
NodeExprPtr destructor_body(TypeRegistry& type_registry,
                            TranslationUnit& c_tu,
                            const NodeRecord& cpp_record,
                            const NodeRecord& c_record,
                            const NodeTypePtr& c_return,
                            const NodeMethod& cpp_method)
{
    switch(bind_type(cpp_record))
    {
        case BindType::OpaquePtr:
            return opaqueptr_destructor_body(type_registry, c_tu, cpp_record,
                                             c_record, cpp_method);
        case BindType::OpaqueBytes:
        case BindType::ValueType:
            return method_body(type_registry, c_tu, cpp_record, c_record,
                               c_return, cpp_method);
    }
}

//------------------------------------------------------------------------------
NodeExprPtr record_method_body(TypeRegistry& type_registry, TranslationUnit& c_tu,
                               const NodeRecord& cpp_record,
                               const NodeRecord& c_record, const NodeTypePtr& c_return,
                               const NodeMethod& cpp_method) {
    if (cpp_method.is_constructor) {
        return constructor_body(type_registry, c_tu, cpp_record,
                                c_record, cpp_method);
    } else if(cpp_method.is_destructor){
        return destructor_body(type_registry, c_tu, cpp_record,
                               c_record, c_return, cpp_method);
    } else {
        return method_body(type_registry, c_tu, cpp_record,
                           c_record, c_return, cpp_method);
    }
}

//------------------------------------------------------------------------------
std::string find_function_short_name(const NodeFunction& cpp_function) {
    auto prefix = std::string("cppmm|rename|");
    for (auto& a : cpp_function.attrs) {
        if (pystring::startswith(a, prefix)) {
            auto short_name = pystring::slice(a, prefix.size());
            return short_name;
        }
    }

    return cpp_function.short_name;
}

//------------------------------------------------------------------------------
void record_method(TypeRegistry& type_registry, TranslationUnit& c_tu,
                   const NodeRecord& cpp_record,
                   const NodeRecord& c_record,
                   const NodeMethod& cpp_method,
                   NodePtr& copy_constructor) {
    // Skip ignored methods
    if (!should_wrap(cpp_record, cpp_method)) {
        return;
    }

    // Convert return type
    auto c_return = convert_type(c_tu, type_registry, cpp_method.return_type);
    if (!c_return) {
        SPDLOG_ERROR("Skipping method {} due to unrecognised return type {}",
                     cpp_method.name, cpp_method.return_type->type_name);
        return;
    }
   
    // The value of the return type cannot be const. If it's a pointer type
    // or reference the pointee type can be const, but the return value cannot.
    c_return->const_ = false;

    auto c_return_for_method = c_return;

    // Convert params
    auto c_params = std::vector<Param>();
    c_params.push_back(this_param(c_record, cpp_method.is_const));

    // Return value
    auto c_return_is_void =
        c_return->kind == NodeKind::BuiltinType &&
        static_cast<const NodeBuiltinType*>(c_return.get())->type_name ==
            "void";

    if(!c_return_is_void) {
        auto return_pointer =
            NodePointerType::n(PointerKind::Pointer, std::move(c_return),
                               false);
        c_params.push_back(Param(std::string("return_"),
                                 std::move(return_pointer),
                                 c_params.size()));
    }


    // Add the other methods
    for (const auto& p : cpp_method.params) {
        if (!parameter(c_tu, type_registry, c_params, p)) {
            SPDLOG_ERROR("Skipping method {} due to unrecognised type {} of "
                         "parameter \"{}\"",
                         cpp_method.name, p.type->type_name, p.name);
            return;
        }
    }

    // Function body
    auto c_function_body = record_method_body(type_registry, c_tu, cpp_record,
                                             c_record, c_return_for_method,
                                             cpp_method);

    auto short_name = find_function_short_name(cpp_method);

    // Build the new method name. We need to generate unique function names
    // that share a common suffix but with different prefixes
    // The full prefix we get by stripping the "_t" from the struct name
    std::string function_prefix = pystring::slice(c_record.name, 0, -2);
    std::string function_suffix = compute_c_name(short_name);
    std::string function_name = function_prefix + "_" + function_suffix;
    function_name = type_registry.make_symbol_unique(function_name);

    // now strip the uniquified suffix from the function name and stick on the
    // nice prefix
    function_suffix = function_name.substr(function_prefix.size() + 1);
    std::string function_nice_name =
        pystring::slice(c_record.nice_name, 0, -2) + "_" + function_suffix;

    auto template_args = cpp_method.template_args;

    // Add the error int
    auto error_return = NodeBuiltinType::n(std::string("unsigned int"), 0,
                                           std::string("unsigned int"), false);

    auto c_function = NodeFunction::n(
        function_name, PLACEHOLDER_ID, cpp_method.attrs, "",
        std::move(error_return), std::move(c_params), function_nice_name,
        cpp_method.comment, std::move(template_args));

    c_function->body = c_function_body;
    c_tu.decls.push_back(NodePtr(c_function));

    // Keep hold of a reference to the copy constructor,
    // we need this later on for implicit conversions.
    //
    // TODO LT: Take the move constructor with priority
    if (cpp_method.is_copy_constructor) {
        
        SPDLOG_WARN("Found copy constructor {}", cpp_method.name);
        copy_constructor = c_function;
    }
}

//------------------------------------------------------------------------------
void record_methods(TypeRegistry& type_registry, TranslationUnit& c_tu,
                    const NodeRecord& cpp_record,
                    const NodeRecord& c_record,
                    NodePtr& copy_constructor) {
    for (const auto& m : cpp_record.methods) {
        record_method(type_registry, c_tu, cpp_record, c_record, m,
                      copy_constructor);
    }
}

/*
//------------------------------------------------------------------------------
void opaqueptr_method(TypeRegistry& type_registry, TranslationUnit& c_tu,
                      const NodeRecord& cpp_record, const NodeRecord& c_record,
                      const NodeMethod& cpp_method) {
    // Skip ignored methods
    if (!should_wrap(cpp_record, cpp_method)) {
        // std::cerr << "ignoring method decl: " << cpp_method.name <<
        // std::endl;
        return;
    }

    // Convert return type
    auto c_return = convert_type(c_tu, type_registry, cpp_method.return_type);
    if (!c_return) {
        SPDLOG_ERROR("Skipping method {} due to unrecognised return type {}",
                     cpp_method.name, cpp_method.return_type->type_name);
        return;
    }

    // The value of the return type cannot be const. If it's a pointer type
    // or reference the pointee type can be const, but the return value cannot.
    c_return->const_ = false;

    auto c_return_for_method = c_return;

    // Convert params
    auto c_params = std::vector<Param>();
    c_params.push_back(this_param(c_record, cpp_method.is_const));

    // Return value
    auto c_return_is_void =
        c_return->kind == NodeKind::BuiltinType &&
        static_cast<const NodeBuiltinType*>(c_return.get())->type_name ==
            "void";

    if(!c_return_is_void) {
        auto return_pointer =
            NodePointerType::n(PointerKind::Pointer, std::move(c_return),
                               false);
        c_params.push_back(Param(std::string("return_"),
                                 std::move(return_pointer),
                                 c_params.size()));
    }

    for (const auto& p : cpp_method.params) {
        if (!parameter(c_tu, type_registry, c_params, p)) {
            SPDLOG_ERROR("Skipping method {} due to unrecognised type {} of "
                         "parameter \"{}\"",
                         cpp_method.name, p.type->type_name, p.name);
            return;
        }
    }

    if (bind_type(cpp_record) == BindType::OpaquePtr &&
        cpp_method.is_constructor) {
        // convert the first parameter to a **
        c_params[0].type = NodePointerType::n(
            PointerKind::Pointer, std::move(c_params[0].type), false);
    }

    // Function body
    NodeExprPtr c_function_body;
    if (cpp_method.is_constructor) {
        c_function_body = opaqueptr_constructor_body(
            type_registry, c_tu, cpp_record, c_record, cpp_method);
    } else if (cpp_method.is_destructor) {
        c_function_body = opaqueptr_destructor_body(
            type_registry, c_tu, cpp_record, c_record, cpp_method);
    } else {
        c_function_body = opaquebytes_method_body(
            type_registry, c_tu, cpp_record, c_record, c_return_for_method,
            cpp_method);
    }

    auto short_name = find_function_short_name(cpp_method);

    // Build the new method name. We need to generate unique function names
    // that share a common suffix but with different prefixes
    // The full prefix we get by stripping the "_t" from the struct name
    std::string function_prefix = pystring::slice(c_record.name, 0, -2);
    std::string function_suffix = compute_c_name(short_name);
    std::string function_name = function_prefix + "_" + function_suffix;
    function_name = type_registry.make_symbol_unique(function_name);

    // now strip the uniquified suffix from the function name and stick on the
    // nice prefix
    function_suffix = function_name.substr(function_prefix.size() + 1);
    std::string function_nice_name =
        pystring::slice(c_record.nice_name, 0, -2) + "_" + function_suffix;

    auto template_args = cpp_method.template_args;

    // Add the error int
    auto error_return = NodeBuiltinType::n(std::string("unsigned int"), 0,
                                           std::string("unsigned int"), false);

    auto c_function = NodeFunction::n(
        function_name, PLACEHOLDER_ID, cpp_method.attrs, "",
        std::move(error_return), std::move(c_params), function_nice_name,
        cpp_method.comment, std::move(template_args));

    c_function->body = c_function_body;
    c_tu.decls.push_back(NodePtr(c_function));
}

//------------------------------------------------------------------------------
void opaqueptr_methods(TypeRegistry& type_registry, TranslationUnit& c_tu,
                       const NodeRecord& cpp_record,
                       const NodeRecord& c_record) {
    for (const auto& m : cpp_record.methods) {
        opaqueptr_method(type_registry, c_tu, cpp_record, c_record, m);
    }
}
*/

//------------------------------------------------------------------------------
void record_entry(NodeId& record_id, TypeRegistry& type_registry,
                  TranslationUnit::Ptr& c_tu, const NodePtr& cpp_node) {
    const auto& cpp_record = *static_cast<const NodeRecord*>(cpp_node.get());

    const auto c_record_name = compute_c_name(cpp_record.name) + "_t";
    const auto nice_name =
        compute_qualified_nice_name(type_registry, cpp_record.namespaces,
                                    cpp_record.alias) +
        "_t";

    // Create the c record
    auto c_record = NodeRecord::n(
        c_tu, c_record_name, record_id++, cpp_record.attrs, cpp_record.size,
        cpp_record.align, cpp_record.alias, cpp_record.namespaces, false,
        cpp_record.trivially_copyable, cpp_record.trivially_movable,
        cpp_record.opaque_type, cpp_record.comment);

    c_record->nice_name = nice_name;

    // Add the cpp and c record to the registry
    type_registry.add(cpp_node->id, cpp_node, c_record);
    type_registry.add_namespace(cpp_record.id, cpp_record.alias);
    type_registry.add_namespace_alias(cpp_record.id, cpp_record.alias, false);

    // Finally add the record to the translation unit
    c_tu->decls.push_back(std::move(c_record));
}

//------------------------------------------------------------------------------
void function_pointer_typedef_entry(NodeId& fpt_id, TypeRegistry& type_registry,
                                    TranslationUnit::Ptr& c_tu,
                                    const NodePtr& cpp_node) {
    const auto& cpp_fpt =
        *static_cast<const NodeFunctionPointerTypedef*>(cpp_node.get());

    const auto c_fpt_name = compute_c_name(cpp_fpt.name);
    const auto nice_name =
        compute_qualified_nice_name(type_registry, cpp_fpt.namespaces,
                                    cpp_fpt.alias) +
        "_t";
    SPDLOG_TRACE("Adding FPT {} -> {} with id {}", c_fpt_name, nice_name,
                 cpp_fpt.id);

    auto return_type = cpp_fpt.return_type;
    auto params = cpp_fpt.params;

    auto c_fpt = NodeFunctionPointerTypedef::n(
        c_tu, c_fpt_name, fpt_id++, cpp_fpt.alias, cpp_fpt.namespaces,
        cpp_fpt.comment, std::move(return_type), std::move(params));
    c_fpt->nice_name = nice_name;

    type_registry.add(cpp_fpt.id, cpp_node, c_fpt);

    c_tu->decls.push_back(std::move(c_fpt));
}

//------------------------------------------------------------------------------
void cast_to_cpp(TranslationUnit& c_tu, const std::string& cpp_record_name,
                 NodeId cpp_record_id, const std::string& c_record_name,
                 NodeId c_record_id, bool const_, PointerKind pointer_kind,
                 BindType bind_type,
                 const std::string& prefix = std::string()) {
    auto rhs = NodePointerType::n(
        PointerKind::Pointer,
        NodeRecordType::n("", 0, c_record_name, c_record_id, const_), false);

    auto cpp_return = NodePointerType::n(
        pointer_kind,
        NodeRecordType::n("", 0, cpp_record_name, cpp_record_id, const_),
        false);

    // Data reference
    auto data_reference =
        (bind_type == BindType::OpaquePtr) ?
            NodeVarRefExpr::n("rhs->data") : NodeVarRefExpr::n("rhs");

    // Cast type
    NodeExprPtr cast_expr = NodeCastExpr::n(
        NodeVarRefExpr::n("rhs"),
        NodePointerType::n(
            PointerKind::Pointer,
            NodeRecordType::n("", 0, cpp_record_name, cpp_record_id, const_),
            false),
        "reinterpret");

    if (pointer_kind == PointerKind::Reference) {
        cast_expr = NodeDerefExpr::n(std::move(cast_expr));
    }

    // Function body
    auto c_function_body = NodeBlockExpr::n(std::vector<NodeExprPtr>({
        NodeReturnExpr::n(std::move(cast_expr)),
    }));

    // Add the new function to the translation unit
    std::vector<std::string> attrs;
    std::vector<Param> params = {Param("rhs", rhs, 0)};
    std::string function_name = prefix + "to_cpp";
    if (pointer_kind == PointerKind::Reference) {
        function_name += "_ref";
    }
    auto c_function = NodeFunction::n(function_name, PLACEHOLDER_ID, attrs, "",
                                      std::move(cpp_return), std::move(params),
                                      "", "", std::vector<NodeTypePtr>{});

    c_function->body = c_function_body;
    c_function->private_ = true;
    c_function->inline_ = true;

    c_tu.decls.push_back(std::move(c_function));
}

//------------------------------------------------------------------------------
void cast_to_c(TranslationUnit& c_tu, const std::string& cpp_record_name,
               NodeId cpp_record_id, const std::string& c_record_name,
               NodeId c_record_id, bool const_, PointerKind pointer_kind,
               BindType bind_type,
               const std::string& prefix = std::string()) {
    auto rhs = NodePointerType::n(
        pointer_kind,
        NodeRecordType::n("", 0, cpp_record_name, cpp_record_id, const_),
        false);

    auto c_return = NodePointerType::n(
        PointerKind::Pointer,
        NodeRecordType::n("", 0, c_record_name, c_record_id, const_), false);

    NodeExprPtr var_ref_expr = NodeVarRefExpr::n("rhs");
    if (pointer_kind == PointerKind::Reference) {
        var_ref_expr = NodeRefExpr::n(std::move(var_ref_expr));
    }

    // Cast type
    NodeExprPtr cast_expr = NodeCastExpr::n(
        std::move(var_ref_expr),
        NodePointerType::n(
            PointerKind::Pointer,
            NodeRecordType::n("", 0, c_record_name, c_record_id, const_),
            false),
        "reinterpret");

    // Function body
    auto c_function_body = NodeBlockExpr::n(std::vector<NodeExprPtr>({
        NodeAssignExpr::n(
            NodeDerefExpr::n(NodeVarRefExpr::n("lhs")),
            std::move(cast_expr)),
    }));

    // Function name
    auto function_name = prefix;
    function_name += "to_c";

    // Add the new function to the translation unit
    std::vector<std::string> attrs;
    std::vector<Param> params =
        {Param("lhs", NodePointerType::n(PointerKind::Pointer, c_return, false), 0),
         Param("rhs", rhs, 1)
    };
    auto void_t = NodeBuiltinType::n("void", 0, "void", false);
    auto c_function = NodeFunction::n(function_name, PLACEHOLDER_ID, attrs, "",
                                      std::move(void_t), std::move(params),
                                      "", "", std::vector<NodeTypePtr>{});

    c_function->body = c_function_body;
    c_function->private_ = true;
    c_function->inline_ = true;

    c_tu.decls.push_back(std::move(c_function));
}

//------------------------------------------------------------------------------
void to_c_copy__trivial(TranslationUnit& c_tu,
                        const std::string& cpp_record_name,
                        NodeId cpp_record_id,
                        const std::string& c_record_name,
                        NodeId c_record_id,
                        const std::string& prefix = std::string()) {
    auto rhs = NodePointerType::n(
        PointerKind::Reference,
        NodeRecordType::n("", 0, cpp_record_name, cpp_record_id, true), false);

    auto c_return = NodeRecordType::n("", 0, c_record_name, c_record_id, false);

    // Add the include needed for memcpy
    c_tu.private_includes.insert("#include <cstring>");

    // Function body
    auto c_function_body = NodeBlockExpr::n(std::vector<NodeExprPtr>(
        {
         // memcpy(&result, &rhs, sizeof(result))
         NodeFunctionCallExpr::n(
             "memcpy",
             std::vector<NodeExprPtr>(
                 {NodeVarRefExpr::n("lhs"),
                  NodeRefExpr::n(NodeVarRefExpr::n("rhs")),
                  NodeFunctionCallExpr::n(
                      "sizeof", std::vector<NodeExprPtr>(
                                    {NodeDerefExpr::n(NodeVarRefExpr::n("lhs"))}
                                ),
                       std::vector<NodeTypePtr>{}
                  )
                 }
            ),
            std::vector<NodeTypePtr>{}
         )
        }
    ));

    // Function name
    auto function_name = prefix;
    function_name += "to_c_copy";

    // Add the new function to the translation unit
    std::vector<std::string> attrs;
    std::vector<Param> params = {
        Param("lhs", NodePointerType::n(PointerKind::Pointer, c_return, false), 0),
        Param("rhs", rhs, 1)
    };
    auto c_function =
        NodeFunction::n(function_name, PLACEHOLDER_ID, attrs, "",
                        NodeBuiltinType::n("void", 0, "void", false),
                        std::move(params), "", "", std::vector<NodeTypePtr>{});

    c_function->body = c_function_body;
    c_function->private_ = true;
    c_function->inline_ = true;

    c_tu.decls.push_back(std::move(c_function));
}

//------------------------------------------------------------------------------
void enum_conversions(TranslationUnit& c_tu, const NodeEnum& cpp_enum,
                      const NodeTypedef& c_enum) {
    const auto& c_n = c_enum.name;
    const auto& c_id = c_enum.id;
    const auto& cpp_n = cpp_enum.name;
    const auto& cpp_id = cpp_enum.id;

    // Function prefix
    auto p = c_n;
    p += "_";

    auto b = BindType::ValueType;
    auto ref = PointerKind::Reference;
    auto pointer = PointerKind::Pointer;

    // Conversions for going from c to cpp
    cast_to_cpp(c_tu, cpp_n, cpp_id, c_n, c_id, true, ref, b, p);
    cast_to_cpp(c_tu, cpp_n, cpp_id, c_n, c_id, false, ref, b, p);
    cast_to_cpp(c_tu, cpp_n, cpp_id, c_n, c_id, true, pointer, b, p);
    cast_to_cpp(c_tu, cpp_n, cpp_id, c_n, c_id, false, pointer, b, p);

    // Conversions for going from cpp to c
    cast_to_c(c_tu, cpp_n, cpp_id, c_n, c_id, true, ref, b, p);
    cast_to_c(c_tu, cpp_n, cpp_id, c_n, c_id, true, pointer, b, p);
    cast_to_c(c_tu, cpp_n, cpp_id, c_n, c_id, false, ref, b, p);
    cast_to_c(c_tu, cpp_n, cpp_id, c_n, c_id, false, pointer, b, p);

    // Enum conversion is always bitwise copy
    to_c_copy__trivial(c_tu, cpp_n, cpp_id, c_n, c_id);
}

//------------------------------------------------------------------------------
const char* enum_infer_underlying_type(
    const size_t enum_size) // TODO LT: In the future, pull this directly out of
                            // the ast file
{
    switch (enum_size) {
    case 8:
        return "char";
    case 16:
        return "short";
    case 32:
        return "unsigned int";
    case 64:
        return "long unsigned int";
    default:
        break;
    }

    panic("Enum size ({}) doesn't match an underlying int type", enum_size);

    return "long unsigned int";
}

//------------------------------------------------------------------------------
void enum_entry(NodeId& new_id, TypeRegistry& type_registry,
                TranslationUnit::Ptr& c_tu, const NodePtr& cpp_node) {
    const auto& cpp_enum = *static_cast<NodeEnum*>(cpp_node.get());

    auto c_enum_name = compute_c_name(cpp_enum.name) + "_e";

    auto c_typedef_name = compute_qualified_nice_name(
        type_registry, cpp_enum.namespaces, cpp_enum.short_name);

    // Create the new enum variants with their namespaced names
    std::vector<std::pair<std::string, std::string>> variants;
    for (const auto& i : cpp_enum.variants) {
        variants.push_back(std::make_pair(
            c_typedef_name + std::string("_") + i.first, i.second));
    }

    // Create the new enum for the options
    auto c_enum =
        NodeEnum::n(c_tu, c_enum_name, c_typedef_name, cpp_enum.short_name,
                    new_id++, cpp_enum.attrs, variants, cpp_enum.size,
                    cpp_enum.align, cpp_enum.namespaces, cpp_enum.comment);
    c_enum->cpp_variants = cpp_enum.variants;

    // Build the typedef for the actual data
    auto underlying_type_name =
        std::string(enum_infer_underlying_type(cpp_enum.size));
    auto c_typedef =
        NodeTypedef::n(c_tu, c_typedef_name,
                       NodeBuiltinType::n(underlying_type_name, 0,
                                          underlying_type_name, false),
                       "");

    // Add the conversion functions for to_c and to_cpp.
    enum_conversions(*c_tu, cpp_enum, *c_typedef);

    type_registry.add(cpp_node->id, cpp_node, c_typedef);

    c_tu->decls.push_back(std::move(c_enum));
    c_tu->decls.push_back(std::move(c_typedef));
}

//------------------------------------------------------------------------------
void function_detail(TypeRegistry& type_registry, TranslationUnit& c_tu,
                     const NodePtr& cpp_node) {
    const NodeFunction& cpp_function =
        *static_cast<const NodeFunction*>(cpp_node.get());

    // Skip ignored methods
    if (!should_wrap_function(cpp_function)) {
        return;
    }

    // Convert return type
    auto c_return = convert_type(c_tu, type_registry, cpp_function.return_type);
    if (!c_return) {
        SPDLOG_ERROR("Skipping function {} due to unrecognised return type {}",
                     cpp_function.name, cpp_function.return_type->type_name);
        return;
    }

    c_return->const_ = false;

    auto c_return_for_function = c_return;

    auto c_params = std::vector<Param>();

    // Return value
    auto c_return_is_void =
        c_return->kind == NodeKind::BuiltinType &&
        static_cast<const NodeBuiltinType*>(c_return.get())->type_name ==
            "void";

    if(!c_return_is_void) {
        auto return_pointer =
            NodePointerType::n(PointerKind::Pointer, std::move(c_return),
                               false);
        c_params.push_back(Param(std::string("return_"),
                                 std::move(return_pointer),
                                 c_params.size()));
    }

    // Convert params
    for (const auto& p : cpp_function.params) {
        if (!parameter(c_tu, type_registry, c_params, p)) {
            SPDLOG_ERROR("Skipping function {} due to unrecognised type {} of "
                         "parameter \"{}\"",
                         cpp_function.name, p.type->type_name, p.name);
            return;
        }
    }

    // Function body
    auto c_function_body =
        function_body(type_registry, c_tu, c_return_for_function, cpp_function);

    auto function_name = compute_c_name(
        compute_qualified_name(type_registry, cpp_function.namespaces,
                               find_function_short_name(cpp_function)));

    auto function_nice_name = compute_c_name(
        compute_qualified_nice_name(type_registry, cpp_function.namespaces,
                                    find_function_short_name(cpp_function)));

    // Build the new method name
    if (function_name == function_nice_name) {
        function_name = function_nice_name =
            type_registry.make_symbol_unique(function_name);
    } else {
        function_name = type_registry.make_symbol_unique(function_name);
        function_nice_name =
            type_registry.make_symbol_unique(function_nice_name);
    }

    auto template_args = cpp_function.template_args;

    auto c_function =
        NodeFunction::n(function_name, PLACEHOLDER_ID, cpp_function.attrs, "",
                        NodeBuiltinType::n("void", 0, "void", false),
                        std::move(c_params),
                        function_nice_name, cpp_function.comment,
                        std::move(template_args));

    c_function->body = c_function_body;
    c_tu.decls.push_back(NodePtr(c_function));
}

//------------------------------------------------------------------------------
void namespace_entry(TypeRegistry& type_registry, const NodePtr& cpp_node) {
    const auto& cpp_namespace =
        *static_cast<const NodeNamespace*>(cpp_node.get());

    SPDLOG_TRACE("Adding namespace \"{}\" \"{}\"", cpp_namespace.short_name,
                 cpp_namespace.alias);
    type_registry.add_namespace(cpp_namespace.id, cpp_namespace.short_name);
    type_registry.add_namespace_alias(cpp_namespace.id, cpp_namespace.alias,
                                      cpp_namespace.collapse);
}

//------------------------------------------------------------------------------
void to_c_copy__constructor(TranslationUnit& c_tu,
                            const NodeRecord& cpp_record,
                            const NodeRecord& c_record,
                            const NodePtr& copy_constructor_ptr) {
    const auto& copy_constructor =
        *static_cast<const NodeFunction*>(copy_constructor_ptr.get());

    auto rhs = NodePointerType::n(
        PointerKind::Reference,
        NodeRecordType::n("", 0, cpp_record.name, cpp_record.id, true), false);

    auto c_return =
        NodeRecordType::n("", 0, c_record.nice_name, c_record.id, false);

    // Function body
    auto c_function_body = NodeBlockExpr::n(std::vector<NodeExprPtr>(
        {
         // copy_constructor(&result, reinterpret_cast<const CTYPE *>(rhs))
         NodeFunctionCallExpr::n(
             copy_constructor.name,
             std::vector<NodeExprPtr>(
                 {NodeVarRefExpr::n("lhs"),
                  NodeCastExpr::n(
                      NodeRefExpr::n(NodeVarRefExpr::n("rhs")),
                      NodePointerType::n(PointerKind::Pointer,
                                         NodeRecordType::n("", 0,
                                                           c_record.nice_name,
                                                           c_record.id, true),
                                         false),
                      "reinterpret")
                }),

            std::vector<NodeTypePtr>{}
          ),
        }
    ));

    // Add the new function to the translation unit
    std::vector<std::string> attrs;
    std::vector<Param> params = {
        Param("lhs", NodePointerType::n(PointerKind::Pointer,
                                        std::move(c_return),
                                        false), 0),
        Param("rhs", rhs, 1),
    };
    auto c_function =
        NodeFunction::n("to_c_copy", PLACEHOLDER_ID, attrs, "",
                        NodeBuiltinType::n("void", 0, "void", false),
                        std::move(params), "", "", std::vector<NodeTypePtr>{});

    c_function->body = c_function_body;
    c_function->private_ = true;
    c_function->inline_ = true;

    c_tu.decls.push_back(std::move(c_function));
}

//------------------------------------------------------------------------------
void record_conversions(TranslationUnit& c_tu,
                        const NodeRecord& cpp_record,
                        const NodeRecord& c_record,
                        const NodePtr& copy_constructor) {
    const auto& c_n = c_record.nice_name;
    const auto& c_id = c_record.id;
    const auto& cpp_n = cpp_record.name;
    const auto& cpp_id = cpp_record.id;

    auto b = bind_type(cpp_record);
    auto ref = PointerKind::Reference;
    auto pointer = PointerKind::Pointer;

    // Conversions for going from cpp to c
    cast_to_cpp(c_tu, cpp_n, cpp_id, c_n, c_id, true, ref, b);
    cast_to_cpp(c_tu, cpp_n, cpp_id, c_n, c_id, false, ref, b);
    cast_to_cpp(c_tu, cpp_n, cpp_id, c_n, c_id, true, pointer, b);
    cast_to_cpp(c_tu, cpp_n, cpp_id, c_n, c_id, false, pointer, b);

    // Conversions for going from c to cpp
    cast_to_c(c_tu, cpp_n, cpp_id, c_n, c_id, true, ref, b);
    cast_to_c(c_tu, cpp_n, cpp_id, c_n, c_id, true, pointer, b);
    cast_to_c(c_tu, cpp_n, cpp_id, c_n, c_id, false, ref, b);
    cast_to_c(c_tu, cpp_n, cpp_id, c_n, c_id, false, pointer, b);

    // Copy conversions.
    // Use copy constructor if its available, or fallback to bitwise copy
    // if it's possible.
    if (copy_constructor) {
        to_c_copy__constructor(c_tu, cpp_record, c_record, copy_constructor);
    } else if (cpp_record.trivially_copyable) {
        to_c_copy__trivial(c_tu, cpp_record.name, cpp_record.id,
                           c_record.nice_name, c_record.id);
    }
}

/*
//------------------------------------------------------------------------------
void opaqueptr_conversions(TranslationUnit& c_tu, const NodeRecord& cpp_record,
                           const NodeRecord& c_record) {
    const auto& c_n = c_record.nice_name;
    const auto& c_id = c_record.id;
    const auto& cpp_n = cpp_record.name;
    const auto& cpp_id = cpp_record.id;

    // Conversions for going from cpp to c
    cast_to_cpp(c_tu, cpp_n, cpp_id, c_n, c_id, true, PointerKind::Reference);
    cast_to_cpp(c_tu, cpp_n, cpp_id, c_n, c_id, false, PointerKind::Reference);
    cast_to_cpp(c_tu, cpp_n, cpp_id, c_n, c_id, true, PointerKind::Pointer);
    cast_to_cpp(c_tu, cpp_n, cpp_id, c_n, c_id, false, PointerKind::Pointer);

    // Conversions for going from c to cpp
    cast_to_c(c_tu, cpp_n, cpp_id, c_n, c_id, true, PointerKind::Reference);
    cast_to_c(c_tu, cpp_n, cpp_id, c_n, c_id, true, PointerKind::Pointer);
    cast_to_c(c_tu, cpp_n, cpp_id, c_n, c_id, false, PointerKind::Reference);
    cast_to_c(c_tu, cpp_n, cpp_id, c_n, c_id, false, PointerKind::Pointer);
}
*/

//------------------------------------------------------------------------------
void valuetype_fields(TypeRegistry& type_registry, TranslationUnit& c_tu,
                      const NodeRecord& cpp_record, NodeRecord& c_record) {
    for (const auto& field : cpp_record.fields) {
        auto c_field_type = convert_type(c_tu, type_registry, field.type);
        if (!c_field_type) {
            panic("Unsupported type for field {} of record {}", field.name,
                  c_record.name);
        }
        c_record.fields.push_back(Field{field.name, c_field_type});
    }
}

//------------------------------------------------------------------------------
void valuetype_record(TypeRegistry& type_registry, TranslationUnit& c_tu,
                      const NodeRecord& cpp_record, NodeRecord& c_record) {
    valuetype_fields(type_registry, c_tu, cpp_record, c_record);
}

//------------------------------------------------------------------------------
void record_fields(TypeRegistry& type_registry, TranslationUnit& c_tu,
                   const NodeRecord& cpp_record, NodeRecord& c_record) {
    switch (bind_type(cpp_record)) {
    case BindType::OpaqueBytes:
        opaquebytes_record(c_record);
        return;
    case BindType::OpaquePtr:
        opaqueptr_record(c_record);
        return;
    case BindType::ValueType:
        valuetype_record(type_registry, c_tu, cpp_record, c_record);
        return;
    }
}

//------------------------------------------------------------------------------
void record_detail(TypeRegistry& type_registry, TranslationUnit& c_tu,
                   const NodePtr& cpp_node) {
    const auto& cpp_record = *static_cast<NodeRecord*>(cpp_node.get());

    // Most simple record implementation is the opaque bytes.
    // Least safe and most restrictive in use, but easiest to implement.
    // So doing that first. Later will switch depending on the cppm attributes.
    auto& c_record = type_registry.edit_c(
        cpp_record.id); // TODO LT: Return optional for error

    // Record
    record_fields(type_registry, c_tu, cpp_record, c_record);

    // Methods
    NodePtr copy_constructor;
    record_methods(type_registry, c_tu, cpp_record, c_record,
                   copy_constructor);

    // Conversions
    record_conversions(c_tu, cpp_record, c_record, copy_constructor);
}

//------------------------------------------------------------------------------
NodeId find_record_id_upper_bound(const Root& root) {
    // Loop through all the record ids and find the largest one.
    // This will be used as the starting point for creating new ids.
    NodeId upper_bound = 0;
    for (const auto& t : root.tus) {
        for (const auto& node : t->decls) {
            if (node->kind == NodeKind::Record) {
                upper_bound = std::max(upper_bound, node->id);
            }
        }
    }

    return upper_bound;
}

//------------------------------------------------------------------------------
std::string header_file_include(std::string header_filename) {
    std::string result = "#include <";
    result += header_filename;
    result += ">";
    return result;
}

//------------------------------------------------------------------------------
void translation_unit_entries(NodeId& new_id, TypeRegistry& type_registry,
                              const std::string& output_directory, Root& root,
                              const size_t cpp_tu_index) {
    const auto& cpp_tu = root.tus[cpp_tu_index];

    // Create a new translation unit
    const auto filepaths =
        generate::compute_c_filepath(output_directory, cpp_tu->filename);

    enum Outputs {
        Header = 0,
        Source = 1,
        PrivateHeader = 2,
    };

    // Make the new translation unit
    auto c_tu = TranslationUnit::new_(std::get<Source>(filepaths));
    c_tu->header_filename = header_file_include(std::get<Header>(filepaths));
    c_tu->private_header_filename =
        header_file_include(std::get<PrivateHeader>(filepaths));
    c_tu->include_paths = cpp_tu->include_paths;
    c_tu->private_includes.insert("#include <cstring>");

    // source includes -> private includes, this is so we have the types
    // we for other translation units
    auto cppmm_bind_h = std::string("cppmm_bind.hpp");
    for (auto& i : cpp_tu->source_includes) {
        auto use_include = pystring::find(i, cppmm_bind_h) == -1;
        if (use_include) {
            c_tu->private_includes.insert(i);
        }
    }

    // cpp namespaces
    for (const auto& node : cpp_tu->decls) {
        switch (node->kind) {
        case NodeKind::Namespace:
            generate::namespace_entry(type_registry, node);
            break;
        default:
            break;
        }
    }

    // function pointers
    for (const auto& node : cpp_tu->decls) {
        if (node->kind == NodeKind::FunctionPointerTypedef) {
            generate::function_pointer_typedef_entry(new_id, type_registry,
                                                     c_tu, node);
        }
    }

    // cpp records -> c records
    for (const auto& node : cpp_tu->decls) {
        switch (node->kind) {
        case NodeKind::Record:
            generate::record_entry(new_id, type_registry, c_tu, node);
            break;
        default:
            break;
        }
    }

    // cpp enums -> c enums
    for (const auto& node : cpp_tu->decls) {
        switch (node->kind) {
        case NodeKind::Enum:
            generate::enum_entry(new_id, type_registry, c_tu, node);
            break;
        default:
            break;
        }
    }

    root.tus.push_back(std::move(c_tu));
}

//------------------------------------------------------------------------------
void translation_unit_details(TypeRegistry& type_registry, Root& root,
                              const size_t cpp_tu_size, const size_t cpp_tu) {
    auto& c_tu = *root.tus[cpp_tu_size + cpp_tu];

    // cpp methods -> c functions
    for (const auto& node : root.tus[cpp_tu]->decls) {
        switch (node->kind) {
        case NodeKind::Record:
            generate::record_detail(type_registry, c_tu, node);
            break;
        case NodeKind::Function:
            generate::function_detail(type_registry, c_tu, node);
            break;
        default:
            break;
        }
    }
}

} // namespace generate

//------------------------------------------------------------------------------
void add_c(const std::string& output_directory, Root& root) {
    // For storing the mappings between cpp and c records
    auto type_registry = TypeRegistry();

    // The starting id for newly created records
    NodeId current_record_id = generate::find_record_id_upper_bound(root) + 1;

    // When we iterate we dont want to loop over newly added c translation units
    const auto tu_count = root.tus.size();
    for (size_t i = 0; i != tu_count; ++i) {
        generate::translation_unit_entries(current_record_id, type_registry,
                                           output_directory, root, i);
    }

    // Implement the records
    for (size_t i = 0; i != tu_count; ++i) {
        generate::translation_unit_details(type_registry, root, tu_count, i);
    }
}

} // namespace transform
} // namespace cppmm
