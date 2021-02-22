//------------------------------------------------------------------------------
// vfx-rs
//------------------------------------------------------------------------------
#include "cppmm_ast.hpp"
#include "cppmm_ast_add_c.hpp"
#include "cppmm_ast_read.hpp"
#include "cppmm_ast_write_c.hpp"
#include "cppmm_ast_write_cmake.hpp"

#include "filesystem.hpp"

#include <fstream>
#include <iostream>

#include <llvm/Support/CommandLine.h>

namespace cl = llvm::cl;
namespace fs = ghc::filesystem;

void generate(const char* input, const char* output) {
    const std::string input_directory = input;
    const std::string output_directory = output;

    // Read the json ast
    auto cpp_ast = cppmm::read::json(input_directory);

    // Add the c translation units
    auto starting_point = cpp_ast.tus.size();
    cppmm::transform::add_c(output_directory, cpp_ast);

    // Save out only the c translation units
    cppmm::write::c(cpp_ast, starting_point);

    // Create a cmake file as well
    cppmm::write::cmake(cpp_ast, starting_point);
}

static cl::opt<std::string> opt_in_dir(cl::Positional, cl::desc("<input dir>"),
                                       cl::Required);

static cl::opt<std::string> opt_out_dir(
    "o", cl::desc("Directory under which output C binding project will be "
                  "written. Defaults to current directory if not specified."));

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

    // attempt to create the output directory if it doesn't exist
    if (!fs::is_directory(out_dir) && !fs::create_directories(out_dir)) {
        std::cerr << "Could not create output directory " << out_dir << "\n";
        return -1;
    }

    generate(opt_in_dir.c_str(), out_dir.c_str());

    return 0;
}
