#pragma once
#include <imf_multipartinputfile_.h>


#include <OpenEXR/ImfMultiPartInputFile.h>
#include <cppmm_bind.hpp>









inline Imf_2_5::MultiPartInputFile const & to_cpp_ref(
    Imf_2_5_MultiPartInputFile const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::MultiPartInputFile const * >(rhs));
}


inline Imf_2_5::MultiPartInputFile & to_cpp_ref(
    Imf_2_5_MultiPartInputFile * rhs)
{
    return *(reinterpret_cast<Imf_2_5::MultiPartInputFile * >(rhs));
}


inline Imf_2_5::MultiPartInputFile const * to_cpp(
    Imf_2_5_MultiPartInputFile const * rhs)
{
    return reinterpret_cast<Imf_2_5::MultiPartInputFile const * >(rhs);
}


inline Imf_2_5::MultiPartInputFile * to_cpp(
    Imf_2_5_MultiPartInputFile * rhs)
{
    return reinterpret_cast<Imf_2_5::MultiPartInputFile * >(rhs);
}


inline Imf_2_5_MultiPartInputFile const * to_c(
    Imf_2_5::MultiPartInputFile const & rhs)
{
    return reinterpret_cast<Imf_2_5_MultiPartInputFile const * >(&(rhs));
}


inline Imf_2_5_MultiPartInputFile const * to_c(
    Imf_2_5::MultiPartInputFile const * rhs)
{
    return reinterpret_cast<Imf_2_5_MultiPartInputFile const * >(rhs);
}


inline Imf_2_5_MultiPartInputFile * to_c(
    Imf_2_5::MultiPartInputFile & rhs)
{
    return reinterpret_cast<Imf_2_5_MultiPartInputFile * >(&(rhs));
}


inline Imf_2_5_MultiPartInputFile * to_c(
    Imf_2_5::MultiPartInputFile * rhs)
{
    return reinterpret_cast<Imf_2_5_MultiPartInputFile * >(rhs);
}
