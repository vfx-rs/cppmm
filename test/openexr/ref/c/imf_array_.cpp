#include <imf_array_private_.h>

#include <new>


void Imf_2_5_ArrayFloat_Array(
    Imf_2_5_ArrayFloat * this_)
{
    new (this_) Imf_2_5::Array<float>();
}

void Imf_2_5_ArrayFloat_Array_1(
    Imf_2_5_ArrayFloat * this_
    , long size)
{
    new (this_) Imf_2_5::Array<float>(size);
}

void Imf_2_5_ArrayFloat_dtor(
    Imf_2_5_ArrayFloat * this_)
{
    (to_cpp(this_)) -> Imf_2_5::Array<float>::~Array();
}

float * Imf_2_5_ArrayFloat_operatorfloat_(
    Imf_2_5_ArrayFloat * this_)
{
    return (to_cpp(this_)) -> operator float *();
}

float const * Imf_2_5_ArrayFloat_operatorconstfloat_(
    Imf_2_5_ArrayFloat const * this_)
{
    return (to_cpp(this_)) -> operator const float *();
}

void Imf_2_5_ArrayFloat_resizeErase(
    Imf_2_5_ArrayFloat * this_
    , long size)
{
    (to_cpp(this_)) -> resizeErase(size);
}

void Imf_2_5_ArrayFloat_resizeEraseUnsafe(
    Imf_2_5_ArrayFloat * this_
    , long size)
{
    (to_cpp(this_)) -> resizeEraseUnsafe(size);
}

long Imf_2_5_ArrayFloat_size(
    Imf_2_5_ArrayFloat const * this_)
{
    return (to_cpp(this_)) -> size();
}

void Imf_2_5_Array2DFloat_Array2D(
    Imf_2_5_Array2DFloat * this_)
{
    new (this_) Imf_2_5::Array2D<float>();
}

void Imf_2_5_Array2DFloat_Array2D_1(
    Imf_2_5_Array2DFloat * this_
    , long sizeX
    , long sizeY)
{
    new (this_) Imf_2_5::Array2D<float>(sizeX, sizeY);
}

void Imf_2_5_Array2DFloat_dtor(
    Imf_2_5_Array2DFloat * this_)
{
    (to_cpp(this_)) -> Imf_2_5::Array2D<float>::~Array2D();
}

float * Imf_2_5_Array2DFloat__index(
    Imf_2_5_Array2DFloat * this_
    , long x)
{
    return (to_cpp(this_)) -> operator[](x);
}

float const * Imf_2_5_Array2DFloat__index_1(
    Imf_2_5_Array2DFloat const * this_
    , long x)
{
    return (to_cpp(this_)) -> operator[](x);
}

void Imf_2_5_Array2DFloat_resizeErase(
    Imf_2_5_Array2DFloat * this_
    , long sizeX
    , long sizeY)
{
    (to_cpp(this_)) -> resizeErase(sizeX, sizeY);
}

void Imf_2_5_Array2DFloat_resizeEraseUnsafe(
    Imf_2_5_Array2DFloat * this_
    , long sizeX
    , long sizeY)
{
    (to_cpp(this_)) -> resizeEraseUnsafe(sizeX, sizeY);
}

long Imf_2_5_Array2DFloat_height(
    Imf_2_5_Array2DFloat const * this_)
{
    return (to_cpp(this_)) -> height();
}

long Imf_2_5_Array2DFloat_width(
    Imf_2_5_Array2DFloat const * this_)
{
    return (to_cpp(this_)) -> width();
}
