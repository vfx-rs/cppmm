#pragma once
#include <half_.h>


#include <OpenEXR/half.h>
#include <cppmm_bind.hpp>






























inline half const & to_cpp_ref(
    Imath_2_5_half const * rhs)
{
    return *(reinterpret_cast<half const * >(rhs));
}


inline half & to_cpp_ref(
    Imath_2_5_half * rhs)
{
    return *(reinterpret_cast<half * >(rhs));
}


inline half const * to_cpp(
    Imath_2_5_half const * rhs)
{
    return reinterpret_cast<half const * >(rhs);
}


inline half * to_cpp(
    Imath_2_5_half * rhs)
{
    return reinterpret_cast<half * >(rhs);
}


inline Imath_2_5_half const * to_c(
    half const & rhs)
{
    return reinterpret_cast<Imath_2_5_half const * >(&(rhs));
}


inline Imath_2_5_half const * to_c(
    half const * rhs)
{
    return reinterpret_cast<Imath_2_5_half const * >(rhs);
}


inline Imath_2_5_half * to_c(
    half & rhs)
{
    return reinterpret_cast<Imath_2_5_half * >(&(rhs));
}


inline Imath_2_5_half * to_c(
    half * rhs)
{
    return reinterpret_cast<Imath_2_5_half * >(rhs);
}


inline Imath_2_5_half to_c_copy(
    half const & rhs)
{
    Imath_2_5_half result;
    Imath_2_5_half_half_2(&(result), reinterpret_cast<Imath_2_5_half const * >(&(rhs)));
    return result;
}
