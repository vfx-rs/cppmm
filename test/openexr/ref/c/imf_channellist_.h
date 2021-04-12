#pragma once
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_Channel_s {
    char data[16];
} __attribute__((aligned(4))) Imf_2_5_Channel;
typedef struct Imf_2_5_ChannelList_s {
    char data[48];
} __attribute__((aligned(8))) Imf_2_5_ChannelList;
typedef struct Imf_2_5_ChannelList_Iterator_s {
    char data[8];
} __attribute__((aligned(8))) Imf_2_5_ChannelList_Iterator;
typedef struct Imf_2_5_ChannelList_ConstIterator_s {
    char data[8];
} __attribute__((aligned(8))) Imf_2_5_ChannelList_ConstIterator;


_Bool Imf_2_5_Channel__eq(
    Imf_2_5_Channel const * this_
    , Imf_2_5_Channel const * other);


void Imf_2_5_Channel_Channel(
    Imf_2_5_Channel * this_
    , Imf_2_5_Channel const * rhs);











void Imf_2_5_ChannelList_insert(
    Imf_2_5_ChannelList * this_
    , char const * name
    , Imf_2_5_Channel const * channel);


Imf_2_5_Channel * Imf_2_5_ChannelList__index(
    Imf_2_5_ChannelList * this_
    , char const * name);


Imf_2_5_Channel const * Imf_2_5_ChannelList__index_1(
    Imf_2_5_ChannelList const * this_
    , char const * name);


Imf_2_5_Channel * Imf_2_5_ChannelList_findChannel(
    Imf_2_5_ChannelList * this_
    , char const * name);


Imf_2_5_Channel const * Imf_2_5_ChannelList_findChannel_1(
    Imf_2_5_ChannelList const * this_
    , char const * name);


Imf_2_5_ChannelList_Iterator Imf_2_5_ChannelList_begin(
    Imf_2_5_ChannelList * this_);


Imf_2_5_ChannelList_ConstIterator Imf_2_5_ChannelList_begin_1(
    Imf_2_5_ChannelList const * this_);


Imf_2_5_ChannelList_Iterator Imf_2_5_ChannelList_end(
    Imf_2_5_ChannelList * this_);


Imf_2_5_ChannelList_ConstIterator Imf_2_5_ChannelList_end_1(
    Imf_2_5_ChannelList const * this_);


Imf_2_5_ChannelList_Iterator Imf_2_5_ChannelList_find(
    Imf_2_5_ChannelList * this_
    , char const * name);


Imf_2_5_ChannelList_ConstIterator Imf_2_5_ChannelList_find_1(
    Imf_2_5_ChannelList const * this_
    , char const * name);


void Imf_2_5_ChannelList_channelsWithPrefix(
    Imf_2_5_ChannelList * this_
    , char const * prefix
    , Imf_2_5_ChannelList_Iterator * first
    , Imf_2_5_ChannelList_Iterator * last);


void Imf_2_5_ChannelList_channelsWithPrefix_1(
    Imf_2_5_ChannelList const * this_
    , char const * prefix
    , Imf_2_5_ChannelList_ConstIterator * first
    , Imf_2_5_ChannelList_ConstIterator * last);










void Imf_2_5_ChannelList_Iterator_Iterator(
    Imf_2_5_ChannelList_Iterator * this_);


char const * Imf_2_5_ChannelList_Iterator_name(
    Imf_2_5_ChannelList_Iterator const * this_);


Imf_2_5_Channel * Imf_2_5_ChannelList_Iterator_channel(
    Imf_2_5_ChannelList_Iterator const * this_);


void Imf_2_5_ChannelList_Iterator_Iterator_1(
    Imf_2_5_ChannelList_Iterator * this_
    , Imf_2_5_ChannelList_Iterator const * rhs);











void Imf_2_5_ChannelList_ConstIterator_ConstIterator(
    Imf_2_5_ChannelList_ConstIterator * this_);


char const * Imf_2_5_ChannelList_ConstIterator_name(
    Imf_2_5_ChannelList_ConstIterator const * this_);


void Imf_2_5_ChannelList_ConstIterator_ConstIterator_1(
    Imf_2_5_ChannelList_ConstIterator * this_
    , Imf_2_5_ChannelList_ConstIterator const * rhs);









#ifdef __cplusplus
}
#endif
