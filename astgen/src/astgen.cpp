#include <algorithm>
#include <cstring>
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

#include "process_binding.hpp"

#include "base64.hpp"
#include "resources.hpp"

#define SPDLOG_ACTIVE_LEVEL TRACE

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include "ast.hpp"

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

std::vector<std::string> parse_project_includes(int argc, const char** argv,
                                                const std::string& cwd) {
    std::vector<std::string> result;
    for (int i = 0; i < argc; ++i) {
        std::string a(argv[i]);
        if (a.find("-I") == 0) {
            result.push_back(
                ps::os::path::abspath(a.substr(2, std::string::npos), cwd));
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

extern bool WARN_UNMATCHED;
static cl::opt<bool> opt_warn_unbound("u", cl::desc("Warn on unbound methods"));

static cl::opt<int> opt_verbosity(
    "v", cl::desc("Verbosity. 0=errors, 1=warnings, 2=info, 3=debug, 4=trace"),
    cl::init(1));

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
    const char* cwd = fs::current_path().c_str();

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

    // if the user didn't add a double dash to the arguments list, we need
    // to insert one here so we can pass arguments to clang
    if (!has_ddash) {
        argv[i++] = "--";
        argc++;
    }

    // add our virtual header path
    argv[i++] = "-isystem";
    argv[i++] = "/CPPMM_VIRTUAL_INCLUDES";

    // grab any user-specified include directories from the command line
    cppmm::PROJECT_INCLUDES = parse_project_includes(argc, argv, cwd);

    ExitOnError eoe;
    CommonOptionsParser OptionsParser = eoe(CommonOptionsParser::create(argc, argv, CppmmCategory));

    // Set up logging
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
        for (const auto& entry :
             fs::recursive_directory_iterator(src_path[0])) {
            if (entry.path().extension() == ".cpp") {
                dir_paths.push_back(
                    // ps::os::path::abspath(entry.path().string(), cwd)
                    entry.path().string());
                SPDLOG_DEBUG("Found binding file {}", entry.path().string());
            }
        }
    } else {
        // otherwise we'll assume we've been given a list of source files to
        // work with
        for (const auto& s : src_path) {
            dir_paths.push_back(ps::os::path::abspath(s, cwd));
        }
    }

    ClangTool Tool(OptionsParser.getCompilations(),
                   ArrayRef<std::string>(dir_paths));

    // Insert macros we'll use in the bindings into a virtual header
    Tool.mapVirtualFile("/CPPMM_VIRTUAL_INCLUDES/cppmm_bind.hpp", R"#(
#define CPPMM_IGNORE __attribute__((annotate("cppmm|ignore")))
#define CPPMM_RENAME(x) __attribute__((annotate("cppmm|rename|" #x)))
#define CPPMM_OPAQUEPTR __attribute__((annotate("cppmm|opaqueptr")))
#define CPPMM_OPAQUEBYTES __attribute__((annotate("cppmm|opaquebytes")))
#define CPPMM_OPAQUETYPE __attribute__((annotate("cppmm|opaquetype")))
#define CPPMM_VALUETYPE __attribute__((annotate("cppmm|valuetype")))
#define CPPMM_COLLAPSE __attribute__((annotate("cppmm|collapse")))
#define CPPMM_IGNORE_UNBOUND __attribute__((annotate("cppmm|ignore_unbound")))
#define CPPMM_TRIVIALLY_COPYABLE __attribute__((annotate("cppmm|trivially_copyable")))
#define CPPMM_TRIVIALLY_MOVABLE __attribute__((annotate("cppmm|trivially_movable")))
#define CPPMM_PROPERTIES(x) __attribute__((annotate("cppmm|properties|" #x)))
#define CPPMM_MANUAL __attribute__((annotate("cppmm|manual")))
#define CPPMM_IMPL __attribute__((annotate("cppmm|impl")))
#define CPPMM_COPY_CTOR __attribute__((annotate("cppmm|copy_constructor")))
#define CPPMM_MOVE_CTOR __attribute__((annotate("cppmm|move_constructor")))

#define CPPMM_THROWS(EX, VAR) __attribute__((annotate("cppmm|throws|" #EX "|" #VAR)))
#define CPPMM_NOEXCEPT __attribute__((annotate("cppmm|noexcept")))
#define CPPMM_FORCE_NAME(x) __attribute__((annotate("cppmm|force_name|" #x)))

#define CPPMM_ENUM_PREFIX(x) __attribute__((annotate("cppmm|enum_prefix|" #x)))
#define CPPMM_ENUM_SUFFIX(x) __attribute__((annotate("cppmm|enum_suffix|" #x)))
#define CPPMM_RUSTIFY_ENUM __attribute__((annotate("cppmm|rustify_enum")))
#define CPPMM_DERIVE(x) __attribute__((annotate("cppmm|derive|" #x)))

#define CPPMM_COPY(NS, CLASS) CLASS(const NS::CLASS& rhs) CPPMM_RENAME(copy); NS::CLASS& operator=(const NS::CLASS& rhs);
#define CPPMM_MOVE(NS, CLASS) CLASS(NS::CLASS&& rhs) CPPMM_IGNORE; NS::CLASS& operator=(NS::CLASS&& rhs) CPPMM_IGNORE;
#define CPPMM_ROFIVE(NS, CLASS) CPPMM_COPY(NS, CLASS) CPPMM_MOVE(NS, CLASS) ~CLASS();
)#");

    // Expose the clang headers (e.g. stddef.h) as virtual headers. These are
    // compiled into the binary as base64 using the source files generated by
    // the bake_resources.py script.
    std::vector<std::string> decoded_headers;
    decoded_headers.reserve(num_files());
    std::vector<std::string> virtual_filenames;
    virtual_filenames.reserve(num_files());

    for (int i = 0; i < num_files(); ++i) {
        virtual_filenames.push_back(std::string("/CPPMM_VIRTUAL_INCLUDES/") +
                                    cppmm_resource_filename(i));
        decoded_headers.push_back(base64::decode(cppmm_resource_array(i)));
    }

    for (int i = 0; i < num_files(); ++i) {
        Tool.mapVirtualFile(virtual_filenames[i], decoded_headers[i]);
    }

    WARN_UNMATCHED = opt_warn_unbound;

    std::string output_dir = cwd;
    if (opt_output_directory != "") {
        output_dir = opt_output_directory;
    }

    for (const auto& i : opt_includes) {
        cppmm::PROJECT_INCLUDES.push_back(i);
    }

    std::vector<std::string> project_libraries;
    for (const auto& l : opt_libraries) {
        project_libraries.push_back(l);
    }

    // get direct includes from the binding files to re-insert into the
    // generated bindings
    for (const auto& src : dir_paths) {
        const auto src_path = ps::os::path::join(cwd, src);
        SPDLOG_DEBUG("joining {} and {} to get {}", cwd, src, src_path);
        cppmm::SOURCE_INCLUDES[src_path] = parse_file_includes(src_path);
    }

    // Run our tool to generate the AST
    auto process_binding_action =
        newFrontendActionFactory<cppmm::ProcessBindingAction>();
    int result = Tool.run(process_binding_action.get());

    // Make sure the location we want to write to exists
    if (!fs::exists(output_dir) && !fs::create_directories(output_dir)) {
        SPDLOG_ERROR("Could not create output directory '{}'", output_dir);
        return -2;
    }

    // Write out the binding AST per translation unit
    cppmm::write_tus(output_dir, src_path[0]);

    return result;
}
