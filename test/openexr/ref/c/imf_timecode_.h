#pragma once
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_TimeCode_s {
    char data[8];
} __attribute__((aligned(4))) Imf_2_5_TimeCode;


void Imf_2_5_TimeCode_TimeCode(
    Imf_2_5_TimeCode * this_);


void Imf_2_5_TimeCode_TimeCode_1(
    Imf_2_5_TimeCode * this_
    , int hours
    , int minutes
    , int seconds
    , int frame
    , _Bool dropFrame
    , _Bool colorFrame
    , _Bool fieldPhase
    , _Bool bgf0
    , _Bool bgf1
    , _Bool bgf2
    , int binaryGroup1
    , int binaryGroup2
    , int binaryGroup3
    , int binaryGroup4
    , int binaryGroup5
    , int binaryGroup6
    , int binaryGroup7
    , int binaryGroup8);


void Imf_2_5_TimeCode_TimeCode_2(
    Imf_2_5_TimeCode * this_
    , Imf_2_5_TimeCode const * other);


void Imf_2_5_TimeCode_dtor(
    Imf_2_5_TimeCode * this_);


Imf_2_5_TimeCode * Imf_2_5_TimeCode__assign(
    Imf_2_5_TimeCode * this_
    , Imf_2_5_TimeCode const * other);


int Imf_2_5_TimeCode_hours(
    Imf_2_5_TimeCode const * this_);


void Imf_2_5_TimeCode_setHours(
    Imf_2_5_TimeCode * this_
    , int value);


int Imf_2_5_TimeCode_minutes(
    Imf_2_5_TimeCode const * this_);


void Imf_2_5_TimeCode_setMinutes(
    Imf_2_5_TimeCode * this_
    , int value);


int Imf_2_5_TimeCode_seconds(
    Imf_2_5_TimeCode const * this_);


void Imf_2_5_TimeCode_setSeconds(
    Imf_2_5_TimeCode * this_
    , int value);


int Imf_2_5_TimeCode_frame(
    Imf_2_5_TimeCode const * this_);


void Imf_2_5_TimeCode_setFrame(
    Imf_2_5_TimeCode * this_
    , int value);


_Bool Imf_2_5_TimeCode_dropFrame(
    Imf_2_5_TimeCode const * this_);


void Imf_2_5_TimeCode_setDropFrame(
    Imf_2_5_TimeCode * this_
    , _Bool value);


_Bool Imf_2_5_TimeCode_colorFrame(
    Imf_2_5_TimeCode const * this_);


void Imf_2_5_TimeCode_setColorFrame(
    Imf_2_5_TimeCode * this_
    , _Bool value);


_Bool Imf_2_5_TimeCode_fieldPhase(
    Imf_2_5_TimeCode const * this_);


void Imf_2_5_TimeCode_setFieldPhase(
    Imf_2_5_TimeCode * this_
    , _Bool value);


_Bool Imf_2_5_TimeCode_bgf0(
    Imf_2_5_TimeCode const * this_);


void Imf_2_5_TimeCode_setBgf0(
    Imf_2_5_TimeCode * this_
    , _Bool value);


_Bool Imf_2_5_TimeCode_bgf1(
    Imf_2_5_TimeCode const * this_);


void Imf_2_5_TimeCode_setBgf1(
    Imf_2_5_TimeCode * this_
    , _Bool value);


_Bool Imf_2_5_TimeCode_bgf2(
    Imf_2_5_TimeCode const * this_);


void Imf_2_5_TimeCode_setBgf2(
    Imf_2_5_TimeCode * this_
    , _Bool value);


int Imf_2_5_TimeCode_binaryGroup(
    Imf_2_5_TimeCode const * this_
    , int group);


void Imf_2_5_TimeCode_setBinaryGroup(
    Imf_2_5_TimeCode * this_
    , int group
    , int value);


unsigned int Imf_2_5_TimeCode_userData(
    Imf_2_5_TimeCode const * this_);


void Imf_2_5_TimeCode_setUserData(
    Imf_2_5_TimeCode * this_
    , unsigned int value);


_Bool Imf_2_5_TimeCode__eq(
    Imf_2_5_TimeCode const * this_
    , Imf_2_5_TimeCode const * v);


_Bool Imf_2_5_TimeCode__ne(
    Imf_2_5_TimeCode const * this_
    , Imf_2_5_TimeCode const * v);









#ifdef __cplusplus
}
#endif
