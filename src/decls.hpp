#pragma once

#include "enum.hpp"
#include "exports.hpp"
#include "function.hpp"
#include "method.hpp"
#include "record.hpp"
#include "vector.hpp"

#include <clang/AST/DeclCXX.h>
#include <clang/AST/Type.h>

#include <unordered_map>

namespace cppmm {

struct File {
    std::unordered_map<std::string, Function> functions;
    std::unordered_map<std::string, Record> records;
};

using FileMap = std::unordered_map<std::string, File>;
using RecordMap = std::unordered_map<std::string, Record>;
using EnumMap = std::unordered_map<std::string, Enum>;
using VectorMap = std::unordered_map<std::string, Vector>;

extern FileMap files;
extern RecordMap records;
extern EnumMap enums;
extern VectorMap vectors;

bool is_builtin(const clang::QualType& qt);

bool is_recordpointer(const clang::QualType& qt);

QualifiedType process_qualified_type(const clang::QualType& qt);
Param process_param_type(const std::string& param_name,
                         const clang::QualType& qt);

Record* process_record(const clang::CXXRecordDecl* record);

Enum* process_enum(const clang::EnumDecl* enum_decl);
Param process_pointee_type(const std::string& param_name,
                           const clang::QualType& qt);
Function process_function(const clang::FunctionDecl* function,
                          const ExportedFunction& ex_function,
                          std::vector<std::string> namespaces);
Method process_method(const clang::CXXMethodDecl* method,
                      const ExportedMethod& ex_method, const Record* record);

Record* find_record(const std::string& c_qname);
Enum* find_enum(const std::string& c_qname);
File* insert_file(const std::string& c_qname, const File& file);
File* find_file(const std::string& c_qname);

} // namespace cppmm
