//------------------------------------------------------------------------------
// vfx-rs
//------------------------------------------------------------------------------
#include "cppmm_ast.hpp"
#include "cppmm_ast_add_c.hpp"
#include "cppmm_ast_read.hpp"
#include "cppmm_ast_write_c.hpp"
#include "cppmm_ast_write_cmake.hpp"
#include "cppmm_ast_write_rustsys.hpp"

#include "filesystem.hpp"
#include "pystring.h"

#include <fstream>
#include <iostream>

#include <llvm/Support/CommandLine.h> // TODO: consider https://github.com/jarro2783/cxxopts to remove clang dep

namespace cl = llvm::cl;
namespace fs = ghc::filesystem;

static cl::opt<std::string> opt_in_dir(cl::Positional, cl::desc("<input dir>"),
                                       cl::Required);

static cl::opt<std::string> opt_out_dir(
    "o", cl::desc("Directory under which output C binding project will be "
                  "written. Defaults to current directory if not specified."));

static cl::opt<std::string> opt_rust_dir(
    "r",
    cl::desc("Directory under which output Rust-sys binding project will be "
             "written. Defaults to current directory if not specified."));

static cl::opt<std::string> opt_project_name(
    "p", cl::desc("Name for the project. This will determine the name of the "
                  "generated C library and the rust crate"));

static cl::list<std::string>
    opt_lib("l", cl::desc("Library that bindings link to."), cl::ZeroOrMore);

static cl::list<std::string>
    opt_lib_dir("L", cl::desc("Directories you can find libraries in."),
                cl::ZeroOrMore);

template <typename T> std::vector<std::string> to_vector(const T& t) {
    std::vector<std::string> result;
    for (auto& i : t) {
        result.push_back(i);
    }

    return result;
}

void generate(const char* input, const char* project_name, const char* output,
              const char* rust_output, const cppmm::Libs& libs,
              const cppmm::LibDirs& lib_dirs) {
    const std::string input_directory = input;
    const std::string output_directory = output;

    // Read the json ast
    auto cpp_ast = cppmm::read::json(input_directory);

    // Add the c translation units
    auto starting_point = cpp_ast.tus.size();
    cppmm::transform::add_c(output_directory, cpp_ast);

    // Save out only the c translation units
    cppmm::write::c(project_name, cpp_ast, starting_point);

    // Create a cmake file as well
    cppmm::write::cmake(project_name, cpp_ast, starting_point, libs, lib_dirs);

    std::string cwd = fs::current_path().string();
    std::string c_dir = pystring::os::path::abspath(output_directory, cwd);

    cppmm::rust_sys::write(rust_output, project_name, c_dir.c_str(), cpp_ast,
                           starting_point, libs, lib_dirs);
}

int main(int argc, char** argv) {
    cl::ParseCommandLineOptions(
        argc, argv,
        " Generates a C binding project from input JSON AST output by astgen");

    // Grab the output directory from the options, defaulting to $CWD if not
    // specified.
    fs::path out_dir = fs::current_path();
    if (opt_out_dir != "") {
        out_dir = fs::path(opt_out_dir.c_str());
    }

    fs::path rust_dir = fs::current_path();
    if (opt_out_dir != "") {
        rust_dir = fs::path(opt_rust_dir.c_str());
    }
    fs::path rust_src_dir = rust_dir / "src";

    std::string project_name;
    if (opt_project_name != "") {
        project_name = opt_project_name;
    } else {
        std::cerr << "Must supply a project name with the -p flag\n";
        return -3;
    }

    // attempt to create the output directory if it doesn't exist
    if (!fs::is_directory(out_dir) && !fs::create_directories(out_dir)) {
        std::cerr << "Could not create output directory " << out_dir << "\n";
        return -1;
    }

    if (!fs::is_directory(rust_dir) && !fs::create_directories(rust_dir)) {
        std::cerr << "Could not create Rust output directory " << rust_dir
                  << "\n";
        return -2;
    }

    if (!fs::is_directory(rust_src_dir) &&
        !fs::create_directories(rust_src_dir)) {
        std::cerr << "Could not create Rust src directory " << rust_src_dir
                  << "\n";
        return -2;
    }

    auto libs = to_vector(opt_lib);
    auto lib_dirs = to_vector(opt_lib_dir);
    generate(opt_in_dir.c_str(), project_name.c_str(), out_dir.c_str(),
             rust_dir.c_str(), libs, lib_dirs);

    return 0;
}
