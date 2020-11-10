#pragma once

#include <string>
#include <vector>

#include "param.hpp"

namespace cppmm {

struct Function {
    std::string cpp_name;
    std::string c_name;
    Param return_type;
    std::vector<Param> params;
    std::string comment;
    std::vector<std::string> namespaces;
    std::string cpp_qname;
    std::string c_qname;
};


}
