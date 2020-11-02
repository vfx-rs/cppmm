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

struct AttrDesc {
    enum Kind {
        Ignore,
        Rename,
        Manual,
    };

    std::string params;
    Kind kind;
};

std::optional<AttrDesc> parse_attributes(std::string attr_src) {
    auto first = attr_src.find("\"");
    auto second = attr_src.find("\"", first + 1);
    attr_src = attr_src.substr(first + 1, second - first - 1);
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
    }

    fmt::print("Warning Could not parse attribute '{}'\n", attr_src);

    return std::nullopt;
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

struct Class {
    std::string name;
    std::vector<std::string> namespaces;
    std::unordered_map<std::string, Method> methods;
};

struct ExportedMethod {
    ExportedMethod(const CXXMethodDecl* method, std::vector<AttrDesc> attrs)
        : attrs(attrs) {
        method = method->getCanonicalDecl();
        cpp_name = method->getNameAsString();
        return_type = method->getReturnType().getCanonicalType().getAsString();
        for (const auto& p : method->parameters()) {
            params.push_back(p->getType().getCanonicalType().getAsString());
        }
        is_const = method->isConst();
        is_static = method->isStatic();

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
    bool is_const = false;
    bool is_static = false;
};

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
};

} // namespace cppmm

std::unordered_map<std::string, cppmm::ExportedFile> ex_files;
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
    os << "auto " << method.cpp_name << "(" << ps::join(", ", param_str)
       << ") -> " << method.return_type;
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
    os << "auto " << method.cpp_name << "(" << ps::join(", ", method.params)
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

cppmm::Method process_method(const CXXMethodDecl* method,
                             const cppmm::ExportedMethod& ex_method) {
    std::vector<cppmm::Param> params;
    for (const auto& p : method->parameters()) {
        const auto param_name = p->getNameAsString();
        // TODO: we get the canonical type here to see through typedefs but
        // do we want to parse them properly and redeclare a C version?
        params.push_back(
            process_param_type(param_name, p->getType().getCanonicalType()));
    }

    std::string comment = get_method_comment(method);

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
                auto namespaces = get_namespaces(method->getParent());
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
    }
};

class CppmmConsumer : public ASTConsumer {
    MatchFinder _match_finder;
    CppmmMatchHandler _handler;

public:
    explicit CppmmConsumer(ASTContext* context) {
        for (const auto& input_class : ex_classes) {
            // Match all class methods that are NOT in the cppmm_bind namespace
            // (or we'll get duplicates)
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

            // If there are attributes, parse them looking for cppmm annotations
            std::vector<AttrDesc> attrs;
            if (method->hasAttrs()) {
                for (const auto& attr : method->attrs()) {
                    const auto src = Lexer::getSourceText(
                        CharSourceRange::getTokenRange(attr->getRange()),
                        _compiler.getSourceManager(), _compiler.getLangOpts());
                    if (auto opt = parse_attributes(src.str())) {
                        attrs.push_back(*opt);
                    }
                }
            }
            cppmm::ExportedMethod ex_method(method, attrs);
            const auto class_name = method->getParent()->getNameAsString();

            // check if we've seen the class this metho belongs to before, and
            // if not process it
            if (ex_classes.find(class_name) == ex_classes.end()) {
                ASTContext& ctx = method->getASTContext();
                SourceManager& sm = ctx.getSourceManager();

                std::string filename = sm.getFilename(method->getBeginLoc());

                auto namespaces = get_namespaces(method->getParent());
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
        // match all method declrations in the cppmm_bind namespace
        DeclarationMatcher decl_matcher =
            cxxMethodDecl(hasAncestor(namespaceDecl(hasName("cppmm_bind"))))
                .bind("methodDecl");
        _match_finder.addMatcher(decl_matcher, &_handler);
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
            new MatchExportsConsumer(&compiler.getASTContext(), compiler));
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
    namespace_renames["OpenImageIO_v2_2"] = "OIIO";

    //--------------------------------------------------------------------------
    // First pass - find all declarations in namespace cppmm_bind that will tell
    // us what we want to bind
    auto match_exports_action = newFrontendActionFactory<MatchExportsAction>();
    int result = Tool.run(match_exports_action.get());

    /*
    for (const auto& ex_cls : ex_classes) {
        fmt::print("{} ({})\n", ex_cls.first, ex_cls.second.filename);
        for (const auto& method : ex_cls.second.methods) {
            // fmt::print("    auto {}({}) -> {}\n", method.name,
            //            ps::join(", ", method.params), method.return_type);
            fmt::print("    {}\n", method);
        }
    }
    */

    //--------------------------------------------------------------------------
    // Second pass - find matching methods to the ones declared in the first
    // pass and filter out the ones we want to generate bindings for
    auto cppmm_action = newFrontendActionFactory<CppmmAction>();
    result = Tool.run(cppmm_action.get());

    // fmt::print("{:-^30}\n", " OUTPUT ");

    std::string casts_macro_invocaions;

    //--------------------------------------------------------------------------
    // Finally - process the filtered methods to generate the actual bindings
    // we'll generate one file of bindings for each file of input, and stick
    // all the bindings in that output, together with all the necessary includes
    for (const auto& bind_file : ex_files) {

        std::string declarations;
        std::string definitions;

        for (const auto& file_class_name : bind_file.second.classes) {
            const auto& cls = classes[file_class_name];
            // fmt::print("{}\n", cls.name);

            std::string class_type = fmt::format(
                "{}{}", prefix_from_namespaces(cls.namespaces, "_"), cls.name);

            declarations = fmt::format("{0}\n\ntypedef struct {1} {1};",
                                       declarations, class_type);

            std::string method_prefix = fmt::format(
                "{}{}", prefix_from_namespaces(cls.namespaces, "_"), cls.name);

            casts_macro_invocaions += create_casts(cls);

            for (auto method_pair : cls.methods) {
                const auto& method = method_pair.second;
                auto c_method_name =
                    fmt::format("{}_{}", method_prefix, method.c_name);
                // fmt::print("    {}\n", c_method_name);

                std::vector<std::string> param_decls;
                std::transform(method.params.begin(), method.params.end(),
                               std::back_inserter(param_decls),
                               cppmm::get_c_function_decl);

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

        const auto basename = ps::os::path::basename(bind_file.first);
        std::string root, ext;
        ps::os::path::splitext(root, ext, basename);
        const auto header = fmt::format("{}.h", root);
        const auto implementation = fmt::format("{}.cpp", root);

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

#ifdef __cplusplus
extern "C" {{
#endif

{}

#ifdef __cplusplus
}}
#endif
    )#",
            declarations);

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
        fmt::print("\n");
        fmt::print("The following methods were not bound, ignored or manually "
                   "overriden:\n");
        for (const auto& ex_class : ex_classes) {
            fmt::print("{}\n", ex_class.second.name);
            for (const auto& rejected_method :
                 ex_class.second.rejected_methods) {
                fmt::print("    {}\n", rejected_method);
            }
        }
    }

    return result;
}
