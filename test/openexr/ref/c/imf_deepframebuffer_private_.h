#pragma once
#include <imf_deepframebuffer_.h>


#include <OpenEXR/ImfDeepFrameBuffer.h>
#include <cppmm_bind.hpp>



inline Imf_2_5::DeepSlice const & to_cpp_ref(
    Imf_2_5_DeepSlice const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::DeepSlice const * >(rhs));
}


inline Imf_2_5::DeepSlice & to_cpp_ref(
    Imf_2_5_DeepSlice * rhs)
{
    return *(reinterpret_cast<Imf_2_5::DeepSlice * >(rhs));
}


inline Imf_2_5::DeepSlice const * to_cpp(
    Imf_2_5_DeepSlice const * rhs)
{
    return reinterpret_cast<Imf_2_5::DeepSlice const * >(rhs);
}


inline Imf_2_5::DeepSlice * to_cpp(
    Imf_2_5_DeepSlice * rhs)
{
    return reinterpret_cast<Imf_2_5::DeepSlice * >(rhs);
}


inline Imf_2_5_DeepSlice const * to_c(
    Imf_2_5::DeepSlice const & rhs)
{
    return reinterpret_cast<Imf_2_5_DeepSlice const * >(&(rhs));
}


inline Imf_2_5_DeepSlice const * to_c(
    Imf_2_5::DeepSlice const * rhs)
{
    return reinterpret_cast<Imf_2_5_DeepSlice const * >(rhs);
}


inline Imf_2_5_DeepSlice * to_c(
    Imf_2_5::DeepSlice & rhs)
{
    return reinterpret_cast<Imf_2_5_DeepSlice * >(&(rhs));
}


inline Imf_2_5_DeepSlice * to_c(
    Imf_2_5::DeepSlice * rhs)
{
    return reinterpret_cast<Imf_2_5_DeepSlice * >(rhs);
}


inline Imf_2_5_DeepSlice to_c_copy(
    Imf_2_5::DeepSlice const & rhs)
{
    Imf_2_5_DeepSlice result;
    Imf_2_5_DeepSlice_DeepSlice(&(result), reinterpret_cast<Imf_2_5_DeepSlice const * >(&(rhs)));
    return result;
}















inline Imf_2_5::DeepFrameBuffer const & to_cpp_ref(
    Imf_2_5_DeepFrameBuffer const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::DeepFrameBuffer const * >(rhs));
}


inline Imf_2_5::DeepFrameBuffer & to_cpp_ref(
    Imf_2_5_DeepFrameBuffer * rhs)
{
    return *(reinterpret_cast<Imf_2_5::DeepFrameBuffer * >(rhs));
}


inline Imf_2_5::DeepFrameBuffer const * to_cpp(
    Imf_2_5_DeepFrameBuffer const * rhs)
{
    return reinterpret_cast<Imf_2_5::DeepFrameBuffer const * >(rhs);
}


inline Imf_2_5::DeepFrameBuffer * to_cpp(
    Imf_2_5_DeepFrameBuffer * rhs)
{
    return reinterpret_cast<Imf_2_5::DeepFrameBuffer * >(rhs);
}


inline Imf_2_5_DeepFrameBuffer const * to_c(
    Imf_2_5::DeepFrameBuffer const & rhs)
{
    return reinterpret_cast<Imf_2_5_DeepFrameBuffer const * >(&(rhs));
}


inline Imf_2_5_DeepFrameBuffer const * to_c(
    Imf_2_5::DeepFrameBuffer const * rhs)
{
    return reinterpret_cast<Imf_2_5_DeepFrameBuffer const * >(rhs);
}


inline Imf_2_5_DeepFrameBuffer * to_c(
    Imf_2_5::DeepFrameBuffer & rhs)
{
    return reinterpret_cast<Imf_2_5_DeepFrameBuffer * >(&(rhs));
}


inline Imf_2_5_DeepFrameBuffer * to_c(
    Imf_2_5::DeepFrameBuffer * rhs)
{
    return reinterpret_cast<Imf_2_5_DeepFrameBuffer * >(rhs);
}






inline Imf_2_5::DeepFrameBuffer::Iterator const & to_cpp_ref(
    Imf_2_5_DeepFrameBuffer_Iterator const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::DeepFrameBuffer::Iterator const * >(rhs));
}


inline Imf_2_5::DeepFrameBuffer::Iterator & to_cpp_ref(
    Imf_2_5_DeepFrameBuffer_Iterator * rhs)
{
    return *(reinterpret_cast<Imf_2_5::DeepFrameBuffer::Iterator * >(rhs));
}


inline Imf_2_5::DeepFrameBuffer::Iterator const * to_cpp(
    Imf_2_5_DeepFrameBuffer_Iterator const * rhs)
{
    return reinterpret_cast<Imf_2_5::DeepFrameBuffer::Iterator const * >(rhs);
}


