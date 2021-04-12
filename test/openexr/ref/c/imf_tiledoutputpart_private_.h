#pragma once
#include <imf_tiledoutputpart_.h>


#include <OpenEXR/ImfTiledOutputPart.h>
#include <cppmm_bind.hpp>































inline Imf_2_5::TiledOutputPart const & to_cpp_ref(
    Imf_2_5_TiledOutputPart const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TiledOutputPart const * >(rhs));
}


inline Imf_2_5::TiledOutputPart & to_cpp_ref(
    Imf_2_5_TiledOutputPart * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TiledOutputPart * >(rhs));
}


inline Imf_2_5::TiledOutputPart const * to_cpp(
    Imf_2_5_TiledOutputPart const * rhs)
{
    return reinterpret_cast<Imf_2_5::TiledOutputPart const * >(rhs);
}


inline Imf_2_5::TiledOutputPart * to_cpp(
    Imf_2_5_TiledOutputPart * rhs)
{
    return reinterpret_cast<Imf_2_5::TiledOutputPart * >(rhs);
}


inline Imf_2_5_TiledOutputPart const * to_c(
    Imf_2_5::TiledOutputPart const & rhs)
{
    return reinterpret_cast<Imf_2_5_TiledOutputPart const * >(&(rhs));
}


inline Imf_2_5_TiledOutputPart const * to_c(
    Imf_2_5::TiledOutputPart const * rhs)
{
    return reinterpret_cast<Imf_2_5_TiledOutputPart const * >(rhs);
}


inline Imf_2_5_TiledOutputPart * to_c(
    Imf_2_5::TiledOutputPart & rhs)
{
    return reinterpret_cast<Imf_2_5_TiledOutputPart * >(&(rhs));
}


inline Imf_2_5_TiledOutputPart * to_c(
    Imf_2_5::TiledOutputPart * rhs)
{
    return reinterpret_cast<Imf_2_5_TiledOutputPart * >(rhs);
}
