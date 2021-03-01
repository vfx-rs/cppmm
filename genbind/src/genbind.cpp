#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <unordered_map>

#include "clang/AST/ASTContext.h"
#include "clang/AST/Decl.h"
#include "clang/AST/DeclCXX.h"
#include "clang/AST/DeclTemplate.h"
#include "clang/AST/Type.h"
#include "clang/Basic/LLVM.h"
#include "llvm/Support/Casting.h"
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/ASTMatchers/ASTMatchFinder.h>
#include <clang/ASTMatchers/ASTMatchers.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendAction.h>

#include "clang/Frontend/FrontendAction.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/Support/CommandLine.h"

#include "filesystem.hpp"
#include "pystring.h"

#define SPDLOG_ACTIVE_LEVEL TRACE

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

using namespace clang::tooling;
using namespace llvm;
using namespace clang;
using namespace clang::ast_matchers;

namespace ps = pystring;
namespace fs = ghc::filesystem;

class GenBindingCallback
    : public clang::ast_matchers::MatchFinder::MatchCallback {
    virtual void
    run(const clang::ast_matchers::MatchFinder::MatchResult& result);
};

void GenBindingCallback::run(const MatchFinder::MatchResult& result) {
    if (const CXXRecordDecl* rec_decl =
            result.Nodes.getNodeAs<CXXRecordDecl>("recordDecl")) {
        // handle_cxx_record_decl(rec_decl);
        SPDLOG_WARN("Got {}", rec_decl->getQualifiedNameAsString());

    } else if (const TypeAliasDecl* tdecl =
                   result.Nodes.getNodeAs<TypeAliasDecl>("typeAliasDecl")) {
        if (const auto* crd =
                tdecl->getUnderlyingType()->getAsCXXRecordDecl()) {
            SPDLOG_INFO("GOT CXXRECORDTTYPE {} from TAD {}",
                        crd->getQualifiedNameAsString(),
                        tdecl->getNameAsString());
            // handle_typealias_decl(tdecl, crd);
        }
    } else if (const FunctionDecl* function =
                   result.Nodes.getNodeAs<FunctionDecl>("functionDecl")) {
        // handle_binding_function(function);
    } else if (const EnumDecl* enum_decl =
                   result.Nodes.getNodeAs<EnumDecl>("enumDecl")) {
        // handle_binding_enum(enum_decl);
    } else if (const VarDecl* var_decl =
                   result.Nodes.getNodeAs<VarDecl>("varDecl")) {
        // handle_binding_var(var_decl);
    } else if (const ClassTemplateDecl* ctd =
                   result.Nodes.getNodeAs<ClassTemplateDecl>(
                       "classTemplateDecl")) {
        ASTContext& ctx = ctd->getASTContext();
        SourceManager& sm = ctx.getSourceManager();
        const auto& loc = ctd->getLocation();
        std::string filename = sm.getFilename(loc).str();

        SPDLOG_WARN("Got CTD {} in {}", ctd->getQualifiedNameAsString(),
                    filename);
    }
}

class GenBindingConsumer : public clang::ASTConsumer {
    clang::ast_matchers::MatchFinder _match_finder;
    GenBindingCallback _handler;

public:
    explicit GenBindingConsumer(clang::ASTContext* context);
    virtual void HandleTranslationUnit(clang::ASTContext& context);
};

class GenBindingAction : public clang::ASTFrontendAction {
public:
    virtual std::unique_ptr<clang::ASTConsumer>
    CreateASTConsumer(clang::CompilerInstance& compiler,
                      llvm::StringRef in_file) {
        return std::unique_ptr<clang::ASTConsumer>(
            new GenBindingConsumer(&compiler.getASTContext()));
    }
};

