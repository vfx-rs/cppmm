#pragma once
#include <imf_array_.h>


#include <OpenEXR/ImfArray.h>
#include <cppmm_bind.hpp>










inline Imf_2_5::Array<float> const & to_cpp_ref(
    Imf_2_5_ArrayFloat const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::Array<float> const * >(rhs));
}


inline Imf_2_5::Array<float> & to_cpp_ref(
    Imf_2_5_ArrayFloat * rhs)
{
    return *(reinterpret_cast<Imf_2_5::Array<float> * >(rhs));
}


inline Imf_2_5::Array<float> const * to_cpp(
    Imf_2_5_ArrayFloat const * rhs)
{
    return reinterpret_cast<Imf_2_5::Array<float> const * >(rhs);
}


inline Imf_2_5::Array<float> * to_cpp(
    Imf_2_5_ArrayFloat * rhs)
{
    return reinterpret_cast<Imf_2_5::Array<float> * >(rhs);
}


inline Imf_2_5_ArrayFloat const * to_c(
    Imf_2_5::Array<float> const & rhs)
{
    return reinterpret_cast<Imf_2_5_ArrayFloat const * >(&(rhs));
}


inline Imf_2_5_ArrayFloat const * to_c(
    Imf_2_5::Array<float> const * rhs)
{
    return reinterpret_cast<Imf_2_5_ArrayFloat const * >(rhs);
}


inline Imf_2_5_ArrayFloat * to_c(
    Imf_2_5::Array<float> & rhs)
{
    return reinterpret_cast<Imf_2_5_ArrayFloat * >(&(rhs));
}


inline Imf_2_5_ArrayFloat * to_c(
    Imf_2_5::Array<float> * rhs)
{
    return reinterpret_cast<Imf_2_5_ArrayFloat * >(rhs);
}











inline Imf_2_5::Array2D<float> const & to_cpp_ref(
    Imf_2_5_Array2DFloat const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::Array2D<float> const * >(rhs));
}


inline Imf_2_5::Array2D<float> & to_cpp_ref(
    Imf_2_5_Array2DFloat * rhs)
{
    return *(reinterpret_cast<Imf_2_5::Array2D<float> * >(rhs));
}


inline Imf_2_5::Array2D<float> const * to_cpp(
    Imf_2_5_Array2DFloat const * rhs)
{
    return reinterpret_cast<Imf_2_5::Array2D<float> const * >(rhs);
}


inline Imf_2_5::Array2D<float> * to_cpp(
    Imf_2_5_Array2DFloat * rhs)
{
    return reinterpret_cast<Imf_2_5::Array2D<float> * >(rhs);
}


inline Imf_2_5_Array2DFloat const * to_c(
    Imf_2_5::Array2D<float> const & rhs)
{
    return reinterpret_cast<Imf_2_5_Array2DFloat const * >(&(rhs));
}


inline Imf_2_5_Array2DFloat const * to_c(
    Imf_2_5::Array2D<float> const * rhs)
{
    return reinterpret_cast<Imf_2_5_Array2DFloat const * >(rhs);
}


inline Imf_2_5_Array2DFloat * to_c(
    Imf_2_5::Array2D<float> & rhs)
{
    return reinterpret_cast<Imf_2_5_Array2DFloat * >(&(rhs));
}


inline Imf_2_5_Array2DFloat * to_c(
    Imf_2_5::Array2D<float> * rhs)
{
    return reinterpret_cast<Imf_2_5_Array2DFloat * >(rhs);
}
