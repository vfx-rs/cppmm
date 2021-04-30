#pragma once
#include <c-dtor.h>


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

inline dtor_Struct_t const * to_c(
    dtor::Struct const & rhs)
{
    return reinterpret_cast<dtor_Struct_t const * >(&(rhs));
}

inline dtor_Struct_t const * to_c(
    dtor::Struct const * rhs)
{
    return reinterpret_cast<dtor_Struct_t const * >(rhs);
}

inline dtor_Struct_t * to_c(
    dtor::Struct & rhs)
{
    return reinterpret_cast<dtor_Struct_t * >(&(rhs));
}

inline dtor_Struct_t * to_c(
    dtor::Struct * rhs)
{
    return reinterpret_cast<dtor_Struct_t * >(rhs);
}
