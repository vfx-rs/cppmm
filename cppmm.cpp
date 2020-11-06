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

using namespace clang::tooling;
using namespace llvm;
using namespace clang;
using namespace clang::ast_matchers;

namespace ps = pystring;

std::string internal_namespace_name = "OpenImageIO_v2_2";
std::string external_namespace_name = "OIIO";

std::unordered_map<std::string, std::string> namespace_renames;

const std::string& rename_namespace(const std::string& in) {
    if (namespace_renames.find(in) != namespace_renames.end()) {
        return namespace_renames[in];
    } else {
        return in;
    }
}

const std::string
prefix_from_namespaces(const std::vector<std::string>& cpp_namespaces,
                       const std::string& sep) {
    std::string prefix;
    if (cpp_namespaces.size() != 0) {
        std::vector<std::string> namespaces;
        namespaces.reserve(cpp_namespaces.size());
        for (const auto& ns : cpp_namespaces) {
            namespaces.push_back(rename_namespace(ns));
        }
        prefix = fmt::format("{}{}{}", ps::join(sep, namespaces), sep, prefix);
    }

    return prefix;
}

bool match_namespaces(const std::vector<std::string>& a,
                      const std::vector<std::string>& b) {
    if (a.size() != b.size()) {
        return false;
    }
    for (int i = 0; i < a.size(); ++i) {
        if (rename_namespace(a[i]) != rename_namespace(b[i])) {
            return false;
        }
    }
    return true;
}

struct AttrDesc {
    enum Kind {
        Ignore,
        Rename,
        Manual,
        OpaquePtr,
        OpaqueBytes,
        ValueType,
    };

    std::string params;
    Kind kind;
};

std::optional<AttrDesc> parse_attributes(std::string attr_src) {
    // fmt::print("Got attr_src {}\n", attr_src);
    std::vector<std::string> toks;
    ps::split(attr_src, toks, ":");
    // fmt::print("toks: [{}]\n", ps::join(", ", toks));
    if (toks.size() == 0 || toks[0] != "cppmm") {
        return std::nullopt;
    }

    if (toks[1] == "ignore") {
        return AttrDesc{{}, AttrDesc::Kind::Ignore};
    } else if (toks[1] == "manual") {
        return AttrDesc{{}, AttrDesc::Kind::Manual};
    } else if (toks[1] == "rename") {
        return AttrDesc{toks[2], AttrDesc::Kind::Rename};
    } else if (toks[1] == "opaqueptr") {
        return AttrDesc{{}, AttrDesc::Kind::OpaquePtr};
    } else if (toks[1] == "opaquebytes") {
        return AttrDesc{{}, AttrDesc::Kind::OpaqueBytes};
    } else if (toks[1] == "valuetype") {
        return AttrDesc{{}, AttrDesc::Kind::ValueType};
    }

    fmt::print("Warning Could not parse attribute '{}'\n", attr_src);

    return std::nullopt;
}

namespace cppmm {

struct CType {
    std::string name;
};

enum TypeKind { OpaquePtr = 0, OpaqueBytes = 1, ValueType = 2 };

class Record;
class Enum;

struct Type {
    std::string name;
    std::vector<std::string> namespaces = {};
    // std::vector<Param> template_params;
    bool is_builtin = false;
    bool is_enum = false;
    bool is_func_proto = false;
    // std::vector<std::pair<std::string, uint64_t>> enumerators = {};
    Record* record = nullptr;
    const Enum* enm = nullptr;

    bool is_pod() const;
};

struct Param {
    std::string name;
    Type type;
    bool is_ptr = false;
    bool is_uptr = false;
    bool is_ref = false;
    bool is_const = false;
    bool requires_cast = false;
};

struct Record {
    std::string cpp_name;
    std::vector<std::string> namespaces;
    std::string c_name;
    TypeKind kind;
    std::string filename;
    std::vector<cppmm::Param> fields;

