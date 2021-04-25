#pragma once
#include <c-renum.h>


#include <cstring>
#include <renum.hpp>


inline rustify::Compression const & rustify_Compression_to_cpp_ref(
    rustify_Compression const * rhs)
{
    return *(reinterpret_cast<rustify::Compression const * >(rhs));
}

inline rustify::Compression & rustify_Compression_to_cpp_ref(
    rustify_Compression * rhs)
{
    return *(reinterpret_cast<rustify::Compression * >(rhs));
}

inline rustify::Compression const * rustify_Compression_to_cpp(
    rustify_Compression const * rhs)
{
    return reinterpret_cast<rustify::Compression const * >(rhs);
}

inline rustify::Compression * rustify_Compression_to_cpp(
    rustify_Compression * rhs)
{
    return reinterpret_cast<rustify::Compression * >(rhs);
}

inline rustify_Compression const * to_c(
    rustify::Compression const & rhs)
{
    return reinterpret_cast<rustify_Compression const * >(&(rhs));
}

inline rustify_Compression const * to_c(
    rustify::Compression const * rhs)
{
    return reinterpret_cast<rustify_Compression const * >(rhs);
}

inline rustify_Compression * to_c(
    rustify::Compression & rhs)
{
    return reinterpret_cast<rustify_Compression * >(&(rhs));
}

inline rustify_Compression * to_c(
    rustify::Compression * rhs)
{
    return reinterpret_cast<rustify_Compression * >(rhs);
}

inline rustify_Compression to_c_copy(
    rustify::Compression const & rhs)
{
    rustify_Compression result;
    memcpy(&(result), &(rhs), sizeof(result));
    return result;
}

inline rustify::LineOrder const & rustify_LineOrder_to_cpp_ref(
    rustify_LineOrder const * rhs)
{
    return *(reinterpret_cast<rustify::LineOrder const * >(rhs));
}

inline rustify::LineOrder & rustify_LineOrder_to_cpp_ref(
    rustify_LineOrder * rhs)
{
    return *(reinterpret_cast<rustify::LineOrder * >(rhs));
}

inline rustify::LineOrder const * rustify_LineOrder_to_cpp(
    rustify_LineOrder const * rhs)
{
    return reinterpret_cast<rustify::LineOrder const * >(rhs);
}

inline rustify::LineOrder * rustify_LineOrder_to_cpp(
    rustify_LineOrder * rhs)
{
    return reinterpret_cast<rustify::LineOrder * >(rhs);
}

inline rustify_LineOrder const * to_c(
    rustify::LineOrder const & rhs)
{
    return reinterpret_cast<rustify_LineOrder const * >(&(rhs));
}

inline rustify_LineOrder const * to_c(
    rustify::LineOrder const * rhs)
{
    return reinterpret_cast<rustify_LineOrder const * >(rhs);
}

inline rustify_LineOrder * to_c(
    rustify::LineOrder & rhs)
{
    return reinterpret_cast<rustify_LineOrder * >(&(rhs));
}

inline rustify_LineOrder * to_c(
    rustify::LineOrder * rhs)
{
    return reinterpret_cast<rustify_LineOrder * >(rhs);
}

inline rustify_LineOrder to_c_copy(
    rustify::LineOrder const & rhs)
{
    rustify_LineOrder result;
    memcpy(&(result), &(rhs), sizeof(result));
    return result;
}

inline rustify::RgbaChannels const & rustify_RgbaChannels_to_cpp_ref(
    rustify_RgbaChannels const * rhs)
{
    return *(reinterpret_cast<rustify::RgbaChannels const * >(rhs));
}

inline rustify::RgbaChannels & rustify_RgbaChannels_to_cpp_ref(
    rustify_RgbaChannels * rhs)
{
    return *(reinterpret_cast<rustify::RgbaChannels * >(rhs));
}

inline rustify::RgbaChannels const * rustify_RgbaChannels_to_cpp(
    rustify_RgbaChannels const * rhs)
{
    return reinterpret_cast<rustify::RgbaChannels const * >(rhs);
}

inline rustify::RgbaChannels * rustify_RgbaChannels_to_cpp(
    rustify_RgbaChannels * rhs)
{
    return reinterpret_cast<rustify::RgbaChannels * >(rhs);
}

inline rustify_RgbaChannels const * to_c(
    rustify::RgbaChannels const & rhs)
{
    return reinterpret_cast<rustify_RgbaChannels const * >(&(rhs));
}

inline rustify_RgbaChannels const * to_c(
    rustify::RgbaChannels const * rhs)
{
    return reinterpret_cast<rustify_RgbaChannels const * >(rhs);
}

inline rustify_RgbaChannels * to_c(
    rustify::RgbaChannels & rhs)
{
    return reinterpret_cast<rustify_RgbaChannels * >(&(rhs));
}

inline rustify_RgbaChannels * to_c(
    rustify::RgbaChannels * rhs)
{
    return reinterpret_cast<rustify_RgbaChannels * >(rhs);
}

inline rustify_RgbaChannels to_c_copy(
    rustify::RgbaChannels const & rhs)
{
    rustify_RgbaChannels result;
    memcpy(&(result), &(rhs), sizeof(result));
    return result;
}
