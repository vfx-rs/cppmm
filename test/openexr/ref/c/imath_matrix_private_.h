#pragma once
#include <imath_matrix_.h>


#include <OpenEXR/ImathMatrix.h>
#include <cppmm_bind.hpp>
#include <vector>











































inline Imath_2_5::Matrix33<float> const & to_cpp_ref(
    Imath_2_5_M33f const * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Matrix33<float> const * >(rhs));
}


inline Imath_2_5::Matrix33<float> & to_cpp_ref(
    Imath_2_5_M33f * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Matrix33<float> * >(rhs));
}


inline Imath_2_5::Matrix33<float> const * to_cpp(
    Imath_2_5_M33f const * rhs)
{
    return reinterpret_cast<Imath_2_5::Matrix33<float> const * >(rhs);
}


inline Imath_2_5::Matrix33<float> * to_cpp(
    Imath_2_5_M33f * rhs)
{
    return reinterpret_cast<Imath_2_5::Matrix33<float> * >(rhs);
}


inline Imath_2_5_M33f const * to_c(
    Imath_2_5::Matrix33<float> const & rhs)
{
    return reinterpret_cast<Imath_2_5_M33f const * >(&(rhs));
}


inline Imath_2_5_M33f const * to_c(
    Imath_2_5::Matrix33<float> const * rhs)
{
    return reinterpret_cast<Imath_2_5_M33f const * >(rhs);
}


inline Imath_2_5_M33f * to_c(
    Imath_2_5::Matrix33<float> & rhs)
{
    return reinterpret_cast<Imath_2_5_M33f * >(&(rhs));
}


inline Imath_2_5_M33f * to_c(
    Imath_2_5::Matrix33<float> * rhs)
{
    return reinterpret_cast<Imath_2_5_M33f * >(rhs);
}


inline Imath_2_5_M33f to_c_copy(
    Imath_2_5::Matrix33<float> const & rhs)
{
    Imath_2_5_M33f result;
    Imath_2_5_M33f_Matrix33_3(&(result), reinterpret_cast<Imath_2_5_M33f const * >(&(rhs)));
    return result;
}











































inline Imath_2_5::Matrix33<double> const & to_cpp_ref(
    Imath_2_5_M33d const * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Matrix33<double> const * >(rhs));
}


inline Imath_2_5::Matrix33<double> & to_cpp_ref(
    Imath_2_5_M33d * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Matrix33<double> * >(rhs));
}


inline Imath_2_5::Matrix33<double> const * to_cpp(
    Imath_2_5_M33d const * rhs)
{
    return reinterpret_cast<Imath_2_5::Matrix33<double> const * >(rhs);
}


inline Imath_2_5::Matrix33<double> * to_cpp(
    Imath_2_5_M33d * rhs)
{
    return reinterpret_cast<Imath_2_5::Matrix33<double> * >(rhs);
}


inline Imath_2_5_M33d const * to_c(
    Imath_2_5::Matrix33<double> const & rhs)
{
    return reinterpret_cast<Imath_2_5_M33d const * >(&(rhs));
}


inline Imath_2_5_M33d const * to_c(
    Imath_2_5::Matrix33<double> const * rhs)
{
    return reinterpret_cast<Imath_2_5_M33d const * >(rhs);
}


inline Imath_2_5_M33d * to_c(
    Imath_2_5::Matrix33<double> & rhs)
{
    return reinterpret_cast<Imath_2_5_M33d * >(&(rhs));
}


inline Imath_2_5_M33d * to_c(
    Imath_2_5::Matrix33<double> * rhs)
{
    return reinterpret_cast<Imath_2_5_M33d * >(rhs);
}


inline Imath_2_5_M33d to_c_copy(
    Imath_2_5::Matrix33<double> const & rhs)
{
    Imath_2_5_M33d result;
    Imath_2_5_M33d_Matrix33_3(&(result), reinterpret_cast<Imath_2_5_M33d const * >(&(rhs)));
    return result;
}












































inline Imath_2_5::Matrix44<float> const & to_cpp_ref(
    Imath_2_5_M44f const * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Matrix44<float> const * >(rhs));
}


inline Imath_2_5::Matrix44<float> & to_cpp_ref(
    Imath_2_5_M44f * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Matrix44<float> * >(rhs));
}


inline Imath_2_5::Matrix44<float> const * to_cpp(
    Imath_2_5_M44f const * rhs)
{
    return reinterpret_cast<Imath_2_5::Matrix44<float> const * >(rhs);
}


inline Imath_2_5::Matrix44<float> * to_cpp(
    Imath_2_5_M44f * rhs)
{
    return reinterpret_cast<Imath_2_5::Matrix44<float> * >(rhs);
}


inline Imath_2_5_M44f const * to_c(
    Imath_2_5::Matrix44<float> const & rhs)
{
    return reinterpret_cast<Imath_2_5_M44f const * >(&(rhs));
}


inline Imath_2_5_M44f const * to_c(
    Imath_2_5::Matrix44<float> const * rhs)
{
    return reinterpret_cast<Imath_2_5_M44f const * >(rhs);
}


inline Imath_2_5_M44f * to_c(
    Imath_2_5::Matrix44<float> & rhs)
{
    return reinterpret_cast<Imath_2_5_M44f * >(&(rhs));
}


inline Imath_2_5_M44f * to_c(
    Imath_2_5::Matrix44<float> * rhs)
{
    return reinterpret_cast<Imath_2_5_M44f * >(rhs);
}


inline Imath_2_5_M44f to_c_copy(
    Imath_2_5::Matrix44<float> const & rhs)
{
    Imath_2_5_M44f result;
    Imath_2_5_M44f_Matrix44_4(&(result), reinterpret_cast<Imath_2_5_M44f const * >(&(rhs)));
    return result;
}












































inline Imath_2_5::Matrix44<double> const & to_cpp_ref(
    Imath_2_5_M44d const * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Matrix44<double> const * >(rhs));
}


inline Imath_2_5::Matrix44<double> & to_cpp_ref(
    Imath_2_5_M44d * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Matrix44<double> * >(rhs));
}


inline Imath_2_5::Matrix44<double> const * to_cpp(
    Imath_2_5_M44d const * rhs)
{
    return reinterpret_cast<Imath_2_5::Matrix44<double> const * >(rhs);
}


inline Imath_2_5::Matrix44<double> * to_cpp(
    Imath_2_5_M44d * rhs)
{
    return reinterpret_cast<Imath_2_5::Matrix44<double> * >(rhs);
}


inline Imath_2_5_M44d const * to_c(
    Imath_2_5::Matrix44<double> const & rhs)
{
    return reinterpret_cast<Imath_2_5_M44d const * >(&(rhs));
}


inline Imath_2_5_M44d const * to_c(
    Imath_2_5::Matrix44<double> const * rhs)
{
    return reinterpret_cast<Imath_2_5_M44d const * >(rhs);
}


inline Imath_2_5_M44d * to_c(
    Imath_2_5::Matrix44<double> & rhs)
{
    return reinterpret_cast<Imath_2_5_M44d * >(&(rhs));
}


inline Imath_2_5_M44d * to_c(
    Imath_2_5::Matrix44<double> * rhs)
{
    return reinterpret_cast<Imath_2_5_M44d * >(rhs);
}


inline Imath_2_5_M44d to_c_copy(
    Imath_2_5::Matrix44<double> const & rhs)
{
    Imath_2_5_M44d result;
    Imath_2_5_M44d_Matrix44_4(&(result), reinterpret_cast<Imath_2_5_M44d const * >(&(rhs)));
    return result;
}
