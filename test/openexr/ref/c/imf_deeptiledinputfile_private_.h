#pragma once
#include <imf_deeptiledinputfile_.h>


#include <OpenEXR/ImfDeepTiledInputFile.h>
#include <cppmm_bind.hpp>



































inline Imf_2_5::DeepTiledInputFile const & to_cpp_ref(
    Imf_2_5_DeepTiledInputFile const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::DeepTiledInputFile const * >(rhs));
}


inline Imf_2_5::DeepTiledInputFile & to_cpp_ref(
    Imf_2_5_DeepTiledInputFile * rhs)
{
    return *(reinterpret_cast<Imf_2_5::DeepTiledInputFile * >(rhs));
}


inline Imf_2_5::DeepTiledInputFile const * to_cpp(
    Imf_2_5_DeepTiledInputFile const * rhs)
{
    return reinterpret_cast<Imf_2_5::DeepTiledInputFile const * >(rhs);
}


inline Imf_2_5::DeepTiledInputFile * to_cpp(
    Imf_2_5_DeepTiledInputFile * rhs)
{
    return reinterpret_cast<Imf_2_5::DeepTiledInputFile * >(rhs);
}


inline Imf_2_5_DeepTiledInputFile const * to_c(
    Imf_2_5::DeepTiledInputFile const & rhs)
{
    return reinterpret_cast<Imf_2_5_DeepTiledInputFile const * >(&(rhs));
}


inline Imf_2_5_DeepTiledInputFile const * to_c(
    Imf_2_5::DeepTiledInputFile const * rhs)
{
    return reinterpret_cast<Imf_2_5_DeepTiledInputFile const * >(rhs);
}


inline Imf_2_5_DeepTiledInputFile * to_c(
    Imf_2_5::DeepTiledInputFile & rhs)
{
    return reinterpret_cast<Imf_2_5_DeepTiledInputFile * >(&(rhs));
}


inline Imf_2_5_DeepTiledInputFile * to_c(
    Imf_2_5::DeepTiledInputFile * rhs)
{
    return reinterpret_cast<Imf_2_5_DeepTiledInputFile * >(rhs);
}
