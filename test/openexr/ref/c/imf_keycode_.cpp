#include <imf_keycode_private_.h>

#include <new>


void Imf_2_5_KeyCode_KeyCode(
    Imf_2_5_KeyCode * this_
    , int filmMfcCode
    , int filmType
    , int prefix
    , int count
    , int perfOffset
    , int perfsPerFrame
    , int perfsPerCount)
{
    new (this_) Imf_2_5::KeyCode(filmMfcCode, filmType, prefix, count, perfOffset, perfsPerFrame, perfsPerCount);
}

void Imf_2_5_KeyCode_KeyCode_1(
    Imf_2_5_KeyCode * this_
    , Imf_2_5_KeyCode const * other)
{
    new (this_) Imf_2_5::KeyCode(to_cpp_ref(other));
}

void Imf_2_5_KeyCode_dtor(
    Imf_2_5_KeyCode * this_)
{
    (to_cpp(this_)) -> Imf_2_5::KeyCode::~KeyCode();
}

Imf_2_5_KeyCode * Imf_2_5_KeyCode__assign(
    Imf_2_5_KeyCode * this_
    , Imf_2_5_KeyCode const * other)
{
    return to_c((to_cpp(this_)) -> operator=(to_cpp_ref(other)));
}

int Imf_2_5_KeyCode_filmMfcCode(
    Imf_2_5_KeyCode const * this_)
{
    return (to_cpp(this_)) -> filmMfcCode();
}

void Imf_2_5_KeyCode_setFilmMfcCode(
    Imf_2_5_KeyCode * this_
    , int filmMfcCode)
{
    (to_cpp(this_)) -> setFilmMfcCode(filmMfcCode);
}

int Imf_2_5_KeyCode_filmType(
    Imf_2_5_KeyCode const * this_)
{
    return (to_cpp(this_)) -> filmType();
}

void Imf_2_5_KeyCode_setFilmType(
    Imf_2_5_KeyCode * this_
    , int filmType)
{
    (to_cpp(this_)) -> setFilmType(filmType);
}

int Imf_2_5_KeyCode_prefix(
    Imf_2_5_KeyCode const * this_)
{
    return (to_cpp(this_)) -> prefix();
}

void Imf_2_5_KeyCode_setPrefix(
    Imf_2_5_KeyCode * this_
    , int prefix)
{
    (to_cpp(this_)) -> setPrefix(prefix);
}

int Imf_2_5_KeyCode_count(
    Imf_2_5_KeyCode const * this_)
{
    return (to_cpp(this_)) -> count();
}

void Imf_2_5_KeyCode_setCount(
    Imf_2_5_KeyCode * this_
    , int count)
{
    (to_cpp(this_)) -> setCount(count);
}

int Imf_2_5_KeyCode_perfOffset(
    Imf_2_5_KeyCode const * this_)
{
    return (to_cpp(this_)) -> perfOffset();
}

void Imf_2_5_KeyCode_setPerfOffset(
    Imf_2_5_KeyCode * this_
    , int perfOffset)
{
    (to_cpp(this_)) -> setPerfOffset(perfOffset);
}

int Imf_2_5_KeyCode_perfsPerFrame(
    Imf_2_5_KeyCode const * this_)
{
    return (to_cpp(this_)) -> perfsPerFrame();
}

void Imf_2_5_KeyCode_setPerfsPerFrame(
    Imf_2_5_KeyCode * this_
    , int perfsPerFrame)
{
    (to_cpp(this_)) -> setPerfsPerFrame(perfsPerFrame);
}

int Imf_2_5_KeyCode_perfsPerCount(
    Imf_2_5_KeyCode const * this_)
{
    return (to_cpp(this_)) -> perfsPerCount();
}

void Imf_2_5_KeyCode_setPerfsPerCount(
    Imf_2_5_KeyCode * this_
    , int perfsPerCount)
{
    (to_cpp(this_)) -> setPerfsPerCount(perfsPerCount);
}