inline Imf_2_5::DeepFrameBuffer::Iterator * to_cpp(
    Imf_2_5_DeepFrameBuffer_Iterator * rhs)
{
    return reinterpret_cast<Imf_2_5::DeepFrameBuffer::Iterator * >(rhs);
}


inline Imf_2_5_DeepFrameBuffer_Iterator const * to_c(
    Imf_2_5::DeepFrameBuffer::Iterator const & rhs)
{
    return reinterpret_cast<Imf_2_5_DeepFrameBuffer_Iterator const * >(&(rhs));
}


inline Imf_2_5_DeepFrameBuffer_Iterator const * to_c(
    Imf_2_5::DeepFrameBuffer::Iterator const * rhs)
{
    return reinterpret_cast<Imf_2_5_DeepFrameBuffer_Iterator const * >(rhs);
}


inline Imf_2_5_DeepFrameBuffer_Iterator * to_c(
    Imf_2_5::DeepFrameBuffer::Iterator & rhs)
{
    return reinterpret_cast<Imf_2_5_DeepFrameBuffer_Iterator * >(&(rhs));
}


inline Imf_2_5_DeepFrameBuffer_Iterator * to_c(
    Imf_2_5::DeepFrameBuffer::Iterator * rhs)
{
    return reinterpret_cast<Imf_2_5_DeepFrameBuffer_Iterator * >(rhs);
}


inline Imf_2_5_DeepFrameBuffer_Iterator to_c_copy(
    Imf_2_5::DeepFrameBuffer::Iterator const & rhs)
{
    Imf_2_5_DeepFrameBuffer_Iterator result;
    Imf_2_5_DeepFrameBuffer_Iterator_Iterator_1(&(result), reinterpret_cast<Imf_2_5_DeepFrameBuffer_Iterator const * >(&(rhs)));
    return result;
}





inline Imf_2_5::DeepFrameBuffer::ConstIterator const & to_cpp_ref(
    Imf_2_5_DeepFrameBuffer_ConstIterator const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::DeepFrameBuffer::ConstIterator const * >(rhs));
}


inline Imf_2_5::DeepFrameBuffer::ConstIterator & to_cpp_ref(
    Imf_2_5_DeepFrameBuffer_ConstIterator * rhs)
{
    return *(reinterpret_cast<Imf_2_5::DeepFrameBuffer::ConstIterator * >(rhs));
}


inline Imf_2_5::DeepFrameBuffer::ConstIterator const * to_cpp(
    Imf_2_5_DeepFrameBuffer_ConstIterator const * rhs)
{
    return reinterpret_cast<Imf_2_5::DeepFrameBuffer::ConstIterator const * >(rhs);
}


inline Imf_2_5::DeepFrameBuffer::ConstIterator * to_cpp(
    Imf_2_5_DeepFrameBuffer_ConstIterator * rhs)
{
    return reinterpret_cast<Imf_2_5::DeepFrameBuffer::ConstIterator * >(rhs);
}


inline Imf_2_5_DeepFrameBuffer_ConstIterator const * to_c(
    Imf_2_5::DeepFrameBuffer::ConstIterator const & rhs)
{
    return reinterpret_cast<Imf_2_5_DeepFrameBuffer_ConstIterator const * >(&(rhs));
}


inline Imf_2_5_DeepFrameBuffer_ConstIterator const * to_c(
    Imf_2_5::DeepFrameBuffer::ConstIterator const * rhs)
{
    return reinterpret_cast<Imf_2_5_DeepFrameBuffer_ConstIterator const * >(rhs);
}


inline Imf_2_5_DeepFrameBuffer_ConstIterator * to_c(
    Imf_2_5::DeepFrameBuffer::ConstIterator & rhs)
{
    return reinterpret_cast<Imf_2_5_DeepFrameBuffer_ConstIterator * >(&(rhs));
}


inline Imf_2_5_DeepFrameBuffer_ConstIterator * to_c(
    Imf_2_5::DeepFrameBuffer::ConstIterator * rhs)
{
    return reinterpret_cast<Imf_2_5_DeepFrameBuffer_ConstIterator * >(rhs);
}


inline Imf_2_5_DeepFrameBuffer_ConstIterator to_c_copy(
    Imf_2_5::DeepFrameBuffer::ConstIterator const & rhs)
{
    Imf_2_5_DeepFrameBuffer_ConstIterator result;
    Imf_2_5_DeepFrameBuffer_ConstIterator_ConstIterator_1(&(result), reinterpret_cast<Imf_2_5_DeepFrameBuffer_ConstIterator const * >(&(rhs)));
    return result;
}
