#pragma once
#include <uptr.h>


#include "uniqueptr-errors-private.h"

#include <cstring>
#include <foo.hpp>
#include <memory>

inline std::unique_ptr<foo::Foo> const & to_cpp_ref(
    std_FooPtr_t const * rhs)
{
        return *(reinterpret_cast<std::unique_ptr<foo::Foo> const * >(rhs));
}

inline std::unique_ptr<foo::Foo> & to_cpp_ref(
    std_FooPtr_t * rhs)
{
        return *(reinterpret_cast<std::unique_ptr<foo::Foo> * >(rhs));
}

inline std::unique_ptr<foo::Foo> const * to_cpp(
    std_FooPtr_t const * rhs)
{
        return reinterpret_cast<std::unique_ptr<foo::Foo> const * >(rhs);
}

inline std::unique_ptr<foo::Foo> * to_cpp(
    std_FooPtr_t * rhs)
{
        return reinterpret_cast<std::unique_ptr<foo::Foo> * >(rhs);
}

inline void to_c(
    std_FooPtr_t const * * lhs
    , std::unique_ptr<foo::Foo> const & rhs)
{
        *(lhs) = reinterpret_cast<std_FooPtr_t const * >(&(rhs));
}

inline void to_c(
    std_FooPtr_t const * * lhs
    , std::unique_ptr<foo::Foo> const * rhs)
{
        *(lhs) = reinterpret_cast<std_FooPtr_t const * >(rhs);
}

inline void to_c(
    std_FooPtr_t * * lhs
    , std::unique_ptr<foo::Foo> & rhs)
{
        *(lhs) = reinterpret_cast<std_FooPtr_t * >(&(rhs));
}

inline void to_c(
    std_FooPtr_t * * lhs
    , std::unique_ptr<foo::Foo> * rhs)
{
        *(lhs) = reinterpret_cast<std_FooPtr_t * >(rhs);
}

inline void to_c_move(
    std_FooPtr_t * lhs
    , std::unique_ptr<foo::Foo> rhs)
{
        new (lhs) std::unique_ptr<foo::Foo>(std::move(rhs));
}