    bool is_pod() const {
        for (const auto& p : fields) {
            if (!p.type.is_pod()) {
                return false;
            }
        }

        return true;
    }
};

struct Enum {
    std::string cpp_name;
    std::vector<std::string> namespaces;
    std::string c_name;
    std::string filename;
    std::vector<std::pair<std::string, uint64_t>> enumerators;
};

bool Type::is_pod() const {
    if (is_builtin || is_enum || is_func_proto) {
        return true;
    }

    if (record) {
        return record->is_pod();
    }

    assert(false && "TYPE POD FALLTHROUGH");
    return false;
}

std::string get_c_function_decl(const Param& param) {
    std::string result;
    if (param.type.name == "basic_string") {
        if (param.is_const) {
            result += "const char*";
        } else {
            result += "char*";
        }
    } else if (param.type.name == "string_view") {
        result += "const char*";
    } else if (param.type.name == "const char *") {
        result += "const char*";
    } else if (param.type.name == "void *") {
        result += "void*";
    } else {
        if (param.is_const) {
            result += "const ";
        }
        result += prefix_from_namespaces(param.type.namespaces, "_") +
                  param.type.name;
        if (param.is_ptr || param.is_ref || param.is_uptr) {
            result += "*";
        }
    }

    result += " ";
    result += param.name;

    return result;
}

std::string get_c_function_call(const Param& param) {
    std::string result;
    if (param.is_ref && !(param.type.name == "basic_string" ||
                          param.type.name == "string_view")) {
        if (param.requires_cast) {
            result = fmt::format("*to_cpp({})", param.name);
        } else {
            result = fmt::format("*{}", param.name);
        }
    } else {
        if (param.requires_cast) {
            result = fmt::format("to_cpp({})", param.name);
        } else {
            result = param.name;
        }
    }
    return result;
}

struct CParam {
    std::string name;
    CType type;
    bool is_ptr = false;
    bool is_const = false;
};

struct Method {
    std::string cpp_name;
    std::string c_name;
    bool is_const = false;
    bool is_static = false;
    Param return_type;
    std::vector<Param> params;
    std::string comment;
};

struct Function {
    std::string cpp_name;
    std::string c_name;
    Param return_type;
    std::vector<Param> params;
    std::string comment;
    std::vector<std::string> namespaces;
};

struct Class {
    std::string name;
    std::vector<std::string> namespaces;
    std::unordered_map<std::string, Method> methods;
};

struct File {
    std::unordered_map<std::string, Function> functions;
    std::unordered_map<std::string, Record> records;
};

struct ExportedFunction {
    ExportedFunction(const FunctionDecl* function, std::vector<AttrDesc> attrs,
                     std::vector<std::string> namespaces = {})
        : attrs(attrs), namespaces(namespaces) {
        function = function->getCanonicalDecl();
        cpp_name = function->getNameAsString();
        return_type =
            function->getReturnType().getCanonicalType().getAsString();
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
};

struct ExportedMethod : public ExportedFunction {
    ExportedMethod(const CXXMethodDecl* method, std::vector<AttrDesc> attrs)
        : ExportedFunction(dyn_cast<FunctionDecl>(method), attrs) {
        is_const = method->isConst();
    }

    bool is_const = false;
};

struct ExportedRecord {
    std::string cpp_name;
    std::vector<std::string> namespaces;
    std::string c_name;
    TypeKind kind;
    std::string filename;
};

struct ExportedEnum {
    std::string cpp_name;
    std::vector<std::string> namespaces;
    std::string c_name;
    std::string filename;
};

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
    std::vector<std::string> includes;
    std::vector<ExportedFunction> functions;
    std::vector<ExportedFunction> rejected_functions;
    std::unordered_map<std::string, ExportedRecord*> records;
    std::unordered_map<std::string, ExportedEnum*> enums;
};

} // namespace cppmm

std::unordered_map<std::string, cppmm::ExportedFile> ex_files;
std::unordered_map<std::string, cppmm::ExportedClass> ex_classes;
std::unordered_map<std::string, cppmm::ExportedRecord> ex_records;
std::unordered_map<std::string, cppmm::ExportedEnum> ex_enums;

std::unordered_map<std::string, cppmm::Class> classes;
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
    return prefix_from_namespaces(type.namespaces, "::") + type.name;
}

std::vector<std::string> get_namespaces(const DeclContext* parent) {
    std::vector<std::string> result;

    while (parent) {
        if (parent->isNamespace()) {
            const NamespaceDecl* ns = static_cast<const NamespaceDecl*>(parent);
            if (ns->getNameAsString() == "cppmm_bind") {
                break;
            }
            result.push_back(ns->getNameAsString());
            parent = parent->getParent();
        } else if (parent->isRecord()) {
            const RecordDecl* rd = static_cast<const RecordDecl*>(parent);
            result.push_back(rd->getNameAsString());
            parent = parent->getParent();
        } else {
            break;
        }
    }

    std::reverse(result.begin(), result.end());
    return result;
}

cppmm::Param process_param_type(const std::string& param_name,
                                const QualType& qt);

