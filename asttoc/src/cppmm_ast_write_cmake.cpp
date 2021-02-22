//------------------------------------------------------------------------------
// vfx-rs
//------------------------------------------------------------------------------
#include "cppmm_ast_write_cmake.hpp"

#include "cppmm_ast.hpp"

#include "pystring.h"

#include <fmt/os.h>

#include <iostream>

#define cassert(C, M) if(!(C)) { std::cerr << M << std::endl; abort(); }

namespace cppmm
{
namespace write
{

#if 0
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
#endif

//------------------------------------------------------------------------------
void cmake(const Root & root, size_t starting_point)
{
#if 0
    cassert(starting_point < root.tus.size(), "starting point is out of range");

    const auto size = root.tus.size();
    for(size_t i=starting_point; i < size; ++i)
    {
        const auto & tu = root.tus[i];
        write_translation_unit(*tu);
    }
#endif
}

} // namespace write
} // namesapce cppmm
