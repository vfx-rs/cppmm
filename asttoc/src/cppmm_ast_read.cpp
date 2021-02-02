
//------------------------------------------------------------------------------
// vfx-rs
//------------------------------------------------------------------------------
#include "cppmm_ast_read.hpp"
#include "json.hh"

#include <memory>
#include <iostream>

namespace nln = nlohmann;

namespace cppmm
{
namespace read
{

namespace {
    const char * ALIGN = "align";
    const char * CHILDREN = "children";
    const char * CONST = "const";
    const char * DECLS = "decls";
    const char * FIELDS = "fields";
    const char * FILENAME = "filename";
    const char * ID = "id";
    const char * INDEX = "index";
    const char * KIND = "kind";
    const char * METHODS = "methods";
    const char * NAME = "name";
    const char * QUALIFIED_NAME = "qualified_name";
    const char * SHORT_NAME = "short_name";
    const char * PARAMS = "params";
    const char * SIZE = "size";
    const char * STATIC = "static";
    const char * RECORD_C = "Record";
    const char * RECORD_L = "record";
    const char * TYPE = "type";
    const char * POINTEE = "pointee";
    const char * RETURN = "return";
}

//------------------------------------------------------------------------------
NodeTypePtr read_type(const nln::json & json);

//------------------------------------------------------------------------------
NodeTypePtr read_type_builtin(const nln::json & json) {
    return std::make_unique<NodeBuiltinType>(
            "",
            json[ID].get<Id>(),
            json[TYPE].get<std::string>(),
            json[CONST].get<bool>()
    );
}

//------------------------------------------------------------------------------
NodeTypePtr read_type_reference(const nln::json & json) {
    return std::make_unique<NodePointerType>(
            "",
            json[ID].get<Id>(),
            json[TYPE].get<std::string>(),
            PointerKind::Reference,
            read_type(json[POINTEE]),
            json[CONST].get<bool>()
    );
}

//------------------------------------------------------------------------------
NodeTypePtr read_type_record(const nln::json & json) {
    return std::make_unique<NodeRecordType>(
            "",
            json[ID].get<Id>(),
            json[TYPE].get<std::string>(),
            json[RECORD_L].get<NodeId>(),
            json[CONST].get<bool>()
    );
}

//------------------------------------------------------------------------------
NodeTypePtr read_type(const nln::json & json) {
    auto kind = json[KIND].get<std::string>();
    if(kind == "BuiltinType") {
        return read_type_builtin(json);
    } else if(kind == "RecordType") {
        return read_type_record(json);
    } else if(kind == "Reference") {
        return read_type_reference(json);
    }

    assert("Shouldn't get here"); // TODO LT: Clean this up
}

//------------------------------------------------------------------------------
Param read_param(const nln::json & json) {

    auto name = json[NAME].get<std::string>();
    auto type = read_type(json[TYPE]);
    auto index = json[INDEX].get<uint64_t>();

    return Param(std::move(name), std::move(type), index);
}

//------------------------------------------------------------------------------
NodeMethod read_method(const nln::json & json) {
    // ignore for the moment
    std::vector<std::string> _attrs;

    auto qualified_name = json[QUALIFIED_NAME].get<std::string>();
    auto short_name = json[SHORT_NAME].get<std::string>();
    auto id = json[ID].get<Id>();
    auto static_ = json[STATIC].get<bool>();
    auto return_type = read_type(json[RETURN]);

    auto params = std::vector<Param>();
    for(const auto & i: json[PARAMS]) {
        params.push_back(read_param(i));
    }

    return NodeMethod(qualified_name, id, _attrs, short_name,
                      std::move(return_type),
                      std::move(params), static_);
}

//------------------------------------------------------------------------------
Field read_field(const nln::json & json) {
    return Field {
        json[NAME].get<std::string>(),
        read_type(json[TYPE]),
    };
}

//------------------------------------------------------------------------------
NodePtr read_record(const nln::json & json) {
    // Ignore these for the moment
    std::vector<std::string> _attrs;
    RecordKind _record_kind;

    // Dont ignore these
    Id id = json[ID].get<Id>();
    uint64_t size = json[SIZE].get<uint64_t>();
    uint64_t align = json[ALIGN].get<uint64_t>();

    // Instantiate the translation unit
    auto result =\
        std::make_unique<NodeRecord>(id, _attrs, _record_kind, size, align);

    // Pull out the methods
    for (const auto & i : json[METHODS] ){
        result->methods.push_back(read_method(i));
    }

    // Pull out the fields
    for (const auto & i : json[FIELDS] ){
        result->fields.push_back(read_field(i));
    }

    // Return the result
    return result;
}

//------------------------------------------------------------------------------
NodePtr read_node(const nln::json & json) {
    auto kind = json[KIND].get<std::string>();

    // TODO LT: Could kind be an enum instead of a string?
    if(kind == RECORD_C) {
        return read_record(json);
    }        

    assert("Have hit a node type that we can't handle");

    // TODO LT: Fix the return type
}

//------------------------------------------------------------------------------
TranslationUnit read_translation_unit(const nln::json & json) {
    // Read the translation unit
    auto filename = json[FILENAME].get<std::string>();

    // Instantiate the translation unit
    auto result = TranslationUnit(filename);

    // Parse the elements of the translation unit
    for (const auto & i : json[DECLS] ){
        result.decls.push_back(read_node(i));
    }

    // Return the result
    return result;
}

//------------------------------------------------------------------------------
Root json(std::istream & input) {
    std::vector<TranslationUnit> tus;

    // Convert the input stream into json structures
    nln::json json;
    input >> json;

    // Later this can be a loop taking in multiple translation units
    tus.push_back(read_translation_unit(json));

    return Root(std::move(tus));
}

} // namespace read
} // namespace cppmm
