#include <imf_channellist_private_.h>

#include <new>


_Bool Imf_2_5_Channel__eq(
    Imf_2_5_Channel const * this_
    , Imf_2_5_Channel const * other)
{
    return (to_cpp(this_)) -> operator==(to_cpp_ref(other));
}

void Imf_2_5_Channel_Channel(
    Imf_2_5_Channel * this_
    , Imf_2_5_Channel const * rhs)
{
    new (this_) Imf_2_5::Channel(to_cpp_ref(rhs));
}

void Imf_2_5_ChannelList_insert(
    Imf_2_5_ChannelList * this_
    , char const * name
    , Imf_2_5_Channel const * channel)
{
    (to_cpp(this_)) -> insert(name, to_cpp_ref(channel));
}

Imf_2_5_Channel * Imf_2_5_ChannelList__index(
    Imf_2_5_ChannelList * this_
    , char const * name)
{
    return to_c((to_cpp(this_)) -> operator[](name));
}

Imf_2_5_Channel const * Imf_2_5_ChannelList__index_1(
    Imf_2_5_ChannelList const * this_
    , char const * name)
{
    return to_c((to_cpp(this_)) -> operator[](name));
}

Imf_2_5_Channel * Imf_2_5_ChannelList_findChannel(
    Imf_2_5_ChannelList * this_
    , char const * name)
{
    return to_c((to_cpp(this_)) -> findChannel(name));
}

Imf_2_5_Channel const * Imf_2_5_ChannelList_findChannel_1(
    Imf_2_5_ChannelList const * this_
    , char const * name)
{
    return to_c((to_cpp(this_)) -> findChannel(name));
}

Imf_2_5_ChannelList_Iterator Imf_2_5_ChannelList_begin(
    Imf_2_5_ChannelList * this_)
{
    return to_c_copy((to_cpp(this_)) -> begin());
}

Imf_2_5_ChannelList_ConstIterator Imf_2_5_ChannelList_begin_1(
    Imf_2_5_ChannelList const * this_)
{
    return to_c_copy((to_cpp(this_)) -> begin());
}

Imf_2_5_ChannelList_Iterator Imf_2_5_ChannelList_end(
    Imf_2_5_ChannelList * this_)
{
    return to_c_copy((to_cpp(this_)) -> end());
}

Imf_2_5_ChannelList_ConstIterator Imf_2_5_ChannelList_end_1(
    Imf_2_5_ChannelList const * this_)
{
    return to_c_copy((to_cpp(this_)) -> end());
}

Imf_2_5_ChannelList_Iterator Imf_2_5_ChannelList_find(
    Imf_2_5_ChannelList * this_
    , char const * name)
{
    return to_c_copy((to_cpp(this_)) -> find(name));
}

Imf_2_5_ChannelList_ConstIterator Imf_2_5_ChannelList_find_1(
    Imf_2_5_ChannelList const * this_
    , char const * name)
{
    return to_c_copy((to_cpp(this_)) -> find(name));
}

void Imf_2_5_ChannelList_channelsWithPrefix(
    Imf_2_5_ChannelList * this_
    , char const * prefix
    , Imf_2_5_ChannelList_Iterator * first
    , Imf_2_5_ChannelList_Iterator * last)
{
    (to_cpp(this_)) -> channelsWithPrefix(prefix, to_cpp_ref(first), to_cpp_ref(last));
}

void Imf_2_5_ChannelList_channelsWithPrefix_1(
    Imf_2_5_ChannelList const * this_
    , char const * prefix
    , Imf_2_5_ChannelList_ConstIterator * first
    , Imf_2_5_ChannelList_ConstIterator * last)
{
    (to_cpp(this_)) -> channelsWithPrefix(prefix, to_cpp_ref(first), to_cpp_ref(last));
}

void Imf_2_5_ChannelList_Iterator_Iterator(
    Imf_2_5_ChannelList_Iterator * this_)
{
    new (this_) Imf_2_5::ChannelList::Iterator();
}

char const * Imf_2_5_ChannelList_Iterator_name(
    Imf_2_5_ChannelList_Iterator const * this_)
{
    return (to_cpp(this_)) -> name();
}

Imf_2_5_Channel * Imf_2_5_ChannelList_Iterator_channel(
    Imf_2_5_ChannelList_Iterator const * this_)
{
    return to_c((to_cpp(this_)) -> channel());
}

void Imf_2_5_ChannelList_Iterator_Iterator_1(
    Imf_2_5_ChannelList_Iterator * this_
    , Imf_2_5_ChannelList_Iterator const * rhs)
{
    new (this_) Imf_2_5::ChannelList::Iterator(to_cpp_ref(rhs));
}

void Imf_2_5_ChannelList_ConstIterator_ConstIterator(
    Imf_2_5_ChannelList_ConstIterator * this_)
{
    new (this_) Imf_2_5::ChannelList::ConstIterator();
}

char const * Imf_2_5_ChannelList_ConstIterator_name(
    Imf_2_5_ChannelList_ConstIterator const * this_)
{
    return (to_cpp(this_)) -> name();
}

void Imf_2_5_ChannelList_ConstIterator_ConstIterator_1(
    Imf_2_5_ChannelList_ConstIterator * this_
    , Imf_2_5_ChannelList_ConstIterator const * rhs)
{
    new (this_) Imf_2_5::ChannelList::ConstIterator(to_cpp_ref(rhs));
}
