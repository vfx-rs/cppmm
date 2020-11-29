#include "enum.hpp"

#include <spdlog/fmt/fmt.h>

namespace cppmm {
std::string Enum::get_declaration() const {
    std::string declarations;
    declarations += fmt::format("enum {} {{\n", c_qname);

    for (const auto& ecd : enumerators) {
        std::string qname = c_qname + "_" + ecd.first;
        declarations += fmt::format("    {} = {},\n", qname, ecd.second);
    }

    declarations += "};\n\n";
    return declarations;
}
} // namespace cppmm
