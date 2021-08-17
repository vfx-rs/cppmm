#include <foo.hpp>

// CPPMM_ macro definitions etc automatically inserted in this virtual header
#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace foo {

struct Foo {
    using BoundType = ::foo::Foo;

    Foo();
    ~Foo();

    static std::unique_ptr<::foo::Foo> create();
};

} // namespace foo

} // namespace cppmm_bind
