#pragma once
#include <imf_deepscanlineoutputfile_.h>


#include <OpenEXR/ImfDeepScanLineOutputFile.h>
#include <cppmm_bind.hpp>














inline Imf_2_5::DeepScanLineOutputFile const & to_cpp_ref(
    Imf_2_5_DeepScanLineOutputFile const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::DeepScanLineOutputFile const * >(rhs));
}


inline Imf_2_5::DeepScanLineOutputFile & to_cpp_ref(
    Imf_2_5_DeepScanLineOutputFile * rhs)
{
    return *(reinterpret_cast<Imf_2_5::DeepScanLineOutputFile * >(rhs));
}


inline Imf_2_5::DeepScanLineOutputFile const * to_cpp(
    Imf_2_5_DeepScanLineOutputFile const * rhs)
{
    return reinterpret_cast<Imf_2_5::DeepScanLineOutputFile const * >(rhs);
}


inline Imf_2_5::DeepScanLineOutputFile * to_cpp(
    Imf_2_5_DeepScanLineOutputFile * rhs)
{
    return reinterpret_cast<Imf_2_5::DeepScanLineOutputFile * >(rhs);
}


inline Imf_2_5_DeepScanLineOutputFile const * to_c(
    Imf_2_5::DeepScanLineOutputFile const & rhs)
{
    return reinterpret_cast<Imf_2_5_DeepScanLineOutputFile const * >(&(rhs));
}


inline Imf_2_5_DeepScanLineOutputFile const * to_c(
    Imf_2_5::DeepScanLineOutputFile const * rhs)
{
    return reinterpret_cast<Imf_2_5_DeepScanLineOutputFile const * >(rhs);
}


inline Imf_2_5_DeepScanLineOutputFile * to_c(
    Imf_2_5::DeepScanLineOutputFile & rhs)
{
    return reinterpret_cast<Imf_2_5_DeepScanLineOutputFile * >(&(rhs));
}


inline Imf_2_5_DeepScanLineOutputFile * to_c(
    Imf_2_5::DeepScanLineOutputFile * rhs)
{
    return reinterpret_cast<Imf_2_5_DeepScanLineOutputFile * >(rhs);
}
