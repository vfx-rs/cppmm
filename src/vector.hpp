#pragma once

#include <string>
#include <vector>
#include <spdlog/fmt/fmt.h>

#include "type.hpp"


namespace cppmm {

struct Vector {
    QualifiedType element_type;
    std::string c_qname;

    std::string create_casts() const {
        return fmt::format("CPPMM_DEFINE_POINTER_CASTS(std::vector<{}>, {});\n",
                           element_type.type.get_cpp_qname(), c_qname);
    }
};

} // namespace cppmm
