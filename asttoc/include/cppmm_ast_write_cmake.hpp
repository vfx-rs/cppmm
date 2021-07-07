//------------------------------------------------------------------------------
// vfx-rs
//------------------------------------------------------------------------------
#pragma once

#include <cstddef>
#include <string>
#include <vector>

namespace cppmm {
class Root;
using Libs = std::vector<std::string>;
using LibDirs = std::vector<std::string>;

namespace write {
void cmake(const char* project_name, const Root& root, size_t starting_point,
           const Libs& libs, const LibDirs& lib_dirs, int version_major,
           int version_minor, int version_patch, const char* base_project_name);

void cmake_modern(const char* project_name, const Root& root,
                  size_t starting_point,
                  const std::vector<std::string>& find_packages,
                  const std::vector<std::string>& target_link_libraries,
                  int version_major, int version_minor, int version_patch,
                  const char* base_project_name);
} // namespace write
} // namespace cppmm
