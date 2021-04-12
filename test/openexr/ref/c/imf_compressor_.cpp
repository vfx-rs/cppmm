#include <imf_compressor_private_.h>

#include <imath_box_private_.h>


void Imf_2_5_Compressor_dtor(
    Imf_2_5_Compressor * this_)
{
    (to_cpp(this_)) -> Imf_2_5::Compressor::~Compressor();
}

int Imf_2_5_Compressor_numScanLines(
    Imf_2_5_Compressor const * this_)
{
    return (to_cpp(this_)) -> numScanLines();
}

int Imf_2_5_Compressor_compress(
    Imf_2_5_Compressor * this_
    , char const * inPtr
    , int inSize
    , int minY
    , char const * * outPtr)
{
    return (to_cpp(this_)) -> compress(inPtr, inSize, minY, *(outPtr));
}

int Imf_2_5_Compressor_compressTile(
    Imf_2_5_Compressor * this_
    , char const * inPtr
    , int inSize
    , Imath_2_5_Box2i range
    , char const * * outPtr)
{
    return (to_cpp(this_)) -> compressTile(inPtr, inSize, to_cpp_ref(&(range)), *(outPtr));
}

int Imf_2_5_Compressor_uncompress(
    Imf_2_5_Compressor * this_
    , char const * inPtr
    , int inSize
    , int minY
    , char const * * outPtr)
{
    return (to_cpp(this_)) -> uncompress(inPtr, inSize, minY, *(outPtr));
}

int Imf_2_5_Compressor_uncompressTile(
    Imf_2_5_Compressor * this_
    , char const * inPtr
    , int inSize
    , Imath_2_5_Box2i range
    , char const * * outPtr)
{
    return (to_cpp(this_)) -> uncompressTile(inPtr, inSize, to_cpp_ref(&(range)), *(outPtr));
}
