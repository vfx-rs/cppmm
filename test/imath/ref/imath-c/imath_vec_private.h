#pragma once
#include <imath_vec.h>


#include <OpenEXR/ImathVec.h>
#include <vector>













inline Imath_2_5::Vec3<float> const & to_cpp_ref(
    Imath_V3f_t const * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Vec3<float> const * >(rhs));
}


inline Imath_2_5::Vec3<float> & to_cpp_ref(
    Imath_V3f_t * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Vec3<float> * >(rhs));
}


inline Imath_2_5::Vec3<float> const * to_cpp(
    Imath_V3f_t const * rhs)
{
    return reinterpret_cast<Imath_2_5::Vec3<float> const * >(rhs);
}


inline Imath_2_5::Vec3<float> * to_cpp(
    Imath_V3f_t * rhs)
{
    return reinterpret_cast<Imath_2_5::Vec3<float> * >(rhs);
}


inline Imath_V3f_t const * to_c(
    Imath_2_5::Vec3<float> const & rhs)
{
    return reinterpret_cast<Imath_V3f_t const * >(&(rhs));
}


inline Imath_V3f_t const * to_c(
    Imath_2_5::Vec3<float> const * rhs)
{
    return reinterpret_cast<Imath_V3f_t const * >(rhs);
}


inline Imath_V3f_t * to_c(
    Imath_2_5::Vec3<float> & rhs)
{
    return reinterpret_cast<Imath_V3f_t * >(&(rhs));
}


inline Imath_V3f_t * to_c(
    Imath_2_5::Vec3<float> * rhs)
{
    return reinterpret_cast<Imath_V3f_t * >(rhs);
}


inline Imath_V3f_t to_c_copy(
    Imath_2_5::Vec3<float> const & rhs)
{
    Imath_V3f_t result;
    Imath_2_5__Vec3_float__Vec3_1(&(result), reinterpret_cast<Imath_V3f_t const * >(&(rhs)));
    return result;
}
