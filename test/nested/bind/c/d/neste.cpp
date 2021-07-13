#include <c/d/neste.hpp>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace nest {

struct NestCDE {
    using BoundType = ::nest::NestCDE;

    int cd;

    void do_something() {}
} CPPMM_VALUETYPE;

} // namespace nest

} // namespace cppmm_bind
