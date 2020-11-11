#include <algorithm>
#include <fstream>
#include <iostream>
#include <optional>
#include <unistd.h>
#include <unordered_map>

#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
// Declares llvm::cl::extrahelp.
#include "llvm/Support/CommandLine.h"

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Lex/Lexer.h"

#include <fmt/format.h>
#include <fmt/printf.h>

#include "pystring.h"

#include "attributes.hpp"
#include "enum.hpp"
#include "function.hpp"
#include "method.hpp"
#include "namespaces.hpp"
#include "param.hpp"
#include "record.hpp"
#include "type.hpp"
#include "exports.hpp"
#include "match_bindings.hpp"

using namespace clang::tooling;
using namespace llvm;
using namespace clang;
using namespace clang::ast_matchers;

namespace ps = pystring;

std::string internal_namespace_name = "OpenImageIO_v2_2";
std::string external_namespace_name = "OIIO";

namespace cppmm {

class Record;
class Enum;
class Vec;

// vector wrapper
struct Vec {
    std::string c_name;
    Type element_type;
};

struct File {
    std::unordered_map<std::string, Function> functions;
    std::unordered_map<std::string, Record> records;
};

} // namespace cppmm

// std::unordered_map<std::string, cppmm::Class> classes;
std::unordered_map<std::string, cppmm::File> files;
std::unordered_map<std::string, cppmm::Record> records;
std::unordered_map<std::string, cppmm::Enum> enums;

bool is_builtin(const QualType& qt) {
    return (qt->isBuiltinType() ||
            (qt->isPointerType() && qt->getPointeeType()->isBuiltinType()));
}

bool is_recordpointer(const QualType& qt) {
    return ((qt->isReferenceType() || qt->isPointerType()) &&
            qt->getPointeeType()->isRecordType());
}

std::string qualified_type_name(const cppmm::Type& type) {
    return cppmm::prefix_from_namespaces(type.namespaces, "::") + type.name;
}

cppmm::Param process_param_type(const std::string& param_name,
                                const QualType& qt);

cppmm::Record* process_record(const CXXRecordDecl* record) {
    std::string cpp_name = record->getNameAsString();
    std::vector<std::string> namespaces = cppmm::get_namespaces(record->getParent());

    const auto c_qname =
        cppmm::prefix_from_namespaces(namespaces, "_") + cpp_name;
    if (records.find(c_qname) != records.end()) {
        // already done this type, return
        return &records[c_qname];
    }

    auto it_ex_record = cppmm::ex_records.find(c_qname);
    if (it_ex_record == cppmm::ex_records.end()) {
        // fmt::print("WARNING: record '{}' has no export definition\n",
        // c_name);
        return nullptr;
    }

    std::vector<cppmm::Param> fields;
    for (const auto* field : record->fields()) {
        std::string field_name = field->getNameAsString();
        // fmt::print("    field: {}\n", field->getNameAsString());
        cppmm::Param field_param =
            process_param_type(field_name, field->getType());
        fields.push_back(field_param);
        // fmt::print("    {}\n", field_param);
    }

    // get size and alignment info
    // clang returns in bits so divide by 8 to get bytes
    ASTContext& ctx = record->getASTContext();
    size_t size = ctx.getTypeSize(record->getTypeForDecl()) / 8;
    size_t alignment = ctx.getTypeAlign(record->getTypeForDecl()) / 8;

    // fmt::print("Processed record {} -> {} in {}\n", cpp_name, c_qname,
    //    it_ex_record->second.filename);
    auto rec = cppmm::Record{
        .cpp_name = cpp_name,
        .namespaces = namespaces,
        .c_name = cpp_name,
        .kind = it_ex_record->second.kind,
        .filename = it_ex_record->second.filename,
        .fields = fields,
        .methods = {},
        .size = size,
        .alignment = alignment,
        .cpp_qname = cppmm::prefix_from_namespaces(namespaces, "::") + cpp_name,
        .c_qname = c_qname,
    };

    if (rec.kind == cppmm::TypeKind::ValueType && !rec.is_pod()) {
        fmt::print("ERROR: {} is valuetype but not POD\n", rec.c_qname);
        return nullptr;
    } else if (rec.kind == cppmm::TypeKind::OpaqueBytes && !rec.is_pod()) {
        fmt::print("ERROR: {} is opaquebytes but not POD\n", rec.c_qname);
        return nullptr;
    }

    records[c_qname] = rec;
    // fmt::print("MATCHED: {}\n", cpp_name);

    return &records[c_qname];
}

