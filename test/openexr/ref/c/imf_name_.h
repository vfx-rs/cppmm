#pragma once

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_Name_s {
    char data[256];
} __attribute__((aligned(1))) Imf_2_5_Name;


void Imf_2_5_Name_Name(
    Imf_2_5_Name * this_);


void Imf_2_5_Name_Name_1(
    Imf_2_5_Name * this_
    , char const * text);


Imf_2_5_Name * Imf_2_5_Name__assign(
    Imf_2_5_Name * this_
    , char const * text);








#ifdef __cplusplus
}
#endif
