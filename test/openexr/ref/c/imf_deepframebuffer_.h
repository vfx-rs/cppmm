#pragma once

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_Slice_s Imf_2_5_Slice;
typedef struct Imf_2_5_DeepSlice_s {
    char data[56];
} __attribute__((aligned(8))) Imf_2_5_DeepSlice;
typedef struct Imf_2_5_DeepFrameBuffer_s {
    char data[104];
} __attribute__((aligned(8))) Imf_2_5_DeepFrameBuffer;
typedef struct Imf_2_5_DeepFrameBuffer_Iterator_s {
    char data[8];
} __attribute__((aligned(8))) Imf_2_5_DeepFrameBuffer_Iterator;
typedef struct Imf_2_5_DeepFrameBuffer_ConstIterator_s {
    char data[8];
} __attribute__((aligned(8))) Imf_2_5_DeepFrameBuffer_ConstIterator;


void Imf_2_5_DeepSlice_DeepSlice(
    Imf_2_5_DeepSlice * this_
    , Imf_2_5_DeepSlice const * rhs);











void Imf_2_5_DeepFrameBuffer_insert(
    Imf_2_5_DeepFrameBuffer * this_
    , char const * name
    , Imf_2_5_DeepSlice const * slice);


Imf_2_5_DeepSlice * Imf_2_5_DeepFrameBuffer__index(
    Imf_2_5_DeepFrameBuffer * this_
    , char const * name);


Imf_2_5_DeepSlice const * Imf_2_5_DeepFrameBuffer__index_1(
    Imf_2_5_DeepFrameBuffer const * this_
    , char const * name);


Imf_2_5_DeepSlice * Imf_2_5_DeepFrameBuffer_findSlice(
    Imf_2_5_DeepFrameBuffer * this_
    , char const * name);


Imf_2_5_DeepSlice const * Imf_2_5_DeepFrameBuffer_findSlice_1(
    Imf_2_5_DeepFrameBuffer const * this_
    , char const * name);


Imf_2_5_DeepFrameBuffer_Iterator Imf_2_5_DeepFrameBuffer_begin(
    Imf_2_5_DeepFrameBuffer * this_);


Imf_2_5_DeepFrameBuffer_ConstIterator Imf_2_5_DeepFrameBuffer_begin_1(
    Imf_2_5_DeepFrameBuffer const * this_);


Imf_2_5_DeepFrameBuffer_Iterator Imf_2_5_DeepFrameBuffer_end(
    Imf_2_5_DeepFrameBuffer * this_);


Imf_2_5_DeepFrameBuffer_ConstIterator Imf_2_5_DeepFrameBuffer_end_1(
    Imf_2_5_DeepFrameBuffer const * this_);


Imf_2_5_DeepFrameBuffer_Iterator Imf_2_5_DeepFrameBuffer_find(
    Imf_2_5_DeepFrameBuffer * this_
    , char const * name);


Imf_2_5_DeepFrameBuffer_ConstIterator Imf_2_5_DeepFrameBuffer_find_1(
    Imf_2_5_DeepFrameBuffer const * this_
    , char const * name);


void Imf_2_5_DeepFrameBuffer_insertSampleCountSlice(
    Imf_2_5_DeepFrameBuffer * this_
    , Imf_2_5_Slice const * slice);


Imf_2_5_Slice const * Imf_2_5_DeepFrameBuffer_getSampleCountSlice(
    Imf_2_5_DeepFrameBuffer const * this_);










void Imf_2_5_DeepFrameBuffer_Iterator_Iterator(
    Imf_2_5_DeepFrameBuffer_Iterator * this_);


char const * Imf_2_5_DeepFrameBuffer_Iterator_name(
    Imf_2_5_DeepFrameBuffer_Iterator const * this_);


Imf_2_5_DeepSlice * Imf_2_5_DeepFrameBuffer_Iterator_slice(
    Imf_2_5_DeepFrameBuffer_Iterator const * this_);


void Imf_2_5_DeepFrameBuffer_Iterator_Iterator_1(
    Imf_2_5_DeepFrameBuffer_Iterator * this_
    , Imf_2_5_DeepFrameBuffer_Iterator const * rhs);











void Imf_2_5_DeepFrameBuffer_ConstIterator_ConstIterator(
    Imf_2_5_DeepFrameBuffer_ConstIterator * this_);


char const * Imf_2_5_DeepFrameBuffer_ConstIterator_name(
    Imf_2_5_DeepFrameBuffer_ConstIterator const * this_);


void Imf_2_5_DeepFrameBuffer_ConstIterator_ConstIterator_1(
    Imf_2_5_DeepFrameBuffer_ConstIterator * this_
    , Imf_2_5_DeepFrameBuffer_ConstIterator const * rhs);









#ifdef __cplusplus
}
#endif
