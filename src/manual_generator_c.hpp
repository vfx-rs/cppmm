#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "filesystem.hpp"

namespace fs = ghc::filesystem;

namespace cppmm {

int generate_manual(
    const fs::path& output_dir,
    const std::vector<std::string>& manual_dir_paths,
    const std::unordered_map<std::string, std::string>& path_manual_path_map);

} // namespace cppmm
