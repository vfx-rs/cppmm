#pragma once

#include <string>
#include <vector>
#include <optional>


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

std::optional<AttrDesc> parse_attributes(std::string attr_src);
}
