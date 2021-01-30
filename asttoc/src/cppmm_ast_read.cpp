
//------------------------------------------------------------------------------
// vfx-rs
//------------------------------------------------------------------------------
#include "cppmm_ast_read.hpp"
#include "json.hh"

Root read_json(std::istream & input) {
    nlohmann::json j;
    input >> j;
}
