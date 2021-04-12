#include <imf_multipartoutputfile_private_.h>

#include <imf_header_private_.h>
#include <imf_io_private_.h>
#include <new>


void Imf_2_5_MultiPartOutputFile_MultiPartOutputFile(
    Imf_2_5_MultiPartOutputFile * this_
    , char const * fileName
    , Imf_2_5_Header const * headers
    , int parts
    , _Bool overrideSharedAttributes
    , int numThreads)
{
    new (this_) Imf_2_5::MultiPartOutputFile(fileName, to_cpp(headers), parts, overrideSharedAttributes, numThreads);
}

void Imf_2_5_MultiPartOutputFile_MultiPartOutputFile_1(
    Imf_2_5_MultiPartOutputFile * this_
    , Imf_2_5_OStream * os
    , Imf_2_5_Header const * headers
    , int parts
    , _Bool overrideSharedAttributes
    , int numThreads)
{
    new (this_) Imf_2_5::MultiPartOutputFile(to_cpp_ref(os), to_cpp(headers), parts, overrideSharedAttributes, numThreads);
}

int Imf_2_5_MultiPartOutputFile_parts(
    Imf_2_5_MultiPartOutputFile const * this_)
{
    return (to_cpp(this_)) -> parts();
}

Imf_2_5_Header const * Imf_2_5_MultiPartOutputFile_header(
    Imf_2_5_MultiPartOutputFile const * this_
    , int n)
{
    return to_c((to_cpp(this_)) -> header(n));
}

void Imf_2_5_MultiPartOutputFile_dtor(
    Imf_2_5_MultiPartOutputFile * this_)
{
    (to_cpp(this_)) -> Imf_2_5::MultiPartOutputFile::~MultiPartOutputFile();
}
