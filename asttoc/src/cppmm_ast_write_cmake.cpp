//------------------------------------------------------------------------------
// vfx-rs
//------------------------------------------------------------------------------
#include "cppmm_ast_write_cmake.hpp"

#include "cppmm_ast.hpp"

#include "pystring.h"

#include <fmt/os.h>

#include <iostream>
#include <set>

#define cassert(C, M) if(!(C)) { std::cerr << M << std::endl; abort(); }

#include "filesystem.hpp"

namespace fs = ghc::filesystem;

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

/*
cmake_minimum_required(VERSION 3.5)

add_subdirectory(fmt)

add_executable(asttoc
  src/main.cpp
  src/pystring.cpp
  src/cppmm_ast_read.cpp
  src/cppmm_ast_add_c.cpp
  src/cppmm_ast_write_c.cpp
  src/cppmm_ast_write_cmake.cpp
)

target_include_directories(asttoc PRIVATE include)
target_include_directories(asttoc PRIVATE fmt/include)
target_include_directories(asttoc PRIVATE ${LLVM_INCLUDE_DIRS})

target_link_libraries(asttoc fmt LLVMSupport)
*/

//------------------------------------------------------------------------------
static void indent(fmt::ostream & out, const size_t depth)
{
    for(size_t i=0; i!= depth; ++i)
    {
        out.print("    ");
    }
}

const std::string compute_out_include_path(const std::string & filename)
{
    return fs::path(filename).parent_path();
}

const std::string compute_cmakefile_path(const std::string & filename)
{
    return fs::path(filename).parent_path() / "CMakeLists.txt";
}

//------------------------------------------------------------------------------
void cmake(const Root & root, size_t starting_point, const Libs & libs,
           const LibDirs & lib_dirs)
{
    cassert(starting_point < root.tus.size(), "starting point is out of range");
    auto cmakefile_path =
        compute_cmakefile_path(root.tus[starting_point]->filename);

    auto project_name = "mm_binding";

    //std::cerr << cmakefile_path << std::endl;

    auto out = fmt::output_file(cmakefile_path);

    // Minimum version
    out.print("cmake_minimum_required(VERSION 3.5)\n");

    // Library    
    std::set<std::string> include_paths;

    out.print("add_library({}\n", project_name);
    const auto size = root.tus.size();
    for(size_t i=starting_point; i < size; ++i)
    {
        const auto & tu = root.tus[i];

        indent(out, 1);
        out.print("{}\n", tu->filename);

        // Add all the include paths
        for(auto & i: tu->include_paths)
        {
            include_paths.insert(i);
        }
    }
    out.print(")\n");

    // Add the include path of the output headers
    include_paths.insert(compute_out_include_path("./"));

    // Include directories
    for(auto & include_path: include_paths)
    {
        out.print("target_include_directories({} PRIVATE {})\n", project_name,
                   include_path);
    }
}

} // namespace write
} // namesapce cppmm
