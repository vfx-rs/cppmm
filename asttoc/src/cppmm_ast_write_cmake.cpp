//------------------------------------------------------------------------------
// vfx-rs
//------------------------------------------------------------------------------
#include "cppmm_ast_write_cmake.hpp"

#include "cppmm_ast.hpp"

#include "pystring.h"

#include <fmt/os.h>

#include <iostream>
#include <set>

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
namespace write {

//------------------------------------------------------------------------------
static void indent(fmt::ostream& out, const size_t depth) {
    for (size_t i = 0; i != depth; ++i) {
        out.print("    ");
    }
}

const std::string compute_out_include_path(const std::string& filename) {
    return fs::path(filename).parent_path();
}

const std::string compute_cmakefile_path(const std::string& filename) {
    return fs::path(filename).parent_path() / "CMakeLists.txt";
}

//------------------------------------------------------------------------------
void cmake(const char* project_name, const Root& root, size_t starting_point,
           const Libs& libs, const LibDirs& lib_dirs, int version_major,
           int version_minor, int version_patch,
           const char* base_project_name) {
    expect(starting_point < root.tus.size(),
           "starting point ({}) is out of range ({})", starting_point,
           root.tus.size());

    auto cmakefile_path =
        compute_cmakefile_path(root.tus[starting_point]->filename);

    auto out = fmt::output_file(cmakefile_path);

    // Minimum version
    out.print("cmake_minimum_required(VERSION 3.5)\n");
    out.print("project({} VERSION {}.{}.{})\n", project_name, version_major,
              version_minor, version_patch);
    out.print("set(CMAKE_CXX_STANDARD 14 CACHE STRING \"\")\n");

    // Library
    std::set<std::string> include_paths;

    const auto size = root.tus.size();
    out.print("set(SOURCES\n");
    for (size_t i = starting_point; i < size; ++i) {
        const auto& tu = root.tus[i];

        // Source files are in a 'src' subdirectory
        indent(out, 1);
        std::string head, tail;
        pystring::os::path::split(head, tail, tu->filename);
        std::string filename = pystring::os::path::join("src", tail);
        out.print("{}\n", filename);

        // Add all the include paths
        for (auto& i : tu->include_paths) {
            include_paths.insert(i);
        }
    }
    indent(out, 1);
    out.print("{}\n", fmt::format("src/{}-errors.cpp", base_project_name));
    out.print(")\n");

    out.print("set(LIBNAME {}-{}_{})\n", project_name, version_major,
              version_minor);
    out.print("add_library(${{LIBNAME}} STATIC ${{SOURCES}})\n");
    out.print("add_library(${{LIBNAME}}-shared SHARED ${{SOURCES}})\n");

    // Add the include path of the output headers
    // include_paths.insert(compute_out_include_path("./"));
    include_paths.insert("include");

    // Include directories
    for (auto& include_path : include_paths) {
        out.print("target_include_directories(${{LIBNAME}} PRIVATE {})\n",
                  include_path);
        out.print(
            "target_include_directories(${{LIBNAME}}-shared PRIVATE {})\n",
            include_path);
    }

    // Add the libraries
    for (auto& lib : libs) {
        auto lib_var = std::string("LIB_") + pystring::upper(lib);

        out.print("find_library ( {} NAMES {} PATHS", lib_var, lib);
        for (auto& lib_dir : lib_dirs) {
            out.print(" {}", lib_dir);
        }
        out.print(")\n");
        out.print("target_link_libraries (${{LIBNAME}} ${{{}}})\n", lib_var);
        out.print("target_link_libraries (${{LIBNAME}}-shared ${{{}}})\n",
                  lib_var);
    }

    // add install command for rust cmake
    out.print(
        "install(TARGETS ${{LIBNAME}} DESTINATION ${{CMAKE_INSTALL_PREFIX}})");
}

//------------------------------------------------------------------------------
void cmake_modern(const char* project_name, const Root& root,
                  size_t starting_point,
                  const std::vector<std::string>& find_packages,
                  const std::vector<std::string>& target_link_libraries,
                  int version_major, int version_minor, int version_patch,
                  const char* base_project_name) {
    expect(starting_point < root.tus.size(),
           "starting point ({}) is out of range ({})", starting_point,
           root.tus.size());

    auto cmakefile_path =
        compute_cmakefile_path(root.tus[starting_point]->filename);

    auto out = fmt::output_file(cmakefile_path);

    // Minimum version
    out.print("cmake_minimum_required(VERSION 3.5)\n");
    out.print("project({} VERSION {}.{}.{})\n", project_name, version_major,
              version_minor, version_patch);
    out.print("set(CMAKE_CXX_STANDARD 14 CACHE STRING \"\")\n");

    // Library
    std::set<std::string> include_paths;

    const auto size = root.tus.size();
    out.print("set(SOURCES\n");
    for (size_t i = starting_point; i < size; ++i) {
        const auto& tu = root.tus[i];

        // For now we assume the output source code is in the same
        // folder as the CMakeLists.txt file
        indent(out, 1);
        out.print("{}\n", fs::path(tu->filename).filename().c_str());

        // Add all the include paths
        for (auto& i : tu->include_paths) {
            include_paths.insert(i);
        }
    }
    indent(out, 1);
    out.print("{}\n", fmt::format("{}-errors.cpp", base_project_name));
    out.print(")\n");

    out.print("set(LIBNAME {}-{}_{})\n", project_name, version_major,
              version_minor);
    out.print("add_library(${{LIBNAME}} STATIC ${{SOURCES}})\n");
    out.print("add_library(${{LIBNAME}}-shared SHARED ${{SOURCES}})\n");

    // Add the include path of the output headers
    include_paths.insert(compute_out_include_path("./"));

    // Include directories
    for (auto& include_path : include_paths) {
        out.print("target_include_directories(${{LIBNAME}} PRIVATE {})\n",
                  include_path);
        out.print(
            "target_include_directories(${{LIBNAME}}-shared PRIVATE {})\n",
            include_path);
    }

    // Add the libraries
    for (const auto& pkg : find_packages) {
        out.print("find_package({} REQUIRED)\n", pkg);
    }

    for (auto& lib : target_link_libraries) {
        out.print("target_link_libraries(${{LIBNAME}} {})\n", lib);
        out.print("target_link_libraries(${{LIBNAME}}-shared {})\n", lib);
    }

    // add install command for rust cmake
    out.print(
        "install(TARGETS ${{LIBNAME}} DESTINATION ${{CMAKE_INSTALL_PREFIX}})");
}

} // namespace write
} // namespace cppmm
