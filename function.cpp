#include "function.hpp"
#include "namespaces.hpp"
#include "enum.hpp"
#include "record.hpp"

#include "pystring.h"

#include <fmt/format.h>

namespace cppmm {

namespace ps = pystring;

std::string Function::get_declaration(
    std::set<std::string>& includes,
    std::set<std::string>& casts_macro_invocations) const {
    std::string c_function_name =
        fmt::format("{}{}", prefix_from_namespaces(namespaces, "_"),
                    c_name);

    std::vector<std::string> param_decls;
    for (const auto& param : params) {
        if (param.qtype.type.record) {
            includes.insert(param.qtype.type.record->filename);
            casts_macro_invocations.insert(
                param.qtype.type.record->create_casts());
        } else if (param.qtype.type.enm) {
            includes.insert(param.qtype.type.enm->filename);
        }

        std::string pdecl = param.create_c_declaration();
        param_decls.push_back(pdecl);
    }

    std::string ret;
    if (return_type.qtype.type.name == "basic_string" &&
        !return_type.qtype.is_ref &&
        !return_type.qtype.is_ptr) {
        ret = "int";
        param_decls.push_back("char* _result_buffer_ptr");
        param_decls.push_back("int _result_buffer_len");
    } else {
        ret = return_type.create_c_declaration();
        if (return_type.qtype.type.record) {
            casts_macro_invocations.insert(
                return_type.qtype.type.record->create_casts());
        }
    }

    return fmt::format("{} {}({})", ret, c_function_name,
                       ps::join(", ", param_decls));
}

std::string
Function::get_definition(const std::string& declaration) const {

    std::vector<std::string> call_params;
    for (const auto& p : params) {
        call_params.push_back(p.create_c_call());
    }

    std::string body;
    bool return_string_copy =
        return_type.qtype.type.name == "basic_string" &&
        !return_type.qtype.is_ref &&
        !return_type.qtype.is_ptr;
    if (return_string_copy) {
        // need to copy to the out parameters
        body = "    const std::string result = ";
    } else if (return_type.qtype.type.name != "void") {
        body = "    return ";
    } else {
        body = "    ";
    }

    bool bitcast_return_type =
        return_type.qtype.type.record &&
        (return_type.qtype.type.record->kind == TypeKind::ValueType ||
         return_type.qtype.type.record->kind == TypeKind::OpaqueBytes);

    if (bitcast_return_type) {
        body += fmt::format("bit_cast<{}>(",
                            return_type.qtype.type.record->c_name);
    } else if (return_type.qtype.requires_cast) {
        body += "to_c(";
    }

    body +=
        prefix_from_namespaces(namespaces, "::") + cpp_name;
    body += fmt::format("({})", ps::join(", ", call_params));

    if (return_type.qtype.is_uptr) {
        body += ".release()";
    }
    if (return_type.qtype.requires_cast || bitcast_return_type) {
        body += ")";
    }
    body += ";";

    if (return_string_copy) {
        body += "\n    safe_strcpy(_result_buffer_ptr, result, "
                "_result_buffer_len);\n    return result.size();";
    }

    return fmt::format("{} {{\n{}\n}}", declaration, body);
}

} // namespace cppmm
