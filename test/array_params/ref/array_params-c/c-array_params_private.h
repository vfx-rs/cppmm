#pragma once
#include <c-array_params.h>


#include <array_params.hpp>
#include <cstring>



inline imath::Matrix44<float> const & to_cpp_ref(
    imath_M44f_t const * rhs)
{
    return *(reinterpret_cast<imath::Matrix44<float> const * >(rhs));
}

inline imath::Matrix44<float> & to_cpp_ref(
    imath_M44f_t * rhs)
{
    return *(reinterpret_cast<imath::Matrix44<float> * >(rhs));
}

inline imath::Matrix44<float> const * to_cpp(
    imath_M44f_t const * rhs)
{
    return reinterpret_cast<imath::Matrix44<float> const * >(rhs);
}

inline imath::Matrix44<float> * to_cpp(
    imath_M44f_t * rhs)
{
    return reinterpret_cast<imath::Matrix44<float> * >(rhs);
}

inline imath_M44f_t const * to_c(
    imath::Matrix44<float> const & rhs)
{
    return reinterpret_cast<imath_M44f_t const * >(&(rhs));
}

inline imath_M44f_t const * to_c(
    imath::Matrix44<float> const * rhs)
{
    return reinterpret_cast<imath_M44f_t const * >(rhs);
}

inline imath_M44f_t * to_c(
    imath::Matrix44<float> & rhs)
{
    return reinterpret_cast<imath_M44f_t * >(&(rhs));
}

inline imath_M44f_t * to_c(
    imath::Matrix44<float> * rhs)
{
    return reinterpret_cast<imath_M44f_t * >(rhs);
}

inline imath_M44f_t to_c_copy(
    imath::Matrix44<float> const & rhs)
{
    imath_M44f_t result;
    memcpy(&(result), &(rhs), sizeof(result));
    return result;
}
