
//------------------------------------------------------------------------------
// vfx-rs
//------------------------------------------------------------------------------
#include "cppmm_ast_read.hpp"
#include "json.hh"

namespace nln = nlohmann;

namespace cppmm
{

namespace {
    const char * ALIGN = "align";
    const char * CHILDREN = "children";
    const char * DECLS = "decls";
    const char * FIELDS = "fields";
    const char * FILENAME = "filename";
    const char * ID = "id";
    const char * KIND = "kind";
    const char * METHODS = "methods";
    const char * NAME = "name";
    const char * SIZE = "size";
    const char * RECORD = "Record";

    struct NodeBasics {
        std::string name;
        NodeId id;
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
        std::unique_ptr<NodeRecord>(
            new NodeRecord(id, _attrs, _record_kind, size, align));

    // Pull out the fields
    std::vector<NodeMethod> methods;
    for (const auto & i : json[METHODS] ){
    }

    // Pull out the methods
    std::vector<Field> fields;
    for (const auto & i : json[FIELDS] ){
    }

    // Return the result
    return result;
}

//------------------------------------------------------------------------------
NodePtr read_node(const nln::json & json) {
    auto kind = json[KIND].get<std::string>();

    // TODO LT: Could kind be an enum instead of a string?
    if(kind == RECORD) {
        return read_record(json);
    }        

    assert("Have hit a node type that we can't handle");

    // TODO LT: Fix the return type
}

//------------------------------------------------------------------------------
TranslationUnit read_translation_unit(const nln::json & json) {
    // Get the very basics
    auto filename = json[FILENAME].get<std::string>();
    auto id = json[ID].get<Id>();

    // Instantiate the translation unit
    auto result = TranslationUnit(filename, id);

    // Parse the elements of the translation unit
    std::vector<NodePtr> decls;
    for (const auto & i : json[DECLS] ){
        decls.push_back(read_node(i));
    }
    result.decls = std::move(decls);

    // Return the result
    return result;
}

//------------------------------------------------------------------------------
Root read_json(std::istream & input) {
    std::vector<TranslationUnit> tus;

    // Convert the input stream into json structures
    nln::json json;
    input >> json;

    // Later this can be a loop taking in multiple translation units
    tus.push_back(read_translation_unit(json));

    return Root(std::move(tus));
}

} // namespace cppmm
