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
std::string compute_c_header_path(const std::string & path)
{
    std::string _;
    std::string result;
    pystring::os::path::splitext(result, _, path);
    result += ".h";

    return result;
}

//------------------------------------------------------------------------------
void write_header(const TranslationUnit & tu)
{
    auto out = fmt::output_file(compute_c_header_path(tu.filename));
    //out.print("Don't {}", "Panic");
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

