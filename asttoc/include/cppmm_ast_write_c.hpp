//------------------------------------------------------------------------------
// vfx-rs
//------------------------------------------------------------------------------
#pragma once

#include <cstddef>

namespace cppmm {
class Root;

namespace write {
void c(const char* project_name, const Root& root, size_t starting_point);
} // namespace write
} // namespace cppmm
