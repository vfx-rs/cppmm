#pragma once
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_Header_s Imf_2_5_Header;
typedef struct Imf_2_5_OStream_s Imf_2_5_OStream;
typedef struct Imf_2_5_MultiPartOutputFile_s {
    char data[16];
} __attribute__((aligned(8))) Imf_2_5_MultiPartOutputFile;


void Imf_2_5_MultiPartOutputFile_MultiPartOutputFile(
    Imf_2_5_MultiPartOutputFile * this_
    , char const * fileName
    , Imf_2_5_Header const * headers
    , int parts
    , _Bool overrideSharedAttributes
    , int numThreads);


void Imf_2_5_MultiPartOutputFile_MultiPartOutputFile_1(
    Imf_2_5_MultiPartOutputFile * this_
    , Imf_2_5_OStream * os
    , Imf_2_5_Header const * headers
    , int parts
    , _Bool overrideSharedAttributes
    , int numThreads);


int Imf_2_5_MultiPartOutputFile_parts(
    Imf_2_5_MultiPartOutputFile const * this_);


Imf_2_5_Header const * Imf_2_5_MultiPartOutputFile_header(
    Imf_2_5_MultiPartOutputFile const * this_
    , int n);


void Imf_2_5_MultiPartOutputFile_dtor(
    Imf_2_5_MultiPartOutputFile * this_);








#ifdef __cplusplus
}
#endif
