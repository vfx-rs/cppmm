#pragma once

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_DeepCompositing_s {
    char data[8];
} __attribute__((aligned(8))) Imf_2_5_DeepCompositing;


void Imf_2_5_DeepCompositing_DeepCompositing(
    Imf_2_5_DeepCompositing * this_);


void Imf_2_5_DeepCompositing_dtor(
    Imf_2_5_DeepCompositing * this_);


void Imf_2_5_DeepCompositing_composite_pixel(
    Imf_2_5_DeepCompositing * this_
    , float * outputs
    , float const * * inputs
    , char const * * channel_names
    , int num_channels
    , int num_samples
    , int sources);


void Imf_2_5_DeepCompositing_sort(
    Imf_2_5_DeepCompositing * this_
    , int * order
    , float const * * inputs
    , char const * * channel_names
    , int num_channels
    , int num_samples
    , int sources);








#ifdef __cplusplus
}
#endif
