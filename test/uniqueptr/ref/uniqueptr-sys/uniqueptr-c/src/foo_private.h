#pragma once
#include <foo.h>


#include "uniqueptr-errors-private.h"

#include <cstring>
#include <foo.hpp>

inline foo::Foo const & to_cpp_ref(
    foo_Foo_t const * rhs)
{
        return *(reinterpret_cast<foo::Foo const * >(rhs));
}

inline foo::Foo & to_cpp_ref(
    foo_Foo_t * rhs)
{
        return *(reinterpret_cast<foo::Foo * >(rhs));
}

inline foo::Foo const * to_cpp(
    foo_Foo_t const * rhs)
{
        return reinterpret_cast<foo::Foo const * >(rhs);
}

inline foo::Foo * to_cpp(
    foo_Foo_t * rhs)
{
        return reinterpret_cast<foo::Foo * >(rhs);
}

inline void to_c(
    foo_Foo_t const * * lhs
    , foo::Foo const & rhs)
{
        *(lhs) = reinterpret_cast<foo_Foo_t const * >(&(rhs));
}

inline void to_c(
    foo_Foo_t const * * lhs
    , foo::Foo const * rhs)
{
        *(lhs) = reinterpret_cast<foo_Foo_t const * >(rhs);
}

inline void to_c(
    foo_Foo_t * * lhs
    , foo::Foo & rhs)
{
        *(lhs) = reinterpret_cast<foo_Foo_t * >(&(rhs));
}

inline void to_c(
    foo_Foo_t * * lhs
    , foo::Foo * rhs)
{
        *(lhs) = reinterpret_cast<foo_Foo_t * >(rhs);
}

