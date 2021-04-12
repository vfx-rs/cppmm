#pragma once
#include <imf_rgba_.h>


#include <OpenEXR/ImfRgba.h>
#include <cppmm_bind.hpp>


inline Imf_2_5::Rgba const & to_cpp_ref(
    Imf_2_5_Rgba const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::Rgba const * >(rhs));
}


inline Imf_2_5::Rgba & to_cpp_ref(
    Imf_2_5_Rgba * rhs)
{
    return *(reinterpret_cast<Imf_2_5::Rgba * >(rhs));
}


inline Imf_2_5::Rgba const * to_cpp(
    Imf_2_5_Rgba const * rhs)
{
    return reinterpret_cast<Imf_2_5::Rgba const * >(rhs);
}


inline Imf_2_5::Rgba * to_cpp(
    Imf_2_5_Rgba * rhs)
{
    return reinterpret_cast<Imf_2_5::Rgba * >(rhs);
}


inline Imf_2_5_Rgba const * to_c(
    Imf_2_5::Rgba const & rhs)
{
    return reinterpret_cast<Imf_2_5_Rgba const * >(&(rhs));
}


inline Imf_2_5_Rgba const * to_c(
    Imf_2_5::Rgba const * rhs)
{
    return reinterpret_cast<Imf_2_5_Rgba const * >(rhs);
}


inline Imf_2_5_Rgba * to_c(
    Imf_2_5::Rgba & rhs)
{
    return reinterpret_cast<Imf_2_5_Rgba * >(&(rhs));
}


inline Imf_2_5_Rgba * to_c(
    Imf_2_5::Rgba * rhs)
{
    return reinterpret_cast<Imf_2_5_Rgba * >(rhs);
}
