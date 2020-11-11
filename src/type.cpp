#include <cassert>
#include <iostream>

#include <fmt/format.h>

#include "record.hpp"
#include "type.hpp"


namespace cppmm {

bool Type::is_pod() const {
    if (is_builtin || is_enum || is_func_proto) {
        return true;
    }

    if (record) {
        return record->is_pod();
    }

    assert(false && "TYPE POD FALLTHROUGH");
    return false;
}
} // namespace cppmm

namespace fmt {

std::ostream& operator<<(std::ostream& os, const cppmm::TypeKind& kind) {
    switch (kind) {
    case cppmm::TypeKind::OpaquePtr:
        os << "OpaquePtr";
        break;
    case cppmm::TypeKind::OpaqueBytes:
        os << "OpaqueBytes";
        break;
    case cppmm::TypeKind::ValueType:
        os << "ValueType";
        break;
    default:
        os << "Unknown";
        break;
    }
    return os;
}

} // namespace fmt
