#pragma once
#include <imf_flatimage_.h>


#include <OpenEXR/ImfFlatImage.h>
#include <cppmm_bind.hpp>



















inline Imf_2_5::FlatImage const & to_cpp_ref(
    Imf_2_5_FlatImage const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::FlatImage const * >(rhs));
}


inline Imf_2_5::FlatImage & to_cpp_ref(
    Imf_2_5_FlatImage * rhs)
{
    return *(reinterpret_cast<Imf_2_5::FlatImage * >(rhs));
}


inline Imf_2_5::FlatImage const * to_cpp(
    Imf_2_5_FlatImage const * rhs)
{
    return reinterpret_cast<Imf_2_5::FlatImage const * >(rhs);
}


inline Imf_2_5::FlatImage * to_cpp(
    Imf_2_5_FlatImage * rhs)
{
    return reinterpret_cast<Imf_2_5::FlatImage * >(rhs);
}


inline Imf_2_5_FlatImage const * to_c(
    Imf_2_5::FlatImage const & rhs)
{
    return reinterpret_cast<Imf_2_5_FlatImage const * >(&(rhs));
}


inline Imf_2_5_FlatImage const * to_c(
    Imf_2_5::FlatImage const * rhs)
{
    return reinterpret_cast<Imf_2_5_FlatImage const * >(rhs);
}


inline Imf_2_5_FlatImage * to_c(
    Imf_2_5::FlatImage & rhs)
{
    return reinterpret_cast<Imf_2_5_FlatImage * >(&(rhs));
}


inline Imf_2_5_FlatImage * to_c(
    Imf_2_5::FlatImage * rhs)
{
    return reinterpret_cast<Imf_2_5_FlatImage * >(rhs);
}
