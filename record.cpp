#include "record.hpp"
#include "namespaces.hpp"

#include <fmt/format.h>

namespace cppmm {

std::string Record::create_casts() const {
    // std::string cpp_type =
    //     prefix_from_namespaces(namespaces, "::") + cpp_name;
    // std::string c_type =
    //     prefix_from_namespaces(namespaces, "_") + cpp_name;
    return fmt::format("CPPMM_DEFINE_POINTER_CASTS({}, {})\n", cpp_qname,
                       c_qname);
}

}
