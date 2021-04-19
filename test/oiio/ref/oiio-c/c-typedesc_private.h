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

inline OIIO_TypeDesc_BASETYPE const * to_c(
    OpenImageIO_v2_2::TypeDesc::BASETYPE const & rhs)
{
    return reinterpret_cast<OIIO_TypeDesc_BASETYPE const * >(&(rhs));
}

inline OIIO_TypeDesc_BASETYPE const * to_c(
    OpenImageIO_v2_2::TypeDesc::BASETYPE const * rhs)
{
    return reinterpret_cast<OIIO_TypeDesc_BASETYPE const * >(rhs);
}

inline OIIO_TypeDesc_BASETYPE * to_c(
    OpenImageIO_v2_2::TypeDesc::BASETYPE & rhs)
{
    return reinterpret_cast<OIIO_TypeDesc_BASETYPE * >(&(rhs));
}

inline OIIO_TypeDesc_BASETYPE * to_c(
    OpenImageIO_v2_2::TypeDesc::BASETYPE * rhs)
{
    return reinterpret_cast<OIIO_TypeDesc_BASETYPE * >(rhs);
}

inline OIIO_TypeDesc_BASETYPE to_c_copy(
    OpenImageIO_v2_2::TypeDesc::BASETYPE const & rhs)
{
    OIIO_TypeDesc_BASETYPE result;
    memcpy(&(result), &(rhs), sizeof(result));
    return result;
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

inline OIIO_TypeDesc_AGGREGATE const * to_c(
    OpenImageIO_v2_2::TypeDesc::AGGREGATE const & rhs)
{
    return reinterpret_cast<OIIO_TypeDesc_AGGREGATE const * >(&(rhs));
}

inline OIIO_TypeDesc_AGGREGATE const * to_c(
    OpenImageIO_v2_2::TypeDesc::AGGREGATE const * rhs)
{
    return reinterpret_cast<OIIO_TypeDesc_AGGREGATE const * >(rhs);
}

inline OIIO_TypeDesc_AGGREGATE * to_c(
    OpenImageIO_v2_2::TypeDesc::AGGREGATE & rhs)
{
    return reinterpret_cast<OIIO_TypeDesc_AGGREGATE * >(&(rhs));
}

inline OIIO_TypeDesc_AGGREGATE * to_c(
    OpenImageIO_v2_2::TypeDesc::AGGREGATE * rhs)
{
    return reinterpret_cast<OIIO_TypeDesc_AGGREGATE * >(rhs);
}

inline OIIO_TypeDesc_AGGREGATE to_c_copy(
    OpenImageIO_v2_2::TypeDesc::AGGREGATE const & rhs)
{
    OIIO_TypeDesc_AGGREGATE result;
    memcpy(&(result), &(rhs), sizeof(result));
    return result;
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

inline OIIO_TypeDesc_VECSEMANTICS const * to_c(
    OpenImageIO_v2_2::TypeDesc::VECSEMANTICS const & rhs)
{
    return reinterpret_cast<OIIO_TypeDesc_VECSEMANTICS const * >(&(rhs));
}

inline OIIO_TypeDesc_VECSEMANTICS const * to_c(
    OpenImageIO_v2_2::TypeDesc::VECSEMANTICS const * rhs)
{
    return reinterpret_cast<OIIO_TypeDesc_VECSEMANTICS const * >(rhs);
}

inline OIIO_TypeDesc_VECSEMANTICS * to_c(
    OpenImageIO_v2_2::TypeDesc::VECSEMANTICS & rhs)
{
    return reinterpret_cast<OIIO_TypeDesc_VECSEMANTICS * >(&(rhs));
}

inline OIIO_TypeDesc_VECSEMANTICS * to_c(
    OpenImageIO_v2_2::TypeDesc::VECSEMANTICS * rhs)
{
    return reinterpret_cast<OIIO_TypeDesc_VECSEMANTICS * >(rhs);
}

inline OIIO_TypeDesc_VECSEMANTICS to_c_copy(
    OpenImageIO_v2_2::TypeDesc::VECSEMANTICS const & rhs)
{
    OIIO_TypeDesc_VECSEMANTICS result;
    memcpy(&(result), &(rhs), sizeof(result));
    return result;
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

inline OIIO_TypeDesc_t const * to_c(
    OpenImageIO_v2_2::TypeDesc const & rhs)
{
    return reinterpret_cast<OIIO_TypeDesc_t const * >(&(rhs));
}

inline OIIO_TypeDesc_t const * to_c(
    OpenImageIO_v2_2::TypeDesc const * rhs)
{
    return reinterpret_cast<OIIO_TypeDesc_t const * >(rhs);
}

inline OIIO_TypeDesc_t * to_c(
    OpenImageIO_v2_2::TypeDesc & rhs)
{
    return reinterpret_cast<OIIO_TypeDesc_t * >(&(rhs));
}

inline OIIO_TypeDesc_t * to_c(
    OpenImageIO_v2_2::TypeDesc * rhs)
{
    return reinterpret_cast<OIIO_TypeDesc_t * >(rhs);
}
