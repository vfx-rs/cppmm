#include "case.hpp"
#include "cppmm_ast.hpp"
#include "filesystem.hpp"
#include "pystring.h"

#include <fmt/os.h>

#include <iostream>

namespace fs = ghc::filesystem;

#define SPDLOG_ACTIVE_LEVEL TRACE

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#define panic(...)                                                             \
    {                                                                          \
        SPDLOG_CRITICAL(__VA_ARGS__);                                          \
        abort();                                                               \
    }

#define expect(CONDITION, ...)                                                 \
    if (!(CONDITION)) {                                                        \
        SPDLOG_CRITICAL(__VA_ARGS__);                                          \
        abort();                                                               \
    }

namespace cppmm {
class Root;
namespace rust_sys {

std::string convert_builtin_type(const NodeBuiltinType* t) {
    if (t->type_name == "int") {
        return "c_int";
    } else if (t->type_name == "char" || t->type_name == "signed char") {
        return "c_char";
    } else if (t->type_name == "short") {
        return "c_short";
    } else if (t->type_name == "long") {
        return "c_long";
    } else if (t->type_name == "long long") {
        return "c_longlong";
    } else if (t->type_name == "unsigned char") {
        return "c_uchar";
    } else if (t->type_name == "unsigned int") {
        return "c_uint";
    } else if (t->type_name == "unsigned short") {
        return "c_ushort";
    } else if (t->type_name == "unsigned long") {
        return "c_ulong";
    } else if (t->type_name == "unsigned long long") {
        return "c_ulonglong";
    } else if (t->type_name == "size_t") {
        return "usize";
    } else if (t->type_name == "bool" || t->type_name == "_Bool") {
        return "bool";
    } else if (t->type_name == "float") {
        return "c_float";
    } else if (t->type_name == "double") {
        return "c_double";
    } else if (t->type_name == "void") {
        return "c_void";
    } else if (t->type_name == "uint64_t") {
        return "u64";
    } else if (t->type_name == "int64_t") {
        return "i64";
    } else if (t->type_name == "ptrdiff_t") {
        return "i64";
    }
    panic("Unhandled builtin {}", t->type_name);
    return t->type_name;
}

std::string sanitize_keyword(std::string s) {
    if (s == "as" || s == "crate" || s == "fn" || s == "impl" || s == "in" ||
        s == "let" || s == "loop" || s == "match" || s == "mod" || s == "mut" ||
        s == "pub" || s == "ref" || s == "self" || s == "Self" ||
        s == "super" || s == "trait" || s == "type" || s == "unsafe" ||
        s == "use" || s == "where" || s == "async" || s == "await" ||
        s == "dyn" || s == "abstract" || s == "become" || s == "box" ||
        s == "final" || s == "macro" || s == "priv" || s == "typeof" ||
        s == "unsized" || s == "yield" || s == "override") {
        return s + "_";
    }
    return s;
}

std::string convert_type(const NodeType* t);

std::string convert_record_type(const NodeRecordType* t) {
    return t->type_name;
}

std::string convert_array_type(const NodeArrayType* t) {
    // const auto el = convert_type(t->element_type);
    // return fmt::format("*const {}", el);

    // we need to decay this to a single pointer, so we need to traverse the
    // graph until we find something that's not an array in order to handle
    // multidimensional arrays (which are laid out as a consecutive chunk)
    const NodeType* p = static_cast<const NodeType*>(t);
    while (p->kind == NodeKind::ArrayType) {
        const NodeArrayType* a = static_cast<const NodeArrayType*>(p);
        p = a->element_type.get();
    }

    std::string cnst = "mut";
    if (p->const_) {
        cnst = "const";
    }

    const auto pointee = convert_type(p);
    return fmt::format("*{} {}", cnst, pointee);
}

std::string convert_type(const NodeType* t);

std::string convert_function_pointer_type(const NodeFunctionProtoType* t) {
    auto return_type = convert_type(t->return_type.get());
    std::vector<std::string> params;
    for (const auto& p : t->params) {
        params.push_back(convert_type(p.get()));
    }
    return fmt::format("Option<extern fn({}) -> {}>", pystring::join(", ", params),
                       return_type);
}

std::string convert_type(const NodeType* t) {
    if (t->kind == NodeKind::BuiltinType) {
        return convert_builtin_type(static_cast<const NodeBuiltinType*>(t));
    } else if (t->kind == NodeKind::RecordType) {

        return convert_record_type(static_cast<const NodeRecordType*>(t));
    } else if (t->kind == NodeKind::ArrayType) {
        return convert_array_type(static_cast<const NodeArrayType*>(t));
    } else if (t->kind == NodeKind::PointerType) {
        std::string cnst = "mut";
        const NodePointerType* p = static_cast<const NodePointerType*>(t);
        if (p->pointee_type->const_) {
            cnst = "const";
        }
        return fmt::format("*{} {}", cnst, convert_type(p->pointee_type.get()));
    } else if (t->kind == NodeKind::FunctionProtoType) {
        return convert_function_pointer_type(
            static_cast<const NodeFunctionProtoType*>(t));
    } else {
        panic("Unhandled type {}", t->type_name);
    }
} // namespace rust_sys

std::vector<std::string> convert_params(const std::vector<Param>& params) {
    std::vector<std::string> result;
    for (const auto& p : params) {
        auto name = sanitize_keyword(to_snake_case(p.name));
        result.push_back(
            fmt::format("{}: {}", name, convert_type(p.type.get())));
    }
    return result;
}

std::vector<std::string> convert_fields(const std::vector<Field>& fields) {
    std::vector<std::string> result;
    for (const auto& f : fields) {
        auto name = sanitize_keyword(to_snake_case(f.name));
        result.push_back(
            fmt::format("pub {}: {}", name, convert_type(f.type.get())));
    }
    return result;
}

void write_function(fmt::ostream& out, const NodeFunction* node_function) {
    // don't want to bind the internal conversion functions
    if (node_function->private_) {
        return;
    }

    std::vector<std::string> params = convert_params(node_function->params);

    // disable this until we can sanitize any formatting that will break rustdoc
    // if (!node_function->comment.empty()) {
    //     auto comment =
    //         pystring::replace(node_function->comment, "\n", "\n/// ");
    //     out.print("/// {}\n", comment);
    // }
    out.print("pub fn {}({})", node_function->name,
              pystring::join(", ", params));

    if (node_function->short_name == "sizeof" ||
        node_function->short_name == "alignof") {
        out.print(" -> usize;\n\n");
    } else {
        std::string ret = convert_type(node_function->return_type.get());
        if (ret != "void") {
            out.print(" -> Exception;\n\n");
        } else {
            out.print(";\n\n");
        }
    }
}

std::string get_derive_attr(const NodeRecord* node_record) {
    for (const auto& a : node_record->attrs) {
        if (pystring::find(a, "cppmm|derive|") == 0) {
            return a.substr(14, a.size() - 15);
        }
    }
    return "";
}

void write_record(fmt::ostream& out, const NodeRecord* node_record, fmt::ostream& out_cppmmabi_in) {
    BindType bt = bind_type(*node_record);

    std::string derive = get_derive_attr(node_record);
    if (derive.empty()) {
        derive = "Clone";
    }

    if (bt == BindType::OpaquePtr) {
        out.print("#[repr(C)]\n");
        out.print("pub struct {} {{\n", node_record->name);
        out.print("    _unused: [u8; 0],\n");
        out.print("}}");

    } else if (bt == BindType::OpaqueBytes) {
        out_cppmmabi_in.print("#[repr(C, align(%ALIGN{}%))]\n", node_record->cpp_name);
        out_cppmmabi_in.print("#[derive({})]\n", derive);
        out_cppmmabi_in.print("pub struct {} {{\n", node_record->name);
        out_cppmmabi_in.print("    _inner: [u8; %SIZE{}%]\n", node_record->cpp_name);
        out_cppmmabi_in.print("}}\n");

        out_cppmmabi_in.print(R"(
impl Default for {} {{
    fn default() -> Self {{
        Self {{ _inner: [0u8; %SIZE{}%] }}
    }}
}}
)",
                  node_record->name, node_record->cpp_name);

        out.print(R"(
impl {0} {{
    pub fn layout() -> std::alloc::Layout {{
        unsafe {{
            std::alloc::Layout::from_size_align(
                {1}_sizeof(),
                {1}_alignof(),
            ).unwrap()
        }}
    }}
}}
)",
                  node_record->name, pystring::slice(node_record->name, 0, -2));

    } else { // BindType::ValueType
        out.print("#[repr(C, align({}))]\n", node_record->align / 8);
        out.print("#[derive({})]\n", derive);
        out.print("pub struct {} {{\n", node_record->name);
        std::vector<std::string> fields = convert_fields(node_record->fields);
        out.print("    {},\n", pystring::join(",\n    ", fields));
        out.print("}}\n");
    }
}

