#include <fmt/format.h>

#include "param.hpp"
#include "namespaces.hpp"
#include "type.hpp"
#include "record.hpp"
#include "enum.hpp"

namespace cppmm {
std::string Param::create_c_declaration() const {
    std::string result;
    if (qtype.type.name == "basic_string") {
        if (qtype.is_const) {
            result += "const char*";
        } else {
            result += "char*";
        }
    } else if (qtype.type.name == "string_view") {
        result += "const char*";
    } else if (qtype.type.name == "const char *") {
        result += "const char*";
    } else if (qtype.type.name == "void *") {
        result += "void*";
    } else {
        if (qtype.is_const) {
            result += "const ";
        }
        if (qtype.type.enm) {
            result += "int";
        } else {
            result += prefix_from_namespaces(qtype.type.namespaces, "_") +
                      qtype.type.name;
            if (qtype.is_ptr || qtype.is_ref || qtype.is_uptr) {
                result += "*";
            }
        }
    }

    result += " ";
    result += name;

    return result;
}

std::string Param::create_c_call() const {
    std::string result;
    if (qtype.is_ref && !(qtype.type.name == "basic_string" ||
                          qtype.type.name == "string_view")) {
        if (qtype.requires_cast) {
            result = fmt::format("*to_cpp({})", name);
        } else {
            result = fmt::format("*{}", name);
        }
    } else {
        if (qtype.type.record &&
            (qtype.type.record->kind == cppmm::TypeKind::ValueType ||
             qtype.type.record->kind == cppmm::TypeKind::OpaqueBytes)) {
            // need to bit-cast this
            result = fmt::format(
                "bit_cast<{}>({})",
                prefix_from_namespaces(qtype.type.record->namespaces, "::") +
                    qtype.type.name,
                name);
        } else if (qtype.type.enm) {
            result = fmt::format(
                "({}){}",
                prefix_from_namespaces(qtype.type.enm->namespaces, "::") +
                    qtype.type.enm->cpp_name,
                name);
        } else if (qtype.requires_cast) {
            result = fmt::format("to_cpp({})", name);
        } else {
            result = name;
        }
    }
    return result;
}
}
