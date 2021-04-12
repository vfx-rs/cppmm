#pragma once
#include <imf_framebuffer_.h>


#include <OpenEXR/ImfFrameBuffer.h>
#include <cppmm_bind.hpp>



inline Imf_2_5::Slice const & to_cpp_ref(
    Imf_2_5_Slice const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::Slice const * >(rhs));
}


inline Imf_2_5::Slice & to_cpp_ref(
    Imf_2_5_Slice * rhs)
{
    return *(reinterpret_cast<Imf_2_5::Slice * >(rhs));
}


inline Imf_2_5::Slice const * to_cpp(
    Imf_2_5_Slice const * rhs)
{
    return reinterpret_cast<Imf_2_5::Slice const * >(rhs);
}


inline Imf_2_5::Slice * to_cpp(
    Imf_2_5_Slice * rhs)
{
    return reinterpret_cast<Imf_2_5::Slice * >(rhs);
}


inline Imf_2_5_Slice const * to_c(
    Imf_2_5::Slice const & rhs)
{
    return reinterpret_cast<Imf_2_5_Slice const * >(&(rhs));
}


inline Imf_2_5_Slice const * to_c(
    Imf_2_5::Slice const * rhs)
{
    return reinterpret_cast<Imf_2_5_Slice const * >(rhs);
}


inline Imf_2_5_Slice * to_c(
    Imf_2_5::Slice & rhs)
{
    return reinterpret_cast<Imf_2_5_Slice * >(&(rhs));
}


inline Imf_2_5_Slice * to_c(
    Imf_2_5::Slice * rhs)
{
    return reinterpret_cast<Imf_2_5_Slice * >(rhs);
}


inline Imf_2_5_Slice to_c_copy(
    Imf_2_5::Slice const & rhs)
{
    Imf_2_5_Slice result;
    Imf_2_5_Slice_Slice(&(result), reinterpret_cast<Imf_2_5_Slice const * >(&(rhs)));
    return result;
}













inline Imf_2_5::FrameBuffer const & to_cpp_ref(
    Imf_2_5_FrameBuffer const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::FrameBuffer const * >(rhs));
}


inline Imf_2_5::FrameBuffer & to_cpp_ref(
    Imf_2_5_FrameBuffer * rhs)
{
    return *(reinterpret_cast<Imf_2_5::FrameBuffer * >(rhs));
}


inline Imf_2_5::FrameBuffer const * to_cpp(
    Imf_2_5_FrameBuffer const * rhs)
{
    return reinterpret_cast<Imf_2_5::FrameBuffer const * >(rhs);
}


inline Imf_2_5::FrameBuffer * to_cpp(
    Imf_2_5_FrameBuffer * rhs)
{
    return reinterpret_cast<Imf_2_5::FrameBuffer * >(rhs);
}


inline Imf_2_5_FrameBuffer const * to_c(
    Imf_2_5::FrameBuffer const & rhs)
{
    return reinterpret_cast<Imf_2_5_FrameBuffer const * >(&(rhs));
}


inline Imf_2_5_FrameBuffer const * to_c(
    Imf_2_5::FrameBuffer const * rhs)
{
    return reinterpret_cast<Imf_2_5_FrameBuffer const * >(rhs);
}


inline Imf_2_5_FrameBuffer * to_c(
    Imf_2_5::FrameBuffer & rhs)
{
    return reinterpret_cast<Imf_2_5_FrameBuffer * >(&(rhs));
}


inline Imf_2_5_FrameBuffer * to_c(
    Imf_2_5::FrameBuffer * rhs)
{
    return reinterpret_cast<Imf_2_5_FrameBuffer * >(rhs);
}






inline Imf_2_5::FrameBuffer::Iterator const & to_cpp_ref(
    Imf_2_5_FrameBuffer_Iterator const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::FrameBuffer::Iterator const * >(rhs));
}


inline Imf_2_5::FrameBuffer::Iterator & to_cpp_ref(
    Imf_2_5_FrameBuffer_Iterator * rhs)
{
    return *(reinterpret_cast<Imf_2_5::FrameBuffer::Iterator * >(rhs));
}


inline Imf_2_5::FrameBuffer::Iterator const * to_cpp(
    Imf_2_5_FrameBuffer_Iterator const * rhs)
{
    return reinterpret_cast<Imf_2_5::FrameBuffer::Iterator const * >(rhs);
}


