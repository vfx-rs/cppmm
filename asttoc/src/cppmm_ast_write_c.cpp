//------------------------------------------------------------------------------
// vfx-rs
//------------------------------------------------------------------------------
#include "cppmm_ast_write_c.hpp"

#include "cppmm_ast.hpp"

#include "pystring.h"

#include <fmt/os.h>

#include <iostream>

#define cassert(C, M) if(!(C)) { std::cerr << M << std::endl; abort(); }

namespace cppmm
{
class Root;

namespace write
{

enum class Access : uint32_t {
    Private = 0,
    Public
};

enum class Place : uint32_t {
    Header = 0,
    Source 
};

//------------------------------------------------------------------------------
static void indent(fmt::ostream & out, const size_t depth)
{
    for(size_t i=0; i!= depth; ++i)
    {
        out.print("    ");
    }
}

//------------------------------------------------------------------------------
std::string compute_c_header_path(const std::string & path,
                                  const char * extension)
{
    std::string _;
    std::string result;
    pystring::os::path::splitext(result, _, path);
    result += extension;

    return result;
}

std::string convert_param(const NodeTypePtr & field,
                          const std::string & name);

//------------------------------------------------------------------------------
std::string convert_builtin_param(const NodeTypePtr & t,
                                  const std::string & name)
{
    const char * const_ = t->const_ ? " const " : " ";
    return fmt::format("{}{}{}", t->type_name, const_, name);
}

//------------------------------------------------------------------------------
std::string convert_record_param(const NodeTypePtr & t,
                                 const std::string & name)
{
    const char * const_ = t->const_ ? " const " : " ";
    return fmt::format("{}{}{}", t->type_name, const_, name);
}

//------------------------------------------------------------------------------
std::string convert_pointer_param(const NodeTypePtr & t,
                                  const std::string & name)
{
    auto p = static_cast<const NodePointerType*>(t.get());

    switch(p->pointer_kind)
    {
        case PointerKind::Pointer:
            return convert_param(p->pointee_type,
                                 fmt::format("* {}", name));
        case PointerKind::Reference:
            return convert_param(p->pointee_type,
                                 fmt::format("& {}", name));
        default:
            break;
    }

    return "";
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

    cassert(false, "Shouldn't get here"); // TODO LT: Clean this up
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

    constexpr auto sizeof_byte = 8;
    const auto align_in_bytes = record.align / sizeof_byte;

    out.print("typedef struct {}_s {{\n", record.name);
    write_fields(out, record);
    out.print("}} __attribute__((aligned({}))) {};\n",
              align_in_bytes, // TODO LT: Only force alignment if 'align' attribute is on it.
              record.name);
}

//------------------------------------------------------------------------------
void write_record_forward_decl(fmt::ostream & out, const NodePtr & node)
{
    const NodeRecord & record = *static_cast<const NodeRecord*>(node.get());
    out.print("typedef struct {0}_s {0};\n", record.name);
}

//------------------------------------------------------------------------------
void write_params(fmt::ostream & out, const NodeFunction & function)
{
    if(!function.params.empty())
    {
        auto param_count = function.params.size();
            out.print("\n");
            indent(out, 1);
            out.print("{}", convert_param(function.params[0].type,
                                          function.params[0].name));
        for(size_t i=1; i < param_count; ++i)
        {
            out.print("\n");
            indent(out, 1);
            out.print(", {}", convert_param(function.params[i].type,
                                            function.params[i].name));
        }
    }
}

//------------------------------------------------------------------------------
void write_function_dcl(fmt::ostream & out, const NodePtr & node, Access access)
{
    const NodeFunction & function =
        *static_cast<const NodeFunction*>(node.get());

    const bool private_ = (access == Access::Private);
    if(private_ == function.private_)
    {
        out.print("\n");
        out.print("{}(", convert_param(function.return_type,
                                       function.name));
        write_params(out, function);
        out.print(");\n");
    }
}

//------------------------------------------------------------------------------
void write_expression(fmt::ostream & out, size_t depth,
                      const NodeExprPtr & node);

//------------------------------------------------------------------------------
void write_function_call_arguments(fmt::ostream & out,
                                   size_t depth,
                                   const NodeFunctionCallExpr & function_call)
{
    if(function_call.args.empty())
    {
        out.print("()");
    }
    else
    {
        // start
        out.print("(");

        // First argument
        write_expression(out, depth, function_call.args[0]);

        // All the others
        for(size_t i=1; i < function_call.args.size(); ++i)
        {
            out.print(", ");
            write_expression(out, depth, function_call.args[i]);
        }

        // start
        out.print(")");
    }
}

//------------------------------------------------------------------------------
void write_expression_function_call(fmt::ostream & out,
                                    size_t depth,
                                    const NodeExprPtr & node)
{
    const auto & function_call =
        *static_cast<const NodeMethodCallExpr*>(node.get());

    out.print("{}", function_call.name);
    write_function_call_arguments(out, depth, function_call);
}

//------------------------------------------------------------------------------
void write_expression_method_call(fmt::ostream & out,
                                  size_t depth, const NodeExprPtr & node)
{
    const auto & method_call =
        *static_cast<const NodeMethodCallExpr*>(node.get());

    out.print("(");
    write_expression(out, depth, method_call.this_);
    out.print(") -> {}", method_call.name);
    write_function_call_arguments(out, depth, method_call);
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

    out.print("{}_cast<{}>(", cast_expr.cast_kind,
                              convert_param(cast_expr.type, ""));
    write_expression(out, depth, cast_expr.inner);
    out.print(")");
}

//------------------------------------------------------------------------------
void write_expression_placement_new(fmt::ostream & out, size_t depth,
                                    const NodeExprPtr & node)
{
    const auto & plcmt_new_expr =
        *static_cast<const NodePlacementNewExpr*>(node.get());

    out.print("new (");
    write_expression(out, depth, plcmt_new_expr.address);
    out.print(") ");
    write_expression(out, depth, plcmt_new_expr.constructor);
}

//------------------------------------------------------------------------------
void write_expression_return(fmt::ostream & out, size_t depth,
                             const NodeExprPtr & node)
{
    const auto & return_expr =
        *static_cast<const NodeReturnExpr*>(node.get());

    out.print("return ");
    write_expression(out, depth, return_expr.inner);
}

//------------------------------------------------------------------------------
void write_expression_var_decl(fmt::ostream & out, size_t depth,
                               const NodeExprPtr & node)
{
    const auto & var_decl_expr =
        *static_cast<const NodeVarDeclExpr*>(node.get());

    out.print("{}", convert_param(var_decl_expr.var_type,
                                  var_decl_expr.var_name));
}

//------------------------------------------------------------------------------
void write_expression_block(fmt::ostream & out, size_t depth,
                               const NodeExprPtr & node)
{
    const auto & block_expr =
        *static_cast<const NodeBlockExpr*>(node.get());

    for(auto & i : block_expr.expressions)
    {
        indent(out, depth);
        write_expression(out, depth + 1, i);
        out.print(";\n");
    }
}

//------------------------------------------------------------------------------
void write_expression_assign(fmt::ostream & out, size_t depth,
                             const NodeExprPtr & node)
{
    const auto & assign_expr =
        *static_cast<const NodeAssignExpr*>(node.get());

    
    write_expression(out, depth + 1, assign_expr.lhs);
    out.print(" = ");
    write_expression(out, depth + 1, assign_expr.rhs);
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
        case NodeKind::PlacementNewExpr:
            return write_expression_placement_new(out, depth, node);
        case NodeKind::ReturnExpr:
            return write_expression_return(out, depth, node);
        case NodeKind::VarDeclExpr:
            return write_expression_var_decl(out, depth, node);
        case NodeKind::BlockExpr:
            return write_expression_block(out, depth, node);
        case NodeKind::AssignExpr:
            return write_expression_assign(out, depth, node);
        default:
            break;
    }

