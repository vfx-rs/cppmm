#pragma once
#include <imf_lut_.h>


#include <OpenEXR/ImfLut.h>
#include <cppmm_bind.hpp>




inline Imf_2_5::HalfLut const & to_cpp_ref(
    Imf_2_5_HalfLut const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::HalfLut const * >(rhs));
}


inline Imf_2_5::HalfLut & to_cpp_ref(
    Imf_2_5_HalfLut * rhs)
{
    return *(reinterpret_cast<Imf_2_5::HalfLut * >(rhs));
}


inline Imf_2_5::HalfLut const * to_cpp(
    Imf_2_5_HalfLut const * rhs)
{
    return reinterpret_cast<Imf_2_5::HalfLut const * >(rhs);
}


inline Imf_2_5::HalfLut * to_cpp(
    Imf_2_5_HalfLut * rhs)
{
    return reinterpret_cast<Imf_2_5::HalfLut * >(rhs);
}


inline Imf_2_5_HalfLut const * to_c(
    Imf_2_5::HalfLut const & rhs)
{
    return reinterpret_cast<Imf_2_5_HalfLut const * >(&(rhs));
}


inline Imf_2_5_HalfLut const * to_c(
    Imf_2_5::HalfLut const * rhs)
{
    return reinterpret_cast<Imf_2_5_HalfLut const * >(rhs);
}


inline Imf_2_5_HalfLut * to_c(
    Imf_2_5::HalfLut & rhs)
{
    return reinterpret_cast<Imf_2_5_HalfLut * >(&(rhs));
}


inline Imf_2_5_HalfLut * to_c(
    Imf_2_5::HalfLut * rhs)
{
    return reinterpret_cast<Imf_2_5_HalfLut * >(rhs);
}




inline Imf_2_5::RgbaLut const & to_cpp_ref(
    Imf_2_5_RgbaLut const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::RgbaLut const * >(rhs));
}


inline Imf_2_5::RgbaLut & to_cpp_ref(
    Imf_2_5_RgbaLut * rhs)
{
    return *(reinterpret_cast<Imf_2_5::RgbaLut * >(rhs));
}


inline Imf_2_5::RgbaLut const * to_cpp(
    Imf_2_5_RgbaLut const * rhs)
{
    return reinterpret_cast<Imf_2_5::RgbaLut const * >(rhs);
}


inline Imf_2_5::RgbaLut * to_cpp(
    Imf_2_5_RgbaLut * rhs)
{
    return reinterpret_cast<Imf_2_5::RgbaLut * >(rhs);
}


inline Imf_2_5_RgbaLut const * to_c(
    Imf_2_5::RgbaLut const & rhs)
{
    return reinterpret_cast<Imf_2_5_RgbaLut const * >(&(rhs));
}


inline Imf_2_5_RgbaLut const * to_c(
    Imf_2_5::RgbaLut const * rhs)
{
    return reinterpret_cast<Imf_2_5_RgbaLut const * >(rhs);
}


inline Imf_2_5_RgbaLut * to_c(
    Imf_2_5::RgbaLut & rhs)
{
    return reinterpret_cast<Imf_2_5_RgbaLut * >(&(rhs));
}


inline Imf_2_5_RgbaLut * to_c(
    Imf_2_5::RgbaLut * rhs)
{
    return reinterpret_cast<Imf_2_5_RgbaLut * >(rhs);
}
