//------------------------------------------------------------------------------
// vfx-rs
//------------------------------------------------------------------------------
#include "cppmm_ast.hpp"
#include "cppmm_ast_read.hpp"
#include "cppmm_ast_write.hpp"
#include "cppmm_ast_add_c.hpp"

#include <fstream>

void generate(const char * input, const char * output)
{
    const std::string input_directory = input;
    const std::string output_directory = output;

    // Read the json ast
    auto cpp_ast = cppmm::read::json(input_directory);

    // Add the c translation units
    auto starting_point = cpp_ast.tus.size();
    cppmm::transform::add_c(output_directory, cpp_ast);

    // Save out only the c translation units
    cppmm::write::cpp(cpp_ast, starting_point);
}

int main()
{
    generate("../test/imath/ref", "out");
    //generate("../test/std/ref", "out");
    //generate("../test/oiio/ref", "out");

    return 0;
}
