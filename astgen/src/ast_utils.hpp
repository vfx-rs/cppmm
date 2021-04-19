#pragma once

#include "clang/AST/Decl.h"
#include "clang/AST/DeclCXX.h"
#include "clang/AST/DeclTemplate.h"

#include <string>

namespace cppmm {
std::vector<std::string> get_attrs(const clang::Decl* decl);
std::string strip_name_kinds(std::string s);
std::string get_record_name(const clang::CXXRecordDecl* crd);
std::string get_namespace_path(const clang::DeclContext* dc);
std::string mangle_decl(const clang::TagDecl* crd);
std::string mangle_type(const clang::QualType& qt);
std::vector<std::string>
mangle_template_args(const clang::TemplateArgumentList& args);
std::string get_comment(const clang::Decl* decl);
std::string get_comment_base64(const clang::Decl* decl);
bool is_noexcept(const clang::FunctionDecl* fd);
} // namespace cppmm
