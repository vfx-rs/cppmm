#include <OpenEXR/half.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

class half {
public:
    using BoundType = ::half;
} CPPMM_OPAQUEBYTES;

} // namespace cppmm_bind
