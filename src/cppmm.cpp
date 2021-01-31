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

#include "filesystem.hpp"
#include "pystring.h"

/* #include "attributes.hpp" */
/* #include "decls.hpp" */
/* #include "enum.hpp" */
/* #include "exports.hpp" */
/* #include "function.hpp" */
/* #include "generator_c.hpp" */
/* #include "generator_rust-sys.hpp" */
/* #include "match_bindings.hpp" */
/* #include "match_decls.hpp" */
/* #include "method.hpp" */
/* #include "namespaces.hpp" */
/* #include "param.hpp" */
/* #include "record.hpp" */
/* #include "type.hpp" */

#include "process_binding.hpp"

// #include <fmt/format.h>
// #include <fmt/printf.h>

#define SPDLOG_ACTIVE_LEVEL TRACE

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

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

int main(int argc, const char** argv) {

    std::vector<std::string> project_includes =
        parse_project_includes(argc, argv);
    CommonOptionsParser OptionsParser(argc, argv, CppmmCategory);

    // set up logging
    auto _console = spdlog::stdout_color_mt("console");
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
    ClangTool Tool(OptionsParser.getCompilations(),
                   ArrayRef<std::string>(dir_paths));

    Tool.mapVirtualFile("/usr/local/include/cppmm_bind.hpp", R"#(
#define CPPMM_IGNORE __attribute__((annotate("cppmm:ignore")))
#define CPPMM_RENAME(x) __attribute__((annotate("cppmm:rename:" #x)))
#define CPPMM_OPAQUEPTR __attribute__((annotate("cppmm:opaqueptr")))
#define CPPMM_OPAQUEBYTES __attribute__((annotate("cppmm:opaquebytes")))
#define CPPMM_VALUETYPE __attribute__((annotate("cppmm:valuetype")))
)#");

    std::string output_dir = cwd;
    if (opt_output_directory != "") {
        output_dir = opt_output_directory;
    }

    for (const auto& i : opt_includes) {
        project_includes.push_back(i);
    }

    std::vector<std::string> project_libraries;
    for (const auto& l : opt_libraries) {
        project_libraries.push_back(l);
    }

    fmt::print("source files: [{}]\n",
               ps::join(", ", OptionsParser.getSourcePathList()));

    // get direct includes from the binding files to re-insert into the
    // generated bindings
    /* for (const auto& src : dir_paths) { */
    /*     const auto src_path = ps::os::path::join(cwd, src); */
    /*     const auto includes = parse_file_includes(src_path); */
    /*     cppmm::files[src_path] = {}; */
    /*     cppmm::files[src_path].includes = includes; */
    /* } */

    // Get namespace renames from command-line options
    /* for (const auto& o : opt_rename_namespace) { */
    /*     std::vector<std::string> toks; */
    /*     ps::split(o, toks, "="); */
    /*     if (toks.size() == 2) { */
    /*         cppmm::add_namespace_rename(toks[1], toks[0]); */
    /*     } */
    /* } */

    //--------------------------------------------------------------------------
    // First pass - find all declarations in namespace cppmm_bind that will
    // tell us what we want to bind
    SPDLOG_DEBUG("");
    SPDLOG_DEBUG(" -------------------------------");
    SPDLOG_DEBUG("|         BINDING PHASE         |");
    SPDLOG_DEBUG(" -------------------------------");
    SPDLOG_DEBUG("");
    auto process_binding_action =
        newFrontendActionFactory<cppmm::ProcessBindingAction>();
    int result = Tool.run(process_binding_action.get());
    // auto match_exports_action =
    //     newFrontendActionFactory<cppmm::MatchBindingsAction>();
    // int result = Tool.run(match_exports_action.get());

    // std::ofstream os;
    // os.open("out.xml", std::ios::out | std::ios::trunc);
    // cppmm::dump_nodes(os);
    cppmm::write_tus();

#if 0
    // for (const auto& ex_file : ex_files) {
    //     fmt::print("FILE: {}\n", ex_file.first);
    //     for (const auto& ex_fun : ex_file.second.functions) {
    //         fmt::print("    {}\n", ex_fun);
    //     }
    // }
    //

    SPDLOG_DEBUG("Binding records:");
    for (const auto& ex_record : cppmm::ex_records) {
        SPDLOG_DEBUG("\n{}\n", ex_record.second);
    }

    SPDLOG_DEBUG("Binding specializations:");
    for (const auto& ex_specvec : cppmm::ex_specs) {
        SPDLOG_DEBUG("{}", ex_specvec.first);
        for (const auto& ex_spec: ex_specvec.second) {
            SPDLOG_DEBUG("    {}", ex_spec);
        }
    }

    //--------------------------------------------------------------------------
    // Second pass - find matching methods to the ones declared in the first
    // pass and filter out the ones we want to generate bindings for
    SPDLOG_DEBUG("");
    SPDLOG_DEBUG(" --------------------------------");
    SPDLOG_DEBUG("|         MATCHING PHASE         |");
    SPDLOG_DEBUG(" --------------------------------");
    SPDLOG_DEBUG("");
    auto cppmm_action = newFrontendActionFactory<cppmm::MatchDeclsAction>();
    result = Tool.run(cppmm_action.get());

    // fmt::print("{:-^30}\n", " OUTPUT ");
    // fmt::print("Types: \n");
    // for (const auto& type : ex_types) {
    //     fmt::print("    {}\n", type.second->name);
    // }

    if (!fs::exists(output_dir) && !fs::create_directories(output_dir)) {
        SPDLOG_ERROR("Could not create output directory '{}'", output_dir);
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
            SPDLOG_ERROR("Could not create output directory '{}'", output_dir);
            return -2;
        }

        generators.push_back(std::unique_ptr<cppmm::Generator>(
            new cppmm::GeneratorRustSys(output_dir)));
    }

    for (const auto& g : generators) {
        g->generate(cppmm::files, cppmm::records, cppmm::enums, cppmm::vectors,
                    project_includes, project_libraries);
    }

    if (opt_warn_unbound) {
        size_t total = 0;
        for (const auto& ex_record : cppmm::ex_records) {
            total += ex_record.second.rejected_methods.size();
        }
        if (total != 0) {
            SPDLOG_WARN(
                "The following methods were not bound, ignored or manually "
                "overriden:");
            for (const auto& ex_record : cppmm::ex_records) {
                if (ex_record.second.rejected_methods.size()) {
                    SPDLOG_WARN("{}", ex_record.second.cpp_qname);
                    for (const auto& rejected_method :
                         ex_record.second.rejected_methods) {
                        SPDLOG_WARN("    {}", rejected_method);
                    }
                }
            }
        }
    }
 #endif

    return result;
}
