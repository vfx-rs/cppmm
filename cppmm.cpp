#include <unordered_map>
#include <algorithm>

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

namespace cppmm {

struct Type {
    std::string name;
    std::vector<std::string> namespaces;
};

struct Param {
    std::string name;
    Type type;
    bool is_ptr = false;
    bool is_ref = false;
    bool is_const = false;
};

struct Method {
    std::string name;
    bool is_const = false;
    bool is_static = false;
    Param return_type;
    std::vector<Param> params;
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
    }

    std::string name;
    std::string return_type;
    // vector of canonical typenames that are this method's parameters.
    std::vector<std::string> params;
};

bool operator==(const ExportedMethod& a, const ExportedMethod& b) {
    return a.name == b.name && a.return_type == b.return_type &&
           a.params == b.params;
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
    } else if (qt->isRecordType()) {
        const CXXRecordDecl* crd = qt->getAsCXXRecordDecl();
        result.type = cppmm::Type{crd->getNameAsString(),
                                  get_namespaces(qt->getAsCXXRecordDecl())};
    } else if (is_recordpointer(qt)) {
        const CXXRecordDecl* crd = qt->getPointeeType()->getAsCXXRecordDecl();
        if (crd) {
            result.type = cppmm::Type{crd->getNameAsString(),
                                    get_namespaces(crd)};
        } else {
            result.type = cppmm::Type{qt.getAsString(), {}};
        }
    }

#if 0
    std::string str_const = "";
    // if (qt.isConstQualified()) {
    //     str_const = "CONST";
    // }

    if (is_builtin(qt)) {
#if defined(DEBUG_PRINT)
        fmt::print("PARAM {} BUILTIN {} {} ({})\n", param_name, str_const,
                   qt.getAsString(), qt.getCanonicalType().getAsString());
#endif

        result.cpp_type = qt.getAsString();
        result.c_type = qt.getCanonicalType().getAsString();

    } else if (qt->isRecordType()) {
        const CXXRecordDecl* crd = qt->getAsCXXRecordDecl();
#if defined(DEBUG_PRINT)
        fmt::print("PARAM {} CXXRecordDecl {} NAME {} QNAME {}\n", param_name,
                   str_const, crd->getNameAsString(),
                   crd->getQualifiedNameAsString());
#endif

        if (crd->getNameAsString() == "basic_string" ||
            crd->getNameAsString() == "string_view") {
            result.cpp_type = crd->getNameAsString();
            result.c_type = "char";
            result.is_const = true;
            result.is_pointer = true;
        } else {
            result.cpp_type = crd->getQualifiedNameAsString();
            result.c_type =
                ps::replace(crd->getQualifiedNameAsString(), "::", "_");
            result.is_const = qt.isConstQualified();
            result.is_pointer = false;
        }

    } else if (is_recordpointer(qt)) {
        const CXXRecordDecl* crd = qt->getPointeeType()->getAsCXXRecordDecl();

        result.is_pointer = true;
        std::string str_ptr_const("");
        if (qt->getPointeeType().isConstQualified()) {
            str_ptr_const = "CONST";
            result.is_const = true;
        }
        if (qt->isReferenceType()) {
            str_ptr_const += " REF";
            if (crd->getNameAsString() == "basic_string" ||
                crd->getNameAsString() == "string_view") {
                result.cpp_type = crd->getNameAsString();
                result.c_type = "char";
                result.is_const = true;
                result.is_pointer = true;
                return result;
            }

        } else {
            str_ptr_const += " PTR";
        }
#if defined(DEBUG_PRINT)
        fmt::print("PARAM {} CXXRecordDecl {} {} NAME {} QNAME {}\n",
                   param_name, str_const, str_ptr_const, crd->getNameAsString(),
                   crd->getQualifiedNameAsString());
#endif

        result.cpp_type = crd->getQualifiedNameAsString();
        result.c_type = ps::replace(crd->getQualifiedNameAsString(), "::", "_");
    }
#endif

    return result;
}

std::unordered_map<std::string, cppmm::Class> classes;

namespace fmt {
std::ostream& operator<<(std::ostream& os, const cppmm::Param& param) {
    if (param.is_const) {
        os << "const ";
    }
    auto ns = param.type.namespaces;
    std::reverse(ns.begin(), ns.end());
    os << ps::join("::", ns) << "::";
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

std::ostream& operator<<(std::ostream& os, const cppmm::Method& method) {
    std::vector<std::string> param_str;
    param_str.reserve(method.params.size());
    for (const auto& p : method.params) {
        param_str.emplace_back(fmt::format("{}", p));
    }
    os << "auto " << method.name << "(" << ps::join(", ", param_str) << ") -> "
       << method.return_type;
    return os;
}

std::ostream& operator<<(std::ostream& os,
                         const cppmm::ExportedMethod& method) {
    os << "auto " << method.name << "(" << ps::join(", ", method.params)
       << ") -> " << method.return_type;
    return os;
}
} // namespace fmt

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

    return cppmm::Method{
        .name = method->getNameAsString(),
        .is_const = method->isConst(),
        .is_static = method->isStatic(),
        .return_type = process_param_type("", method->getReturnType()),
        .params = params,
    };
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
                classes[class_name] = cppmm::Class {
                    class_name,
                    namespaces,
                    {}
                };
            }

            const auto this_ex_method = cppmm::ExportedMethod(method);
            // fmt::print("    matching {}\n", this_ex_method);

            // now see if we can find the method in the exported methods on
            // the exported class
            const auto it_method = std::find_if(
                it_class->second.methods.begin(),
                it_class->second.methods.end(),
                [&this_ex_method](const cppmm::ExportedMethod& ex_method) {
                    return ex_method == this_ex_method;
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
        // const auto input_class_names = std::vector<std::string>{"ImageInput"};
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
                ex_classes[class_name] = cppmm::ExportedClass {
                    class_name,
                    namespaces,
                    {}
                };
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

    for (const auto& cls : classes) {
        std::string prefix = fmt::format("{}", cls.first);
        if (cls.second.namespaces.size()) {
            auto ns = cls.second.namespaces;
            std::reverse(ns.begin(), ns.end());
            prefix = fmt::format("{}_{}", ps::join("_", ns), prefix);
        }
        fmt::print("{}\n", cls.first);
        for (auto method : cls.second.methods) {
            method.name = fmt::format("{}_{}", prefix, method.name);
            fmt::print("    {}\n", method);
        }
    }

    return result;
}
