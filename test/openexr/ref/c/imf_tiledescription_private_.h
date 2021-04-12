#pragma once
#include <imf_tiledescription_.h>


#include <OpenEXR/ImfTileDescription.h>
#include <cppmm_bind.hpp>


inline Imf_2_5::TileDescription const & to_cpp_ref(
    Imf_2_5_TileDescription const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TileDescription const * >(rhs));
}


inline Imf_2_5::TileDescription & to_cpp_ref(
    Imf_2_5_TileDescription * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TileDescription * >(rhs));
}


inline Imf_2_5::TileDescription const * to_cpp(
    Imf_2_5_TileDescription const * rhs)
{
    return reinterpret_cast<Imf_2_5::TileDescription const * >(rhs);
}


inline Imf_2_5::TileDescription * to_cpp(
    Imf_2_5_TileDescription * rhs)
{
    return reinterpret_cast<Imf_2_5::TileDescription * >(rhs);
}


inline Imf_2_5_TileDescription const * to_c(
    Imf_2_5::TileDescription const & rhs)
{
    return reinterpret_cast<Imf_2_5_TileDescription const * >(&(rhs));
}


inline Imf_2_5_TileDescription const * to_c(
    Imf_2_5::TileDescription const * rhs)
{
    return reinterpret_cast<Imf_2_5_TileDescription const * >(rhs);
}


inline Imf_2_5_TileDescription * to_c(
    Imf_2_5::TileDescription & rhs)
{
    return reinterpret_cast<Imf_2_5_TileDescription * >(&(rhs));
}


inline Imf_2_5_TileDescription * to_c(
    Imf_2_5::TileDescription * rhs)
{
    return reinterpret_cast<Imf_2_5_TileDescription * >(rhs);
}
