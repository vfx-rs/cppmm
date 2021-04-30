#pragma once
#include <c-optr.h>


#include <optr.hpp>





inline optr::PubCtor const & to_cpp_ref(
    optr_PubCtor_t const * rhs)
{
    return *(reinterpret_cast<optr::PubCtor const * >(rhs));
}

inline optr::PubCtor & to_cpp_ref(
    optr_PubCtor_t * rhs)
{
    return *(reinterpret_cast<optr::PubCtor * >(rhs));
}

inline optr::PubCtor const * to_cpp(
    optr_PubCtor_t const * rhs)
{
    return reinterpret_cast<optr::PubCtor const * >(rhs);
}

inline optr::PubCtor * to_cpp(
    optr_PubCtor_t * rhs)
{
    return reinterpret_cast<optr::PubCtor * >(rhs);
}

inline optr_PubCtor_t const * to_c(
    optr::PubCtor const & rhs)
{
    return reinterpret_cast<optr_PubCtor_t const * >(&(rhs));
}

inline optr_PubCtor_t const * to_c(
    optr::PubCtor const * rhs)
{
    return reinterpret_cast<optr_PubCtor_t const * >(rhs);
}

inline optr_PubCtor_t * to_c(
    optr::PubCtor & rhs)
{
    return reinterpret_cast<optr_PubCtor_t * >(&(rhs));
}

inline optr_PubCtor_t * to_c(
    optr::PubCtor * rhs)
{
    return reinterpret_cast<optr_PubCtor_t * >(rhs);
}


inline optr::PrvCtor const & to_cpp_ref(
    optr_PrvCtor_t const * rhs)
{
    return *(reinterpret_cast<optr::PrvCtor const * >(rhs));
}

inline optr::PrvCtor & to_cpp_ref(
    optr_PrvCtor_t * rhs)
{
    return *(reinterpret_cast<optr::PrvCtor * >(rhs));
}

inline optr::PrvCtor const * to_cpp(
    optr_PrvCtor_t const * rhs)
{
    return reinterpret_cast<optr::PrvCtor const * >(rhs);
}

inline optr::PrvCtor * to_cpp(
    optr_PrvCtor_t * rhs)
{
    return reinterpret_cast<optr::PrvCtor * >(rhs);
}

inline optr_PrvCtor_t const * to_c(
    optr::PrvCtor const & rhs)
{
    return reinterpret_cast<optr_PrvCtor_t const * >(&(rhs));
}

inline optr_PrvCtor_t const * to_c(
    optr::PrvCtor const * rhs)
{
    return reinterpret_cast<optr_PrvCtor_t const * >(rhs);
}

inline optr_PrvCtor_t * to_c(
    optr::PrvCtor & rhs)
{
    return reinterpret_cast<optr_PrvCtor_t * >(&(rhs));
}

inline optr_PrvCtor_t * to_c(
    optr::PrvCtor * rhs)
{
    return reinterpret_cast<optr_PrvCtor_t * >(rhs);
}

inline optr::AllPrv const & to_cpp_ref(
    optr_AllPrv_t const * rhs)
{
    return *(reinterpret_cast<optr::AllPrv const * >(rhs));
}

inline optr::AllPrv & to_cpp_ref(
    optr_AllPrv_t * rhs)
{
    return *(reinterpret_cast<optr::AllPrv * >(rhs));
}

inline optr::AllPrv const * to_cpp(
    optr_AllPrv_t const * rhs)
{
    return reinterpret_cast<optr::AllPrv const * >(rhs);
}

inline optr::AllPrv * to_cpp(
    optr_AllPrv_t * rhs)
{
    return reinterpret_cast<optr::AllPrv * >(rhs);
}

inline optr_AllPrv_t const * to_c(
    optr::AllPrv const & rhs)
{
    return reinterpret_cast<optr_AllPrv_t const * >(&(rhs));
}

inline optr_AllPrv_t const * to_c(
    optr::AllPrv const * rhs)
{
    return reinterpret_cast<optr_AllPrv_t const * >(rhs);
}

inline optr_AllPrv_t * to_c(
    optr::AllPrv & rhs)
{
    return reinterpret_cast<optr_AllPrv_t * >(&(rhs));
}

inline optr_AllPrv_t * to_c(
    optr::AllPrv * rhs)
{
    return reinterpret_cast<optr_AllPrv_t * >(rhs);
}

inline optr::Opaque const & to_cpp_ref(
    optr_Opaque_t const * rhs)
{
    return *(reinterpret_cast<optr::Opaque const * >(rhs));
}

inline optr::Opaque & to_cpp_ref(
    optr_Opaque_t * rhs)
{
    return *(reinterpret_cast<optr::Opaque * >(rhs));
}

inline optr::Opaque const * to_cpp(
    optr_Opaque_t const * rhs)
{
    return reinterpret_cast<optr::Opaque const * >(rhs);
}

inline optr::Opaque * to_cpp(
    optr_Opaque_t * rhs)
{
    return reinterpret_cast<optr::Opaque * >(rhs);
}

inline optr_Opaque_t const * to_c(
    optr::Opaque const & rhs)
{
    return reinterpret_cast<optr_Opaque_t const * >(&(rhs));
}

inline optr_Opaque_t const * to_c(
    optr::Opaque const * rhs)
{
    return reinterpret_cast<optr_Opaque_t const * >(rhs);
}

inline optr_Opaque_t * to_c(
    optr::Opaque & rhs)
{
    return reinterpret_cast<optr_Opaque_t * >(&(rhs));
}

inline optr_Opaque_t * to_c(
    optr::Opaque * rhs)
{
    return reinterpret_cast<optr_Opaque_t * >(rhs);
}
