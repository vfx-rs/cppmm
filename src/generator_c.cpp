#include "generator_c.hpp"
#include "filesystem.hpp"
#include "pystring.h"

namespace ps = pystring;

namespace {

std::string bind_file_root(const std::string& filename) {
    const auto basename = ps::os::path::basename(filename);
    std::string root, ext;
    ps::os::path::splitext(root, ext, basename);
    return root;
}
} // namespace

namespace cppmm {

namespace fs = ghc::filesystem;

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

std::string get_vector_declaration(const cppmm::Vector& vec) {
    std::string format_str =
        R"#(
typedef struct {{ char _private[24]; }} {0} CPPMM_ALIGN(8);

void {0}_ctor({0}* vec);
void {0}_dtor(const {0}* vec);
int {0}_size(const {0}* vec);
{1}* {0}_data({0}* vec);
)#";

    if (vec.element_type.type.var.is<Record>() &&
        vec.element_type.type.var.cast<Record>()->kind ==
            RecordKind::OpaquePtr) {
        format_str +=
            R"#(
void {0}_get(const {0}* vec, int index, {1}** element);
void {0}_set({0}* vec, int index, {1}* element);
)#";

    } else {
        format_str +=
            R"#(
void {0}_get(const {0}* vec, int index, {1}* element);
void {0}_set({0}* vec, int index, {1}* element);
)#";
    }

    return fmt::format(format_str, vec.c_qname,
                       vec.element_type.type.get_c_qname());
} // namespace cppmm

std::string
get_vector_implementation(const cppmm::Vector& vec,
                          std::set<std::string>& casts_macro_invocations) {
    // casts for the vector
    casts_macro_invocations.insert(vec.create_casts());
    // casts for the element
    if (const cppmm::Record* record =
            vec.element_type.type.var.cast_or_null<cppmm::Record>()) {
        casts_macro_invocations.insert(record->create_casts());
    }

    std::string format_str =
        R"#(
void {0}_ctor({0}* vec) {{
    new (vec) std::vector<{2}>();
}}

void {0}_dtor(const {0}* vec) {{
    to_cpp(vec)->~vector();
}}

int {0}_size(const {0}* vec) {{
    return to_cpp(vec)->size();
}}

{1}* {0}_data({0}* vec) {{
    return to_c(to_cpp(vec)->data());
}}
)#";

    if (vec.element_type.type.var.is<Record>() &&
        vec.element_type.type.var.cast<Record>()->kind ==
            RecordKind::OpaquePtr) {
        format_str +=
            R"#(
void {0}_get(const {0}* vec, int index, {1}** element) {{
    const std::vector<{2}>& v = *to_cpp(vec);
    const {2}* p = &v[index];
    *element = to_c(p);
}}

void {0}_set({0}* vec, int index, {1}* element) {{
    (*to_cpp(vec))[index] = *to_cpp(element);
}}
)#";

    } else {
        format_str +=
            R"#(
void {0}_get(const {0}* vec, int index, {1}* element) {{
    const std::vector<{2}>& v = *to_cpp(vec);
    const {2}* p = &v[index];
    *element = *to_c(p);
}}

void {0}_set({0}* vec, int index, {1}* element) {{
    (*to_cpp(vec))[index] = *to_cpp(element);
}}
)#";
    }

    return fmt::format(
        format_str,
        vec.c_qname,                            //< 0: C vector name
        vec.element_type.type.get_c_qname(),    //< 1: C element name
        vec.element_type.type.get_cpp_qname()); //< 2: C++ element
}

void write_containers_header(const std::string& filename) {
    const std::string header = R"#(
#pragma once
#ifdef __cplusplus
extern "C" {
#else
#include <stdbool.h>
#endif

#if defined(_WIN32) || defined(__CYGWIN__)
#define CPPMM_ALIGN(x) __declspec(align(x))
#else
#define CPPMM_ALIGN(x) __attribute__((aligned(x)))
#endif


typedef struct { char _private[24]; } cppmm_string_vector CPPMM_ALIGN(8);

const char* cppmm_string_vector_get(const cppmm_string_vector* vec, int index);
int cppmm_string_vector_size(const cppmm_string_vector* vec);


#ifdef __cplusplus
}
#endif
    )#";

    auto out = fopen(filename.c_str(), "w");
    fprintf(out, "%s", header.c_str());
    fclose(out);
}

void write_containers_implementation(const std::string& filename) {
    const std::string src = R"#(
#include "cppmm_containers.h"
#include <string>
#include <vector>

namespace {
#include "casts.h"

CPPMM_DEFINE_POINTER_CASTS(std::vector<std::string>, cppmm_string_vector);


#undef CPPMM_DEFINE_POINTER_CASTS
}

extern "C" {

const char* cppmm_string_vector_get(const cppmm_string_vector* vec, int index) {
    return (*to_cpp(vec))[index].c_str();
}

int cppmm_string_vector_size(const cppmm_string_vector* vec) {
    return to_cpp(vec)->size();
}

}
    )#";

    auto out = fopen(filename.c_str(), "w");
    fprintf(out, "%s", src.c_str());
    fclose(out);
}

