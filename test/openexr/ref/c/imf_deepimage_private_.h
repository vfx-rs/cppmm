#pragma once
#include <imf_deepimage_.h>


#include <OpenEXR/ImfDeepImage.h>
#include <cppmm_bind.hpp>



















inline Imf_2_5::DeepImage const & to_cpp_ref(
    Imf_2_5_DeepImage const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::DeepImage const * >(rhs));
}


inline Imf_2_5::DeepImage & to_cpp_ref(
    Imf_2_5_DeepImage * rhs)
{
    return *(reinterpret_cast<Imf_2_5::DeepImage * >(rhs));
}


inline Imf_2_5::DeepImage const * to_cpp(
    Imf_2_5_DeepImage const * rhs)
{
    return reinterpret_cast<Imf_2_5::DeepImage const * >(rhs);
}


inline Imf_2_5::DeepImage * to_cpp(
    Imf_2_5_DeepImage * rhs)
{
    return reinterpret_cast<Imf_2_5::DeepImage * >(rhs);
}


inline Imf_2_5_DeepImage const * to_c(
    Imf_2_5::DeepImage const & rhs)
{
    return reinterpret_cast<Imf_2_5_DeepImage const * >(&(rhs));
}


inline Imf_2_5_DeepImage const * to_c(
    Imf_2_5::DeepImage const * rhs)
{
    return reinterpret_cast<Imf_2_5_DeepImage const * >(rhs);
}


inline Imf_2_5_DeepImage * to_c(
    Imf_2_5::DeepImage & rhs)
{
    return reinterpret_cast<Imf_2_5_DeepImage * >(&(rhs));
}


inline Imf_2_5_DeepImage * to_c(
    Imf_2_5::DeepImage * rhs)
{
    return reinterpret_cast<Imf_2_5_DeepImage * >(rhs);
}
