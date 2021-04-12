#pragma once
#include <imf_channellist_.h>


#include <OpenEXR/ImfChannelList.h>
#include <cppmm_bind.hpp>




inline Imf_2_5::Channel const & to_cpp_ref(
    Imf_2_5_Channel const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::Channel const * >(rhs));
}


inline Imf_2_5::Channel & to_cpp_ref(
    Imf_2_5_Channel * rhs)
{
    return *(reinterpret_cast<Imf_2_5::Channel * >(rhs));
}


inline Imf_2_5::Channel const * to_cpp(
    Imf_2_5_Channel const * rhs)
{
    return reinterpret_cast<Imf_2_5::Channel const * >(rhs);
}


inline Imf_2_5::Channel * to_cpp(
    Imf_2_5_Channel * rhs)
{
    return reinterpret_cast<Imf_2_5::Channel * >(rhs);
}


inline Imf_2_5_Channel const * to_c(
    Imf_2_5::Channel const & rhs)
{
    return reinterpret_cast<Imf_2_5_Channel const * >(&(rhs));
}


inline Imf_2_5_Channel const * to_c(
    Imf_2_5::Channel const * rhs)
{
    return reinterpret_cast<Imf_2_5_Channel const * >(rhs);
}


inline Imf_2_5_Channel * to_c(
    Imf_2_5::Channel & rhs)
{
    return reinterpret_cast<Imf_2_5_Channel * >(&(rhs));
}


inline Imf_2_5_Channel * to_c(
    Imf_2_5::Channel * rhs)
{
    return reinterpret_cast<Imf_2_5_Channel * >(rhs);
}


inline Imf_2_5_Channel to_c_copy(
    Imf_2_5::Channel const & rhs)
{
    Imf_2_5_Channel result;
    Imf_2_5_Channel_Channel(&(result), reinterpret_cast<Imf_2_5_Channel const * >(&(rhs)));
    return result;
}















inline Imf_2_5::ChannelList const & to_cpp_ref(
    Imf_2_5_ChannelList const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::ChannelList const * >(rhs));
}


inline Imf_2_5::ChannelList & to_cpp_ref(
    Imf_2_5_ChannelList * rhs)
{
    return *(reinterpret_cast<Imf_2_5::ChannelList * >(rhs));
}


inline Imf_2_5::ChannelList const * to_cpp(
    Imf_2_5_ChannelList const * rhs)
{
    return reinterpret_cast<Imf_2_5::ChannelList const * >(rhs);
}


inline Imf_2_5::ChannelList * to_cpp(
    Imf_2_5_ChannelList * rhs)
{
    return reinterpret_cast<Imf_2_5::ChannelList * >(rhs);
}


inline Imf_2_5_ChannelList const * to_c(
    Imf_2_5::ChannelList const & rhs)
{
    return reinterpret_cast<Imf_2_5_ChannelList const * >(&(rhs));
}


inline Imf_2_5_ChannelList const * to_c(
    Imf_2_5::ChannelList const * rhs)
{
    return reinterpret_cast<Imf_2_5_ChannelList const * >(rhs);
}


inline Imf_2_5_ChannelList * to_c(
    Imf_2_5::ChannelList & rhs)
{
    return reinterpret_cast<Imf_2_5_ChannelList * >(&(rhs));
}


inline Imf_2_5_ChannelList * to_c(
    Imf_2_5::ChannelList * rhs)
{
    return reinterpret_cast<Imf_2_5_ChannelList * >(rhs);
}






inline Imf_2_5::ChannelList::Iterator const & to_cpp_ref(
    Imf_2_5_ChannelList_Iterator const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::ChannelList::Iterator const * >(rhs));
}


inline Imf_2_5::ChannelList::Iterator & to_cpp_ref(
    Imf_2_5_ChannelList_Iterator * rhs)
{
    return *(reinterpret_cast<Imf_2_5::ChannelList::Iterator * >(rhs));
}


inline Imf_2_5::ChannelList::Iterator const * to_cpp(
    Imf_2_5_ChannelList_Iterator const * rhs)
{
    return reinterpret_cast<Imf_2_5::ChannelList::Iterator const * >(rhs);
}


