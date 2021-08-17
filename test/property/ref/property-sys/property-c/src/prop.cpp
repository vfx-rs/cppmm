#include "prop_private.h"


#include <stdexcept>

unsigned int prop__Foo_get_a(
    prop_Foo_t const * this_
    , int const * * return_)
{
        *(return_) = &((to_cpp(this_))->a);
        return 0;
}

unsigned int prop__Foo_set_a(
    prop_Foo_t * this_
    , int const * value)
{
        (to_cpp(this_))->a = *(value);
        return 0;
}

unsigned int prop__Foo_get_b(
    prop_Foo_t const * this_
    , float const * * return_)
{
        *(return_) = &((to_cpp(this_))->b);
        return 0;
}

unsigned int prop__Foo_set_b(
    prop_Foo_t * this_
    , float const * value)
{
        (to_cpp(this_))->b = *(value);
        return 0;
}

unsigned int prop__Foo_get_bar(
    prop_Foo_t const * this_
    , prop_Bar_t const * * return_)
{
        to_c(return_, (to_cpp(this_))->bar);
        return 0;
}

unsigned int prop__Foo_set_bar(
    prop_Foo_t * this_
    , prop_Bar_t const * value)
{
        (to_cpp(this_))->bar = to_cpp_ref(value);
        return 0;
}