bool has_rustify_enum_attr(const NodeEnum* node_enum) {
    return std::find(node_enum->attrs.begin(), node_enum->attrs.end(),
                     "cppmm|rustify_enum") != node_enum->attrs.end();
}

std::string get_enum_prefix(const NodeEnum* node_enum) {
    for (const auto& a : node_enum->attrs) {
        if (pystring::find(a, "cppmm|enum_prefix|") == 0) {
            return a.substr(18);
        }
    }
    return "";
}

std::string get_enum_suffix(const NodeEnum* node_enum) {
    for (const auto& a : node_enum->attrs) {
        if (pystring::find(a, "cppmm|enum_suffix|") == 0) {
            return a.substr(18);
        }
    }
    return "";
}

std::string remove_suffix(const std::string& str, const std::string& sfx) {
    auto p = str.rfind(sfx);
    if (p >= str.size()) {
        return str;
    }

    if (str.size() - p - sfx.size() == 0) {
        return str.substr(0, p);
    }

    return str;
}

std::string remove_prefix(const std::string& str, const std::string& pfx) {
    auto p = str.find(pfx);
    if (p == 0) {
        return str.substr(pfx.size(), std::string::npos);
    }

    return str;
}

void write_enum(fmt::ostream& out, const NodeEnum* node_enum) {
    std::string repr("u64");
    if (node_enum->size == 8) {
        repr = "u8";
    } else if (node_enum->size == 16) {
        repr = "u16";
    } else if (node_enum->size == 32) {
        repr = "u32";
    }

    bool rustify = has_rustify_enum_attr(node_enum);
    std::string pub = "pub ";

    // if (!node_enum->comment.empty()) {
    //     auto comment = pystring::replace(node_enum->comment, "\n", "\n/// ");
    //     out.print("/// {}\n", comment);
    // }
    out.print("#[repr(transparent)]\n#[derive(Debug, Copy, Clone, PartialEq, "
              "Eq)]\n{0}struct "
              "{1}({0}{2});\n",
              pub, node_enum->name, repr);
    for (const auto& p : node_enum->variants) {
        out.print("{3}const {0}: {1} = {1}({2});\n", p.first, node_enum->name,
                  p.second, pub);
    }

    if (rustify) {
        // Convert the newtype to a proper Rust enum
        // panic on invalid values
        std::string prefix = get_enum_prefix(node_enum);
        std::string suffix = get_enum_suffix(node_enum);

        auto rust_variants = node_enum->cpp_variants;
        for (auto& v : rust_variants) {
            v.first = sanitize_keyword(to_pascal_case(
                remove_prefix(remove_suffix(v.first, suffix), prefix)));
        }

        out.print("\n#[repr({})]\n", repr);
        out.print("#[derive(Debug, Copy, Clone, PartialEq, Eq)]\n");
        out.print("pub enum {} {{\n", node_enum->short_name);
        for (const auto& p : rust_variants) {
            out.print("    {} = {},\n", p.first, p.second);
        }
        out.print("}}\n\n");

        out.print("impl From<{}> for {} {{\n", node_enum->name,
                  node_enum->short_name);
        out.print("    fn from(e: {}) -> {} {{\n", node_enum->name,
                  node_enum->short_name);
        out.print("        match e {{\n");

        for (int i = 0; i < node_enum->variants.size(); ++i) {
            out.print("            {} => {}::{},\n",
                      node_enum->variants[i].first, node_enum->short_name,
                      rust_variants[i].first);
        }
        out.print("            _ => panic!(\"Invalid value {{:?}} for {} in "
                  "conversion\", e),\n",
                  node_enum->short_name);

        out.print("        }}\n");
        out.print("    }}\n");
        out.print("}}\n\n");

        out.print("impl From<{}> for {} {{\n", node_enum->short_name,
                  node_enum->name);
        out.print("    fn from(e: {}) -> {} {{\n", node_enum->short_name,
                  node_enum->name);
        out.print("        match e {{\n");

        for (int i = 0; i < node_enum->variants.size(); ++i) {
            out.print("            {}::{} => {},\n", node_enum->short_name,
                      rust_variants[i].first, node_enum->variants[i].first);
        }
        out.print("        }}\n");
        out.print("    }}\n");
        out.print("}}\n");
    }
}

