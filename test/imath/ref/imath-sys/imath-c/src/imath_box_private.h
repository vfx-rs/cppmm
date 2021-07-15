#pragma once
#include <imath_box.h>


#include "imath-errors-private.h"

#include <OpenEXR/ImathBox.h>
#include <cstring>

inline Imath_2_5::Box<Imath::Vec3<float> > const & to_cpp_ref(
    Imath_Box3f_t const * rhs)
{
        return *(reinterpret_cast<Imath_2_5::Box<Imath::Vec3<float> > const * >(rhs));
}

inline Imath_2_5::Box<Imath::Vec3<float> > & to_cpp_ref(
    Imath_Box3f_t * rhs)
{
        return *(reinterpret_cast<Imath_2_5::Box<Imath::Vec3<float> > * >(rhs));
}

inline Imath_2_5::Box<Imath::Vec3<float> > const * to_cpp(
    Imath_Box3f_t const * rhs)
{
        return reinterpret_cast<Imath_2_5::Box<Imath::Vec3<float> > const * >(rhs);
}

inline Imath_2_5::Box<Imath::Vec3<float> > * to_cpp(
    Imath_Box3f_t * rhs)
{
        return reinterpret_cast<Imath_2_5::Box<Imath::Vec3<float> > * >(rhs);
}

inline void to_c(
    Imath_Box3f_t const * * lhs
    , Imath_2_5::Box<Imath::Vec3<float> > const & rhs)
{
        *(lhs) = reinterpret_cast<Imath_Box3f_t const * >(&(rhs));
}

inline void to_c(
    Imath_Box3f_t const * * lhs
    , Imath_2_5::Box<Imath::Vec3<float> > const * rhs)
{
        *(lhs) = reinterpret_cast<Imath_Box3f_t const * >(rhs);
}

inline void to_c(
    Imath_Box3f_t * * lhs
    , Imath_2_5::Box<Imath::Vec3<float> > & rhs)
{
        *(lhs) = reinterpret_cast<Imath_Box3f_t * >(&(rhs));
}

inline void to_c(
    Imath_Box3f_t * * lhs
    , Imath_2_5::Box<Imath::Vec3<float> > * rhs)
{
        *(lhs) = reinterpret_cast<Imath_Box3f_t * >(rhs);
}

inline void to_c_copy(
    Imath_Box3f_t * lhs
    , Imath_2_5::Box<Imath::Vec3<float> > const & rhs)
{
        memcpy(lhs, &(rhs), sizeof(*(lhs)));
}

inline Imath_2_5::Box<Imath::Vec3<int> > const & to_cpp_ref(
    Imath_Box3i_t const * rhs)
{
        return *(reinterpret_cast<Imath_2_5::Box<Imath::Vec3<int> > const * >(rhs));
}

inline Imath_2_5::Box<Imath::Vec3<int> > & to_cpp_ref(
    Imath_Box3i_t * rhs)
{
        return *(reinterpret_cast<Imath_2_5::Box<Imath::Vec3<int> > * >(rhs));
}

inline Imath_2_5::Box<Imath::Vec3<int> > const * to_cpp(
    Imath_Box3i_t const * rhs)
{
        return reinterpret_cast<Imath_2_5::Box<Imath::Vec3<int> > const * >(rhs);
}

inline Imath_2_5::Box<Imath::Vec3<int> > * to_cpp(
    Imath_Box3i_t * rhs)
{
        return reinterpret_cast<Imath_2_5::Box<Imath::Vec3<int> > * >(rhs);
}

inline void to_c(
    Imath_Box3i_t const * * lhs
    , Imath_2_5::Box<Imath::Vec3<int> > const & rhs)
{
        *(lhs) = reinterpret_cast<Imath_Box3i_t const * >(&(rhs));
}

inline void to_c(
    Imath_Box3i_t const * * lhs
    , Imath_2_5::Box<Imath::Vec3<int> > const * rhs)
{
        *(lhs) = reinterpret_cast<Imath_Box3i_t const * >(rhs);
}

inline void to_c(
    Imath_Box3i_t * * lhs
    , Imath_2_5::Box<Imath::Vec3<int> > & rhs)
{
        *(lhs) = reinterpret_cast<Imath_Box3i_t * >(&(rhs));
}

inline void to_c(
    Imath_Box3i_t * * lhs
    , Imath_2_5::Box<Imath::Vec3<int> > * rhs)
{
        *(lhs) = reinterpret_cast<Imath_Box3i_t * >(rhs);
}

inline void to_c_copy(
    Imath_Box3i_t * lhs
    , Imath_2_5::Box<Imath::Vec3<int> > const & rhs)
{
        memcpy(lhs, &(rhs), sizeof(*(lhs)));
}

