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
        return "c_uchar";
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
    return fmt::format("extern fn({}) -> {}", pystring::join(", ", params),
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
        result.push_back(fmt::format("{}: {}", sanitize_keyword(p.name),
                                     convert_type(p.type.get())));
    }
    return result;
}

std::vector<std::string> convert_fields(const std::vector<Field>& fields) {
    std::vector<std::string> result;
    for (const auto& f : fields) {
        result.push_back(fmt::format("pub {}: {}", sanitize_keyword(f.name),
                                     convert_type(f.type.get())));
    }
    return result;
}

void write_function(fmt::ostream& out, const NodeFunction* node_function) {
    // don't want to bind the internal conversion functions
    if (node_function->private_) {
        return;
    }

    std::vector<std::string> params = convert_params(node_function->params);

    if (!node_function->comment.empty()) {
        auto comment =
            pystring::replace(node_function->comment, "\n", "\n/// ");
        out.print("/// {}\n", comment);
    }
    out.print("pub fn {}({})", node_function->name,
              pystring::join(", ", params));

    std::string ret = convert_type(node_function->return_type.get());
    if (ret != "void") {
        out.print(" -> {};\n\n", ret);
    } else {
        out.print(";\n\n");
    }
}

void write_record(fmt::ostream& out, const NodeRecord* node_record) {
    if (!node_record->comment.empty()) {
        auto comment = pystring::replace(node_record->comment, "\n", "\n/// ");
        out.print("/// {}\n", comment);
    }
    out.print("#[repr(C, align({}))]\n", node_record->align / 8);
    out.print("#[derive(Clone)]\n");
    out.print("pub struct {} {{\n", node_record->name);

    BindType bt = bind_type(*node_record);
    if (bt == BindType::OpaquePtr) {
        // temporary hack until ptr is implemented
        bt = BindType::OpaqueBytes;
    }

    if (bt == BindType::ValueType) {
        std::vector<std::string> fields = convert_fields(node_record->fields);
        out.print("    {},\n", pystring::join(",\n    ", fields));
    } else if (bt == BindType::OpaqueBytes) {
        out.print("    _inner: [u8; {}]\n", node_record->size / 8);
    } else {
        // ...
    }

    out.print("}}\n");

    if (bt == BindType::OpaqueBytes) {
        out.print(R"(
impl Default for {} {{
    fn default() -> Self {{
        Self {{ _inner: [0u8; {}] }}
    }}
}}
)",
                  node_record->name, node_record->size / 8);
    }
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

    if (!node_enum->comment.empty()) {
        auto comment = pystring::replace(node_enum->comment, "\n", "\n/// ");
        out.print("/// {}\n", comment);
    }
    out.print("#[repr(transparent)]\n#[derive(Debug, Copy, Clone)]\npub struct "
              "{}(pub {});\n",
              node_enum->name, repr);
    for (const auto& p : node_enum->variants) {
        out.print("pub const {0}: {1} = {1}({2});\n", p.first, node_enum->name,
                  p.second);
    }
}

void write_translation_unit(const char* out_dir, fmt::ostream& out_lib,
                            const TranslationUnit& tu) {
    fs::path rust_src = fs::path(out_dir) / "src";
    fs::path tu_stem = fs::path(tu.filename).stem();
    std::string mod_name = pystring::replace(tu_stem.string(), "-", "_");

    fs::path rust_mod = rust_src / (mod_name + ".rs");
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

    out_lib.print("pub mod {};\n", mod_name);

    out.print("#![allow(non_snake_case)]\n");
    out.print("#![allow(non_camel_case_types)]\n");
    out.print("#![allow(non_upper_case_globals)]\n");
    out.print("#![allow(unused_imports)]\n");

    out.print("use crate::*;\n");
    out.print("use std::os::raw::*;\n\n");

    for (const auto* n : node_records) {
        write_record(out, n);
        out.print("\n");

        out_lib.print("pub use {}::{} as {};\n", mod_name, n->name,
                      n->nice_name);
    }

    out_lib.print("\n");
    out.print("\n");

    for (const auto* n : node_enums) {
        write_enum(out, n);
        out.print("\n");
        out_lib.print("pub use {}::{} as {};\n", mod_name, n->name,
                      n->nice_name);
        for (const auto& p : n->variants) {
            out_lib.print("pub use {}::{};\n", mod_name, p.first);
        }
    }

    out.print("\n");

    out.print("extern \"C\" {{\n\n");

    for (const auto* n : node_functions) {
        if (n->private_) {
            continue;
        }
        write_function(out, n);
        out_lib.print("pub use {}::{} as {};\n", mod_name, n->name,
                      n->nice_name);
    }

    out.print("\n}} // extern \"C\"\n");
}

void write(const char* out_dir, const char* project_name, const char* c_dir,
           const Root& root, size_t starting_point,
           const std::vector<std::string>& libs,
           const std::vector<std::string>& lib_dirs, int version_major,
           int version_minor, int version_patch) {

    expect(starting_point < root.tus.size(),
           "starting point ({}) is out of range ({})", starting_point,
           root.tus.size());

    fs::path rust_src = fs::path(out_dir) / "src";
    fs::path lib_rs = rust_src / "lib.rs";
    fs::path p_cargo_toml = fs::path(out_dir) / "Cargo.toml";

    auto out_lib = fmt::output_file(lib_rs.string());

    const auto size = root.tus.size();
    for (size_t i = starting_point; i < size; ++i) {
        const auto& tu = root.tus[i];
        write_translation_unit(out_dir, out_lib, *tu);
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

    std::string cargo_toml =
        fmt::format(R"(
[package]
name = "{}-sys"
version = "{}.{}.{}"
authors = ["Anders Langlands <anderslanglands@gmail.com>"]
edition = "2018"

[build-dependencies]
cmake = "0.1"

[dependencies]

)",
                    project_name, version_major, version_minor, version_patch);

    auto out_cargo_toml = fmt::output_file(p_cargo_toml.string());
    out_cargo_toml.print(cargo_toml);

    auto build_rs = fmt::output_file((fs::path(out_dir) / "build.rs").string());
    build_rs.print(R"#(
fn main() {{
    let dst = cmake::Config::new("{}").build();
    println!("cargo:rustc-link-search=native={{}}", dst.display());
    println!("cargo:rustc-link-lib=dylib={}-c-{}_{}");
)#",
                   c_dir, project_name, version_major, version_minor);

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
