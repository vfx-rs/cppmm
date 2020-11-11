#include "decls.hpp"
#include "exports.hpp"
#include "namespaces.hpp"

#include "pystring.h"

#include <clang/AST/DeclCXX.h>
#include <clang/AST/Type.h>

#include <fmt/format.h>

using namespace clang;

namespace cppmm {

std::unordered_map<std::string, cppmm::File> files;
std::unordered_map<std::string, cppmm::Record> records;
std::unordered_map<std::string, cppmm::Enum> enums;

bool is_builtin(const QualType& qt) {
    return (qt->isBuiltinType() ||
            (qt->isPointerType() && qt->getPointeeType()->isBuiltinType()));
}

bool is_recordpointer(const QualType& qt) {
    return ((qt->isReferenceType() || qt->isPointerType()) &&
            qt->getPointeeType()->isRecordType());
}

std::string qualified_type_name(const cppmm::Type& type) {
    return cppmm::prefix_from_namespaces(type.namespaces, "::") + type.name;
}

cppmm::Param process_param_type(const std::string& param_name,
                                const QualType& qt);

cppmm::Record* process_record(const CXXRecordDecl* record) {
    std::string cpp_name = record->getNameAsString();
    std::vector<std::string> namespaces = cppmm::get_namespaces(record->getParent());

    const auto c_qname =
        cppmm::prefix_from_namespaces(namespaces, "_") + cpp_name;
    if (records.find(c_qname) != records.end()) {
        // already done this type, return
        return &records[c_qname];
    }

    auto it_ex_record = cppmm::ex_records.find(c_qname);
    if (it_ex_record == cppmm::ex_records.end()) {
        // fmt::print("WARNING: record '{}' has no export definition\n",
        // c_name);
        return nullptr;
    }

    std::vector<cppmm::Param> fields;
    for (const auto* field : record->fields()) {
        std::string field_name = field->getNameAsString();
        // fmt::print("    field: {}\n", field->getNameAsString());
        cppmm::Param field_param =
            process_param_type(field_name, field->getType());
        fields.push_back(field_param);
        // fmt::print("    {}\n", field_param);
    }

    // get size and alignment info
    // clang returns in bits so divide by 8 to get bytes
    ASTContext& ctx = record->getASTContext();
    size_t size = ctx.getTypeSize(record->getTypeForDecl()) / 8;
    size_t alignment = ctx.getTypeAlign(record->getTypeForDecl()) / 8;

    // fmt::print("Processed record {} -> {} in {}\n", cpp_name, c_qname,
    //    it_ex_record->second.filename);
    auto rec = cppmm::Record{
        .cpp_name = cpp_name,
        .namespaces = namespaces,
        .c_name = cpp_name,
        .kind = it_ex_record->second.kind,
        .filename = it_ex_record->second.filename,
        .fields = fields,
        .methods = {},
        .size = size,
        .alignment = alignment,
        .cpp_qname = cppmm::prefix_from_namespaces(namespaces, "::") + cpp_name,
        .c_qname = c_qname,
    };

    if (rec.kind == cppmm::TypeKind::ValueType && !rec.is_pod()) {
        fmt::print("ERROR: {} is valuetype but not POD\n", rec.c_qname);
        return nullptr;
    } else if (rec.kind == cppmm::TypeKind::OpaqueBytes && !rec.is_pod()) {
        fmt::print("ERROR: {} is opaquebytes but not POD\n", rec.c_qname);
        return nullptr;
    }

    records[c_qname] = rec;
    // fmt::print("MATCHED: {}\n", cpp_name);

    return &records[c_qname];
}

cppmm::Enum* process_enum(const EnumDecl* enum_decl) {
    std::string cpp_name = enum_decl->getNameAsString();
    std::vector<std::string> namespaces =
        cppmm::get_namespaces(enum_decl->getParent());
    const auto c_name = cpp_name;
    const auto cpp_qname =
        cppmm::prefix_from_namespaces(namespaces, "::") + cpp_name;
    const auto c_qname =
        cppmm::prefix_from_namespaces(namespaces, "_") + c_name;
    if (enums.find(c_qname) != enums.end()) {
        // already done this type, return
        return &enums[c_qname];
    }

    auto it_ex_enum = cppmm::ex_enums.find(c_qname);
    if (it_ex_enum == cppmm::ex_enums.end()) {
        // fmt::print("WARNING: enum '{}' has no export definition\n",
        // c_qname);
        return nullptr;
    }

    // fmt::print("Processed enum {} -> {} in {}\n", cpp_name, c_qname,
    //    it_ex_enum->second.filename);

    std::vector<std::pair<std::string, uint64_t>> enumerators;
    for (const auto& ecd : enum_decl->enumerators()) {
        enumerators.push_back(std::make_pair<std::string, uint64_t>(
            ecd->getNameAsString(), ecd->getInitVal().getLimitedValue()));
    }

    enums[c_qname] = cppmm::Enum{.cpp_name = cpp_name,
                                 .namespaces = namespaces,
                                 .c_name = c_name,
                                 .filename = it_ex_enum->second.filename,
                                 .enumerators = enumerators,
                                 .cpp_qname = cpp_qname,
                                 .c_qname = c_qname};

    // fmt::print("MATCHED: {}\n", cpp_name);

    return &enums[c_qname];
}

cppmm::Param process_pointee_type(const std::string& param_name,
                                  const QualType& qt) {
    cppmm::Param result;
    result.name = param_name;

    if (is_builtin(qt)) {
        std::string name = qt.getTypePtr()
                               ->getUnqualifiedDesugaredType()
                               ->getAs<BuiltinType>()
                               ->desugar()
                               .getAsString();

        // C++ doesn't like _Bool but we can include stdbool.h for C
        if (name == "_Bool") {
            name = "bool";
        }
        result.qtype.type = cppmm::Type{name, {}, .is_builtin = true};
        result.qtype.requires_cast = false;
    } else if (qt->isRecordType()) {
        const CXXRecordDecl* crd = qt->getAsCXXRecordDecl();
        if (crd->getNameAsString() == "unique_ptr") {
            const auto* tst = qt->getAs<TemplateSpecializationType>();
            result =
                process_pointee_type(param_name, tst->getArgs()->getAsType());
            result.qtype.is_uptr = true;
        } else if (crd->getNameAsString() == "vector") {

        } else {
            const CXXRecordDecl* crd = qt->getAsCXXRecordDecl();
            cppmm::Record* record_ptr = process_record(crd);
            if (record_ptr == nullptr) {
                // fmt::print("ERROR: could not process record for {}\n",
                //            crd->getNameAsString());
            }
            std::string type_name = crd->getNameAsString();
            result.qtype.type =
                cppmm::Type{.name = type_name,
                            .namespaces = cppmm::get_namespaces(
                                qt->getAsCXXRecordDecl()->getParent()),
                            .is_builtin = false,
                            .is_enum = false,
                            .is_func_proto = false,
                            .record = record_ptr,
                            .enm = nullptr};
            result.qtype.requires_cast =
                !(crd->getNameAsString() == "basic_string" ||
                  crd->getNameAsString() == "string_view");
        }
    } else if (qt->isEnumeralType()) {
        const auto* enum_decl = qt->getAs<EnumType>()->getDecl();
        const cppmm::Enum* enm = process_enum(enum_decl);

        result.qtype.type = cppmm::Type{.name = enm->cpp_name,
                                        .namespaces = enm->namespaces,
                                        .is_builtin = false,
                                        .is_enum = true,
                                        .is_func_proto = false,
                                        .record = nullptr,
                                        .enm = enm};
    } else {
        fmt::print("Unhandled type: {}\n", qt.getAsString());
        qt->dump();
    }

    result.qtype.is_const = qt.isConstQualified();
    return result;
}

cppmm::Param process_param_type(const std::string& param_name,
                                const QualType& qt) {
    cppmm::Param result;
    bool is_ptr = qt->isPointerType();
    bool is_ref = qt->isReferenceType();

    if (is_ptr || is_ref) {
        result = process_pointee_type(param_name, qt->getPointeeType());
        result.qtype.is_ptr = is_ptr;
        result.qtype.is_ref = is_ref;
    } else if (is_builtin(qt)) {
        result = process_pointee_type(param_name, qt);
    } else if (qt->isRecordType()) {
        result = process_pointee_type(param_name, qt);
    } else if (qt->isEnumeralType()) {
        result = process_pointee_type(param_name, qt);
    } else {
        fmt::print("ERROR unhandled param type {}\n", qt.getAsString());
        qt->dump();
    }

    return result;
}

std::string get_decl_comment(const Decl* decl) {
    ASTContext& ctx = decl->getASTContext();
    SourceManager& sm = ctx.getSourceManager();
    const RawComment* rc = ctx.getRawCommentForDeclNoCache(decl);
    std::string result;
    if (rc) {
        std::string raw = rc->getRawText(sm);
        // dedent lines
        std::vector<std::string> lines;
        pystring::splitlines(raw, lines);
        for (auto& line : lines) {
            line = pystring::strip(line);
        }

        result = pystring::join("\n", lines);
    }

    return result;
}

cppmm::Function process_function(const FunctionDecl* function,
                                 const cppmm::ExportedFunction& ex_function,
                                 std::vector<std::string> namespaces) {
    std::vector<cppmm::Param> params;
    for (const auto& p : function->parameters()) {
        const auto param_name = p->getNameAsString();
        params.push_back(process_param_type(param_name, p->getType()));
    }

    std::string comment = get_decl_comment(function);

    return cppmm::Function{
        ex_function.cpp_name,
        ex_function.c_name,
        process_param_type("", function->getReturnType()),
        params,
        comment,
        namespaces,
    };
}

cppmm::Method process_method(const CXXMethodDecl* method,
                             const cppmm::ExportedMethod& ex_method,
                             const cppmm::Record* record) {
    std::vector<cppmm::Param> params;
    for (const auto& p : method->parameters()) {
        const auto param_name = p->getNameAsString();
        params.push_back(process_param_type(param_name, p->getType()));
    }

    std::string comment = get_decl_comment(method);

    bool is_constructor = false;
    bool is_copy_constructor = false;
    bool is_copy_assignment = method->isCopyAssignmentOperator();
    bool is_operator = false;
    bool is_conversion_operator = false;
    std::string op;

    if (isa<CXXConstructorDecl>(method)) {
        const auto* ctor = cast<CXXConstructorDecl>(method);
        is_constructor = true;
        is_copy_constructor = ctor->isCopyConstructor();
    } else if (ex_method.cpp_name.find("operator") == 0) {
        // we assume that clang always concatenates the operator name with the
        // symbols so we can use this to tell the difference with a conversion
        // operator. FIXME: is this true?
        std::vector<std::string> toks;
        pystring::split(ex_method.cpp_name, toks);
        if (toks.size() == 1) {
            op = ex_method.cpp_name.substr(8, 100);
            is_operator = true;
            // fmt::print("Got operator '{}'\n", op);
        } else {
            op = toks[1];
            is_conversion_operator = true;
            // fmt::print("Got conversion op to '{}'\n", op);
        }
    }

    // do some parameter patching. clang ignores the parameter name for copy
    // ctor and assignment but we need one so just use "other"
    if (is_copy_constructor || is_copy_assignment) {
        params[0].name = "other";
    }

    std::vector<std::string> namespaces = record->namespaces;
    namespaces.push_back(record->c_name);

    return cppmm::Method{ex_method.cpp_name,
                         ex_method.c_name,
                         process_param_type("", method->getReturnType()),
                         params,
                         comment,
                         namespaces,
                         method->isConst(),
                         method->isStatic(),
                         is_constructor,
                         is_copy_constructor,
                         is_copy_assignment,
                         is_operator,
                         is_conversion_operator,
                         op};
}

} // namespace cppmm

namespace fmt {
std::ostream& operator<<(std::ostream& os, const cppmm::Method& method);
}
