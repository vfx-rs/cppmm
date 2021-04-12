#pragma once
#include <imf_header_.h>


#include <OpenEXR/ImfHeader.h>
#include <cppmm_bind.hpp>
















































inline Imf_2_5::Header const & to_cpp_ref(
    Imf_2_5_Header const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::Header const * >(rhs));
}


inline Imf_2_5::Header & to_cpp_ref(
    Imf_2_5_Header * rhs)
{
    return *(reinterpret_cast<Imf_2_5::Header * >(rhs));
}


inline Imf_2_5::Header const * to_cpp(
    Imf_2_5_Header const * rhs)
{
    return reinterpret_cast<Imf_2_5::Header const * >(rhs);
}


inline Imf_2_5::Header * to_cpp(
    Imf_2_5_Header * rhs)
{
    return reinterpret_cast<Imf_2_5::Header * >(rhs);
}


inline Imf_2_5_Header const * to_c(
    Imf_2_5::Header const & rhs)
{
    return reinterpret_cast<Imf_2_5_Header const * >(&(rhs));
}


inline Imf_2_5_Header const * to_c(
    Imf_2_5::Header const * rhs)
{
    return reinterpret_cast<Imf_2_5_Header const * >(rhs);
}


inline Imf_2_5_Header * to_c(
    Imf_2_5::Header & rhs)
{
    return reinterpret_cast<Imf_2_5_Header * >(&(rhs));
}


inline Imf_2_5_Header * to_c(
    Imf_2_5::Header * rhs)
{
    return reinterpret_cast<Imf_2_5_Header * >(rhs);
}








inline Imf_2_5::Header::Iterator const & to_cpp_ref(
    Imf_2_5_Header_Iterator const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::Header::Iterator const * >(rhs));
}


inline Imf_2_5::Header::Iterator & to_cpp_ref(
    Imf_2_5_Header_Iterator * rhs)
{
    return *(reinterpret_cast<Imf_2_5::Header::Iterator * >(rhs));
}


inline Imf_2_5::Header::Iterator const * to_cpp(
    Imf_2_5_Header_Iterator const * rhs)
{
    return reinterpret_cast<Imf_2_5::Header::Iterator const * >(rhs);
}


inline Imf_2_5::Header::Iterator * to_cpp(
    Imf_2_5_Header_Iterator * rhs)
{
    return reinterpret_cast<Imf_2_5::Header::Iterator * >(rhs);
}


inline Imf_2_5_Header_Iterator const * to_c(
    Imf_2_5::Header::Iterator const & rhs)
{
    return reinterpret_cast<Imf_2_5_Header_Iterator const * >(&(rhs));
}


inline Imf_2_5_Header_Iterator const * to_c(
    Imf_2_5::Header::Iterator const * rhs)
{
    return reinterpret_cast<Imf_2_5_Header_Iterator const * >(rhs);
}


inline Imf_2_5_Header_Iterator * to_c(
    Imf_2_5::Header::Iterator & rhs)
{
    return reinterpret_cast<Imf_2_5_Header_Iterator * >(&(rhs));
}


inline Imf_2_5_Header_Iterator * to_c(
    Imf_2_5::Header::Iterator * rhs)
{
    return reinterpret_cast<Imf_2_5_Header_Iterator * >(rhs);
}


inline Imf_2_5_Header_Iterator to_c_copy(
    Imf_2_5::Header::Iterator const & rhs)
{
    Imf_2_5_Header_Iterator result;
    Imf_2_5_Header_Iterator_Iterator_1(&(result), reinterpret_cast<Imf_2_5_Header_Iterator const * >(&(rhs)));
    return result;
}







inline Imf_2_5::Header::ConstIterator const & to_cpp_ref(
    Imf_2_5_Header_ConstIterator const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::Header::ConstIterator const * >(rhs));
}


inline Imf_2_5::Header::ConstIterator & to_cpp_ref(
    Imf_2_5_Header_ConstIterator * rhs)
{
    return *(reinterpret_cast<Imf_2_5::Header::ConstIterator * >(rhs));
}


inline Imf_2_5::Header::ConstIterator const * to_cpp(
    Imf_2_5_Header_ConstIterator const * rhs)
{
    return reinterpret_cast<Imf_2_5::Header::ConstIterator const * >(rhs);
}


inline Imf_2_5::Header::ConstIterator * to_cpp(
    Imf_2_5_Header_ConstIterator * rhs)
{
    return reinterpret_cast<Imf_2_5::Header::ConstIterator * >(rhs);
}


inline Imf_2_5_Header_ConstIterator const * to_c(
    Imf_2_5::Header::ConstIterator const & rhs)
{
    return reinterpret_cast<Imf_2_5_Header_ConstIterator const * >(&(rhs));
}


inline Imf_2_5_Header_ConstIterator const * to_c(
    Imf_2_5::Header::ConstIterator const * rhs)
{
    return reinterpret_cast<Imf_2_5_Header_ConstIterator const * >(rhs);
}


inline Imf_2_5_Header_ConstIterator * to_c(
    Imf_2_5::Header::ConstIterator & rhs)
{
    return reinterpret_cast<Imf_2_5_Header_ConstIterator * >(&(rhs));
}


inline Imf_2_5_Header_ConstIterator * to_c(
    Imf_2_5::Header::ConstIterator * rhs)
{
    return reinterpret_cast<Imf_2_5_Header_ConstIterator * >(rhs);
}


inline Imf_2_5_Header_ConstIterator to_c_copy(
    Imf_2_5::Header::ConstIterator const & rhs)
{
    Imf_2_5_Header_ConstIterator result;
    Imf_2_5_Header_ConstIterator_ConstIterator_1(&(result), reinterpret_cast<Imf_2_5_Header_ConstIterator const * >(&(rhs)));
    return result;
}
