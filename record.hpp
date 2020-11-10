#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "param.hpp"
#include "method.hpp"

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
};

}