cppmm::Enum* process_enum(const EnumDecl* enum_decl) {
    std::string cpp_name = enum_decl->getNameAsString();
    std::vector<std::string> namespaces =
        cppmm::get_namespaces(enum_decl->getParent());
    const auto c_name = cpp_name;
    const auto cpp_qname =
        cppmm::prefix_from_namespaces(namespaces, "::") + cpp_name;
    const auto c_qname =
        cppmm::prefix_from_namespaces(namespaces, "_") + c_name;
    if (enums.find(c_qname) != enums.end()) {
        // already done this type, return
        return &enums[c_qname];
    }

    auto it_ex_enum = cppmm::ex_enums.find(c_qname);
    if (it_ex_enum == cppmm::ex_enums.end()) {
        // fmt::print("WARNING: enum '{}' has no export definition\n",
        // c_qname);
        return nullptr;
    }

    // fmt::print("Processed enum {} -> {} in {}\n", cpp_name, c_qname,
    //    it_ex_enum->second.filename);

    std::vector<std::pair<std::string, uint64_t>> enumerators;
    for (const auto& ecd : enum_decl->enumerators()) {
        enumerators.push_back(std::make_pair<std::string, uint64_t>(
            ecd->getNameAsString(), ecd->getInitVal().getLimitedValue()));
    }

    enums[c_qname] = cppmm::Enum{.cpp_name = cpp_name,
                                 .namespaces = namespaces,
                                 .c_name = c_name,
                                 .filename = it_ex_enum->second.filename,
                                 .enumerators = enumerators,
                                 .cpp_qname = cpp_qname,
                                 .c_qname = c_qname};

    // fmt::print("MATCHED: {}\n", cpp_name);

    return &enums[c_qname];
}

cppmm::Param process_pointee_type(const std::string& param_name,
                                  const QualType& qt) {
    cppmm::Param result;
    result.name = param_name;

    if (is_builtin(qt)) {
        std::string name = qt.getTypePtr()
                               ->getUnqualifiedDesugaredType()
                               ->getAs<BuiltinType>()
                               ->desugar()
                               .getAsString();

        // C++ doesn't like _Bool but we can include stdbool.h for C
        if (name == "_Bool") {
            name = "bool";
        }
        result.qtype.type = cppmm::Type{name, {}, .is_builtin = true};
        result.qtype.requires_cast = false;
    } else if (qt->isRecordType()) {
        const CXXRecordDecl* crd = qt->getAsCXXRecordDecl();
        if (crd->getNameAsString() == "unique_ptr") {
            const auto* tst = qt->getAs<TemplateSpecializationType>();
            result =
                process_pointee_type(param_name, tst->getArgs()->getAsType());
            result.qtype.is_uptr = true;
        } else if (crd->getNameAsString() == "vector") {

        } else {
            const CXXRecordDecl* crd = qt->getAsCXXRecordDecl();
            cppmm::Record* record_ptr = process_record(crd);
            if (record_ptr == nullptr) {
                // fmt::print("ERROR: could not process record for {}\n",
                //            crd->getNameAsString());
            }
            std::string type_name = crd->getNameAsString();
            result.qtype.type =
                cppmm::Type{.name = type_name,
                            .namespaces = cppmm::get_namespaces(
                                qt->getAsCXXRecordDecl()->getParent()),
                            .is_builtin = false,
                            .is_enum = false,
                            .is_func_proto = false,
                            .record = record_ptr,
                            .enm = nullptr};
            result.qtype.requires_cast =
                !(crd->getNameAsString() == "basic_string" ||
                  crd->getNameAsString() == "string_view");
        }
    } else if (qt->isEnumeralType()) {
        const auto* enum_decl = qt->getAs<EnumType>()->getDecl();
        const cppmm::Enum* enm = process_enum(enum_decl);

        result.qtype.type = cppmm::Type{.name = enm->cpp_name,
                                        .namespaces = enm->namespaces,
                                        .is_builtin = false,
                                        .is_enum = true,
                                        .is_func_proto = false,
                                        .record = nullptr,
                                        .enm = enm};
    } else {
        fmt::print("Unhandled type: {}\n", qt.getAsString());
        qt->dump();
    }

    result.qtype.is_const = qt.isConstQualified();
    return result;
}

