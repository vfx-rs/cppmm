//------------------------------------------------------------------------------
// vfx-rs
//------------------------------------------------------------------------------
//#include "cereal/cereal.hpp"
#include "cppmm_ast.hpp"
#include "cppmm_ast_read.hpp"
#include "cppmm_ast_write.hpp"
#include "cppmm_ast_add_c.hpp"

#include <fstream>

int main()
{
    const std::string output_directory = "out/";

    std::ifstream input_file;
    input_file.open("/Volumes/src/cppmm/test/imath/ref/imath_vec.json");

    // Read the json ast
    auto cpp_ast = cppmm::read::json(input_file);

    // Add the c translation units
    auto starting_point = cpp_ast.tus.size();
    cppmm::transform::add_c(output_directory, cpp_ast);

    // Save out only the c translation units
    cppmm::write::cpp(cpp_ast, starting_point);

    return 0;
}
