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

inline void to_c(
    DN_Class_Enum const * * lhs
    , DN::v2_2::Class::Enum const & rhs)
{
        *(lhs) = reinterpret_cast<DN_Class_Enum const * >(&(rhs));
}

inline void to_c(
    DN_Class_Enum const * * lhs
    , DN::v2_2::Class::Enum const * rhs)
{
        *(lhs) = reinterpret_cast<DN_Class_Enum const * >(rhs);
}

inline void to_c(
    DN_Class_Enum * * lhs
    , DN::v2_2::Class::Enum & rhs)
{
        *(lhs) = reinterpret_cast<DN_Class_Enum * >(&(rhs));
}

inline void to_c(
    DN_Class_Enum * * lhs
    , DN::v2_2::Class::Enum * rhs)
{
        *(lhs) = reinterpret_cast<DN_Class_Enum * >(rhs);
}

inline void to_c_copy(
    DN_Class_Enum * lhs
    , DN::v2_2::Class::Enum const & rhs)
{
        memcpy(lhs, &(rhs), sizeof(*(lhs)));
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

inline void to_c(
    DN_Class_t const * * lhs
    , DN::v2_2::Class const & rhs)
{
        *(lhs) = reinterpret_cast<DN_Class_t const * >(&(rhs));
}

inline void to_c(
    DN_Class_t const * * lhs
    , DN::v2_2::Class const * rhs)
{
        *(lhs) = reinterpret_cast<DN_Class_t const * >(rhs);
}

inline void to_c(
    DN_Class_t * * lhs
    , DN::v2_2::Class & rhs)
{
        *(lhs) = reinterpret_cast<DN_Class_t * >(&(rhs));
}

inline void to_c(
    DN_Class_t * * lhs
    , DN::v2_2::Class * rhs)
{
        *(lhs) = reinterpret_cast<DN_Class_t * >(rhs);
}

inline void to_c_copy(
    DN_Class_t * lhs
    , DN::v2_2::Class const & rhs)
{
        memcpy(lhs, &(rhs), sizeof(*(lhs)));
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

inline void to_c(
    DN_Class_Struct_t const * * lhs
    , DN::v2_2::Class::Struct const & rhs)
{
        *(lhs) = reinterpret_cast<DN_Class_Struct_t const * >(&(rhs));
}

inline void to_c(
    DN_Class_Struct_t const * * lhs
    , DN::v2_2::Class::Struct const * rhs)
{
        *(lhs) = reinterpret_cast<DN_Class_Struct_t const * >(rhs);
}

inline void to_c(
    DN_Class_Struct_t * * lhs
    , DN::v2_2::Class::Struct & rhs)
{
        *(lhs) = reinterpret_cast<DN_Class_Struct_t * >(&(rhs));
}

inline void to_c(
    DN_Class_Struct_t * * lhs
    , DN::v2_2::Class::Struct * rhs)
{
        *(lhs) = reinterpret_cast<DN_Class_Struct_t * >(rhs);
}

inline void to_c_copy(
    DN_Class_Struct_t * lhs
    , DN::v2_2::Class::Struct const & rhs)
{
        memcpy(lhs, &(rhs), sizeof(*(lhs)));
}

