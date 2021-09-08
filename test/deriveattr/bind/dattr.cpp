#include <dattr.hpp>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace foo {

struct Foo { 
    using BoundType = ::foo::Foo;
    int bar; 
} CPPMM_VALUETYPE CPPMM_DERIVE("Copy, Clone, Debug, PartialEq, Eq, PartialOrd, Ord, Hash");

}

}