void write_cmakelists(const std::string& filename,
                      const std::string& project_name,
                      const std::vector<std::string> source_files,
                      const std::vector<std::string>& includes,
                      const std::vector<std::string>& libraries) {
    const std::string src =
        fmt::format(R"#(cmake_minimum_required(VERSION 3.5)
project({0})

add_library({0} STATIC
  {1}
)

target_compile_options({0} PRIVATE
  -fno-strict-aliasing
)

target_include_directories({0} PUBLIC
  {2}
)

target_link_libraries({0} PUBLIC
  {3}
)
)#",
                    project_name, ps::join("\n  ", source_files),
                    ps::join("\n  ", includes), ps::join("\n  ", libraries));
    auto out = fopen(filename.c_str(), "w");
    fprintf(out, "%s", src.c_str());
    fclose(out);
}

// FIXME: the logic of what things end up in what maps is a bit gnarly here.
// We should really move everythign that's in ExportedFile into File during
// the second phase, and clarify what's expected to be in what maps exactly.
void GeneratorC::generate(const ExportedFileMap& ex_files, const FileMap& files,
                          const RecordMap& records, const EnumMap& enums,
                          const VectorMap& vectors,
                          const std::vector<std::string>& project_includes,
                          const std::vector<std::string>& project_libraries) {
    std::vector<std::string> source_files;
    fs::path output_dir_path = fs::path(_output_dir);
    std::string project_name = output_dir_path.stem();

    for (const auto& bind_file : ex_files) {
        std::set<std::string> casts_macro_invocations;
        std::string declarations;
        std::string definitions;

        std::set<std::string> header_includes;
        header_includes.insert("cppmm_containers.h");

        if (bind_file.first == "") {
            // FIXME: how is this getting in there?
            continue;
        }

        for (const auto& rec_pair : bind_file.second.records) {
            const auto it_record = records.find(rec_pair.first);
            if (it_record == records.end()) {
                fmt::print("ERROR: record {} not found in records map\n",
                           rec_pair.first);
                continue;
            }

            const auto& record = it_record->second;
            declarations += record.get_declaration(casts_macro_invocations);

            const auto it_vec = vectors.find(record.c_qname);
            if (it_vec != vectors.end()) {
                if (it_vec->second.element_type.type.name == "basic_string") {
                } else {
                    declarations += get_vector_declaration(it_vec->second);
                    definitions += get_vector_implementation(
                        it_vec->second, casts_macro_invocations);
                }
            }

            definitions += record.get_definition();
        }

        for (const auto& enm_pair : bind_file.second.enums) {
            const auto it_enum = enums.find(enm_pair.first);
            if (it_enum == enums.end()) {
                fmt::print("ERROR: enum {} not found in enums map\n",
                           enm_pair.first);
                continue;
            }
            const auto& enm = it_enum->second;
            declarations += enm.get_declaration();
        }

        const auto it_file = files.find(bind_file.first);
        if (it_file != files.end()) {
            for (const auto& it_function : it_file->second.functions) {
                const auto& function = it_function.second;

                std::string declaration = function.get_declaration(
                    header_includes, casts_macro_invocations);

                std::string definition = function.get_definition(declaration);

                declarations = fmt::format("{}\n{}\n{};\n", declarations,
                                           function.comment, declaration);

                definitions =
                    fmt::format("{}\n{}\n\n\n", definitions, definition);
            }
        }

        for (const auto& record_pair : bind_file.second.records) {
            const auto it_record = records.find(record_pair.second->c_qname);
            if (it_record == records.end()) {
                fmt::print("ERROR: record {} not found in records map\n",
                           record_pair.second->c_qname);
                continue;
            }
            const auto& record = it_record->second;

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

        write_header(output_dir_path / header, declarations,
                     header_include_stmts);

        std::string implementation_path = output_dir_path / implementation;
        write_implementation(implementation_path, root,
                             bind_file.second.includes, casts, definitions);
        source_files.push_back(implementation);
    }

    write_casts_header(output_dir_path / "casts.h");
    write_containers_header(output_dir_path / "cppmm_containers.h");
    std::string containers_implementation =
        output_dir_path / "cppmm_containers.cpp";
    write_containers_implementation(containers_implementation);
    source_files.push_back("cppmm_containers.cpp");

    write_cmakelists(output_dir_path / "CMakeLists.txt", project_name,
                     source_files, project_includes, project_libraries);
}

} // namespace cppmm
