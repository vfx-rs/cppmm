#pragma once
#include <c/d/neste.h>


#include "nested-errors-private.h"

#include <c/d/neste.hpp>
#include <cstring>

inline nest::NestCDE const & to_cpp_ref(
    nest_NestCDE_t const * rhs)
{
        return *(reinterpret_cast<nest::NestCDE const * >(rhs));
}

inline nest::NestCDE & to_cpp_ref(
    nest_NestCDE_t * rhs)
{
        return *(reinterpret_cast<nest::NestCDE * >(rhs));
}

inline nest::NestCDE const * to_cpp(
    nest_NestCDE_t const * rhs)
{
        return reinterpret_cast<nest::NestCDE const * >(rhs);
}

inline nest::NestCDE * to_cpp(
    nest_NestCDE_t * rhs)
{
        return reinterpret_cast<nest::NestCDE * >(rhs);
}

inline void to_c(
    nest_NestCDE_t const * * lhs
    , nest::NestCDE const & rhs)
{
        *(lhs) = reinterpret_cast<nest_NestCDE_t const * >(&(rhs));
}

inline void to_c(
    nest_NestCDE_t const * * lhs
    , nest::NestCDE const * rhs)
{
        *(lhs) = reinterpret_cast<nest_NestCDE_t const * >(rhs);
}

inline void to_c(
    nest_NestCDE_t * * lhs
    , nest::NestCDE & rhs)
{
        *(lhs) = reinterpret_cast<nest_NestCDE_t * >(&(rhs));
}

inline void to_c(
    nest_NestCDE_t * * lhs
    , nest::NestCDE * rhs)
{
        *(lhs) = reinterpret_cast<nest_NestCDE_t * >(rhs);
}

inline void to_c_copy(
    nest_NestCDE_t * lhs
    , nest::NestCDE const & rhs)
{
        memcpy(lhs, &(rhs), sizeof(*(lhs)));
}

