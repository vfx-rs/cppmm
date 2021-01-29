#include <string>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

class string {
public:
    using BoundType = ::std::string;
} CPPMM_OPAQUEPTR;

} // namespace cppmm_bind