cppmm::Record* process_record(const CXXRecordDecl* record) {
    std::string cpp_name = record->getNameAsString();
    std::vector<std::string> namespaces = get_namespaces(record->getParent());

    const auto c_name = prefix_from_namespaces(namespaces, "_") + cpp_name;
    if (records.find(c_name) != records.end()) {
        // already done this type, return
        return &records[c_name];
    }

    auto it_ex_record = ex_records.find(c_name);
    if (it_ex_record == ex_records.end()) {
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

    fmt::print("Processed record {} -> {} in {}\n", cpp_name, c_name,
               it_ex_record->second.filename);
    records[c_name] = cppmm::Record{.cpp_name = cpp_name,
                                    .namespaces = namespaces,
                                    .c_name = c_name,
                                    .kind = it_ex_record->second.kind,
                                    .filename = it_ex_record->second.filename,
                                    .fields = fields};
    const auto* rptr = &records[c_name];
    if (rptr->kind == cppmm::TypeKind::ValueType && !rptr->is_pod()) {
        fmt::print("ERROR: {} is valuetype but not POD\n", rptr->c_name);
    }
    fmt::print("MATCHED: {}\n", cpp_name);

    return &records[c_name];
}

cppmm::Enum* process_enum(const EnumDecl* enum_decl) {
    std::string cpp_name = enum_decl->getNameAsString();
    std::vector<std::string> namespaces =
        get_namespaces(enum_decl->getParent());

    const auto c_name = prefix_from_namespaces(namespaces, "_") + cpp_name;
    if (enums.find(c_name) != enums.end()) {
        // already done this type, return
        return &enums[c_name];
    }

    auto it_ex_enum = ex_enums.find(c_name);
    if (it_ex_enum == ex_enums.end()) {
        // fmt::print("WARNING: enum '{}' has no export definition\n",
        // c_name);
        return nullptr;
    }

    fmt::print("Processed enum {} -> {} in {}\n", cpp_name, c_name,
               it_ex_enum->second.filename);

    std::vector<std::pair<std::string, uint64_t>> enumerators;
    for (const auto& ecd : enum_decl->enumerators()) {
        enumerators.push_back(std::make_pair<std::string, uint64_t>(
            ecd->getNameAsString(), ecd->getInitVal().getLimitedValue()));
    }

    enums[c_name] = cppmm::Enum{.cpp_name = cpp_name,
                                .namespaces = namespaces,
                                .c_name = c_name,
                                .filename = it_ex_enum->second.filename,
                                .enumerators = enumerators};

    fmt::print("MATCHED: {}\n", cpp_name);

    return &enums[c_name];
}

cppmm::Param process_pointee_type(const std::string& param_name,
                                  const QualType& qt) {
    cppmm::Param result;
    result.name = param_name;

    if (is_builtin(qt)) {
        std::string name = qt.getAsString();
        result.type = cppmm::Type{qt.getTypePtr()
                                      ->getUnqualifiedDesugaredType()
                                      ->getAs<BuiltinType>()
                                      ->desugar()
                                      .getAsString(),
                                  {},
                                  .is_builtin = true};
        result.requires_cast = false;
    } else if (qt->isRecordType()) {
        const CXXRecordDecl* crd = qt->getAsCXXRecordDecl();
        if (crd->getNameAsString() == "unique_ptr") {
            const auto* tst = qt->getAs<TemplateSpecializationType>();
            result =
                process_pointee_type(param_name, tst->getArgs()->getAsType());
            result.is_uptr = true;
        } else {
            const CXXRecordDecl* crd = qt->getAsCXXRecordDecl();
            cppmm::Record* record_ptr = process_record(crd);
            result.type = cppmm::Type{
                crd->getNameAsString(),
                get_namespaces(qt->getAsCXXRecordDecl()->getParent()),
                .record = record_ptr};
            result.requires_cast = !(crd->getNameAsString() == "basic_string" ||
                                     crd->getNameAsString() == "string_view");
        }
    } else if (qt->isEnumeralType()) {
        // const auto* enum_decl = qt->getAs<EnumType>()->getDecl();
        // const auto ns = get_namespaces(enum_decl->getParent());
        // std::vector<std::pair<std::string, uint64_t>> enumerators;
        // for (const auto& ecd : enum_decl->enumerators()) {
        //     enumerators.push_back(std::make_pair<std::string, uint64_t>(
        //         ecd->getNameAsString(),
        //         ecd->getInitVal().getLimitedValue()));
        // }
        const auto* enum_decl = qt->getAs<EnumType>()->getDecl();
        const cppmm::Enum* enm = process_enum(enum_decl);

        result.type = cppmm::Type{enm->cpp_name, enm->namespaces,
                                  .is_enum = true, .enm = enm};
        std::string qname = qualified_type_name(result.type);

    } else {
        fmt::print("Unhandled type: {}\n", qt.getAsString());
        qt->dump();
    }

    result.is_const = qt.isConstQualified();
    return result;
}

cppmm::Param process_param_type(const std::string& param_name,
                                const QualType& qt) {
    cppmm::Param result;
    bool is_ptr = qt->isPointerType();
    bool is_ref = qt->isReferenceType();

    if (is_ptr || is_ref) {
        result = process_pointee_type(param_name, qt->getPointeeType());
        result.is_ptr = is_ptr;
        result.is_ref = is_ref;
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
std::ostream& operator<<(std::ostream& os, const cppmm::Param& param) {
    if (param.is_const) {
        os << "const ";
    }
    auto& ns = param.type.namespaces;
    if (ns.size()) {
        os << ps::join("::", ns) << "::";
    }
    os << param.type.name;
    if (param.is_ptr) {
        os << "* ";
    } else if (param.is_ref) {
        os << "& ";
    } else {
        os << " ";
    }
    os << param.name;
    return os;
}

std::ostream& operator<<(std::ostream& os, const cppmm::CParam& param) {
    if (param.is_const) {
        os << "const ";
    }
    os << param.type.name;
    if (param.is_ptr) {
        os << "* ";
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

std::ostream& operator<<(std::ostream& os,
                         const cppmm::ExportedFunction& method) {
    if (method.is_static) {
        os << "static ";
    }
    auto ns = prefix_from_namespaces(method.namespaces, "::");
    os << "auto " << ns << method.cpp_name << "("
       << ps::join(", ", method.params) << ") -> " << method.return_type;
    return os;
}

std::ostream& operator<<(std::ostream& os,
                         const cppmm::ExportedMethod& method) {
    if (method.is_static) {
        os << "static ";
    }
    os << "auto " << method.cpp_name << "(" << ps::join(", ", method.params)
       << ") -> " << method.return_type;
    if (method.is_const) {
        os << " const";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const cppmm::ExportedRecord& type) {
    os << "struct " << type.c_name;
    if (type.kind == cppmm::TypeKind::OpaquePtr) {
        os << " //< opaque ptr";
    } else if (type.kind == cppmm::TypeKind::OpaqueBytes) {
        os << " //< opaque bytes";
    } else if (type.kind == cppmm::TypeKind::ValueType) {
        os << " //< value type";
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
        .cpp_name = ex_function.cpp_name,
        .c_name = ex_function.c_name,
        .return_type = process_param_type("", function->getReturnType()),
        .params = params,
        .comment = comment,
        .namespaces = namespaces};
}

cppmm::Method process_method(const CXXMethodDecl* method,
                             const cppmm::ExportedMethod& ex_method) {
    std::vector<cppmm::Param> params;
    for (const auto& p : method->parameters()) {
        const auto param_name = p->getNameAsString();
        params.push_back(process_param_type(param_name, p->getType()));
    }

    std::string comment = get_decl_comment(method);

    return cppmm::Method{.cpp_name = ex_method.cpp_name,
                         .c_name = ex_method.c_name,
                         .is_const = method->isConst(),
                         .is_static = method->isStatic(),
                         .return_type =
                             process_param_type("", method->getReturnType()),
                         .params = params,
                         .comment = comment};
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
        auto namespaces = get_namespaces(function->getParent());
        const auto this_ex_function =
            cppmm::ExportedFunction(function, {}, namespaces);

        // now see if we can find the function in the exported functions on
        // the exported class
        const cppmm::ExportedFunction* matched_ex_function = nullptr;
        std::string matched_file;
        bool rejected = true;
        for (const auto& ex_file : ex_files) {
            for (const auto& ex_function : ex_file.second.functions) {
                if (this_ex_function.cpp_name == ex_function.cpp_name &&
                    match_namespaces(this_ex_function.namespaces,
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
            ex_files[matched_file].rejected_functions.push_back(
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
        const auto class_name = method->getParent()->getNameAsString();

        // first make sure this method is on a class we want to export
        // this should never return if we're filtering correctly at the
        // top level.
        auto it_class = ex_classes.find(class_name);
        if (it_class == ex_classes.end()) {
            return;
        }

        auto& ex_class = it_class->second;

        // see if we have a converted class already and if not, make one
        // currently this doesn't do anything useful, ultimately we want
        // to store a table of classes that we're converting and where
        // they're declared so we can include the appropriate C headers in
        // the bindings, as well as error if something is used but not
        // declared for binding
        if (classes.find(class_name) == classes.end()) {
            auto namespaces = get_namespaces(method->getParent()->getParent());
            classes[class_name] = cppmm::Class{class_name, namespaces, {}};
        }

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

        // fmt::print("        MATCHED {} {}\n", method_name,
        //            method->getQualifiedNameAsString());

        // now grab the method parameters for further processing
        // if we don't already have a method definition for the C version
        // of this method
        if (classes[class_name].methods.find(matched_ex_method->c_name) ==
            classes[class_name].methods.end()) {
            classes[class_name].methods[matched_ex_method->c_name] =
                process_method(method, *matched_ex_method);
        }
    }
};

class CppmmConsumer : public ASTConsumer {
    MatchFinder _match_finder;
    CppmmMatchHandler _handler;

public:
    explicit CppmmConsumer(ASTContext* context) {
        // match all record (custom type) declarations in all files
        for (const auto& ex_file : ex_files) {
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

        for (const auto& ex_enum : ex_enums) {
            DeclarationMatcher enum_decl_matcher =
                enumDecl(
                    hasName(ex_enum.second.cpp_name),
                    unless(hasAncestor(namespaceDecl(hasName("cppmm_bind")))),
                    unless(isImplicit()))
                    .bind("enumDecl");
            _match_finder.addMatcher(enum_decl_matcher, &_handler);
        }

        for (const auto& input_class : ex_classes) {
            // Match all class methods that are NOT in the cppmm_bind namespace
            // (or we'll get duplicates)
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

std::vector<AttrDesc> get_attrs(const Decl* decl) {
    std::vector<AttrDesc> attrs;
    if (decl->hasAttrs()) {
        ASTContext& ctx = decl->getASTContext();
        for (const auto& attr : decl->attrs()) {
            const AnnotateAttr* ann = cast<const AnnotateAttr>(attr);
            if (ann) {
                if (auto opt = parse_attributes(ann->getAnnotation().str())) {
                    attrs.push_back(*opt);
                }
            }
        }
    }

    return attrs;
}

class MatchExportsCallback : public MatchFinder::MatchCallback {
    virtual void run(const MatchFinder::MatchResult& result) {
        if (const CXXRecordDecl* record =
                result.Nodes.getNodeAs<CXXRecordDecl>("recordDecl")) {
            handle_record(record);
        } else if (const EnumDecl* enum_decl =
                       result.Nodes.getNodeAs<EnumDecl>("enumDecl")) {
            handle_enum(enum_decl);
        } else if (const CXXMethodDecl* method =
                       result.Nodes.getNodeAs<CXXMethodDecl>("methodDecl")) {
            handle_method(method);
        } else if (const FunctionDecl* function =
                       result.Nodes.getNodeAs<FunctionDecl>("functionDecl")) {
            handle_function(function);
        }
    }

    void handle_enum(const EnumDecl* enum_decl) {
        const auto ns = get_namespaces(enum_decl->getParent());
        std::vector<std::pair<std::string, uint64_t>> enumerators;
        // for (const auto& ecd : enum_decl->enumerators()) {
        //     enumerators.push_back(std::make_pair<std::string, uint64_t>(
        //         ecd->getNameAsString(),
        //         ecd->getInitVal().getLimitedValue()));
        // }

        ASTContext& ctx = enum_decl->getASTContext();
        SourceManager& sm = ctx.getSourceManager();
        const auto& loc = enum_decl->getLocation();
        std::string filename = sm.getFilename(loc);

        cppmm::ExportedEnum ex_enum;
        ex_enum.cpp_name = enum_decl->getNameAsString();
        ex_enum.c_name = prefix_from_namespaces(ns, "_") + ex_enum.cpp_name;
        fmt::print("Found enum: {}\n", ex_enum.c_name);
        ex_enum.namespaces = ns;
        ex_enum.filename = filename;

        if (ex_enums.find(ex_enum.c_name) != ex_enums.end()) {
            fmt::print("WARNING: Ignoring duplicate definition for {}\n",
                       ex_enum.c_name);
            return;
        }

        ex_enums[ex_enum.c_name] = ex_enum;

        if (ex_files.find(filename) == ex_files.end()) {
            ex_files[filename] = {};
        }

        auto& ex_file = ex_files[filename];
        if (ex_file.enums.find(ex_enum.c_name) == ex_file.enums.end()) {
            ex_file.enums[ex_enum.c_name] = &ex_enums[ex_enum.c_name];
            // fmt::print("GOT TYPE: {}\n", ex_record);
        }
    }

    void handle_record(const CXXRecordDecl* record) {
        cppmm::ExportedRecord ex_record;

        ex_record.cpp_name = record->getNameAsString();
        ex_record.namespaces = get_namespaces(record->getParent());
        ex_record.c_name = prefix_from_namespaces(ex_record.namespaces, "_") +
                           ex_record.cpp_name;

        if (ex_records.find(ex_record.c_name) != ex_records.end()) {
            fmt::print("WARNING: Ignoring duplicate definition for {}\n",
                       ex_record.c_name);
            return;
        }

        std::vector<AttrDesc> attrs = get_attrs(record);
        for (const auto& attr : attrs) {
            if (attr.kind == AttrDesc::Kind::OpaquePtr) {
                ex_record.kind = cppmm::TypeKind::OpaquePtr;
            } else if (attr.kind == AttrDesc::Kind::OpaqueBytes) {
                ex_record.kind = cppmm::TypeKind::OpaqueBytes;
            } else if (attr.kind == AttrDesc::Kind::ValueType) {
                ex_record.kind = cppmm::TypeKind::ValueType;
            }
        }

        // fmt::print("record {}\n", ex_record.cpp_name);
        // record->dump();
        ASTContext& ctx = record->getASTContext();
        SourceManager& sm = ctx.getSourceManager();
        const auto& loc = record->getLocation();
        std::string filename = sm.getFilename(loc);
        fmt::print("    {}:{}:{}\n", filename, sm.getSpellingLineNumber(loc),
                   sm.getSpellingColumnNumber(loc));

        ex_record.filename = filename;

        ex_records[ex_record.c_name] = ex_record;
        cppmm::ExportedRecord* ex_record_ptr = &ex_records[ex_record.c_name];

        if (ex_files.find(filename) == ex_files.end()) {
            ex_files[filename] = {};
        }

        auto& ex_file = ex_files[filename];
        if (ex_file.records.find(ex_record.c_name) == ex_file.records.end()) {
            ex_file.records[ex_record.c_name] = ex_record_ptr;
            // fmt::print("GOT TYPE: {}\n", ex_record);
        }
    }

    void handle_function(const FunctionDecl* function) {
        // fmt::print("GOT FUNCTION: {}\n", function->getNameAsString());
        std::vector<AttrDesc> attrs = get_attrs(function);

        // figure out which file we're in
        ASTContext& ctx = function->getASTContext();
        SourceManager& sm = ctx.getSourceManager();
        std::string filename = sm.getFilename(function->getBeginLoc());

        auto namespaces = get_namespaces(function->getParent());

        cppmm::ExportedFunction ex_function(function, attrs, namespaces);

        if (ex_files.find(filename) == ex_files.end()) {
            ex_files[filename] = {};
        }
        ex_files[filename].functions.push_back(ex_function);
    }

    void handle_method(const CXXMethodDecl* method) {
        // If there are attributes, parse them looking for cppmm annotations
        std::vector<AttrDesc> attrs = get_attrs(method);
        cppmm::ExportedMethod ex_method(method, attrs);
        const auto class_name = method->getParent()->getNameAsString();

        // check if we've seen the class this method belongs to before, and
        // if not process it
        if (ex_classes.find(class_name) == ex_classes.end()) {
            ASTContext& ctx = method->getASTContext();
            SourceManager& sm = ctx.getSourceManager();

            std::string filename = sm.getFilename(method->getBeginLoc());

            auto namespaces = get_namespaces(method->getParent()->getParent());
            ex_classes[class_name] =
                cppmm::ExportedClass{class_name, filename, namespaces, {}};

            if (ex_files.find(filename) == ex_files.end()) {
                ex_files[filename] = {};
            }
            ex_files[filename].classes.push_back(class_name);
        }

        // store this method signiature to match against in the second pass
        ex_classes[class_name].methods.push_back(ex_method);
    }
};

class MatchExportsConsumer : public ASTConsumer {
    MatchFinder _match_finder;
    MatchExportsCallback _handler;

public:
    explicit MatchExportsConsumer(ASTContext* context) {
        // match all record declrations in the cppmm_bind namespace
        DeclarationMatcher enum_decl_matcher =
            enumDecl(hasAncestor(namespaceDecl(hasName("cppmm_bind"))),
                     unless(isImplicit()))
                .bind("enumDecl");
        _match_finder.addMatcher(enum_decl_matcher, &_handler);

        // match all record declrations in the cppmm_bind namespace
        DeclarationMatcher record_decl_matcher =
            cxxRecordDecl(hasAncestor(namespaceDecl(hasName("cppmm_bind"))),
                          unless(isImplicit()))
                .bind("recordDecl");
        _match_finder.addMatcher(record_decl_matcher, &_handler);

        // match all method declrations in the cppmm_bind namespace
        DeclarationMatcher method_decl_matcher =
            cxxMethodDecl(hasAncestor(namespaceDecl(hasName("cppmm_bind"))))
                .bind("methodDecl");
        _match_finder.addMatcher(method_decl_matcher, &_handler);

        // match all function declarations
        DeclarationMatcher function_decl_matcher =
            functionDecl(hasAncestor(namespaceDecl(hasName("cppmm_bind"))),
                         unless(hasAncestor(recordDecl())))
                .bind("functionDecl");
        _match_finder.addMatcher(function_decl_matcher, &_handler);
    }

    virtual void HandleTranslationUnit(ASTContext& context) {
        _match_finder.matchAST(context);
    }
};

class MatchExportsAction : public ASTFrontendAction {
public:
    virtual std::unique_ptr<ASTConsumer>
    CreateASTConsumer(CompilerInstance& compiler, StringRef in_file) {
        return std::unique_ptr<ASTConsumer>(
            new MatchExportsConsumer(&compiler.getASTContext()));
    }
};

std::vector<std::string> get_includes(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    std::vector<std::string> result;
    // TODO: we probably want to do this with a preprocessor callback, but for
    // now do the dumb way
    while (std::getline(file, line)) {
        if (line.find("#include") == 0) {
            result.push_back(line);
        }
    }

    return result;
}

std::string create_casts(const cppmm::Class& cls) {
    std::string cpp_type =
        prefix_from_namespaces(cls.namespaces, "::") + cls.name;
    std::string c_type = prefix_from_namespaces(cls.namespaces, "_") + cls.name;
    return fmt::format("CPPMM_DEFINE_POINTER_CASTS({}, {})\n", cpp_type,
                       c_type);
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
        const auto includes = get_includes(src_path);
        ex_files[src_path] = {};
        ex_files[src_path].includes = includes;
    }

    // TODO: we need to declare this properly somehow, maybe a special namespace
    // where we can do a namespace OIIO = OpenImageIO_v2_2?
    for (const auto& o : opt_rename_namespace) {
        std::vector<std::string> toks;
        ps::split(o, toks, "=");
        if (toks.size() == 2) {
            fmt::print("RENAME {} -> {}\n", toks[1], toks[0]);
            namespace_renames[toks[1]] = toks[0];
        }
    }

    //--------------------------------------------------------------------------
    // First pass - find all declarations in namespace cppmm_bind that will tell
    // us what we want to bind
    // fmt::print("1st pass ----------\n");
    auto match_exports_action = newFrontendActionFactory<MatchExportsAction>();
    int result = Tool.run(match_exports_action.get());

    for (const auto& ex_file : ex_files) {
        fmt::print("FILE: {}\n", ex_file.first);
        for (const auto& ex_fun : ex_file.second.functions) {
            fmt::print("    {}\n", ex_fun);
        }
    }

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

    std::string casts_macro_invocaions;

    //--------------------------------------------------------------------------
    // Finally - process the filtered methods to generate the actual bindings
    // we'll generate one file of bindings for each file of input, and stick
    // all the bindings in that output, together with all the necessary includes
    for (const auto& bind_file : ex_files) {

        std::string declarations;
        std::string definitions;

        std::set<std::string> includes;

        for (const auto& rec_pair : bind_file.second.records) {
            const auto& record = records[rec_pair.first];
            if (record.kind == cppmm::TypeKind::OpaquePtr) {
                declarations +=
                    fmt::format("typedef struct {0} {0};\n\n", record.c_name);
            } else if (record.kind == cppmm::TypeKind::ValueType) {
                declarations += fmt::format("typedef struct {{\n");
                for (const auto& field : record.fields) {
                    declarations += fmt::format("    {} {};\n", field.type.name,
                                                field.name);
                }
                declarations += fmt::format("}} {};\n\n", record.c_name);
            }
        }

        for (const auto& enm_pair : bind_file.second.enums) {
            const auto& enm = enums[enm_pair.first];
            declarations += fmt::format("enum {} {{\n", enm.c_name);

            for (const auto& ecd : enm.enumerators) {
                std::string c_name = enm.c_name + "_" + ecd.first;
                declarations +=
                    fmt::format("    {} = {},\n", c_name, ecd.second);
            }

            declarations += "};\n\n";
        }

        for (const auto& it_function : files[bind_file.first].functions) {
            const auto& function = it_function.second;
            std::string c_function_name = fmt::format(
                "{}{}", prefix_from_namespaces(function.namespaces, "_"),
                function.c_name);

            std::vector<std::string> param_decls;
            std::transform(function.params.begin(), function.params.end(),
                           std::back_inserter(param_decls),
                           cppmm::get_c_function_decl);

            std::string ret = cppmm::get_c_function_decl(function.return_type);

            std::string declaration = fmt::format(
                "{} {}({})", ret, c_function_name, ps::join(", ", param_decls));

            declarations = fmt::format("{}\n{}\n{};\n", declarations,
                                       function.comment, declaration);
        }

        for (const auto& file_class_name : bind_file.second.classes) {
            const auto& cls = classes[file_class_name];
            // fmt::print("{}\n", cls.name);

            std::string class_type = fmt::format(
                "{}{}", prefix_from_namespaces(cls.namespaces, "_"), cls.name);

            std::string method_prefix = fmt::format(
                "{}{}", prefix_from_namespaces(cls.namespaces, "_"), cls.name);

            casts_macro_invocaions += create_casts(cls);

            for (auto method_pair : cls.methods) {
                const auto& method = method_pair.second;
                auto c_method_name =
                    fmt::format("{}_{}", method_prefix, method.c_name);

                std::vector<std::string> param_decls;
                std::transform(method.params.begin(), method.params.end(),
                               std::back_inserter(param_decls),
                               cppmm::get_c_function_decl);

                for (const auto& param : method.params) {
                    if (param.type.record) {
                        includes.insert(param.type.record->filename);
                    } else if (param.type.enm) {
                        includes.insert(param.type.enm->filename);
                    }
                }

                std::string ret =
                    cppmm::get_c_function_decl(method.return_type);

                std::string declaration;
                if (method.is_static) {
                    declaration = fmt::format("{} {}({})", ret, c_method_name,
                                              ps::join(", ", param_decls));
                } else {
                    std::string constqual;
                    if (method.is_const) {
                        constqual = "const ";
                    }
                    declaration =
                        fmt::format("{} {}({}{}* self", ret, c_method_name,
                                    constqual, class_type);
                    if (param_decls.size()) {
                        declaration = fmt::format("{}, {})", declaration,
                                                  ps::join(", ", param_decls));
                    } else {
                        declaration = fmt::format("{})", declaration);
                    }
                }

                declarations = fmt::format("{}\n{}\n{};\n", declarations,
                                           method.comment, declaration);

                std::string body = "    return ";
                if (method.return_type.requires_cast) {
                    body += "to_c(";
                }
                if (method.is_static) {
                    body += prefix_from_namespaces(cls.namespaces, "::") +
                            cls.name + "::";
                } else {
                    body += "to_cpp(self)->";
                }
                body += method.cpp_name;
                std::vector<std::string> call_params;
                for (const auto& p : method.params) {
                    call_params.push_back(cppmm::get_c_function_call(p));
                }
                body += fmt::format("({})", ps::join(", ", call_params));
                if (method.return_type.is_uptr) {
                    body += ".release()";
                }
                if (method.return_type.requires_cast) {
                    body += ")";
                }
                body += ";";

                std::string definition =
                    fmt::format("{} {{\n{}\n}}", declaration, body);

                definitions =
                    fmt::format("{}\n{}\n\n\n", definitions, definition);
            }
        }

        const std::string root = bind_file_root(bind_file.first);
        const auto header = fmt::format("{}.h", root);
        const auto implementation = fmt::format("{}.cpp", root);

        // fmt::print("INCLUDES FOR {}\n", root);
        std::string include_stmts;
        for (const auto& i : includes) {
            const std::string include_root = bind_file_root(i);
            if (include_root != root) {
                // fmt::print("    {}.h\n", include_root);
                include_stmts +=
                    fmt::format("#include \"{}.h\"\n", include_root);
            }
        }

        definitions = fmt::format(
            R"#(//
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
            ps::join("\n", bind_file.second.includes), casts_macro_invocaions,
            definitions);

        auto out = fopen(implementation.c_str(), "w");
        fprintf(out, "%s", definitions.c_str());

        out = fopen(header.c_str(), "w");

        declarations = fmt::format(
            R"#(#pragma once

{}

#ifdef __cplusplus
extern "C" {{
#endif

{}

#ifdef __cplusplus
}}
#endif
    )#",
            include_stmts, declarations);

        fprintf(out, "%s", declarations.c_str());
    }

    std::string casts_implementation = R"#(#pragma once

// Macro to define short conversion functions between C and C++ API types to
// save us from eye-gougingly verbose casts everywhere
#define CPPMM_DEFINE_POINTER_CASTS(CPPTYPE, CTYPE)          \
CPPTYPE* to_cpp(CTYPE* ptr) {                               \
    return retinterpret_cast<CPPTYPE*>(ptr)                 \
}                                                           \
                                                            \
const CPPTYPE* to_cpp(const CTYPE* ptr) {                   \
    return retinterpret_cast<const CPPTYPE*>(ptr)           \
}                                                           \
                                                            \
CTYPE* to_c(CPPTYPE* ptr) {                                 \
    return retinterpret_cast<CTYPE*>(ptr)                   \
}                                                           \
                                                            \
const CTYPE* to_c(const CPPTYPE* ptr) {                     \
    return retinterpret_cast<const CTYPE*>(ptr)             \
}                                                           \
                                                            \

    )#";

    auto out = fopen("casts.h", "w");
    fprintf(out, "%s", casts_implementation.c_str());

    // fmt::print("{}\n", casts_implementation);

    // fmt::print("{}\n", declarations);
    // fmt::print("{}\n", definitions);

    if (opt_warn_unbound) {
        size_t total = 0;
        for (const auto& ex_class : ex_classes) {
            total += ex_class.second.rejected_methods.size();
        }
        if (total != 0) {
            fmt::print(
                "The following methods were not bound, ignored or manually "
                "overriden:\n");
            for (const auto& ex_class : ex_classes) {
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
