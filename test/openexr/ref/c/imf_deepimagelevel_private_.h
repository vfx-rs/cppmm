#pragma once
#include <imf_deepimagelevel_.h>


#include <OpenEXR/ImfDeepImageLevel.h>
#include <cppmm_bind.hpp>















inline Imf_2_5::DeepImageLevel const & to_cpp_ref(
    Imf_2_5_DeepImageLevel const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::DeepImageLevel const * >(rhs));
}


inline Imf_2_5::DeepImageLevel & to_cpp_ref(
    Imf_2_5_DeepImageLevel * rhs)
{
    return *(reinterpret_cast<Imf_2_5::DeepImageLevel * >(rhs));
}


inline Imf_2_5::DeepImageLevel const * to_cpp(
    Imf_2_5_DeepImageLevel const * rhs)
{
    return reinterpret_cast<Imf_2_5::DeepImageLevel const * >(rhs);
}


inline Imf_2_5::DeepImageLevel * to_cpp(
    Imf_2_5_DeepImageLevel * rhs)
{
    return reinterpret_cast<Imf_2_5::DeepImageLevel * >(rhs);
}


inline Imf_2_5_DeepImageLevel const * to_c(
    Imf_2_5::DeepImageLevel const & rhs)
{
    return reinterpret_cast<Imf_2_5_DeepImageLevel const * >(&(rhs));
}


inline Imf_2_5_DeepImageLevel const * to_c(
    Imf_2_5::DeepImageLevel const * rhs)
{
    return reinterpret_cast<Imf_2_5_DeepImageLevel const * >(rhs);
}


inline Imf_2_5_DeepImageLevel * to_c(
    Imf_2_5::DeepImageLevel & rhs)
{
    return reinterpret_cast<Imf_2_5_DeepImageLevel * >(&(rhs));
}


inline Imf_2_5_DeepImageLevel * to_c(
    Imf_2_5::DeepImageLevel * rhs)
{
    return reinterpret_cast<Imf_2_5_DeepImageLevel * >(rhs);
}







inline Imf_2_5::DeepImageLevel::Iterator const & to_cpp_ref(
    Imf_2_5_DeepImageLevel_Iterator const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::DeepImageLevel::Iterator const * >(rhs));
}


inline Imf_2_5::DeepImageLevel::Iterator & to_cpp_ref(
    Imf_2_5_DeepImageLevel_Iterator * rhs)
{
    return *(reinterpret_cast<Imf_2_5::DeepImageLevel::Iterator * >(rhs));
}


inline Imf_2_5::DeepImageLevel::Iterator const * to_cpp(
    Imf_2_5_DeepImageLevel_Iterator const * rhs)
{
    return reinterpret_cast<Imf_2_5::DeepImageLevel::Iterator const * >(rhs);
}


inline Imf_2_5::DeepImageLevel::Iterator * to_cpp(
    Imf_2_5_DeepImageLevel_Iterator * rhs)
{
    return reinterpret_cast<Imf_2_5::DeepImageLevel::Iterator * >(rhs);
}


inline Imf_2_5_DeepImageLevel_Iterator const * to_c(
    Imf_2_5::DeepImageLevel::Iterator const & rhs)
{
    return reinterpret_cast<Imf_2_5_DeepImageLevel_Iterator const * >(&(rhs));
}


inline Imf_2_5_DeepImageLevel_Iterator const * to_c(
    Imf_2_5::DeepImageLevel::Iterator const * rhs)
{
    return reinterpret_cast<Imf_2_5_DeepImageLevel_Iterator const * >(rhs);
}


inline Imf_2_5_DeepImageLevel_Iterator * to_c(
    Imf_2_5::DeepImageLevel::Iterator & rhs)
{
    return reinterpret_cast<Imf_2_5_DeepImageLevel_Iterator * >(&(rhs));
}


inline Imf_2_5_DeepImageLevel_Iterator * to_c(
    Imf_2_5::DeepImageLevel::Iterator * rhs)
{
    return reinterpret_cast<Imf_2_5_DeepImageLevel_Iterator * >(rhs);
}


inline Imf_2_5_DeepImageLevel_Iterator to_c_copy(
    Imf_2_5::DeepImageLevel::Iterator const & rhs)
{
    Imf_2_5_DeepImageLevel_Iterator result;
    Imf_2_5_DeepImageLevel_Iterator_Iterator_1(&(result), reinterpret_cast<Imf_2_5_DeepImageLevel_Iterator const * >(&(rhs)));
    return result;
}







inline Imf_2_5::DeepImageLevel::ConstIterator const & to_cpp_ref(
    Imf_2_5_DeepImageLevel_ConstIterator const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::DeepImageLevel::ConstIterator const * >(rhs));
}


inline Imf_2_5::DeepImageLevel::ConstIterator & to_cpp_ref(
    Imf_2_5_DeepImageLevel_ConstIterator * rhs)
{
    return *(reinterpret_cast<Imf_2_5::DeepImageLevel::ConstIterator * >(rhs));
}


inline Imf_2_5::DeepImageLevel::ConstIterator const * to_cpp(
    Imf_2_5_DeepImageLevel_ConstIterator const * rhs)
{
    return reinterpret_cast<Imf_2_5::DeepImageLevel::ConstIterator const * >(rhs);
}


inline Imf_2_5::DeepImageLevel::ConstIterator * to_cpp(
    Imf_2_5_DeepImageLevel_ConstIterator * rhs)
{
    return reinterpret_cast<Imf_2_5::DeepImageLevel::ConstIterator * >(rhs);
}


inline Imf_2_5_DeepImageLevel_ConstIterator const * to_c(
    Imf_2_5::DeepImageLevel::ConstIterator const & rhs)
{
    return reinterpret_cast<Imf_2_5_DeepImageLevel_ConstIterator const * >(&(rhs));
}


inline Imf_2_5_DeepImageLevel_ConstIterator const * to_c(
    Imf_2_5::DeepImageLevel::ConstIterator const * rhs)
{
    return reinterpret_cast<Imf_2_5_DeepImageLevel_ConstIterator const * >(rhs);
}


inline Imf_2_5_DeepImageLevel_ConstIterator * to_c(
    Imf_2_5::DeepImageLevel::ConstIterator & rhs)
{
    return reinterpret_cast<Imf_2_5_DeepImageLevel_ConstIterator * >(&(rhs));
}


inline Imf_2_5_DeepImageLevel_ConstIterator * to_c(
    Imf_2_5::DeepImageLevel::ConstIterator * rhs)
{
    return reinterpret_cast<Imf_2_5_DeepImageLevel_ConstIterator * >(rhs);
}


inline Imf_2_5_DeepImageLevel_ConstIterator to_c_copy(
    Imf_2_5::DeepImageLevel::ConstIterator const & rhs)
{
    Imf_2_5_DeepImageLevel_ConstIterator result;
    Imf_2_5_DeepImageLevel_ConstIterator_ConstIterator_1(&(result), reinterpret_cast<Imf_2_5_DeepImageLevel_ConstIterator const * >(&(rhs)));
    return result;
}
