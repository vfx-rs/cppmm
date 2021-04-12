#pragma once
#include <imf_deepscanlineinputfile_.h>


#include <OpenEXR/ImfDeepScanLineInputFile.h>
#include <cppmm_bind.hpp>




















inline Imf_2_5::DeepScanLineInputFile const & to_cpp_ref(
    Imf_2_5_DeepScanLineInputFile const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::DeepScanLineInputFile const * >(rhs));
}


inline Imf_2_5::DeepScanLineInputFile & to_cpp_ref(
    Imf_2_5_DeepScanLineInputFile * rhs)
{
    return *(reinterpret_cast<Imf_2_5::DeepScanLineInputFile * >(rhs));
}


inline Imf_2_5::DeepScanLineInputFile const * to_cpp(
    Imf_2_5_DeepScanLineInputFile const * rhs)
{
    return reinterpret_cast<Imf_2_5::DeepScanLineInputFile const * >(rhs);
}


inline Imf_2_5::DeepScanLineInputFile * to_cpp(
    Imf_2_5_DeepScanLineInputFile * rhs)
{
    return reinterpret_cast<Imf_2_5::DeepScanLineInputFile * >(rhs);
}


inline Imf_2_5_DeepScanLineInputFile const * to_c(
    Imf_2_5::DeepScanLineInputFile const & rhs)
{
    return reinterpret_cast<Imf_2_5_DeepScanLineInputFile const * >(&(rhs));
}


inline Imf_2_5_DeepScanLineInputFile const * to_c(
    Imf_2_5::DeepScanLineInputFile const * rhs)
{
    return reinterpret_cast<Imf_2_5_DeepScanLineInputFile const * >(rhs);
}


inline Imf_2_5_DeepScanLineInputFile * to_c(
    Imf_2_5::DeepScanLineInputFile & rhs)
{
    return reinterpret_cast<Imf_2_5_DeepScanLineInputFile * >(&(rhs));
}


inline Imf_2_5_DeepScanLineInputFile * to_c(
    Imf_2_5::DeepScanLineInputFile * rhs)
{
    return reinterpret_cast<Imf_2_5_DeepScanLineInputFile * >(rhs);
}
