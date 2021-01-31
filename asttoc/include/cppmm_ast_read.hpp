//------------------------------------------------------------------------------
// vfx-rs
//------------------------------------------------------------------------------
#pragma once
#include <istream>
#include "cppmm_ast.hpp"

namespace cppmm
{

Root read_json(std::istream & input);

} // namesapce cppmm
