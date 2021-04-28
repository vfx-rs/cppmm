#pragma once
#include <imath_vec.h>


#include <OpenEXR/ImathVec.h>
#include <cstring>
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
    memcpy(&(result), &(rhs), sizeof(result));
    return result;
}










inline Imath_2_5::Vec3<int> const & to_cpp_ref(
    Imath_V3i_t const * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Vec3<int> const * >(rhs));
}

inline Imath_2_5::Vec3<int> & to_cpp_ref(
    Imath_V3i_t * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Vec3<int> * >(rhs));
}

inline Imath_2_5::Vec3<int> const * to_cpp(
    Imath_V3i_t const * rhs)
{
    return reinterpret_cast<Imath_2_5::Vec3<int> const * >(rhs);
}

inline Imath_2_5::Vec3<int> * to_cpp(
    Imath_V3i_t * rhs)
{
    return reinterpret_cast<Imath_2_5::Vec3<int> * >(rhs);
}

inline Imath_V3i_t const * to_c(
    Imath_2_5::Vec3<int> const & rhs)
{
    return reinterpret_cast<Imath_V3i_t const * >(&(rhs));
}

inline Imath_V3i_t const * to_c(
    Imath_2_5::Vec3<int> const * rhs)
{
    return reinterpret_cast<Imath_V3i_t const * >(rhs);
}

inline Imath_V3i_t * to_c(
    Imath_2_5::Vec3<int> & rhs)
{
    return reinterpret_cast<Imath_V3i_t * >(&(rhs));
}

inline Imath_V3i_t * to_c(
    Imath_2_5::Vec3<int> * rhs)
{
    return reinterpret_cast<Imath_V3i_t * >(rhs);
}

inline Imath_V3i_t to_c_copy(
    Imath_2_5::Vec3<int> const & rhs)
{
    Imath_V3i_t result;
    memcpy(&(result), &(rhs), sizeof(result));
    return result;
}
