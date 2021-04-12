#include <imf_io_private_.h>



void Imf_2_5_OStream_dtor(
    Imf_2_5_OStream * this_)
{
    (to_cpp(this_)) -> Imf_2_5::OStream::~OStream();
}

void Imf_2_5_OStream_write(
    Imf_2_5_OStream * this_
    , char const * c
    , int n)
{
    (to_cpp(this_)) -> write(c, n);
}

unsigned long Imf_2_5_OStream_tellp(
    Imf_2_5_OStream * this_)
{
    return (to_cpp(this_)) -> tellp();
}

void Imf_2_5_OStream_seekp(
    Imf_2_5_OStream * this_
    , unsigned long pos)
{
    (to_cpp(this_)) -> seekp(pos);
}

char const * Imf_2_5_OStream_fileName(
    Imf_2_5_OStream const * this_)
{
    return (to_cpp(this_)) -> fileName();
}

void Imf_2_5_IStream_dtor(
    Imf_2_5_IStream * this_)
{
    (to_cpp(this_)) -> Imf_2_5::IStream::~IStream();
}

_Bool Imf_2_5_IStream_isMemoryMapped(
    Imf_2_5_IStream const * this_)
{
    return (to_cpp(this_)) -> isMemoryMapped();
}

_Bool Imf_2_5_IStream_read(
    Imf_2_5_IStream * this_
    , char * c
    , int n)
{
    return (to_cpp(this_)) -> read(c, n);
}

char * Imf_2_5_IStream_readMemoryMapped(
    Imf_2_5_IStream * this_
    , int n)
{
    return (to_cpp(this_)) -> readMemoryMapped(n);
}

unsigned long Imf_2_5_IStream_tellg(
    Imf_2_5_IStream * this_)
{
    return (to_cpp(this_)) -> tellg();
}

void Imf_2_5_IStream_seekg(
    Imf_2_5_IStream * this_
    , unsigned long pos)
{
    (to_cpp(this_)) -> seekg(pos);
}

void Imf_2_5_IStream_clear(
    Imf_2_5_IStream * this_)
{
    (to_cpp(this_)) -> clear();
}

char const * Imf_2_5_IStream_fileName(
    Imf_2_5_IStream const * this_)
{
    return (to_cpp(this_)) -> fileName();
}
