#pragma once

#include <string>
#include <vector>

#include "param.hpp"
#include "function.hpp"

namespace cppmm {

struct Method : public Function {
    Method(std::string cpp_name, std::string c_name, QualifiedType return_type,
           std::vector<Param> params, std::string comment,
           std::vector<std::string> namespaces, bool is_const, bool is_static,
           bool is_constructor, bool is_copy_constructor,
           bool is_copy_assignment, bool is_operator,
           bool is_conversion_operator, std::string op,
           std::vector<std::string> template_args);

    bool is_const = false;
    bool is_static = false;
    bool is_constructor = false;
    bool is_copy_constructor = false;
    bool is_copy_assignment = false;
    bool is_operator = false;
    bool is_conversion_operator = false;
    std::string op;
};

} // namespace cppmm
