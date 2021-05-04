#pragma once
#include <c-comments.h>


#include <comments.hpp>
#include <cstring>


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

inline void to_c(
    comments_Class_t const * * lhs
    , comments::Class const & rhs)
{
        *(lhs) = reinterpret_cast<comments_Class_t const * >(&(rhs));
}

inline void to_c(
    comments_Class_t const * * lhs
    , comments::Class const * rhs)
{
        *(lhs) = reinterpret_cast<comments_Class_t const * >(rhs);
}

inline void to_c(
    comments_Class_t * * lhs
    , comments::Class & rhs)
{
        *(lhs) = reinterpret_cast<comments_Class_t * >(&(rhs));
}

inline void to_c(
    comments_Class_t * * lhs
    , comments::Class * rhs)
{
        *(lhs) = reinterpret_cast<comments_Class_t * >(rhs);
}

inline void to_c_copy(
    comments_Class_t * lhs
    , comments::Class const & rhs)
{
        memcpy(lhs, &(rhs), sizeof(*(lhs)));
}

/** This is a free function that also does nothing interesting */