cppmm::Param process_param_type(const std::string& param_name,
                                const QualType& qt) {
    cppmm::Param result;
    bool is_ptr = qt->isPointerType();
    bool is_ref = qt->isReferenceType();

    if (is_ptr || is_ref) {
        result = process_pointee_type(param_name, qt->getPointeeType());
        result.qtype.is_ptr = is_ptr;
        result.qtype.is_ref = is_ref;
    } else if (is_builtin(qt)) {
        result = process_pointee_type(param_name, qt);
    } else if (qt->isRecordType()) {
        result = process_pointee_type(param_name, qt);
    } else if (qt->isEnumeralType()) {
        result = process_pointee_type(param_name, qt);
    } else {
        fmt::print("ERROR unhandled param type {}\n", qt.getAsString());
        qt->dump();
    }

    return result;
}

namespace fmt {
std::ostream& operator<<(std::ostream& os, const cppmm::TypeKind& kind) {
    switch (kind) {
    case cppmm::TypeKind::OpaquePtr:
        os << "OpaquePtr";
        break;
    case cppmm::TypeKind::OpaqueBytes:
        os << "OpaqueBytes";
        break;
    case cppmm::TypeKind::ValueType:
        os << "ValueType";
        break;
    default:
        os << "Unknown";
        break;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const cppmm::Param& param) {
    if (param.qtype.is_const) {
        os << "const ";
    }
    auto& ns = param.qtype.type.namespaces;
    if (ns.size()) {
        os << ps::join("::", ns) << "::";
    }
    os << param.qtype.type.name;
    if (param.qtype.is_ptr) {
        os << "* ";
    } else if (param.qtype.is_ref) {
        os << "& ";
    } else {
        os << " ";
    }
    os << param.name;
    return os;
}

std::ostream& operator<<(std::ostream& os, const cppmm::Method& method) {
    std::vector<std::string> param_str;
    param_str.reserve(method.params.size());
    for (const auto& p : method.params) {
        param_str.emplace_back(fmt::format("{}", p));
    }
    if (method.is_static) {
        os << "static ";
    }
    os << "auto " << method.cpp_name << "(" << ps::join(", ", param_str)
       << ") -> " << method.return_type;
    if (method.is_const) {
        os << " const";
    }
    return os;
}
} // namespace fmt

std::string get_decl_comment(const Decl* decl) {
    ASTContext& ctx = decl->getASTContext();
    SourceManager& sm = ctx.getSourceManager();
    const RawComment* rc = ctx.getRawCommentForDeclNoCache(decl);
    std::string result;
    if (rc) {
        std::string raw = rc->getRawText(sm);
        // dedent lines
        std::vector<std::string> lines;
        ps::splitlines(raw, lines);
        for (auto& line : lines) {
            line = ps::strip(line);
        }

        result = ps::join("\n", lines);
    }

    return result;
}

cppmm::Function process_function(const FunctionDecl* function,
                                 const cppmm::ExportedFunction& ex_function,
                                 std::vector<std::string> namespaces) {
    std::vector<cppmm::Param> params;
    for (const auto& p : function->parameters()) {
        const auto param_name = p->getNameAsString();
        params.push_back(process_param_type(param_name, p->getType()));
    }

    std::string comment = get_decl_comment(function);

    return cppmm::Function{
        ex_function.cpp_name,
        ex_function.c_name,
        process_param_type("", function->getReturnType()),
        params,
        comment,
        namespaces,
    };
}

cppmm::Method process_method(const CXXMethodDecl* method,
                             const cppmm::ExportedMethod& ex_method,
                             const cppmm::Record* record) {
    std::vector<cppmm::Param> params;
    for (const auto& p : method->parameters()) {
        const auto param_name = p->getNameAsString();
        params.push_back(process_param_type(param_name, p->getType()));
    }

    std::string comment = get_decl_comment(method);

    bool is_constructor = false;
    bool is_copy_constructor = false;
    bool is_copy_assignment = method->isCopyAssignmentOperator();
    bool is_operator = false;
    bool is_conversion_operator = false;
    std::string op;

    if (isa<CXXConstructorDecl>(method)) {
        const auto* ctor = cast<CXXConstructorDecl>(method);
        is_constructor = true;
        is_copy_constructor = ctor->isCopyConstructor();
    } else if (ex_method.cpp_name.find("operator") == 0) {
        // we assume that clang always concatenates the operator name with the
        // symbols so we can use this to tell the difference with a conversion
        // operator. FIXME: is this true?
        std::vector<std::string> toks;
        ps::split(ex_method.cpp_name, toks);
        if (toks.size() == 1) {
            op = ex_method.cpp_name.substr(8, 100);
            is_operator = true;
            // fmt::print("Got operator '{}'\n", op);
        } else {
            op = toks[1];
            is_conversion_operator = true;
            // fmt::print("Got conversion op to '{}'\n", op);
        }
    }

    // do some parameter patching. clang ignores the parameter name for copy
    // ctor and assignment but we need one so just use "other"
    if (is_copy_constructor || is_copy_assignment) {
        params[0].name = "other";
    }

    std::vector<std::string> namespaces = record->namespaces;
    namespaces.push_back(record->c_name);

    return cppmm::Method{ex_method.cpp_name,
                         ex_method.c_name,
                         process_param_type("", method->getReturnType()),
                         params,
                         comment,
                         namespaces,
                         method->isConst(),
                         method->isStatic(),
                         is_constructor,
                         is_copy_constructor,
                         is_copy_assignment,
                         is_operator,
                         is_conversion_operator,
                         op};
}

class CppmmMatchHandler : public MatchFinder::MatchCallback {
    virtual void run(const MatchFinder::MatchResult& result) {
        if (const CXXMethodDecl* method =
                result.Nodes.getNodeAs<CXXMethodDecl>("methodDecl")) {
            handle_method(method);
        } else if (const EnumDecl* enum_decl =
                       result.Nodes.getNodeAs<EnumDecl>("enumDecl")) {
            handle_enum(enum_decl);
        } else if (const FunctionDecl* function =
                       result.Nodes.getNodeAs<FunctionDecl>("functionDecl")) {
            handle_function(function);
        } else if (const CXXRecordDecl* record =
                       result.Nodes.getNodeAs<CXXRecordDecl>("recordDecl")) {
            handle_record(record);
        }
    }

