#pragma once
#include <imf_imagechannel_.h>


#include <OpenEXR/ImfImageChannel.h>
#include <cppmm_bind.hpp>











inline Imf_2_5::ImageChannel const & to_cpp_ref(
    Imf_2_5_ImageChannel const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::ImageChannel const * >(rhs));
}


inline Imf_2_5::ImageChannel & to_cpp_ref(
    Imf_2_5_ImageChannel * rhs)
{
    return *(reinterpret_cast<Imf_2_5::ImageChannel * >(rhs));
}


inline Imf_2_5::ImageChannel const * to_cpp(
    Imf_2_5_ImageChannel const * rhs)
{
    return reinterpret_cast<Imf_2_5::ImageChannel const * >(rhs);
}


inline Imf_2_5::ImageChannel * to_cpp(
    Imf_2_5_ImageChannel * rhs)
{
    return reinterpret_cast<Imf_2_5::ImageChannel * >(rhs);
}


inline Imf_2_5_ImageChannel const * to_c(
    Imf_2_5::ImageChannel const & rhs)
{
    return reinterpret_cast<Imf_2_5_ImageChannel const * >(&(rhs));
}


inline Imf_2_5_ImageChannel const * to_c(
    Imf_2_5::ImageChannel const * rhs)
{
    return reinterpret_cast<Imf_2_5_ImageChannel const * >(rhs);
}


inline Imf_2_5_ImageChannel * to_c(
    Imf_2_5::ImageChannel & rhs)
{
    return reinterpret_cast<Imf_2_5_ImageChannel * >(&(rhs));
}


inline Imf_2_5_ImageChannel * to_c(
    Imf_2_5::ImageChannel * rhs)
{
    return reinterpret_cast<Imf_2_5_ImageChannel * >(rhs);
}
