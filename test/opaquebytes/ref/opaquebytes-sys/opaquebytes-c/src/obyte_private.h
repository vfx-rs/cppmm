#pragma once
#include <obyte.h>


#include "opaquebytes-errors-private.h"

#include <cstring>
#include <obyte.hpp>

inline obyte::Foo const & to_cpp_ref(
    obyte_Foo_t const * rhs)
{
        return *(reinterpret_cast<obyte::Foo const * >(rhs));
}

inline obyte::Foo & to_cpp_ref(
    obyte_Foo_t * rhs)
{
        return *(reinterpret_cast<obyte::Foo * >(rhs));
}

inline obyte::Foo const * to_cpp(
    obyte_Foo_t const * rhs)
{
        return reinterpret_cast<obyte::Foo const * >(rhs);
}

inline obyte::Foo * to_cpp(
    obyte_Foo_t * rhs)
{
        return reinterpret_cast<obyte::Foo * >(rhs);
}

inline void to_c(
    obyte_Foo_t const * * lhs
    , obyte::Foo const & rhs)
{
        *(lhs) = reinterpret_cast<obyte_Foo_t const * >(&(rhs));
}

inline void to_c(
    obyte_Foo_t const * * lhs
    , obyte::Foo const * rhs)
{
        *(lhs) = reinterpret_cast<obyte_Foo_t const * >(rhs);
}

inline void to_c(
    obyte_Foo_t * * lhs
    , obyte::Foo & rhs)
{
        *(lhs) = reinterpret_cast<obyte_Foo_t * >(&(rhs));
}

inline void to_c(
    obyte_Foo_t * * lhs
    , obyte::Foo * rhs)
{
        *(lhs) = reinterpret_cast<obyte_Foo_t * >(rhs);
}

inline void to_c_move(
    obyte_Foo_t * lhs
    , obyte::Foo rhs)
{
        new (lhs) obyte::Foo(std::move(rhs));
}

