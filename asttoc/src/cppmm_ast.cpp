#include "cppmm_ast.hpp"

namespace cppmm {

std::map<unsigned int, std::string> EXCEPTION_MAP;

std::map<NodeId, std::shared_ptr<NodeRecord>> RECORD_MAP;
std::map<NodeId, std::shared_ptr<NodeType>> TYPE_MAP;
} // namespace cppmm
