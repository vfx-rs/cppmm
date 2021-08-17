#include <prop.hpp>

#include <cppmm_bind.hpp>
namespace cppmm_bind {

namespace prop {

struct Bar {
    using BoundType = ::prop::Bar;

} CPPMM_OPAQUEPTR;

struct Foo {
    using BoundType = ::prop::Foo;
} CPPMM_PROPERTIES(a; b; bar);

} // namespace prop

} // namespace cppmm_bind
