#include <prop.hpp>

#include <cppmm_bind.hpp>
namespace cppmm_bind {

namespace prop {

struct Bar {
    using BoundType = ::prop::Bar;

} CPPMM_OPAQUEPTR;

struct Foo {
    using BoundType = ::prop::Foo;
    static void bum();
} CPPMM_PROPERTIES(a; b; bar; u);

uint64_t fuz(uint64_t& a, uint64_t* b, uint64_t c);

} // namespace prop

} // namespace cppmm_bind
