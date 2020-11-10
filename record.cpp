#include "record.hpp"
#include "namespaces.hpp"

#include "pystring.h"

#include <fmt/format.h>

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

std::string Record::get_method_definition(const Method& method,
                                  const std::string& declaration) const {
    std::vector<std::string> call_params;
    for (const auto& p : method.params) {
        call_params.push_back(p.create_c_call());
    }

    std::string body;

    if (method.is_constructor && kind == TypeKind::OpaquePtr) {
        body = get_opaqueptr_constructor_body(call_params);
    } else if (method.is_constructor && (kind == TypeKind::ValueType ||
                                         kind == TypeKind::OpaqueBytes)) {
        body = get_valuetype_constructor_body(call_params);
    } else if (method.is_copy_assignment) {
        body = "    *to_cpp(self) = ";
        body += call_params[0] + ";\n    return self;";
    } else if (method.is_operator) {
        if (kind == TypeKind::OpaquePtr) {
            if (call_params.size() == 0) {
                // unary operator can't work for an opqaue pointer without
                // allocating
                // FIXME: what do we want to do here?
                fmt::print(
                    "WARNING: method {} is a unary operator but its parent "
                    "class is of kind OpaquePtr and so cannot be autobound "
                    "without allocating. It will be ignored.\n",
                    declaration);
            } else if (method.op.find("=") == std::string::npos) {
                // Similarly, any non-assigning operator can't work for the same
                // reason
                // FIXME: what do we want to do here?
                fmt::print(
                    "WARNING: method {} is a non-assigning operator (i.e. "
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
                body =
                    fmt::format("    return bit_cast<{}>(*to_cpp(self) {} {});",
                                c_qname, method.op, call_params[0]);
            } else {
                body =
                    fmt::format("    return bit_cast<{}>({}(*to_cpp(self)));",
                                c_qname, method.op);
            }
        }
    } else {
        bool return_string_ref =
            method.return_type.qtype.type.name == "basic_string" &&
            method.return_type.qtype.is_ref;
        bool return_string_copy =
            method.return_type.qtype.type.name == "basic_string" &&
            !method.return_type.qtype.is_ref;
        if (return_string_copy) {
            // need to copy to the out parameters
            body = "    const std::string result = ";
        } else if (method.return_type.qtype.type.name != "void") {
            body = "    return ";
        } else {
            body = "    ";
        }

        bool bitcast_return_type =
            method.return_type.qtype.type.record &&
            (method.return_type.qtype.type.record->kind ==
                 TypeKind::ValueType ||
             method.return_type.qtype.type.record->kind ==
                 TypeKind::OpaqueBytes);

        if (bitcast_return_type) {
            body += fmt::format("bit_cast<{}>(",
                                method.return_type.qtype.type.record->c_name);
        } else if (method.return_type.qtype.requires_cast) {
            body += "to_c(";
        }
        if (method.is_static) {
            body += cpp_qname + "::";
        } else {
            body += "to_cpp(self)->";
        }
        body += method.cpp_name;
        body += fmt::format("({})", ps::join(", ", call_params));
        if (method.return_type.qtype.is_uptr) {
            body += ".release()";
        } else if (return_string_ref) {
            body += ".c_str()";
        }
        if (method.return_type.qtype.requires_cast || bitcast_return_type) {
            body += ")";
        }
        body += ";";

        if (return_string_copy) {
            body += "\n    safe_strcpy(_result_buffer_ptr, result, "
                    "_result_buffer_len);\n    return result.size();";
        }
    }

    return fmt::format("{} {{\n{}\n}}", declaration, body);
}

} // namespace cppmm
