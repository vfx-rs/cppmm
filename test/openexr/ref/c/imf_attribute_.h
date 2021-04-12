#pragma once

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_KeyCode_s Imf_2_5_KeyCode;
typedef struct Imf_2_5_TileDescription_s Imf_2_5_TileDescription;
typedef struct Imf_2_5_Rational_s Imf_2_5_Rational;
typedef struct Imf_2_5_PreviewImage_s Imf_2_5_PreviewImage;
typedef struct Imath_2_5_V3f_s Imath_2_5_V3f;
typedef struct Imath_2_5_V3i_s Imath_2_5_V3i;
typedef struct Imath_2_5_V3d_s Imath_2_5_V3d;
typedef struct Imath_2_5_V2i_s Imath_2_5_V2i;
typedef struct Imath_2_5_V2d_s Imath_2_5_V2d;
typedef struct Imf_2_5_TimeCode_s Imf_2_5_TimeCode;
typedef struct Imath_2_5_Box2i_s Imath_2_5_Box2i;
typedef struct Imath_2_5_V2f_s Imath_2_5_V2f;
typedef struct Imf_2_5_OStream_s Imf_2_5_OStream;
typedef struct Imf_2_5_IStream_s Imf_2_5_IStream;
typedef struct Imath_2_5_M33f_s Imath_2_5_M33f;
typedef struct Imath_2_5_M33d_s Imath_2_5_M33d;
typedef struct Imath_2_5_M44f_s Imath_2_5_M44f;
typedef struct Imath_2_5_M44d_s Imath_2_5_M44d;
typedef struct Imf_2_5_ChannelList_s Imf_2_5_ChannelList;
typedef struct Imf_2_5_Chromaticities_s Imf_2_5_Chromaticities;
typedef struct Imath_2_5_Box2f_s Imath_2_5_Box2f;
typedef struct Imf_2_5_Attribute_s {
    char data[8];
} __attribute__((aligned(8))) Imf_2_5_Attribute;
typedef struct Imf_2_5_IntAttribute_s {
    char data[16];
} __attribute__((aligned(8))) Imf_2_5_IntAttribute;
typedef struct Imf_2_5_FloatAttribute_s {
    char data[16];
} __attribute__((aligned(8))) Imf_2_5_FloatAttribute;
typedef struct Imf_2_5_DoubleAttribute_s {
    char data[16];
} __attribute__((aligned(8))) Imf_2_5_DoubleAttribute;
typedef struct Imf_2_5_Box2iAttribute_s {
    char data[24];
} __attribute__((aligned(8))) Imf_2_5_Box2iAttribute;
typedef struct Imf_2_5_Box2fAttribute_s {
    char data[24];
} __attribute__((aligned(8))) Imf_2_5_Box2fAttribute;
typedef struct Imf_2_5_ChannelListAttribute_s {
    char data[56];
} __attribute__((aligned(8))) Imf_2_5_ChannelListAttribute;
typedef struct Imf_2_5_ChromaticitiesAttribute_s {
    char data[40];
} __attribute__((aligned(8))) Imf_2_5_ChromaticitiesAttribute;
typedef struct Imf_2_5_CompressionAttribute_s {
    char data[16];
} __attribute__((aligned(8))) Imf_2_5_CompressionAttribute;
typedef struct Imf_2_5_DeepImageStateAttribute_s {
    char data[16];
} __attribute__((aligned(8))) Imf_2_5_DeepImageStateAttribute;
typedef struct Imf_2_5_EnvmapAttribute_s {
    char data[16];
} __attribute__((aligned(8))) Imf_2_5_EnvmapAttribute;
typedef struct Imf_2_5_FloatVectorAttribute_s {
    char data[32];
} __attribute__((aligned(8))) Imf_2_5_FloatVectorAttribute;
typedef struct Imf_2_5_StringVectorAttribute_s {
    char data[32];
} __attribute__((aligned(8))) Imf_2_5_StringVectorAttribute;
typedef struct Imf_2_5_StringAttribute_s {
    char data[40];
} __attribute__((aligned(8))) Imf_2_5_StringAttribute;
typedef struct Imf_2_5_KeyCodeAttribute_s {
    char data[40];
} __attribute__((aligned(8))) Imf_2_5_KeyCodeAttribute;
typedef struct Imf_2_5_LineOrderAttribute_s {
    char data[16];
} __attribute__((aligned(8))) Imf_2_5_LineOrderAttribute;
typedef struct Imf_2_5_M33fAttribute_s {
    char data[48];
} __attribute__((aligned(8))) Imf_2_5_M33fAttribute;
typedef struct Imf_2_5_M33dAttribute_s {
    char data[80];
} __attribute__((aligned(8))) Imf_2_5_M33dAttribute;
typedef struct Imf_2_5_M44fAttribute_s {
    char data[72];
} __attribute__((aligned(8))) Imf_2_5_M44fAttribute;
typedef struct Imf_2_5_M44dAttribute_s {
    char data[136];
} __attribute__((aligned(8))) Imf_2_5_M44dAttribute;
typedef struct Imf_2_5_PreviewImageAttribute_s {
    char data[24];
} __attribute__((aligned(8))) Imf_2_5_PreviewImageAttribute;
typedef struct Imf_2_5_RationalAttribute_s {
    char data[16];
} __attribute__((aligned(8))) Imf_2_5_RationalAttribute;
typedef struct Imf_2_5_TileDescriptionAttribute_s {
    char data[24];
} __attribute__((aligned(8))) Imf_2_5_TileDescriptionAttribute;
typedef struct Imf_2_5_TimeCodeAttribute_s {
    char data[16];
} __attribute__((aligned(8))) Imf_2_5_TimeCodeAttribute;
typedef struct Imf_2_5_V2iAttribute_s {
    char data[16];
} __attribute__((aligned(8))) Imf_2_5_V2iAttribute;
typedef struct Imf_2_5_V2fAttribute_s {
    char data[16];
} __attribute__((aligned(8))) Imf_2_5_V2fAttribute;
typedef struct Imf_2_5_V2dAttribute_s {
    char data[24];
} __attribute__((aligned(8))) Imf_2_5_V2dAttribute;
typedef struct Imf_2_5_V3iAttribute_s {
    char data[24];
} __attribute__((aligned(8))) Imf_2_5_V3iAttribute;
typedef struct Imf_2_5_V3fAttribute_s {
    char data[24];
} __attribute__((aligned(8))) Imf_2_5_V3fAttribute;
typedef struct Imf_2_5_V3dAttribute_s {
    char data[32];
} __attribute__((aligned(8))) Imf_2_5_V3dAttribute;
typedef struct std_vector_s {
    char data[24];
} __attribute__((aligned(8))) std_vector;


