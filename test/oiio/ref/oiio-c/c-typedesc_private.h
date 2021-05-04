#pragma once
#include <c-typedesc.h>


#include <OpenImageIO/typedesc.h>
#include <cstring>


inline OpenImageIO_v2_2::TypeDesc::BASETYPE const & OIIO_TypeDesc_BASETYPE_to_cpp_ref(
    OIIO_TypeDesc_BASETYPE const * rhs)
{
        return *(reinterpret_cast<OpenImageIO_v2_2::TypeDesc::BASETYPE const * >(rhs));
}

inline OpenImageIO_v2_2::TypeDesc::BASETYPE & OIIO_TypeDesc_BASETYPE_to_cpp_ref(
    OIIO_TypeDesc_BASETYPE * rhs)
{
        return *(reinterpret_cast<OpenImageIO_v2_2::TypeDesc::BASETYPE * >(rhs));
}

inline OpenImageIO_v2_2::TypeDesc::BASETYPE const * OIIO_TypeDesc_BASETYPE_to_cpp(
    OIIO_TypeDesc_BASETYPE const * rhs)
{
        return reinterpret_cast<OpenImageIO_v2_2::TypeDesc::BASETYPE const * >(rhs);
}

inline OpenImageIO_v2_2::TypeDesc::BASETYPE * OIIO_TypeDesc_BASETYPE_to_cpp(
    OIIO_TypeDesc_BASETYPE * rhs)
{
        return reinterpret_cast<OpenImageIO_v2_2::TypeDesc::BASETYPE * >(rhs);
}

inline void to_c(
    OIIO_TypeDesc_BASETYPE const * * lhs
    , OpenImageIO_v2_2::TypeDesc::BASETYPE const & rhs)
{
        *(lhs) = reinterpret_cast<OIIO_TypeDesc_BASETYPE const * >(&(rhs));
}

inline void to_c(
    OIIO_TypeDesc_BASETYPE const * * lhs
    , OpenImageIO_v2_2::TypeDesc::BASETYPE const * rhs)
{
        *(lhs) = reinterpret_cast<OIIO_TypeDesc_BASETYPE const * >(rhs);
}

inline void to_c(
    OIIO_TypeDesc_BASETYPE * * lhs
    , OpenImageIO_v2_2::TypeDesc::BASETYPE & rhs)
{
        *(lhs) = reinterpret_cast<OIIO_TypeDesc_BASETYPE * >(&(rhs));
}

inline void to_c(
    OIIO_TypeDesc_BASETYPE * * lhs
    , OpenImageIO_v2_2::TypeDesc::BASETYPE * rhs)
{
        *(lhs) = reinterpret_cast<OIIO_TypeDesc_BASETYPE * >(rhs);
}

inline void to_c_copy(
    OIIO_TypeDesc_BASETYPE * lhs
    , OpenImageIO_v2_2::TypeDesc::BASETYPE const & rhs)
{
        memcpy(lhs, &(rhs), sizeof(*(lhs)));
}

inline OpenImageIO_v2_2::TypeDesc::AGGREGATE const & OIIO_TypeDesc_AGGREGATE_to_cpp_ref(
    OIIO_TypeDesc_AGGREGATE const * rhs)
{
        return *(reinterpret_cast<OpenImageIO_v2_2::TypeDesc::AGGREGATE const * >(rhs));
}

inline OpenImageIO_v2_2::TypeDesc::AGGREGATE & OIIO_TypeDesc_AGGREGATE_to_cpp_ref(
    OIIO_TypeDesc_AGGREGATE * rhs)
{
        return *(reinterpret_cast<OpenImageIO_v2_2::TypeDesc::AGGREGATE * >(rhs));
}

inline OpenImageIO_v2_2::TypeDesc::AGGREGATE const * OIIO_TypeDesc_AGGREGATE_to_cpp(
    OIIO_TypeDesc_AGGREGATE const * rhs)
{
        return reinterpret_cast<OpenImageIO_v2_2::TypeDesc::AGGREGATE const * >(rhs);
}

inline OpenImageIO_v2_2::TypeDesc::AGGREGATE * OIIO_TypeDesc_AGGREGATE_to_cpp(
    OIIO_TypeDesc_AGGREGATE * rhs)
{
        return reinterpret_cast<OpenImageIO_v2_2::TypeDesc::AGGREGATE * >(rhs);
}

inline void to_c(
    OIIO_TypeDesc_AGGREGATE const * * lhs
    , OpenImageIO_v2_2::TypeDesc::AGGREGATE const & rhs)
{
        *(lhs) = reinterpret_cast<OIIO_TypeDesc_AGGREGATE const * >(&(rhs));
}

inline void to_c(
    OIIO_TypeDesc_AGGREGATE const * * lhs
    , OpenImageIO_v2_2::TypeDesc::AGGREGATE const * rhs)
{
        *(lhs) = reinterpret_cast<OIIO_TypeDesc_AGGREGATE const * >(rhs);
}

inline void to_c(
    OIIO_TypeDesc_AGGREGATE * * lhs
    , OpenImageIO_v2_2::TypeDesc::AGGREGATE & rhs)
{
        *(lhs) = reinterpret_cast<OIIO_TypeDesc_AGGREGATE * >(&(rhs));
}

