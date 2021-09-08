#include <obyte.hpp>
#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace obyte {

struct Foo {
    using BoundType = ::obyte::Foo;
} CPPMM_OPAQUEBYTES;


}

}
