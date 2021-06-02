#pragma once
#include <c-array_params.h>


#include "array_params-errors-private.h"

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

inline void to_c(
    imath_M44f_t const * * lhs
    , imath::Matrix44<float> const & rhs)
{
        *(lhs) = reinterpret_cast<imath_M44f_t const * >(&(rhs));
}

inline void to_c(
    imath_M44f_t const * * lhs
    , imath::Matrix44<float> const * rhs)
{
        *(lhs) = reinterpret_cast<imath_M44f_t const * >(rhs);
}

inline void to_c(
    imath_M44f_t * * lhs
    , imath::Matrix44<float> & rhs)
{
        *(lhs) = reinterpret_cast<imath_M44f_t * >(&(rhs));
}

inline void to_c(
    imath_M44f_t * * lhs
    , imath::Matrix44<float> * rhs)
{
        *(lhs) = reinterpret_cast<imath_M44f_t * >(rhs);
}

inline void to_c_copy(
    imath_M44f_t * lhs
    , imath::Matrix44<float> const & rhs)
{
        memcpy(lhs, &(rhs), sizeof(*(lhs)));
}