void write_translation_unit(const char* out_dir, fmt::ostream& out_lib,
                            const TranslationUnit& tu, fmt::ostream& out_cppmmabi_in) {
    fs::path rust_src = fs::path(out_dir) / "src";
    fs::path tu_stem = fs::path(tu.filename).replace_extension("");
    std::string mod_name = pystring::replace(tu_stem.string(), "-", "_");

    fs::path rust_mod = rust_src / (mod_name + ".rs");
    fs::create_directories(rust_mod.parent_path());
    auto out = fmt::output_file(rust_mod.string());

    std::vector<NodeFunction*> node_functions;
    std::vector<NodeRecord*> node_records;
    std::vector<NodeEnum*> node_enums;

    for (const auto& node : tu.decls) {
        if (node->kind == NodeKind::Function) {
            node_functions.push_back(static_cast<NodeFunction*>(node.get()));
        } else if (node->kind == NodeKind::Record) {
            node_records.push_back(static_cast<NodeRecord*>(node.get()));
        } else if (node->kind == NodeKind::Enum) {
            node_enums.push_back(static_cast<NodeEnum*>(node.get()));
        }
    }

    // out_lib.print("pub mod {};\n", mod_name);
    std::string new_mod_name = "";
    for (const auto& p : tu_stem) {
        new_mod_name += pystring::replace(p.string(), "-", "_") + "::";
    }

    out.print("#![allow(non_snake_case)]\n");
    out.print("#![allow(non_camel_case_types)]\n");
    out.print("#![allow(non_upper_case_globals)]\n");
    out.print("#![allow(unused_imports)]\n");

    out.print("use crate::*;\n");
    out.print("pub use crate::cppmmabi::*;\n");
    out.print("use std::os::raw::*;\n\n");

    for (const auto* n : node_records) {
        write_record(out, n, out_cppmmabi_in);
        out.print("\n");

        out_lib.print("pub use {}{} as {};\n", new_mod_name, n->name,
                      n->nice_name);
    }

    out_lib.print("\n");
    out.print("\n");

    for (const auto* n : node_enums) {
        write_enum(out, n);
        out.print("\n");
        out_lib.print("pub use {}{} as {};\n", new_mod_name, n->name,
                      n->nice_name);
        for (const auto& p : n->variants) {
            out_lib.print("pub use {}{};\n", new_mod_name, p.first);
        }

        if (has_rustify_enum_attr(n)) {
            out_lib.print("pub use {}{};\n", new_mod_name, n->short_name);
        }
    }

    out.print("\n");

    out.print("extern \"C\" {{\n\n");

    for (const auto* n : node_functions) {
        if (n->private_) {
            continue;
        }
        write_function(out, n);
        out_lib.print("pub use {}{} as {};\n", new_mod_name, n->name,
                      n->nice_name);
    }

    out.print("\n}} // extern \"C\"\n");
}

