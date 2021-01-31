
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
    const char * ID = "id";
    const char * KIND = "kind";
    const char * NAME = "name";
    const char * SIZE = "size";

    struct NodeBasics {
        std::string name;
        NodeId id;
    };
}

//------------------------------------------------------------------------------
NodeBasics read_node_basics(const nln::json & json) {
    NodeBasics result;
    
    // TODO LT: Better error handling
    result.name = json[NAME].get<std::string>();
    result.id = json[ID].get<uint64_t>();

    return result;
}

NodePtr read_node(const nln::json & json);

//------------------------------------------------------------------------------
NodePtr read_record(const nln::json & json) {
    // Get the very basics
    auto basics = read_node_basics(json);

    // Ignore these for the moment
    std::vector<std::string> _attrs;
    RecordKind _record_kind;

    // Dont ignore these
    uint64_t size = json[SIZE].get<uint64_t>();
    uint64_t align = json[ALIGN].get<uint64_t>();

    // Instantiate the translation unit
    auto result =\
        std::unique_ptr<NodeRecord>(
            new NodeRecord(basics.name, basics.id, _attrs, _record_kind, size,
                           align));

    // Parse the elements of the translation unit
    /*
    std::vector<NodePtr> children;
    for (const auto & i : json ){
        children.push_back(read_node(i));
    }
    */

    // Return the result
    return result;
}

//------------------------------------------------------------------------------
NodePtr read_translation_unit(const nln::json & json) {
    // Get the very basics
    auto basics = read_node_basics(json);

    // Instantiate the translation unit
    auto result =\
        std::unique_ptr<TranslationUnit>(
            new TranslationUnit(basics.name, basics.id));

    // Parse the elements of the translation unit
    std::vector<NodePtr> children;
    for (const auto & i : json ){
        children.push_back(read_node(i));
    }

    // transfer the children over to the result
    result->children = std::move(children);

    // Return the result
    return result;
}

//------------------------------------------------------------------------------
NodePtr read_node(const nln::json & json) {
    auto kind = json[KIND].get<uint64_t>();

    if (kind < static_cast<uint64_t>(NodeKind::Sentinal)) {
        switch (static_cast<NodeKind>(kind)) {
            case NodeKind::TranslationUnit:
                return read_translation_unit(json);
            case NodeKind::Record:
                return read_record(json);
            default:
                break;
        }
    }

    assert("Have hit an node type that we can't handle");

    // TODO LT: Fix the return type
}

//------------------------------------------------------------------------------
Root read_json(std::istream & input) {
    std::vector<NodePtr> nodes;

    // Convert the input stream into json structures
    nln::json json;
    input >> json;

    // Read each node
    for (const auto & i : json ){
        nodes.push_back(read_node(i));
    }

    return Root(std::move(nodes));
}

} // namespace cppmm
