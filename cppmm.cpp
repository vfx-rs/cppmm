#include <algorithm>
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

namespace cppmm {

struct CType {
    std::string name;
};

struct Type {
    std::string name;
    std::vector<std::string> namespaces;
    // std::vector<Param> template_params;
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
    std::string name;
    bool is_const = false;
    bool is_static = false;
    Param return_type;
    std::vector<Param> params;
    std::string comment;
};

struct Class {
    std::string name;
    std::vector<std::string> namespaces;
    std::vector<Method> methods;
};

struct ExportedMethod {

    ExportedMethod(const CXXMethodDecl* method) {
        method = method->getCanonicalDecl();
        name = method->getNameAsString();
        return_type = method->getReturnType().getCanonicalType().getAsString();
        for (const auto& p : method->parameters()) {
            params.push_back(p->getType().getCanonicalType().getAsString());
        }
        is_const = method->isConst();
        is_static = method->isStatic();
    }
    std::string name;
    std::string return_type;
    // vector of canonical typenames that are this method's parameters.
    std::vector<std::string> params;
    bool is_const = false;
    bool is_static = false;
};

bool operator==(const ExportedMethod& a, const ExportedMethod& b) {
    return a.name == b.name && a.return_type == b.return_type &&
           a.params == b.params && a.is_const == b.is_const &&
           a.is_static == b.is_static;
}

struct ExportedClass {
    std::string name;
    std::vector<std::string> namespaces;
    std::vector<ExportedMethod> methods;
};

} // namespace cppmm

std::unordered_map<std::string, cppmm::ExportedClass> ex_classes;

bool is_builtin(const QualType& qt) {
    return (qt->isBuiltinType() ||
            (qt->isPointerType() && qt->getPointeeType()->isBuiltinType()));
}

bool is_recordpointer(const QualType& qt) {
    return ((qt->isReferenceType() || qt->isPointerType()) &&
            qt->getPointeeType()->isRecordType());
}

std::vector<std::string> get_namespaces(const CXXRecordDecl* crd) {
    std::vector<std::string> result;
    const DeclContext* parent = crd->getParent();

    while (parent) {
        if (parent->isNamespace()) {
            const NamespaceDecl* ns = static_cast<const NamespaceDecl*>(parent);
            if (ns->getNameAsString() == "cppmm_bind") {
                break;
            }
            result.push_back(ns->getNameAsString());
            parent = parent->getParent();
        } else {
            break;
        }
    }

    std::reverse(result.begin(), result.end());
    return result;
}

// #define DEBUG_PRINT

cppmm::Param process_param_type(const std::string& param_name,
                                const QualType& qt) {
    cppmm::Param result;
    result.name = param_name;
    result.is_const = qt.isConstQualified();
    result.is_ptr = qt->isPointerType();
    result.is_ref = qt->isReferenceType();

    if (is_builtin(qt)) {
        result.type = cppmm::Type{qt.getAsString(), {}};
        result.requires_cast = false;
    } else if (qt->isRecordType()) {
        const CXXRecordDecl* crd = qt->getAsCXXRecordDecl();
        if (crd->getNameAsString() == "unique_ptr") {
            const auto* tst = qt->getAs<TemplateSpecializationType>();
            result =
                process_param_type(param_name, tst->getArgs()->getAsType());
            result.is_uptr = true;
        } else {
            const CXXRecordDecl* crd = qt->getAsCXXRecordDecl();
            result.type = cppmm::Type{crd->getNameAsString(),
                                    get_namespaces(qt->getAsCXXRecordDecl())};
            result.requires_cast = !(crd->getNameAsString() == "basic_string" ||
                                     crd->getNameAsString() == "string_view");
        }
    } else if (is_recordpointer(qt)) {
        result.is_const = qt->getPointeeType().isConstQualified();
        result.requires_cast = true;
        const CXXRecordDecl* crd = qt->getPointeeType()->getAsCXXRecordDecl();
        if (crd) {
            result.type =
                cppmm::Type{crd->getNameAsString(), get_namespaces(crd)};
        } else {
            result.type = cppmm::Type{qt.getAsString(), {}};
        }
        result.requires_cast = !(crd->getNameAsString() == "basic_string" ||
                                 crd->getNameAsString() == "string_view");
    }

    return result;
}

std::unordered_map<std::string, cppmm::Class> classes;

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
    os << "auto " << method.name << "(" << ps::join(", ", param_str) << ") -> "
       << method.return_type;
    if (method.is_const) {
        os << " const";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os,
                         const cppmm::ExportedMethod& method) {
    if (method.is_static) {
        os << "static ";
    }
    os << "auto " << method.name << "(" << ps::join(", ", method.params)
       << ") -> " << method.return_type;
    if (method.is_const) {
        os << " const";
    }
    return os;
}
} // namespace fmt

