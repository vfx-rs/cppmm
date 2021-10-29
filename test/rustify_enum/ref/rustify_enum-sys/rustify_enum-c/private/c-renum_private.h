#pragma once
#include <c-renum.h>


#include "rustify_enum-errors-private.h"

#include <cstring>
#include <renum.hpp>

inline rustify::Foo::Bar const & rustify_Foo_Bar_to_cpp_ref(
    rustify_Foo_Bar const * rhs)
{
        return *(reinterpret_cast<rustify::Foo::Bar const * >(rhs));
}

inline rustify::Foo::Bar & rustify_Foo_Bar_to_cpp_ref(
    rustify_Foo_Bar * rhs)
{
        return *(reinterpret_cast<rustify::Foo::Bar * >(rhs));
}

inline rustify::Foo::Bar const * rustify_Foo_Bar_to_cpp(
    rustify_Foo_Bar const * rhs)
{
        return reinterpret_cast<rustify::Foo::Bar const * >(rhs);
}

inline rustify::Foo::Bar * rustify_Foo_Bar_to_cpp(
    rustify_Foo_Bar * rhs)
{
        return reinterpret_cast<rustify::Foo::Bar * >(rhs);
}

inline void to_c(
    rustify_Foo_Bar const * * lhs
    , rustify::Foo::Bar const & rhs)
{
        *(lhs) = reinterpret_cast<rustify_Foo_Bar const * >(&(rhs));
}

inline void to_c(
    rustify_Foo_Bar const * * lhs
    , rustify::Foo::Bar const * rhs)
{
        *(lhs) = reinterpret_cast<rustify_Foo_Bar const * >(rhs);
}

inline void to_c(
    rustify_Foo_Bar * * lhs
    , rustify::Foo::Bar & rhs)
{
        *(lhs) = reinterpret_cast<rustify_Foo_Bar * >(&(rhs));
}

inline void to_c(
    rustify_Foo_Bar * * lhs
    , rustify::Foo::Bar * rhs)
{
        *(lhs) = reinterpret_cast<rustify_Foo_Bar * >(rhs);
}

inline void to_c_copy(
    rustify_Foo_Bar * lhs
    , rustify::Foo::Bar const & rhs)
{
        memcpy(lhs, &(rhs), sizeof(*(lhs)));
}

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

inline void to_c(
    rustify_Compression const * * lhs
    , rustify::Compression const & rhs)
{
        *(lhs) = reinterpret_cast<rustify_Compression const * >(&(rhs));
}

inline void to_c(
    rustify_Compression const * * lhs
    , rustify::Compression const * rhs)
{
        *(lhs) = reinterpret_cast<rustify_Compression const * >(rhs);
}

inline void to_c(
    rustify_Compression * * lhs
    , rustify::Compression & rhs)
{
        *(lhs) = reinterpret_cast<rustify_Compression * >(&(rhs));
}

inline void to_c(
    rustify_Compression * * lhs
    , rustify::Compression * rhs)
{
        *(lhs) = reinterpret_cast<rustify_Compression * >(rhs);
}

inline void to_c_copy(
    rustify_Compression * lhs
    , rustify::Compression const & rhs)
{
        memcpy(lhs, &(rhs), sizeof(*(lhs)));
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

inline void to_c(
    rustify_LineOrder const * * lhs
    , rustify::LineOrder const & rhs)
{
        *(lhs) = reinterpret_cast<rustify_LineOrder const * >(&(rhs));
}

inline void to_c(
    rustify_LineOrder const * * lhs
    , rustify::LineOrder const * rhs)
{
        *(lhs) = reinterpret_cast<rustify_LineOrder const * >(rhs);
}

inline void to_c(
    rustify_LineOrder * * lhs
    , rustify::LineOrder & rhs)
{
        *(lhs) = reinterpret_cast<rustify_LineOrder * >(&(rhs));
}

inline void to_c(
    rustify_LineOrder * * lhs
    , rustify::LineOrder * rhs)
{
        *(lhs) = reinterpret_cast<rustify_LineOrder * >(rhs);
}

inline void to_c_copy(
    rustify_LineOrder * lhs
    , rustify::LineOrder const & rhs)
{
        memcpy(lhs, &(rhs), sizeof(*(lhs)));
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

inline void to_c(
    rustify_RgbaChannels const * * lhs
    , rustify::RgbaChannels const & rhs)
{
        *(lhs) = reinterpret_cast<rustify_RgbaChannels const * >(&(rhs));
}

inline void to_c(
    rustify_RgbaChannels const * * lhs
    , rustify::RgbaChannels const * rhs)
{
        *(lhs) = reinterpret_cast<rustify_RgbaChannels const * >(rhs);
}

inline void to_c(
    rustify_RgbaChannels * * lhs
    , rustify::RgbaChannels & rhs)
{
        *(lhs) = reinterpret_cast<rustify_RgbaChannels * >(&(rhs));
}

inline void to_c(
    rustify_RgbaChannels * * lhs
    , rustify::RgbaChannels * rhs)
{
        *(lhs) = reinterpret_cast<rustify_RgbaChannels * >(rhs);
}

inline void to_c_copy(
    rustify_RgbaChannels * lhs
    , rustify::RgbaChannels const & rhs)
{
        memcpy(lhs, &(rhs), sizeof(*(lhs)));
}

inline rustify::Foo const & to_cpp_ref(
    rustify_Foo_t const * rhs)
{
        return *(reinterpret_cast<rustify::Foo const * >(rhs));
}

inline rustify::Foo & to_cpp_ref(
    rustify_Foo_t * rhs)
{
        return *(reinterpret_cast<rustify::Foo * >(rhs));
}

inline rustify::Foo const * to_cpp(
    rustify_Foo_t const * rhs)
{
        return reinterpret_cast<rustify::Foo const * >(rhs);
}

inline rustify::Foo * to_cpp(
    rustify_Foo_t * rhs)
{
        return reinterpret_cast<rustify::Foo * >(rhs);
}

inline void to_c(
    rustify_Foo_t const * * lhs
    , rustify::Foo const & rhs)
{
        *(lhs) = reinterpret_cast<rustify_Foo_t const * >(&(rhs));
}

inline void to_c(
    rustify_Foo_t const * * lhs
    , rustify::Foo const * rhs)
{
        *(lhs) = reinterpret_cast<rustify_Foo_t const * >(rhs);
}

inline void to_c(
    rustify_Foo_t * * lhs
    , rustify::Foo & rhs)
{
        *(lhs) = reinterpret_cast<rustify_Foo_t * >(&(rhs));
}

inline void to_c(
    rustify_Foo_t * * lhs
    , rustify::Foo * rhs)
{
        *(lhs) = reinterpret_cast<rustify_Foo_t * >(rhs);
}

inline void to_c_copy(
    rustify_Foo_t * lhs
    , rustify::Foo const & rhs)
{
        memcpy(lhs, &(rhs), sizeof(*(lhs)));
}

