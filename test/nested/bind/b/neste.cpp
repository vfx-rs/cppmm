#include <b/neste.hpp>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace nest {

struct NestBE {
    using BoundType = ::nest::NestBE;

    int b;

    void do_something() {}
} CPPMM_VALUETYPE;

} // namespace nest

} // namespace cppmm_bind
