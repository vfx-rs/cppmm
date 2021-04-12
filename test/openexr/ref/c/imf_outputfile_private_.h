#pragma once
#include <imf_outputfile_.h>


#include <OpenEXR/ImfOutputFile.h>
#include <cppmm_bind.hpp>















inline Imf_2_5::OutputFile const & to_cpp_ref(
    Imf_2_5_OutputFile const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::OutputFile const * >(rhs));
}


inline Imf_2_5::OutputFile & to_cpp_ref(
    Imf_2_5_OutputFile * rhs)
{
    return *(reinterpret_cast<Imf_2_5::OutputFile * >(rhs));
}


inline Imf_2_5::OutputFile const * to_cpp(
    Imf_2_5_OutputFile const * rhs)
{
    return reinterpret_cast<Imf_2_5::OutputFile const * >(rhs);
}


inline Imf_2_5::OutputFile * to_cpp(
    Imf_2_5_OutputFile * rhs)
{
    return reinterpret_cast<Imf_2_5::OutputFile * >(rhs);
}


inline Imf_2_5_OutputFile const * to_c(
    Imf_2_5::OutputFile const & rhs)
{
    return reinterpret_cast<Imf_2_5_OutputFile const * >(&(rhs));
}


inline Imf_2_5_OutputFile const * to_c(
    Imf_2_5::OutputFile const * rhs)
{
    return reinterpret_cast<Imf_2_5_OutputFile const * >(rhs);
}


inline Imf_2_5_OutputFile * to_c(
    Imf_2_5::OutputFile & rhs)
{
    return reinterpret_cast<Imf_2_5_OutputFile * >(&(rhs));
}


inline Imf_2_5_OutputFile * to_c(
    Imf_2_5::OutputFile * rhs)
{
    return reinterpret_cast<Imf_2_5_OutputFile * >(rhs);
}
