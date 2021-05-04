#pragma once
#include <c-optr.h>


#include <cstring>
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

inline void to_c(
    optr_PubCtor_t const * * lhs
    , optr::PubCtor const & rhs)
{
        *(lhs) = reinterpret_cast<optr_PubCtor_t const * >(&(rhs));
}

inline void to_c(
    optr_PubCtor_t const * * lhs
    , optr::PubCtor const * rhs)
{
        *(lhs) = reinterpret_cast<optr_PubCtor_t const * >(rhs);
}

inline void to_c(
    optr_PubCtor_t * * lhs
    , optr::PubCtor & rhs)
{
        *(lhs) = reinterpret_cast<optr_PubCtor_t * >(&(rhs));
}

inline void to_c(
    optr_PubCtor_t * * lhs
    , optr::PubCtor * rhs)
{
        *(lhs) = reinterpret_cast<optr_PubCtor_t * >(rhs);
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

inline void to_c(
    optr_PrvCtor_t const * * lhs
    , optr::PrvCtor const & rhs)
{
        *(lhs) = reinterpret_cast<optr_PrvCtor_t const * >(&(rhs));
}

inline void to_c(
    optr_PrvCtor_t const * * lhs
    , optr::PrvCtor const * rhs)
{
        *(lhs) = reinterpret_cast<optr_PrvCtor_t const * >(rhs);
}

inline void to_c(
    optr_PrvCtor_t * * lhs
    , optr::PrvCtor & rhs)
{
        *(lhs) = reinterpret_cast<optr_PrvCtor_t * >(&(rhs));
}

inline void to_c(
    optr_PrvCtor_t * * lhs
    , optr::PrvCtor * rhs)
{
        *(lhs) = reinterpret_cast<optr_PrvCtor_t * >(rhs);
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

inline void to_c(
    optr_AllPrv_t const * * lhs
    , optr::AllPrv const & rhs)
{
        *(lhs) = reinterpret_cast<optr_AllPrv_t const * >(&(rhs));
}

inline void to_c(
    optr_AllPrv_t const * * lhs
    , optr::AllPrv const * rhs)
{
        *(lhs) = reinterpret_cast<optr_AllPrv_t const * >(rhs);
}

inline void to_c(
    optr_AllPrv_t * * lhs
    , optr::AllPrv & rhs)
{
        *(lhs) = reinterpret_cast<optr_AllPrv_t * >(&(rhs));
}

inline void to_c(
    optr_AllPrv_t * * lhs
    , optr::AllPrv * rhs)
{
        *(lhs) = reinterpret_cast<optr_AllPrv_t * >(rhs);
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

inline void to_c(
    optr_Opaque_t const * * lhs
    , optr::Opaque const & rhs)
{
        *(lhs) = reinterpret_cast<optr_Opaque_t const * >(&(rhs));
}

inline void to_c(
    optr_Opaque_t const * * lhs
    , optr::Opaque const * rhs)
{
        *(lhs) = reinterpret_cast<optr_Opaque_t const * >(rhs);
}

inline void to_c(
    optr_Opaque_t * * lhs
    , optr::Opaque & rhs)
{
        *(lhs) = reinterpret_cast<optr_Opaque_t * >(&(rhs));
}

inline void to_c(
    optr_Opaque_t * * lhs
    , optr::Opaque * rhs)
{
        *(lhs) = reinterpret_cast<optr_Opaque_t * >(rhs);
}
