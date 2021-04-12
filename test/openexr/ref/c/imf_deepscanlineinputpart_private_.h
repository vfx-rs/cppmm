#pragma once
#include <imf_deepscanlineinputpart_.h>


#include <OpenEXR/ImfDeepScanLineInputPart.h>
#include <cppmm_bind.hpp>


















inline Imf_2_5::DeepScanLineInputPart const & to_cpp_ref(
    Imf_2_5_DeepScanLineInputPart const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::DeepScanLineInputPart const * >(rhs));
}


inline Imf_2_5::DeepScanLineInputPart & to_cpp_ref(
    Imf_2_5_DeepScanLineInputPart * rhs)
{
    return *(reinterpret_cast<Imf_2_5::DeepScanLineInputPart * >(rhs));
}


inline Imf_2_5::DeepScanLineInputPart const * to_cpp(
    Imf_2_5_DeepScanLineInputPart const * rhs)
{
    return reinterpret_cast<Imf_2_5::DeepScanLineInputPart const * >(rhs);
}


inline Imf_2_5::DeepScanLineInputPart * to_cpp(
    Imf_2_5_DeepScanLineInputPart * rhs)
{
    return reinterpret_cast<Imf_2_5::DeepScanLineInputPart * >(rhs);
}


inline Imf_2_5_DeepScanLineInputPart const * to_c(
    Imf_2_5::DeepScanLineInputPart const & rhs)
{
    return reinterpret_cast<Imf_2_5_DeepScanLineInputPart const * >(&(rhs));
}


inline Imf_2_5_DeepScanLineInputPart const * to_c(
    Imf_2_5::DeepScanLineInputPart const * rhs)
{
    return reinterpret_cast<Imf_2_5_DeepScanLineInputPart const * >(rhs);
}


inline Imf_2_5_DeepScanLineInputPart * to_c(
    Imf_2_5::DeepScanLineInputPart & rhs)
{
    return reinterpret_cast<Imf_2_5_DeepScanLineInputPart * >(&(rhs));
}


inline Imf_2_5_DeepScanLineInputPart * to_c(
    Imf_2_5::DeepScanLineInputPart * rhs)
{
    return reinterpret_cast<Imf_2_5_DeepScanLineInputPart * >(rhs);
}
