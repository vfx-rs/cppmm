#include "record.hpp"
#include "enum.hpp"
#include "namespaces.hpp"
#include "vector.hpp"
#include "function.hpp"

#include "pystring.h"

#include <spdlog/fmt/fmt.h>

namespace cppmm {

namespace ps = pystring;

std::string Record::create_casts() const {
    return fmt::format("CPPMM_DEFINE_POINTER_CASTS({}, {})\n", cpp_qname,
                       c_qname);
}

std::string Record::get_opaqueptr_constructor_body(
    const std::vector<std::string>& call_params) const {
    return fmt::format("    return to_c(new {}({}));", cpp_qname,
                       ps::join(", ", call_params));
}

std::string Record::get_valuetype_constructor_body(
    const std::vector<std::string>& call_params) const {
    return fmt::format("    self = to_c(new (self) {}({}));", cpp_qname,
                       ps::join(", ", call_params));
}

std::string Record::get_opaqueptr_constructor_declaration(
    const std::string& c_method_name,
    const std::vector<std::string>& param_decls) const {
    return fmt::format("{}* {}({})", c_qname, c_method_name,
                       ps::join(", ", param_decls));
}

std::string Record::get_method_declaration(
    const Method& method, std::set<std::string>& includes,
    std::set<std::string>& casts_macro_invocations) const {
    std::vector<std::string> param_decls;

    for (const auto& param : method.params) {
        if (const Record* record =
                param.qtype.type.var.cast_or_null<Record>()) {
            includes.insert(record->filename);
            casts_macro_invocations.insert(record->create_casts());
        } else if (const Enum* enm =
                       param.qtype.type.var.cast_or_null<Enum>()) {
            includes.insert(enm->filename);
        } else if (const Vector* vector =
                       param.qtype.type.var.cast_or_null<Vector>()) {
            casts_macro_invocations.insert(vector->create_casts());
        }

        std::string pdecl = param.create_c_declaration();
        param_decls.push_back(pdecl);
    }

    std::string declaration;

    if (method.is_constructor && kind == RecordKind::OpaquePtr) {
        return get_opaqueptr_constructor_declaration(method.c_qname,
                                                     param_decls);
    } else {
        std::string ret;
        if (method.return_type.type.name == "basic_string" &&
            !method.return_type.is_ref && !method.return_type.is_ptr) {
            ret = "int";
            param_decls.push_back("char* _result_buffer_ptr");
            param_decls.push_back("int _result_buffer_len");
        } else {
            ret = method.return_type.create_c_declaration();
            if (const Record* record =
                    method.return_type.type.var.cast_or_null<Record>()) {
                casts_macro_invocations.insert(record->create_casts());
            }
        }

        if (method.is_static) {
            declaration = fmt::format("{} {}({})", ret, method.c_qname,
                                      ps::join(", ", param_decls));
        } else {
            std::string constqual;
            if (method.is_const) {
                constqual = "const ";
            }
            declaration = fmt::format("{} {}({}{}* self", ret, method.c_qname,
                                      constqual, c_qname);
            if (param_decls.size()) {
                declaration = fmt::format("{}, {})", declaration,
                                          ps::join(", ", param_decls));
            } else {
                declaration = fmt::format("{})", declaration);
            }
        }

        return declaration;
    }
}

std::string
Record::get_operator_body(const Method& method, const std::string& declaration,
                          const std::vector<std::string>& call_params) const {
    std::string body;
    if (kind == RecordKind::OpaquePtr) {
        if (call_params.size() == 0) {
            // unary operator can't work for an opqaue pointer without
            // allocating
            // FIXME: what do we want to do here?
            fmt::print("WARNING: method {} is a unary operator but its parent "
                       "class is of kind OpaquePtr and so cannot be autobound "
                       "without allocating. It will be ignored.\n",
                       declaration);
        } else if (method.op.find("=") == std::string::npos) {
            // Similarly, any non-assigning operator can't work for the same
            // reason
            // FIXME: what do we want to do here?
            fmt::print("WARNING: method {} is a non-assigning operator (i.e. "
                       "it returns a copy) but its parent class is of kind "
                       "OpaquePtr and so cannot be autobound without "
                       "allocating. It will be ignored.\n",
                       declaration);
        } else {
            body = fmt::format("    *to_cpp(self) {} ", method.op);
            body += call_params[0] + ";\n    return self;";
        }
    } else {
        // opaquebytes or valuetype
        if (call_params.size() > 0 &&
            method.op.find("=") != std::string::npos) {
            // assigning operator
            body = fmt::format("    *to_cpp(self) {} ", method.op);
            body += call_params[0] + ";\n    return self;";
        } else if (call_params.size() > 0) {
            // copying operator
            body = fmt::format("    return bit_cast<{}>(*to_cpp(self) {} {});",
                               c_qname, method.op, call_params[0]);
        } else {
            body = fmt::format("    return bit_cast<{}>({}(*to_cpp(self)));",
                               c_qname, method.op);
        }
    }

    return body;
}

std::string
Record::get_method_definition(const Method& method,
                              const std::string& declaration) const {
    std::vector<std::string> call_params;
    for (const auto& p : method.params) {
        call_params.push_back(p.create_c_call());
    }

    std::string body;
    const TypeVariant& return_var = method.return_type.type.var;
    std::string call_prefix;
    if (method.is_static) {
        call_prefix = cpp_qname + "::" + method.cpp_name;
    } else {
        call_prefix = "to_cpp(self)->" + method.cpp_name;
    }

    if (method.is_constructor && kind == RecordKind::OpaquePtr) {
        body = get_opaqueptr_constructor_body(call_params);
    } else if (method.is_constructor && (kind == RecordKind::ValueType ||
                                         kind == RecordKind::OpaqueBytes)) {
        body = get_valuetype_constructor_body(call_params);
    } else if (method.is_copy_assignment) {
        body = "    *to_cpp(self) = ";
        body += call_params[0] + ";\n    return self;";
    } else if (method.is_operator) {
        body = get_operator_body(method, declaration, call_params);
    } else if (method.return_type.type.name == "basic_string" &&
               method.return_type.is_ref) {
        body = get_return_string_ref_body(method, call_prefix, call_params);
    } else if (method.return_type.type.name == "basic_string" &&
               !method.return_type.is_ref) {
        body = get_return_string_copy_body(method, call_prefix, call_params);
    } else if (method.return_type.is_uptr) {
        body = get_return_uniqueptr_body(method, call_prefix, call_params);
    } else if (const Record* record = return_var.cast_or_null<Record>()) {
        if (record->kind == RecordKind::ValueType) {
            body = get_return_valuetype_body(method, call_prefix, call_params);
        } else if (record->kind == RecordKind::OpaqueBytes) {
            body =
                get_return_opaquebytes_body(method, call_prefix, call_params);
        } else {
            body = get_return_opaqueptr_body(method, call_prefix, call_params);
        }
    } else if (return_var.is<Vector>()) {
        body = get_return_opaquebytes_body(method, call_prefix, call_params);
    } else if (method.return_type.type.name == "void") {
        body = get_return_void_body(method, call_prefix, call_params);
    } else {
        body = get_return_builtin_body(method, call_prefix, call_params);
    }

    return fmt::format("{} {{\n{}\n}}", declaration, body);
}

std::string Record::get_definition() const {
    std::string definitions;
    if (kind == cppmm::RecordKind::OpaquePtr) {
    } else if (kind == cppmm::RecordKind::OpaqueBytes) {
        definitions += fmt::format("static_assert(sizeof({}) == "
                                   "sizeof({}), \"sizes do not match\");\n",
                                   cpp_qname, c_qname);
        definitions += fmt::format("static_assert(alignof({}) == alignof({}), "
                                   "\"alignments do not match\");\n",
                                   cpp_qname, c_qname);
    } else if (kind == cppmm::RecordKind::ValueType) {
        definitions += fmt::format("static_assert(sizeof({}) == "
                                   "sizeof({}), \"sizes do not "
                                   "match\");\n",
                                   cpp_qname, c_qname);
        definitions += fmt::format("static_assert(alignof({}) == "
                                   "alignof({}), \"alignments do not "
                                   "match\");\n",
                                   cpp_qname, c_qname);

        for (const auto& field : fields) {
            definitions += fmt::format("static_assert(offsetof({0}, {2}) == "
                                       "offsetof({1}, {2}), "
                                       "\"field offset does not match\");\n",
                                       cpp_qname, c_qname, field.name);
        }
        definitions += "\n";
    }

    return definitions;
}

std::string
Record::get_declaration(std::set<std::string>& casts_macro_invocations) const {
    std::string declarations;
    if (kind == cppmm::RecordKind::OpaquePtr) {
        declarations += fmt::format("typedef struct {0} {0};\n\n", c_qname);
        casts_macro_invocations.insert(create_casts());
    } else if (kind == cppmm::RecordKind::OpaqueBytes) {
        declarations +=
            fmt::format("typedef struct {{ char _private[{}]; }} {} "
                        "CPPMM_ALIGN({});\n",
                        size, c_qname, alignment);

    } else if (kind == cppmm::RecordKind::ValueType) {
        declarations += fmt::format("typedef struct {{\n");

        for (const auto& field : fields) {
            declarations +=
                fmt::format("    {} {};\n", field.qtype.type.name, field.name);
        }
        declarations += fmt::format("}} {};\n\n", c_qname);
    }

    return declarations;
}

} // namespace cppmm
