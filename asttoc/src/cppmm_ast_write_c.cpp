//------------------------------------------------------------------------------
// vfx-rs
//------------------------------------------------------------------------------
#include "cppmm_ast_write_c.hpp"

#include "cppmm_ast.hpp"

#include "pystring.h"

#include <fmt/os.h>

#include <iostream>

#include "filesystem.hpp"
namespace fs = ghc::filesystem;

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
class Root;

namespace write {

enum class Access : uint32_t { Private = 0, Public };

enum class Place : uint32_t { Header = 0, Source };

//------------------------------------------------------------------------------
static void indent(fmt::ostream& out, const size_t depth) {
    for (size_t i = 0; i != depth; ++i) {
        out.print("    ");
    }
}

//------------------------------------------------------------------------------
std::string compute_c_header_path(const std::string& path,
                                  const char* extension) {
    std::string _;
    std::string result;
    pystring::os::path::splitext(result, _, path);
    result += extension;

    return result;
}

std::string convert_param(const NodeTypePtr& field, const std::string& name);

//------------------------------------------------------------------------------
std::string convert_builtin_param(const NodeTypePtr& t,
                                  const std::string& name) {
    const char* const_ = t->const_ ? " const " : " ";
    return fmt::format("{}{}{}", t->type_name, const_, name);
}

//------------------------------------------------------------------------------
std::string convert_record_param(const NodeTypePtr& t,
                                 const std::string& name) {
    const char* const_ = t->const_ ? " const " : " ";
    return fmt::format("{}{}{}", t->type_name, const_, name);
}

//------------------------------------------------------------------------------
std::string convert_pointer_param(const NodeTypePtr& t,
                                  const std::string& name) {
    auto p = static_cast<const NodePointerType*>(t.get());

    switch (p->pointer_kind) {
    case PointerKind::Pointer:
        return convert_param(p->pointee_type, fmt::format("* {}", name));
    case PointerKind::Reference:
        return convert_param(p->pointee_type, fmt::format("& {}", name));
    default:
        break;
    }

    return "";
}

//------------------------------------------------------------------------------
std::string convert_array_param(const NodeTypePtr& t, const std::string& name) {
    auto p = static_cast<const NodeArrayType*>(t.get());

    return convert_param(p->element_type, fmt::format("{}[{}]", name, p->size));
}

//------------------------------------------------------------------------------
std::string convert_function_pointer_param(const NodeTypePtr& t,
                                           const std::string& name) {
    auto p = static_cast<const NodeFunctionProtoType*>(t.get());

    return fmt::format("{} {}", p->type, name);
}

//------------------------------------------------------------------------------
std::string convert_param(const NodeTypePtr& t, const std::string& name) {
    switch (t->kind) {
    case NodeKind::ArrayType:
        return convert_array_param(t, name);
    case NodeKind::BuiltinType:
        return convert_builtin_param(t, name);
    case NodeKind::RecordType:
        return convert_record_param(t, name);
    case NodeKind::PointerType:
        return convert_pointer_param(t, name);
    case NodeKind::FunctionProtoType:
        return convert_function_pointer_param(t, name);
    default:
        break;
    }

    SPDLOG_CRITICAL("Unhandled node kind {}", t->kind);
    return "";
}

//------------------------------------------------------------------------------
void write_field(fmt::ostream& out, const Field& field) {
    indent(out, 1);
    out.print("{};\n", convert_param(field.type, field.name));
}

//------------------------------------------------------------------------------
void write_fields(fmt::ostream& out, const NodeRecord& record) {
    for (const auto& f : record.fields) {
        write_field(out, f);
    }
}

//------------------------------------------------------------------------------
void write_record(fmt::ostream& out, const NodePtr& node) {
    const NodeRecord& record = *static_cast<const NodeRecord*>(node.get());

    constexpr auto sizeof_byte = 8;
    const auto align_in_bytes = record.align / sizeof_byte;

    if (!record.comment.empty()) {
        auto comment = record.comment;
        out.print("/** {} */\n", comment);
    }

    if (record.opaque_type) {
        out.print("typedef struct {0}_s {0};\n", record.name);
    } else {
        out.print("typedef struct {}_s {{\n", record.name);
        write_fields(out, record);
        out.print("}} __attribute__((aligned({}))) {};\n",
                  align_in_bytes, // TODO LT: Only force alignment if 'align'
                                  // attribute is on it.
                  record.name);
    }

    if (record.name != record.nice_name) {
        out.print("typedef {} {};\n\n", record.name, record.nice_name);
    }
}

//------------------------------------------------------------------------------
void write_record_forward_decl(fmt::ostream& out, const NodePtr& node) {
    const NodeRecord& record = *static_cast<const NodeRecord*>(node.get());
    out.print("typedef struct {0}_s {0};\n", record.name);
    if (record.name != record.nice_name) {
        out.print("typedef {} {};\n", record.name, record.nice_name);
    }
}

//------------------------------------------------------------------------------
void write_enum(fmt::ostream& out, const NodePtr& node) {
    const NodeEnum& enum_ = *static_cast<const NodeEnum*>(node.get());

    if (!enum_.comment.empty()) {
        auto comment = enum_.comment;
        out.print("/** {} */\n", comment);
    }
    out.print("enum {} {{\n", enum_.name);
    for (const auto& v : enum_.variants) {
        out.print("    {} = {},\n", v.first, v.second);
    }
    out.print("}};\n");
}

//------------------------------------------------------------------------------
void write_typedef(fmt::ostream& out, const NodePtr& node) {
    const NodeTypedef& typedef_ = *static_cast<const NodeTypedef*>(node.get());

    out.print("typedef {};\n", convert_param(typedef_.type, typedef_.name));
}

//------------------------------------------------------------------------------
void write_params(fmt::ostream& out, const NodeFunction& function) {
    if (!function.params.empty()) {
        auto param_count = function.params.size();
        out.print("\n");
        indent(out, 1);
        out.print("{}", convert_param(function.params[0].type,
                                      function.params[0].name));
        for (size_t i = 1; i < param_count; ++i) {
            out.print("\n");
            indent(out, 1);
            out.print(", {}", convert_param(function.params[i].type,
                                            function.params[i].name));
        }
    }
}

//------------------------------------------------------------------------------
void write_function_pointer_typedef(fmt::ostream& out, const NodePtr& node) {
    const NodeFunctionPointerTypedef& fpt =
        *static_cast<const NodeFunctionPointerTypedef*>(node.get());

    if (!fpt.comment.empty()) {
        auto comment = fpt.comment;
        out.print("/** {} */\n", comment);
    }

    std::vector<std::string> params;
    for (const auto& p : fpt.params) {
        params.push_back(convert_param(p.type, p.name));
    }

    out.print("typedef {} (*{})({});", convert_param(fpt.return_type, ""),
              fpt.nice_name, pystring::join(", ", params));
}

//------------------------------------------------------------------------------
void write_function_dcl(fmt::ostream& out, const NodePtr& node, Access access,
                        bool& wrote_anything) {
    const NodeFunction& function =
        *static_cast<const NodeFunction*>(node.get());

    const bool private_ = (access == Access::Private);
    if (private_ == function.private_) {
        wrote_anything = true;

        if (!function.comment.empty()) {
            auto comment = function.comment;
            out.print("/** {} */\n", comment);
        }

        out.print("{}(", convert_param(function.return_type, function.name));
        write_params(out, function);
        out.print(");\n");
    }
}

//------------------------------------------------------------------------------
void write_function_define(fmt::ostream& out, const NodePtr& node,
                           Access access, bool& wrote_anything) {
    const NodeFunction& function =
        *static_cast<const NodeFunction*>(node.get());

    const bool private_ = (access == Access::Private);
    if (private_ == function.private_ && function.nice_name != "" &&
        function.name != function.nice_name) {
        wrote_anything = true;
        out.print("#define {} {}\n\n", function.nice_name, function.name);
    }
}

//------------------------------------------------------------------------------
void write_expression(fmt::ostream& out, size_t depth, const NodeExprPtr& node);

//------------------------------------------------------------------------------
void write_function_call_arguments(fmt::ostream& out, size_t depth,
                                   const NodeFunctionCallExpr& function_call) {
    if (function_call.args.empty()) {
        out.print("()");
    } else {
        // start
        out.print("(");

        // First argument
        write_expression(out, depth, function_call.args[0]);

        // All the others
        for (size_t i = 1; i < function_call.args.size(); ++i) {
            out.print(", ");
            write_expression(out, depth, function_call.args[i]);
        }

        // start
        out.print(")");
    }
}

//------------------------------------------------------------------------------
void write_function_call_template_args(
    fmt::ostream& out, size_t depth,
    const NodeFunctionCallExpr& function_call) {
    if (function_call.template_args.empty()) {
        return;
    } else {
        // start
        out.print("<");

        std::vector<std::string> args;
        for (const auto& t : function_call.template_args) {
            auto c = "";
            if (t->const_) {
                c = "const ";
            }
            args.push_back(fmt::format("{}{}", c, t->type_name));
        }

        out.print(pystring::join(", ", args));

        out.print(">");
    }
}

//------------------------------------------------------------------------------
void write_expression_function_call(fmt::ostream& out, size_t depth,
                                    const NodeExprPtr& node) {
    const auto& function_call =
        *static_cast<const NodeMethodCallExpr*>(node.get());

    out.print("{}", function_call.name);
    write_function_call_template_args(out, depth, function_call);
    write_function_call_arguments(out, depth, function_call);
}

//------------------------------------------------------------------------------
void write_expression_infix_operator(fmt::ostream& out, size_t depth,
                                     const NodeExprPtr& node) {
    const auto& function_call =
        *static_cast<const NodeInfixOperatorExpr*>(node.get());

    // we know we only have an infix op when there's 2 arguments
    // start
    out.print("(");

    // First argument
    write_expression(out, depth, function_call.args[0]);
    out.print(" {} ", function_call.name);
    write_expression(out, depth, function_call.args[1]);

    // start
    out.print(")");
}

//------------------------------------------------------------------------------
void write_expression_move(fmt::ostream& out, size_t depth,
                           const NodeExprPtr& node) {
    const auto& move_expr = *static_cast<const NodeMoveExpr*>(node.get());

    out.print("std::move(");
    write_expression(out, depth, move_expr.inner);
    out.print(")");
}

//------------------------------------------------------------------------------
void write_expression_method_call(fmt::ostream& out, size_t depth,
                                  const NodeExprPtr& node) {
    const auto& method_call =
        *static_cast<const NodeMethodCallExpr*>(node.get());

    out.print("(");
    write_expression(out, depth, method_call.this_);
    out.print(") -> {}", method_call.name);
    write_function_call_template_args(out, depth, method_call);
    write_function_call_arguments(out, depth, method_call);
}

//------------------------------------------------------------------------------
void write_expression_var_ref(fmt::ostream& out, size_t depth,
                              const NodeExprPtr& node) {
    const auto& var_ref = *static_cast<const NodeVarRefExpr*>(node.get());

    out.print("{}", var_ref.var_name);
}

//------------------------------------------------------------------------------
void write_expression_deref(fmt::ostream& out, size_t depth,
                            const NodeExprPtr& node) {
    const auto& deref = *static_cast<const NodeDerefExpr*>(node.get());

    out.print("*(");
    write_expression(out, depth, deref.inner);
    out.print(")");
}

//------------------------------------------------------------------------------
void write_expression_arrow(fmt::ostream& out, size_t depth,
                            const NodeExprPtr& node) {
    const auto& arrow = *static_cast<const NodeArrowExpr*>(node.get());

    out.print("(");
    write_expression(out, depth, arrow.pointer);
    out.print(")->");
    write_expression(out, depth, arrow.pointee);
}

//------------------------------------------------------------------------------
void write_expression_ref(fmt::ostream& out, size_t depth,
                          const NodeExprPtr& node) {
    const auto& ref = *static_cast<const NodeRefExpr*>(node.get());

    out.print("&(");
    write_expression(out, depth, ref.inner);
    out.print(")");
}

//------------------------------------------------------------------------------
void write_expression_cast(fmt::ostream& out, size_t depth,
                           const NodeExprPtr& node) {
    const auto& cast_expr = *static_cast<const NodeCastExpr*>(node.get());

    out.print("{}_cast<{}>(", cast_expr.cast_kind,
              convert_param(cast_expr.type, ""));
    write_expression(out, depth, cast_expr.inner);
    out.print(")");
}

//------------------------------------------------------------------------------
void write_expression_placement_new(fmt::ostream& out, size_t depth,
                                    const NodeExprPtr& node) {
    const auto& plcmt_new_expr =
        *static_cast<const NodePlacementNewExpr*>(node.get());

    out.print("new (");
    write_expression(out, depth, plcmt_new_expr.address);
    out.print(") ");
    write_expression(out, depth, plcmt_new_expr.constructor);
}

//------------------------------------------------------------------------------
void write_expression_new(fmt::ostream& out, size_t depth,
                          const NodeExprPtr& node) {
    const auto& new_expr = *static_cast<const NodeNewExpr*>(node.get());

    out.print("new ");
    write_expression(out, depth, new_expr.constructor);
}

//------------------------------------------------------------------------------
void write_expression_delete(fmt::ostream& out, size_t depth,
                             const NodeExprPtr& node) {
    const auto& delete_expr = *static_cast<const NodeDeleteExpr*>(node.get());

    out.print("delete ");
    write_expression(out, depth, delete_expr.pointer);
}

//------------------------------------------------------------------------------
void write_expression_return(fmt::ostream& out, size_t depth,
                             const NodeExprPtr& node) {
    const auto& return_expr = *static_cast<const NodeReturnExpr*>(node.get());

    out.print("return ");
    write_expression(out, depth, return_expr.inner);
}

//------------------------------------------------------------------------------
void write_expression_var_decl(fmt::ostream& out, size_t depth,
                               const NodeExprPtr& node) {
    const auto& var_decl_expr =
        *static_cast<const NodeVarDeclExpr*>(node.get());

    out.print("{}",
              convert_param(var_decl_expr.var_type, var_decl_expr.var_name));
}

//------------------------------------------------------------------------------
void write_expression_block(fmt::ostream& out, size_t depth,
                            const NodeExprPtr& node) {
    const auto& block_expr = *static_cast<const NodeBlockExpr*>(node.get());

    for (auto& i : block_expr.expressions) {
        indent(out, depth);
        write_expression(out, depth + 1, i);
        out.print(";\n");
    }
}

//------------------------------------------------------------------------------
void write_expression_assign(fmt::ostream& out, size_t depth,
                             const NodeExprPtr& node) {
    const auto& assign_expr = *static_cast<const NodeAssignExpr*>(node.get());

    write_expression(out, depth + 1, assign_expr.lhs);
    out.print(" = ");
    write_expression(out, depth + 1, assign_expr.rhs);
}

//------------------------------------------------------------------------------
void write_expression(fmt::ostream& out, size_t depth,
                      const NodeExprPtr& node) {
    // Do nothing if this expression is empty
    if (!node) {
        return;
    }

    switch (node->kind) {
    case NodeKind::FunctionCallExpr:
        return write_expression_function_call(out, depth, node);
    case NodeKind::MethodCallExpr:
        return write_expression_method_call(out, depth, node);
    case NodeKind::VarRefExpr:
        return write_expression_var_ref(out, depth, node);
    case NodeKind::DerefExpr:
        return write_expression_deref(out, depth, node);
    case NodeKind::ArrowExpr:
        return write_expression_arrow(out, depth, node);
    case NodeKind::RefExpr:
        return write_expression_ref(out, depth, node);
    case NodeKind::CastExpr:
        return write_expression_cast(out, depth, node);
    case NodeKind::PlacementNewExpr:
        return write_expression_placement_new(out, depth, node);
    case NodeKind::NewExpr:
        return write_expression_new(out, depth, node);
    case NodeKind::DeleteExpr:
        return write_expression_delete(out, depth, node);
    case NodeKind::ReturnExpr:
        return write_expression_return(out, depth, node);
    case NodeKind::VarDeclExpr:
        return write_expression_var_decl(out, depth, node);
    case NodeKind::BlockExpr:
        return write_expression_block(out, depth, node);
    case NodeKind::AssignExpr:
        return write_expression_assign(out, depth, node);
    case NodeKind::InfixOperatorExpr:
        return write_expression_infix_operator(out, depth, node);
    case NodeKind::MoveExpr:
        return write_expression_move(out, depth, node);
    default:
        break;
    }

    panic("Unhandled expression kind {}", node->kind);
}

//------------------------------------------------------------------------------
void write_function_bdy(fmt::ostream& out, const NodePtr& node, Access access,
                        bool& wrote_anything) {
    const NodeFunction& function =
        *static_cast<const NodeFunction*>(node.get());

    const bool private_ = (access == Access::Private);
    if (private_ == function.private_) {
        wrote_anything = true;

        if (function.inline_) {
            out.print("inline ");
        }

        out.print("{}(", convert_param(function.return_type, function.name));
        write_params(out, function);
        out.print(")\n");
        out.print("{{\n");

        // FIXME AL: taking a shortcut here. We need to express this in terms
        // of expression nodes, but let's get it working first
        if (!function.private_ && function.short_name != "sizeof" &&
            function.short_name != "alignof" && !function.is_noexcept) {
            out.print("    try {{\n");
        }

        write_expression(out, 2, function.body);

        if (!function.private_ && function.short_name != "sizeof" &&
            function.short_name != "alignof" && !function.is_noexcept) {
            for (const auto& e : function.exceptions) {
                out.print("    }} catch ({}& e) {{\n"
                          "        TLG_EXCEPTION_STRING = e.what();\n"
                          "        return {};\n",
                          e.cpp_name, e.error_code);
            }

            out.print("    }} catch (std::exception& e) {{\n"
                      "        TLG_EXCEPTION_STRING = e.what();\n"
                      "        return -1;\n"
                      "    }}\n");
        }

        out.print("}}\n");
    }
}

//------------------------------------------------------------------------------
bool write_function(fmt::ostream& out, const NodePtr& node, Access access,
                    Place place) {
    const NodeFunction& function =
        *static_cast<const NodeFunction*>(node.get());

    auto wrote_any = false;
    if (function.inline_) {
        switch (place) {
        case Place::Header:
            write_function_bdy(out, node, access, wrote_any);
            write_function_define(out, node, access, wrote_any);
            break;
        default:
            break;
        }
    } else {
        switch (place) {
        case Place::Header:
            write_function_dcl(out, node, access, wrote_any);
            write_function_define(out, node, access, wrote_any);
            break;
        case Place::Source:
            write_function_bdy(out, node, access, wrote_any);
            break;
        default:
            break;
        }
    }

    return wrote_any;
}

//------------------------------------------------------------------------------
void write_header_includes(fmt::ostream& out, const TranslationUnit& tu) {
    for (const auto& i : tu.header_includes) {
        out.print("{}\n", i);
    }

    out.print("\n");
}

//------------------------------------------------------------------------------
void write_source_includes(fmt::ostream& out, const TranslationUnit& tu) {
    if (!tu.private_header_filename.empty()) {
        out.print("{}\n", tu.private_header_filename);
    }

    out.print("\n");

    for (const auto& i : tu.source_includes) {
        out.print("{}\n", i);
    }

    out.print("\n");
}

//------------------------------------------------------------------------------
void write_private_header(const TranslationUnit& tu, fs::path base_dir) {
    std::string basename, ext;
    pystring::os::path::splitext(basename, ext, tu.filename);
    fs::path filename = base_dir / "src" / (basename + "_private.h");
    fs::create_directories(filename.parent_path());
    auto out = fmt::output_file(filename.string());

    out.print("#pragma once\n");

    if (!tu.header_filename.empty()) {
        out.print("{}\n\n", tu.header_filename);
    }

    out.print("\n");

    for (const auto& i : tu.private_includes) {
        out.print("{}\n", i);
    }

    // Write out all the records
    for (const auto& node : tu.decls) {
        if (node->kind == NodeKind::Record) {
            if (node->private_) {
                write_record(out, node);
            }
        }
    }

    out.print("\n");

    // Then all the private functions
    for (const auto& node : tu.decls) {
        if (node->kind == NodeKind::Function) {
            if (write_function(out, node, Access::Private, Place::Header)) {
                out.print("\n");
            }
        }
    }
}

//------------------------------------------------------------------------------
void write_header(const TranslationUnit& tu, fs::path base_dir) {
    std::string basename, ext;
    pystring::os::path::splitext(basename, ext, tu.filename);
    fs::path filename = base_dir / "include" / (basename + ".h");
    fs::create_directories(filename.parent_path());
    auto out = fmt::output_file(filename.string());

    out.print("#pragma once\n");

    // Write all the includes needed in the header file
    write_header_includes(out, tu);

    // Extern "C"
    out.print("#ifdef __cplusplus\nextern \"C\" {{\n#endif\n\n");

    // Write out all the forward declarations
    bool wrote_any = false;
    for (const auto& node : tu.forward_decls) {
        if (node->kind == NodeKind::Record) {
            write_record_forward_decl(out, node);
            wrote_any = true;
        }
    }

    if (wrote_any) {
        out.print("\n");
    }

    wrote_any = false;
    // Write out all the enums and typedefs
    for (const auto& node : tu.decls) {
        switch (node->kind) {
        case NodeKind::Enum:
            write_enum(out, node);
            wrote_any = true;
            break;
        case NodeKind::Typedef:
            write_typedef(out, node);
            wrote_any = true;
            break;
        case NodeKind::FunctionPointerTypedef:
            write_function_pointer_typedef(out, node);
            wrote_any = true;
        default:
            break;
        }
    }

    if (wrote_any) {
        out.print("\n");
    }

    wrote_any = false;
    // Write out all the records
    for (const auto& node : tu.decls) {
        if (node->kind == NodeKind::Record) {
            if (!node->private_) {
                write_record(out, node);
                wrote_any = true;
            }
        }
    }

    if (wrote_any) {
        out.print("\n");
    }

    // Then all the public functions
    for (const auto& node : tu.decls) {
        if (node->kind == NodeKind::Function) {
            if (write_function(out, node, Access::Public, Place::Header)) {
                out.print("\n");
            }
        }
    }

    // Extern "C"
    out.print("#ifdef __cplusplus\n}}\n#endif\n");
}

//------------------------------------------------------------------------------
void write_source(const TranslationUnit& tu, fs::path base_dir) {
    fs::path filename = base_dir / "src" / tu.filename;
    fs::create_directories(filename.parent_path());
    auto out = fmt::output_file(filename.string());

    // Write out the source includes
    write_source_includes(out, tu);

    out.print("#include <stdexcept>\n\n");

    // Write out the function definitions
    for (const auto& node : tu.decls) {
        if (node->kind == NodeKind::Function) {
            if (write_function(out, node, Access::Public, Place::Source)) {
                out.print("\n");
            }
        }
    }
}

//------------------------------------------------------------------------------
void write_translation_unit(const TranslationUnit& tu, fs::path base_dir) {
    write_header(tu, base_dir);
    write_private_header(tu, base_dir);
    write_source(tu, base_dir);
}

//------------------------------------------------------------------------------
void c(const char* project_name, const Root& root, size_t starting_point,
       const char* output_dir) {
    expect(starting_point < root.tus.size(),
           "starting point ({}) is out of range ({})", starting_point,
           root.tus.size());

    auto base_dir = fs::path(output_dir);
    const auto size = root.tus.size();
    for (size_t i = starting_point; i < size; ++i) {
        const auto& tu = root.tus[i];
        write_translation_unit(*tu, base_dir);
    }
}

//------------------------------------------------------------------------------
void write_error_header(const char* filename, const char* project_name) {
    auto out = fmt::output_file(filename);

    out.print(R"(#pragma once
#ifdef __cplusplus
extern "C" {{
#endif

const char* {}_get_exception_string();

#ifdef __cplusplus
}}
#endif
)",
              project_name);
}

