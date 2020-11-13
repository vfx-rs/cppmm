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

int main(int argc, const char** argv) {
    CommonOptionsParser OptionsParser(argc, argv, CppmmCategory);
    ClangTool Tool(OptionsParser.getCompilations(),
                   OptionsParser.getSourcePathList());

    // fmt::print("source files: [{}]\n",
    //            ps::join(", ", OptionsParser.getSourcePathList()));

    std::string cwd = fs::current_path();

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

    //--------------------------------------------------------------------------
    // Finally - process the filtered methods to generate the actual
    // bindings we'll generate one file of bindings for each file of input,
    // and stick all the bindings in that output, together with all the
    // necessary includes
    std::vector<std::unique_ptr<cppmm::Generator>> generators;
    generators.push_back(
        std::unique_ptr<cppmm::Generator>(new cppmm::GeneratorC()));

    for (const auto& g : generators) {
        g->generate(cppmm::ex_files, cppmm::files, cppmm::records, cppmm::enums,
                    cppmm::vectors);
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
