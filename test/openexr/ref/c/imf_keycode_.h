#pragma once

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_KeyCode_s {
    char data[28];
} __attribute__((aligned(4))) Imf_2_5_KeyCode;


void Imf_2_5_KeyCode_KeyCode(
    Imf_2_5_KeyCode * this_
    , int filmMfcCode
    , int filmType
    , int prefix
    , int count
    , int perfOffset
    , int perfsPerFrame
    , int perfsPerCount);


void Imf_2_5_KeyCode_KeyCode_1(
    Imf_2_5_KeyCode * this_
    , Imf_2_5_KeyCode const * other);


void Imf_2_5_KeyCode_dtor(
    Imf_2_5_KeyCode * this_);


Imf_2_5_KeyCode * Imf_2_5_KeyCode__assign(
    Imf_2_5_KeyCode * this_
    , Imf_2_5_KeyCode const * other);


int Imf_2_5_KeyCode_filmMfcCode(
    Imf_2_5_KeyCode const * this_);


void Imf_2_5_KeyCode_setFilmMfcCode(
    Imf_2_5_KeyCode * this_
    , int filmMfcCode);


int Imf_2_5_KeyCode_filmType(
    Imf_2_5_KeyCode const * this_);


void Imf_2_5_KeyCode_setFilmType(
    Imf_2_5_KeyCode * this_
    , int filmType);


int Imf_2_5_KeyCode_prefix(
    Imf_2_5_KeyCode const * this_);


void Imf_2_5_KeyCode_setPrefix(
    Imf_2_5_KeyCode * this_
    , int prefix);


int Imf_2_5_KeyCode_count(
    Imf_2_5_KeyCode const * this_);


void Imf_2_5_KeyCode_setCount(
    Imf_2_5_KeyCode * this_
    , int count);


int Imf_2_5_KeyCode_perfOffset(
    Imf_2_5_KeyCode const * this_);


void Imf_2_5_KeyCode_setPerfOffset(
    Imf_2_5_KeyCode * this_
    , int perfOffset);


int Imf_2_5_KeyCode_perfsPerFrame(
    Imf_2_5_KeyCode const * this_);


void Imf_2_5_KeyCode_setPerfsPerFrame(
    Imf_2_5_KeyCode * this_
    , int perfsPerFrame);


int Imf_2_5_KeyCode_perfsPerCount(
    Imf_2_5_KeyCode const * this_);


void Imf_2_5_KeyCode_setPerfsPerCount(
    Imf_2_5_KeyCode * this_
    , int perfsPerCount);









#ifdef __cplusplus
}
#endif
