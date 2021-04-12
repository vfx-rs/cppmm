#pragma once
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_TileDescription_s Imf_2_5_TileDescription;
typedef struct Imf_2_5_PreviewImage_s Imf_2_5_PreviewImage;
typedef struct Imath_2_5_Box2i_s Imath_2_5_Box2i;
typedef struct Imath_2_5_V2f_s Imath_2_5_V2f;
typedef struct Imf_2_5_OStream_s Imf_2_5_OStream;
typedef struct Imf_2_5_IStream_s Imf_2_5_IStream;
typedef struct Imf_2_5_Attribute_s Imf_2_5_Attribute;
typedef struct Imf_2_5_ChannelList_s Imf_2_5_ChannelList;
typedef struct Imf_2_5_Header_s {
    char data[56];
} __attribute__((aligned(8))) Imf_2_5_Header;
typedef struct Imf_2_5_Header_Iterator_s {
    char data[8];
} __attribute__((aligned(8))) Imf_2_5_Header_Iterator;
typedef struct Imf_2_5_Header_ConstIterator_s {
    char data[8];
} __attribute__((aligned(8))) Imf_2_5_Header_ConstIterator;


void Imf_2_5_Header_dtor(
    Imf_2_5_Header * this_);


void Imf_2_5_Header_insert(
    Imf_2_5_Header * this_
    , char const * name
    , Imf_2_5_Attribute const * attribute);


void Imf_2_5_Header_erase(
    Imf_2_5_Header * this_
    , char const * name);


Imf_2_5_Attribute * Imf_2_5_Header__index(
    Imf_2_5_Header * this_
    , char const * name);


Imf_2_5_Attribute const * Imf_2_5_Header__index_1(
    Imf_2_5_Header const * this_
    , char const * name);


Imf_2_5_Header_Iterator Imf_2_5_Header_begin(
    Imf_2_5_Header * this_);


Imf_2_5_Header_ConstIterator Imf_2_5_Header_begin_1(
    Imf_2_5_Header const * this_);


Imf_2_5_Header_Iterator Imf_2_5_Header_end(
    Imf_2_5_Header * this_);


Imf_2_5_Header_ConstIterator Imf_2_5_Header_end_1(
    Imf_2_5_Header const * this_);


Imf_2_5_Header_Iterator Imf_2_5_Header_find(
    Imf_2_5_Header * this_
    , char const * name);


Imf_2_5_Header_ConstIterator Imf_2_5_Header_find_1(
    Imf_2_5_Header const * this_
    , char const * name);


Imath_2_5_Box2i * Imf_2_5_Header_displayWindow(
    Imf_2_5_Header * this_);


Imath_2_5_Box2i const * Imf_2_5_Header_displayWindow_1(
    Imf_2_5_Header const * this_);


Imath_2_5_Box2i * Imf_2_5_Header_dataWindow(
    Imf_2_5_Header * this_);


Imath_2_5_Box2i const * Imf_2_5_Header_dataWindow_1(
    Imf_2_5_Header const * this_);


float * Imf_2_5_Header_pixelAspectRatio(
    Imf_2_5_Header * this_);


float const * Imf_2_5_Header_pixelAspectRatio_1(
    Imf_2_5_Header const * this_);


Imath_2_5_V2f * Imf_2_5_Header_screenWindowCenter(
    Imf_2_5_Header * this_);


Imath_2_5_V2f const * Imf_2_5_Header_screenWindowCenter_1(
    Imf_2_5_Header const * this_);


float * Imf_2_5_Header_screenWindowWidth(
    Imf_2_5_Header * this_);


float const * Imf_2_5_Header_screenWindowWidth_1(
    Imf_2_5_Header const * this_);


Imf_2_5_ChannelList * Imf_2_5_Header_channels(
    Imf_2_5_Header * this_);


Imf_2_5_ChannelList const * Imf_2_5_Header_channels_1(
    Imf_2_5_Header const * this_);


_Bool Imf_2_5_Header_hasName(
    Imf_2_5_Header const * this_);


_Bool Imf_2_5_Header_hasType(
    Imf_2_5_Header const * this_);


