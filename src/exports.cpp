#include "exports.hpp"
#include "namespaces.hpp"

#include "pystring.h"

#include <unordered_map>

namespace cppmm {

std::unordered_map<std::string, ExportedFile> ex_files;
std::unordered_map<std::string, ExportedClass> ex_classes;
std::unordered_map<std::string, ExportedRecord> ex_records;
std::unordered_map<std::string, ExportedEnum> ex_enums;
ExportedSpecMap ex_specs;

ExportedFunction::ExportedFunction(const clang::FunctionDecl* function,
                                   std::string filename,
                                   std::vector<AttrDesc> attrs,
                                   std::vector<std::string> namespaces)
    : filename(filename), attrs(attrs), namespaces(namespaces) {
    function = function->getCanonicalDecl();
    cpp_name = function->getNameAsString();
    return_type = function->getReturnType().getCanonicalType().getAsString();
    for (const auto& p : function->parameters()) {
        params.push_back(p->getType().getCanonicalType().getAsString());
    }
    is_static = function->isStatic();

    c_name = cpp_name;
    for (const auto& attr : attrs) {
        if (attr.kind == AttrDesc::Kind::Rename) {
            c_name = attr.params;
        }
    }
}

bool operator==(const ExportedFunction& a, const ExportedFunction& b) {
    return a.cpp_name == b.cpp_name && a.return_type == b.return_type &&
           a.params == b.params && a.is_static == b.is_static &&
           match_namespaces(a.namespaces, b.namespaces);
}

bool operator==(const ExportedMethod& a, const ExportedMethod& b) {
    return a.cpp_name == b.cpp_name && a.return_type == b.return_type &&
           a.params == b.params && a.is_const == b.is_const &&
           a.is_static == b.is_static;
}

const std::unordered_map<std::string, ExportedFile>& get_ex_files() {
    return ex_files;
}

const std::unordered_map<std::string, ExportedClass>& get_ex_classes() {
    return ex_classes;
}

const std::unordered_map<std::string, ExportedEnum>& get_ex_enums() {
    return ex_enums;
}

} // namespace cppmm

namespace fmt {
std::ostream& operator<<(std::ostream& os,
                         const cppmm::ExportedFunction& method) {
    if (method.is_static) {
        os << "static ";
    }
    auto ns = cppmm::prefix_from_namespaces(method.namespaces, "::");
    os << "auto " << ns << method.cpp_name << "("
       << pystring::join(", ", method.params) << ") -> " << method.return_type;
    return os;
}

std::ostream& operator<<(std::ostream& os,
                         const cppmm::ExportedMethod& method) {
    if (method.is_static) {
        os << "static ";
    }
    os << "auto " << method.cpp_name << "("
       << pystring::join(", ", method.params) << ") -> " << method.return_type;
    if (method.is_const) {
        os << " const";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const cppmm::ExportedRecord& type) {
    os << "struct " << type.c_name;
    if (type.kind == cppmm::RecordKind::OpaquePtr) {
        os << " //< opaque ptr";
    } else if (type.kind == cppmm::RecordKind::OpaqueBytes) {
        os << " //< opaque bytes";
    } else if (type.kind == cppmm::RecordKind::ValueType) {
        os << " //< value type";
    }
    return os;
}

} // namespace fmt
