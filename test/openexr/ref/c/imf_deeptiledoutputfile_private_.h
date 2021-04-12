#pragma once
#include <imf_deeptiledoutputfile_.h>


#include <OpenEXR/ImfDeepTiledOutputFile.h>
#include <cppmm_bind.hpp>































inline Imf_2_5::DeepTiledOutputFile const & to_cpp_ref(
    Imf_2_5_DeepTiledOutputFile const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::DeepTiledOutputFile const * >(rhs));
}


inline Imf_2_5::DeepTiledOutputFile & to_cpp_ref(
    Imf_2_5_DeepTiledOutputFile * rhs)
{
    return *(reinterpret_cast<Imf_2_5::DeepTiledOutputFile * >(rhs));
}


inline Imf_2_5::DeepTiledOutputFile const * to_cpp(
    Imf_2_5_DeepTiledOutputFile const * rhs)
{
    return reinterpret_cast<Imf_2_5::DeepTiledOutputFile const * >(rhs);
}


inline Imf_2_5::DeepTiledOutputFile * to_cpp(
    Imf_2_5_DeepTiledOutputFile * rhs)
{
    return reinterpret_cast<Imf_2_5::DeepTiledOutputFile * >(rhs);
}


inline Imf_2_5_DeepTiledOutputFile const * to_c(
    Imf_2_5::DeepTiledOutputFile const & rhs)
{
    return reinterpret_cast<Imf_2_5_DeepTiledOutputFile const * >(&(rhs));
}


inline Imf_2_5_DeepTiledOutputFile const * to_c(
    Imf_2_5::DeepTiledOutputFile const * rhs)
{
    return reinterpret_cast<Imf_2_5_DeepTiledOutputFile const * >(rhs);
}


inline Imf_2_5_DeepTiledOutputFile * to_c(
    Imf_2_5::DeepTiledOutputFile & rhs)
{
    return reinterpret_cast<Imf_2_5_DeepTiledOutputFile * >(&(rhs));
}


inline Imf_2_5_DeepTiledOutputFile * to_c(
    Imf_2_5::DeepTiledOutputFile * rhs)
{
    return reinterpret_cast<Imf_2_5_DeepTiledOutputFile * >(rhs);
}
