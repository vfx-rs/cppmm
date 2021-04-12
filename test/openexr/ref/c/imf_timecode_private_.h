#pragma once
#include <imf_timecode_.h>


#include <OpenEXR/ImfTimeCode.h>
#include <cppmm_bind.hpp>

































inline Imf_2_5::TimeCode const & to_cpp_ref(
    Imf_2_5_TimeCode const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TimeCode const * >(rhs));
}


inline Imf_2_5::TimeCode & to_cpp_ref(
    Imf_2_5_TimeCode * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TimeCode * >(rhs));
}


inline Imf_2_5::TimeCode const * to_cpp(
    Imf_2_5_TimeCode const * rhs)
{
    return reinterpret_cast<Imf_2_5::TimeCode const * >(rhs);
}


inline Imf_2_5::TimeCode * to_cpp(
    Imf_2_5_TimeCode * rhs)
{
    return reinterpret_cast<Imf_2_5::TimeCode * >(rhs);
}


inline Imf_2_5_TimeCode const * to_c(
    Imf_2_5::TimeCode const & rhs)
{
    return reinterpret_cast<Imf_2_5_TimeCode const * >(&(rhs));
}


inline Imf_2_5_TimeCode const * to_c(
    Imf_2_5::TimeCode const * rhs)
{
    return reinterpret_cast<Imf_2_5_TimeCode const * >(rhs);
}


inline Imf_2_5_TimeCode * to_c(
    Imf_2_5::TimeCode & rhs)
{
    return reinterpret_cast<Imf_2_5_TimeCode * >(&(rhs));
}


inline Imf_2_5_TimeCode * to_c(
    Imf_2_5::TimeCode * rhs)
{
    return reinterpret_cast<Imf_2_5_TimeCode * >(rhs);
}


inline Imf_2_5_TimeCode to_c_copy(
    Imf_2_5::TimeCode const & rhs)
{
    Imf_2_5_TimeCode result;
    Imf_2_5_TimeCode_TimeCode_2(&(result), reinterpret_cast<Imf_2_5_TimeCode const * >(&(rhs)));
    return result;
}