std::string get_method_comment(const CXXMethodDecl* method) {
    ASTContext& ctx = method->getASTContext();
    SourceManager& sm = ctx.getSourceManager();
    const RawComment* rc = ctx.getRawCommentForDeclNoCache(method);
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

cppmm::Method process_method(const CXXMethodDecl* method) {
    // const auto return_param = process_param_type("RET",
    // method->getReturnType());
    // fmt::print("        -> {}\n",
    // method->getReturnType().getCanonicalType().getAsString());
    std::vector<cppmm::Param> params;
    for (const auto& p : method->parameters()) {
        const auto param_name = p->getNameAsString();
        params.push_back(process_param_type(param_name, p->getType()));
        // fmt::print("        {} {}\n",
        // p->getType().getCanonicalType().getAsString(), param_name);
    }

    std::string comment = get_method_comment(method);

    return cppmm::Method{.name = method->getNameAsString(),
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
            const auto method_name = method->getNameAsString();
            const auto class_name = method->getParent()->getNameAsString();

            // first make sure this method is on a class we want to export
            // this should never return if we're filtering correctly at the
            // top level.
            auto it_class = ex_classes.find(class_name);
            if (it_class == ex_classes.end()) {
                return;
            }

            if (classes.find(class_name) == classes.end()) {
                auto namespaces = get_namespaces(method->getParent());
                classes[class_name] = cppmm::Class{class_name, namespaces, {}};
            }

            const auto this_ex_method = cppmm::ExportedMethod(method);
            // fmt::print("    matching {}\n", this_ex_method);

            // now see if we can find the method in the exported methods on
            // the exported class
            const auto it_method = std::find_if(
                it_class->second.methods.begin(),
                it_class->second.methods.end(),
                [&this_ex_method](const cppmm::ExportedMethod& ex_method) {
                    bool match = ex_method == this_ex_method;
                    if (!match && ex_method.name == this_ex_method.name) {
                        fmt::print("      REJECTED:\n");
                        fmt::print("            {}:\n", this_ex_method);
                        fmt::print("            {}:\n", ex_method);
                    }
                    return match;
                });

            if (it_method == it_class->second.methods.end()) {
                return;
            }
            fmt::print("        MATCHED {} {}\n", method_name,
                       method->getQualifiedNameAsString());

            // now grab the method parameters for further processing
            classes[class_name].methods.push_back(process_method(method));
        }
    }
};

class CppmmConsumer : public ASTConsumer {
    MatchFinder _match_finder;
    CppmmMatchHandler _handler;

public:
    explicit CppmmConsumer(ASTContext* context) {
        // const auto input_class_names = std::vector<std::string>{"ImageSpec",
        // "ImageInput", "ImageOutput", "IOProxy"};
        // const auto input_class_names =
        // std::vector<std::string>{"ImageInput"};
        for (const auto& input_class : ex_classes) {
            DeclarationMatcher decl_matcher =
                cxxMethodDecl(
                    ofClass(hasName(input_class.first)),
                    unless(hasAncestor(namespaceDecl(hasName("cppmm_bind")))))
                    .bind("methodDecl");
            _match_finder.addMatcher(decl_matcher, &_handler);
        }
    }

