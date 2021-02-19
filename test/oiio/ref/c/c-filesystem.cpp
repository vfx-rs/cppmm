#include <c-filesystem.h>

#include <OpenImageIO/filesystem.h>
#include <cppmm_bind.hpp>
#include <c-filesystem_private.h>


void OpenImageIO_v2_2_Filesystem_IOProxy_~IOProxy(
    OpenImageIO_v2_2_Filesystem_IOProxy * self)
{
    (to_cpp(self)) -> ~IOProxy();
}

char * OpenImageIO_v2_2_Filesystem_IOProxy_proxytype(
    OpenImageIO_v2_2_Filesystem_IOProxy const * self)
{
    return to_c((to_cpp(self)) -> proxytype());
}

void OpenImageIO_v2_2_Filesystem_IOProxy_close(
    OpenImageIO_v2_2_Filesystem_IOProxy * self)
{
    (to_cpp(self)) -> close();
}

_Bool OpenImageIO_v2_2_Filesystem_IOProxy_opened(
    OpenImageIO_v2_2_Filesystem_IOProxy const * self)
{
    return (to_cpp(self)) -> opened();
}

long OpenImageIO_v2_2_Filesystem_IOProxy_tell(
    OpenImageIO_v2_2_Filesystem_IOProxy * self)
{
    return (to_cpp(self)) -> tell();
}

_Bool OpenImageIO_v2_2_Filesystem_IOProxy_seek(
    OpenImageIO_v2_2_Filesystem_IOProxy * self
    , long offset)
{
    return (to_cpp(self)) -> seek(offset);
}

unsigned long OpenImageIO_v2_2_Filesystem_IOProxy_read(
    OpenImageIO_v2_2_Filesystem_IOProxy * self
    , void * buf
    , unsigned long size)
{
    return (to_cpp(self)) -> read(to_cpp(buf), size);
}

unsigned long OpenImageIO_v2_2_Filesystem_IOProxy_write(
    OpenImageIO_v2_2_Filesystem_IOProxy * self
    , void * buf
    , unsigned long size)
{
    return (to_cpp(self)) -> write(to_cpp(buf), size);
}

unsigned long OpenImageIO_v2_2_Filesystem_IOProxy_pread(
    OpenImageIO_v2_2_Filesystem_IOProxy * self
    , void * buf
    , unsigned long size
    , long offset)
{
    return (to_cpp(self)) -> pread(to_cpp(buf), size, offset);
}

unsigned long OpenImageIO_v2_2_Filesystem_IOProxy_pwrite(
    OpenImageIO_v2_2_Filesystem_IOProxy * self
    , void * buf
    , unsigned long size
    , long offset)
{
    return (to_cpp(self)) -> pwrite(to_cpp(buf), size, offset);
}

_Bool OpenImageIO_v2_2_Filesystem_IOProxy_seek(
    OpenImageIO_v2_2_Filesystem_IOProxy * self
    , long offset
    , int origin)
{
    return (to_cpp(self)) -> seek(offset, origin);
}

void OpenImageIO_v2_2_Filesystem_IOMemReader_IOMemReader(
    OpenImageIO_v2_2_Filesystem_IOMemReader * self
    , void * buf
    , unsigned long size)
{
    new (self) IOMemReader(to_cpp(buf), size);
}

char * OpenImageIO_v2_2_Filesystem_IOMemReader_proxytype(
    OpenImageIO_v2_2_Filesystem_IOMemReader const * self)
{
    return to_c((to_cpp(self)) -> proxytype());
}

_Bool OpenImageIO_v2_2_Filesystem_IOMemReader_seek(
    OpenImageIO_v2_2_Filesystem_IOMemReader * self
    , long offset)
{
    return (to_cpp(self)) -> seek(offset);
}

unsigned long OpenImageIO_v2_2_Filesystem_IOMemReader_read(
    OpenImageIO_v2_2_Filesystem_IOMemReader * self
    , void * buf
    , unsigned long size)
{
    return (to_cpp(self)) -> read(to_cpp(buf), size);
}

unsigned long OpenImageIO_v2_2_Filesystem_IOMemReader_pread(
    OpenImageIO_v2_2_Filesystem_IOMemReader * self
    , void * buf
    , unsigned long size
    , long offset)
{
    return (to_cpp(self)) -> pread(to_cpp(buf), size, offset);
}

void OpenImageIO_v2_2_Filesystem_IOMemReader_~IOMemReader(
    OpenImageIO_v2_2_Filesystem_IOMemReader * self)
{
    (to_cpp(self)) -> ~IOMemReader();
}
