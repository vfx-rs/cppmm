#include "hello.hpp"

namespace cppmm_bind {

namespace hello {

struct Hello {
    using BoundType = ::hello::Hello;
    void hello() const;
};

} // namespace hello

} // namespace cppmm_bind
