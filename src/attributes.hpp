#pragma once

#include <string>
#include <vector>
#include "optional.hpp"


namespace cppmm {

struct AttrDesc {
    enum Kind {
        Ignore,
        Rename,
        Manual,
        OpaquePtr,
        OpaqueBytes,
        ValueType,
    };

    std::string params;
    Kind kind;
};

tl::optional<AttrDesc> parse_attributes(std::string attr_src);
}