    void handle_record(const CXXRecordDecl* record) { process_record(record); }
    void handle_enum(const EnumDecl* enum_decl) { process_enum(enum_decl); }

    void handle_function(const FunctionDecl* function) {
        // convert this method so we can match it against our stored ones
        auto namespaces = cppmm::get_namespaces(function->getParent());
        const auto this_ex_function =
            cppmm::ExportedFunction(function, {}, namespaces);

        // now see if we can find the function in the exported functions on
        // the exported class
        const cppmm::ExportedFunction* matched_ex_function = nullptr;
        std::string matched_file;
        bool rejected = true;
        for (const auto& ex_file : cppmm::ex_files) {
            for (const auto& ex_function : ex_file.second.functions) {
                if (this_ex_function.cpp_name == ex_function.cpp_name &&
                    cppmm::match_namespaces(this_ex_function.namespaces,
                                            ex_function.namespaces)) {
                    matched_file = ex_file.first;
                }

                if (this_ex_function == ex_function) {
                    // found a matching exported function (but may still be
                    // ignored)
                    rejected = false;
                    if (!(ex_function.is_ignored() ||
                          ex_function.is_manual())) {
                        // not ignored, this is the one we'll use
                        matched_ex_function = &ex_function;
                        break;
                    }
                    // } else {
                    // if (this_ex_function.cpp_name == ex_function.cpp_name) {
                    //     fmt::print("REJECTED {}\n", this_ex_function);
                    // }
                }
            }
        }

        // store the rejected function on the class so we can warn that we
        // didn't find a match
        if (rejected) {
            cppmm::ex_files[matched_file].rejected_functions.push_back(
                this_ex_function);
        }

        // we don't want to bind this function so bail
        if (matched_ex_function == nullptr) {
            return;
        }

        if (files.find(matched_file) == files.end()) {
            files[matched_file] = {};
        }
        auto& file = files[matched_file];
        if (file.functions.find(matched_ex_function->c_name) ==
            file.functions.end()) {
            file.functions[matched_ex_function->c_name] =
                process_function(function, *matched_ex_function, namespaces);
        }
        // fmt::print("        MATCHED {} {}\n", function->getNameAsString(),
        //            function->getQualifiedNameAsString());
    }

