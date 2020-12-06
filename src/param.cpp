#include "param.hpp"
#include "enum.hpp"
#include "namespaces.hpp"
#include "record.hpp"
#include "type.hpp"

#include "pystring.h"

#include <spdlog/fmt/fmt.h>

namespace cppmm {
std::string Param::create_c_declaration() const {
    return fmt::format("{} {}", qtype.create_c_declaration(), name);
}

std::string Param::create_c_call() const {
    std::string result;
    if (qtype.is_ref && !(qtype.type.name == "string_view")) {
        if (qtype.requires_cast) {
            result = fmt::format("*to_cpp({})", name);
        } else {
            result = fmt::format("*{}", name);
        }
    } else {
        if (const Record* record = qtype.type.var.cast_or_null<Record>()) {
            if (record->kind == cppmm::RecordKind::ValueType ||
                record->kind == cppmm::RecordKind::OpaqueBytes) {
                // need to bit-cast this
                result = fmt::format(
                    "bit_cast<{}>({})",
                    prefix_from_namespaces(record->namespaces, "::") +
                        qtype.type.name,
                    name);
            } else {
                result = fmt::format("to_cpp({})", name);
            }
        } else if (const Enum* enm = qtype.type.var.cast_or_null<Enum>()) {
            result = fmt::format("({}){}",
                                 prefix_from_namespaces(enm->namespaces, "::") +
                                     enm->cpp_name,
                                 name);
        } else if (qtype.requires_cast) {
            result = fmt::format("to_cpp({})", name);
        } else {
            result = name;
        }
    }
    return result;
}
} // namespace cppmm
