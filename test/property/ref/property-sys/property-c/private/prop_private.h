#pragma once
#include <prop.h>


#include "property-errors-private.h"

#include <cstring>
#include <prop.hpp>

inline prop::Bar const & to_cpp_ref(
    prop_Bar_t const * rhs)
{
        return *(reinterpret_cast<prop::Bar const * >(rhs));
}

inline prop::Bar & to_cpp_ref(
    prop_Bar_t * rhs)
{
        return *(reinterpret_cast<prop::Bar * >(rhs));
}

inline prop::Bar const * to_cpp(
    prop_Bar_t const * rhs)
{
        return reinterpret_cast<prop::Bar const * >(rhs);
}

inline prop::Bar * to_cpp(
    prop_Bar_t * rhs)
{
        return reinterpret_cast<prop::Bar * >(rhs);
}

inline void to_c(
    prop_Bar_t const * * lhs
    , prop::Bar const & rhs)
{
        *(lhs) = reinterpret_cast<prop_Bar_t const * >(&(rhs));
}

inline void to_c(
    prop_Bar_t const * * lhs
    , prop::Bar const * rhs)
{
        *(lhs) = reinterpret_cast<prop_Bar_t const * >(rhs);
}

inline void to_c(
    prop_Bar_t * * lhs
    , prop::Bar & rhs)
{
        *(lhs) = reinterpret_cast<prop_Bar_t * >(&(rhs));
}

inline void to_c(
    prop_Bar_t * * lhs
    , prop::Bar * rhs)
{
        *(lhs) = reinterpret_cast<prop_Bar_t * >(rhs);
}

inline void to_c_copy(
    prop_Bar_t * lhs
    , prop::Bar const & rhs)
{
        memcpy(lhs, &(rhs), sizeof(*(lhs)));
}

inline prop::Foo const & to_cpp_ref(
    prop_Foo_t const * rhs)
{
        return *(reinterpret_cast<prop::Foo const * >(rhs));
}

inline prop::Foo & to_cpp_ref(
    prop_Foo_t * rhs)
{
        return *(reinterpret_cast<prop::Foo * >(rhs));
}

inline prop::Foo const * to_cpp(
    prop_Foo_t const * rhs)
{
        return reinterpret_cast<prop::Foo const * >(rhs);
}

inline prop::Foo * to_cpp(
    prop_Foo_t * rhs)
{
        return reinterpret_cast<prop::Foo * >(rhs);
}

inline void to_c(
    prop_Foo_t const * * lhs
    , prop::Foo const & rhs)
{
        *(lhs) = reinterpret_cast<prop_Foo_t const * >(&(rhs));
}

inline void to_c(
    prop_Foo_t const * * lhs
    , prop::Foo const * rhs)
{
        *(lhs) = reinterpret_cast<prop_Foo_t const * >(rhs);
}

inline void to_c(
    prop_Foo_t * * lhs
    , prop::Foo & rhs)
{
        *(lhs) = reinterpret_cast<prop_Foo_t * >(&(rhs));
}

inline void to_c(
    prop_Foo_t * * lhs
    , prop::Foo * rhs)
{
        *(lhs) = reinterpret_cast<prop_Foo_t * >(rhs);
}

inline void to_c_copy(
    prop_Foo_t * lhs
    , prop::Foo const & rhs)
{
        memcpy(lhs, &(rhs), sizeof(*(lhs)));
}