    void handle_method(const CXXMethodDecl* method) {
        const auto method_name = method->getNameAsString();
        auto* record = process_record(method->getParent());
        if (record == nullptr) {
            fmt::print("ERROR could not process record for {}\n",
                       method->getParent()->getNameAsString());
            abort();
        }

        auto it_class = cppmm::ex_classes.find(record->cpp_name);
        if (it_class == cppmm::ex_classes.end()) {
            return;
        }

        auto& ex_class = it_class->second;

        // convert this method so we can match it against our stored ones
        const auto this_ex_method = cppmm::ExportedMethod(method, {});

        // now see if we can find the method in the exported methods on
        // the exported class
        const cppmm::ExportedMethod* matched_ex_method = nullptr;
        bool rejected = true;
        for (const auto& ex_method : ex_class.methods) {
            if (this_ex_method == ex_method) {
                // found a matching exported method (but may still be
                // ignored)
                rejected = false;
                if (!(ex_method.is_ignored() || ex_method.is_manual())) {
                    // not ignored, this is the one we'll use
                    matched_ex_method = &ex_method;
                    break;
                }
            }
        }

        // store the rejected method on the class so we can warn that we
        // didn't find a match
        if (rejected) {
            ex_class.rejected_methods.push_back(this_ex_method);
        }

        // we don't want to bind this method so bail
        if (matched_ex_method == nullptr) {
            return;
        }

        if (record->methods.find(matched_ex_method->c_name) ==
            record->methods.end()) {
            record->methods[matched_ex_method->c_name] =
                process_method(method, *matched_ex_method, record);
        }
    }
};

class CppmmConsumer : public ASTConsumer {
    MatchFinder _match_finder;
    CppmmMatchHandler _handler;

public:
    explicit CppmmConsumer(ASTContext* context) {
        // match all record (custom type) declarations in all files
        for (const auto& ex_file : cppmm::ex_files) {
            for (const auto& record : ex_file.second.records) {
                DeclarationMatcher record_decl_matcher =
                    cxxRecordDecl(hasName(record.second->cpp_name),
                                  unless(hasAncestor(
                                      namespaceDecl(hasName("cppmm_bind")))),
                                  unless(isImplicit()))
                        .bind("recordDecl");
                _match_finder.addMatcher(record_decl_matcher, &_handler);
            }
        }

        for (const auto& ex_enum : cppmm::ex_enums) {
            DeclarationMatcher enum_decl_matcher =
                enumDecl(
                    hasName(ex_enum.second.cpp_name),
                    unless(hasAncestor(namespaceDecl(hasName("cppmm_bind")))),
                    unless(isImplicit()))
                    .bind("enumDecl");
            _match_finder.addMatcher(enum_decl_matcher, &_handler);
        }

        for (const auto& input_class : cppmm::ex_classes) {
            // Match all class methods that are NOT in the cppmm_bind
            // namespace (or we'll get duplicates)
            DeclarationMatcher method_decl_matcher =
                cxxMethodDecl(
                    isPublic(), ofClass(hasName(input_class.first)),
                    unless(hasAncestor(namespaceDecl(hasName("cppmm_bind")))))
                    .bind("methodDecl");
            _match_finder.addMatcher(method_decl_matcher, &_handler);
        }

        // match all function declarations
        DeclarationMatcher function_decl_matcher =
            functionDecl(
                unless(hasAncestor(namespaceDecl(hasName("cppmm_bind")))),
                unless(hasAncestor(recordDecl())))
                .bind("functionDecl");
        _match_finder.addMatcher(function_decl_matcher, &_handler);
    }

