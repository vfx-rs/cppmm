#include "exports.hpp"
#include "namespaces.hpp"

#include "pystring.h"

#include <unordered_map>

namespace cppmm {

std::unordered_map<std::string, cppmm::ExportedFile> ex_files;
std::unordered_map<std::string, cppmm::ExportedClass> ex_classes;
std::unordered_map<std::string, cppmm::ExportedRecord> ex_records;
std::unordered_map<std::string, cppmm::ExportedEnum> ex_enums;

ExportedFunction::ExportedFunction(const clang::FunctionDecl* function,
                                   std::vector<AttrDesc> attrs,
                                   std::vector<std::string> namespaces)
    : attrs(attrs), namespaces(namespaces) {
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

ExportedRecord* find_ex_record(const std::string& c_qname) {
    auto it = ex_records.find(c_qname);
    if (it == ex_records.end()) {
        return nullptr;
    } else {
        return &(it->second);
    }
}

ExportedRecord* insert_ex_record(const std::string& c_qname,
                             const ExportedRecord& ex_record) {
    ex_records[c_qname] = ex_record;
    return &ex_records[c_qname];
}

ExportedClass* find_ex_class(const std::string& c_qname) {
    auto it = ex_classes.find(c_qname);
    if (it == ex_classes.end()) {
        return nullptr;
    } else {
        return &(it->second);
    }
}

ExportedClass* insert_ex_class(const std::string& c_qname,
                             const ExportedClass& ex_class) {
    ex_classes[c_qname] = ex_class;
    return &ex_classes[c_qname];
}

ExportedEnum* find_ex_enum(const std::string& c_qname) {
    auto it = ex_enums.find(c_qname);
    if (it == ex_enums.end()) {
        return nullptr;
    } else {
        return &(it->second);
    }
}

ExportedEnum* insert_ex_enum(const std::string& c_qname,
                             const ExportedEnum& ex_enum) {
    ex_enums[c_qname] = ex_enum;
    return &ex_enums[c_qname];
}

ExportedFile* find_ex_file(const std::string& c_qname) {
    auto it = ex_files.find(c_qname);
    if (it == ex_files.end()) {
        return nullptr;
    } else {
        return &(it->second);
    }
}

ExportedFile* insert_ex_file(const std::string& filename,
                             const ExportedFile& ex_file) {
    ex_files[filename] = ex_file;
    return &ex_files[filename];
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
