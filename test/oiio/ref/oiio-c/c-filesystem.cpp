#include <c-filesystem_private.h>

#include <new>
#include <std_string_private.h>

void OpenImageIO_v2_2__Filesystem__IOProxy_delete(
    OIIO_Filesystem_IOProxy_t * this_)
{
    (to_cpp(this_)) -> OpenImageIO_v2_2::Filesystem::IOProxy::~IOProxy();
}
char const * OpenImageIO_v2_2__Filesystem__IOProxy_proxytype(
    OIIO_Filesystem_IOProxy_t const * this_)
{
    return (to_cpp(this_)) -> proxytype();
}
void OpenImageIO_v2_2__Filesystem__IOProxy_close(
    OIIO_Filesystem_IOProxy_t * this_)
{
    (to_cpp(this_)) -> close();
}
_Bool OpenImageIO_v2_2__Filesystem__IOProxy_opened(
    OIIO_Filesystem_IOProxy_t const * this_)
{
    return (to_cpp(this_)) -> opened();
}
long OpenImageIO_v2_2__Filesystem__IOProxy_tell(
    OIIO_Filesystem_IOProxy_t * this_)
{
    return (to_cpp(this_)) -> tell();
}
_Bool OpenImageIO_v2_2__Filesystem__IOProxy_seek(
    OIIO_Filesystem_IOProxy_t * this_
    , long offset)
{
    return (to_cpp(this_)) -> seek(offset);
}
unsigned long OpenImageIO_v2_2__Filesystem__IOProxy_read(
    OIIO_Filesystem_IOProxy_t * this_
    , void * buf
    , unsigned long size)
{
    return (to_cpp(this_)) -> read(buf, size);
}
unsigned long OpenImageIO_v2_2__Filesystem__IOProxy_write(
    OIIO_Filesystem_IOProxy_t * this_
    , void const * buf
    , unsigned long size)
{
    return (to_cpp(this_)) -> write(buf, size);
}
unsigned long OpenImageIO_v2_2__Filesystem__IOProxy_pread(
    OIIO_Filesystem_IOProxy_t * this_
    , void * buf
    , unsigned long size
    , long offset)
{
    return (to_cpp(this_)) -> pread(buf, size, offset);
}
unsigned long OpenImageIO_v2_2__Filesystem__IOProxy_pwrite(
    OIIO_Filesystem_IOProxy_t * this_
    , void const * buf
    , unsigned long size
    , long offset)
{
    return (to_cpp(this_)) -> pwrite(buf, size, offset);
}
std___cxx11_string_t const * OpenImageIO_v2_2__Filesystem__IOProxy_filename(
    OIIO_Filesystem_IOProxy_t const * this_)
{
    return to_c((to_cpp(this_)) -> filename());
}
_Bool OpenImageIO_v2_2__Filesystem__IOProxy_seek_1(
    OIIO_Filesystem_IOProxy_t * this_
    , long offset
    , int origin)
{
    return (to_cpp(this_)) -> seek(offset, origin);
}
char const * OpenImageIO_v2_2__Filesystem__IOMemReader_proxytype(
    OIIO_Filesystem_IOMemReader_t const * this_)
{
    return (to_cpp(this_)) -> proxytype();
}
void OpenImageIO_v2_2__Filesystem__IOMemReader_close(
    OIIO_Filesystem_IOMemReader_t * this_)
{
    (to_cpp(this_)) -> close();
}
_Bool OpenImageIO_v2_2__Filesystem__IOMemReader_opened(
    OIIO_Filesystem_IOMemReader_t const * this_)
{
    return (to_cpp(this_)) -> opened();
}
long OpenImageIO_v2_2__Filesystem__IOMemReader_tell(
    OIIO_Filesystem_IOMemReader_t * this_)
{
    return (to_cpp(this_)) -> tell();
}
_Bool OpenImageIO_v2_2__Filesystem__IOMemReader_seek(
    OIIO_Filesystem_IOMemReader_t * this_
    , long offset)
{
    return (to_cpp(this_)) -> seek(offset);
}
unsigned long OpenImageIO_v2_2__Filesystem__IOMemReader_read(
    OIIO_Filesystem_IOMemReader_t * this_
    , void * buf
    , unsigned long size)
{
    return (to_cpp(this_)) -> read(buf, size);
}
unsigned long OpenImageIO_v2_2__Filesystem__IOMemReader_write(
    OIIO_Filesystem_IOMemReader_t * this_
    , void const * buf
    , unsigned long size)
{
    return (to_cpp(this_)) -> write(buf, size);
}
unsigned long OpenImageIO_v2_2__Filesystem__IOMemReader_pread(
    OIIO_Filesystem_IOMemReader_t * this_
    , void * buf
    , unsigned long size
    , long offset)
{
    return (to_cpp(this_)) -> pread(buf, size, offset);
}
unsigned long OpenImageIO_v2_2__Filesystem__IOMemReader_pwrite(
    OIIO_Filesystem_IOMemReader_t * this_
    , void const * buf
    , unsigned long size
    , long offset)
{
    return (to_cpp(this_)) -> pwrite(buf, size, offset);
}
_Bool OpenImageIO_v2_2__Filesystem__IOMemReader_seek_1(
    OIIO_Filesystem_IOMemReader_t * this_
    , long offset
    , int origin)
{
    return (to_cpp(this_)) -> seek(offset, origin);
}
void OpenImageIO_v2_2__Filesystem__IOMemReader_new(
    OIIO_Filesystem_IOMemReader_t * this_
    , void * buf
    , unsigned long size)
{
    new (this_) OpenImageIO_v2_2::Filesystem::IOMemReader(buf, size);
}
void OpenImageIO_v2_2__Filesystem__IOMemReader_delete(
    OIIO_Filesystem_IOMemReader_t * this_)
{
    (to_cpp(this_)) -> OpenImageIO_v2_2::Filesystem::IOMemReader::~IOMemReader();
}
std___cxx11_string_t OpenImageIO_v2_2_Filesystem_filename(
    std___cxx11_string_t const * filepath)
{
    return to_c_copy(OpenImageIO_v2_2::Filesystem::filename(to_cpp_ref(filepath)));
}
std___cxx11_string_t OpenImageIO_v2_2_Filesystem_extension(
    std___cxx11_string_t const * filepath
    , _Bool include_dot)
{
    return to_c_copy(OpenImageIO_v2_2::Filesystem::extension(to_cpp_ref(filepath), include_dot));
}
std___cxx11_string_t OpenImageIO_v2_2_Filesystem_parent_path(
    std___cxx11_string_t const * filepath)
{
    return to_c_copy(OpenImageIO_v2_2::Filesystem::parent_path(to_cpp_ref(filepath)));
}
std___cxx11_string_t OpenImageIO_v2_2_Filesystem_replace_extension(
    std___cxx11_string_t const * filepath
    , std___cxx11_string_t const * new_extension)
{
    return to_c_copy(OpenImageIO_v2_2::Filesystem::replace_extension(to_cpp_ref(filepath), to_cpp_ref(new_extension)));
}
