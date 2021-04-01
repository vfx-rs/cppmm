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
void cmake(const Root& root, size_t starting_point, const Libs& libs,
           const LibDirs& lib_dirs);
} // namespace write
} // namespace cppmm
