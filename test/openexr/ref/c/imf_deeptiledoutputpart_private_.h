#pragma once
#include <imf_deeptiledoutputpart_.h>


#include <OpenEXR/ImfDeepTiledOutputPart.h>
#include <cppmm_bind.hpp>





























inline Imf_2_5::DeepTiledOutputPart const & to_cpp_ref(
    Imf_2_5_DeepTiledOutputPart const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::DeepTiledOutputPart const * >(rhs));
}


inline Imf_2_5::DeepTiledOutputPart & to_cpp_ref(
    Imf_2_5_DeepTiledOutputPart * rhs)
{
    return *(reinterpret_cast<Imf_2_5::DeepTiledOutputPart * >(rhs));
}


inline Imf_2_5::DeepTiledOutputPart const * to_cpp(
    Imf_2_5_DeepTiledOutputPart const * rhs)
{
    return reinterpret_cast<Imf_2_5::DeepTiledOutputPart const * >(rhs);
}


inline Imf_2_5::DeepTiledOutputPart * to_cpp(
    Imf_2_5_DeepTiledOutputPart * rhs)
{
    return reinterpret_cast<Imf_2_5::DeepTiledOutputPart * >(rhs);
}


inline Imf_2_5_DeepTiledOutputPart const * to_c(
    Imf_2_5::DeepTiledOutputPart const & rhs)
{
    return reinterpret_cast<Imf_2_5_DeepTiledOutputPart const * >(&(rhs));
}


inline Imf_2_5_DeepTiledOutputPart const * to_c(
    Imf_2_5::DeepTiledOutputPart const * rhs)
{
    return reinterpret_cast<Imf_2_5_DeepTiledOutputPart const * >(rhs);
}


inline Imf_2_5_DeepTiledOutputPart * to_c(
    Imf_2_5::DeepTiledOutputPart & rhs)
{
    return reinterpret_cast<Imf_2_5_DeepTiledOutputPart * >(&(rhs));
}


inline Imf_2_5_DeepTiledOutputPart * to_c(
    Imf_2_5::DeepTiledOutputPart * rhs)
{
    return reinterpret_cast<Imf_2_5_DeepTiledOutputPart * >(rhs);
}
