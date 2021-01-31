//------------------------------------------------------------------------------
// vfx-rs
//------------------------------------------------------------------------------
//#include "cereal/cereal.hpp"
#include "cppmm_ast.hpp"
#include "cppmm_ast_read.hpp"

#include <fstream>

int main()
{
    std::ifstream input_file;
    input_file.open("/Volumes/src/cppmm/test/imath/ref/imath_vec.json");

    auto ast = cppmm::read_json(input_file);

    return 0;
}
