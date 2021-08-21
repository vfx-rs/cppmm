#include "uptr_private.h"

#include "foo_private.h"
#include <new>

#include <stdexcept>

UNIQUEPTR_CPPMM_API unsigned int std__unique_ptr_foo__Foo__ctor(
    std_FooPtr_t * * this_
    , foo_Foo_t * p)
{
        to_c(this_, new std::unique_ptr<foo::Foo>(to_cpp(p)));
        return 0;
}

UNIQUEPTR_CPPMM_API unsigned int std__unique_ptr_foo__Foo__dtor(
    std_FooPtr_t * this_)
{
        delete to_cpp(this_);
        return 0;
}

UNIQUEPTR_CPPMM_API unsigned int std__unique_ptr_foo__Foo__get(
    std_FooPtr_t const * this_
    , foo_Foo_t * * return_)
{
        to_c(return_, (to_cpp(this_)) -> get());
        return 0;
}

