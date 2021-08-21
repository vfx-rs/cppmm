#include "c-specs_private.h"

#include "std_string_private.h"
#include <new>

#include <stdexcept>

TMP_SPECS_CPPMM_API unsigned int specs__Attribute_int__value(
    specs_IntAttribute_t * this_
    , int const * * return_)
{
    try {
        *(return_) = &((to_cpp(this_)) -> value());
        return 0;
    } catch (std::exception& e) {
        TLG_EXCEPTION_STRING = e.what();
        return -1;
    }
}

TMP_SPECS_CPPMM_API unsigned int specs__Attribute_int__do_something(
    int * v)
{
    try {
        specs::Attribute<int>::do_something(*(v));
        return 0;
    } catch (std::exception& e) {
        TLG_EXCEPTION_STRING = e.what();
        return -1;
    }
}

TMP_SPECS_CPPMM_API unsigned int specs__Attribute_int__ctor(
    specs_IntAttribute_t * * this_)
{
    try {
        to_c(this_, new specs::Attribute<int>());
        return 0;
    } catch (std::exception& e) {
        TLG_EXCEPTION_STRING = e.what();
        return -1;
    }
}

TMP_SPECS_CPPMM_API unsigned int specs__Attribute_float__value(
    specs_FloatAttribute_t * this_
    , float const * * return_)
{
    try {
        *(return_) = &((to_cpp(this_)) -> value());
        return 0;
    } catch (std::exception& e) {
        TLG_EXCEPTION_STRING = e.what();
        return -1;
    }
}

TMP_SPECS_CPPMM_API unsigned int specs__Attribute_float__do_something(
    float * v)
{
    try {
        specs::Attribute<float>::do_something(*(v));
        return 0;
    } catch (std::exception& e) {
        TLG_EXCEPTION_STRING = e.what();
        return -1;
    }
}

TMP_SPECS_CPPMM_API unsigned int specs__Attribute_float__ctor(
    specs_FloatAttribute_t * * this_)
{
    try {
        to_c(this_, new specs::Attribute<float>());
        return 0;
    } catch (std::exception& e) {
        TLG_EXCEPTION_STRING = e.what();
        return -1;
    }
}

TMP_SPECS_CPPMM_API unsigned int specs__Attribute_std__string__value(
    specs_StringAttribute_t * this_
    , std_string_t const * * return_)
{
    try {
        to_c(return_, (to_cpp(this_)) -> value());
        return 0;
    } catch (std::exception& e) {
        TLG_EXCEPTION_STRING = e.what();
        return -1;
    }
}

TMP_SPECS_CPPMM_API unsigned int specs__Attribute_std__string__do_something(
    std_string_t * v)
{
    try {
        specs::Attribute<std::string>::do_something(to_cpp_ref(v));
        return 0;
    } catch (std::exception& e) {
        TLG_EXCEPTION_STRING = e.what();
        return -1;
    }
}

TMP_SPECS_CPPMM_API unsigned int specs__Attribute_std__string__ctor(
    specs_StringAttribute_t * * this_)
{
    try {
        to_c(this_, new specs::Attribute<std::string>());
        return 0;
    } catch (std::exception& e) {
        TLG_EXCEPTION_STRING = e.what();
        return -1;
    }
}

TMP_SPECS_CPPMM_API unsigned int specs__Attribute_std__string__dtor(
    specs_StringAttribute_t * this_)
{
    try {
        delete to_cpp(this_);
        return 0;
    } catch (std::exception& e) {
        TLG_EXCEPTION_STRING = e.what();
        return -1;
    }
}

TMP_SPECS_CPPMM_API unsigned int specs__Specs_findAttribute_int(
    specs_Specs_t * this_
    , specs_IntAttribute_t * * return_
    , char const * name)
{
    try {
        to_c(return_, (to_cpp(this_)) -> findAttribute<specs::Attribute<int>>(name));
        return 0;
    } catch (std::exception& e) {
        TLG_EXCEPTION_STRING = e.what();
        return -1;
    }
}

TMP_SPECS_CPPMM_API unsigned int specs__Specs_findAttribute_float(
    specs_Specs_t * this_
    , specs_FloatAttribute_t * * return_
    , char const * name)
{
    try {
        to_c(return_, (to_cpp(this_)) -> findAttribute<specs::Attribute<float>>(name));
        return 0;
    } catch (std::exception& e) {
        TLG_EXCEPTION_STRING = e.what();
        return -1;
    }
}

TMP_SPECS_CPPMM_API unsigned int specs__Specs_findAttribute_int_const(
    specs_Specs_t const * this_
    , specs_IntAttribute_t const * * return_
    , char const * name)
{
    try {
        to_c(return_, (to_cpp(this_)) -> findAttribute<specs::Attribute<int>>(name));
        return 0;
    } catch (std::exception& e) {
        TLG_EXCEPTION_STRING = e.what();
        return -1;
    }
}

TMP_SPECS_CPPMM_API unsigned int specs__Specs_findAttribute_float_const(
    specs_Specs_t const * this_
    , specs_FloatAttribute_t const * * return_
    , char const * name)
{
    try {
        to_c(return_, (to_cpp(this_)) -> findAttribute<specs::Attribute<float>>(name));
        return 0;
    } catch (std::exception& e) {
        TLG_EXCEPTION_STRING = e.what();
        return -1;
    }
}

