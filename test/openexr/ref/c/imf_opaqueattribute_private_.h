#pragma once
#include <imf_opaqueattribute_.h>


#include <OpenEXR/ImfOpaqueAttribute.h>
#include <cppmm_bind.hpp>










inline Imf_2_5::OpaqueAttribute const & to_cpp_ref(
    Imf_2_5_OpaqueAttribute const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::OpaqueAttribute const * >(rhs));
}


inline Imf_2_5::OpaqueAttribute & to_cpp_ref(
    Imf_2_5_OpaqueAttribute * rhs)
{
    return *(reinterpret_cast<Imf_2_5::OpaqueAttribute * >(rhs));
}


inline Imf_2_5::OpaqueAttribute const * to_cpp(
    Imf_2_5_OpaqueAttribute const * rhs)
{
    return reinterpret_cast<Imf_2_5::OpaqueAttribute const * >(rhs);
}


inline Imf_2_5::OpaqueAttribute * to_cpp(
    Imf_2_5_OpaqueAttribute * rhs)
{
    return reinterpret_cast<Imf_2_5::OpaqueAttribute * >(rhs);
}


inline Imf_2_5_OpaqueAttribute const * to_c(
    Imf_2_5::OpaqueAttribute const & rhs)
{
    return reinterpret_cast<Imf_2_5_OpaqueAttribute const * >(&(rhs));
}


inline Imf_2_5_OpaqueAttribute const * to_c(
    Imf_2_5::OpaqueAttribute const * rhs)
{
    return reinterpret_cast<Imf_2_5_OpaqueAttribute const * >(rhs);
}


inline Imf_2_5_OpaqueAttribute * to_c(
    Imf_2_5::OpaqueAttribute & rhs)
{
    return reinterpret_cast<Imf_2_5_OpaqueAttribute * >(&(rhs));
}


inline Imf_2_5_OpaqueAttribute * to_c(
    Imf_2_5::OpaqueAttribute * rhs)
{
    return reinterpret_cast<Imf_2_5_OpaqueAttribute * >(rhs);
}


inline Imf_2_5_OpaqueAttribute to_c_copy(
    Imf_2_5::OpaqueAttribute const & rhs)
{
    Imf_2_5_OpaqueAttribute result;
    Imf_2_5_OpaqueAttribute_OpaqueAttribute_1(&(result), reinterpret_cast<Imf_2_5_OpaqueAttribute const * >(&(rhs)));
    return result;
}