GenBindingConsumer::GenBindingConsumer(ASTContext* context) {
    // match all record declrations in the cppmm_bind namespace
    SPDLOG_WARN("HELLOO");
    DeclarationMatcher record_decl_matcher =
        cxxRecordDecl(hasAncestor(namespaceDecl(hasName("Imath_2_5"))),
                      unless(isImplicit()))
            .bind("recordDecl");
    _match_finder.addMatcher(record_decl_matcher, &_handler);

    DeclarationMatcher ctd_matcher =
        classTemplateDecl(hasAncestor(namespaceDecl(hasName("Imath_2_5"))),
                          unless(isImplicit()))
            .bind("classTemplateDecl");
    _match_finder.addMatcher(ctd_matcher, &_handler);

    // // match all typedef declrations in the cppmm_bind namespace
    // DeclarationMatcher typedef_decl_matcher =
    //     typeAliasDecl(hasAncestor(namespaceDecl(hasName("cppmm_bind"))),
    //                   unless(hasAncestor(recordDecl())),
    //                   unless(isImplicit()))
    //         .bind("typeAliasDecl");
    // _match_finder.addMatcher(typedef_decl_matcher, &_handler);

    // // match all function declarations
    // DeclarationMatcher function_decl_matcher =
    //     functionDecl(hasAncestor(namespaceDecl(hasName("cppmm_bind"))),
    //                  unless(hasAncestor(recordDecl())))
    //         .bind("functionDecl");
    // _match_finder.addMatcher(function_decl_matcher, &_handler);

    // // match all enum declrations in the cppmm_bind namespace
    // DeclarationMatcher enum_decl_matcher =
    //     enumDecl(hasAncestor(namespaceDecl(hasName("cppmm_bind"))),
    //              unless(isImplicit()))
    //         .bind("enumDecl");
    // _match_finder.addMatcher(enum_decl_matcher, &_handler);

    // // match all variable declrations in the cppmm_bind namespace
    // DeclarationMatcher var_decl_matcher =
    //     varDecl(hasAncestor(namespaceDecl(hasName("cppmm_bind"))),
    //             unless(anyOf(isImplicit(), parmVarDecl())))
    //         .bind("varDecl");
    // _match_finder.addMatcher(var_decl_matcher, &_handler);
}

/// Run the binding AST matcher, then run secondary matchers to find functions
/// and enums we're interested in from the bindings (stored in the first pass)
void GenBindingConsumer::HandleTranslationUnit(ASTContext& context) {
    _match_finder.matchAST(context);

    SPDLOG_WARN("--- finished matching");
    /*
    for (const auto& fn : binding_functions) {
        SPDLOG_DEBUG("    {}", fn.first);
    }

    // add a matcher for each function we found in the binding
    for (const auto& kv : binding_functions) {
        for (const auto& fn : kv.second) {
            SPDLOG_DEBUG("Adding matcher for function {}", fn.short_name);
            DeclarationMatcher function_decl_matcher =
                functionDecl(
                    hasName(fn.short_name),
                    unless(hasAncestor(namespaceDecl(hasName("cppmm_bind")))),
                    unless(hasAncestor(recordDecl())))
                    .bind("libraryFunctionDecl");
            _library_finder.addMatcher(function_decl_matcher,
                                       &_library_handler);
        }
    }

    // and a matcher for each enum
    for (const auto& kv : binding_enums) {
        SPDLOG_DEBUG("Adding matcher for enum {}", kv.first);
        DeclarationMatcher enum_decl_matcher =
            enumDecl(hasName(kv.second.short_name),
                     unless(hasAncestor(namespaceDecl(hasName("cppmm_bind")))),
                     unless(hasAncestor(recordDecl())))
                .bind("libraryEnumDecl");
        _library_finder.addMatcher(enum_decl_matcher, &_library_handler);
    }

    // and a matcher for each var
    for (const auto& kv : binding_vars) {
        SPDLOG_DEBUG("Adding matcher for var {}", kv.first);
        DeclarationMatcher var_decl_matcher =
            varDecl(hasName(kv.second.short_name),
                    unless(hasAncestor(namespaceDecl(hasName("cppmm_bind")))))
                .bind("libraryVarDecl");
        _library_finder.addMatcher(var_decl_matcher, &_library_handler);
    }

    _library_finder.matchAST(context);
    */
}
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

std::vector<std::string> parse_project_includes(int argc, const char** argv) {
    std::vector<std::string> result;
    for (int i = 0; i < argc; ++i) {
        std::string a(argv[i]);
        if (a.find("-I") == 0) {
            result.push_back(a.substr(2, std::string::npos));
        }
    }
    return result;
}

// list of includes for each input source file
// this global is read in process_bindings.cpp
std::unordered_map<std::string, std::vector<std::string>> source_includes;
std::vector<std::string> project_includes;

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

static cl::opt<int> opt_verbosity(
    "v", cl::desc("Verbosity. 0=errors, 1=warnings, 2=info, 3=debug, 4=trace"));

static cl::opt<std::string> opt_output_directory(
    "o",
    cl::desc(
        "Directory under which output project directories will be written"));
static cl::list<std::string>
    opt_rename_namespace("n", cl::desc("Rename namespace <to>=<from>"));
static cl::opt<std::string> opt_rust_sys_directory(
    "rust-sys",
    cl::desc("Directory under which rust-sys project will be written"));

static cl::list<std::string>
    opt_includes("i", cl::desc("Extra includes for the project"));
static cl::list<std::string>
    opt_libraries("l", cl::desc("Libraries to link against"));