void Imf_2_5_Attribute_dtor(
    Imf_2_5_Attribute * this_);


char const * Imf_2_5_Attribute_typeName(
    Imf_2_5_Attribute const * this_);


Imf_2_5_Attribute * Imf_2_5_Attribute_copy(
    Imf_2_5_Attribute const * this_);


void Imf_2_5_Attribute_writeValueTo(
    Imf_2_5_Attribute const * this_
    , Imf_2_5_OStream * os
    , int version);


void Imf_2_5_Attribute_readValueFrom(
    Imf_2_5_Attribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version);


void Imf_2_5_Attribute_copyValueFrom(
    Imf_2_5_Attribute * this_
    , Imf_2_5_Attribute const * other);










char const * Imf_2_5_IntAttribute_typeName(
    Imf_2_5_IntAttribute const * this_);


Imf_2_5_Attribute * Imf_2_5_IntAttribute_copy(
    Imf_2_5_IntAttribute const * this_);


void Imf_2_5_IntAttribute_writeValueTo(
    Imf_2_5_IntAttribute const * this_
    , Imf_2_5_OStream * os
    , int version);


void Imf_2_5_IntAttribute_readValueFrom(
    Imf_2_5_IntAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version);


void Imf_2_5_IntAttribute_copyValueFrom(
    Imf_2_5_IntAttribute * this_
    , Imf_2_5_Attribute const * other);


void Imf_2_5_IntAttribute_TypedAttribute(
    Imf_2_5_IntAttribute * this_);


void Imf_2_5_IntAttribute_TypedAttribute_1(
    Imf_2_5_IntAttribute * this_
    , int const * value);


void Imf_2_5_IntAttribute_dtor(
    Imf_2_5_IntAttribute * this_);


int * Imf_2_5_IntAttribute_value(
    Imf_2_5_IntAttribute * this_);


int const * Imf_2_5_IntAttribute_value_1(
    Imf_2_5_IntAttribute const * this_);










char const * Imf_2_5_FloatAttribute_typeName(
    Imf_2_5_FloatAttribute const * this_);


Imf_2_5_Attribute * Imf_2_5_FloatAttribute_copy(
    Imf_2_5_FloatAttribute const * this_);


void Imf_2_5_FloatAttribute_writeValueTo(
    Imf_2_5_FloatAttribute const * this_
    , Imf_2_5_OStream * os
    , int version);


void Imf_2_5_FloatAttribute_readValueFrom(
    Imf_2_5_FloatAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version);


void Imf_2_5_FloatAttribute_copyValueFrom(
    Imf_2_5_FloatAttribute * this_
    , Imf_2_5_Attribute const * other);


void Imf_2_5_FloatAttribute_TypedAttribute(
    Imf_2_5_FloatAttribute * this_);


void Imf_2_5_FloatAttribute_TypedAttribute_1(
    Imf_2_5_FloatAttribute * this_
    , float const * value);


void Imf_2_5_FloatAttribute_dtor(
    Imf_2_5_FloatAttribute * this_);


float * Imf_2_5_FloatAttribute_value(
    Imf_2_5_FloatAttribute * this_);


float const * Imf_2_5_FloatAttribute_value_1(
    Imf_2_5_FloatAttribute const * this_);










char const * Imf_2_5_DoubleAttribute_typeName(
    Imf_2_5_DoubleAttribute const * this_);


Imf_2_5_Attribute * Imf_2_5_DoubleAttribute_copy(
    Imf_2_5_DoubleAttribute const * this_);


void Imf_2_5_DoubleAttribute_writeValueTo(
    Imf_2_5_DoubleAttribute const * this_
    , Imf_2_5_OStream * os
    , int version);


void Imf_2_5_DoubleAttribute_readValueFrom(
    Imf_2_5_DoubleAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version);


void Imf_2_5_DoubleAttribute_copyValueFrom(
    Imf_2_5_DoubleAttribute * this_
    , Imf_2_5_Attribute const * other);


void Imf_2_5_DoubleAttribute_TypedAttribute(
    Imf_2_5_DoubleAttribute * this_);


void Imf_2_5_DoubleAttribute_TypedAttribute_1(
    Imf_2_5_DoubleAttribute * this_
    , double const * value);


void Imf_2_5_DoubleAttribute_dtor(
    Imf_2_5_DoubleAttribute * this_);


double * Imf_2_5_DoubleAttribute_value(
    Imf_2_5_DoubleAttribute * this_);


double const * Imf_2_5_DoubleAttribute_value_1(
    Imf_2_5_DoubleAttribute const * this_);










char const * Imf_2_5_Box2iAttribute_typeName(
    Imf_2_5_Box2iAttribute const * this_);


