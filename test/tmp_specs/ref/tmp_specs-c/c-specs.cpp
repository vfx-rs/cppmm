#include <c-specs_private.h>


#include <stdexcept>

unsigned int specs__Attribute_int__value(
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
unsigned int specs__Attribute_float__value(
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
unsigned int specs__Specs_findAttribute_int(
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
unsigned int specs__Specs_findAttribute_float(
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
unsigned int specs__Specs_findAttribute_int_const(
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
unsigned int specs__Specs_findAttribute_float_const(
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