    cassert(false, "write expression Shouldn't get here"); // TODO LT: Clean this up
}

//------------------------------------------------------------------------------
void write_function_bdy(fmt::ostream & out, const NodePtr & node, Access access)
{
    const NodeFunction & function =
        *static_cast<const NodeFunction*>(node.get());

    const bool private_ = (access == Access::Private);
    if(private_ == function.private_)
    {
        out.print("\n");
        if(function.inline_)
        {
            out.print("inline ");
        }

        out.print("{}(", convert_param(function.return_type,
                                       function.name));
        write_params(out, function);
        out.print(")\n");
        out.print("{{\n");
        write_expression(out, 1, function.body);
        out.print("}}\n");
    }
}

//------------------------------------------------------------------------------
void write_function(fmt::ostream & out, const NodePtr & node, Access access,
                    Place place)
{
    const NodeFunction & function =
        *static_cast<const NodeFunction*>(node.get());

    if(function.inline_)
    {
        switch(place)
        {
        case Place::Header:
            write_function_bdy(out, node, access);
            return;
        default:
            return;
        }
    }
    else
    {
        switch(place)
        {
        case Place::Header:
            write_function_dcl(out, node, access);
            return;
        case Place::Source:
            write_function_bdy(out, node, access);
            return;
        }
    }
}


//------------------------------------------------------------------------------
void write_header_includes(fmt::ostream & out, const TranslationUnit & tu)
{
    for(const auto & i : tu.header_includes)
    {
        out.print("{}\n", i);
    }

    out.print("\n");
}

//------------------------------------------------------------------------------
void write_source_includes(fmt::ostream & out, const TranslationUnit & tu)
{
    if(!tu.private_header_filename.empty())
    {
        out.print("{}\n", tu.private_header_filename);
    }

    out.print("\n");

    for(const auto & i : tu.source_includes)
    {
        out.print("{}\n", i);
    }

    out.print("\n");
}

//------------------------------------------------------------------------------
void write_private_header(const TranslationUnit & tu)
{
    auto out =
        fmt::output_file(compute_c_header_path(tu.filename, "private_.h"));

    out.print("#pragma once\n");

    if(!tu.header_filename.empty())
    {
        out.print("{}\n\n", tu.header_filename);
    }

    out.print("\n");

    for(const auto & i : tu.private_includes)
    {
        out.print("{}\n", i);
    }

    // Then all the private functions
    for(const auto & node : tu.decls)
    {
        if (node->kind == NodeKind::Function)
        {
            out.print("\n");
            write_function(out, node, Access::Private, Place::Header);
        }
    }
}

//------------------------------------------------------------------------------
void write_header(const TranslationUnit & tu)
{
    auto out = fmt::output_file(compute_c_header_path(tu.filename, ".h"));

    out.print("#pragma once\n");


    // Write all the includes needed in the header file
    write_header_includes(out, tu);

    // Extern "C"
    out.print("#ifdef __cplusplus\nextern \"C\" {{\n#endif\n");

    // Write out all the forward declarations
    for(const auto & node : tu.forward_decls)
    {
        if (node->kind == NodeKind::Record)
        {
            write_record_forward_decl(out, node);
        }
    }

    // Write out all the records first
    for(const auto & node : tu.decls)
    {
        if (node->kind == NodeKind::Record)
        {
            write_record(out, node);
        }
    }

    // Then all the public functions
    for(const auto & node : tu.decls)
    {
        if (node->kind == NodeKind::Function)
        {
            out.print("\n");
            write_function(out, node, Access::Public, Place::Header);
        }
    }

    // Extern "C"
    out.print("#ifdef __cplusplus\n}}\n#endif\n");
}

//------------------------------------------------------------------------------
void write_source(const TranslationUnit & tu)
{
    auto out = fmt::output_file(tu.filename);

    // Write out the source includes
    write_source_includes(out, tu);

    // Write out the function definitions
    for(const auto & node : tu.decls)
    {
        if (node->kind == NodeKind::Function)
        {
            write_function(out, node, Access::Public, Place::Source);
        }
    }
}

//------------------------------------------------------------------------------
void write_translation_unit(const TranslationUnit & tu)
{
    write_header(tu);
    write_private_header(tu);
    write_source(tu);
}

//------------------------------------------------------------------------------
void c(const Root & root, size_t starting_point)
{
    cassert(starting_point < root.tus.size(), "starting point is out of range");

    const auto size = root.tus.size();
    for(size_t i=starting_point; i < size; ++i)
    {
        const auto & tu = root.tus[i];
        write_translation_unit(*tu);
    }
}
} // namespace read
} // namesapce cppmm
