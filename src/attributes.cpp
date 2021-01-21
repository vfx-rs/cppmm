#include "attributes.hpp"

#include "pystring.h"

#include <spdlog/fmt/fmt.h>
#include <spdlog/spdlog.h>

namespace cppmm {

namespace ps = pystring;

tl::optional<AttrDesc> parse_attributes(std::string attr_src) {
    // fmt::print("Got attr_src {}\n", attr_src);
    std::vector<std::string> toks;
    ps::split(attr_src, toks, ":");
    // fmt::print("toks: [{}]\n", ps::join(", ", toks));
    if (toks.size() == 0 || toks[0] != "cppmm") {
        return tl::nullopt;
    }

    if (toks[1] == "ignore") {
        return AttrDesc{{}, AttrDesc::Kind::Ignore};
    } else if (toks[1] == "manual") {
        return AttrDesc{{}, AttrDesc::Kind::Manual};
    } else if (toks[1] == "rename") {
        return AttrDesc{toks[2], AttrDesc::Kind::Rename};
    } else if (toks[1] == "opaqueptr") {
        return AttrDesc{{}, AttrDesc::Kind::OpaquePtr};
    } else if (toks[1] == "opaquebytes") {
        return AttrDesc{{}, AttrDesc::Kind::OpaqueBytes};
    } else if (toks[1] == "valuetype") {
        return AttrDesc{{}, AttrDesc::Kind::ValueType};
    }

    SPDLOG_ERROR("Could not parse attribute '{}'", attr_src);

    return tl::nullopt;
}

}
