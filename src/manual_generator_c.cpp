#include <fstream>
#include <iostream>
#include <memory>

// #include <fmt/printf.h>

#include "manual_generator_c.hpp"

namespace fs = ghc::filesystem;

namespace cppmm {
int generate_manual(
    const fs::path& output_dir,
    const std::vector<std::string>& manual_dir_paths,
    const std::unordered_map<std::string, std::string>& path_manual_path_map) {
    std::unordered_map<std::string, std::string> manual_path_map;
    manual_path_map.reserve(path_manual_path_map.size());

    // Reverse the relationship from path -> manual_path to manual_path -> path.
    // The idea in the code where this gets called is we'll likely know about
    // the path and not what is its associated manual path.
    for (const auto& item : path_manual_path_map) {
        manual_path_map[item.second] = item.first;
    }

    std::unique_ptr<char> data(new char[1024]);

    for (const fs::path& manual_path : manual_dir_paths) {
        const auto item = manual_path_map.find(manual_path);

        if (item == manual_path_map.end()) {
            std::cout << "Could not find path from manual path " << manual_path << std::endl;
            return 1;
        }

        fs::path path = item->second;
        fs::path src_path = output_dir / path.filename();

        std::fstream src_file;
        src_file.open(src_path, std::ios::app);

        if (!src_file) {
            std::cout << "Could not open source path " << src_path << " for appending" << std::endl;
            return 1;
        }

        std::fstream manual_file;
        manual_file.open(manual_path, std::ios::in);

        if (!manual_file) {
            std::cout << "Could not open manual path " << manual_path << " for reading" << std::endl;
            return 1;
        }

        src_file << "\n";
        src_file << "// "
                    "----------------------------------------------------------"
                    "------------------------------\n";
        src_file << "// Manually created methods. These will need to be added "
                    "to the appropriate header by hand.\n";
        src_file << "// "
                    "----------------------------------------------------------"
                    "------------------------------\n\n";

        while (true) {
            int count = manual_file.readsome(data.get(), 1024);

            if (count == 0) {
                break;
            }

            if (!manual_file) {
                std::cout << "Could not read from manual path " << manual_path << std::endl;
                return 1;
            }

            src_file.write(data.get(), count);

            if (!src_file) {
                std::cout << "Could not write to source path " << src_path << std::endl;
                return 1;
            }
        }

        manual_file.close();
        src_file.close();
    }

    return 0;
}
} // namespace cppmm
