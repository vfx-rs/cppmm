#include "enum.hpp"

#include <fmt/format.h>

namespace cppmm {
std::string Enum::get_declaration() const {
    std::string declarations;
    declarations += fmt::format("enum {} {{\n", c_name);

    for (const auto& ecd : enumerators) {
        std::string qname = c_name + "_" + ecd.first;
        declarations += fmt::format("    {} = {},\n", qname, ecd.second);
    }

    declarations += "};\n\n";
    return declarations;
}
} // namespace cppmm