inline Imf_2_5::ChannelList::Iterator * to_cpp(
    Imf_2_5_ChannelList_Iterator * rhs)
{
    return reinterpret_cast<Imf_2_5::ChannelList::Iterator * >(rhs);
}


inline Imf_2_5_ChannelList_Iterator const * to_c(
    Imf_2_5::ChannelList::Iterator const & rhs)
{
    return reinterpret_cast<Imf_2_5_ChannelList_Iterator const * >(&(rhs));
}


inline Imf_2_5_ChannelList_Iterator const * to_c(
    Imf_2_5::ChannelList::Iterator const * rhs)
{
    return reinterpret_cast<Imf_2_5_ChannelList_Iterator const * >(rhs);
}


inline Imf_2_5_ChannelList_Iterator * to_c(
    Imf_2_5::ChannelList::Iterator & rhs)
{
    return reinterpret_cast<Imf_2_5_ChannelList_Iterator * >(&(rhs));
}


inline Imf_2_5_ChannelList_Iterator * to_c(
    Imf_2_5::ChannelList::Iterator * rhs)
{
    return reinterpret_cast<Imf_2_5_ChannelList_Iterator * >(rhs);
}


inline Imf_2_5_ChannelList_Iterator to_c_copy(
    Imf_2_5::ChannelList::Iterator const & rhs)
{
    Imf_2_5_ChannelList_Iterator result;
    Imf_2_5_ChannelList_Iterator_Iterator_1(&(result), reinterpret_cast<Imf_2_5_ChannelList_Iterator const * >(&(rhs)));
    return result;
}





inline Imf_2_5::ChannelList::ConstIterator const & to_cpp_ref(
    Imf_2_5_ChannelList_ConstIterator const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::ChannelList::ConstIterator const * >(rhs));
}


inline Imf_2_5::ChannelList::ConstIterator & to_cpp_ref(
    Imf_2_5_ChannelList_ConstIterator * rhs)
{
    return *(reinterpret_cast<Imf_2_5::ChannelList::ConstIterator * >(rhs));
}


inline Imf_2_5::ChannelList::ConstIterator const * to_cpp(
    Imf_2_5_ChannelList_ConstIterator const * rhs)
{
    return reinterpret_cast<Imf_2_5::ChannelList::ConstIterator const * >(rhs);
}


inline Imf_2_5::ChannelList::ConstIterator * to_cpp(
    Imf_2_5_ChannelList_ConstIterator * rhs)
{
    return reinterpret_cast<Imf_2_5::ChannelList::ConstIterator * >(rhs);
}


inline Imf_2_5_ChannelList_ConstIterator const * to_c(
    Imf_2_5::ChannelList::ConstIterator const & rhs)
{
    return reinterpret_cast<Imf_2_5_ChannelList_ConstIterator const * >(&(rhs));
}


inline Imf_2_5_ChannelList_ConstIterator const * to_c(
    Imf_2_5::ChannelList::ConstIterator const * rhs)
{
    return reinterpret_cast<Imf_2_5_ChannelList_ConstIterator const * >(rhs);
}


inline Imf_2_5_ChannelList_ConstIterator * to_c(
    Imf_2_5::ChannelList::ConstIterator & rhs)
{
    return reinterpret_cast<Imf_2_5_ChannelList_ConstIterator * >(&(rhs));
}


inline Imf_2_5_ChannelList_ConstIterator * to_c(
    Imf_2_5::ChannelList::ConstIterator * rhs)
{
    return reinterpret_cast<Imf_2_5_ChannelList_ConstIterator * >(rhs);
}


inline Imf_2_5_ChannelList_ConstIterator to_c_copy(
    Imf_2_5::ChannelList::ConstIterator const & rhs)
{
    Imf_2_5_ChannelList_ConstIterator result;
    Imf_2_5_ChannelList_ConstIterator_ConstIterator_1(&(result), reinterpret_cast<Imf_2_5_ChannelList_ConstIterator const * >(&(rhs)));
    return result;
}
