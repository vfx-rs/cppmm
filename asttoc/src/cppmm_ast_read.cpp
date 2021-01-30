
//------------------------------------------------------------------------------
// vfx-rs
//------------------------------------------------------------------------------
#include "cppmm_ast_read.hpp"
#include "json.hh"

namespace nln = nlohmann;

//------------------------------------------------------------------------------
NodeTranslationUnit read_translation_unit() {
}

//------------------------------------------------------------------------------
Root read_json(std::istream & input) {
    std::vector<NodePtr> nodes;

    nln::json j;
    input >> j;

    return Root(std::move(nodes));
}
