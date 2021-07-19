#include "foo_private.h"

#include "uptr_private.h"
#include <new>

#include <stdexcept>

unsigned int foo__Foo_ctor(
    foo_Foo_t * * this_)
{
    try {
        to_c(this_, new foo::Foo());
        return 0;
    } catch (std::exception& e) {
        TLG_EXCEPTION_STRING = e.what();
        return -1;
    }
}

unsigned int foo__Foo_dtor(
    foo_Foo_t * this_)
{
    try {
        delete to_cpp(this_);
        return 0;
    } catch (std::exception& e) {
        TLG_EXCEPTION_STRING = e.what();
        return -1;
    }
}

unsigned int foo__Foo_create(
    std_FooPtr_t * * return_)
{
    try {
        new (*(return_)) std::unique_ptr<foo::Foo>(std::move(foo::Foo::create()));
        return 0;
    } catch (std::exception& e) {
        TLG_EXCEPTION_STRING = e.what();
        return -1;
    }
}

