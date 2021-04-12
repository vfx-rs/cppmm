#pragma once
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_OStream_s {
    char data[40];
} __attribute__((aligned(8))) Imf_2_5_OStream;
typedef struct Imf_2_5_IStream_s {
    char data[40];
} __attribute__((aligned(8))) Imf_2_5_IStream;


void Imf_2_5_OStream_dtor(
    Imf_2_5_OStream * this_);


void Imf_2_5_OStream_write(
    Imf_2_5_OStream * this_
    , char const * c
    , int n);


unsigned long Imf_2_5_OStream_tellp(
    Imf_2_5_OStream * this_);


void Imf_2_5_OStream_seekp(
    Imf_2_5_OStream * this_
    , unsigned long pos);


char const * Imf_2_5_OStream_fileName(
    Imf_2_5_OStream const * this_);










void Imf_2_5_IStream_dtor(
    Imf_2_5_IStream * this_);


_Bool Imf_2_5_IStream_isMemoryMapped(
    Imf_2_5_IStream const * this_);


_Bool Imf_2_5_IStream_read(
    Imf_2_5_IStream * this_
    , char * c
    , int n);


char * Imf_2_5_IStream_readMemoryMapped(
    Imf_2_5_IStream * this_
    , int n);


unsigned long Imf_2_5_IStream_tellg(
    Imf_2_5_IStream * this_);


void Imf_2_5_IStream_seekg(
    Imf_2_5_IStream * this_
    , unsigned long pos);


void Imf_2_5_IStream_clear(
    Imf_2_5_IStream * this_);


char const * Imf_2_5_IStream_fileName(
    Imf_2_5_IStream const * this_);








#ifdef __cplusplus
}
#endif
