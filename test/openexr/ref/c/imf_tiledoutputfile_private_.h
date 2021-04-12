#pragma once
#include <imf_tiledoutputfile_.h>


#include <OpenEXR/ImfTiledOutputFile.h>
#include <cppmm_bind.hpp>
































inline Imf_2_5::TiledOutputFile const & to_cpp_ref(
    Imf_2_5_TiledOutputFile const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TiledOutputFile const * >(rhs));
}


inline Imf_2_5::TiledOutputFile & to_cpp_ref(
    Imf_2_5_TiledOutputFile * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TiledOutputFile * >(rhs));
}


inline Imf_2_5::TiledOutputFile const * to_cpp(
    Imf_2_5_TiledOutputFile const * rhs)
{
    return reinterpret_cast<Imf_2_5::TiledOutputFile const * >(rhs);
}


inline Imf_2_5::TiledOutputFile * to_cpp(
    Imf_2_5_TiledOutputFile * rhs)
{
    return reinterpret_cast<Imf_2_5::TiledOutputFile * >(rhs);
}


inline Imf_2_5_TiledOutputFile const * to_c(
    Imf_2_5::TiledOutputFile const & rhs)
{
    return reinterpret_cast<Imf_2_5_TiledOutputFile const * >(&(rhs));
}


inline Imf_2_5_TiledOutputFile const * to_c(
    Imf_2_5::TiledOutputFile const * rhs)
{
    return reinterpret_cast<Imf_2_5_TiledOutputFile const * >(rhs);
}


inline Imf_2_5_TiledOutputFile * to_c(
    Imf_2_5::TiledOutputFile & rhs)
{
    return reinterpret_cast<Imf_2_5_TiledOutputFile * >(&(rhs));
}


inline Imf_2_5_TiledOutputFile * to_c(
    Imf_2_5::TiledOutputFile * rhs)
{
    return reinterpret_cast<Imf_2_5_TiledOutputFile * >(rhs);
}
