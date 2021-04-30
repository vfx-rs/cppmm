#pragma once
#include <c-comments.h>


#include <comments.hpp>


/** This method doesn't do anything interesting at all */

inline comments::Class const & to_cpp_ref(
    comments_Class_t const * rhs)
{
    return *(reinterpret_cast<comments::Class const * >(rhs));
}

inline comments::Class & to_cpp_ref(
    comments_Class_t * rhs)
{
    return *(reinterpret_cast<comments::Class * >(rhs));
}

inline comments::Class const * to_cpp(
    comments_Class_t const * rhs)
{
    return reinterpret_cast<comments::Class const * >(rhs);
}

inline comments::Class * to_cpp(
    comments_Class_t * rhs)
{
    return reinterpret_cast<comments::Class * >(rhs);
}

inline comments_Class_t const * to_c(
    comments::Class const & rhs)
{
    return reinterpret_cast<comments_Class_t const * >(&(rhs));
}

inline comments_Class_t const * to_c(
    comments::Class const * rhs)
{
    return reinterpret_cast<comments_Class_t const * >(rhs);
}

inline comments_Class_t * to_c(
    comments::Class & rhs)
{
    return reinterpret_cast<comments_Class_t * >(&(rhs));
}

inline comments_Class_t * to_c(
    comments::Class * rhs)
{
    return reinterpret_cast<comments_Class_t * >(rhs);
}

/** This is a free function that also does nothing interesting */
