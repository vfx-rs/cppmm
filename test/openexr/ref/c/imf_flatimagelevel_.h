#pragma once

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_FlatImageChannel_s Imf_2_5_FlatImageChannel;
typedef struct Imath_2_5_Box2i_s Imath_2_5_Box2i;
typedef struct Imf_2_5_Image_s Imf_2_5_Image;
typedef struct Imf_2_5_FlatImageLevel_s {
    char data[88];
} __attribute__((aligned(8))) Imf_2_5_FlatImageLevel;
typedef struct Imf_2_5_FlatImageLevel_Iterator_s {
    char data[8];
} __attribute__((aligned(8))) Imf_2_5_FlatImageLevel_Iterator;
typedef struct Imf_2_5_FlatImageLevel_ConstIterator_s {
    char data[8];
} __attribute__((aligned(8))) Imf_2_5_FlatImageLevel_ConstIterator;


Imf_2_5_Image * Imf_2_5_FlatImageLevel_image(
    Imf_2_5_FlatImageLevel * this_);


Imf_2_5_Image const * Imf_2_5_FlatImageLevel_image_1(
    Imf_2_5_FlatImageLevel const * this_);


int Imf_2_5_FlatImageLevel_xLevelNumber(
    Imf_2_5_FlatImageLevel const * this_);


int Imf_2_5_FlatImageLevel_yLevelNumber(
    Imf_2_5_FlatImageLevel const * this_);


Imath_2_5_Box2i const * Imf_2_5_FlatImageLevel_dataWindow(
    Imf_2_5_FlatImageLevel const * this_);


Imf_2_5_FlatImageLevel_Iterator Imf_2_5_FlatImageLevel_begin(
    Imf_2_5_FlatImageLevel * this_);


Imf_2_5_FlatImageLevel_ConstIterator Imf_2_5_FlatImageLevel_begin_1(
    Imf_2_5_FlatImageLevel const * this_);


Imf_2_5_FlatImageLevel_Iterator Imf_2_5_FlatImageLevel_end(
    Imf_2_5_FlatImageLevel * this_);


Imf_2_5_FlatImageLevel_ConstIterator Imf_2_5_FlatImageLevel_end_1(
    Imf_2_5_FlatImageLevel const * this_);










void Imf_2_5_FlatImageLevel_Iterator_Iterator(
    Imf_2_5_FlatImageLevel_Iterator * this_);


Imf_2_5_FlatImageLevel_Iterator * Imf_2_5_FlatImageLevel_Iterator__op_inc(
    Imf_2_5_FlatImageLevel_Iterator * this_);


Imf_2_5_FlatImageLevel_Iterator Imf_2_5_FlatImageLevel_Iterator__op_inc_1(
    Imf_2_5_FlatImageLevel_Iterator * this_
    , int );


Imf_2_5_FlatImageChannel * Imf_2_5_FlatImageLevel_Iterator_channel(
    Imf_2_5_FlatImageLevel_Iterator const * this_);


void Imf_2_5_FlatImageLevel_Iterator_Iterator_1(
    Imf_2_5_FlatImageLevel_Iterator * this_
    , Imf_2_5_FlatImageLevel_Iterator const * rhs);











void Imf_2_5_FlatImageLevel_ConstIterator_ConstIterator(
    Imf_2_5_FlatImageLevel_ConstIterator * this_);


Imf_2_5_FlatImageLevel_ConstIterator * Imf_2_5_FlatImageLevel_ConstIterator__op_inc(
    Imf_2_5_FlatImageLevel_ConstIterator * this_);


Imf_2_5_FlatImageLevel_ConstIterator Imf_2_5_FlatImageLevel_ConstIterator__op_inc_1(
    Imf_2_5_FlatImageLevel_ConstIterator * this_
    , int );


Imf_2_5_FlatImageChannel const * Imf_2_5_FlatImageLevel_ConstIterator_channel(
    Imf_2_5_FlatImageLevel_ConstIterator const * this_);


void Imf_2_5_FlatImageLevel_ConstIterator_ConstIterator_1(
    Imf_2_5_FlatImageLevel_ConstIterator * this_
    , Imf_2_5_FlatImageLevel_ConstIterator const * rhs);









#ifdef __cplusplus
}
#endif
