#include <cassert>
#include <iostream>

#include <fmt/format.h>

#include "record.hpp"
#include "type.hpp"
#include "enum.hpp"


namespace cppmm {

Builtin builtin_int{};

bool Type::is_pod() const {
    if (var.is<Builtin>() || var.is<Enum>() || var.is<FuncProto>()) {
        return true;
    }

    if (const Record* record = var.cast_or_null<Record>()) {
        return record->is_pod();
    }

    assert(false && "TYPE POD FALLTHROUGH");
    return false;
}
} // namespace cppmm

namespace fmt {

std::ostream& operator<<(std::ostream& os, const cppmm::RecordKind& kind) {
    switch (kind) {
    case cppmm::RecordKind::OpaquePtr:
        os << "OpaquePtr";
        break;
    case cppmm::RecordKind::OpaqueBytes:
        os << "OpaqueBytes";
        break;
    case cppmm::RecordKind::ValueType:
        os << "ValueType";
        break;
    default:
        os << "Unknown";
        break;
    }
    return os;
}

} // namespace fmt
