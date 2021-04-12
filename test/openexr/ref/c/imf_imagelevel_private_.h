#pragma once
#include <imf_imagelevel_.h>


#include <OpenEXR/ImfImageLevel.h>
#include <cppmm_bind.hpp>




inline Imf_2_5::ImageLevel const & to_cpp_ref(
    Imf_2_5_ImageLevel const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::ImageLevel const * >(rhs));
}


inline Imf_2_5::ImageLevel & to_cpp_ref(
    Imf_2_5_ImageLevel * rhs)
{
    return *(reinterpret_cast<Imf_2_5::ImageLevel * >(rhs));
}


inline Imf_2_5::ImageLevel const * to_cpp(
    Imf_2_5_ImageLevel const * rhs)
{
    return reinterpret_cast<Imf_2_5::ImageLevel const * >(rhs);
}


inline Imf_2_5::ImageLevel * to_cpp(
    Imf_2_5_ImageLevel * rhs)
{
    return reinterpret_cast<Imf_2_5::ImageLevel * >(rhs);
}


inline Imf_2_5_ImageLevel const * to_c(
    Imf_2_5::ImageLevel const & rhs)
{
    return reinterpret_cast<Imf_2_5_ImageLevel const * >(&(rhs));
}


inline Imf_2_5_ImageLevel const * to_c(
    Imf_2_5::ImageLevel const * rhs)
{
    return reinterpret_cast<Imf_2_5_ImageLevel const * >(rhs);
}


inline Imf_2_5_ImageLevel * to_c(
    Imf_2_5::ImageLevel & rhs)
{
    return reinterpret_cast<Imf_2_5_ImageLevel * >(&(rhs));
}


inline Imf_2_5_ImageLevel * to_c(
    Imf_2_5::ImageLevel * rhs)
{
    return reinterpret_cast<Imf_2_5_ImageLevel * >(rhs);
}
