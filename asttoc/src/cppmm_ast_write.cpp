//------------------------------------------------------------------------------
// vfx-rs
//------------------------------------------------------------------------------
#include "cppmm_ast_write.hpp"

#include "cppmm_ast.hpp"

#include "pystring.h"

#include <fmt/os.h>
#include <cassert>

#include <iostream>

namespace cppmm
{
class Root;

namespace write
{
//------------------------------------------------------------------------------
void indent(fmt::ostream & out, const size_t depth)
{
    for(size_t i=0; i!= depth; ++i)
    {
        out.print("    ");
    }
}

//------------------------------------------------------------------------------
std::string compute_c_header_path(const std::string & path)
{
    std::string _;
    std::string result;
    pystring::os::path::splitext(result, _, path);
    result += ".h";

    return result;
}

std::string convert_param(const NodeTypePtr & field,
                          const std::string & name);

//------------------------------------------------------------------------------
std::string convert_builtin_param(const NodeTypePtr & t,
                                  const std::string & name)
{
    return fmt::format("{} {}", t->type_name, name);
}

//------------------------------------------------------------------------------
std::string convert_record_param(const NodeTypePtr & t,
                                 const std::string & name)
{
    return fmt::format("{} {}", t->type_name, name);
}

//------------------------------------------------------------------------------
std::string convert_pointer_param(const NodeTypePtr & t,
                                  const std::string & name)
{
    auto p = static_cast<const NodePointerType*>(t.get());

    return convert_param(p->pointee_type,
                         fmt::format("*{}", name));
}

//------------------------------------------------------------------------------
std::string convert_array_param(const NodeTypePtr & t,
                                const std::string & name)
{
    auto p = static_cast<const NodeArrayType*>(t.get());

    return convert_param(p->element_type,
                         fmt::format("{}[{}]", name, p->size));
}

//------------------------------------------------------------------------------
std::string convert_param(const NodeTypePtr & t,
                          const std::string & name)
{
    switch (t->kind)
    {
        case NodeKind::ArrayType:
            return convert_array_param(t, name);
        case NodeKind::BuiltinType:
            return convert_builtin_param(t, name);
        case NodeKind::RecordType:
            return convert_record_param(t, name);
        case NodeKind::PointerType:
            return convert_pointer_param(t, name);
        default:
            break;
    }

    assert("Shouldn't get here"); // TODO LT: Clean this up
}

//------------------------------------------------------------------------------
void write_field(fmt::ostream & out, const Field & field)
{
    indent(out, 1);
    out.print("{};\n", convert_param(field.type, field.name));
}

//------------------------------------------------------------------------------
void write_fields(fmt::ostream & out, const NodeRecord & record)
{
    for(const auto & f : record.fields)
    {
        write_field(out, f);
    }
}

//------------------------------------------------------------------------------
void write_record(fmt::ostream & out, const NodePtr & node)
{
    const NodeRecord & record = *static_cast<const NodeRecord*>(node.get());

    out.print("typedef struct {{\n");
    write_fields(out, record);
    out.print("}} __attribute__((aligned({}))) {};\n", record.align, // TODO LT: Only force alignment if 'align' attribute is on it.
              record.name);
}

//------------------------------------------------------------------------------
void write_params(fmt::ostream & out, const NodeFunction & function)
{
    if(!function.params.empty())
    {
        auto param_count = function.params.size();
            out.print("{}", convert_param(function.params[0].type,
                                          function.params[0].name));
        for(size_t i=1; i < param_count; ++i)
        {
            out.print(", {}", convert_param(function.params[i].type,
                                            function.params[i].name));
        }
    }
}

//------------------------------------------------------------------------------
void write_function(fmt::ostream & out, const NodePtr & node)
{
    const NodeFunction & function =
        *static_cast<const NodeFunction*>(node.get());

    out.print("{}(", convert_param(function.return_type,
                                   function.name));
    write_params(out, function);
    out.print(");\n");
}

void write_expression(fmt::ostream & out, size_t depth,
                      const NodeExprPtr & node);

//------------------------------------------------------------------------------
void write_function_call_arguments(fmt::ostream & out,
                                   size_t depth,
                                   const NodeFunctionCallExpr & function_call)
{
    if(!function_call.args.empty())
    {
        // First argument
        indent(out, depth + 1);
        write_expression(out, depth, function_call.args[0]);

        // All the others
        for(size_t i=1; i < function_call.args.size(); ++i)
        {
            out.print(",\n");
            indent(out, depth + 1);
            write_expression(out, depth, function_call.args[i]);
        }
    }
}

//------------------------------------------------------------------------------
void write_expression_function_call(fmt::ostream & out,
                                    size_t depth,
                                    const NodeExprPtr & node)
{
    const auto & function_call =
        *static_cast<const NodeMethodCallExpr*>(node.get());

    out.print("{}(\n", function_call.name);
    write_function_call_arguments(out, depth+1, function_call);
    out.print(")");
}

//------------------------------------------------------------------------------
void write_expression_method_call(fmt::ostream & out,
                                  size_t depth, const NodeExprPtr & node)
{
    const auto & method_call =
        *static_cast<const NodeMethodCallExpr*>(node.get());

    out.print("(");
    write_expression(out, depth, method_call.this_);
    out.print(") -> \n");
    indent(out, depth + 1);
    out.print("{}(\n", method_call.name);
    write_function_call_arguments(out, depth+1, method_call);
    out.print(")");
}

//------------------------------------------------------------------------------
void write_expression_var_ref(fmt::ostream & out,  size_t depth,
                              const NodeExprPtr & node)
{
    const auto & var_ref =
        *static_cast<const NodeVarRefExpr*>(node.get());

    out.print("{}", var_ref.var_name);
}

//------------------------------------------------------------------------------
void write_expression_deref(fmt::ostream & out,  size_t depth,
                            const NodeExprPtr & node)
{
    const auto & deref =
        *static_cast<const NodeDerefExpr*>(node.get());

    out.print("*(");
    write_expression(out, depth, deref.inner);
    out.print(")");
}

//------------------------------------------------------------------------------
void write_expression_ref(fmt::ostream & out, size_t depth,
                          const NodeExprPtr & node)
{
    const auto & ref =
        *static_cast<const NodeRefExpr*>(node.get());

    out.print("&(");
    write_expression(out, depth, ref.inner);
    out.print(")");
}

//------------------------------------------------------------------------------
void write_expression_cast(fmt::ostream & out, size_t depth,
                           const NodeExprPtr & node)
{
    const auto & cast_expr =
        *static_cast<const NodeCastExpr*>(node.get());

    out.print("reinterpret_cast<{}>(", convert_param(cast_expr.type, ""));
    write_expression(out, depth, cast_expr.inner);
    out.print(")");
}

//------------------------------------------------------------------------------
void write_expression(fmt::ostream & out, size_t depth,
                      const NodeExprPtr & node)
{
    // Do nothing if this expression is empty
    if(!node)
    {
        return;
    }

    switch (node->kind)
    {
        case NodeKind::FunctionCallExpr:
            return write_expression_function_call(out, depth, node);
        case NodeKind::MethodCallExpr:
            return write_expression_method_call(out, depth, node);
        case NodeKind::VarRefExpr:
            return write_expression_var_ref(out, depth, node);
        case NodeKind::DerefExpr:
            return write_expression_deref(out, depth, node);
        case NodeKind::RefExpr:
            return write_expression_ref(out, depth, node);
        case NodeKind::CastExpr:
            return write_expression_cast(out, depth, node);
        default:
            break;
    }

    assert("Shouldn't get here"); // TODO LT: Clean this up
}

//------------------------------------------------------------------------------
void write_function_body(fmt::ostream & out, const NodePtr & node)
{
    const NodeFunction & function =
        *static_cast<const NodeFunction*>(node.get());

    out.print("{}(", convert_param(function.return_type,
                                   function.name));
    write_params(out, function);
    out.print(")\n");
    out.print("{{\n");
    indent(out, 1);
    write_expression(out, 1, function.body);
    out.print("}}\n");
}

//------------------------------------------------------------------------------
void write_header(const TranslationUnit & tu)
{
    auto out = fmt::output_file(compute_c_header_path(tu.filename));

    // Write out all the records first
    for(const auto & node : tu.decls)
    {
        if (node->kind == NodeKind::Record)
        {
            write_record(out, node);
        }
    }

    // Then all the functions
    for(const auto & node : tu.decls)
    {
        if (node->kind == NodeKind::Function)
        {
            write_function(out, node);
        }
    }
}

//------------------------------------------------------------------------------
void write_source(const TranslationUnit & tu)
{
    auto out = fmt::output_file(tu.filename);

    // Write out the function definitions
    for(const auto & node : tu.decls)
    {
        if (node->kind == NodeKind::Function)
        {
            write_function_body(out, node);
        }
    }
}

//------------------------------------------------------------------------------
void write_translation_unit(const TranslationUnit & tu)
{
    write_header(tu);
    write_source(tu);
}

//------------------------------------------------------------------------------
void cpp(const Root & root, size_t starting_point)
{
    assert(starting_point < root.tu.size());

    const auto size = root.tus.size();
    for(size_t i=starting_point; i < size; ++i)
    {
        const auto & tu = root.tus[i];
        write_translation_unit(tu);
    }
}
} // namespace read
} // namesapce cppmm

