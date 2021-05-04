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

inline void to_c(
    Imath_V3f_t const * * lhs
    , Imath_2_5::Vec3<float> const & rhs)
{
        *(lhs) = reinterpret_cast<Imath_V3f_t const * >(&(rhs));
}

inline void to_c(
    Imath_V3f_t const * * lhs
    , Imath_2_5::Vec3<float> const * rhs)
{
        *(lhs) = reinterpret_cast<Imath_V3f_t const * >(rhs);
}

inline void to_c(
    Imath_V3f_t * * lhs
    , Imath_2_5::Vec3<float> & rhs)
{
        *(lhs) = reinterpret_cast<Imath_V3f_t * >(&(rhs));
}

inline void to_c(
    Imath_V3f_t * * lhs
    , Imath_2_5::Vec3<float> * rhs)
{
        *(lhs) = reinterpret_cast<Imath_V3f_t * >(rhs);
}

inline void to_c_copy(
    Imath_V3f_t * lhs
    , Imath_2_5::Vec3<float> const & rhs)
{
        memcpy(lhs, &(rhs), sizeof(*(lhs)));
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

inline void to_c(
    Imath_V3i_t const * * lhs
    , Imath_2_5::Vec3<int> const & rhs)
{
        *(lhs) = reinterpret_cast<Imath_V3i_t const * >(&(rhs));
}

inline void to_c(
    Imath_V3i_t const * * lhs
    , Imath_2_5::Vec3<int> const * rhs)
{
        *(lhs) = reinterpret_cast<Imath_V3i_t const * >(rhs);
}

inline void to_c(
    Imath_V3i_t * * lhs
    , Imath_2_5::Vec3<int> & rhs)
{
        *(lhs) = reinterpret_cast<Imath_V3i_t * >(&(rhs));
}

inline void to_c(
    Imath_V3i_t * * lhs
    , Imath_2_5::Vec3<int> * rhs)
{
        *(lhs) = reinterpret_cast<Imath_V3i_t * >(rhs);
}

inline void to_c_copy(
    Imath_V3i_t * lhs
    , Imath_2_5::Vec3<int> const & rhs)
{
        memcpy(lhs, &(rhs), sizeof(*(lhs)));
}
