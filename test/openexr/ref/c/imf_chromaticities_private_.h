#pragma once
#include <imf_chromaticities_.h>


#include <OpenEXR/ImfChromaticities.h>
#include <cppmm_bind.hpp>


inline Imf_2_5::Chromaticities const & to_cpp_ref(
    Imf_2_5_Chromaticities const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::Chromaticities const * >(rhs));
}


inline Imf_2_5::Chromaticities & to_cpp_ref(
    Imf_2_5_Chromaticities * rhs)
{
    return *(reinterpret_cast<Imf_2_5::Chromaticities * >(rhs));
}


inline Imf_2_5::Chromaticities const * to_cpp(
    Imf_2_5_Chromaticities const * rhs)
{
    return reinterpret_cast<Imf_2_5::Chromaticities const * >(rhs);
}


inline Imf_2_5::Chromaticities * to_cpp(
    Imf_2_5_Chromaticities * rhs)
{
    return reinterpret_cast<Imf_2_5::Chromaticities * >(rhs);
}


inline Imf_2_5_Chromaticities const * to_c(
    Imf_2_5::Chromaticities const & rhs)
{
    return reinterpret_cast<Imf_2_5_Chromaticities const * >(&(rhs));
}


inline Imf_2_5_Chromaticities const * to_c(
    Imf_2_5::Chromaticities const * rhs)
{
    return reinterpret_cast<Imf_2_5_Chromaticities const * >(rhs);
}


inline Imf_2_5_Chromaticities * to_c(
    Imf_2_5::Chromaticities & rhs)
{
    return reinterpret_cast<Imf_2_5_Chromaticities * >(&(rhs));
}


inline Imf_2_5_Chromaticities * to_c(
    Imf_2_5::Chromaticities * rhs)
{
    return reinterpret_cast<Imf_2_5_Chromaticities * >(rhs);
}
