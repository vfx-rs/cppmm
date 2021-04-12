#pragma once

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_SampleCountChannel_s Imf_2_5_SampleCountChannel;
typedef struct Imf_2_5_DeepImage_s Imf_2_5_DeepImage;
typedef struct Imath_2_5_Box2i_s Imath_2_5_Box2i;
typedef struct Imf_2_5_DeepImageChannel_s Imf_2_5_DeepImageChannel;
typedef struct Imf_2_5_Image_s Imf_2_5_Image;
typedef struct Imf_2_5_DeepImageLevel_s {
    char data[192];
} __attribute__((aligned(8))) Imf_2_5_DeepImageLevel;
typedef struct Imf_2_5_DeepImageLevel_Iterator_s {
    char data[8];
} __attribute__((aligned(8))) Imf_2_5_DeepImageLevel_Iterator;
typedef struct Imf_2_5_DeepImageLevel_ConstIterator_s {
    char data[8];
} __attribute__((aligned(8))) Imf_2_5_DeepImageLevel_ConstIterator;


Imf_2_5_Image * Imf_2_5_DeepImageLevel_image(
    Imf_2_5_DeepImageLevel * this_);


Imf_2_5_Image const * Imf_2_5_DeepImageLevel_image_1(
    Imf_2_5_DeepImageLevel const * this_);


int Imf_2_5_DeepImageLevel_xLevelNumber(
    Imf_2_5_DeepImageLevel const * this_);


int Imf_2_5_DeepImageLevel_yLevelNumber(
    Imf_2_5_DeepImageLevel const * this_);


Imath_2_5_Box2i const * Imf_2_5_DeepImageLevel_dataWindow(
    Imf_2_5_DeepImageLevel const * this_);


Imf_2_5_DeepImage * Imf_2_5_DeepImageLevel_deepImage(
    Imf_2_5_DeepImageLevel * this_);


Imf_2_5_DeepImage const * Imf_2_5_DeepImageLevel_deepImage_1(
    Imf_2_5_DeepImageLevel const * this_);


Imf_2_5_DeepImageLevel_Iterator Imf_2_5_DeepImageLevel_begin(
    Imf_2_5_DeepImageLevel * this_);


Imf_2_5_DeepImageLevel_ConstIterator Imf_2_5_DeepImageLevel_begin_1(
    Imf_2_5_DeepImageLevel const * this_);


Imf_2_5_DeepImageLevel_Iterator Imf_2_5_DeepImageLevel_end(
    Imf_2_5_DeepImageLevel * this_);


Imf_2_5_DeepImageLevel_ConstIterator Imf_2_5_DeepImageLevel_end_1(
    Imf_2_5_DeepImageLevel const * this_);


Imf_2_5_SampleCountChannel * Imf_2_5_DeepImageLevel_sampleCounts(
    Imf_2_5_DeepImageLevel * this_);


Imf_2_5_SampleCountChannel const * Imf_2_5_DeepImageLevel_sampleCounts_1(
    Imf_2_5_DeepImageLevel const * this_);










void Imf_2_5_DeepImageLevel_Iterator_Iterator(
    Imf_2_5_DeepImageLevel_Iterator * this_);


Imf_2_5_DeepImageLevel_Iterator * Imf_2_5_DeepImageLevel_Iterator__op_inc(
    Imf_2_5_DeepImageLevel_Iterator * this_);


Imf_2_5_DeepImageLevel_Iterator Imf_2_5_DeepImageLevel_Iterator__op_inc_1(
    Imf_2_5_DeepImageLevel_Iterator * this_
    , int );


Imf_2_5_DeepImageChannel * Imf_2_5_DeepImageLevel_Iterator_channel(
    Imf_2_5_DeepImageLevel_Iterator const * this_);


void Imf_2_5_DeepImageLevel_Iterator_Iterator_1(
    Imf_2_5_DeepImageLevel_Iterator * this_
    , Imf_2_5_DeepImageLevel_Iterator const * rhs);











void Imf_2_5_DeepImageLevel_ConstIterator_ConstIterator(
    Imf_2_5_DeepImageLevel_ConstIterator * this_);


Imf_2_5_DeepImageLevel_ConstIterator * Imf_2_5_DeepImageLevel_ConstIterator__op_inc(
    Imf_2_5_DeepImageLevel_ConstIterator * this_);


Imf_2_5_DeepImageLevel_ConstIterator Imf_2_5_DeepImageLevel_ConstIterator__op_inc_1(
    Imf_2_5_DeepImageLevel_ConstIterator * this_
    , int );


Imf_2_5_DeepImageChannel const * Imf_2_5_DeepImageLevel_ConstIterator_channel(
    Imf_2_5_DeepImageLevel_ConstIterator const * this_);


void Imf_2_5_DeepImageLevel_ConstIterator_ConstIterator_1(
    Imf_2_5_DeepImageLevel_ConstIterator * this_
    , Imf_2_5_DeepImageLevel_ConstIterator const * rhs);









#ifdef __cplusplus
}
#endif
