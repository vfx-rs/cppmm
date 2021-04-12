#pragma once
#include <imf_framebuffer_.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_DeepImageLevel_s Imf_2_5_DeepImageLevel;
typedef struct Imf_2_5_SampleCountChannel_s {
    char data[104];
} __attribute__((aligned(8))) Imf_2_5_SampleCountChannel;
typedef struct Imf_2_5_SampleCountChannel_Edit_s {
    char data[16];
} __attribute__((aligned(8))) Imf_2_5_SampleCountChannel_Edit;


Imf_2_5_Slice Imf_2_5_SampleCountChannel_slice(
    Imf_2_5_SampleCountChannel const * this_);


Imf_2_5_DeepImageLevel * Imf_2_5_SampleCountChannel_deepLevel(
    Imf_2_5_SampleCountChannel * this_);


Imf_2_5_DeepImageLevel const * Imf_2_5_SampleCountChannel_deepLevel_1(
    Imf_2_5_SampleCountChannel const * this_);


unsigned int const * Imf_2_5_SampleCountChannel_operator()(
    Imf_2_5_SampleCountChannel const * this_
    , int x
    , int y);


unsigned int const * Imf_2_5_SampleCountChannel_at(
    Imf_2_5_SampleCountChannel const * this_
    , int x
    , int y);


unsigned int const * Imf_2_5_SampleCountChannel_row(
    Imf_2_5_SampleCountChannel const * this_
    , int r);


void Imf_2_5_SampleCountChannel_set(
    Imf_2_5_SampleCountChannel * this_
    , int x
    , int y
    , unsigned int newNumSamples);


void Imf_2_5_SampleCountChannel_set_1(
    Imf_2_5_SampleCountChannel * this_
    , int r
    , unsigned int * newNumSamples);


void Imf_2_5_SampleCountChannel_clear(
    Imf_2_5_SampleCountChannel * this_);


unsigned int * Imf_2_5_SampleCountChannel_beginEdit(
    Imf_2_5_SampleCountChannel * this_);


void Imf_2_5_SampleCountChannel_endEdit(
    Imf_2_5_SampleCountChannel * this_);


unsigned int const * Imf_2_5_SampleCountChannel_numSamples(
    Imf_2_5_SampleCountChannel const * this_);


unsigned int const * Imf_2_5_SampleCountChannel_sampleListSizes(
    Imf_2_5_SampleCountChannel const * this_);


unsigned long const * Imf_2_5_SampleCountChannel_sampleListPositions(
    Imf_2_5_SampleCountChannel const * this_);


unsigned long Imf_2_5_SampleCountChannel_sampleBufferSize(
    Imf_2_5_SampleCountChannel const * this_);










void Imf_2_5_SampleCountChannel_Edit_Edit(
    Imf_2_5_SampleCountChannel_Edit * this_
    , Imf_2_5_SampleCountChannel * level);


void Imf_2_5_SampleCountChannel_Edit_dtor(
    Imf_2_5_SampleCountChannel_Edit * this_);


unsigned int * Imf_2_5_SampleCountChannel_Edit_sampleCounts(
    Imf_2_5_SampleCountChannel_Edit const * this_);








#ifdef __cplusplus
}
#endif
