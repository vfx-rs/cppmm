#include <imf_opaqueattribute_private_.h>

#include <imf_attribute_private_.h>
#include <imf_io_private_.h>
#include <new>


char const * Imf_2_5_OpaqueAttribute_typeName(
    Imf_2_5_OpaqueAttribute const * this_)
{
    return (to_cpp(this_)) -> typeName();
}

Imf_2_5_Attribute * Imf_2_5_OpaqueAttribute_copy(
    Imf_2_5_OpaqueAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> copy());
}

void Imf_2_5_OpaqueAttribute_writeValueTo(
    Imf_2_5_OpaqueAttribute const * this_
    , Imf_2_5_OStream * os
    , int version)
{
    (to_cpp(this_)) -> writeValueTo(to_cpp_ref(os), version);
}

void Imf_2_5_OpaqueAttribute_readValueFrom(
    Imf_2_5_OpaqueAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version)
{
    (to_cpp(this_)) -> readValueFrom(to_cpp_ref(is), size, version);
}

void Imf_2_5_OpaqueAttribute_copyValueFrom(
    Imf_2_5_OpaqueAttribute * this_
    , Imf_2_5_Attribute const * other)
{
    (to_cpp(this_)) -> copyValueFrom(to_cpp_ref(other));
}

void Imf_2_5_OpaqueAttribute_OpaqueAttribute(
    Imf_2_5_OpaqueAttribute * this_
    , char const * typeName)
{
    new (this_) Imf_2_5::OpaqueAttribute(typeName);
}

void Imf_2_5_OpaqueAttribute_OpaqueAttribute_1(
    Imf_2_5_OpaqueAttribute * this_
    , Imf_2_5_OpaqueAttribute const * other)
{
    new (this_) Imf_2_5::OpaqueAttribute(to_cpp_ref(other));
}

void Imf_2_5_OpaqueAttribute_dtor(
    Imf_2_5_OpaqueAttribute * this_)
{
    (to_cpp(this_)) -> Imf_2_5::OpaqueAttribute::~OpaqueAttribute();
}
