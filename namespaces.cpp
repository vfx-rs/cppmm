#include <unordered_map>

#include <fmt/format.h>

#include "pystring.h"

#include "namespaces.hpp"

namespace cppmm {

namespace ps = pystring;

std::unordered_map<std::string, std::string> namespace_renames;

void add_namespace_rename(const std::string& from, const std::string& to) {
    namespace_renames[from] = to;
}

const std::string& rename_namespace(const std::string& in) {
    if (namespace_renames.find(in) != namespace_renames.end()) {
        return namespace_renames[in];
    } else {
        return in;
    }
}

const std::string
prefix_from_namespaces(const std::vector<std::string>& cpp_namespaces,
                       const std::string& sep) {
    std::string prefix;
    if (cpp_namespaces.size() != 0) {
        std::vector<std::string> namespaces;
        namespaces.reserve(cpp_namespaces.size());
        for (const auto& ns : cpp_namespaces) {
            namespaces.push_back(rename_namespace(ns));
        }
        prefix = fmt::format("{}{}{}", ps::join(sep, namespaces), sep, prefix);
    }

    return prefix;
}

bool match_namespaces(const std::vector<std::string>& a,
                      const std::vector<std::string>& b) {
    if (a.size() != b.size()) {
        return false;
    }
    for (int i = 0; i < a.size(); ++i) {
        if (rename_namespace(a[i]) != rename_namespace(b[i])) {
            return false;
        }
    }
    return true;
}

}
