#pragma once
#include <imf_io_.h>


#include <OpenEXR/ImfIO.h>
#include <cppmm_bind.hpp>







inline Imf_2_5::OStream const & to_cpp_ref(
    Imf_2_5_OStream const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::OStream const * >(rhs));
}


inline Imf_2_5::OStream & to_cpp_ref(
    Imf_2_5_OStream * rhs)
{
    return *(reinterpret_cast<Imf_2_5::OStream * >(rhs));
}


inline Imf_2_5::OStream const * to_cpp(
    Imf_2_5_OStream const * rhs)
{
    return reinterpret_cast<Imf_2_5::OStream const * >(rhs);
}


inline Imf_2_5::OStream * to_cpp(
    Imf_2_5_OStream * rhs)
{
    return reinterpret_cast<Imf_2_5::OStream * >(rhs);
}


inline Imf_2_5_OStream const * to_c(
    Imf_2_5::OStream const & rhs)
{
    return reinterpret_cast<Imf_2_5_OStream const * >(&(rhs));
}


inline Imf_2_5_OStream const * to_c(
    Imf_2_5::OStream const * rhs)
{
    return reinterpret_cast<Imf_2_5_OStream const * >(rhs);
}


inline Imf_2_5_OStream * to_c(
    Imf_2_5::OStream & rhs)
{
    return reinterpret_cast<Imf_2_5_OStream * >(&(rhs));
}


inline Imf_2_5_OStream * to_c(
    Imf_2_5::OStream * rhs)
{
    return reinterpret_cast<Imf_2_5_OStream * >(rhs);
}










inline Imf_2_5::IStream const & to_cpp_ref(
    Imf_2_5_IStream const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::IStream const * >(rhs));
}


inline Imf_2_5::IStream & to_cpp_ref(
    Imf_2_5_IStream * rhs)
{
    return *(reinterpret_cast<Imf_2_5::IStream * >(rhs));
}


inline Imf_2_5::IStream const * to_cpp(
    Imf_2_5_IStream const * rhs)
{
    return reinterpret_cast<Imf_2_5::IStream const * >(rhs);
}


inline Imf_2_5::IStream * to_cpp(
    Imf_2_5_IStream * rhs)
{
    return reinterpret_cast<Imf_2_5::IStream * >(rhs);
}


inline Imf_2_5_IStream const * to_c(
    Imf_2_5::IStream const & rhs)
{
    return reinterpret_cast<Imf_2_5_IStream const * >(&(rhs));
}


inline Imf_2_5_IStream const * to_c(
    Imf_2_5::IStream const * rhs)
{
    return reinterpret_cast<Imf_2_5_IStream const * >(rhs);
}


inline Imf_2_5_IStream * to_c(
    Imf_2_5::IStream & rhs)
{
    return reinterpret_cast<Imf_2_5_IStream * >(&(rhs));
}


inline Imf_2_5_IStream * to_c(
    Imf_2_5::IStream * rhs)
{
    return reinterpret_cast<Imf_2_5_IStream * >(rhs);
}
