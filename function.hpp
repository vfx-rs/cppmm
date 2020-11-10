#pragma once

#include <set>
#include <string>
#include <vector>

#include "param.hpp"

namespace cppmm {

struct Function {

    Function() {}

    Function(std::string cpp_name, std::string c_name, Param return_type,
             std::vector<Param> params, std::string comment,
             std::vector<std::string> namespaces);

    std::string cpp_name;
    std::string c_name;
    Param return_type;
    std::vector<Param> params;
    std::string comment;
    std::string cpp_qname;
    std::string c_qname;

    std::string
    get_declaration(std::set<std::string>& includes,
                    std::set<std::string>& casts_macro_invocations) const;

    std::string get_definition(const std::string& declaration) const;
};

} // namespace cppmm
