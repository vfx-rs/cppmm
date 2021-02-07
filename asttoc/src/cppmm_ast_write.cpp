//------------------------------------------------------------------------------
// vfx-rs
//------------------------------------------------------------------------------
#include "cppmm_ast_write.hpp"

#include "cppmm_ast.hpp"

#include "pystring.h"

#include <fmt/os.h>
#include <cassert>

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
    //out.print("Don't {}", "Panic");
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

