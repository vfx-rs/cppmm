#include <imf_framebuffer_private_.h>

#include <new>


void Imf_2_5_Slice_Slice(
    Imf_2_5_Slice * this_
    , Imf_2_5_Slice const * rhs)
{
    new (this_) Imf_2_5::Slice(to_cpp_ref(rhs));
}

void Imf_2_5_FrameBuffer_insert(
    Imf_2_5_FrameBuffer * this_
    , char const * name
    , Imf_2_5_Slice const * slice)
{
    (to_cpp(this_)) -> insert(name, to_cpp_ref(slice));
}

Imf_2_5_Slice * Imf_2_5_FrameBuffer__index(
    Imf_2_5_FrameBuffer * this_
    , char const * name)
{
    return to_c((to_cpp(this_)) -> operator[](name));
}

Imf_2_5_Slice const * Imf_2_5_FrameBuffer__index_1(
    Imf_2_5_FrameBuffer const * this_
    , char const * name)
{
    return to_c((to_cpp(this_)) -> operator[](name));
}

Imf_2_5_Slice * Imf_2_5_FrameBuffer_findSlice(
    Imf_2_5_FrameBuffer * this_
    , char const * name)
{
    return to_c((to_cpp(this_)) -> findSlice(name));
}

Imf_2_5_Slice const * Imf_2_5_FrameBuffer_findSlice_1(
    Imf_2_5_FrameBuffer const * this_
    , char const * name)
{
    return to_c((to_cpp(this_)) -> findSlice(name));
}

Imf_2_5_FrameBuffer_Iterator Imf_2_5_FrameBuffer_begin(
    Imf_2_5_FrameBuffer * this_)
{
    return to_c_copy((to_cpp(this_)) -> begin());
}

Imf_2_5_FrameBuffer_ConstIterator Imf_2_5_FrameBuffer_begin_1(
    Imf_2_5_FrameBuffer const * this_)
{
    return to_c_copy((to_cpp(this_)) -> begin());
}

Imf_2_5_FrameBuffer_Iterator Imf_2_5_FrameBuffer_end(
    Imf_2_5_FrameBuffer * this_)
{
    return to_c_copy((to_cpp(this_)) -> end());
}

Imf_2_5_FrameBuffer_ConstIterator Imf_2_5_FrameBuffer_end_1(
    Imf_2_5_FrameBuffer const * this_)
{
    return to_c_copy((to_cpp(this_)) -> end());
}

Imf_2_5_FrameBuffer_Iterator Imf_2_5_FrameBuffer_find(
    Imf_2_5_FrameBuffer * this_
    , char const * name)
{
    return to_c_copy((to_cpp(this_)) -> find(name));
}

Imf_2_5_FrameBuffer_ConstIterator Imf_2_5_FrameBuffer_find_1(
    Imf_2_5_FrameBuffer const * this_
    , char const * name)
{
    return to_c_copy((to_cpp(this_)) -> find(name));
}

void Imf_2_5_FrameBuffer_Iterator_Iterator(
    Imf_2_5_FrameBuffer_Iterator * this_)
{
    new (this_) Imf_2_5::FrameBuffer::Iterator();
}

char const * Imf_2_5_FrameBuffer_Iterator_name(
    Imf_2_5_FrameBuffer_Iterator const * this_)
{
    return (to_cpp(this_)) -> name();
}

Imf_2_5_Slice * Imf_2_5_FrameBuffer_Iterator_slice(
    Imf_2_5_FrameBuffer_Iterator const * this_)
{
    return to_c((to_cpp(this_)) -> slice());
}

void Imf_2_5_FrameBuffer_Iterator_Iterator_1(
    Imf_2_5_FrameBuffer_Iterator * this_
    , Imf_2_5_FrameBuffer_Iterator const * rhs)
{
    new (this_) Imf_2_5::FrameBuffer::Iterator(to_cpp_ref(rhs));
}

void Imf_2_5_FrameBuffer_ConstIterator_ConstIterator(
    Imf_2_5_FrameBuffer_ConstIterator * this_)
{
    new (this_) Imf_2_5::FrameBuffer::ConstIterator();
}

char const * Imf_2_5_FrameBuffer_ConstIterator_name(
    Imf_2_5_FrameBuffer_ConstIterator const * this_)
{
    return (to_cpp(this_)) -> name();
}

void Imf_2_5_FrameBuffer_ConstIterator_ConstIterator_1(
    Imf_2_5_FrameBuffer_ConstIterator * this_
    , Imf_2_5_FrameBuffer_ConstIterator const * rhs)
{
    new (this_) Imf_2_5::FrameBuffer::ConstIterator(to_cpp_ref(rhs));
}
