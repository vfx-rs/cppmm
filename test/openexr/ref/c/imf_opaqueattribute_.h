#pragma once

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_OStream_s Imf_2_5_OStream;
typedef struct Imf_2_5_IStream_s Imf_2_5_IStream;
typedef struct Imf_2_5_Attribute_s Imf_2_5_Attribute;
typedef struct Imf_2_5_OpaqueAttribute_s {
    char data[64];
} __attribute__((aligned(8))) Imf_2_5_OpaqueAttribute;


char const * Imf_2_5_OpaqueAttribute_typeName(
    Imf_2_5_OpaqueAttribute const * this_);


Imf_2_5_Attribute * Imf_2_5_OpaqueAttribute_copy(
    Imf_2_5_OpaqueAttribute const * this_);


void Imf_2_5_OpaqueAttribute_writeValueTo(
    Imf_2_5_OpaqueAttribute const * this_
    , Imf_2_5_OStream * os
    , int version);


void Imf_2_5_OpaqueAttribute_readValueFrom(
    Imf_2_5_OpaqueAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version);


void Imf_2_5_OpaqueAttribute_copyValueFrom(
    Imf_2_5_OpaqueAttribute * this_
    , Imf_2_5_Attribute const * other);


void Imf_2_5_OpaqueAttribute_OpaqueAttribute(
    Imf_2_5_OpaqueAttribute * this_
    , char const * typeName);


void Imf_2_5_OpaqueAttribute_OpaqueAttribute_1(
    Imf_2_5_OpaqueAttribute * this_
    , Imf_2_5_OpaqueAttribute const * other);


void Imf_2_5_OpaqueAttribute_dtor(
    Imf_2_5_OpaqueAttribute * this_);









#ifdef __cplusplus
}
#endif
