#include "function.hpp"
#include "enum.hpp"
#include "namespaces.hpp"
#include "record.hpp"
#include "vector.hpp"

#include "pystring.h"

#include <spdlog/fmt/fmt.h>

namespace cppmm {

namespace ps = pystring;

Function::Function(std::string cpp_name, std::string c_name,
                   QualifiedType return_type, std::vector<Param> params,
                   std::string comment, std::vector<std::string> namespaces,
                   std::string filename, std::vector<std::string> template_args)
    : cpp_name(cpp_name), c_name(c_name), return_type(return_type),
      params(params), comment(comment), namespaces(namespaces),
      filename(filename) {
    cpp_qname = prefix_from_namespaces(namespaces, "::") + cpp_name;
    c_qname = prefix_from_namespaces(namespaces, "_") + c_name;
    c_pretty_name =
        prefix_from_namespaces(rename_all_namespaces(namespaces), "_") + c_name;

    if (!template_args.empty()) {
        cpp_qname += fmt::format("<{}>", ps::join(", ", template_args));
    }
}

std::string
Function::get_declaration(std::set<std::string>& includes,
                          std::set<std::string>& casts_macro_invocations,
                          std::vector<std::string>& pretty_defines) const {

    std::vector<std::string> param_decls;
    for (const auto& param : params) {
        if (const Record* record =
                param.qtype.type.var.cast_or_null<Record>()) {
            includes.insert(record->filename);
            casts_macro_invocations.insert(record->create_casts());
        } else if (const Enum* enm =
                       param.qtype.type.var.cast_or_null<Enum>()) {
            includes.insert(enm->filename);
        }

        std::string pdecl = param.create_c_declaration();
        param_decls.push_back(pdecl);
    }

    auto ret = return_type.create_c_declaration();
    if (const Record* record =
            return_type.type.var.cast_or_null<Record>()) {
        casts_macro_invocations.insert(record->create_casts());
    }

    pretty_defines.push_back(
        fmt::format("#define {} {}", c_pretty_name, c_qname));

    return fmt::format("{} {}({})", ret, c_qname, ps::join(", ", param_decls));
}

std::string Function::get_definition(const std::string& declaration) const {

    std::vector<std::string> call_params;
    for (const auto& p : params) {
        call_params.push_back(p.create_c_call());
    }

    std::string body;
    const std::string call_prefix =
        prefix_from_namespaces(namespaces, "::") + cpp_name;
    const TypeVariant& return_var = return_type.type.var;

    if (return_type.type.name == "basic_string" && return_type.is_ref) {
        body = get_return_string_ref_body(*this, call_prefix, call_params);
    } else if (return_type.type.name == "basic_string" && !return_type.is_ref) {
        body = get_return_string_copy_body(*this, call_prefix, call_params);
    } else if (return_type.is_uptr) {
        body = get_return_uniqueptr_body(*this, call_prefix, call_params);
    } else if (const Record* record = return_var.cast_or_null<Record>()) {
        if (record->kind == RecordKind::ValueType) {
            body = get_return_valuetype_body(*this, call_prefix, call_params);
        } else if (record->kind == RecordKind::OpaqueBytes) {
            body = get_return_opaquebytes_body(*this, call_prefix, call_params);
        } else {
            body = get_return_opaqueptr_body(*this, call_prefix, call_params);
        }
    } else if (return_var.is<Vector>()) {
        body = get_return_opaquebytes_body(*this, call_prefix, call_params);
    } else if (return_type.type.name == "void") {
        body = get_return_void_body(*this, call_prefix, call_params);
    } else {
        body = get_return_builtin_body(*this, call_prefix, call_params);
    }

    return fmt::format("{} {{\n{}\n}}", declaration, body);
}

std::string
get_return_string_ref_body(const Function& function,
                           const std::string& call_prefix,
                           const std::vector<std::string>& call_params) {
    // just get the char* from the string ref
    return fmt::format("    return {}({}).c_str();", call_prefix,
                       ps::join(", ", call_params));
}

std::string
get_return_string_copy_body(const Function& function,
                            const std::string& call_prefix,
                            const std::vector<std::string>& call_params) {
    // assign the return value to a temporary string, then copy the chars into
    // the out parameters we added to the call params
    return fmt::format(R"#(    const std::string result = {}({});
    safe_strcpy(_result_buffer_ptr, result, _result_buffer_len);
    return result.size();)#",
                       call_prefix, ps::join(", ", call_params));
}

std::string
get_return_valuetype_body(const Function& function,
                          const std::string& call_prefix,
                          const std::vector<std::string>& call_params) {
    // just bit_cast the return value
    return fmt::format("    return bit_cast<{}>({}({}));",
                       function.return_type.type.get_c_qname(), call_prefix,
                       ps::join(", ", call_params));
}

std::string
get_return_opaquebytes_body(const Function& function,
                            const std::string& call_prefix,
                            const std::vector<std::string>& call_params) {
    // here we need to assign to a temporary variable, then placement new the
    // move constructor into our opaque bytes struct so that the temp does not
    // try and clean up after itself (assuming that the type has implemented
    // move constructors correctly)
    return fmt::format(R"#(    {0} tmp = {1}({2});
    {3} ret;
    new (&ret) {0}(std::move(tmp));
    return ret;)#",

                       function.return_type.type.get_cpp_qname(), call_prefix,
                       ps::join(", ", call_params),
                       function.return_type.type.get_c_qname());
}

std::string
get_return_opaqueptr_body(const Function& function,
                          const std::string& call_prefix,
                          const std::vector<std::string>& call_params) {
    // Just cast the pointer.
    // FIXME: what if the function returns an opaqueptr type on the stack?
    return fmt::format("    return to_c({}({}));", call_prefix,
                       ps::join(", ", call_params));
}

std::string
get_return_uniqueptr_body(const Function& function,
                          const std::string& call_prefix,
                          const std::vector<std::string>& call_params) {
    // FIXME: this assumes that what's stored in the uniqueptr is not a
    // builtin, which is almost certainly always true, but might not be.
    return fmt::format("    return to_c({}({}).release());", call_prefix,
                       ps::join(", ", call_params));
}

std::string
get_return_builtin_body(const Function& function,
                        const std::string& call_prefix,
                        const std::vector<std::string>& call_params) {
    return fmt::format("    return {}({});", call_prefix,
                       ps::join(", ", call_params));
}

std::string get_return_void_body(const Function& function,
                                 const std::string& call_prefix,
                                 const std::vector<std::string>& call_params) {
    return fmt::format("    {}({});", call_prefix, ps::join(", ", call_params));
}

} // namespace cppmm
