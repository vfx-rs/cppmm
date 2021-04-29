#include <c-specs_private.h>


int const * specs__Attribute_int__value(
    specs_IntAttribute_t * this_)
{
    return &((to_cpp(this_)) -> value());
}
float const * specs__Attribute_float__value(
    specs_FloatAttribute_t * this_)
{
    return &((to_cpp(this_)) -> value());
}
specs_IntAttribute_t * specs__Specs_findAttribute_int(
    specs_Specs_t * this_
    , char const * name)
{
    return to_c((to_cpp(this_)) -> findAttribute<specs::Attribute<int>>(name));
}
specs_FloatAttribute_t * specs__Specs_findAttribute_float(
    specs_Specs_t * this_
    , char const * name)
{
    return to_c((to_cpp(this_)) -> findAttribute<specs::Attribute<float>>(name));
}
specs_IntAttribute_t const * specs__Specs_findAttribute_int_const(
    specs_Specs_t const * this_
    , char const * name)
{
    return to_c((to_cpp(this_)) -> findAttribute<specs::Attribute<int>>(name));
}
specs_FloatAttribute_t const * specs__Specs_findAttribute_float_const(
    specs_Specs_t const * this_
    , char const * name)
{
    return to_c((to_cpp(this_)) -> findAttribute<specs::Attribute<float>>(name));
}
