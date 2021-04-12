#pragma once
#include <imf_tiledinputfile_.h>


#include <OpenEXR/ImfTiledInputFile.h>
#include <cppmm_bind.hpp>






























inline Imf_2_5::TiledInputFile const & to_cpp_ref(
    Imf_2_5_TiledInputFile const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TiledInputFile const * >(rhs));
}


inline Imf_2_5::TiledInputFile & to_cpp_ref(
    Imf_2_5_TiledInputFile * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TiledInputFile * >(rhs));
}


inline Imf_2_5::TiledInputFile const * to_cpp(
    Imf_2_5_TiledInputFile const * rhs)
{
    return reinterpret_cast<Imf_2_5::TiledInputFile const * >(rhs);
}


inline Imf_2_5::TiledInputFile * to_cpp(
    Imf_2_5_TiledInputFile * rhs)
{
    return reinterpret_cast<Imf_2_5::TiledInputFile * >(rhs);
}


inline Imf_2_5_TiledInputFile const * to_c(
    Imf_2_5::TiledInputFile const & rhs)
{
    return reinterpret_cast<Imf_2_5_TiledInputFile const * >(&(rhs));
}


inline Imf_2_5_TiledInputFile const * to_c(
    Imf_2_5::TiledInputFile const * rhs)
{
    return reinterpret_cast<Imf_2_5_TiledInputFile const * >(rhs);
}


inline Imf_2_5_TiledInputFile * to_c(
    Imf_2_5::TiledInputFile & rhs)
{
    return reinterpret_cast<Imf_2_5_TiledInputFile * >(&(rhs));
}


inline Imf_2_5_TiledInputFile * to_c(
    Imf_2_5::TiledInputFile * rhs)
{
    return reinterpret_cast<Imf_2_5_TiledInputFile * >(rhs);
}
