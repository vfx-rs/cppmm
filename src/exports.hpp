#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include <clang/AST/DeclCXX.h>

#include "attributes.hpp"
#include "type.hpp"

namespace cppmm {

struct ExportedFunction {
    ExportedFunction(const clang::FunctionDecl* function,
                     std::string filename,
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
};

struct ExportedSpecialization {
    std::string record_cpp_qname;
    std::string alias;
    std::vector<std::string> template_args;
};

struct ExportedEnum {
    std::string cpp_name;
    std::vector<std::string> namespaces;
    std::string c_name;
    std::string filename;
    std::string c_qname;
    std::string cpp_qname;
};

struct ExportedClass {
    std::string name;
    std::string filename;
    std::vector<std::string> namespaces;
    std::vector<ExportedMethod> methods;
    std::vector<ExportedMethod> rejected_methods;
};

struct ExportedFile {
    std::string name;
    std::vector<std::string> classes;
    std::vector<ExportedFunction> functions;
    std::unordered_map<std::string, std::vector<std::vector<std::string>>> function_specializations;
    std::unordered_map<std::string, std::vector<std::unordered_map<std::string,std::string>>> spec_named_args;
    std::vector<ExportedFunction> rejected_functions;
    std::unordered_map<std::string, ExportedRecord*> records;
    std::unordered_map<std::string, ExportedEnum*> enums;
};

using ExportedFileMap = std::unordered_map<std::string, ExportedFile>;
using ExportedClassMap = std::unordered_map<std::string, ExportedClass>;
using ExportedRecordMap = std::unordered_map<std::string, ExportedRecord>;
using ExportedSpecMap = std::unordered_map<std::string, std::vector<ExportedSpecialization>>;
using ExportedEnumMap = std::unordered_map<std::string, ExportedEnum>;

extern ExportedFileMap ex_files;
extern ExportedClassMap ex_classes;
extern ExportedRecordMap ex_records;
extern ExportedSpecMap ex_specs;
extern ExportedEnumMap ex_enums;

// ExportedRecord* find_ex_record(const std::string& c_qname);
// ExportedRecord* insert_ex_record(const std::string& c_qname,
//                              const ExportedRecord& ex_record);
// ExportedClass* find_ex_class(const std::string& c_qname);
// ExportedClass* insert_ex_class(const std::string& c_qname,
//                              const ExportedClass& ex_class);
// ExportedEnum* insert_ex_enum(const std::string& c_qname,
//                              const ExportedEnum& ex_enum);
// ExportedEnum* find_ex_enum(const std::string& c_qname);
// ExportedFile* insert_ex_file(const std::string& filename,
//                              const ExportedFile& ex_file);
// ExportedFile* find_ex_file(const std::string& filename);
// const std::unordered_map<std::string, ExportedFile>& get_ex_files();
// const std::unordered_map<std::string, ExportedClass>& get_ex_classes();
// const std::unordered_map<std::string, ExportedEnum>& get_ex_enums();

bool operator==(const ExportedFunction& a, const ExportedFunction& b);
bool operator==(const ExportedMethod& a, const ExportedMethod& b);

} // namespace cppmm

namespace fmt {
std::ostream& operator<<(std::ostream& os,
                         const cppmm::ExportedFunction& method);
std::ostream& operator<<(std::ostream& os, const cppmm::ExportedMethod& method);
std::ostream& operator<<(std::ostream& os, const cppmm::ExportedRecord& type);
} // namespace fmt