    virtual void HandleTranslationUnit(ASTContext& context) {
        _match_finder.matchAST(context);

        fmt::print("{:-^30}\n", " DONE ");
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

class MatchExportsCallback : public MatchFinder::MatchCallback {
    CompilerInstance& _compiler;
    virtual void run(const MatchFinder::MatchResult& result) {
        if (const CXXMethodDecl* method =
                result.Nodes.getNodeAs<CXXMethodDecl>("methodDecl")) {

            cppmm::ExportedMethod ex_method(method);
            const auto class_name = method->getParent()->getNameAsString();

            if (method->hasAttrs()) {
                for (const auto& attr : method->attrs()) {
                    // fmt::print("ATTR: {}\n", attr->getSpelling());
                    const auto src = Lexer::getSourceText(
                        CharSourceRange::getTokenRange(attr->getRange()),
                        _compiler.getSourceManager(), _compiler.getLangOpts());
                    // fmt::print("    {}\n", src.str());

                    // TODO: if we have an annotate with cppmm:ignore or
                    // cppmm:manual, put these onto a list of methods we don't
                    // need to convert or warn about being missing
                }
            }

            if (ex_classes.find(class_name) == ex_classes.end()) {
                auto namespaces = get_namespaces(method->getParent());
                ex_classes[class_name] =
                    cppmm::ExportedClass{class_name, namespaces, {}};
            }

            ex_classes[class_name].methods.push_back(ex_method);
        }
    }

public:
    MatchExportsCallback(CompilerInstance& compiler) : _compiler(compiler) {}
};

class MatchExportsConsumer : public ASTConsumer {
    MatchFinder _match_finder;
    MatchExportsCallback _handler;

public:
    explicit MatchExportsConsumer(ASTContext* context,
                                  CompilerInstance& compiler)
        : _handler(compiler) {
        DeclarationMatcher decl_matcher =
            cxxMethodDecl(hasAncestor(namespaceDecl(hasName("cppmm_bind"))))
                .bind("methodDecl");
        _match_finder.addMatcher(decl_matcher, &_handler);
    }

    virtual void HandleTranslationUnit(ASTContext& context) {
        _match_finder.matchAST(context);

        fmt::print("{:-^30}\n", " DONE ");
    }
};

class MatchExportsAction : public ASTFrontendAction {
public:
    virtual std::unique_ptr<ASTConsumer>
    CreateASTConsumer(CompilerInstance& compiler, StringRef in_file) {
        return std::unique_ptr<ASTConsumer>(
            new MatchExportsConsumer(&compiler.getASTContext(), compiler));
    }
};

// Apply a custom category to all command-line options so that they are the
// only ones displayed.
static llvm::cl::OptionCategory MyToolCategory("my-tool options");

// CommonOptionsParser declares HelpMessage with a description of the common
// command-line options related to the compilation database and input files.
// It's nice to have this help message in all tools.
static cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);

// A help message for this specific tool can be added afterwards.
static cl::extrahelp MoreHelp("\nMore help text...\n");

static cl::opt<std::string> def_file("d", cl::desc("Def file"));

int main(int argc, const char** argv) {
    CommonOptionsParser OptionsParser(argc, argv, MyToolCategory);
    ClangTool Tool(OptionsParser.getCompilations(),
                   OptionsParser.getSourcePathList());

    namespace_renames["OpenImageIO_v2_2"] = "OIIO";

    auto match_exports_action = newFrontendActionFactory<MatchExportsAction>();
    int result = Tool.run(match_exports_action.get());

    for (const auto& ex_cls : ex_classes) {
        fmt::print("{}\n", ex_cls.first);
        for (const auto& method : ex_cls.second.methods) {
            // fmt::print("    auto {}({}) -> {}\n", method.name,
            //            ps::join(", ", method.params), method.return_type);
            fmt::print("    {}\n", method);
        }
    }

    auto cppmm_action = newFrontendActionFactory<CppmmAction>();
    result = Tool.run(cppmm_action.get());

    fmt::print("{:-^30}\n", " OUTPUT ");

    std::string declarations;
    std::string definitions;

    for (const auto& cls : classes) {

        std::string class_type = fmt::format(
            "{}{}", prefix_from_namespaces(cls.second.namespaces, "_"),
            cls.first);

        declarations = fmt::format("{}\n\ntypedef struct {1} {1};",
                                   declarations, class_type);

        std::string method_prefix = fmt::format(
            "{}{}", prefix_from_namespaces(cls.second.namespaces, "_"),
            cls.first);

        for (auto method : cls.second.methods) {
            auto c_method_name =
                fmt::format("{}_{}", method_prefix, method.name);

            std::vector<std::string> param_decls;
            std::transform(method.params.begin(), method.params.end(),
                           std::back_inserter(param_decls),
                           cppmm::get_c_function_decl);

            std::string ret = cppmm::get_c_function_decl(method.return_type);

            std::string declaration;
            if (method.is_static) {
                declaration = fmt::format("{} {}({})", ret, c_method_name,
                                          ps::join(", ", param_decls));
            } else {
                std::string constqual;
                if (method.is_const) {
                    constqual = "const ";
                }
                declaration = fmt::format("{} {}({}{}* self", ret,
                                          c_method_name, constqual, class_type);
                if (param_decls.size()) {
                    declaration = fmt::format("{}, {})", declaration,
                                              ps::join(", ", param_decls));
                } else {
                    declaration = fmt::format("{})", declaration);
                }
            }

            // fmt::print("// decl\n{};\n", declaration);
            fmt::print("{}\n", method.comment);
            fmt::print("{};\n", declaration);

            declarations = fmt::format("{}\n{}\n{};\n", declarations,
                                       method.comment, declaration);

            std::string body = "    return ";
            if (method.return_type.requires_cast) {
                body += "to_c(";
            }
            if (method.is_static) {
                body += prefix_from_namespaces(cls.second.namespaces, "::") +
                        cls.first + "::";
            } else {
                body += "to_cpp(self)->";
            }
            body += method.name;
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

            fmt::print("// def\n{}\n\n", definition);

            definitions = fmt::format("{}\n\n\n{}\n", definitions, definition);
        }
    }

    auto out = fopen("testbind.cpp", "w");
    fprintf(out, "%s", definitions.c_str());

    out = fopen("testbind.h", "w");
    fprintf(out, "#pragma once\n\n");
    fprintf(out, "#ifdef __cplusplus\nextern \"C\" {\n#endif\n\n");
    fprintf(out, "%s", declarations.c_str());
    fprintf(out, "#ifdef __cplusplus\n}\n#endif\n\n");

    return result;
}
