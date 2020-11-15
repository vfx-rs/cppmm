#include "generator_rust-sys.hpp"
#include "filesystem.hpp"
#include "pystring.h"
#include "record.hpp"

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

namespace {
void write_cargo_toml(const std::string& filename,
                      const std::string& project_name) {
    std::string src = fmt::format(
        R"#([package]
name = "{}"
version = "0.1.0"
authors = ["Anders Langlands <anderslanglands@gmail.com>"]
edition = "2018"

[dependencies]
)#",
        project_name);

    auto out = fopen(filename.c_str(), "w");
    fprintf(out, "%s", src.c_str());
    fclose(out);
}

void write_source_file(const std::string& filename,
                       const std::string& declarations) {
    std::string src = declarations;

    auto out = fopen(filename.c_str(), "w");
    fprintf(out, "%s", src.c_str());
    fclose(out);
}

void write_lib_rs(const std::string& filename,
                  const std::vector<std::string>& mods) {
    std::string src =
R"#(#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]

)#";
    for (const auto& mod : mods) {
        src += "pub mod " + mod + ";\n";
        src += "pub use " + mod + "::*;\n";
    }
    src += "\n";

    auto out = fopen(filename.c_str(), "w");
    fprintf(out, "%s", src.c_str());
    fclose(out);
}

std::string rust_type_name(const std::string& c_qname) {
    if (c_qname == "char") {
        return "i8";
    } else if (c_qname == "unsigned char") {
        return "u8";
    } else if (c_qname == "short") {
        return "i16";
    } else if (c_qname == "unsigned short") {
        return "u16";
    } else if (c_qname == "int") {
        return "i32";
    } else if (c_qname == "unsigned int") {
        return "u32";
    } else if (c_qname == "long") {
        return "i64";
    } else if (c_qname == "unsigned long") {
        return "u64";
    } else if (c_qname == "size_t") {
        return "usize";
    } else if (c_qname == "float") {
        return "f32";
    } else if (c_qname == "double") {
        return "f64";
    } else {
        return c_qname;
    }
}

std::string get_record_declaration(const Record& record) {
    if (record.kind == RecordKind::OpaquePtr) {
        return fmt::format(
            R"#(
#[repr(C)]
pub struct {0}_t {{
    _unused: [u8; 0],
}}
pub type {0} = *mut {0}_t;
)#",
            record.c_qname);
    } else if (record.kind == cppmm::RecordKind::OpaqueBytes) {
        return fmt::format(
            R"#(
#[repr(C, align({1}))]
pub struct {0} {{
    _unused: [u8; {2}],
}}
)#",
            record.c_qname, record.alignment, record.size);
    } else {
        // ValueType
        std::string result = fmt::format(
            R"#(
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct {0} {{
)#",
            record.c_qname);

        for (const auto& field : record.fields) {
            result +=
                fmt::format("    {}: {},\n", field.name,
                            rust_type_name(field.qtype.type.get_c_qname()));
        }
        result += "}\n";

        return result;
    }
}

std::string get_vector_declaration(const Vector& vec) {
    std::string format_str =
        R"#(#[repr(C, align(8))]
pub struct {0} {{ unused: [u8; 24] }}

extern "C" {{
    pub fn {0}_ctor(vec: *mut {0});
    pub fn {0}_dtor(vec: *const {0});
    pub fn {0}_size(vec: *const {0}) -> i32;
    pub fn {0}_data(vec: *const {0}) -> *mut {1};
)#";

    if (vec.element_type.type.var.is<Record>() &&
        vec.element_type.type.var.cast<Record>()->kind ==
            RecordKind::OpaquePtr) {
        format_str +=
            R"#(    pub fn {0}_get(vec: *const {0}, index: i32, element: *mut *mut {1});
    pub fn {0}_set(vec: *mut {0}, index: i32, element: *const {1});
}}
)#";
    } else {
        format_str +=
            R"#(    pub fn {0}_get(vec: *const {0}, index: i32, element: *mut {1});
    pub fn {0}_set(vec: *mut {0}, index: i32, element: *const {1});
}}
)#";
    }

    return fmt::format(format_str, vec.c_qname,
                       rust_type_name(vec.element_type.type.get_c_qname()));
}
} // namespace

void GeneratorRustSys::generate(
    const ExportedFileMap& ex_files, const FileMap& files,
    const RecordMap& records, const EnumMap& enums, const VectorMap& vectors,
    const std::vector<std::string>& project_includes,
    const std::vector<std::string>& project_libraries) {
    fs::path output_dir_path = fs::path(_output_dir);
    fs::path output_src_path = output_dir_path / "src";
    std::string project_name = output_dir_path.stem();

    if (!fs::exists(output_src_path)) {
        if (!fs::create_directories(output_src_path)) {
            fmt::print("ERROR: could not create output src directory '{}'\n",
                       output_src_path.string());
            abort();
        }
    }

    std::vector<std::string> mods;

    for (const auto& bind_file : ex_files) {
        std::string declarations;

        if (bind_file.first == "") {
            // FIXME: how is this getting in there?
            continue;
        }

        // First, record declarations
        for (const auto& rec_pair : bind_file.second.records) {
            const auto it_record = records.find(rec_pair.first);
            if (it_record == records.end()) {
                fmt::print("ERROR: record {} not found in records map\n",
                           rec_pair.first);
                continue;
            }

            const auto& record = it_record->second;
            declarations += get_record_declaration(record);

            const auto it_vec = vectors.find(record.c_qname);
            if (it_vec != vectors.end()) {
                if (it_vec->second.element_type.type.name == "basic_string") {
                } else {
                    declarations += get_vector_declaration(it_vec->second);
                }
            }
        }

        const std::string root = bind_file_root(bind_file.first);
        const auto src_file = fmt::format("{}.rs", root);
        const auto src_path = output_dir_path / "src" / src_file;
        write_source_file(src_path.string(), declarations);
        mods.push_back(root);
    }

    write_cargo_toml(output_dir_path / "Cargo.toml", project_name);
    write_lib_rs(output_dir_path / "src" / "lib.rs", mods);
}
} // namespace cppmm
