#pragma once
#include <imf_compressor_.h>


#include <OpenEXR/ImfCompressor.h>
#include <cppmm_bind.hpp>








inline Imf_2_5::Compressor const & to_cpp_ref(
    Imf_2_5_Compressor const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::Compressor const * >(rhs));
}


inline Imf_2_5::Compressor & to_cpp_ref(
    Imf_2_5_Compressor * rhs)
{
    return *(reinterpret_cast<Imf_2_5::Compressor * >(rhs));
}


inline Imf_2_5::Compressor const * to_cpp(
    Imf_2_5_Compressor const * rhs)
{
    return reinterpret_cast<Imf_2_5::Compressor const * >(rhs);
}


inline Imf_2_5::Compressor * to_cpp(
    Imf_2_5_Compressor * rhs)
{
    return reinterpret_cast<Imf_2_5::Compressor * >(rhs);
}


inline Imf_2_5_Compressor const * to_c(
    Imf_2_5::Compressor const & rhs)
{
    return reinterpret_cast<Imf_2_5_Compressor const * >(&(rhs));
}


inline Imf_2_5_Compressor const * to_c(
    Imf_2_5::Compressor const * rhs)
{
    return reinterpret_cast<Imf_2_5_Compressor const * >(rhs);
}


inline Imf_2_5_Compressor * to_c(
    Imf_2_5::Compressor & rhs)
{
    return reinterpret_cast<Imf_2_5_Compressor * >(&(rhs));
}


inline Imf_2_5_Compressor * to_c(
    Imf_2_5::Compressor * rhs)
{
    return reinterpret_cast<Imf_2_5_Compressor * >(rhs);
}
