#pragma once
#include <imf_name_.h>


#include <OpenEXR/ImfName.h>
#include <cppmm_bind.hpp>





inline Imf_2_5::Name const & to_cpp_ref(
    Imf_2_5_Name const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::Name const * >(rhs));
}


inline Imf_2_5::Name & to_cpp_ref(
    Imf_2_5_Name * rhs)
{
    return *(reinterpret_cast<Imf_2_5::Name * >(rhs));
}


inline Imf_2_5::Name const * to_cpp(
    Imf_2_5_Name const * rhs)
{
    return reinterpret_cast<Imf_2_5::Name const * >(rhs);
}


inline Imf_2_5::Name * to_cpp(
    Imf_2_5_Name * rhs)
{
    return reinterpret_cast<Imf_2_5::Name * >(rhs);
}


inline Imf_2_5_Name const * to_c(
    Imf_2_5::Name const & rhs)
{
    return reinterpret_cast<Imf_2_5_Name const * >(&(rhs));
}


inline Imf_2_5_Name const * to_c(
    Imf_2_5::Name const * rhs)
{
    return reinterpret_cast<Imf_2_5_Name const * >(rhs);
}


inline Imf_2_5_Name * to_c(
    Imf_2_5::Name & rhs)
{
    return reinterpret_cast<Imf_2_5_Name * >(&(rhs));
}


inline Imf_2_5_Name * to_c(
    Imf_2_5::Name * rhs)
{
    return reinterpret_cast<Imf_2_5_Name * >(rhs);
}