Imf_2_5_Attribute * Imf_2_5_Box2iAttribute_copy(
    Imf_2_5_Box2iAttribute const * this_);


void Imf_2_5_Box2iAttribute_writeValueTo(
    Imf_2_5_Box2iAttribute const * this_
    , Imf_2_5_OStream * os
    , int version);


void Imf_2_5_Box2iAttribute_readValueFrom(
    Imf_2_5_Box2iAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version);


void Imf_2_5_Box2iAttribute_copyValueFrom(
    Imf_2_5_Box2iAttribute * this_
    , Imf_2_5_Attribute const * other);


void Imf_2_5_Box2iAttribute_TypedAttribute(
    Imf_2_5_Box2iAttribute * this_);


void Imf_2_5_Box2iAttribute_TypedAttribute_1(
    Imf_2_5_Box2iAttribute * this_
    , Imath_2_5_Box2i const * value);


void Imf_2_5_Box2iAttribute_dtor(
    Imf_2_5_Box2iAttribute * this_);


Imath_2_5_Box2i * Imf_2_5_Box2iAttribute_value(
    Imf_2_5_Box2iAttribute * this_);


Imath_2_5_Box2i const * Imf_2_5_Box2iAttribute_value_1(
    Imf_2_5_Box2iAttribute const * this_);










char const * Imf_2_5_Box2fAttribute_typeName(
    Imf_2_5_Box2fAttribute const * this_);


Imf_2_5_Attribute * Imf_2_5_Box2fAttribute_copy(
    Imf_2_5_Box2fAttribute const * this_);


void Imf_2_5_Box2fAttribute_writeValueTo(
    Imf_2_5_Box2fAttribute const * this_
    , Imf_2_5_OStream * os
    , int version);


void Imf_2_5_Box2fAttribute_readValueFrom(
    Imf_2_5_Box2fAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version);


void Imf_2_5_Box2fAttribute_copyValueFrom(
    Imf_2_5_Box2fAttribute * this_
    , Imf_2_5_Attribute const * other);


void Imf_2_5_Box2fAttribute_TypedAttribute(
    Imf_2_5_Box2fAttribute * this_);


void Imf_2_5_Box2fAttribute_TypedAttribute_1(
    Imf_2_5_Box2fAttribute * this_
    , Imath_2_5_Box2f const * value);


void Imf_2_5_Box2fAttribute_dtor(
    Imf_2_5_Box2fAttribute * this_);


Imath_2_5_Box2f * Imf_2_5_Box2fAttribute_value(
    Imf_2_5_Box2fAttribute * this_);


Imath_2_5_Box2f const * Imf_2_5_Box2fAttribute_value_1(
    Imf_2_5_Box2fAttribute const * this_);










char const * Imf_2_5_ChannelListAttribute_typeName(
    Imf_2_5_ChannelListAttribute const * this_);


Imf_2_5_Attribute * Imf_2_5_ChannelListAttribute_copy(
    Imf_2_5_ChannelListAttribute const * this_);


void Imf_2_5_ChannelListAttribute_writeValueTo(
    Imf_2_5_ChannelListAttribute const * this_
    , Imf_2_5_OStream * os
    , int version);


void Imf_2_5_ChannelListAttribute_readValueFrom(
    Imf_2_5_ChannelListAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version);


void Imf_2_5_ChannelListAttribute_copyValueFrom(
    Imf_2_5_ChannelListAttribute * this_
    , Imf_2_5_Attribute const * other);


void Imf_2_5_ChannelListAttribute_TypedAttribute(
    Imf_2_5_ChannelListAttribute * this_);


void Imf_2_5_ChannelListAttribute_TypedAttribute_1(
    Imf_2_5_ChannelListAttribute * this_
    , Imf_2_5_ChannelList const * value);


void Imf_2_5_ChannelListAttribute_dtor(
    Imf_2_5_ChannelListAttribute * this_);


Imf_2_5_ChannelList * Imf_2_5_ChannelListAttribute_value(
    Imf_2_5_ChannelListAttribute * this_);


Imf_2_5_ChannelList const * Imf_2_5_ChannelListAttribute_value_1(
    Imf_2_5_ChannelListAttribute const * this_);










char const * Imf_2_5_ChromaticitiesAttribute_typeName(
    Imf_2_5_ChromaticitiesAttribute const * this_);


Imf_2_5_Attribute * Imf_2_5_ChromaticitiesAttribute_copy(
    Imf_2_5_ChromaticitiesAttribute const * this_);


void Imf_2_5_ChromaticitiesAttribute_writeValueTo(
    Imf_2_5_ChromaticitiesAttribute const * this_
    , Imf_2_5_OStream * os
    , int version);


void Imf_2_5_ChromaticitiesAttribute_readValueFrom(
    Imf_2_5_ChromaticitiesAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version);


void Imf_2_5_ChromaticitiesAttribute_copyValueFrom(
    Imf_2_5_ChromaticitiesAttribute * this_
    , Imf_2_5_Attribute const * other);


void Imf_2_5_ChromaticitiesAttribute_TypedAttribute(
    Imf_2_5_ChromaticitiesAttribute * this_);


void Imf_2_5_ChromaticitiesAttribute_TypedAttribute_1(
    Imf_2_5_ChromaticitiesAttribute * this_
    , Imf_2_5_Chromaticities const * value);


void Imf_2_5_ChromaticitiesAttribute_dtor(
    Imf_2_5_ChromaticitiesAttribute * this_);


Imf_2_5_Chromaticities * Imf_2_5_ChromaticitiesAttribute_value(
    Imf_2_5_ChromaticitiesAttribute * this_);


