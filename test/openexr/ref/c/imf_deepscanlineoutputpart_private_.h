#pragma once
#include <imf_deepscanlineoutputpart_.h>


#include <OpenEXR/ImfDeepScanLineOutputPart.h>
#include <cppmm_bind.hpp>












inline Imf_2_5::DeepScanLineOutputPart const & to_cpp_ref(
    Imf_2_5_DeepScanLineOutputPart const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::DeepScanLineOutputPart const * >(rhs));
}


inline Imf_2_5::DeepScanLineOutputPart & to_cpp_ref(
    Imf_2_5_DeepScanLineOutputPart * rhs)
{
    return *(reinterpret_cast<Imf_2_5::DeepScanLineOutputPart * >(rhs));
}


inline Imf_2_5::DeepScanLineOutputPart const * to_cpp(
    Imf_2_5_DeepScanLineOutputPart const * rhs)
{
    return reinterpret_cast<Imf_2_5::DeepScanLineOutputPart const * >(rhs);
}


inline Imf_2_5::DeepScanLineOutputPart * to_cpp(
    Imf_2_5_DeepScanLineOutputPart * rhs)
{
    return reinterpret_cast<Imf_2_5::DeepScanLineOutputPart * >(rhs);
}


inline Imf_2_5_DeepScanLineOutputPart const * to_c(
    Imf_2_5::DeepScanLineOutputPart const & rhs)
{
    return reinterpret_cast<Imf_2_5_DeepScanLineOutputPart const * >(&(rhs));
}


inline Imf_2_5_DeepScanLineOutputPart const * to_c(
    Imf_2_5::DeepScanLineOutputPart const * rhs)
{
    return reinterpret_cast<Imf_2_5_DeepScanLineOutputPart const * >(rhs);
}


inline Imf_2_5_DeepScanLineOutputPart * to_c(
    Imf_2_5::DeepScanLineOutputPart & rhs)
{
    return reinterpret_cast<Imf_2_5_DeepScanLineOutputPart * >(&(rhs));
}


inline Imf_2_5_DeepScanLineOutputPart * to_c(
    Imf_2_5::DeepScanLineOutputPart * rhs)
{
    return reinterpret_cast<Imf_2_5_DeepScanLineOutputPart * >(rhs);
}
