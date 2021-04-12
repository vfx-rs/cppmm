#include <imf_deepframebuffer_private_.h>

#include <imf_framebuffer_private_.h>
#include <new>


void Imf_2_5_DeepSlice_DeepSlice(
    Imf_2_5_DeepSlice * this_
    , Imf_2_5_DeepSlice const * rhs)
{
    new (this_) Imf_2_5::DeepSlice(to_cpp_ref(rhs));
}

void Imf_2_5_DeepFrameBuffer_insert(
    Imf_2_5_DeepFrameBuffer * this_
    , char const * name
    , Imf_2_5_DeepSlice const * slice)
{
    (to_cpp(this_)) -> insert(name, to_cpp_ref(slice));
}

Imf_2_5_DeepSlice * Imf_2_5_DeepFrameBuffer__index(
    Imf_2_5_DeepFrameBuffer * this_
    , char const * name)
{
    return to_c((to_cpp(this_)) -> operator[](name));
}

Imf_2_5_DeepSlice const * Imf_2_5_DeepFrameBuffer__index_1(
    Imf_2_5_DeepFrameBuffer const * this_
    , char const * name)
{
    return to_c((to_cpp(this_)) -> operator[](name));
}

Imf_2_5_DeepSlice * Imf_2_5_DeepFrameBuffer_findSlice(
    Imf_2_5_DeepFrameBuffer * this_
    , char const * name)
{
    return to_c((to_cpp(this_)) -> findSlice(name));
}

Imf_2_5_DeepSlice const * Imf_2_5_DeepFrameBuffer_findSlice_1(
    Imf_2_5_DeepFrameBuffer const * this_
    , char const * name)
{
    return to_c((to_cpp(this_)) -> findSlice(name));
}

Imf_2_5_DeepFrameBuffer_Iterator Imf_2_5_DeepFrameBuffer_begin(
    Imf_2_5_DeepFrameBuffer * this_)
{
    return to_c_copy((to_cpp(this_)) -> begin());
}

Imf_2_5_DeepFrameBuffer_ConstIterator Imf_2_5_DeepFrameBuffer_begin_1(
    Imf_2_5_DeepFrameBuffer const * this_)
{
    return to_c_copy((to_cpp(this_)) -> begin());
}

Imf_2_5_DeepFrameBuffer_Iterator Imf_2_5_DeepFrameBuffer_end(
    Imf_2_5_DeepFrameBuffer * this_)
{
    return to_c_copy((to_cpp(this_)) -> end());
}

Imf_2_5_DeepFrameBuffer_ConstIterator Imf_2_5_DeepFrameBuffer_end_1(
    Imf_2_5_DeepFrameBuffer const * this_)
{
    return to_c_copy((to_cpp(this_)) -> end());
}

Imf_2_5_DeepFrameBuffer_Iterator Imf_2_5_DeepFrameBuffer_find(
    Imf_2_5_DeepFrameBuffer * this_
    , char const * name)
{
    return to_c_copy((to_cpp(this_)) -> find(name));
}

Imf_2_5_DeepFrameBuffer_ConstIterator Imf_2_5_DeepFrameBuffer_find_1(
    Imf_2_5_DeepFrameBuffer const * this_
    , char const * name)
{
    return to_c_copy((to_cpp(this_)) -> find(name));
}

void Imf_2_5_DeepFrameBuffer_insertSampleCountSlice(
    Imf_2_5_DeepFrameBuffer * this_
    , Imf_2_5_Slice const * slice)
{
    (to_cpp(this_)) -> insertSampleCountSlice(to_cpp_ref(slice));
}

Imf_2_5_Slice const * Imf_2_5_DeepFrameBuffer_getSampleCountSlice(
    Imf_2_5_DeepFrameBuffer const * this_)
{
    return to_c((to_cpp(this_)) -> getSampleCountSlice());
}

void Imf_2_5_DeepFrameBuffer_Iterator_Iterator(
    Imf_2_5_DeepFrameBuffer_Iterator * this_)
{
    new (this_) Imf_2_5::DeepFrameBuffer::Iterator();
}

char const * Imf_2_5_DeepFrameBuffer_Iterator_name(
    Imf_2_5_DeepFrameBuffer_Iterator const * this_)
{
    return (to_cpp(this_)) -> name();
}

Imf_2_5_DeepSlice * Imf_2_5_DeepFrameBuffer_Iterator_slice(
    Imf_2_5_DeepFrameBuffer_Iterator const * this_)
{
    return to_c((to_cpp(this_)) -> slice());
}

void Imf_2_5_DeepFrameBuffer_Iterator_Iterator_1(
    Imf_2_5_DeepFrameBuffer_Iterator * this_
    , Imf_2_5_DeepFrameBuffer_Iterator const * rhs)
{
    new (this_) Imf_2_5::DeepFrameBuffer::Iterator(to_cpp_ref(rhs));
}

void Imf_2_5_DeepFrameBuffer_ConstIterator_ConstIterator(
    Imf_2_5_DeepFrameBuffer_ConstIterator * this_)
{
    new (this_) Imf_2_5::DeepFrameBuffer::ConstIterator();
}

char const * Imf_2_5_DeepFrameBuffer_ConstIterator_name(
    Imf_2_5_DeepFrameBuffer_ConstIterator const * this_)
{
    return (to_cpp(this_)) -> name();
}

void Imf_2_5_DeepFrameBuffer_ConstIterator_ConstIterator_1(
    Imf_2_5_DeepFrameBuffer_ConstIterator * this_
    , Imf_2_5_DeepFrameBuffer_ConstIterator const * rhs)
{
    new (this_) Imf_2_5::DeepFrameBuffer::ConstIterator(to_cpp_ref(rhs));
}
