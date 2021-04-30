#pragma once
#include <c-dn.h>


#include <cstring>
#include <dn.hpp>


inline DN::v2_2::Class::Enum const & DN_Class_Enum_to_cpp_ref(
    DN_Class_Enum const * rhs)
{
    return *(reinterpret_cast<DN::v2_2::Class::Enum const * >(rhs));
}

inline DN::v2_2::Class::Enum & DN_Class_Enum_to_cpp_ref(
    DN_Class_Enum * rhs)
{
    return *(reinterpret_cast<DN::v2_2::Class::Enum * >(rhs));
}

inline DN::v2_2::Class::Enum const * DN_Class_Enum_to_cpp(
    DN_Class_Enum const * rhs)
{
    return reinterpret_cast<DN::v2_2::Class::Enum const * >(rhs);
}

inline DN::v2_2::Class::Enum * DN_Class_Enum_to_cpp(
    DN_Class_Enum * rhs)
{
    return reinterpret_cast<DN::v2_2::Class::Enum * >(rhs);
}

inline DN_Class_Enum const * to_c(
    DN::v2_2::Class::Enum const & rhs)
{
    return reinterpret_cast<DN_Class_Enum const * >(&(rhs));
}

inline DN_Class_Enum const * to_c(
    DN::v2_2::Class::Enum const * rhs)
{
    return reinterpret_cast<DN_Class_Enum const * >(rhs);
}

inline DN_Class_Enum * to_c(
    DN::v2_2::Class::Enum & rhs)
{
    return reinterpret_cast<DN_Class_Enum * >(&(rhs));
}

inline DN_Class_Enum * to_c(
    DN::v2_2::Class::Enum * rhs)
{
    return reinterpret_cast<DN_Class_Enum * >(rhs);
}

inline DN_Class_Enum to_c_copy(
    DN::v2_2::Class::Enum const & rhs)
{
    DN_Class_Enum result;
    memcpy(&(result), &(rhs), sizeof(result));
    return result;
}

inline DN::v2_2::Class const & to_cpp_ref(
    DN_Class_t const * rhs)
{
    return *(reinterpret_cast<DN::v2_2::Class const * >(rhs));
}

inline DN::v2_2::Class & to_cpp_ref(
    DN_Class_t * rhs)
{
    return *(reinterpret_cast<DN::v2_2::Class * >(rhs));
}

inline DN::v2_2::Class const * to_cpp(
    DN_Class_t const * rhs)
{
    return reinterpret_cast<DN::v2_2::Class const * >(rhs);
}

inline DN::v2_2::Class * to_cpp(
    DN_Class_t * rhs)
{
    return reinterpret_cast<DN::v2_2::Class * >(rhs);
}

inline DN_Class_t const * to_c(
    DN::v2_2::Class const & rhs)
{
    return reinterpret_cast<DN_Class_t const * >(&(rhs));
}

inline DN_Class_t const * to_c(
    DN::v2_2::Class const * rhs)
{
    return reinterpret_cast<DN_Class_t const * >(rhs);
}

inline DN_Class_t * to_c(
    DN::v2_2::Class & rhs)
{
    return reinterpret_cast<DN_Class_t * >(&(rhs));
}

inline DN_Class_t * to_c(
    DN::v2_2::Class * rhs)
{
    return reinterpret_cast<DN_Class_t * >(rhs);
}


inline DN::v2_2::Class::Struct const & to_cpp_ref(
    DN_Class_Struct_t const * rhs)
{
    return *(reinterpret_cast<DN::v2_2::Class::Struct const * >(rhs));
}

inline DN::v2_2::Class::Struct & to_cpp_ref(
    DN_Class_Struct_t * rhs)
{
    return *(reinterpret_cast<DN::v2_2::Class::Struct * >(rhs));
}

inline DN::v2_2::Class::Struct const * to_cpp(
    DN_Class_Struct_t const * rhs)
{
    return reinterpret_cast<DN::v2_2::Class::Struct const * >(rhs);
}

inline DN::v2_2::Class::Struct * to_cpp(
    DN_Class_Struct_t * rhs)
{
    return reinterpret_cast<DN::v2_2::Class::Struct * >(rhs);
}

inline DN_Class_Struct_t const * to_c(
    DN::v2_2::Class::Struct const & rhs)
{
    return reinterpret_cast<DN_Class_Struct_t const * >(&(rhs));
}

inline DN_Class_Struct_t const * to_c(
    DN::v2_2::Class::Struct const * rhs)
{
    return reinterpret_cast<DN_Class_Struct_t const * >(rhs);
}

inline DN_Class_Struct_t * to_c(
    DN::v2_2::Class::Struct & rhs)
{
    return reinterpret_cast<DN_Class_Struct_t * >(&(rhs));
}

inline DN_Class_Struct_t * to_c(
    DN::v2_2::Class::Struct * rhs)
{
    return reinterpret_cast<DN_Class_Struct_t * >(rhs);
}

inline DN_Class_Struct_t to_c_copy(
    DN::v2_2::Class::Struct const & rhs)
{
    DN_Class_Struct_t result;
    memcpy(&(result), &(rhs), sizeof(result));
    return result;
}

