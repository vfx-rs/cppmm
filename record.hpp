#pragma once

#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "method.hpp"
#include "param.hpp"

namespace cppmm {
struct Record {
    std::string cpp_name;
    std::vector<std::string> namespaces;
    std::string c_name;
    TypeKind kind;
    std::string filename;
    std::vector<cppmm::Param> fields;
    std::unordered_map<std::string, Method> methods;
    size_t size;
    size_t alignment;
    std::string cpp_qname;
    std::string c_qname;

    bool is_pod() const {
        for (const auto& p : fields) {
            if (!p.qtype.is_pod()) {
                return false;
            }
        }

        return true;
    }

    std::string create_casts() const;

    std::string get_opaqueptr_constructor_declaration(
        const std::string& c_method_name,
        const std::vector<std::string>& param_decls) const;

    std::string get_opaqueptr_constructor_body(
        const std::vector<std::string>& call_params) const;

    std::string get_valuetype_constructor_body(
        const std::vector<std::string>& call_params) const;

    std::string get_method_declaration(
        const Method& method, std::set<std::string>& includes,
        std::set<std::string>& casts_macro_invocations) const;

    std::string get_method_definition(const Method& method,
                                      const std::string& declaration) const;
};

} // namespace cppmm
