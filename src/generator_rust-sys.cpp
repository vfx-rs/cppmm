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

[build-dependencies]
cmake = "0.1"

[dependencies]
)#",
        project_name);

    auto out = fopen(filename.c_str(), "w");
    fprintf(out, "%s", src.c_str());
    fclose(out);
}

void write_source_file(const std::string& filename,
                       const std::string& declarations,
                       const std::set<std::string>& use_stmts) {
    std::string src;
    for (const auto& use : use_stmts) {
        src += use;
    }

    src += declarations;

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
        const auto rmod = ps::replace(mod, "-", "_");
        src += "pub mod " + rmod + ";\n";
        src += "pub use " + rmod + "::*;\n";
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
    } else if (c_qname == "void") {
        return "std::os::raw::c_void";
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

std::string get_enum_declaration(const Enum& enm) {
    std::string declarations;
    declarations += fmt::format("#[repr(i32)]\npub enum {} {{\n", enm.c_qname);

    std::set<uint64_t> emitted_variants;
    for (const auto& ecd : enm.enumerators) {
        // std::string qname = enm.c_qname + "_" + ecd.first;
        std::string qname = ecd.first;
        if (emitted_variants.find(ecd.second) == emitted_variants.end()) {
            declarations += fmt::format("    {} = {},\n", qname, ecd.second);
            emitted_variants.insert(ecd.second);
        } else {
            fmt::print("WARNING: ignoring duplicate enum variant {} = {}\n",
                       qname, ecd.second);
            declarations += fmt::format("//  {} = {},\n", qname, ecd.second);
        }
    }

    declarations += "}\n\n";
    return declarations;
}

std::string get_rust_qtype(const QualifiedType& qtype) {
    std::string result;

    if (qtype.type.name == "basic_string") {
        if (qtype.is_const) {
            result = "*const std::os::raw::c_char";
        } else {
            result = "*mut std::os::raw::c_char";
        }

    } else if (qtype.type.name == "string_view") {
        result = "*const std::os::raw::c_char";
    } else if (qtype.type.name == "const char *") {
        result = "*const std::os::raw::c_char";
    } else if (qtype.type.name == "char *") {
        result = "*mut std::os::raw::c_char";
    } else if (qtype.type.name == "void *") {
        result = "*mut std::os::raw::c_void";
    } else if (qtype.type.var.is<Enum>()) {
        result = "i32";
    } else if (const Vector* vec = qtype.type.var.cast_or_null<Vector>()) {
        if (qtype.is_ptr || qtype.is_ref || qtype.is_uptr) {
            if (qtype.is_const) {
                result = "*const ";
            } else {
                result = "*mut ";
            }
        }
        result += vec->c_qname;
    } else if (const Record* record = qtype.type.var.cast_or_null<Record>()) {
        if (qtype.is_ptr || qtype.is_ref || qtype.is_uptr) {
            if (qtype.is_const) {
                result = "*const ";
            } else {
                result = "*mut ";
            }
        }
        result += record->c_qname;
    } else if (qtype.type.var.is<Builtin>()) {
        if (qtype.is_ptr || qtype.is_ref || qtype.is_uptr) {
            if (qtype.is_const) {
                result = "*const ";
            } else {
                result = "*mut ";
            }
        }
        result += rust_type_name(qtype.type.name);
    } else {
        return "UNHANDLED";
    }

    return result;
}

std::string sanitize_param_name(const std::string name) {
    // FIXME: fill out this list
    if (name == "type" || name == "self") {
        return std::string("_") + name;
    }

    return name;
}

std::string get_param_declaration(const Param& param) {
    return fmt::format("{}: {}", sanitize_param_name(param.name),
                       get_rust_qtype(param.qtype));
}

std::string get_function_declaration(const Function& function,
                                     std::set<std::string>& use_stmts) {
    std::vector<std::string> param_decls;
    for (const auto& param : function.params) {
        std::string pdecl = get_param_declaration(param);
        param_decls.push_back(pdecl);
    }

    std::string ret;
    if (function.return_type.type.name == "basic_string" &&
        !function.return_type.is_ref && !function.return_type.is_ptr) {
        ret = "i32";
        param_decls.push_back("_result_buffer_ptr: *mut std::os::raw::c_char");
        param_decls.push_back("_result_buffer_len: i32");
    } else {
        ret = get_rust_qtype(function.return_type);
    }

    return fmt::format("pub fn {}({}) -> {}", function.c_qname,
                       ps::join(", ", param_decls), ret);
}

std::string get_opaqueptr_constructor_declaration(
    const Record& record, const std::string& c_method_name,
    const std::vector<std::string>& param_decls) {
    return fmt::format("pub fn {}({}) -> *mut {}", c_method_name,
                       ps::join(", ", param_decls), record.c_qname);
}

std::string get_method_declaration(const Record& record, const Method& method,
                                   std::set<std::string>& use_stmts) {
    std::vector<std::string> param_decls;
    std::string declaration;

    for (const auto& param : method.params) {
        std::string pdecl = get_param_declaration(param);
        param_decls.push_back(pdecl);
    }

    if (method.is_constructor && record.kind == RecordKind::OpaquePtr) {
        return get_opaqueptr_constructor_declaration(record, method.c_qname,
                                                     param_decls);
    } else {
        std::string ret;
        if (method.return_type.type.name == "basic_string" &&
            !method.return_type.is_ref && !method.return_type.is_ptr) {
            ret = "i32";
            param_decls.push_back(
                "_result_buffer_ptr: *mut std::os::raw::c_char");
            param_decls.push_back("_result_buffer_len: i32");
        } else {
            ret = get_rust_qtype(method.return_type);
            // if (const Record* record =
            //         method.return_type.type.var.cast_or_null<Record>()) {
            //     use_stmts.insert(fmt::format("use crate::{}::{};\n",
            //                                  bind_file_root(record->filename),
            //                                  record->c_qname));
            // }
        }

        if (method.is_static) {
            declaration = fmt::format("pub fn {}({})", method.c_qname,
                                      ps::join(", ", param_decls));
        } else {
            std::string constqual;
            if (method.is_const) {
                constqual = "const";
            } else {
                constqual = "mut";
            }
            declaration = fmt::format("pub fn {}(_self: *{} {}", method.c_qname,
                                      constqual, record.c_qname);
            if (param_decls.size()) {
                declaration = fmt::format("{}, {})", declaration,
                                          ps::join(", ", param_decls));
            } else {
                declaration = fmt::format("{})", declaration);
            }
        }

        if (ret != "void") {
            declaration += fmt::format(" -> {}", ret);
        }

        return declaration;
    }
}

void write_containers_implementation(const std::string& filename) {
    const std::string src =
        R"#(#[repr(C, align(8))]
pub struct cppmm_string_vector { unused: [u8; 24] }

extern "C" {

pub fn cppmm_string_vector_get(vec: *const cppmm_string_vector, index: i32) -> *const std::os::raw::c_char;
pub fn cppmm_string_vector_size(vec: *const cppmm_string_vector) -> i32;

}
)#";

    auto out = fopen(filename.c_str(), "w");
    fprintf(out, "%s", src.c_str());
    fclose(out);
}

