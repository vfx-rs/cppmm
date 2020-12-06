#pragma once

#include <set>
#include <string>
#include <vector>

#include "param.hpp"

namespace cppmm {

struct Function {

    Function(std::string cpp_name, std::string c_name,
             QualifiedType return_type, std::vector<Param> params,
             std::string comment, std::vector<std::string> namespaces,
             std::string filename, std::vector<std::string> template_args);

    std::string cpp_name;
    std::string c_name;
    QualifiedType return_type;
    std::vector<Param> params;
    std::string comment;
    std::vector<std::string> namespaces;
    std::string cpp_qname;
    std::string c_qname;
    std::string filename; //< file where this function is declared
    std::string c_pretty_name;

    std::string
    get_declaration(std::set<std::string>& includes,
                    std::set<std::string>& casts_macro_invocations,
                    std::vector<std::string>& pretty_defines) const;

    std::string get_definition(const std::string& declaration) const;
};

#if 0 
std::string
get_return_string_ref_body(const Function& function,
                           const std::string& call_prefix,
                           const std::vector<std::string>& call_params);

std::string
get_return_string_copy_body(const Function& function,
                            const std::string& call_prefix,
                            const std::vector<std::string>& call_params);

#endif

std::string
get_return_valuetype_body(const Function& function,
                          const std::string& call_prefix,
                          const std::vector<std::string>& call_params);

std::string
get_return_opaquebytes_body(const Function& function,
                            const std::string& call_prefix,
                            const std::vector<std::string>& call_params);

std::string
get_return_opaqueptr_body(const Function& function,
                          const std::string& call_prefix,
                          const std::vector<std::string>& call_params);

std::string
get_return_uniqueptr_body(const Function& function,
                          const std::string& call_prefix,
                          const std::vector<std::string>& call_params);

std::string
get_return_builtin_body(const Function& function,
                        const std::string& call_prefix,
                        const std::vector<std::string>& call_params);

std::string get_return_void_body(const Function& function,
                                 const std::string& call_prefix,
                                 const std::vector<std::string>& call_params);

} // namespace cppmm
