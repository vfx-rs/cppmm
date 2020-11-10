#include "method.hpp"
#include "namespaces.hpp"

namespace cppmm {

Method::Method(std::string cpp_name, std::string c_name, Param return_type,
               std::vector<Param> params, std::string comment,
               std::vector<std::string> namespaces, bool is_const,
               bool is_static, bool is_constructor, bool is_copy_constructor,
               bool is_copy_assignment, bool is_operator,
               bool is_conversion_operator, std::string op)
    : Function(cpp_name, c_name, return_type, params, comment, namespaces),
      is_const(is_const), is_static(is_static), is_constructor(is_constructor),
      is_copy_constructor(is_copy_constructor),
      is_copy_assignment(is_copy_assignment), is_operator(is_operator),
      is_conversion_operator(is_conversion_operator), op(op) {}

} // namespace cppmm