    virtual void HandleTranslationUnit(ASTContext& context) {
        _match_finder.matchAST(context);
    }
};

class CppmmAction : public ASTFrontendAction {
public:
    virtual std::unique_ptr<ASTConsumer>
    CreateASTConsumer(CompilerInstance& compiler, StringRef in_file) {
        return std::unique_ptr<ASTConsumer>(
            new CppmmConsumer(&compiler.getASTContext()));
    }
};

std::vector<std::string> parse_file_includes(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    std::vector<std::string> result;
    // TODO: we probably want to do this with a preprocessor callback, but
    // for now do the dumb way
    while (std::getline(file, line)) {
        if (line.find("#include") == 0) {
            result.push_back(line);
        }
    }

    return result;
}

// Apply a custom category to all command-line options so that they are the
// only ones displayed.
static llvm::cl::OptionCategory CppmmCategory("cppmm options");

// CommonOptionsParser declares HelpMessage with a description of the common
// command-line options related to the compilation database and input files.
// It's nice to have this help message in all tools.
static cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);

// A help message for this specific tool can be added afterwards.
static cl::extrahelp MoreHelp("\nMore help text...\n");

static cl::opt<bool> opt_warn_unbound("u", cl::desc("Warn on unbound methods"));
static cl::list<std::string>
    opt_rename_namespace("n", cl::desc("Rename namespace <to>=<from>"));

std::string bind_file_root(const std::string& filename) {
    const auto basename = ps::os::path::basename(filename);
    std::string root, ext;
    ps::os::path::splitext(root, ext, basename);
    return root;
}

void write_header(const std::string& filename, const std::string& declarations,
                  const std::string& include_stmts) {

    std::string out_str = fmt::format(
        R"#(#pragma once

{}

#ifdef __cplusplus
extern "C" {{
#else
#include <stdbool.h>
#endif

#if defined(_WIN32) || defined(__CYGWIN__)
#define CPPMM_ALIGN(x) __declspec(align(x))
#else
#define CPPMM_ALIGN(x) __attribute__((aligned(x)))
#endif

{}

#undef CPPMM_ALIGN

#ifdef __cplusplus
}}
#endif
    )#",
        include_stmts, declarations);

    auto out = fopen(filename.c_str(), "w");
    fprintf(out, "%s", out_str.c_str());
    fclose(out);
}

