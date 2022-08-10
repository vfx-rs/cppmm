//------------------------------------------------------------------------------
// vfx-rs
//------------------------------------------------------------------------------
#pragma once

#include <cstddef>
#include <string>
#include <vector>

namespace cppmm {
class Root;

namespace rust_sys {
void write(const char* out_dir, const char* project_name, const char* license,
           const char* c_dir, const std::string& c_cmake_dir,
           const Root& root, size_t starting_point,
           const std::vector<std::string>& libs,
           const std::vector<std::string>& lib_dirs,
           const std::vector<std::string>& authors,
           int version_major, int version_minor, int version_patch);
} // namespace rust_sys
} // namespace cppmm
