#pragma once
#include "pystring.h"

namespace cppmm {

inline bool is_stl_version_namespace(const std::string& name) {
    return name == "std::__1";
}

inline std::string prune_stl(const std::string& str) {
    return pystring::replace(str, "std::__1", "std");
}

} // namespace cppmm
