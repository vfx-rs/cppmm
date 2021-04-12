#pragma once
#include <imf_deepcompositing_.h>


#include <OpenEXR/ImfDeepCompositing.h>
#include <cppmm_bind.hpp>






inline Imf_2_5::DeepCompositing const & to_cpp_ref(
    Imf_2_5_DeepCompositing const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::DeepCompositing const * >(rhs));
}


inline Imf_2_5::DeepCompositing & to_cpp_ref(
    Imf_2_5_DeepCompositing * rhs)
{
    return *(reinterpret_cast<Imf_2_5::DeepCompositing * >(rhs));
}


inline Imf_2_5::DeepCompositing const * to_cpp(
    Imf_2_5_DeepCompositing const * rhs)
{
    return reinterpret_cast<Imf_2_5::DeepCompositing const * >(rhs);
}


inline Imf_2_5::DeepCompositing * to_cpp(
    Imf_2_5_DeepCompositing * rhs)
{
    return reinterpret_cast<Imf_2_5::DeepCompositing * >(rhs);
}


inline Imf_2_5_DeepCompositing const * to_c(
    Imf_2_5::DeepCompositing const & rhs)
{
    return reinterpret_cast<Imf_2_5_DeepCompositing const * >(&(rhs));
}


inline Imf_2_5_DeepCompositing const * to_c(
    Imf_2_5::DeepCompositing const * rhs)
{
    return reinterpret_cast<Imf_2_5_DeepCompositing const * >(rhs);
}


inline Imf_2_5_DeepCompositing * to_c(
    Imf_2_5::DeepCompositing & rhs)
{
    return reinterpret_cast<Imf_2_5_DeepCompositing * >(&(rhs));
}


inline Imf_2_5_DeepCompositing * to_c(
    Imf_2_5::DeepCompositing * rhs)
{
    return reinterpret_cast<Imf_2_5_DeepCompositing * >(rhs);
}
