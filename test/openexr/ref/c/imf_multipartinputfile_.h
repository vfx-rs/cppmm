#pragma once
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_Header_s Imf_2_5_Header;
typedef struct Imf_2_5_IStream_s Imf_2_5_IStream;
typedef struct Imf_2_5_MultiPartInputFile_s {
    char data[16];
} __attribute__((aligned(8))) Imf_2_5_MultiPartInputFile;


void Imf_2_5_MultiPartInputFile_MultiPartInputFile(
    Imf_2_5_MultiPartInputFile * this_
    , char const * fileName
    , int numThreads
    , _Bool reconstructChunkOffsetTable);


void Imf_2_5_MultiPartInputFile_MultiPartInputFile_1(
    Imf_2_5_MultiPartInputFile * this_
    , Imf_2_5_IStream * is
    , int numThreads
    , _Bool reconstructChunkOffsetTable);


void Imf_2_5_MultiPartInputFile_dtor(
    Imf_2_5_MultiPartInputFile * this_);


int Imf_2_5_MultiPartInputFile_parts(
    Imf_2_5_MultiPartInputFile const * this_);


Imf_2_5_Header const * Imf_2_5_MultiPartInputFile_header(
    Imf_2_5_MultiPartInputFile const * this_
    , int n);


int Imf_2_5_MultiPartInputFile_version(
    Imf_2_5_MultiPartInputFile const * this_);


_Bool Imf_2_5_MultiPartInputFile_partComplete(
    Imf_2_5_MultiPartInputFile const * this_
    , int part);








#ifdef __cplusplus
}
#endif