void write_build_rs(const std::string& filename,
                    const std::vector<std::string>& libs) {

    std::string link_lines;
    for (const auto& l : libs) {
        std::string head, tail;
        ps::os::path::split(head, tail, l);
        std::string root, ext;
        ps::os::path::splitext(root, ext, tail);
        link_lines += fmt::format(
            "    println!(\"cargo:rustc-link-search=native={}\");\n", head);
        link_lines += fmt::format(
            "    println!(\"cargo:rustc-link-lib=dylib={}\");\n",
            root.substr(3, std::string::npos));
    }

    std::string src = fmt::format(
        R"#(
fn main() {{
    let dst = cmake::Config::new("clib").build();
    println!("cargo:rustc-link-search=native={{}}", dst.display());
    println!("cargo:rustc-link-lib=static=clib");

{}

    #[cfg(target_os = "linux")]
    println!("cargo:rustc-link-lib=dylib=stdc++");
    #[cfg(target_os = "macos")]
    println!("cargo:rustc-link-lib=dylib=c++");
}}
)#",
        link_lines);

    auto out = fopen(filename.c_str(), "w");
    fprintf(out, "%s", src.c_str());
    fclose(out);
}

} // namespace

GeneratorRustSys::GeneratorRustSys(std::string output_dir)
    : Generator(output_dir),
      _c_generator((fs::path(output_dir) / "clib").string()) {}

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

    // generate the inbuilt C library
    _c_generator.generate(ex_files, files, records, enums, vectors,
                          project_includes, project_libraries);

    std::vector<std::string> mods;
    mods.push_back("cppmm_containers");

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

        for (const auto& enm_pair : bind_file.second.enums) {
            const auto it_enum = enums.find(enm_pair.first);
            if (it_enum == enums.end()) {
                fmt::print("ERROR: enum {} not found in enums map\n",
                           enm_pair.first);
                continue;
            }
            const auto& enm = it_enum->second;
            declarations += get_enum_declaration(enm);
        }

        std::set<std::string> use_stmts;
        use_stmts.insert("use crate::*;\n");

        const auto it_file = files.find(bind_file.first);
        declarations += "extern \"C\" {\n";
        if (it_file != files.end()) {
            for (const auto& it_function : it_file->second.functions) {
                const auto& function = it_function.second;

                std::string declaration =
                    get_function_declaration(function, use_stmts);

                declarations =
                    fmt::format("{}\n{};\n", declarations, declaration);
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

                std::string declaration =
                    get_method_declaration(record, method, use_stmts);

                declarations =
                    fmt::format("{}\n{};\n", declarations, declaration);
            }
        }

        declarations += "}\n";

        const std::string root =
            ps::replace(bind_file_root(bind_file.first), "-", "_");
        const auto src_file = fmt::format("{}.rs", root);
        const auto src_path = output_dir_path / "src" / src_file;
        write_source_file(src_path.string(), declarations, use_stmts);
        mods.push_back(root);
    }

    write_cargo_toml(output_dir_path / "Cargo.toml", project_name);
    write_lib_rs(output_dir_path / "src" / "lib.rs", mods);
    write_containers_implementation(output_dir_path / "src" /
                                    "cppmm_containers.rs");

    write_build_rs(output_dir_path / "build.rs", project_libraries);
}
} // namespace cppmm
