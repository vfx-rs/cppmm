#pragma once
#include <c-dtor.h>


#include <cstring>
#include <dtor.hpp>




inline dtor::Struct const & to_cpp_ref(
    dtor_Struct_t const * rhs)
{
        return *(reinterpret_cast<dtor::Struct const * >(rhs));
}

inline dtor::Struct & to_cpp_ref(
    dtor_Struct_t * rhs)
{
        return *(reinterpret_cast<dtor::Struct * >(rhs));
}

inline dtor::Struct const * to_cpp(
    dtor_Struct_t const * rhs)
{
        return reinterpret_cast<dtor::Struct const * >(rhs);
}

inline dtor::Struct * to_cpp(
    dtor_Struct_t * rhs)
{
        return reinterpret_cast<dtor::Struct * >(rhs);
}

inline void to_c(
    dtor_Struct_t const * * lhs
    , dtor::Struct const & rhs)
{
        *(lhs) = reinterpret_cast<dtor_Struct_t const * >(&(rhs));
}

inline void to_c(
    dtor_Struct_t const * * lhs
    , dtor::Struct const * rhs)
{
        *(lhs) = reinterpret_cast<dtor_Struct_t const * >(rhs);
}

inline void to_c(
    dtor_Struct_t * * lhs
    , dtor::Struct & rhs)
{
        *(lhs) = reinterpret_cast<dtor_Struct_t * >(&(rhs));
}

inline void to_c(
    dtor_Struct_t * * lhs
    , dtor::Struct * rhs)
{
        *(lhs) = reinterpret_cast<dtor_Struct_t * >(rhs);
}