void write_implementation(const std::string& filename, const std::string& root,
                          const std::vector<std::string>& includes,
                          const std::string& casts,
                          const std::string& definitions) {
    std::string out_str = fmt::format(
        R"#(//
#include "{}.h"
{}

namespace {{
#include "casts.h"

{}
#undef CPPMM_DEFINE_POINTER_CASTS
}}

extern "C" {{
{}
}}
    )#",
        root, ps::join("\n", includes), casts, definitions);

    auto out = fopen(filename.c_str(), "w");
    fprintf(out, "%s", out_str.c_str());
    fclose(out);
}

void write_casts_header(const std::string& filename) {
    std::string casts_header = R"#(#pragma once
#include <string.h>
// Macro to define short conversion functions between C and C++ API types to
// save us from eye-gougingly verbose casts everywhere
#define CPPMM_DEFINE_POINTER_CASTS(CPPTYPE, CTYPE)          \
CPPTYPE* to_cpp(CTYPE* ptr) {                               \
    return reinterpret_cast<CPPTYPE*>(ptr);                 \
}                                                           \
                                                            \
const CPPTYPE* to_cpp(const CTYPE* ptr) {                   \
    return reinterpret_cast<const CPPTYPE*>(ptr);           \
}                                                           \
                                                            \
CTYPE* to_c(CPPTYPE* ptr) {                                 \
    return reinterpret_cast<CTYPE*>(ptr);                   \
}                                                           \
                                                            \
const CTYPE* to_c(const CPPTYPE* ptr) {                     \
    return reinterpret_cast<const CTYPE*>(ptr);             \
}                                                           \
                                                            \

template <typename TO, typename FROM>
TO bit_cast(FROM f) {
    static_assert(sizeof(TO) == sizeof(FROM), "sizes do not match");
    static_assert(alignof(TO) == alignof(FROM), "alignments do not match");

    TO result;
    memcpy((void*)&result, (void*)&f, sizeof(f));
    return result;
}

void safe_strcpy(char* dst, const std::string& str, int buffer_size) {
    size_t last_char = std::min((size_t)buffer_size - 1, str.size());
    memcpy(dst, str.c_str(), last_char);
    dst[last_char] = '\0';
}
    )#";

    auto out = fopen(filename.c_str(), "w");
    fprintf(out, "%s", casts_header.c_str());
    fclose(out);
}

