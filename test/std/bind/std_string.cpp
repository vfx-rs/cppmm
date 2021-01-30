#include <string>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

class basic_string {
public:
    using BoundType = ::std::string;
} CPPMM_OPAQUEBYTES;

std::string inst;

} // namespace cppmm_bind
