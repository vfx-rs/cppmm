#pragma once

#include <vector>
#include <string>

namespace cppmm {

struct Enum {
    std::string cpp_name;
    std::vector<std::string> namespaces;
    std::string c_name;
    std::string filename;
    std::vector<std::pair<std::string, uint64_t>> enumerators;
    std::string cpp_qname;
    std::string c_qname;

    std::string get_declaration() const;
};

}
