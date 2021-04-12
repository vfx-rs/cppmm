#pragma once
#include <imf_deeptiledinputpart_.h>


#include <OpenEXR/ImfDeepTiledInputPart.h>
#include <cppmm_bind.hpp>
































inline Imf_2_5::DeepTiledInputPart const & to_cpp_ref(
    Imf_2_5_DeepTiledInputPart const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::DeepTiledInputPart const * >(rhs));
}


inline Imf_2_5::DeepTiledInputPart & to_cpp_ref(
    Imf_2_5_DeepTiledInputPart * rhs)
{
    return *(reinterpret_cast<Imf_2_5::DeepTiledInputPart * >(rhs));
}


inline Imf_2_5::DeepTiledInputPart const * to_cpp(
    Imf_2_5_DeepTiledInputPart const * rhs)
{
    return reinterpret_cast<Imf_2_5::DeepTiledInputPart const * >(rhs);
}


inline Imf_2_5::DeepTiledInputPart * to_cpp(
    Imf_2_5_DeepTiledInputPart * rhs)
{
    return reinterpret_cast<Imf_2_5::DeepTiledInputPart * >(rhs);
}


inline Imf_2_5_DeepTiledInputPart const * to_c(
    Imf_2_5::DeepTiledInputPart const & rhs)
{
    return reinterpret_cast<Imf_2_5_DeepTiledInputPart const * >(&(rhs));
}


inline Imf_2_5_DeepTiledInputPart const * to_c(
    Imf_2_5::DeepTiledInputPart const * rhs)
{
    return reinterpret_cast<Imf_2_5_DeepTiledInputPart const * >(rhs);
}


inline Imf_2_5_DeepTiledInputPart * to_c(
    Imf_2_5::DeepTiledInputPart & rhs)
{
    return reinterpret_cast<Imf_2_5_DeepTiledInputPart * >(&(rhs));
}


inline Imf_2_5_DeepTiledInputPart * to_c(
    Imf_2_5::DeepTiledInputPart * rhs)
{
    return reinterpret_cast<Imf_2_5_DeepTiledInputPart * >(rhs);
}
