#pragma once
#include <imf_inputfile_.h>


#include <OpenEXR/ImfInputFile.h>
#include <cppmm_bind.hpp>

















inline Imf_2_5::InputFile const & to_cpp_ref(
    Imf_2_5_InputFile const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::InputFile const * >(rhs));
}


inline Imf_2_5::InputFile & to_cpp_ref(
    Imf_2_5_InputFile * rhs)
{
    return *(reinterpret_cast<Imf_2_5::InputFile * >(rhs));
}


inline Imf_2_5::InputFile const * to_cpp(
    Imf_2_5_InputFile const * rhs)
{
    return reinterpret_cast<Imf_2_5::InputFile const * >(rhs);
}


inline Imf_2_5::InputFile * to_cpp(
    Imf_2_5_InputFile * rhs)
{
    return reinterpret_cast<Imf_2_5::InputFile * >(rhs);
}


inline Imf_2_5_InputFile const * to_c(
    Imf_2_5::InputFile const & rhs)
{
    return reinterpret_cast<Imf_2_5_InputFile const * >(&(rhs));
}


inline Imf_2_5_InputFile const * to_c(
    Imf_2_5::InputFile const * rhs)
{
    return reinterpret_cast<Imf_2_5_InputFile const * >(rhs);
}


inline Imf_2_5_InputFile * to_c(
    Imf_2_5::InputFile & rhs)
{
    return reinterpret_cast<Imf_2_5_InputFile * >(&(rhs));
}


inline Imf_2_5_InputFile * to_c(
    Imf_2_5::InputFile * rhs)
{
    return reinterpret_cast<Imf_2_5_InputFile * >(rhs);
}