Imf_2_5_Chromaticities const * Imf_2_5_ChromaticitiesAttribute_value_1(
    Imf_2_5_ChromaticitiesAttribute const * this_);










char const * Imf_2_5_CompressionAttribute_typeName(
    Imf_2_5_CompressionAttribute const * this_);


Imf_2_5_Attribute * Imf_2_5_CompressionAttribute_copy(
    Imf_2_5_CompressionAttribute const * this_);


void Imf_2_5_CompressionAttribute_writeValueTo(
    Imf_2_5_CompressionAttribute const * this_
    , Imf_2_5_OStream * os
    , int version);


void Imf_2_5_CompressionAttribute_readValueFrom(
    Imf_2_5_CompressionAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version);


void Imf_2_5_CompressionAttribute_copyValueFrom(
    Imf_2_5_CompressionAttribute * this_
    , Imf_2_5_Attribute const * other);


void Imf_2_5_CompressionAttribute_TypedAttribute(
    Imf_2_5_CompressionAttribute * this_);


void Imf_2_5_CompressionAttribute_dtor(
    Imf_2_5_CompressionAttribute * this_);










char const * Imf_2_5_DeepImageStateAttribute_typeName(
    Imf_2_5_DeepImageStateAttribute const * this_);


Imf_2_5_Attribute * Imf_2_5_DeepImageStateAttribute_copy(
    Imf_2_5_DeepImageStateAttribute const * this_);


void Imf_2_5_DeepImageStateAttribute_writeValueTo(
    Imf_2_5_DeepImageStateAttribute const * this_
    , Imf_2_5_OStream * os
    , int version);


void Imf_2_5_DeepImageStateAttribute_readValueFrom(
    Imf_2_5_DeepImageStateAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version);


void Imf_2_5_DeepImageStateAttribute_copyValueFrom(
    Imf_2_5_DeepImageStateAttribute * this_
    , Imf_2_5_Attribute const * other);


void Imf_2_5_DeepImageStateAttribute_TypedAttribute(
    Imf_2_5_DeepImageStateAttribute * this_);


void Imf_2_5_DeepImageStateAttribute_dtor(
    Imf_2_5_DeepImageStateAttribute * this_);










char const * Imf_2_5_EnvmapAttribute_typeName(
    Imf_2_5_EnvmapAttribute const * this_);


Imf_2_5_Attribute * Imf_2_5_EnvmapAttribute_copy(
    Imf_2_5_EnvmapAttribute const * this_);


void Imf_2_5_EnvmapAttribute_writeValueTo(
    Imf_2_5_EnvmapAttribute const * this_
    , Imf_2_5_OStream * os
    , int version);


void Imf_2_5_EnvmapAttribute_readValueFrom(
    Imf_2_5_EnvmapAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version);


void Imf_2_5_EnvmapAttribute_copyValueFrom(
    Imf_2_5_EnvmapAttribute * this_
    , Imf_2_5_Attribute const * other);


void Imf_2_5_EnvmapAttribute_TypedAttribute(
    Imf_2_5_EnvmapAttribute * this_);


void Imf_2_5_EnvmapAttribute_dtor(
    Imf_2_5_EnvmapAttribute * this_);










char const * Imf_2_5_FloatVectorAttribute_typeName(
    Imf_2_5_FloatVectorAttribute const * this_);


Imf_2_5_Attribute * Imf_2_5_FloatVectorAttribute_copy(
    Imf_2_5_FloatVectorAttribute const * this_);


void Imf_2_5_FloatVectorAttribute_writeValueTo(
    Imf_2_5_FloatVectorAttribute const * this_
    , Imf_2_5_OStream * os
    , int version);


void Imf_2_5_FloatVectorAttribute_readValueFrom(
    Imf_2_5_FloatVectorAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version);


void Imf_2_5_FloatVectorAttribute_copyValueFrom(
    Imf_2_5_FloatVectorAttribute * this_
    , Imf_2_5_Attribute const * other);


void Imf_2_5_FloatVectorAttribute_TypedAttribute(
    Imf_2_5_FloatVectorAttribute * this_);


void Imf_2_5_FloatVectorAttribute_TypedAttribute_1(
    Imf_2_5_FloatVectorAttribute * this_
    , std_vector const * value);


void Imf_2_5_FloatVectorAttribute_dtor(
    Imf_2_5_FloatVectorAttribute * this_);


std_vector * Imf_2_5_FloatVectorAttribute_value(
    Imf_2_5_FloatVectorAttribute * this_);


std_vector const * Imf_2_5_FloatVectorAttribute_value_1(
    Imf_2_5_FloatVectorAttribute const * this_);










char const * Imf_2_5_StringVectorAttribute_typeName(
    Imf_2_5_StringVectorAttribute const * this_);


Imf_2_5_Attribute * Imf_2_5_StringVectorAttribute_copy(
    Imf_2_5_StringVectorAttribute const * this_);


void Imf_2_5_StringVectorAttribute_writeValueTo(
    Imf_2_5_StringVectorAttribute const * this_
    , Imf_2_5_OStream * os
    , int version);


void Imf_2_5_StringVectorAttribute_readValueFrom(
    Imf_2_5_StringVectorAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version);


void Imf_2_5_StringVectorAttribute_copyValueFrom(
    Imf_2_5_StringVectorAttribute * this_
    , Imf_2_5_Attribute const * other);


void Imf_2_5_StringVectorAttribute_TypedAttribute(
    Imf_2_5_StringVectorAttribute * this_);


void Imf_2_5_StringVectorAttribute_dtor(
    Imf_2_5_StringVectorAttribute * this_);










char const * Imf_2_5_StringAttribute_typeName(
    Imf_2_5_StringAttribute const * this_);


