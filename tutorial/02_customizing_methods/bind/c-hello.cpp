#include "hello.hpp"

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace hello {

struct Hello {
    using BoundType = ::hello::Hello;
    void hello(const char* msg) const CPPMM_RENAME(hello_string);
    void hello(const int msg) const CPPMM_RENAME(hello_int);
    void hello(const float msg) const CPPMM_RENAME(hello_float);
};

} // namespace hello

} // namespace cppmm_bind
