#pragma once
#include <imf_parthelper_.h>


#include <OpenEXR/ImfPartHelper.h>
#include <cppmm_bind.hpp>


inline Imf_2_5::MultiViewChannelName const & to_cpp_ref(
    Imf_2_5_MultiViewChannelName const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::MultiViewChannelName const * >(rhs));
}


inline Imf_2_5::MultiViewChannelName & to_cpp_ref(
    Imf_2_5_MultiViewChannelName * rhs)
{
    return *(reinterpret_cast<Imf_2_5::MultiViewChannelName * >(rhs));
}


inline Imf_2_5::MultiViewChannelName const * to_cpp(
    Imf_2_5_MultiViewChannelName const * rhs)
{
    return reinterpret_cast<Imf_2_5::MultiViewChannelName const * >(rhs);
}


inline Imf_2_5::MultiViewChannelName * to_cpp(
    Imf_2_5_MultiViewChannelName * rhs)
{
    return reinterpret_cast<Imf_2_5::MultiViewChannelName * >(rhs);
}


inline Imf_2_5_MultiViewChannelName const * to_c(
    Imf_2_5::MultiViewChannelName const & rhs)
{
    return reinterpret_cast<Imf_2_5_MultiViewChannelName const * >(&(rhs));
}


inline Imf_2_5_MultiViewChannelName const * to_c(
    Imf_2_5::MultiViewChannelName const * rhs)
{
    return reinterpret_cast<Imf_2_5_MultiViewChannelName const * >(rhs);
}


inline Imf_2_5_MultiViewChannelName * to_c(
    Imf_2_5::MultiViewChannelName & rhs)
{
    return reinterpret_cast<Imf_2_5_MultiViewChannelName * >(&(rhs));
}


inline Imf_2_5_MultiViewChannelName * to_c(
    Imf_2_5::MultiViewChannelName * rhs)
{
    return reinterpret_cast<Imf_2_5_MultiViewChannelName * >(rhs);
}