Imf_2_5_Attribute * Imf_2_5_StringAttribute_copy(
    Imf_2_5_StringAttribute const * this_);


void Imf_2_5_StringAttribute_writeValueTo(
    Imf_2_5_StringAttribute const * this_
    , Imf_2_5_OStream * os
    , int version);


void Imf_2_5_StringAttribute_readValueFrom(
    Imf_2_5_StringAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version);


void Imf_2_5_StringAttribute_copyValueFrom(
    Imf_2_5_StringAttribute * this_
    , Imf_2_5_Attribute const * other);


void Imf_2_5_StringAttribute_TypedAttribute(
    Imf_2_5_StringAttribute * this_);


void Imf_2_5_StringAttribute_dtor(
    Imf_2_5_StringAttribute * this_);










char const * Imf_2_5_KeyCodeAttribute_typeName(
    Imf_2_5_KeyCodeAttribute const * this_);


Imf_2_5_Attribute * Imf_2_5_KeyCodeAttribute_copy(
    Imf_2_5_KeyCodeAttribute const * this_);


void Imf_2_5_KeyCodeAttribute_writeValueTo(
    Imf_2_5_KeyCodeAttribute const * this_
    , Imf_2_5_OStream * os
    , int version);


void Imf_2_5_KeyCodeAttribute_readValueFrom(
    Imf_2_5_KeyCodeAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version);


void Imf_2_5_KeyCodeAttribute_copyValueFrom(
    Imf_2_5_KeyCodeAttribute * this_
    , Imf_2_5_Attribute const * other);


void Imf_2_5_KeyCodeAttribute_TypedAttribute(
    Imf_2_5_KeyCodeAttribute * this_);


void Imf_2_5_KeyCodeAttribute_TypedAttribute_1(
    Imf_2_5_KeyCodeAttribute * this_
    , Imf_2_5_KeyCode const * value);


void Imf_2_5_KeyCodeAttribute_dtor(
    Imf_2_5_KeyCodeAttribute * this_);


Imf_2_5_KeyCode * Imf_2_5_KeyCodeAttribute_value(
    Imf_2_5_KeyCodeAttribute * this_);


Imf_2_5_KeyCode const * Imf_2_5_KeyCodeAttribute_value_1(
    Imf_2_5_KeyCodeAttribute const * this_);










char const * Imf_2_5_LineOrderAttribute_typeName(
    Imf_2_5_LineOrderAttribute const * this_);


Imf_2_5_Attribute * Imf_2_5_LineOrderAttribute_copy(
    Imf_2_5_LineOrderAttribute const * this_);


void Imf_2_5_LineOrderAttribute_writeValueTo(
    Imf_2_5_LineOrderAttribute const * this_
    , Imf_2_5_OStream * os
    , int version);


void Imf_2_5_LineOrderAttribute_readValueFrom(
    Imf_2_5_LineOrderAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version);


void Imf_2_5_LineOrderAttribute_copyValueFrom(
    Imf_2_5_LineOrderAttribute * this_
    , Imf_2_5_Attribute const * other);


void Imf_2_5_LineOrderAttribute_TypedAttribute(
    Imf_2_5_LineOrderAttribute * this_);


void Imf_2_5_LineOrderAttribute_dtor(
    Imf_2_5_LineOrderAttribute * this_);










char const * Imf_2_5_M33fAttribute_typeName(
    Imf_2_5_M33fAttribute const * this_);


Imf_2_5_Attribute * Imf_2_5_M33fAttribute_copy(
    Imf_2_5_M33fAttribute const * this_);


void Imf_2_5_M33fAttribute_writeValueTo(
    Imf_2_5_M33fAttribute const * this_
    , Imf_2_5_OStream * os
    , int version);


void Imf_2_5_M33fAttribute_readValueFrom(
    Imf_2_5_M33fAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version);


void Imf_2_5_M33fAttribute_copyValueFrom(
    Imf_2_5_M33fAttribute * this_
    , Imf_2_5_Attribute const * other);


void Imf_2_5_M33fAttribute_TypedAttribute(
    Imf_2_5_M33fAttribute * this_);


void Imf_2_5_M33fAttribute_TypedAttribute_1(
    Imf_2_5_M33fAttribute * this_
    , Imath_2_5_M33f const * value);


void Imf_2_5_M33fAttribute_dtor(
    Imf_2_5_M33fAttribute * this_);


Imath_2_5_M33f * Imf_2_5_M33fAttribute_value(
    Imf_2_5_M33fAttribute * this_);


Imath_2_5_M33f const * Imf_2_5_M33fAttribute_value_1(
    Imf_2_5_M33fAttribute const * this_);










char const * Imf_2_5_M33dAttribute_typeName(
    Imf_2_5_M33dAttribute const * this_);


Imf_2_5_Attribute * Imf_2_5_M33dAttribute_copy(
    Imf_2_5_M33dAttribute const * this_);


void Imf_2_5_M33dAttribute_writeValueTo(
    Imf_2_5_M33dAttribute const * this_
    , Imf_2_5_OStream * os
    , int version);


void Imf_2_5_M33dAttribute_readValueFrom(
    Imf_2_5_M33dAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version);


void Imf_2_5_M33dAttribute_copyValueFrom(
    Imf_2_5_M33dAttribute * this_
    , Imf_2_5_Attribute const * other);


void Imf_2_5_M33dAttribute_TypedAttribute(
    Imf_2_5_M33dAttribute * this_);


void Imf_2_5_M33dAttribute_TypedAttribute_1(
    Imf_2_5_M33dAttribute * this_
    , Imath_2_5_M33d const * value);


void Imf_2_5_M33dAttribute_dtor(
    Imf_2_5_M33dAttribute * this_);


