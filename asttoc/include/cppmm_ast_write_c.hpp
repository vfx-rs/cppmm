//------------------------------------------------------------------------------
// vfx-rs
//------------------------------------------------------------------------------
#pragma once

#include <cstddef>
#include <string>

namespace cppmm {
class Root;

namespace write {
void c(const char* project_name, const Root& root, size_t starting_point,
       const char* output_dir, const std::string& api_prefix);
void cerrors(const char* output_dir, Root& root, size_t starting_point,
             const char* project_name, const std::string& api_prefix);
std::string capiexport(const char* output_dir, Root& root, size_t starting_point,
             const char* project_name);
} // namespace write
} // namespace cppmm
