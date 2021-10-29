#pragma once
#include <b/neste.h>


#include "nested-errors-private.h"

#include <b/neste.hpp>
#include <cstring>

inline nest::NestBE const & to_cpp_ref(
    nest_NestBE_t const * rhs)
{
        return *(reinterpret_cast<nest::NestBE const * >(rhs));
}

inline nest::NestBE & to_cpp_ref(
    nest_NestBE_t * rhs)
{
        return *(reinterpret_cast<nest::NestBE * >(rhs));
}

inline nest::NestBE const * to_cpp(
    nest_NestBE_t const * rhs)
{
        return reinterpret_cast<nest::NestBE const * >(rhs);
}

inline nest::NestBE * to_cpp(
    nest_NestBE_t * rhs)
{
        return reinterpret_cast<nest::NestBE * >(rhs);
}

inline void to_c(
    nest_NestBE_t const * * lhs
    , nest::NestBE const & rhs)
{
        *(lhs) = reinterpret_cast<nest_NestBE_t const * >(&(rhs));
}

inline void to_c(
    nest_NestBE_t const * * lhs
    , nest::NestBE const * rhs)
{
        *(lhs) = reinterpret_cast<nest_NestBE_t const * >(rhs);
}

inline void to_c(
    nest_NestBE_t * * lhs
    , nest::NestBE & rhs)
{
        *(lhs) = reinterpret_cast<nest_NestBE_t * >(&(rhs));
}

inline void to_c(
    nest_NestBE_t * * lhs
    , nest::NestBE * rhs)
{
        *(lhs) = reinterpret_cast<nest_NestBE_t * >(rhs);
}

inline void to_c_copy(
    nest_NestBE_t * lhs
    , nest::NestBE const & rhs)
{
        memcpy(lhs, &(rhs), sizeof(*(lhs)));
}