Imath_2_5_M33d * Imf_2_5_M33dAttribute_value(
    Imf_2_5_M33dAttribute * this_);


Imath_2_5_M33d const * Imf_2_5_M33dAttribute_value_1(
    Imf_2_5_M33dAttribute const * this_);










char const * Imf_2_5_M44fAttribute_typeName(
    Imf_2_5_M44fAttribute const * this_);


Imf_2_5_Attribute * Imf_2_5_M44fAttribute_copy(
    Imf_2_5_M44fAttribute const * this_);


void Imf_2_5_M44fAttribute_writeValueTo(
    Imf_2_5_M44fAttribute const * this_
    , Imf_2_5_OStream * os
    , int version);


void Imf_2_5_M44fAttribute_readValueFrom(
    Imf_2_5_M44fAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version);


void Imf_2_5_M44fAttribute_copyValueFrom(
    Imf_2_5_M44fAttribute * this_
    , Imf_2_5_Attribute const * other);


void Imf_2_5_M44fAttribute_TypedAttribute(
    Imf_2_5_M44fAttribute * this_);


void Imf_2_5_M44fAttribute_TypedAttribute_1(
    Imf_2_5_M44fAttribute * this_
    , Imath_2_5_M44f const * value);


void Imf_2_5_M44fAttribute_dtor(
    Imf_2_5_M44fAttribute * this_);


Imath_2_5_M44f * Imf_2_5_M44fAttribute_value(
    Imf_2_5_M44fAttribute * this_);


Imath_2_5_M44f const * Imf_2_5_M44fAttribute_value_1(
    Imf_2_5_M44fAttribute const * this_);










char const * Imf_2_5_M44dAttribute_typeName(
    Imf_2_5_M44dAttribute const * this_);


Imf_2_5_Attribute * Imf_2_5_M44dAttribute_copy(
    Imf_2_5_M44dAttribute const * this_);


void Imf_2_5_M44dAttribute_writeValueTo(
    Imf_2_5_M44dAttribute const * this_
    , Imf_2_5_OStream * os
    , int version);


void Imf_2_5_M44dAttribute_readValueFrom(
    Imf_2_5_M44dAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version);


void Imf_2_5_M44dAttribute_copyValueFrom(
    Imf_2_5_M44dAttribute * this_
    , Imf_2_5_Attribute const * other);


void Imf_2_5_M44dAttribute_TypedAttribute(
    Imf_2_5_M44dAttribute * this_);


void Imf_2_5_M44dAttribute_TypedAttribute_1(
    Imf_2_5_M44dAttribute * this_
    , Imath_2_5_M44d const * value);


void Imf_2_5_M44dAttribute_dtor(
    Imf_2_5_M44dAttribute * this_);


Imath_2_5_M44d * Imf_2_5_M44dAttribute_value(
    Imf_2_5_M44dAttribute * this_);


Imath_2_5_M44d const * Imf_2_5_M44dAttribute_value_1(
    Imf_2_5_M44dAttribute const * this_);










char const * Imf_2_5_PreviewImageAttribute_typeName(
    Imf_2_5_PreviewImageAttribute const * this_);


Imf_2_5_Attribute * Imf_2_5_PreviewImageAttribute_copy(
    Imf_2_5_PreviewImageAttribute const * this_);


void Imf_2_5_PreviewImageAttribute_writeValueTo(
    Imf_2_5_PreviewImageAttribute const * this_
    , Imf_2_5_OStream * os
    , int version);


void Imf_2_5_PreviewImageAttribute_readValueFrom(
    Imf_2_5_PreviewImageAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version);


void Imf_2_5_PreviewImageAttribute_copyValueFrom(
    Imf_2_5_PreviewImageAttribute * this_
    , Imf_2_5_Attribute const * other);


void Imf_2_5_PreviewImageAttribute_TypedAttribute(
    Imf_2_5_PreviewImageAttribute * this_);


void Imf_2_5_PreviewImageAttribute_TypedAttribute_1(
    Imf_2_5_PreviewImageAttribute * this_
    , Imf_2_5_PreviewImage const * value);


void Imf_2_5_PreviewImageAttribute_dtor(
    Imf_2_5_PreviewImageAttribute * this_);


Imf_2_5_PreviewImage * Imf_2_5_PreviewImageAttribute_value(
    Imf_2_5_PreviewImageAttribute * this_);


Imf_2_5_PreviewImage const * Imf_2_5_PreviewImageAttribute_value_1(
    Imf_2_5_PreviewImageAttribute const * this_);










char const * Imf_2_5_RationalAttribute_typeName(
    Imf_2_5_RationalAttribute const * this_);


Imf_2_5_Attribute * Imf_2_5_RationalAttribute_copy(
    Imf_2_5_RationalAttribute const * this_);


void Imf_2_5_RationalAttribute_writeValueTo(
    Imf_2_5_RationalAttribute const * this_
    , Imf_2_5_OStream * os
    , int version);


void Imf_2_5_RationalAttribute_readValueFrom(
    Imf_2_5_RationalAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version);


void Imf_2_5_RationalAttribute_copyValueFrom(
    Imf_2_5_RationalAttribute * this_
    , Imf_2_5_Attribute const * other);


void Imf_2_5_RationalAttribute_TypedAttribute(
    Imf_2_5_RationalAttribute * this_);


void Imf_2_5_RationalAttribute_TypedAttribute_1(
    Imf_2_5_RationalAttribute * this_
    , Imf_2_5_Rational const * value);


void Imf_2_5_RationalAttribute_dtor(
    Imf_2_5_RationalAttribute * this_);


Imf_2_5_Rational * Imf_2_5_RationalAttribute_value(
    Imf_2_5_RationalAttribute * this_);