void Imf_2_5_Header_setVersion(
    Imf_2_5_Header * this_
    , int const version);


int * Imf_2_5_Header_version(
    Imf_2_5_Header * this_);


int const * Imf_2_5_Header_version_1(
    Imf_2_5_Header const * this_);


_Bool Imf_2_5_Header_hasVersion(
    Imf_2_5_Header const * this_);


void Imf_2_5_Header_setChunkCount(
    Imf_2_5_Header * this_
    , int chunks);


_Bool Imf_2_5_Header_hasChunkCount(
    Imf_2_5_Header const * this_);


int const * Imf_2_5_Header_chunkCount(
    Imf_2_5_Header const * this_);


int * Imf_2_5_Header_chunkCount_1(
    Imf_2_5_Header * this_);


_Bool Imf_2_5_Header_hasView(
    Imf_2_5_Header const * this_);


void Imf_2_5_Header_setTileDescription(
    Imf_2_5_Header * this_
    , Imf_2_5_TileDescription const * td);


Imf_2_5_TileDescription * Imf_2_5_Header_tileDescription(
    Imf_2_5_Header * this_);


Imf_2_5_TileDescription const * Imf_2_5_Header_tileDescription_1(
    Imf_2_5_Header const * this_);


_Bool Imf_2_5_Header_hasTileDescription(
    Imf_2_5_Header const * this_);


void Imf_2_5_Header_setPreviewImage(
    Imf_2_5_Header * this_
    , Imf_2_5_PreviewImage const * p);


Imf_2_5_PreviewImage * Imf_2_5_Header_previewImage(
    Imf_2_5_Header * this_);


Imf_2_5_PreviewImage const * Imf_2_5_Header_previewImage_1(
    Imf_2_5_Header const * this_);


_Bool Imf_2_5_Header_hasPreviewImage(
    Imf_2_5_Header const * this_);


void Imf_2_5_Header_sanityCheck(
    Imf_2_5_Header const * this_
    , _Bool isTiled
    , _Bool isMultipartFile);


_Bool Imf_2_5_Header_readsNothing(
    Imf_2_5_Header * this_);


unsigned long Imf_2_5_Header_writeTo(
    Imf_2_5_Header const * this_
    , Imf_2_5_OStream * os
    , _Bool isTiled);


void Imf_2_5_Header_readFrom(
    Imf_2_5_Header * this_
    , Imf_2_5_IStream * is
    , int * version);










void Imf_2_5_Header_Iterator_Iterator(
    Imf_2_5_Header_Iterator * this_);


Imf_2_5_Header_Iterator * Imf_2_5_Header_Iterator__op_inc(
    Imf_2_5_Header_Iterator * this_);


Imf_2_5_Header_Iterator Imf_2_5_Header_Iterator__op_inc_1(
    Imf_2_5_Header_Iterator * this_
    , int );


char const * Imf_2_5_Header_Iterator_name(
    Imf_2_5_Header_Iterator const * this_);


Imf_2_5_Attribute * Imf_2_5_Header_Iterator_attribute(
    Imf_2_5_Header_Iterator const * this_);


void Imf_2_5_Header_Iterator_Iterator_1(
    Imf_2_5_Header_Iterator * this_
    , Imf_2_5_Header_Iterator const * rhs);











void Imf_2_5_Header_ConstIterator_ConstIterator(
    Imf_2_5_Header_ConstIterator * this_);


Imf_2_5_Header_ConstIterator * Imf_2_5_Header_ConstIterator__op_inc(
    Imf_2_5_Header_ConstIterator * this_);


Imf_2_5_Header_ConstIterator Imf_2_5_Header_ConstIterator__op_inc_1(
    Imf_2_5_Header_ConstIterator * this_
    , int );


char const * Imf_2_5_Header_ConstIterator_name(
    Imf_2_5_Header_ConstIterator const * this_);


void Imf_2_5_Header_ConstIterator_ConstIterator_1(
    Imf_2_5_Header_ConstIterator * this_
    , Imf_2_5_Header_ConstIterator const * rhs);









#ifdef __cplusplus
}
#endif
