#include <imf_multipartinputfile_private_.h>

#include <imf_header_private_.h>
#include <imf_io_private_.h>
#include <new>


void Imf_2_5_MultiPartInputFile_MultiPartInputFile(
    Imf_2_5_MultiPartInputFile * this_
    , char const * fileName
    , int numThreads
    , _Bool reconstructChunkOffsetTable)
{
    new (this_) Imf_2_5::MultiPartInputFile(fileName, numThreads, reconstructChunkOffsetTable);
}

void Imf_2_5_MultiPartInputFile_MultiPartInputFile_1(
    Imf_2_5_MultiPartInputFile * this_
    , Imf_2_5_IStream * is
    , int numThreads
    , _Bool reconstructChunkOffsetTable)
{
    new (this_) Imf_2_5::MultiPartInputFile(to_cpp_ref(is), numThreads, reconstructChunkOffsetTable);
}

void Imf_2_5_MultiPartInputFile_dtor(
    Imf_2_5_MultiPartInputFile * this_)
{
    (to_cpp(this_)) -> Imf_2_5::MultiPartInputFile::~MultiPartInputFile();
}

int Imf_2_5_MultiPartInputFile_parts(
    Imf_2_5_MultiPartInputFile const * this_)
{
    return (to_cpp(this_)) -> parts();
}

Imf_2_5_Header const * Imf_2_5_MultiPartInputFile_header(
    Imf_2_5_MultiPartInputFile const * this_
    , int n)
{
    return to_c((to_cpp(this_)) -> header(n));
}

int Imf_2_5_MultiPartInputFile_version(
    Imf_2_5_MultiPartInputFile const * this_)
{
    return (to_cpp(this_)) -> version();
}

_Bool Imf_2_5_MultiPartInputFile_partComplete(
    Imf_2_5_MultiPartInputFile const * this_
    , int part)
{
    return (to_cpp(this_)) -> partComplete(part);
}