//------------------------------------------------------------------------------
void write_error_header_private(const char* filename,
                                const char* project_name) {
    auto out = fmt::output_file(filename);

    out.print(R"(#pragma once
#include <string>
extern thread_local std::string TLG_EXCEPTION_STRING;
)",
              project_name);
}

//------------------------------------------------------------------------------
void write_error_source(const char* filename, const char* public_header,
                        const char* private_header, const char* project_name) {
    auto out = fmt::output_file(filename);

    out.print(R"(#include "{0}"
#include "{1}"

thread_local std::string TLG_EXCEPTION_STRING;

const char* {2}_get_exception_string() {{
    return TLG_EXCEPTION_STRING.c_str();
}}

)",
              public_header, private_header, project_name);
}

//------------------------------------------------------------------------------
void cerrors(const char* output_dir, Root& root, size_t starting_point,
             const char* project_name) {
    auto basename = fmt::format("{}-errors", project_name);
    auto header_fn = fs::path(basename).replace_extension(".h");
    auto private_header_fn =
        fs::path(fmt::format("{}-errors-private.h", project_name));
    auto source_fn = fs::path(basename).replace_extension(".cpp");

    auto header_path = fs::path(output_dir) / "include" / header_fn;
    auto private_header_path = fs::path(output_dir) / "src" / private_header_fn;
    auto source_path = fs::path(output_dir) / "src" / source_fn;

    write_error_header(header_path.c_str(), project_name);
    write_error_header_private(private_header_path.c_str(), project_name);
    write_error_source(source_path.c_str(), header_fn.c_str(),
                       private_header_fn.c_str(), project_name);

    expect(starting_point < root.tus.size(),
           "starting point ({}) is out of range ({})", starting_point,
           root.tus.size());

    const auto size = root.tus.size();
    for (size_t i = starting_point; i < size; ++i) {
        auto& tu = root.tus[i];
        tu->private_includes.insert(
            fmt::format("#include \"{}\"\n", private_header_fn.string()));
    }
}

} // namespace write
} // namespace cppmm
