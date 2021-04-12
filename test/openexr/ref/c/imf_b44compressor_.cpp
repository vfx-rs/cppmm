#include <imf_b44compressor_private_.h>

#include <imath_box_private_.h>
#include <imf_header_private_.h>
#include <new>


int Imf_2_5_B44Compressor_numScanLines(
    Imf_2_5_B44Compressor const * this_)
{
    return (to_cpp(this_)) -> numScanLines();
}

int Imf_2_5_B44Compressor_compress(
    Imf_2_5_B44Compressor * this_
    , char const * inPtr
    , int inSize
    , int minY
    , char const * * outPtr)
{
    return (to_cpp(this_)) -> compress(inPtr, inSize, minY, *(outPtr));
}

int Imf_2_5_B44Compressor_compressTile(
    Imf_2_5_B44Compressor * this_
    , char const * inPtr
    , int inSize
    , Imath_2_5_Box2i range
    , char const * * outPtr)
{
    return (to_cpp(this_)) -> compressTile(inPtr, inSize, to_cpp_ref(&(range)), *(outPtr));
}

int Imf_2_5_B44Compressor_uncompress(
    Imf_2_5_B44Compressor * this_
    , char const * inPtr
    , int inSize
    , int minY
    , char const * * outPtr)
{
    return (to_cpp(this_)) -> uncompress(inPtr, inSize, minY, *(outPtr));
}

int Imf_2_5_B44Compressor_uncompressTile(
    Imf_2_5_B44Compressor * this_
    , char const * inPtr
    , int inSize
    , Imath_2_5_Box2i range
    , char const * * outPtr)
{
    return (to_cpp(this_)) -> uncompressTile(inPtr, inSize, to_cpp_ref(&(range)), *(outPtr));
}

void Imf_2_5_B44Compressor_B44Compressor(
    Imf_2_5_B44Compressor * this_
    , Imf_2_5_Header const * hdr
    , unsigned long maxScanLineSize
    , unsigned long numScanLines
    , _Bool optFlatFields)
{
    new (this_) Imf_2_5::B44Compressor(to_cpp_ref(hdr), maxScanLineSize, numScanLines, optFlatFields);
}

void Imf_2_5_B44Compressor_dtor(
    Imf_2_5_B44Compressor * this_)
{
    (to_cpp(this_)) -> Imf_2_5::B44Compressor::~B44Compressor();
}
