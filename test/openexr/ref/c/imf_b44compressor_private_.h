#pragma once
#include <imf_b44compressor_.h>


#include <OpenEXR/ImfB44Compressor.h>
#include <cppmm_bind.hpp>









inline Imf_2_5::B44Compressor const & to_cpp_ref(
    Imf_2_5_B44Compressor const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::B44Compressor const * >(rhs));
}


inline Imf_2_5::B44Compressor & to_cpp_ref(
    Imf_2_5_B44Compressor * rhs)
{
    return *(reinterpret_cast<Imf_2_5::B44Compressor * >(rhs));
}


inline Imf_2_5::B44Compressor const * to_cpp(
    Imf_2_5_B44Compressor const * rhs)
{
    return reinterpret_cast<Imf_2_5::B44Compressor const * >(rhs);
}


inline Imf_2_5::B44Compressor * to_cpp(
    Imf_2_5_B44Compressor * rhs)
{
    return reinterpret_cast<Imf_2_5::B44Compressor * >(rhs);
}


inline Imf_2_5_B44Compressor const * to_c(
    Imf_2_5::B44Compressor const & rhs)
{
    return reinterpret_cast<Imf_2_5_B44Compressor const * >(&(rhs));
}


inline Imf_2_5_B44Compressor const * to_c(
    Imf_2_5::B44Compressor const * rhs)
{
    return reinterpret_cast<Imf_2_5_B44Compressor const * >(rhs);
}


inline Imf_2_5_B44Compressor * to_c(
    Imf_2_5::B44Compressor & rhs)
{
    return reinterpret_cast<Imf_2_5_B44Compressor * >(&(rhs));
}


inline Imf_2_5_B44Compressor * to_c(
    Imf_2_5::B44Compressor * rhs)
{
    return reinterpret_cast<Imf_2_5_B44Compressor * >(rhs);
}
