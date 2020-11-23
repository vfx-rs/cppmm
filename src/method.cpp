#include <iostream>

#include <fmt/format.h>
#include <fmt/ostream.h>

#include "method.hpp"
#include "namespaces.hpp"
#include "param.hpp"

#include "pystring.h"

namespace cppmm {

Method::Method(std::string cpp_name, std::string c_name, QualifiedType return_type,
               std::vector<Param> params, std::string comment,
               std::vector<std::string> namespaces, bool is_const,
               bool is_static, bool is_constructor, bool is_copy_constructor,
               bool is_copy_assignment, bool is_operator,
               bool is_conversion_operator, std::string op, std::vector<std::string> template_args)
    : Function(cpp_name, c_name, return_type, params, comment, namespaces, "", template_args),
      is_const(is_const), is_static(is_static), is_constructor(is_constructor),
      is_copy_constructor(is_copy_constructor),
      is_copy_assignment(is_copy_assignment), is_operator(is_operator),
      is_conversion_operator(is_conversion_operator), op(op) {}

} // namespace cppmm

namespace fmt {
std::ostream& operator<<(std::ostream& os, const cppmm::Method& method) {
    std::vector<std::string> param_str;
    param_str.reserve(method.params.size());
    for (const auto& p : method.params) {
        param_str.emplace_back(fmt::format("{}", p));
    }
    if (method.is_static) {
        os << "static ";
    }
    os << "auto " << method.cpp_name << "(" << pystring::join(", ", param_str)
       << ") -> " << method.return_type;
    if (method.is_const) {
        os << " const";
    }
    return os;
}

}
