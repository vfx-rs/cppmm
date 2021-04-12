#pragma once
#include <imf_inputpart_.h>


#include <OpenEXR/ImfInputPart.h>
#include <cppmm_bind.hpp>















inline Imf_2_5::InputPart const & to_cpp_ref(
    Imf_2_5_InputPart const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::InputPart const * >(rhs));
}


inline Imf_2_5::InputPart & to_cpp_ref(
    Imf_2_5_InputPart * rhs)
{
    return *(reinterpret_cast<Imf_2_5::InputPart * >(rhs));
}


inline Imf_2_5::InputPart const * to_cpp(
    Imf_2_5_InputPart const * rhs)
{
    return reinterpret_cast<Imf_2_5::InputPart const * >(rhs);
}


inline Imf_2_5::InputPart * to_cpp(
    Imf_2_5_InputPart * rhs)
{
    return reinterpret_cast<Imf_2_5::InputPart * >(rhs);
}


inline Imf_2_5_InputPart const * to_c(
    Imf_2_5::InputPart const & rhs)
{
    return reinterpret_cast<Imf_2_5_InputPart const * >(&(rhs));
}


inline Imf_2_5_InputPart const * to_c(
    Imf_2_5::InputPart const * rhs)
{
    return reinterpret_cast<Imf_2_5_InputPart const * >(rhs);
}


inline Imf_2_5_InputPart * to_c(
    Imf_2_5::InputPart & rhs)
{
    return reinterpret_cast<Imf_2_5_InputPart * >(&(rhs));
}


inline Imf_2_5_InputPart * to_c(
    Imf_2_5::InputPart * rhs)
{
    return reinterpret_cast<Imf_2_5_InputPart * >(rhs);
}
