#pragma once
#include <imf_rational_.h>


#include <OpenEXR/ImfRational.h>
#include <cppmm_bind.hpp>






inline Imf_2_5::Rational const & to_cpp_ref(
    Imf_2_5_Rational const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::Rational const * >(rhs));
}


inline Imf_2_5::Rational & to_cpp_ref(
    Imf_2_5_Rational * rhs)
{
    return *(reinterpret_cast<Imf_2_5::Rational * >(rhs));
}


inline Imf_2_5::Rational const * to_cpp(
    Imf_2_5_Rational const * rhs)
{
    return reinterpret_cast<Imf_2_5::Rational const * >(rhs);
}


inline Imf_2_5::Rational * to_cpp(
    Imf_2_5_Rational * rhs)
{
    return reinterpret_cast<Imf_2_5::Rational * >(rhs);
}


inline Imf_2_5_Rational const * to_c(
    Imf_2_5::Rational const & rhs)
{
    return reinterpret_cast<Imf_2_5_Rational const * >(&(rhs));
}


inline Imf_2_5_Rational const * to_c(
    Imf_2_5::Rational const * rhs)
{
    return reinterpret_cast<Imf_2_5_Rational const * >(rhs);
}


inline Imf_2_5_Rational * to_c(
    Imf_2_5::Rational & rhs)
{
    return reinterpret_cast<Imf_2_5_Rational * >(&(rhs));
}


inline Imf_2_5_Rational * to_c(
    Imf_2_5::Rational * rhs)
{
    return reinterpret_cast<Imf_2_5_Rational * >(rhs);
}
