#pragma once
#include <imf_compositedeepscanline_.h>


#include <OpenEXR/ImfCompositeDeepScanLine.h>
#include <cppmm_bind.hpp>












inline Imf_2_5::CompositeDeepScanLine const & to_cpp_ref(
    Imf_2_5_CompositeDeepScanLine const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::CompositeDeepScanLine const * >(rhs));
}


inline Imf_2_5::CompositeDeepScanLine & to_cpp_ref(
    Imf_2_5_CompositeDeepScanLine * rhs)
{
    return *(reinterpret_cast<Imf_2_5::CompositeDeepScanLine * >(rhs));
}


inline Imf_2_5::CompositeDeepScanLine const * to_cpp(
    Imf_2_5_CompositeDeepScanLine const * rhs)
{
    return reinterpret_cast<Imf_2_5::CompositeDeepScanLine const * >(rhs);
}


inline Imf_2_5::CompositeDeepScanLine * to_cpp(
    Imf_2_5_CompositeDeepScanLine * rhs)
{
    return reinterpret_cast<Imf_2_5::CompositeDeepScanLine * >(rhs);
}


inline Imf_2_5_CompositeDeepScanLine const * to_c(
    Imf_2_5::CompositeDeepScanLine const & rhs)
{
    return reinterpret_cast<Imf_2_5_CompositeDeepScanLine const * >(&(rhs));
}


inline Imf_2_5_CompositeDeepScanLine const * to_c(
    Imf_2_5::CompositeDeepScanLine const * rhs)
{
    return reinterpret_cast<Imf_2_5_CompositeDeepScanLine const * >(rhs);
}


inline Imf_2_5_CompositeDeepScanLine * to_c(
    Imf_2_5::CompositeDeepScanLine & rhs)
{
    return reinterpret_cast<Imf_2_5_CompositeDeepScanLine * >(&(rhs));
}


inline Imf_2_5_CompositeDeepScanLine * to_c(
    Imf_2_5::CompositeDeepScanLine * rhs)
{
    return reinterpret_cast<Imf_2_5_CompositeDeepScanLine * >(rhs);
}
