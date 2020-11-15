#include <algorithm>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <unordered_map>

#include "clang/Frontend/FrontendAction.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/Support/CommandLine.h"

#include <fmt/format.h>
#include <fmt/printf.h>

#include "filesystem.hpp"
#include "pystring.h"

#include "attributes.hpp"
#include "decls.hpp"
#include "enum.hpp"
#include "exports.hpp"
#include "function.hpp"
#include "generator_c.hpp"
#include "generator_rust-sys.hpp"
#include "match_bindings.hpp"
#include "match_decls.hpp"
#include "method.hpp"
#include "namespaces.hpp"
#include "param.hpp"
#include "record.hpp"
#include "type.hpp"

using namespace clang::tooling;
using namespace llvm;
using namespace clang;
using namespace clang::ast_matchers;

namespace ps = pystring;
namespace fs = ghc::filesystem;

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
static cl::opt<std::string> opt_output_directory(
    "o",
    cl::desc(
        "Directory under which output project directories will be written"));
static cl::list<std::string>
    opt_rename_namespace("n", cl::desc("Rename namespace <to>=<from>"));
static cl::opt<std::string> opt_rust_sys_directory(
    "rust-sys",
    cl::desc(
        "Directory under which rust-sys project will be written"));

static cl::list<std::string> opt_includes("i", cl::desc("Extra includes for the project"));
static cl::list<std::string> opt_libraries("l", cl::desc("Libraries to link against"));

int main(int argc, const char** argv) {
    std::vector<std::string> project_includes = parse_project_includes(argc, argv);
    CommonOptionsParser OptionsParser(argc, argv, CppmmCategory);

    std::string cwd = fs::current_path();
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
                dir_paths.push_back(entry.path().string());
            }
        }
    } else {
        // otherwise we'll assume we've been given a list of source files to
        // work with (old behaviour)
        // TODO: can we reliably keep this working?
        for (const auto& s : src_path) {
            dir_paths.push_back(s);
        }
    }
    ClangTool Tool(OptionsParser.getCompilations(),
                   ArrayRef<std::string>(dir_paths));

    std::string output_dir = cwd;
    if (opt_output_directory != "") {
        output_dir = opt_output_directory;
    }

    for (const auto& i: opt_includes) {
        project_includes.push_back(i);
    }

    std::vector<std::string> project_libraries;
    for (const auto& l: opt_libraries) {
        project_libraries.push_back(l);
    }

    // fmt::print("source files: [{}]\n",
    //            ps::join(", ", OptionsParser.getSourcePathList()));

    // get direct includes from the binding files to re-insert into the
    // generated bindings
    for (const auto& src : dir_paths) {
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
    auto match_exports_action =
        newFrontendActionFactory<cppmm::MatchBindingsAction>();
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
    auto cppmm_action = newFrontendActionFactory<cppmm::MatchDeclsAction>();
    result = Tool.run(cppmm_action.get());

    // fmt::print("{:-^30}\n", " OUTPUT ");
    // fmt::print("Types: \n");
    // for (const auto& type : ex_types) {
    //     fmt::print("    {}\n", type.second->name);
    // }

    if (!fs::exists(output_dir) && !fs::create_directories(output_dir)) {
        fmt::print("ERROR: could not create output directory '{}'\n",
                   output_dir);
        return -2;
    }

    //--------------------------------------------------------------------------
    // Finally - process the filtered methods to generate the actual
    // bindings we'll generate one file of bindings for each file of input,
    // and stick all the bindings in that output, together with all the
    // necessary includes
    std::vector<std::unique_ptr<cppmm::Generator>> generators;
    generators.push_back(
        std::unique_ptr<cppmm::Generator>(new cppmm::GeneratorC(output_dir)));

    if (opt_rust_sys_directory != "") {
        std::string output_dir = opt_rust_sys_directory;
        if (!fs::exists(output_dir) && !fs::create_directories(output_dir)) {
            fmt::print("ERROR: could not create output directory '{}'\n",
                       output_dir);
            return -2;
        }

        generators.push_back(std::unique_ptr<cppmm::Generator>(new cppmm::GeneratorRustSys(output_dir)));
    }

    for (const auto& g : generators) {
        g->generate(cppmm::ex_files, cppmm::files, cppmm::records,
                    cppmm::enums, cppmm::vectors, project_includes,
                    project_libraries);
    }

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
