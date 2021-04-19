#include <comments.hpp>
#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace comments {

struct Class {
    using BoundType = ::comments::Class;
    void method() {}
};

void function() {}

} // namespace comments

} // namespace cppmm_bind
