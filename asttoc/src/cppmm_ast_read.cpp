
//------------------------------------------------------------------------------
// vfx-rs
//------------------------------------------------------------------------------
#include "cppmm_ast_read.hpp"
#include "json.hh"

namespace nln = nlohmann;

namespace cppmm
{

namespace {
    const char * KIND = "kind";
}

//------------------------------------------------------------------------------
NodePtr read_translation_unit(const nln::json & json) {
}

//------------------------------------------------------------------------------
NodePtr read_node(nln::json & json) {
    auto kind = json[KIND].get<uint64_t>();

    if (kind < static_cast<uint64_t>(NodeKind::Sentinal)) {
        switch (static_cast<NodeKind>(kind)) {
            case NodeKind::TranslationUnit:
                return read_translation_unit(json);
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
    nln::json j;
    input >> j;

    // Read each node
    for (const auto & j_node : j ){
        nodes.push_back(read_node(j));
    }

    return Root(std::move(nodes));
}

} // namespace cppmm
