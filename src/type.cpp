#include <cassert>
#include <iostream>

#include <fmt/format.h>

#include "enum.hpp"
#include "namespaces.hpp"
#include "record.hpp"
#include "type.hpp"
#include "vector.hpp"

#include "pystring.h"

namespace cppmm {

Builtin builtin_int{};
String builtin_string{};

bool Type::is_pod() const {
    if (var.is<Builtin>() || var.is<Enum>() || var.is<FuncProto>()) {
        return true;
    }

    if (var.is<Vector>()) {
        return false;
    }

    if (const Record* record = var.cast_or_null<Record>()) {
        return record->is_pod();
    }

    assert(false && "TYPE POD FALLTHROUGH");
    return false;
}

const char* Type::get_c_qname() const {
    if (const Builtin* builtin = var.cast_or_null<Builtin>()) {
        return name.c_str();
    } else if (const Record* record = var.cast_or_null<Record>()) {
        return record->c_qname.c_str();
    } else if (const Vector* vector = var.cast_or_null<Vector>()) {
        return vector->c_qname.c_str();
    } else if (const String* str = var.cast_or_null<String>()) {
        return "string";
    } else if (const Enum* enm = var.cast_or_null<Enum>()) {
        return enm->c_qname.c_str();
    }
    return "UNHANDLED";
}

std::string Type::get_cpp_qname() const {
    if (const Builtin* builtin = var.cast_or_null<Builtin>()) {
        return name;
    } else if (const Record* record = var.cast_or_null<Record>()) {
        return record->cpp_qname;
    } else if (const Vector* vector = var.cast_or_null<Vector>()) {
        return fmt::format("std::vector<{}>",
                           vector->element_type.type.get_cpp_qname());
    } else if (const String* str = var.cast_or_null<String>()) {
        return "std::string";
    } else if (const Enum* enm = var.cast_or_null<Enum>()) {
        return enm->cpp_qname;
    }
    return "UNHANDLED";
}

// FIXME: really need to swap the types out at a lower level and store the
// original type as well as the converted type rather than doing all this
// string replacement shenanigans
std::string QualifiedType::create_c_declaration() const {
    std::string result;
    if (type.name == "basic_string") {
        if (is_const) {
            result += "const char*";
        } else {
            result += "char*";
        }
    } else if (type.name == "string_view") {
        result += "const char*";
    } else if (type.name == "const char *") {
        result += "const char*";
    } else if (type.name == "void *") {
        result += "void*";
    } else {
        if (is_const) {
            result += "const ";
        }
        if (type.var.is<Enum>()) {
            result += "int";
        } else if (const Vector* vec = type.var.cast_or_null<Vector>()) {
            result += fmt::format("{}", vec->c_qname);
            if (is_ptr || is_ref || is_uptr) {
                result += "*";
            }
        } else {
            // result += prefix_from_namespaces(type.namespaces, "_") + type.name;
            result += type.get_c_qname();
            if (is_ptr || is_ref || is_uptr) {
                result += "*";
            }
        }
    }

    return result;
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

std::ostream& operator<<(std::ostream& os, const cppmm::QualifiedType& qtype) {
    if (qtype.is_const) {
        os << "const ";
    }
    auto& ns = qtype.type.namespaces;
    if (ns.size()) {
        os << pystring::join("::", ns) << "::";
    }
    os << qtype.type.name;
    if (qtype.is_ptr) {
        os << "*";
    } else if (qtype.is_ref) {
        os << "&";
    }
    return os;
}

} // namespace fmt
