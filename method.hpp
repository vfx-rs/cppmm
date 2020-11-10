#pragma once

#include <string>
#include <vector>

#include "param.hpp"

namespace cppmm {

struct Method {

    std::string cpp_name;
    std::string c_name;
    bool is_const = false;
    bool is_static = false;
    Param return_type;
    std::vector<Param> params;
    std::string comment;
    bool is_constructor = false;
    bool is_copy_constructor = false;
    bool is_copy_assignment = false;
    bool is_operator = false;
    bool is_conversion_operator = false;
    std::string op;
    std::string cpp_qname;
    std::string c_qname;
};

}