void write_modules(fs::path dir) {
    auto out_mod = fmt::output_file((dir / "mod.rs").string());

    for (const auto& entry : fs::directory_iterator(dir)) {
        if (entry.is_regular_file() &&
            entry.path().filename().extension() == ".rs" &&
            entry.path().filename() != "mod.rs") {
            // SPDLOG_DEBUG("got regular file {}", entry.path().string());
            out_mod.print(
                "pub mod {};\n",
                entry.path().filename().replace_extension("").string());
        } else if (entry.is_directory()) {
            out_mod.print("pub mod {0};\npub use {0}::*;\n",
                          entry.path().filename().string());
            write_modules(entry.path());
        }
    }
}

void write(const char* out_dir, const char* project_name,
           const char* c_dir, const std::string& c_cmake_dir,
           const Root& root, size_t starting_point,
           const std::vector<std::string>& libs,
           const std::vector<std::string>& lib_dirs,
           const std::vector<std::string>& authors,
           int version_major,
           int version_minor, int version_patch) {

    expect(starting_point < root.tus.size(),
           "starting point ({}) is out of range ({})", starting_point,
           root.tus.size());

    fs::path rust_src = fs::path(out_dir) / "src";
    fs::path rust_src_out = fs::path(out_dir) / "src";
    fs::create_directories(rust_src);
    fs::path lib_rs = rust_src / "lib.rs";
    fs::path p_cargo_toml = fs::path(out_dir) / "Cargo.toml";

    auto out_lib = fmt::output_file(lib_rs.string());
    out_lib.print(
        R"(#[repr(transparent)] 
pub struct Exception(u32);

impl Exception {{
    pub fn into_result(self) -> Result<(), Error> {{
        match self.0 {{
            0 => {{
                Ok(())
            }}
)");

    for (const auto& ex : EXCEPTION_MAP) {
        out_lib.print(R"(            {} => {{
                let s = unsafe {{ std::ffi::CStr::from_ptr({}_get_exception_string()).to_string_lossy().to_string()}};
                Err(Error::{}(s))
            }}
)",
                      ex.first, project_name, to_pascal_case(ex.second));
    }

    out_lib.print(R"(
            std::u32::MAX => {{
                let s = unsafe {{ std::ffi::CStr::from_ptr({0}_get_exception_string()).to_string_lossy().to_string()}};
                panic!("Unhandled exception: {{}}", s)
            }}
            _ => {{
                let s = unsafe {{ std::ffi::CStr::from_ptr({0}_get_exception_string()).to_string_lossy().to_string()}};
                panic!("Unexpected exception value: {{}} - {{}}", self.0, s)
            }}
        }}
    }}
}}
)",
                  project_name);

    out_lib.print(R"(
#[derive(Debug, PartialEq)]
pub enum Error {{
)");

    for (const auto& ex : EXCEPTION_MAP) {
        out_lib.print("    {}(String),\n", to_pascal_case(ex.second));
    }

    out_lib.print("}}\n");

    out_lib.print(R"(
impl std::error::Error for Error {{
    fn source(&self) -> Option<&(dyn std::error::Error + 'static)> {{
        None
    }}
}}

use std::fmt;
impl fmt::Display for Error {{
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {{
)");

    if (EXCEPTION_MAP.empty()) {
        out_lib.print(R"(
        Ok(())
    }}
}}
)");
    } else {

        out_lib.print(R"(
        match self {{
    )");

        for (const auto& ex : EXCEPTION_MAP) {
            out_lib.print("                Error::{0}(s) => write!(f, \"{0}: "
                          "{{}}\", s),\n",
                          to_pascal_case(ex.second));
        }

        out_lib.print(R"(
        }}
    }}
}}
)");
    }

    out_lib.print("extern {{\n    pub fn {}_get_exception_string() -> *const "
                  "std::os::raw::c_char;\n}}\n\n",
                  project_name);

    // write the abi module
    auto p_cppmmabi = rust_src / "cppmmabi.rs";
    auto out_cppmmabi = fmt::output_file(p_cppmmabi.string());
    out_cppmmabi.print(
            R"(
include!(concat!(env!("OUT_DIR"), "/cppmm_abi_out/", "cppmmabi.rs"));
            )"
    );

    // write the source abi info for the generator
    auto p_cppmmabi_in = fs::path(out_dir) / "cppmm_abi_in" / "cppmmabi.rs";
    fs::create_directories(fs::path(out_dir) / "cppmm_abi_in");
    auto out_cppmmabi_in = fmt::output_file(p_cppmmabi_in.string());

    const auto size = root.tus.size();
    for (size_t i = starting_point; i < size; ++i) {
        const auto& tu = root.tus[i];
        write_translation_unit(out_dir, out_lib, *tu, out_cppmmabi_in);
    }

    // now recurse through the src directory and write the mod files
    for (const auto& entry : fs::directory_iterator(rust_src)) {
        if (entry.is_regular_file() &&
            entry.path().filename().extension() == ".rs" &&
            entry.path().filename() != "lib.rs" &&
            entry.path().filename() != "test.rs") {
            // SPDLOG_DEBUG("got regular file {}", entry.path().string());
            out_lib.print(
                "pub mod {};\n",
                entry.path().filename().replace_extension("").string());
        } else if (entry.is_directory()) {
            out_lib.print("pub mod {};\n", entry.path().filename().string());
            write_modules(entry.path());
        }
    }

    // write the test import and an empty test file
    auto p_test = rust_src / "test.rs";
    auto out_test = fmt::output_file(p_test.string());
    out_test.print(
        R"(// Empty dummy test file for automated testing. This will be replaced by a 
// file copied in from the test suite

#[test]
fn it_works() {{
    assert!(true, "It works!");
}})");

    out_lib.print(R"#(

#[cfg(test)]
mod test;
)#");

    // Generate the quoted interior of the "authors = [...]" string list.
    std::string authors_list_str;
    for (const auto& author : authors) {
        if (!authors_list_str.empty()) {
            authors_list_str += ", ";
        }
        authors_list_str += '"';
        authors_list_str += author;
        authors_list_str += '"';
    }

    std::string cargo_toml =
        fmt::format(R"(
[package]
name = "{}-sys"
version = "{}.{}.{}"
authors = [{}]
edition = "2018"

[build-dependencies]
cmake = "0.1"
regex = "^1.5"
quick-xml = "0.22"

[dependencies]

[package.metadata.docs.rs]
targets = ["x86_64-unknown-linux-gnu"]

)",
                    project_name, version_major, version_minor, version_patch,
                    authors_list_str);

    auto out_cargo_toml = fmt::output_file(p_cargo_toml.string());
    out_cargo_toml.print(cargo_toml);

    auto build_rs = fmt::output_file((fs::path(out_dir) / "build.rs").string());
    build_rs.print(R"#(
fn main() {{
    // Skip linking on docs.rs: https://docs.rs/about/builds#detecting-docsrs
    let building_docs = std::env::var("DOCS_RS").is_ok();
    if building_docs {{
        return;
    }}
    let dst = cmake::Config::new("{0}").build();
    println!("cargo:rustc-link-search=native={{}}", dst.display());
    println!("cargo:rustc-link-lib=dylib={1}-c-{2}_{3}");

    let out_dir = std::env::var("OUT_DIR").unwrap();
    let output = std::process::Command::new("python")
        .args(&["{1}-c/abigen/insert_abi.py", 
            "cppmm_abi_in", 
            &format!("{{}}/cppmm_abi_out", out_dir), 
            &format!("{{}}/build/abigen.txt", out_dir)])
        .output().expect("couldn't do the thing");

    if !output.status.success() {{
        for line in std::str::from_utf8(&output.stderr).unwrap().lines() {{
            println!("cargo:warning={{}}", line);
        }}
        panic!("failed");
    }}


)#",
                   c_cmake_dir.c_str(), project_name, version_major, version_minor);

    for (const auto& d : lib_dirs) {
        build_rs.print("    println!(\"cargo:rustc-link-search=native={}\");\n",
                       d);
    }

    for (const auto& l : libs) {
        build_rs.print("    println!(\"cargo:rustc-link-lib=dylib={}\");\n", l);
    }

    build_rs.print(R"(

    #[cfg(target_os = "linux")]
    println!("cargo:rustc-link-lib=dylib=stdc++");
    #[cfg(target_os = "macos")]
    println!("cargo:rustc-link-lib=dylib=c++");
}}
    )");

} // namespace rust_sys

} // namespace rust_sys
} // namespace cppmm
