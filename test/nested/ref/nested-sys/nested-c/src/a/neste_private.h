#pragma once
#include <a/neste.h>


#include "nested-errors-private.h"

#include <a/neste.hpp>
#include <cstring>

inline nest::NestAE const & to_cpp_ref(
    nest_NestAE_t const * rhs)
{
        return *(reinterpret_cast<nest::NestAE const * >(rhs));
}

inline nest::NestAE & to_cpp_ref(
    nest_NestAE_t * rhs)
{
        return *(reinterpret_cast<nest::NestAE * >(rhs));
}

inline nest::NestAE const * to_cpp(
    nest_NestAE_t const * rhs)
{
        return reinterpret_cast<nest::NestAE const * >(rhs);
}

inline nest::NestAE * to_cpp(
    nest_NestAE_t * rhs)
{
        return reinterpret_cast<nest::NestAE * >(rhs);
}

inline void to_c(
    nest_NestAE_t const * * lhs
    , nest::NestAE const & rhs)
{
        *(lhs) = reinterpret_cast<nest_NestAE_t const * >(&(rhs));
}

inline void to_c(
    nest_NestAE_t const * * lhs
    , nest::NestAE const * rhs)
{
        *(lhs) = reinterpret_cast<nest_NestAE_t const * >(rhs);
}

inline void to_c(
    nest_NestAE_t * * lhs
    , nest::NestAE & rhs)
{
        *(lhs) = reinterpret_cast<nest_NestAE_t * >(&(rhs));
}

inline void to_c(
    nest_NestAE_t * * lhs
    , nest::NestAE * rhs)
{
        *(lhs) = reinterpret_cast<nest_NestAE_t * >(rhs);
}

inline void to_c_copy(
    nest_NestAE_t * lhs
    , nest::NestAE const & rhs)
{
        memcpy(lhs, &(rhs), sizeof(*(lhs)));
}

