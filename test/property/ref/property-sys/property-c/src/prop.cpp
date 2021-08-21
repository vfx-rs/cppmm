#include "prop_private.h"


#include <stdexcept>

PROPERTY_CPPMM_API unsigned int prop__Foo_bum()
{
    try {
        prop::Foo::bum();
        return 0;
    } catch (std::exception& e) {
        TLG_EXCEPTION_STRING = e.what();
        return -1;
    }
}

PROPERTY_CPPMM_API unsigned int prop__Foo_get_a(
    prop_Foo_t const * this_
    , int const * * return_)
{
        *(return_) = &((to_cpp(this_))->a);
        return 0;
}

PROPERTY_CPPMM_API unsigned int prop__Foo_set_a(
    prop_Foo_t * this_
    , int const * value)
{
        (to_cpp(this_))->a = *(value);
        return 0;
}

PROPERTY_CPPMM_API unsigned int prop__Foo_get_b(
    prop_Foo_t const * this_
    , float const * * return_)
{
        *(return_) = &((to_cpp(this_))->b);
        return 0;
}

PROPERTY_CPPMM_API unsigned int prop__Foo_set_b(
    prop_Foo_t * this_
    , float const * value)
{
        (to_cpp(this_))->b = *(value);
        return 0;
}

PROPERTY_CPPMM_API unsigned int prop__Foo_get_bar(
    prop_Foo_t const * this_
    , prop_Bar_t const * * return_)
{
        to_c(return_, (to_cpp(this_))->bar);
        return 0;
}

PROPERTY_CPPMM_API unsigned int prop__Foo_set_bar(
    prop_Foo_t * this_
    , prop_Bar_t const * value)
{
        (to_cpp(this_))->bar = to_cpp_ref(value);
        return 0;
}

PROPERTY_CPPMM_API unsigned int prop__Foo_get_u(
    prop_Foo_t const * this_
    , uint64_t const * * return_)
{
        *(return_) = &((to_cpp(this_))->u);
        return 0;
}

PROPERTY_CPPMM_API unsigned int prop__Foo_set_u(
    prop_Foo_t * this_
    , uint64_t const * value)
{
        (to_cpp(this_))->u = *(value);
        return 0;
}

PROPERTY_CPPMM_API unsigned int prop_fuz(
    uint64_t * return_
    , uint64_t * a
    , uint64_t * b
    , uint64_t c)
{
    try {
        *(return_) = prop::fuz(*(a), b, c);
        return 0;
    } catch (std::exception& e) {
        TLG_EXCEPTION_STRING = e.what();
        return -1;
    }
}