int main(int argc, const char** argv) {
    CommonOptionsParser OptionsParser(argc, argv, CppmmCategory);
    ClangTool Tool(OptionsParser.getCompilations(),
                   OptionsParser.getSourcePathList());

    // fmt::print("source files: [{}]\n",
    //            ps::join(", ", OptionsParser.getSourcePathList()));

    char buf[2048];
    std::string cwd = getcwd(buf, sizeof(buf));

    for (const auto& src : OptionsParser.getSourcePathList()) {
        const auto src_path = ps::os::path::join(cwd, src);
        const auto includes = parse_file_includes(src_path);
        cppmm::ex_files[src_path] = {};
        cppmm::ex_files[src_path].includes = includes;
    }

    // Get namespace renames from command-line options
    for (const auto& o : opt_rename_namespace) {
        std::vector<std::string> toks;
        ps::split(o, toks, "=");
        if (toks.size() == 2) {
            cppmm::add_namespace_rename(toks[1], toks[0]);
        }
    }

    //--------------------------------------------------------------------------
    // First pass - find all declarations in namespace cppmm_bind that will
    // tell us what we want to bind fmt::print("1st pass ----------\n");
    auto match_exports_action = newFrontendActionFactory<cppmm::MatchBindingsAction>();
    int result = Tool.run(match_exports_action.get());

    // for (const auto& ex_file : ex_files) {
    //     fmt::print("FILE: {}\n", ex_file.first);
    //     for (const auto& ex_fun : ex_file.second.functions) {
    //         fmt::print("    {}\n", ex_fun);
    //     }
    // }

    //--------------------------------------------------------------------------
    // Second pass - find matching methods to the ones declared in the first
    // pass and filter out the ones we want to generate bindings for
    // fmt::print("2nd pass ----------\n");
    auto cppmm_action = newFrontendActionFactory<CppmmAction>();
    result = Tool.run(cppmm_action.get());

    // fmt::print("{:-^30}\n", " OUTPUT ");
    // fmt::print("Types: \n");
    // for (const auto& type : ex_types) {
    //     fmt::print("    {}\n", type.second->name);
    // }

    std::set<std::string> casts_macro_invocations;

    //--------------------------------------------------------------------------
    // Finally - process the filtered methods to generate the actual
    // bindings we'll generate one file of bindings for each file of input,
    // and stick all the bindings in that output, together with all the
    // necessary includes
    for (const auto& bind_file : cppmm::ex_files) {

        std::string declarations;
        std::string definitions;

        std::set<std::string> header_includes;

        for (const auto& rec_pair : bind_file.second.records) {
            const auto& record = records[rec_pair.first];
            declarations += record.get_declaration(casts_macro_invocations);
            definitions += record.get_definition();
        }

        for (const auto& enm_pair : bind_file.second.enums) {
            const auto& enm = enums[enm_pair.first];
            declarations += enm.get_declaration();
        }

        for (const auto& it_function : files[bind_file.first].functions) {
            const auto& function = it_function.second;

            std::string declaration = function.get_declaration(
                header_includes, casts_macro_invocations);

            std::string definition = function.get_definition(declaration);

            declarations = fmt::format("{}\n{}\n{};\n", declarations,
                                       function.comment, declaration);

            definitions = fmt::format("{}\n{}\n\n\n", definitions, definition);
        }

        for (const auto& record_pair : bind_file.second.records) {
            const cppmm::Record& record = records[record_pair.second->c_qname];

            for (auto method_pair : record.methods) {
                const auto& method = method_pair.second;

                std::string declaration = record.get_method_declaration(
                    method, header_includes, casts_macro_invocations);

                std::string definition =
                    record.get_method_definition(method, declaration);

                declarations = fmt::format("{}\n{}\n{};\n", declarations,
                                           method.comment, declaration);

                definitions =
                    fmt::format("{}\n{}\n\n\n", definitions, definition);
            }
        }

        const std::string root = bind_file_root(bind_file.first);
        const auto header = fmt::format("{}.h", root);
        const auto implementation = fmt::format("{}.cpp", root);

        // fmt::print("INCLUDES FOR {}\n", root);
        std::string header_include_stmts;
        for (const auto& i : header_includes) {
            const std::string include_root = bind_file_root(i);
            if (include_root != root) {
                // fmt::print("    {}.h\n", include_root);
                header_include_stmts +=
                    fmt::format("#include \"{}.h\"\n", include_root);
            }
        }

        std::string casts;
        for (const auto& s : casts_macro_invocations) {
            casts += s;
        }

        write_header(header, declarations, header_include_stmts);
        write_implementation(implementation, root, bind_file.second.includes,
                             casts, definitions);
    }

    write_casts_header("casts.h");

    if (opt_warn_unbound) {
        size_t total = 0;
        for (const auto& ex_class : cppmm::ex_classes) {
            total += ex_class.second.rejected_methods.size();
        }
        if (total != 0) {
            fmt::print(
                "The following methods were not bound, ignored or manually "
                "overriden:\n");
            for (const auto& ex_class : cppmm::ex_classes) {
                if (ex_class.second.rejected_methods.size()) {
                    fmt::print("{}\n", ex_class.second.name);
                    for (const auto& rejected_method :
                         ex_class.second.rejected_methods) {
                        fmt::print("    {}\n", rejected_method);
                    }
                }
            }
        }
    }

    return result;
}