Imf_2_5_Rational const * Imf_2_5_RationalAttribute_value_1(
    Imf_2_5_RationalAttribute const * this_);










char const * Imf_2_5_TileDescriptionAttribute_typeName(
    Imf_2_5_TileDescriptionAttribute const * this_);


Imf_2_5_Attribute * Imf_2_5_TileDescriptionAttribute_copy(
    Imf_2_5_TileDescriptionAttribute const * this_);


void Imf_2_5_TileDescriptionAttribute_writeValueTo(
    Imf_2_5_TileDescriptionAttribute const * this_
    , Imf_2_5_OStream * os
    , int version);


void Imf_2_5_TileDescriptionAttribute_readValueFrom(
    Imf_2_5_TileDescriptionAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version);


void Imf_2_5_TileDescriptionAttribute_copyValueFrom(
    Imf_2_5_TileDescriptionAttribute * this_
    , Imf_2_5_Attribute const * other);


void Imf_2_5_TileDescriptionAttribute_TypedAttribute(
    Imf_2_5_TileDescriptionAttribute * this_);


void Imf_2_5_TileDescriptionAttribute_TypedAttribute_1(
    Imf_2_5_TileDescriptionAttribute * this_
    , Imf_2_5_TileDescription const * value);


void Imf_2_5_TileDescriptionAttribute_dtor(
    Imf_2_5_TileDescriptionAttribute * this_);


Imf_2_5_TileDescription * Imf_2_5_TileDescriptionAttribute_value(
    Imf_2_5_TileDescriptionAttribute * this_);


Imf_2_5_TileDescription const * Imf_2_5_TileDescriptionAttribute_value_1(
    Imf_2_5_TileDescriptionAttribute const * this_);










char const * Imf_2_5_TimeCodeAttribute_typeName(
    Imf_2_5_TimeCodeAttribute const * this_);


Imf_2_5_Attribute * Imf_2_5_TimeCodeAttribute_copy(
    Imf_2_5_TimeCodeAttribute const * this_);


void Imf_2_5_TimeCodeAttribute_writeValueTo(
    Imf_2_5_TimeCodeAttribute const * this_
    , Imf_2_5_OStream * os
    , int version);


void Imf_2_5_TimeCodeAttribute_readValueFrom(
    Imf_2_5_TimeCodeAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version);


void Imf_2_5_TimeCodeAttribute_copyValueFrom(
    Imf_2_5_TimeCodeAttribute * this_
    , Imf_2_5_Attribute const * other);


void Imf_2_5_TimeCodeAttribute_TypedAttribute(
    Imf_2_5_TimeCodeAttribute * this_);


void Imf_2_5_TimeCodeAttribute_TypedAttribute_1(
    Imf_2_5_TimeCodeAttribute * this_
    , Imf_2_5_TimeCode const * value);


void Imf_2_5_TimeCodeAttribute_dtor(
    Imf_2_5_TimeCodeAttribute * this_);


Imf_2_5_TimeCode * Imf_2_5_TimeCodeAttribute_value(
    Imf_2_5_TimeCodeAttribute * this_);


Imf_2_5_TimeCode const * Imf_2_5_TimeCodeAttribute_value_1(
    Imf_2_5_TimeCodeAttribute const * this_);










char const * Imf_2_5_V2iAttribute_typeName(
    Imf_2_5_V2iAttribute const * this_);


Imf_2_5_Attribute * Imf_2_5_V2iAttribute_copy(
    Imf_2_5_V2iAttribute const * this_);


void Imf_2_5_V2iAttribute_writeValueTo(
    Imf_2_5_V2iAttribute const * this_
    , Imf_2_5_OStream * os
    , int version);


void Imf_2_5_V2iAttribute_readValueFrom(
    Imf_2_5_V2iAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version);


void Imf_2_5_V2iAttribute_copyValueFrom(
    Imf_2_5_V2iAttribute * this_
    , Imf_2_5_Attribute const * other);


void Imf_2_5_V2iAttribute_TypedAttribute(
    Imf_2_5_V2iAttribute * this_);


void Imf_2_5_V2iAttribute_TypedAttribute_1(
    Imf_2_5_V2iAttribute * this_
    , Imath_2_5_V2i const * value);


void Imf_2_5_V2iAttribute_dtor(
    Imf_2_5_V2iAttribute * this_);


Imath_2_5_V2i * Imf_2_5_V2iAttribute_value(
    Imf_2_5_V2iAttribute * this_);


Imath_2_5_V2i const * Imf_2_5_V2iAttribute_value_1(
    Imf_2_5_V2iAttribute const * this_);










char const * Imf_2_5_V2fAttribute_typeName(
    Imf_2_5_V2fAttribute const * this_);


Imf_2_5_Attribute * Imf_2_5_V2fAttribute_copy(
    Imf_2_5_V2fAttribute const * this_);


void Imf_2_5_V2fAttribute_writeValueTo(
    Imf_2_5_V2fAttribute const * this_
    , Imf_2_5_OStream * os
    , int version);


void Imf_2_5_V2fAttribute_readValueFrom(
    Imf_2_5_V2fAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version);


void Imf_2_5_V2fAttribute_copyValueFrom(
    Imf_2_5_V2fAttribute * this_
    , Imf_2_5_Attribute const * other);


void Imf_2_5_V2fAttribute_TypedAttribute(
    Imf_2_5_V2fAttribute * this_);


void Imf_2_5_V2fAttribute_TypedAttribute_1(
    Imf_2_5_V2fAttribute * this_
    , Imath_2_5_V2f const * value);


void Imf_2_5_V2fAttribute_dtor(
    Imf_2_5_V2fAttribute * this_);


