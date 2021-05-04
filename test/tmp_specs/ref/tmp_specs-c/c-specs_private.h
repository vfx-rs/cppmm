#pragma once
#include <c-specs.h>


#include <cstring>
#include <tmp_specs.hpp>



inline specs::Attribute<int> const & to_cpp_ref(
    specs_IntAttribute_t const * rhs)
{
        return *(reinterpret_cast<specs::Attribute<int> const * >(rhs));
}

inline specs::Attribute<int> & to_cpp_ref(
    specs_IntAttribute_t * rhs)
{
        return *(reinterpret_cast<specs::Attribute<int> * >(rhs));
}

inline specs::Attribute<int> const * to_cpp(
    specs_IntAttribute_t const * rhs)
{
        return reinterpret_cast<specs::Attribute<int> const * >(rhs);
}

inline specs::Attribute<int> * to_cpp(
    specs_IntAttribute_t * rhs)
{
        return reinterpret_cast<specs::Attribute<int> * >(rhs);
}

inline void to_c(
    specs_IntAttribute_t const * * lhs
    , specs::Attribute<int> const & rhs)
{
        *(lhs) = reinterpret_cast<specs_IntAttribute_t const * >(&(rhs));
}

inline void to_c(
    specs_IntAttribute_t const * * lhs
    , specs::Attribute<int> const * rhs)
{
        *(lhs) = reinterpret_cast<specs_IntAttribute_t const * >(rhs);
}

inline void to_c(
    specs_IntAttribute_t * * lhs
    , specs::Attribute<int> & rhs)
{
        *(lhs) = reinterpret_cast<specs_IntAttribute_t * >(&(rhs));
}

inline void to_c(
    specs_IntAttribute_t * * lhs
    , specs::Attribute<int> * rhs)
{
        *(lhs) = reinterpret_cast<specs_IntAttribute_t * >(rhs);
}

inline void to_c_copy(
    specs_IntAttribute_t * lhs
    , specs::Attribute<int> const & rhs)
{
        memcpy(lhs, &(rhs), sizeof(*(lhs)));
}


inline specs::Attribute<float> const & to_cpp_ref(
    specs_FloatAttribute_t const * rhs)
{
        return *(reinterpret_cast<specs::Attribute<float> const * >(rhs));
}

inline specs::Attribute<float> & to_cpp_ref(
    specs_FloatAttribute_t * rhs)
{
        return *(reinterpret_cast<specs::Attribute<float> * >(rhs));
}

inline specs::Attribute<float> const * to_cpp(
    specs_FloatAttribute_t const * rhs)
{
        return reinterpret_cast<specs::Attribute<float> const * >(rhs);
}

inline specs::Attribute<float> * to_cpp(
    specs_FloatAttribute_t * rhs)
{
        return reinterpret_cast<specs::Attribute<float> * >(rhs);
}

inline void to_c(
    specs_FloatAttribute_t const * * lhs
    , specs::Attribute<float> const & rhs)
{
        *(lhs) = reinterpret_cast<specs_FloatAttribute_t const * >(&(rhs));
}

inline void to_c(
    specs_FloatAttribute_t const * * lhs
    , specs::Attribute<float> const * rhs)
{
        *(lhs) = reinterpret_cast<specs_FloatAttribute_t const * >(rhs);
}

inline void to_c(
    specs_FloatAttribute_t * * lhs
    , specs::Attribute<float> & rhs)
{
        *(lhs) = reinterpret_cast<specs_FloatAttribute_t * >(&(rhs));
}

inline void to_c(
    specs_FloatAttribute_t * * lhs
    , specs::Attribute<float> * rhs)
{
        *(lhs) = reinterpret_cast<specs_FloatAttribute_t * >(rhs);
}

inline void to_c_copy(
    specs_FloatAttribute_t * lhs
    , specs::Attribute<float> const & rhs)
{
        memcpy(lhs, &(rhs), sizeof(*(lhs)));
}





inline specs::Specs const & to_cpp_ref(
    specs_Specs_t const * rhs)
{
        return *(reinterpret_cast<specs::Specs const * >(rhs));
}

inline specs::Specs & to_cpp_ref(
    specs_Specs_t * rhs)
{
        return *(reinterpret_cast<specs::Specs * >(rhs));
}

inline specs::Specs const * to_cpp(
    specs_Specs_t const * rhs)
{
        return reinterpret_cast<specs::Specs const * >(rhs);
}

inline specs::Specs * to_cpp(
    specs_Specs_t * rhs)
{
        return reinterpret_cast<specs::Specs * >(rhs);
}

inline void to_c(
    specs_Specs_t const * * lhs
    , specs::Specs const & rhs)
{
        *(lhs) = reinterpret_cast<specs_Specs_t const * >(&(rhs));
}

inline void to_c(
    specs_Specs_t const * * lhs
    , specs::Specs const * rhs)
{
        *(lhs) = reinterpret_cast<specs_Specs_t const * >(rhs);
}

inline void to_c(
    specs_Specs_t * * lhs
    , specs::Specs & rhs)
{
        *(lhs) = reinterpret_cast<specs_Specs_t * >(&(rhs));
}

inline void to_c(
    specs_Specs_t * * lhs
    , specs::Specs * rhs)
{
        *(lhs) = reinterpret_cast<specs_Specs_t * >(rhs);
}

inline void to_c_copy(
    specs_Specs_t * lhs
    , specs::Specs const & rhs)
{
        memcpy(lhs, &(rhs), sizeof(*(lhs)));
}
