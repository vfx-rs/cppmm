
//------------------------------------------------------------------------------
// vfx-rs
//------------------------------------------------------------------------------
#include "cppmm_ast_read.hpp"
#include "base64.hpp"
#include "filesystem.hpp"
#include "json.hh"

#include <iostream>
#include <memory>

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

namespace fs = ghc::filesystem;

namespace nln = nlohmann;

namespace cppmm {
namespace read {

namespace {
const char* ALIGN = "align";
const char* ALIAS = "alias";
const char* ATTRIBUTES = "attributes";
const char* ABSTRACT = "abstract";
const char* CHILDREN = "children";
const char* DESTRUCTOR = "destructor";
const char* COLLAPSE = "collapse";
const char* COMMENT = "comment";
const char* CONSTRUCTOR = "constructor";
const char* COPY_CONSTRUCTOR = "copy_constructor";
const char* CONST = "const";
const char* DECLS = "decls";
const char* ENUM_C = "Enum";
const char* ENUM_L = "enum";
const char* FIELDS = "fields";
const char* FILENAME = "filename";
const char* FUNCTION_C = "Function";
const char* ID = "id";
const char* INDEX = "index";
const char* KIND = "kind";
const char* METHODS = "methods";
const char* NAME = "name";
const char* NAMESPACE_C = "Namespace";
const char* NAMESPACES = "namespaces";
const char* QUALIFIED_NAME = "qualified_name";
const char* SHORT_NAME = "short_name";
const char* PARAMS = "params";
const char* SIZE = "size";
const char* STATIC = "static";
const char* RECORD_C = "Record";
const char* RECORD_L = "record";
const char* TYPE = "type";
const char* TRIVIALLY_COPYABLE = "trivially_copyable";
const char* POINTEE = "pointee";
const char* RETURN = "return";
const char* SOURCE_INCLUDES = "source_includes";
const char* INCLUDE_PATHS = "include_paths";
const char* VARIANTS = "variants";
const char* VAR_C = "Var";
const char* ELEMENT_TYPE = "element_type";
const char* FUNCTION_POINTER_TYPEDEF_C = "FunctionPointerTypedef";
const char* FUNCTION_POINTER_TYPEDEF_L = "function_pointer_typedef";
} // namespace

//------------------------------------------------------------------------------
NodeTypePtr read_type(const nln::json& json);

//------------------------------------------------------------------------------
NodeTypePtr read_type_builtin(const nln::json& json) {
    return NodeBuiltinType::n("", json[ID].get<Id>(),
                              json[TYPE].get<std::string>(),
                              json[CONST].get<bool>());
}

//------------------------------------------------------------------------------
NodeTypePtr read_type_pointer(const nln::json& json, PointerKind pointer_kind) {
    return NodePointerType::n(pointer_kind, read_type(json[POINTEE]),
                              json[CONST].get<bool>());
}

//------------------------------------------------------------------------------
NodeTypePtr read_type_record(const nln::json& json) {
    return NodeRecordType::n(
        "", json[ID].get<Id>(), json[TYPE].get<std::string>(),
        json[RECORD_L].get<NodeId>(), json[CONST].get<bool>());
}

//------------------------------------------------------------------------------
NodeTypePtr read_type_enum(const nln::json& json) {
    return NodeEnumType::n("", json[ID].get<Id>(),
                           json[TYPE].get<std::string>(),
                           json[ENUM_L].get<NodeId>(), json[CONST].get<bool>());
}

//------------------------------------------------------------------------------
NodeTypePtr read_type_const_array(const nln::json& json) {
    return NodeArrayType::n("", json[ID].get<NodeId>(),
                            json[TYPE].get<std::string>(),
                            read_type(json[ELEMENT_TYPE]),
                            json[SIZE].get<int>(), json[CONST].get<bool>());
}

//------------------------------------------------------------------------------
NodeTypePtr read_type_unknown(const nln::json& json) {
    return NodeUnknownType::n(json[CONST].get<bool>());
}

NodeTypePtr read_type_function_proto(const nln::json& json);

//------------------------------------------------------------------------------
NodeTypePtr read_type(const nln::json& json) {

    auto kind_iter = json.find(KIND);
    if (kind_iter != json.end()) {
        auto kind = json[KIND].get<std::string>();
        if (kind == "BuiltinType") {
            return read_type_builtin(json);
        } else if (kind == "RecordType") {
            return read_type_record(json);
        } else if (kind == "Reference") {
            return read_type_pointer(json, PointerKind::Reference);
        } else if (kind == "RValueReference") {
            return read_type_pointer(json, PointerKind::RValueReference);
        } else if (kind == "Pointer") {
            return read_type_pointer(json, PointerKind::Pointer);
        } else if (kind == "EnumType") {
            return read_type_enum(json);
        } else if (kind == "FunctionProtoType") {
            return read_type_function_proto(json);
        } else if (kind == "ConstantArrayType") {
            return read_type_const_array(json);
        }

        SPDLOG_CRITICAL("Unhandled type kind {}", kind);
    } else {
        auto type_iter = json.find(TYPE);
        if (type_iter != json.end() &&
            type_iter->get<std::string>() == "UNKNOWN") {
            return read_type_unknown(json);
        } else {
            SPDLOG_CRITICAL("Could not find {} in json", TYPE);
        }
    }

    panic("{}", json);
}

//------------------------------------------------------------------------------
Param read_param(const nln::json& json) {

    auto name = json[NAME].get<std::string>();
    auto type = read_type(json[TYPE]);
    auto index = json[INDEX].get<uint64_t>();

    return Param(std::move(name), std::move(type), index);
}

//------------------------------------------------------------------------------
std::vector<std::string> read_attrs(const nln::json& json) {
    auto attrs = std::vector<std::string>();
    for (const auto& i : json[ATTRIBUTES]) {
        attrs.push_back(i.get<std::string>());
    }
    return attrs;
}

//------------------------------------------------------------------------------
std::string read_comment(const nln::json& json) {
    std::string comment;
    auto comment_ = json.find(COMMENT);
    if (comment_ != json.end()) {
        comment = base64::decode(comment_->get<std::string>());
    }

    return comment;
}

//------------------------------------------------------------------------------
NodeTypePtr read_type_function_proto(const nln::json& json) {
    auto return_type = read_type(json[RETURN]);

    auto params = std::vector<NodeTypePtr>();
    for (const auto& i : json[PARAMS]) {
        auto p = read_param(i);
        params.push_back(std::move(p.type));
    }

    return NodeFunctionProtoType::n(
        std::move(return_type), std::move(params),
        json[TYPE].get<std::string>(),
        json[FUNCTION_POINTER_TYPEDEF_L].get<NodeId>());
}

//------------------------------------------------------------------------------
NodePtr read_function(const TranslationUnit::Ptr& tu, const nln::json& json) {
    // ignore for the moment
    auto attrs = read_attrs(json);

    auto qualified_name = json[QUALIFIED_NAME].get<std::string>();

    auto short_name = json[SHORT_NAME].get<std::string>();
    auto id = json[ID].get<Id>();
    auto return_type = read_type(json[RETURN]);

    auto params = std::vector<Param>();
    for (const auto& i : json[PARAMS]) {
        params.push_back(read_param(i));
    }

    // Namespaces
    std::vector<NodeId> namespaces;
    for (const auto& ns : json[NAMESPACES]) {
        namespaces.push_back(ns);
    }

    auto comment = read_comment(json);

    auto result = NodeFunction::n(qualified_name, id, attrs, short_name,
                                  std::move(return_type), std::move(params),
                                  qualified_name, std::move(comment));
    result->namespaces = namespaces;

    return result;
}

//------------------------------------------------------------------------------
NodeMethod read_method(const nln::json& json) {

    auto qualified_name = json[QUALIFIED_NAME].get<std::string>();
    auto attrs = read_attrs(json);

    auto short_name = json[SHORT_NAME].get<std::string>();
    auto id = json[ID].get<Id>();
    auto static_ = json[STATIC].get<bool>();
    auto constructor = json[CONSTRUCTOR].get<bool>();
    auto destructor = json[DESTRUCTOR].get<bool>();
    auto copy_constructor = json[COPY_CONSTRUCTOR].get<bool>();
    auto return_type = read_type(json[RETURN]);
    auto const_ = json[CONST].get<bool>();
    auto comment = read_comment(json);

    auto params = std::vector<Param>();
    for (const auto& i : json[PARAMS]) {
        params.push_back(read_param(i));
    }

    return NodeMethod(qualified_name, id, attrs, short_name,
                      std::move(return_type), std::move(params), static_,
                      constructor, copy_constructor, destructor, const_,
                      std::move(comment));
}

//------------------------------------------------------------------------------
Field read_field(const nln::json& json) {
    return Field{
        std::move(json[NAME].get<std::string>()),
        std::move(read_type(json[TYPE])),
    };
}

//------------------------------------------------------------------------------
NodePtr read_record(const TranslationUnit::Ptr& tu, const nln::json& json) {
    // Dont ignore these
    Id id = json[ID].get<Id>();
    auto size = json[SIZE].get<uint64_t>();
    auto align = json[ALIGN].get<uint64_t>();
    auto qual_name = json[NAME].get<std::string>();
    auto name = json[SHORT_NAME].get<std::string>();

    // Find if abstract
    auto abstract = false;
    auto abstract_a = json.find(ABSTRACT);
    if (abstract_a != json.end()) {
        abstract = abstract_a->get<bool>();
    }

    // Find if trivially_copyable
    auto trivially_copyable = false;
    auto trivially_copyable_a = json.find(TRIVIALLY_COPYABLE);
    if (trivially_copyable_a != json.end()) {
        trivially_copyable = trivially_copyable_a->get<bool>();
    }

    // Override the name with an alias if one is provided
    auto alias = json.find(ALIAS);
    if (alias != json.end()) {
        name = alias->get<std::string>();
    }

    // Namespaces
    std::vector<NodeId> namespaces;
    for (const auto& ns : json[NAMESPACES]) {
        namespaces.push_back(ns);
    }

    // Pull out the attributes
    std::vector<std::string> attrs = read_attrs(json);

    // Read the comment
    auto comment = read_comment(json);

    // Instantiate the translation unit
    auto result =
        NodeRecord::n(tu, qual_name, id, attrs, size, align, name, namespaces,
                      abstract, trivially_copyable, std::move(comment));

    // Pull out the methods
    for (const auto& i : json[METHODS]) {
        result->methods.push_back(read_method(i));
    }

    // Pull out the fields
    for (const auto& i : json[FIELDS]) {
        result->fields.push_back(std::move(read_field(i)));
    }

    // Return the result
    return result;
}

struct sort_enum_vars {
    bool operator()(const std::pair<std::string, std::string>& a,
                    const std::pair<std::string, std::string>& b) {
        return atoi(a.second.c_str()) < atoi(b.second.c_str());
    }
};

//------------------------------------------------------------------------------
NodePtr read_enum(const TranslationUnit::Ptr& tu, const nln::json& json) {
    Id id = json[ID].get<Id>();
    auto size = json[SIZE].get<uint64_t>();
    auto align = json[ALIGN].get<uint64_t>();
    auto name = json[NAME].get<std::string>();
    auto short_name = json[SHORT_NAME].get<std::string>();

    std::vector<NodeId> namespaces;
    for (const auto& ns : json[NAMESPACES]) {
        namespaces.push_back(ns);
    }

    std::vector<std::string> attrs = read_attrs(json);

    // Pull out the variants
    std::vector<std::pair<std::string, std::string>> variants;
    for (const auto& i : json[VARIANTS].items()) {
        variants.push_back(std::make_pair(
            i.key(),
            i.value().get<std::string>() // TODO LT: Check with anders, can
                                         // value be long int?
            ));
    }

    std::sort(variants.begin(), variants.end(), sort_enum_vars{});

    auto comment = read_comment(json);

    // Instantiate the translation unit
    auto result = NodeEnum::n(tu, name, name, short_name, id, attrs, variants,
                              size, align, namespaces, std::move(comment));

    // Return the result
    return result;
}

//------------------------------------------------------------------------------
NodePtr read_var(const TranslationUnit::Ptr& tu, const nln::json& json) {
    // Ignore these for the moment
    std::vector<std::string> _attrs;

    // Dont ignore these
    auto name = json[SHORT_NAME].get<std::string>();
    // std::cout << "read type" << std::endl;
    auto type = read_type(json[TYPE]);

    // Instantiate the translation unit
    auto result = NodeVarDeclExpr::n(type, name);

    // Return the result
    return result;
}

//------------------------------------------------------------------------------
NodePtr read_namespace(const TranslationUnit::Ptr& tu, const nln::json& json) {
    // Ignore these for the moment
    std::vector<std::string> _attrs;

    // Dont ignore these
    Id id = json[ID].get<Id>();
    auto name = json[NAME].get<std::string>();
    auto short_name = json[SHORT_NAME].get<std::string>();
    auto alias = json[ALIAS].get<std::string>();
    auto collapse = json[COLLAPSE].get<bool>();

    auto result = NodeNamespace::n(name, id, short_name, alias, collapse);

    // Return the result
    return result;
}

//------------------------------------------------------------------------------
NodePtr read_function_pointer_typedef(const TranslationUnit::Ptr& tu,
                                      const nln::json& json) {
    // Ignore these for the moment
    std::vector<std::string> _attrs;

    // Dont ignore these
    Id id = json[ID].get<Id>();
    auto name = json[NAME].get<std::string>();
    auto alias = json[ALIAS].get<std::string>();

    std::vector<NodeId> namespaces;
    for (const auto& ns : json[NAMESPACES]) {
        namespaces.push_back(ns);
    }

    auto comment = read_comment(json);

    auto return_type = read_type(json[RETURN]);

    auto params = std::vector<Param>();
    for (const auto& i : json[PARAMS]) {
        params.push_back(read_param(i));
    }

    auto result = NodeFunctionPointerTypedef::n(
        tu, name, id, alias, namespaces, std::move(comment),
        std::move(return_type), std::move(params));

    // Return the result
    return result;
}

//------------------------------------------------------------------------------
NodePtr read_node(const TranslationUnit::Ptr& tu, const nln::json& json) {
    auto kind = json[KIND].get<std::string>();

    if (kind == RECORD_C) {
        return read_record(tu, json);
    } else if (kind == ENUM_C) {
        return read_enum(tu, json);
    } else if (kind == FUNCTION_C) {
        return read_function(tu, json);
    } else if (kind == NAMESPACE_C) {
        return read_namespace(tu, json);
    } else if (kind == VAR_C) {
        return read_var(tu, json);
    } else if (kind == FUNCTION_POINTER_TYPEDEF_C) {
        return read_function_pointer_typedef(tu, json);
    }

    panic("Unhandled node kind {}", kind);

    // TODO LT: Fix the return type
}

//------------------------------------------------------------------------------
TranslationUnit::Ptr read_translation_unit(const nln::json& json) {
    // Read the translation unit
    auto filename = json[FILENAME].get<std::string>();

    // Instantiate the translation unit
    auto result = TranslationUnit::new_(filename);

    // Loop over the source includes
    for (auto& i : json[SOURCE_INCLUDES]) {
        result->source_includes.insert(i.get<std::string>());
    }

    // Loop over the include directories
    for (auto& i : json[INCLUDE_PATHS]) {
        result->include_paths.push_back(i.get<std::string>());
    }

    // Parse the elements of the translation unit
    for (const auto& i : json[DECLS]) {
        result->decls.push_back(read_node(result, i));
    }

    // Return the result
    return result;
}

//------------------------------------------------------------------------------
Root json(const std::string& input_directory) {

    std::vector<TranslationUnit::Ptr> tus;

    for (const auto& p : fs::directory_iterator(input_directory)) {
        if (p.path().extension() == ".json") {
            // Open the json file
            std::ifstream input_file;
            input_file.open(p.path());

            // Convert the input stream into json structures
            nln::json json;
            input_file >> json;

            // Later this can be a loop taking in multiple translation units
            tus.push_back(read_translation_unit(json));
        }
    }

    return Root(std::move(tus));
}

} // namespace read
} // namespace cppmm