int main(int argc_, const char** argv_) {
    // set up logging
    auto _console = spdlog::stdout_color_mt("console");
    std::string cwd = fs::current_path();

    // FIXME: there's got to be a more sensible way of doing this but I can't
    // figure it out...
    int argc = argc_ + 2;
    const char** argv = new const char*[argc + 1];
    int i;
    bool has_ddash = false;
    for (i = 0; i < argc_; ++i) {
        argv[i] = argv_[i];
        if (!strcmp(argv[i], "--")) {
            has_ddash = true;
        }
    }

    // get the path to the binary, assuming that the resources folder will be
    // stored alongside it
    // FIXME: this method will work only on linux...
    auto exe_path = cwd / fs::path(argv[0]);
    if (fs::is_symlink(exe_path)) {
        exe_path = fs::read_symlink(exe_path);
    }
    if (exe_path.empty()) {
        SPDLOG_CRITICAL("Could not get exe path");
        return -1;
    }

    std::string respath1 = (exe_path.parent_path() / "resources").string();
    if (!has_ddash) {
        argv[i++] = "--";
        argc++;
    }
    argv[i++] = "-isystem";
    argv[i++] = respath1.c_str();

    project_includes = parse_project_includes(argc, argv);

    CommonOptionsParser OptionsParser(argc, argv, CppmmCategory);

    switch (opt_verbosity) {
    case 0:
        spdlog::set_level(spdlog::level::err);
        break;
    case 1:
        spdlog::set_level(spdlog::level::warn);
        break;
    case 2:
        spdlog::set_level(spdlog::level::info);
        break;
    case 3:
        spdlog::set_level(spdlog::level::debug);
        break;
    case 4:
        spdlog::set_level(spdlog::level::trace);
        break;
    default:
        spdlog::set_level(spdlog::level::warn);
        break;
    }
    spdlog::set_pattern("%20s:%4# %^[%5l]%$ %v");

    ArrayRef<std::string> src_path = OptionsParser.getSourcePathList();
    std::vector<std::string> dir_paths;
    if (src_path.size() == 1 && fs::is_directory(src_path[0])) {
        // we've been supplied a single directory to start from, find all the
        // cpp files under it to use as binding files
        // TODO: figure out a better directory structure, e.g.
        // /bind
        // /config.toml
        for (const auto& entry : fs::directory_iterator(src_path[0])) {
            if (entry.path().extension() == ".cpp") {
                dir_paths.push_back(
                    ps::os::path::abspath(entry.path().string(), cwd));
                SPDLOG_DEBUG("Found binding file {}", entry.path().string());
            }
        }
    } else {
        // otherwise we'll assume we've been given a list of source files to
        // work with (old behaviour)
        // TODO: can we reliably keep this working?
        for (const auto& s : src_path) {
            dir_paths.push_back(ps::os::path::abspath(s, cwd));
        }
    }
    auto& compdb = OptionsParser.getCompilations();

    for (const auto& f : compdb.getAllFiles()) {
        SPDLOG_WARN("f {}", f);
    }

    ClangTool Tool(compdb, ArrayRef<std::string>(dir_paths));

    Tool.mapVirtualFile("/usr/local/include/cppmm_bind.hpp", R"#(
#define CPPMM_IGNORE __attribute__((annotate("cppmm|ignore")))
#define CPPMM_RENAME(x) __attribute__((annotate("cppmm|rename|" #x)))
#define CPPMM_OPAQUEPTR __attribute__((annotate("cppmm|opaqueptr")))
#define CPPMM_OPAQUEBYTES __attribute__((annotate("cppmm|opaquebytes")))
#define CPPMM_VALUETYPE __attribute__((annotate("cppmm|valuetype")))

#define CPPMM_THROWS(EX, VAR) __attribute__((annotate("cppmm|throws|" #EX "|" #VAR)))
)#");

    std::string output_dir = cwd;
    if (opt_output_directory != "") {
        output_dir = opt_output_directory;
    }

    // for (const auto& i : opt_includes) {
    //     project_includes.push_back(i);
    // }

    // std::vector<std::string> project_libraries;
    // for (const auto& l : opt_libraries) {
    //     project_libraries.push_back(l);
    // }

    // get direct includes from the binding files to re-insert into the
    // generated bindings
    // for (const auto& src : dir_paths) {
    //     const auto src_path = ps::os::path::join(cwd, src);
    //     source_includes[src_path] = parse_file_includes(src_path);
    // }

    auto process_binding_action = newFrontendActionFactory<GenBindingAction>();
    int result = Tool.run(process_binding_action.get());

    if (!fs::exists(output_dir) && !fs::create_directories(output_dir)) {
        SPDLOG_ERROR("Could not create output directory '{}'", output_dir);
        return -2;
    }

    // cppmm::write_tus(output_dir);

    return result;
}
