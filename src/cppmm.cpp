#include <algorithm>
#include <fstream>
#include <iostream>
#include <optional>
#include <unistd.h>
#include <unordered_map>

#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "llvm/Support/CommandLine.h"

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
#include "match_decls.hpp"
#include "decls.hpp"

using namespace clang::tooling;
using namespace llvm;
using namespace clang;
using namespace clang::ast_matchers;

namespace ps = pystring;

namespace cppmm {

// vector wrapper
struct Vec {
    std::string c_name;
    Type element_type;
};

} // namespace cppmm


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
    auto cppmm_action = newFrontendActionFactory<cppmm::MatchDeclsAction>();
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
            const auto& record = cppmm::records[rec_pair.first];
            declarations += record.get_declaration(casts_macro_invocations);
            definitions += record.get_definition();
        }

        for (const auto& enm_pair : bind_file.second.enums) {
            const auto& enm = cppmm::enums[enm_pair.first];
            declarations += enm.get_declaration();
        }

        for (const auto& it_function : cppmm::files[bind_file.first].functions) {
            const auto& function = it_function.second;

            std::string declaration = function.get_declaration(
                header_includes, casts_macro_invocations);

            std::string definition = function.get_definition(declaration);

            declarations = fmt::format("{}\n{}\n{};\n", declarations,
                                       function.comment, declaration);

            definitions = fmt::format("{}\n{}\n\n\n", definitions, definition);
        }

        for (const auto& record_pair : bind_file.second.records) {
            const cppmm::Record& record = cppmm::records[record_pair.second->c_qname];

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