inline Imf_2_5::FrameBuffer::Iterator * to_cpp(
    Imf_2_5_FrameBuffer_Iterator * rhs)
{
    return reinterpret_cast<Imf_2_5::FrameBuffer::Iterator * >(rhs);
}


inline Imf_2_5_FrameBuffer_Iterator const * to_c(
    Imf_2_5::FrameBuffer::Iterator const & rhs)
{
    return reinterpret_cast<Imf_2_5_FrameBuffer_Iterator const * >(&(rhs));
}


inline Imf_2_5_FrameBuffer_Iterator const * to_c(
    Imf_2_5::FrameBuffer::Iterator const * rhs)
{
    return reinterpret_cast<Imf_2_5_FrameBuffer_Iterator const * >(rhs);
}


inline Imf_2_5_FrameBuffer_Iterator * to_c(
    Imf_2_5::FrameBuffer::Iterator & rhs)
{
    return reinterpret_cast<Imf_2_5_FrameBuffer_Iterator * >(&(rhs));
}


inline Imf_2_5_FrameBuffer_Iterator * to_c(
    Imf_2_5::FrameBuffer::Iterator * rhs)
{
    return reinterpret_cast<Imf_2_5_FrameBuffer_Iterator * >(rhs);
}


inline Imf_2_5_FrameBuffer_Iterator to_c_copy(
    Imf_2_5::FrameBuffer::Iterator const & rhs)
{
    Imf_2_5_FrameBuffer_Iterator result;
    Imf_2_5_FrameBuffer_Iterator_Iterator_1(&(result), reinterpret_cast<Imf_2_5_FrameBuffer_Iterator const * >(&(rhs)));
    return result;
}





inline Imf_2_5::FrameBuffer::ConstIterator const & to_cpp_ref(
    Imf_2_5_FrameBuffer_ConstIterator const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::FrameBuffer::ConstIterator const * >(rhs));
}


inline Imf_2_5::FrameBuffer::ConstIterator & to_cpp_ref(
    Imf_2_5_FrameBuffer_ConstIterator * rhs)
{
    return *(reinterpret_cast<Imf_2_5::FrameBuffer::ConstIterator * >(rhs));
}


inline Imf_2_5::FrameBuffer::ConstIterator const * to_cpp(
    Imf_2_5_FrameBuffer_ConstIterator const * rhs)
{
    return reinterpret_cast<Imf_2_5::FrameBuffer::ConstIterator const * >(rhs);
}


inline Imf_2_5::FrameBuffer::ConstIterator * to_cpp(
    Imf_2_5_FrameBuffer_ConstIterator * rhs)
{
    return reinterpret_cast<Imf_2_5::FrameBuffer::ConstIterator * >(rhs);
}


inline Imf_2_5_FrameBuffer_ConstIterator const * to_c(
    Imf_2_5::FrameBuffer::ConstIterator const & rhs)
{
    return reinterpret_cast<Imf_2_5_FrameBuffer_ConstIterator const * >(&(rhs));
}


inline Imf_2_5_FrameBuffer_ConstIterator const * to_c(
    Imf_2_5::FrameBuffer::ConstIterator const * rhs)
{
    return reinterpret_cast<Imf_2_5_FrameBuffer_ConstIterator const * >(rhs);
}


inline Imf_2_5_FrameBuffer_ConstIterator * to_c(
    Imf_2_5::FrameBuffer::ConstIterator & rhs)
{
    return reinterpret_cast<Imf_2_5_FrameBuffer_ConstIterator * >(&(rhs));
}


inline Imf_2_5_FrameBuffer_ConstIterator * to_c(
    Imf_2_5::FrameBuffer::ConstIterator * rhs)
{
    return reinterpret_cast<Imf_2_5_FrameBuffer_ConstIterator * >(rhs);
}


inline Imf_2_5_FrameBuffer_ConstIterator to_c_copy(
    Imf_2_5::FrameBuffer::ConstIterator const & rhs)
{
    Imf_2_5_FrameBuffer_ConstIterator result;
    Imf_2_5_FrameBuffer_ConstIterator_ConstIterator_1(&(result), reinterpret_cast<Imf_2_5_FrameBuffer_ConstIterator const * >(&(rhs)));
    return result;
}
