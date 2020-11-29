#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include <clang/AST/DeclCXX.h>

#include "attributes.hpp"
#include "type.hpp"

#include "pystring.h"

#include <spdlog/fmt/fmt.h>

namespace cppmm {

struct ExportedFunction {
    ExportedFunction(const clang::FunctionDecl* function, std::string filename,
                     std::vector<AttrDesc> attrs,
                     std::vector<std::string> namespaces = {});

    bool is_ignored() const {
        for (const auto& attr : attrs) {
            if (attr.kind == AttrDesc::Kind::Ignore)
                return true;
        }
        return false;
    }

    bool is_manual() const {
        for (const auto& attr : attrs) {
            if (attr.kind == AttrDesc::Kind::Manual)
                return true;
        }
        return false;
    }

    std::string cpp_name;
    std::string c_name; //< may be different if we rename it
    std::string return_type;
    // vector of canonical typenames that are this method's parameters.
    std::vector<std::string> params;
    std::vector<AttrDesc> attrs;
    std::vector<std::string> namespaces; //< only used for free functions (ugh)
    bool is_static = false;
    std::string filename;
    std::string cpp_qname;
};

struct ExportedMethod : public ExportedFunction {
    ExportedMethod(const clang::CXXMethodDecl* method,
                   std::vector<AttrDesc> attrs)
        : ExportedFunction(clang::dyn_cast<clang::FunctionDecl>(method), "",
                           attrs) {
        is_const = method->isConst();
    }

    bool is_const = false;
};

struct ExportedRecord {
    std::string cpp_name;
    std::vector<std::string> namespaces;
    std::string c_name;
    RecordKind kind;
    std::string filename;
    std::string c_qname;
    std::string cpp_qname;
    std::string dependent_qname;
    std::vector<std::string> template_args;
    bool is_dependent;
    std::vector<ExportedMethod> methods;
    std::vector<ExportedMethod> rejected_methods;
};

struct ExportedSpecialization {
    std::string record_cpp_qname;
    std::string alias;
    std::vector<std::string> template_args;
    std::unordered_map<std::string, std::string> template_named_args;
};

struct ExportedEnum {
    std::string cpp_name;
    std::vector<std::string> namespaces;
    std::string c_name;
    std::string filename;
    std::string c_qname;
    std::string cpp_qname;
};

struct ExportedFile {
    std::string name;
    std::vector<std::string> classes;
    std::vector<ExportedFunction> functions;
    std::unordered_map<std::string, std::vector<std::vector<std::string>>>
        function_specializations;
    std::unordered_map<
        std::string, std::vector<std::unordered_map<std::string, std::string>>>
        spec_named_args;
    std::vector<ExportedFunction> rejected_functions;
    std::unordered_map<std::string, ExportedRecord*> records;
    std::unordered_map<std::string, ExportedEnum*> enums;
};

using ExportedFileMap = std::unordered_map<std::string, ExportedFile>;
using ExportedRecordMap = std::unordered_map<std::string, ExportedRecord>;
using ExportedSpecMap =
    std::unordered_map<std::string, std::vector<ExportedSpecialization>>;
using ExportedEnumMap = std::unordered_map<std::string, ExportedEnum>;

extern ExportedFileMap ex_files;
extern ExportedRecordMap ex_records;
extern ExportedSpecMap ex_specs;
extern ExportedEnumMap ex_enums;

bool operator==(const ExportedFunction& a, const ExportedFunction& b);
bool operator==(const ExportedMethod& a, const ExportedMethod& b);

} // namespace cppmm

std::ostream& operator<<(std::ostream& os,
                         const cppmm::ExportedFunction& method);
std::ostream& operator<<(std::ostream& os, const cppmm::ExportedMethod& method);

template <> struct fmt::formatter<cppmm::ExportedMethod> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.end(); }

    template <typename FormatContext>
    auto format(const cppmm::ExportedMethod& method, FormatContext& ctx) {
        if (method.is_static) {
            format_to(ctx.out(), "static ");
        }
        format_to(ctx.out(), "auto {}({}) -> {}", method.cpp_name,
                  pystring::join(", ", method.params), method.return_type);
        if (method.is_const) {
            format_to(ctx.out(), " const");
        }
        return format_to(ctx.out(), ";");
    }
};

template <> struct fmt::formatter<cppmm::ExportedRecord> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.end(); }

    template <typename FormatContext>
    auto format(const cppmm::ExportedRecord& type, FormatContext& ctx) {

        format_to(ctx.out(), "struct {} {{\n", type.cpp_qname);
        for (const auto& ex_method : type.methods) {
            format_to(ctx.out(), "    {}\n", ex_method);
        }
        format_to(ctx.out(), "}}");
        if (type.kind == cppmm::RecordKind::OpaquePtr) {
            format_to(ctx.out(), " CPPMM_OPAQUEPTR");
        } else if (type.kind == cppmm::RecordKind::OpaqueBytes) {
            format_to(ctx.out(), " CPPMM_OPAQUEBYTES");
        } else if (type.kind == cppmm::RecordKind::ValueType) {
            format_to(ctx.out(), " CPPMM_VALUETYPE");
        }
        return format_to(ctx.out(), ";");
    }
};

template <> struct fmt::formatter<cppmm::ExportedSpecialization> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.end(); }

    template <typename FormatContext>
    auto format(const cppmm::ExportedSpecialization& spec, FormatContext& ctx) {
        return format_to(ctx.out(), "using {} = {}<{}>;", spec.alias,
                         spec.record_cpp_qname,
                         pystring::join(", ", spec.template_args));
    }
};
