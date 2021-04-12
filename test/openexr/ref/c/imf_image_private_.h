#pragma once
#include <imf_image_.h>


#include <OpenEXR/ImfImage.h>
#include <cppmm_bind.hpp>


















inline Imf_2_5::Image const & to_cpp_ref(
    Imf_2_5_Image const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::Image const * >(rhs));
}


inline Imf_2_5::Image & to_cpp_ref(
    Imf_2_5_Image * rhs)
{
    return *(reinterpret_cast<Imf_2_5::Image * >(rhs));
}


inline Imf_2_5::Image const * to_cpp(
    Imf_2_5_Image const * rhs)
{
    return reinterpret_cast<Imf_2_5::Image const * >(rhs);
}


inline Imf_2_5::Image * to_cpp(
    Imf_2_5_Image * rhs)
{
    return reinterpret_cast<Imf_2_5::Image * >(rhs);
}


inline Imf_2_5_Image const * to_c(
    Imf_2_5::Image const & rhs)
{
    return reinterpret_cast<Imf_2_5_Image const * >(&(rhs));
}


inline Imf_2_5_Image const * to_c(
    Imf_2_5::Image const * rhs)
{
    return reinterpret_cast<Imf_2_5_Image const * >(rhs);
}


inline Imf_2_5_Image * to_c(
    Imf_2_5::Image & rhs)
{
    return reinterpret_cast<Imf_2_5_Image * >(&(rhs));
}


inline Imf_2_5_Image * to_c(
    Imf_2_5::Image * rhs)
{
    return reinterpret_cast<Imf_2_5_Image * >(rhs);
}
