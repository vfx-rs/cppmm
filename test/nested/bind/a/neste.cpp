#include <a/neste.hpp>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace nest {

struct NestAE {
    using BoundType = ::nest::NestAE;

    int a;

    void do_something() {}
} CPPMM_VALUETYPE;

} // namespace nest

} // namespace cppmm_bind
