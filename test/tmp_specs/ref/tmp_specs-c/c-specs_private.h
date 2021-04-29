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

inline specs_IntAttribute_t const * to_c(
    specs::Attribute<int> const & rhs)
{
    return reinterpret_cast<specs_IntAttribute_t const * >(&(rhs));
}

inline specs_IntAttribute_t const * to_c(
    specs::Attribute<int> const * rhs)
{
    return reinterpret_cast<specs_IntAttribute_t const * >(rhs);
}

inline specs_IntAttribute_t * to_c(
    specs::Attribute<int> & rhs)
{
    return reinterpret_cast<specs_IntAttribute_t * >(&(rhs));
}

inline specs_IntAttribute_t * to_c(
    specs::Attribute<int> * rhs)
{
    return reinterpret_cast<specs_IntAttribute_t * >(rhs);
}

inline specs_IntAttribute_t to_c_copy(
    specs::Attribute<int> const & rhs)
{
    specs_IntAttribute_t result;
    memcpy(&(result), &(rhs), sizeof(result));
    return result;
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

inline specs_FloatAttribute_t const * to_c(
    specs::Attribute<float> const & rhs)
{
    return reinterpret_cast<specs_FloatAttribute_t const * >(&(rhs));
}

inline specs_FloatAttribute_t const * to_c(
    specs::Attribute<float> const * rhs)
{
    return reinterpret_cast<specs_FloatAttribute_t const * >(rhs);
}

inline specs_FloatAttribute_t * to_c(
    specs::Attribute<float> & rhs)
{
    return reinterpret_cast<specs_FloatAttribute_t * >(&(rhs));
}

inline specs_FloatAttribute_t * to_c(
    specs::Attribute<float> * rhs)
{
    return reinterpret_cast<specs_FloatAttribute_t * >(rhs);
}

inline specs_FloatAttribute_t to_c_copy(
    specs::Attribute<float> const & rhs)
{
    specs_FloatAttribute_t result;
    memcpy(&(result), &(rhs), sizeof(result));
    return result;
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

inline specs_Specs_t const * to_c(
    specs::Specs const & rhs)
{
    return reinterpret_cast<specs_Specs_t const * >(&(rhs));
}

inline specs_Specs_t const * to_c(
    specs::Specs const * rhs)
{
    return reinterpret_cast<specs_Specs_t const * >(rhs);
}

inline specs_Specs_t * to_c(
    specs::Specs & rhs)
{
    return reinterpret_cast<specs_Specs_t * >(&(rhs));
}

inline specs_Specs_t * to_c(
    specs::Specs * rhs)
{
    return reinterpret_cast<specs_Specs_t * >(rhs);
}

inline specs_Specs_t to_c_copy(
    specs::Specs const & rhs)
{
    specs_Specs_t result;
    memcpy(&(result), &(rhs), sizeof(result));
    return result;
}
