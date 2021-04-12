#pragma once

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_Rational_s {
    char data[8];
} __attribute__((aligned(4))) Imf_2_5_Rational;


void Imf_2_5_Rational_Rational(
    Imf_2_5_Rational * this_);


void Imf_2_5_Rational_Rational_1(
    Imf_2_5_Rational * this_
    , int n
    , int d);


void Imf_2_5_Rational_Rational_2(
    Imf_2_5_Rational * this_
    , double x);


double Imf_2_5_Rational_operatordouble(
    Imf_2_5_Rational const * this_);








#ifdef __cplusplus
}
#endif
