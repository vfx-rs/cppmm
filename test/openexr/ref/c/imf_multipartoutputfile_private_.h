#pragma once
#include <imf_multipartoutputfile_.h>


#include <OpenEXR/ImfMultiPartOutputFile.h>
#include <cppmm_bind.hpp>







inline Imf_2_5::MultiPartOutputFile const & to_cpp_ref(
    Imf_2_5_MultiPartOutputFile const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::MultiPartOutputFile const * >(rhs));
}


inline Imf_2_5::MultiPartOutputFile & to_cpp_ref(
    Imf_2_5_MultiPartOutputFile * rhs)
{
    return *(reinterpret_cast<Imf_2_5::MultiPartOutputFile * >(rhs));
}


inline Imf_2_5::MultiPartOutputFile const * to_cpp(
    Imf_2_5_MultiPartOutputFile const * rhs)
{
    return reinterpret_cast<Imf_2_5::MultiPartOutputFile const * >(rhs);
}


inline Imf_2_5::MultiPartOutputFile * to_cpp(
    Imf_2_5_MultiPartOutputFile * rhs)
{
    return reinterpret_cast<Imf_2_5::MultiPartOutputFile * >(rhs);
}


inline Imf_2_5_MultiPartOutputFile const * to_c(
    Imf_2_5::MultiPartOutputFile const & rhs)
{
    return reinterpret_cast<Imf_2_5_MultiPartOutputFile const * >(&(rhs));
}


inline Imf_2_5_MultiPartOutputFile const * to_c(
    Imf_2_5::MultiPartOutputFile const * rhs)
{
    return reinterpret_cast<Imf_2_5_MultiPartOutputFile const * >(rhs);
}


inline Imf_2_5_MultiPartOutputFile * to_c(
    Imf_2_5::MultiPartOutputFile & rhs)
{
    return reinterpret_cast<Imf_2_5_MultiPartOutputFile * >(&(rhs));
}


inline Imf_2_5_MultiPartOutputFile * to_c(
    Imf_2_5::MultiPartOutputFile * rhs)
{
    return reinterpret_cast<Imf_2_5_MultiPartOutputFile * >(rhs);
}
