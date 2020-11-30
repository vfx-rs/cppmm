#include "enum.hpp"

#include <spdlog/fmt/fmt.h>

namespace cppmm {
std::string Enum::get_declaration(std::vector<std::string>& pretty_defines) const {
    std::string declarations;

    pretty_defines.push_back(fmt::format("#define {} {}", c_pretty_name, c_qname));

    declarations += fmt::format("enum {} {{\n", c_qname);

    for (const auto& ecd : enumerators) {
        std::string qname = c_pretty_name + "_" + ecd.first;
        declarations += fmt::format("    {} = {},\n", qname, ecd.second);
    }

    declarations += "};\n\n";
    return declarations;
}
} // namespace cppmm
