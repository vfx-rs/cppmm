#include "exports.hpp"
#include "namespaces.hpp"

#include "pystring.h"

#include <unordered_map>

#include <spdlog/fmt/fmt.h>

namespace cppmm {

std::unordered_map<std::string, ExportedFile> ex_files;
std::unordered_map<std::string, ExportedRecord> ex_records;
std::unordered_map<std::string, ExportedEnum> ex_enums;
ExportedSpecMap ex_specs;

namespace {

std::string convert_cpp_name(const std::string& cpp_name) {
    if (cpp_name == "operator+") {
        return "op_add";
    } else if (cpp_name == "operator+=") {
        return "op_add_assign";
    } else if (cpp_name == "operator-") {
        return "op_sub";
    } else if (cpp_name == "operator-=") {
        return "op_sub_assign";
    } else if (cpp_name == "operator*") {
        return "op_mul";
    } else if (cpp_name == "operator*=") {
        return "op_mul_assign";
    } else if (cpp_name == "operator/") {
        return "op_div";
    } else if (cpp_name == "operator/=") {
        return "op_div_assign";
    } else if (cpp_name == "operator==") {
        return "op_eq";
    } else if (cpp_name == "operator!=") {
        return "op_neq";
    } else if (cpp_name == "operator<") {
        return "op_lt";
    } else {
        auto pos = cpp_name.find("operator ");
        if (pos == 0) {
            // implicit conversion operator. extract the type and default to
            // "to_type" as the name
            std::string type = cpp_name.substr(9, std::string::npos);
            return fmt::format("to_{}", type);
        }

        // if there's no special cases, just return the c++ name
        return cpp_name;
    }
}

}

ExportedFunction::ExportedFunction(const clang::FunctionDecl* function,
                                   std::string filename,
                                   std::vector<AttrDesc> attrs,
                                   std::vector<std::string> namespaces)
    : filename(filename), attrs(attrs), namespaces(namespaces) {
    function = function->getCanonicalDecl();
    cpp_name = function->getNameAsString();
    return_type = function->getReturnType().getCanonicalType().getAsString();
    for (const auto& p : function->parameters()) {
        // if (p->getType()->isTemplateTypeParmType()) {
        //     fmt::print("    {} is TTPT\n", p->getNameAsString());
        // }
        params.push_back(p->getType().getCanonicalType().getAsString());
    }
    is_static = function->isStatic();

    cpp_qname = prefix_from_namespaces(namespaces, "::") + cpp_name;
    c_name = convert_cpp_name(cpp_name);
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
    os << "struct " << type.cpp_qname << " {" << std::endl;

    for (const auto& ex_method: type.methods) {
        os << "    " << ex_method << std::endl;
    }

    os << "}";
    if (type.kind == cppmm::RecordKind::OpaquePtr) {
        os << " CPPMM_OPAQUEPTR";
    } else if (type.kind == cppmm::RecordKind::OpaqueBytes) {
        os << " CPPMM_OPAQUEBYTES";
    } else if (type.kind == cppmm::RecordKind::ValueType) {
        os << " CPPMM_VALUETYPE";
    }
    os << ";" << std::endl;
    return os;
}

} // namespace fmt