Imath_2_5_V2f * Imf_2_5_V2fAttribute_value(
    Imf_2_5_V2fAttribute * this_);


Imath_2_5_V2f const * Imf_2_5_V2fAttribute_value_1(
    Imf_2_5_V2fAttribute const * this_);










char const * Imf_2_5_V2dAttribute_typeName(
    Imf_2_5_V2dAttribute const * this_);


Imf_2_5_Attribute * Imf_2_5_V2dAttribute_copy(
    Imf_2_5_V2dAttribute const * this_);


void Imf_2_5_V2dAttribute_writeValueTo(
    Imf_2_5_V2dAttribute const * this_
    , Imf_2_5_OStream * os
    , int version);


void Imf_2_5_V2dAttribute_readValueFrom(
    Imf_2_5_V2dAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version);


void Imf_2_5_V2dAttribute_copyValueFrom(
    Imf_2_5_V2dAttribute * this_
    , Imf_2_5_Attribute const * other);


void Imf_2_5_V2dAttribute_TypedAttribute(
    Imf_2_5_V2dAttribute * this_);


void Imf_2_5_V2dAttribute_TypedAttribute_1(
    Imf_2_5_V2dAttribute * this_
    , Imath_2_5_V2d const * value);


void Imf_2_5_V2dAttribute_dtor(
    Imf_2_5_V2dAttribute * this_);


Imath_2_5_V2d * Imf_2_5_V2dAttribute_value(
    Imf_2_5_V2dAttribute * this_);


Imath_2_5_V2d const * Imf_2_5_V2dAttribute_value_1(
    Imf_2_5_V2dAttribute const * this_);










char const * Imf_2_5_V3iAttribute_typeName(
    Imf_2_5_V3iAttribute const * this_);


Imf_2_5_Attribute * Imf_2_5_V3iAttribute_copy(
    Imf_2_5_V3iAttribute const * this_);


void Imf_2_5_V3iAttribute_writeValueTo(
    Imf_2_5_V3iAttribute const * this_
    , Imf_2_5_OStream * os
    , int version);


void Imf_2_5_V3iAttribute_readValueFrom(
    Imf_2_5_V3iAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version);


void Imf_2_5_V3iAttribute_copyValueFrom(
    Imf_2_5_V3iAttribute * this_
    , Imf_2_5_Attribute const * other);


void Imf_2_5_V3iAttribute_TypedAttribute(
    Imf_2_5_V3iAttribute * this_);


void Imf_2_5_V3iAttribute_TypedAttribute_1(
    Imf_2_5_V3iAttribute * this_
    , Imath_2_5_V3i const * value);


void Imf_2_5_V3iAttribute_dtor(
    Imf_2_5_V3iAttribute * this_);


Imath_2_5_V3i * Imf_2_5_V3iAttribute_value(
    Imf_2_5_V3iAttribute * this_);


Imath_2_5_V3i const * Imf_2_5_V3iAttribute_value_1(
    Imf_2_5_V3iAttribute const * this_);










char const * Imf_2_5_V3fAttribute_typeName(
    Imf_2_5_V3fAttribute const * this_);


Imf_2_5_Attribute * Imf_2_5_V3fAttribute_copy(
    Imf_2_5_V3fAttribute const * this_);


void Imf_2_5_V3fAttribute_writeValueTo(
    Imf_2_5_V3fAttribute const * this_
    , Imf_2_5_OStream * os
    , int version);


void Imf_2_5_V3fAttribute_readValueFrom(
    Imf_2_5_V3fAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version);


void Imf_2_5_V3fAttribute_copyValueFrom(
    Imf_2_5_V3fAttribute * this_
    , Imf_2_5_Attribute const * other);


void Imf_2_5_V3fAttribute_TypedAttribute(
    Imf_2_5_V3fAttribute * this_);


void Imf_2_5_V3fAttribute_TypedAttribute_1(
    Imf_2_5_V3fAttribute * this_
    , Imath_2_5_V3f const * value);


void Imf_2_5_V3fAttribute_dtor(
    Imf_2_5_V3fAttribute * this_);


Imath_2_5_V3f * Imf_2_5_V3fAttribute_value(
    Imf_2_5_V3fAttribute * this_);


Imath_2_5_V3f const * Imf_2_5_V3fAttribute_value_1(
    Imf_2_5_V3fAttribute const * this_);










char const * Imf_2_5_V3dAttribute_typeName(
    Imf_2_5_V3dAttribute const * this_);


Imf_2_5_Attribute * Imf_2_5_V3dAttribute_copy(
    Imf_2_5_V3dAttribute const * this_);


void Imf_2_5_V3dAttribute_writeValueTo(
    Imf_2_5_V3dAttribute const * this_
    , Imf_2_5_OStream * os
    , int version);


void Imf_2_5_V3dAttribute_readValueFrom(
    Imf_2_5_V3dAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version);


void Imf_2_5_V3dAttribute_copyValueFrom(
    Imf_2_5_V3dAttribute * this_
    , Imf_2_5_Attribute const * other);


void Imf_2_5_V3dAttribute_TypedAttribute(
    Imf_2_5_V3dAttribute * this_);


void Imf_2_5_V3dAttribute_TypedAttribute_1(
    Imf_2_5_V3dAttribute * this_
    , Imath_2_5_V3d const * value);


void Imf_2_5_V3dAttribute_dtor(
    Imf_2_5_V3dAttribute * this_);


Imath_2_5_V3d * Imf_2_5_V3dAttribute_value(
    Imf_2_5_V3dAttribute * this_);


Imath_2_5_V3d const * Imf_2_5_V3dAttribute_value_1(
    Imf_2_5_V3dAttribute const * this_);
















#ifdef __cplusplus
}
#endif
