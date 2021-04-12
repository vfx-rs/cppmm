#pragma once
#include <imf_tiledinputpart_.h>


#include <OpenEXR/ImfTiledInputPart.h>
#include <cppmm_bind.hpp>




























inline Imf_2_5::TiledInputPart const & to_cpp_ref(
    Imf_2_5_TiledInputPart const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TiledInputPart const * >(rhs));
}


inline Imf_2_5::TiledInputPart & to_cpp_ref(
    Imf_2_5_TiledInputPart * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TiledInputPart * >(rhs));
}


inline Imf_2_5::TiledInputPart const * to_cpp(
    Imf_2_5_TiledInputPart const * rhs)
{
    return reinterpret_cast<Imf_2_5::TiledInputPart const * >(rhs);
}


inline Imf_2_5::TiledInputPart * to_cpp(
    Imf_2_5_TiledInputPart * rhs)
{
    return reinterpret_cast<Imf_2_5::TiledInputPart * >(rhs);
}


inline Imf_2_5_TiledInputPart const * to_c(
    Imf_2_5::TiledInputPart const & rhs)
{
    return reinterpret_cast<Imf_2_5_TiledInputPart const * >(&(rhs));
}


inline Imf_2_5_TiledInputPart const * to_c(
    Imf_2_5::TiledInputPart const * rhs)
{
    return reinterpret_cast<Imf_2_5_TiledInputPart const * >(rhs);
}


inline Imf_2_5_TiledInputPart * to_c(
    Imf_2_5::TiledInputPart & rhs)
{
    return reinterpret_cast<Imf_2_5_TiledInputPart * >(&(rhs));
}


inline Imf_2_5_TiledInputPart * to_c(
    Imf_2_5::TiledInputPart * rhs)
{
    return reinterpret_cast<Imf_2_5_TiledInputPart * >(rhs);
}
