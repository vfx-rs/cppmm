#pragma once
#include <c-filesystem.h>


#include <OpenImageIO/filesystem.h>
#include <cstring>


inline OpenImageIO_v2_2::Filesystem::IOProxy::Mode const & OIIO_Filesystem_IOProxy_Mode_to_cpp_ref(
    OIIO_Filesystem_IOProxy_Mode const * rhs)
{
    return *(reinterpret_cast<OpenImageIO_v2_2::Filesystem::IOProxy::Mode const * >(rhs));
}

inline OpenImageIO_v2_2::Filesystem::IOProxy::Mode & OIIO_Filesystem_IOProxy_Mode_to_cpp_ref(
    OIIO_Filesystem_IOProxy_Mode * rhs)
{
    return *(reinterpret_cast<OpenImageIO_v2_2::Filesystem::IOProxy::Mode * >(rhs));
}

inline OpenImageIO_v2_2::Filesystem::IOProxy::Mode const * OIIO_Filesystem_IOProxy_Mode_to_cpp(
    OIIO_Filesystem_IOProxy_Mode const * rhs)
{
    return reinterpret_cast<OpenImageIO_v2_2::Filesystem::IOProxy::Mode const * >(rhs);
}

inline OpenImageIO_v2_2::Filesystem::IOProxy::Mode * OIIO_Filesystem_IOProxy_Mode_to_cpp(
    OIIO_Filesystem_IOProxy_Mode * rhs)
{
    return reinterpret_cast<OpenImageIO_v2_2::Filesystem::IOProxy::Mode * >(rhs);
}

inline OIIO_Filesystem_IOProxy_Mode const * to_c(
    OpenImageIO_v2_2::Filesystem::IOProxy::Mode const & rhs)
{
    return reinterpret_cast<OIIO_Filesystem_IOProxy_Mode const * >(&(rhs));
}

inline OIIO_Filesystem_IOProxy_Mode const * to_c(
    OpenImageIO_v2_2::Filesystem::IOProxy::Mode const * rhs)
{
    return reinterpret_cast<OIIO_Filesystem_IOProxy_Mode const * >(rhs);
}

inline OIIO_Filesystem_IOProxy_Mode * to_c(
    OpenImageIO_v2_2::Filesystem::IOProxy::Mode & rhs)
{
    return reinterpret_cast<OIIO_Filesystem_IOProxy_Mode * >(&(rhs));
}

inline OIIO_Filesystem_IOProxy_Mode * to_c(
    OpenImageIO_v2_2::Filesystem::IOProxy::Mode * rhs)
{
    return reinterpret_cast<OIIO_Filesystem_IOProxy_Mode * >(rhs);
}

inline OIIO_Filesystem_IOProxy_Mode to_c_copy(
    OpenImageIO_v2_2::Filesystem::IOProxy::Mode const & rhs)
{
    OIIO_Filesystem_IOProxy_Mode result;
    memcpy(&(result), &(rhs), sizeof(result));
    return result;
}













inline OpenImageIO_v2_2::Filesystem::IOProxy const & to_cpp_ref(
    OIIO_Filesystem_IOProxy_t const * rhs)
{
    return *(reinterpret_cast<OpenImageIO_v2_2::Filesystem::IOProxy const * >(rhs));
}

inline OpenImageIO_v2_2::Filesystem::IOProxy & to_cpp_ref(
    OIIO_Filesystem_IOProxy_t * rhs)
{
    return *(reinterpret_cast<OpenImageIO_v2_2::Filesystem::IOProxy * >(rhs));
}

inline OpenImageIO_v2_2::Filesystem::IOProxy const * to_cpp(
    OIIO_Filesystem_IOProxy_t const * rhs)
{
    return reinterpret_cast<OpenImageIO_v2_2::Filesystem::IOProxy const * >(rhs);
}

inline OpenImageIO_v2_2::Filesystem::IOProxy * to_cpp(
    OIIO_Filesystem_IOProxy_t * rhs)
{
    return reinterpret_cast<OpenImageIO_v2_2::Filesystem::IOProxy * >(rhs);
}

inline OIIO_Filesystem_IOProxy_t const * to_c(
    OpenImageIO_v2_2::Filesystem::IOProxy const & rhs)
{
    return reinterpret_cast<OIIO_Filesystem_IOProxy_t const * >(&(rhs));
}

inline OIIO_Filesystem_IOProxy_t const * to_c(
    OpenImageIO_v2_2::Filesystem::IOProxy const * rhs)
{
    return reinterpret_cast<OIIO_Filesystem_IOProxy_t const * >(rhs);
}

inline OIIO_Filesystem_IOProxy_t * to_c(
    OpenImageIO_v2_2::Filesystem::IOProxy & rhs)
{
    return reinterpret_cast<OIIO_Filesystem_IOProxy_t * >(&(rhs));
}

inline OIIO_Filesystem_IOProxy_t * to_c(
    OpenImageIO_v2_2::Filesystem::IOProxy * rhs)
{
    return reinterpret_cast<OIIO_Filesystem_IOProxy_t * >(rhs);
}













inline OpenImageIO_v2_2::Filesystem::IOMemReader const & to_cpp_ref(
    OIIO_Filesystem_IOMemReader_t const * rhs)
{
    return *(reinterpret_cast<OpenImageIO_v2_2::Filesystem::IOMemReader const * >(rhs));
}

inline OpenImageIO_v2_2::Filesystem::IOMemReader & to_cpp_ref(
    OIIO_Filesystem_IOMemReader_t * rhs)
{
    return *(reinterpret_cast<OpenImageIO_v2_2::Filesystem::IOMemReader * >(rhs));
}

inline OpenImageIO_v2_2::Filesystem::IOMemReader const * to_cpp(
    OIIO_Filesystem_IOMemReader_t const * rhs)
{
    return reinterpret_cast<OpenImageIO_v2_2::Filesystem::IOMemReader const * >(rhs);
}

inline OpenImageIO_v2_2::Filesystem::IOMemReader * to_cpp(
    OIIO_Filesystem_IOMemReader_t * rhs)
{
    return reinterpret_cast<OpenImageIO_v2_2::Filesystem::IOMemReader * >(rhs);
}

inline OIIO_Filesystem_IOMemReader_t const * to_c(
    OpenImageIO_v2_2::Filesystem::IOMemReader const & rhs)
{
    return reinterpret_cast<OIIO_Filesystem_IOMemReader_t const * >(&(rhs));
}

inline OIIO_Filesystem_IOMemReader_t const * to_c(
    OpenImageIO_v2_2::Filesystem::IOMemReader const * rhs)
{
    return reinterpret_cast<OIIO_Filesystem_IOMemReader_t const * >(rhs);
}

inline OIIO_Filesystem_IOMemReader_t * to_c(
    OpenImageIO_v2_2::Filesystem::IOMemReader & rhs)
{
    return reinterpret_cast<OIIO_Filesystem_IOMemReader_t * >(&(rhs));
}

inline OIIO_Filesystem_IOMemReader_t * to_c(
    OpenImageIO_v2_2::Filesystem::IOMemReader * rhs)
{
    return reinterpret_cast<OIIO_Filesystem_IOMemReader_t * >(rhs);
}

/** Return the filename (excluding any directories, but including the
file extension, if any) of a filepath. */

/** Return the file extension (including the last '.' if
include_dot=true) of a filename or filepath. */

/** Return all but the last part of the path, for example,
parent_path("foo/bar") returns "foo", and parent_path("foo")
returns "". */

/** Replace the file extension of a filename or filepath. Does not alter
filepath, just returns a new string.  Note that the new_extension
should contain a leading '.' dot. */
