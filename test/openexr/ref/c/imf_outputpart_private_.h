#pragma once
#include <imf_outputpart_.h>


#include <OpenEXR/ImfOutputPart.h>
#include <cppmm_bind.hpp>













inline Imf_2_5::OutputPart const & to_cpp_ref(
    Imf_2_5_OutputPart const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::OutputPart const * >(rhs));
}


inline Imf_2_5::OutputPart & to_cpp_ref(
    Imf_2_5_OutputPart * rhs)
{
    return *(reinterpret_cast<Imf_2_5::OutputPart * >(rhs));
}


inline Imf_2_5::OutputPart const * to_cpp(
    Imf_2_5_OutputPart const * rhs)
{
    return reinterpret_cast<Imf_2_5::OutputPart const * >(rhs);
}


inline Imf_2_5::OutputPart * to_cpp(
    Imf_2_5_OutputPart * rhs)
{
    return reinterpret_cast<Imf_2_5::OutputPart * >(rhs);
}


inline Imf_2_5_OutputPart const * to_c(
    Imf_2_5::OutputPart const & rhs)
{
    return reinterpret_cast<Imf_2_5_OutputPart const * >(&(rhs));
}


inline Imf_2_5_OutputPart const * to_c(
    Imf_2_5::OutputPart const * rhs)
{
    return reinterpret_cast<Imf_2_5_OutputPart const * >(rhs);
}


inline Imf_2_5_OutputPart * to_c(
    Imf_2_5::OutputPart & rhs)
{
    return reinterpret_cast<Imf_2_5_OutputPart * >(&(rhs));
}


inline Imf_2_5_OutputPart * to_c(
    Imf_2_5::OutputPart * rhs)
{
    return reinterpret_cast<Imf_2_5_OutputPart * >(rhs);
}
