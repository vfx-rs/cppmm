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
    std::ifstream input_file;
    input_file.open("/Volumes/src/cppmm/test/imath/ref/imath_vec.json");

    auto cpp_ast = cppmm::read::json(input_file);
    auto full_ast = cppmm::transform::add_c(cpp_ast);

    cppmm::write::cpp(full_ast);

    return 0;
}
