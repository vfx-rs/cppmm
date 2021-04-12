#include <imf_timecode_private_.h>

#include <new>


void Imf_2_5_TimeCode_TimeCode(
    Imf_2_5_TimeCode * this_)
{
    new (this_) Imf_2_5::TimeCode();
}

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
    , int binaryGroup8)
{
    new (this_) Imf_2_5::TimeCode(hours, minutes, seconds, frame, dropFrame, colorFrame, fieldPhase, bgf0, bgf1, bgf2, binaryGroup1, binaryGroup2, binaryGroup3, binaryGroup4, binaryGroup5, binaryGroup6, binaryGroup7, binaryGroup8);
}

void Imf_2_5_TimeCode_TimeCode_2(
    Imf_2_5_TimeCode * this_
    , Imf_2_5_TimeCode const * other)
{
    new (this_) Imf_2_5::TimeCode(to_cpp_ref(other));
}

void Imf_2_5_TimeCode_dtor(
    Imf_2_5_TimeCode * this_)
{
    (to_cpp(this_)) -> Imf_2_5::TimeCode::~TimeCode();
}

Imf_2_5_TimeCode * Imf_2_5_TimeCode__assign(
    Imf_2_5_TimeCode * this_
    , Imf_2_5_TimeCode const * other)
{
    return to_c((to_cpp(this_)) -> operator=(to_cpp_ref(other)));
}

int Imf_2_5_TimeCode_hours(
    Imf_2_5_TimeCode const * this_)
{
    return (to_cpp(this_)) -> hours();
}

void Imf_2_5_TimeCode_setHours(
    Imf_2_5_TimeCode * this_
    , int value)
{
    (to_cpp(this_)) -> setHours(value);
}

int Imf_2_5_TimeCode_minutes(
    Imf_2_5_TimeCode const * this_)
{
    return (to_cpp(this_)) -> minutes();
}

void Imf_2_5_TimeCode_setMinutes(
    Imf_2_5_TimeCode * this_
    , int value)
{
    (to_cpp(this_)) -> setMinutes(value);
}

int Imf_2_5_TimeCode_seconds(
    Imf_2_5_TimeCode const * this_)
{
    return (to_cpp(this_)) -> seconds();
}

void Imf_2_5_TimeCode_setSeconds(
    Imf_2_5_TimeCode * this_
    , int value)
{
    (to_cpp(this_)) -> setSeconds(value);
}

int Imf_2_5_TimeCode_frame(
    Imf_2_5_TimeCode const * this_)
{
    return (to_cpp(this_)) -> frame();
}

void Imf_2_5_TimeCode_setFrame(
    Imf_2_5_TimeCode * this_
    , int value)
{
    (to_cpp(this_)) -> setFrame(value);
}

_Bool Imf_2_5_TimeCode_dropFrame(
    Imf_2_5_TimeCode const * this_)
{
    return (to_cpp(this_)) -> dropFrame();
}

void Imf_2_5_TimeCode_setDropFrame(
    Imf_2_5_TimeCode * this_
    , _Bool value)
{
    (to_cpp(this_)) -> setDropFrame(value);
}

_Bool Imf_2_5_TimeCode_colorFrame(
    Imf_2_5_TimeCode const * this_)
{
    return (to_cpp(this_)) -> colorFrame();
}

void Imf_2_5_TimeCode_setColorFrame(
    Imf_2_5_TimeCode * this_
    , _Bool value)
{
    (to_cpp(this_)) -> setColorFrame(value);
}

_Bool Imf_2_5_TimeCode_fieldPhase(
    Imf_2_5_TimeCode const * this_)
{
    return (to_cpp(this_)) -> fieldPhase();
}

void Imf_2_5_TimeCode_setFieldPhase(
    Imf_2_5_TimeCode * this_
    , _Bool value)
{
    (to_cpp(this_)) -> setFieldPhase(value);
}

_Bool Imf_2_5_TimeCode_bgf0(
    Imf_2_5_TimeCode const * this_)
{
    return (to_cpp(this_)) -> bgf0();
}

void Imf_2_5_TimeCode_setBgf0(
    Imf_2_5_TimeCode * this_
    , _Bool value)
{
    (to_cpp(this_)) -> setBgf0(value);
}

_Bool Imf_2_5_TimeCode_bgf1(
    Imf_2_5_TimeCode const * this_)
{
    return (to_cpp(this_)) -> bgf1();
}

void Imf_2_5_TimeCode_setBgf1(
    Imf_2_5_TimeCode * this_
    , _Bool value)
{
    (to_cpp(this_)) -> setBgf1(value);
}

_Bool Imf_2_5_TimeCode_bgf2(
    Imf_2_5_TimeCode const * this_)
{
    return (to_cpp(this_)) -> bgf2();
}

void Imf_2_5_TimeCode_setBgf2(
    Imf_2_5_TimeCode * this_
    , _Bool value)
{
    (to_cpp(this_)) -> setBgf2(value);
}

int Imf_2_5_TimeCode_binaryGroup(
    Imf_2_5_TimeCode const * this_
    , int group)
{
    return (to_cpp(this_)) -> binaryGroup(group);
}

void Imf_2_5_TimeCode_setBinaryGroup(
    Imf_2_5_TimeCode * this_
    , int group
    , int value)
{
    (to_cpp(this_)) -> setBinaryGroup(group, value);
}

unsigned int Imf_2_5_TimeCode_userData(
    Imf_2_5_TimeCode const * this_)
{
    return (to_cpp(this_)) -> userData();
}

void Imf_2_5_TimeCode_setUserData(
    Imf_2_5_TimeCode * this_
    , unsigned int value)
{
    (to_cpp(this_)) -> setUserData(value);
}

_Bool Imf_2_5_TimeCode__eq(
    Imf_2_5_TimeCode const * this_
    , Imf_2_5_TimeCode const * v)
{
    return (to_cpp(this_)) -> operator==(to_cpp_ref(v));
}

_Bool Imf_2_5_TimeCode__ne(
    Imf_2_5_TimeCode const * this_
    , Imf_2_5_TimeCode const * v)
{
    return (to_cpp(this_)) -> operator!=(to_cpp_ref(v));
}
