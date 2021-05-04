#pragma once
#include <c-ex.h>


#include <cstring>
#include <ex.hpp>




inline ex::Struct const & to_cpp_ref(
    ex_Struct_t const * rhs)
{
        return *(reinterpret_cast<ex::Struct const * >(rhs));
}

inline ex::Struct & to_cpp_ref(
    ex_Struct_t * rhs)
{
        return *(reinterpret_cast<ex::Struct * >(rhs));
}

inline ex::Struct const * to_cpp(
    ex_Struct_t const * rhs)
{
        return reinterpret_cast<ex::Struct const * >(rhs);
}

inline ex::Struct * to_cpp(
    ex_Struct_t * rhs)
{
        return reinterpret_cast<ex::Struct * >(rhs);
}

inline void to_c(
    ex_Struct_t const * * lhs
    , ex::Struct const & rhs)
{
        *(lhs) = reinterpret_cast<ex_Struct_t const * >(&(rhs));
}

inline void to_c(
    ex_Struct_t const * * lhs
    , ex::Struct const * rhs)
{
        *(lhs) = reinterpret_cast<ex_Struct_t const * >(rhs);
}

inline void to_c(
    ex_Struct_t * * lhs
    , ex::Struct & rhs)
{
        *(lhs) = reinterpret_cast<ex_Struct_t * >(&(rhs));
}

inline void to_c(
    ex_Struct_t * * lhs
    , ex::Struct * rhs)
{
        *(lhs) = reinterpret_cast<ex_Struct_t * >(rhs);
}

inline void to_c_copy(
    ex_Struct_t * lhs
    , ex::Struct const & rhs)
{
        memcpy(lhs, &(rhs), sizeof(*(lhs)));
}


