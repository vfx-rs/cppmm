//------------------------------------------------------------------------------
// vfx-rs
//------------------------------------------------------------------------------
#pragma once

#include <cstddef>

namespace cppmm {
class Root;

namespace write {
void c(const char* project_name, const Root& root, size_t starting_point,
       const char* output_dir);
void cerrors(const char* output_dir, Root& root, size_t starting_point,
             const char* project_name);
} // namespace write
} // namespace cppmm
