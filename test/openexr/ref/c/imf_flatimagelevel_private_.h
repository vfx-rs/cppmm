#pragma once
#include <imf_flatimagelevel_.h>


#include <OpenEXR/ImfFlatImageLevel.h>
#include <cppmm_bind.hpp>











inline Imf_2_5::FlatImageLevel const & to_cpp_ref(
    Imf_2_5_FlatImageLevel const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::FlatImageLevel const * >(rhs));
}


inline Imf_2_5::FlatImageLevel & to_cpp_ref(
    Imf_2_5_FlatImageLevel * rhs)
{
    return *(reinterpret_cast<Imf_2_5::FlatImageLevel * >(rhs));
}


inline Imf_2_5::FlatImageLevel const * to_cpp(
    Imf_2_5_FlatImageLevel const * rhs)
{
    return reinterpret_cast<Imf_2_5::FlatImageLevel const * >(rhs);
}


inline Imf_2_5::FlatImageLevel * to_cpp(
    Imf_2_5_FlatImageLevel * rhs)
{
    return reinterpret_cast<Imf_2_5::FlatImageLevel * >(rhs);
}


inline Imf_2_5_FlatImageLevel const * to_c(
    Imf_2_5::FlatImageLevel const & rhs)
{
    return reinterpret_cast<Imf_2_5_FlatImageLevel const * >(&(rhs));
}


inline Imf_2_5_FlatImageLevel const * to_c(
    Imf_2_5::FlatImageLevel const * rhs)
{
    return reinterpret_cast<Imf_2_5_FlatImageLevel const * >(rhs);
}


inline Imf_2_5_FlatImageLevel * to_c(
    Imf_2_5::FlatImageLevel & rhs)
{
    return reinterpret_cast<Imf_2_5_FlatImageLevel * >(&(rhs));
}


inline Imf_2_5_FlatImageLevel * to_c(
    Imf_2_5::FlatImageLevel * rhs)
{
    return reinterpret_cast<Imf_2_5_FlatImageLevel * >(rhs);
}







inline Imf_2_5::FlatImageLevel::Iterator const & to_cpp_ref(
    Imf_2_5_FlatImageLevel_Iterator const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::FlatImageLevel::Iterator const * >(rhs));
}


inline Imf_2_5::FlatImageLevel::Iterator & to_cpp_ref(
    Imf_2_5_FlatImageLevel_Iterator * rhs)
{
    return *(reinterpret_cast<Imf_2_5::FlatImageLevel::Iterator * >(rhs));
}


inline Imf_2_5::FlatImageLevel::Iterator const * to_cpp(
    Imf_2_5_FlatImageLevel_Iterator const * rhs)
{
    return reinterpret_cast<Imf_2_5::FlatImageLevel::Iterator const * >(rhs);
}


inline Imf_2_5::FlatImageLevel::Iterator * to_cpp(
    Imf_2_5_FlatImageLevel_Iterator * rhs)
{
    return reinterpret_cast<Imf_2_5::FlatImageLevel::Iterator * >(rhs);
}


inline Imf_2_5_FlatImageLevel_Iterator const * to_c(
    Imf_2_5::FlatImageLevel::Iterator const & rhs)
{
    return reinterpret_cast<Imf_2_5_FlatImageLevel_Iterator const * >(&(rhs));
}


inline Imf_2_5_FlatImageLevel_Iterator const * to_c(
    Imf_2_5::FlatImageLevel::Iterator const * rhs)
{
    return reinterpret_cast<Imf_2_5_FlatImageLevel_Iterator const * >(rhs);
}


inline Imf_2_5_FlatImageLevel_Iterator * to_c(
    Imf_2_5::FlatImageLevel::Iterator & rhs)
{
    return reinterpret_cast<Imf_2_5_FlatImageLevel_Iterator * >(&(rhs));
}


inline Imf_2_5_FlatImageLevel_Iterator * to_c(
    Imf_2_5::FlatImageLevel::Iterator * rhs)
{
    return reinterpret_cast<Imf_2_5_FlatImageLevel_Iterator * >(rhs);
}


inline Imf_2_5_FlatImageLevel_Iterator to_c_copy(
    Imf_2_5::FlatImageLevel::Iterator const & rhs)
{
    Imf_2_5_FlatImageLevel_Iterator result;
    Imf_2_5_FlatImageLevel_Iterator_Iterator_1(&(result), reinterpret_cast<Imf_2_5_FlatImageLevel_Iterator const * >(&(rhs)));
    return result;
}







inline Imf_2_5::FlatImageLevel::ConstIterator const & to_cpp_ref(
    Imf_2_5_FlatImageLevel_ConstIterator const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::FlatImageLevel::ConstIterator const * >(rhs));
}


inline Imf_2_5::FlatImageLevel::ConstIterator & to_cpp_ref(
    Imf_2_5_FlatImageLevel_ConstIterator * rhs)
{
    return *(reinterpret_cast<Imf_2_5::FlatImageLevel::ConstIterator * >(rhs));
}


inline Imf_2_5::FlatImageLevel::ConstIterator const * to_cpp(
    Imf_2_5_FlatImageLevel_ConstIterator const * rhs)
{
    return reinterpret_cast<Imf_2_5::FlatImageLevel::ConstIterator const * >(rhs);
}


inline Imf_2_5::FlatImageLevel::ConstIterator * to_cpp(
    Imf_2_5_FlatImageLevel_ConstIterator * rhs)
{
    return reinterpret_cast<Imf_2_5::FlatImageLevel::ConstIterator * >(rhs);
}


inline Imf_2_5_FlatImageLevel_ConstIterator const * to_c(
    Imf_2_5::FlatImageLevel::ConstIterator const & rhs)
{
    return reinterpret_cast<Imf_2_5_FlatImageLevel_ConstIterator const * >(&(rhs));
}


inline Imf_2_5_FlatImageLevel_ConstIterator const * to_c(
    Imf_2_5::FlatImageLevel::ConstIterator const * rhs)
{
    return reinterpret_cast<Imf_2_5_FlatImageLevel_ConstIterator const * >(rhs);
}


inline Imf_2_5_FlatImageLevel_ConstIterator * to_c(
    Imf_2_5::FlatImageLevel::ConstIterator & rhs)
{
    return reinterpret_cast<Imf_2_5_FlatImageLevel_ConstIterator * >(&(rhs));
}


inline Imf_2_5_FlatImageLevel_ConstIterator * to_c(
    Imf_2_5::FlatImageLevel::ConstIterator * rhs)
{
    return reinterpret_cast<Imf_2_5_FlatImageLevel_ConstIterator * >(rhs);
}


inline Imf_2_5_FlatImageLevel_ConstIterator to_c_copy(
    Imf_2_5::FlatImageLevel::ConstIterator const & rhs)
{
    Imf_2_5_FlatImageLevel_ConstIterator result;
    Imf_2_5_FlatImageLevel_ConstIterator_ConstIterator_1(&(result), reinterpret_cast<Imf_2_5_FlatImageLevel_ConstIterator const * >(&(rhs)));
    return result;
}
