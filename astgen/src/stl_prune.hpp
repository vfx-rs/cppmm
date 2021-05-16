#pragma once
#include "pystring.h"

namespace cppmm {

inline bool is_stl_version_namespace(const std::string& name) {
    return (name == "std::__1") || (name == "std::__cxx11");
}

inline std::string prune_stl(const std::string& str) {
    return pystring::replace(pystring::replace(str, "std::__1", "std"),
                             "std::__cxx11", "std");
}

} // namespace cppmm
