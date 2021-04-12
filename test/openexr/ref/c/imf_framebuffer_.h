#pragma once

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_Slice_s {
    char data[56];
} __attribute__((aligned(8))) Imf_2_5_Slice;
typedef struct Imf_2_5_FrameBuffer_s {
    char data[48];
} __attribute__((aligned(8))) Imf_2_5_FrameBuffer;
typedef struct Imf_2_5_FrameBuffer_Iterator_s {
    char data[8];
} __attribute__((aligned(8))) Imf_2_5_FrameBuffer_Iterator;
typedef struct Imf_2_5_FrameBuffer_ConstIterator_s {
    char data[8];
} __attribute__((aligned(8))) Imf_2_5_FrameBuffer_ConstIterator;


void Imf_2_5_Slice_Slice(
    Imf_2_5_Slice * this_
    , Imf_2_5_Slice const * rhs);











void Imf_2_5_FrameBuffer_insert(
    Imf_2_5_FrameBuffer * this_
    , char const * name
    , Imf_2_5_Slice const * slice);


Imf_2_5_Slice * Imf_2_5_FrameBuffer__index(
    Imf_2_5_FrameBuffer * this_
    , char const * name);


Imf_2_5_Slice const * Imf_2_5_FrameBuffer__index_1(
    Imf_2_5_FrameBuffer const * this_
    , char const * name);


Imf_2_5_Slice * Imf_2_5_FrameBuffer_findSlice(
    Imf_2_5_FrameBuffer * this_
    , char const * name);


Imf_2_5_Slice const * Imf_2_5_FrameBuffer_findSlice_1(
    Imf_2_5_FrameBuffer const * this_
    , char const * name);


Imf_2_5_FrameBuffer_Iterator Imf_2_5_FrameBuffer_begin(
    Imf_2_5_FrameBuffer * this_);


Imf_2_5_FrameBuffer_ConstIterator Imf_2_5_FrameBuffer_begin_1(
    Imf_2_5_FrameBuffer const * this_);


Imf_2_5_FrameBuffer_Iterator Imf_2_5_FrameBuffer_end(
    Imf_2_5_FrameBuffer * this_);


Imf_2_5_FrameBuffer_ConstIterator Imf_2_5_FrameBuffer_end_1(
    Imf_2_5_FrameBuffer const * this_);


Imf_2_5_FrameBuffer_Iterator Imf_2_5_FrameBuffer_find(
    Imf_2_5_FrameBuffer * this_
    , char const * name);


Imf_2_5_FrameBuffer_ConstIterator Imf_2_5_FrameBuffer_find_1(
    Imf_2_5_FrameBuffer const * this_
    , char const * name);










void Imf_2_5_FrameBuffer_Iterator_Iterator(
    Imf_2_5_FrameBuffer_Iterator * this_);


char const * Imf_2_5_FrameBuffer_Iterator_name(
    Imf_2_5_FrameBuffer_Iterator const * this_);


Imf_2_5_Slice * Imf_2_5_FrameBuffer_Iterator_slice(
    Imf_2_5_FrameBuffer_Iterator const * this_);


void Imf_2_5_FrameBuffer_Iterator_Iterator_1(
    Imf_2_5_FrameBuffer_Iterator * this_
    , Imf_2_5_FrameBuffer_Iterator const * rhs);











void Imf_2_5_FrameBuffer_ConstIterator_ConstIterator(
    Imf_2_5_FrameBuffer_ConstIterator * this_);


char const * Imf_2_5_FrameBuffer_ConstIterator_name(
    Imf_2_5_FrameBuffer_ConstIterator const * this_);


void Imf_2_5_FrameBuffer_ConstIterator_ConstIterator_1(
    Imf_2_5_FrameBuffer_ConstIterator * this_
    , Imf_2_5_FrameBuffer_ConstIterator const * rhs);









#ifdef __cplusplus
}
#endif