inline void to_c(
    OIIO_TypeDesc_AGGREGATE * * lhs
    , OpenImageIO_v2_2::TypeDesc::AGGREGATE * rhs)
{
        *(lhs) = reinterpret_cast<OIIO_TypeDesc_AGGREGATE * >(rhs);
}

inline void to_c_copy(
    OIIO_TypeDesc_AGGREGATE * lhs
    , OpenImageIO_v2_2::TypeDesc::AGGREGATE const & rhs)
{
        memcpy(lhs, &(rhs), sizeof(*(lhs)));
}

inline OpenImageIO_v2_2::TypeDesc::VECSEMANTICS const & OIIO_TypeDesc_VECSEMANTICS_to_cpp_ref(
    OIIO_TypeDesc_VECSEMANTICS const * rhs)
{
        return *(reinterpret_cast<OpenImageIO_v2_2::TypeDesc::VECSEMANTICS const * >(rhs));
}

inline OpenImageIO_v2_2::TypeDesc::VECSEMANTICS & OIIO_TypeDesc_VECSEMANTICS_to_cpp_ref(
    OIIO_TypeDesc_VECSEMANTICS * rhs)
{
        return *(reinterpret_cast<OpenImageIO_v2_2::TypeDesc::VECSEMANTICS * >(rhs));
}

inline OpenImageIO_v2_2::TypeDesc::VECSEMANTICS const * OIIO_TypeDesc_VECSEMANTICS_to_cpp(
    OIIO_TypeDesc_VECSEMANTICS const * rhs)
{
        return reinterpret_cast<OpenImageIO_v2_2::TypeDesc::VECSEMANTICS const * >(rhs);
}

inline OpenImageIO_v2_2::TypeDesc::VECSEMANTICS * OIIO_TypeDesc_VECSEMANTICS_to_cpp(
    OIIO_TypeDesc_VECSEMANTICS * rhs)
{
        return reinterpret_cast<OpenImageIO_v2_2::TypeDesc::VECSEMANTICS * >(rhs);
}

inline void to_c(
    OIIO_TypeDesc_VECSEMANTICS const * * lhs
    , OpenImageIO_v2_2::TypeDesc::VECSEMANTICS const & rhs)
{
        *(lhs) = reinterpret_cast<OIIO_TypeDesc_VECSEMANTICS const * >(&(rhs));
}

inline void to_c(
    OIIO_TypeDesc_VECSEMANTICS const * * lhs
    , OpenImageIO_v2_2::TypeDesc::VECSEMANTICS const * rhs)
{
        *(lhs) = reinterpret_cast<OIIO_TypeDesc_VECSEMANTICS const * >(rhs);
}

inline void to_c(
    OIIO_TypeDesc_VECSEMANTICS * * lhs
    , OpenImageIO_v2_2::TypeDesc::VECSEMANTICS & rhs)
{
        *(lhs) = reinterpret_cast<OIIO_TypeDesc_VECSEMANTICS * >(&(rhs));
}

inline void to_c(
    OIIO_TypeDesc_VECSEMANTICS * * lhs
    , OpenImageIO_v2_2::TypeDesc::VECSEMANTICS * rhs)
{
        *(lhs) = reinterpret_cast<OIIO_TypeDesc_VECSEMANTICS * >(rhs);
}

inline void to_c_copy(
    OIIO_TypeDesc_VECSEMANTICS * lhs
    , OpenImageIO_v2_2::TypeDesc::VECSEMANTICS const & rhs)
{
        memcpy(lhs, &(rhs), sizeof(*(lhs)));
}

inline OpenImageIO_v2_2::TypeDesc const & to_cpp_ref(
    OIIO_TypeDesc_t const * rhs)
{
        return *(reinterpret_cast<OpenImageIO_v2_2::TypeDesc const * >(rhs));
}

inline OpenImageIO_v2_2::TypeDesc & to_cpp_ref(
    OIIO_TypeDesc_t * rhs)
{
        return *(reinterpret_cast<OpenImageIO_v2_2::TypeDesc * >(rhs));
}

inline OpenImageIO_v2_2::TypeDesc const * to_cpp(
    OIIO_TypeDesc_t const * rhs)
{
        return reinterpret_cast<OpenImageIO_v2_2::TypeDesc const * >(rhs);
}

inline OpenImageIO_v2_2::TypeDesc * to_cpp(
    OIIO_TypeDesc_t * rhs)
{
        return reinterpret_cast<OpenImageIO_v2_2::TypeDesc * >(rhs);
}

inline void to_c(
    OIIO_TypeDesc_t const * * lhs
    , OpenImageIO_v2_2::TypeDesc const & rhs)
{
        *(lhs) = reinterpret_cast<OIIO_TypeDesc_t const * >(&(rhs));
}

inline void to_c(
    OIIO_TypeDesc_t const * * lhs
    , OpenImageIO_v2_2::TypeDesc const * rhs)
{
        *(lhs) = reinterpret_cast<OIIO_TypeDesc_t const * >(rhs);
}

inline void to_c(
    OIIO_TypeDesc_t * * lhs
    , OpenImageIO_v2_2::TypeDesc & rhs)
{
        *(lhs) = reinterpret_cast<OIIO_TypeDesc_t * >(&(rhs));
}

inline void to_c(
    OIIO_TypeDesc_t * * lhs
    , OpenImageIO_v2_2::TypeDesc * rhs)
{
        *(lhs) = reinterpret_cast<OIIO_TypeDesc_t * >(rhs);
}
