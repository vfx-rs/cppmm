#pragma once
#include <mimpl.h>


#include "mimpl-errors-private.h"

#include <cstring>
#include <mimpl.hpp>

inline mimpl::Number const & to_cpp_ref(
    mimpl_Number_t const * rhs)
{
        return *(reinterpret_cast<mimpl::Number const * >(rhs));
}

inline mimpl::Number & to_cpp_ref(
    mimpl_Number_t * rhs)
{
        return *(reinterpret_cast<mimpl::Number * >(rhs));
}

inline mimpl::Number const * to_cpp(
    mimpl_Number_t const * rhs)
{
        return reinterpret_cast<mimpl::Number const * >(rhs);
}

inline mimpl::Number * to_cpp(
    mimpl_Number_t * rhs)
{
        return reinterpret_cast<mimpl::Number * >(rhs);
}

inline void to_c(
    mimpl_Number_t const * * lhs
    , mimpl::Number const & rhs)
{
        *(lhs) = reinterpret_cast<mimpl_Number_t const * >(&(rhs));
}

inline void to_c(
    mimpl_Number_t const * * lhs
    , mimpl::Number const * rhs)
{
        *(lhs) = reinterpret_cast<mimpl_Number_t const * >(rhs);
}

inline void to_c(
    mimpl_Number_t * * lhs
    , mimpl::Number & rhs)
{
        *(lhs) = reinterpret_cast<mimpl_Number_t * >(&(rhs));
}

inline void to_c(
    mimpl_Number_t * * lhs
    , mimpl::Number * rhs)
{
        *(lhs) = reinterpret_cast<mimpl_Number_t * >(rhs);
}

inline void to_c_copy(
    mimpl_Number_t * lhs
    , mimpl::Number const & rhs)
{
        memcpy(lhs, &(rhs), sizeof(*(lhs)));
}

