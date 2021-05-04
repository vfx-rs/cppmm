#include <c-filesystem_private.h>

#include <new>
#include <std_string_private.h>

unsigned int OpenImageIO_v2_2__Filesystem__IOProxy_delete(
    OIIO_Filesystem_IOProxy_t * this_)
{
    try {
        delete to_cpp(this_);
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2__Filesystem__IOProxy_proxytype(
    OIIO_Filesystem_IOProxy_t const * this_
    , char const * * return_)
{
    try {
        *(return_) = (to_cpp(this_)) -> proxytype();
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2__Filesystem__IOProxy_close(
    OIIO_Filesystem_IOProxy_t * this_)
{
    try {
        (to_cpp(this_)) -> close();
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2__Filesystem__IOProxy_opened(
    OIIO_Filesystem_IOProxy_t const * this_
    , _Bool * return_)
{
    try {
        *(return_) = (to_cpp(this_)) -> opened();
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2__Filesystem__IOProxy_tell(
    OIIO_Filesystem_IOProxy_t * this_
    , long * return_)
{
    try {
        *(return_) = (to_cpp(this_)) -> tell();
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2__Filesystem__IOProxy_seek(
    OIIO_Filesystem_IOProxy_t * this_
    , _Bool * return_
    , long offset)
{
    try {
        *(return_) = (to_cpp(this_)) -> seek(offset);
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2__Filesystem__IOProxy_read(
    OIIO_Filesystem_IOProxy_t * this_
    , unsigned long * return_
    , void * buf
    , unsigned long size)
{
    try {
        *(return_) = (to_cpp(this_)) -> read(buf, size);
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2__Filesystem__IOProxy_write(
    OIIO_Filesystem_IOProxy_t * this_
    , unsigned long * return_
    , void const * buf
    , unsigned long size)
{
    try {
        *(return_) = (to_cpp(this_)) -> write(buf, size);
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2__Filesystem__IOProxy_pread(
    OIIO_Filesystem_IOProxy_t * this_
    , unsigned long * return_
    , void * buf
    , unsigned long size
    , long offset)
{
    try {
        *(return_) = (to_cpp(this_)) -> pread(buf, size, offset);
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2__Filesystem__IOProxy_pwrite(
    OIIO_Filesystem_IOProxy_t * this_
    , unsigned long * return_
    , void const * buf
    , unsigned long size
    , long offset)
{
    try {
        *(return_) = (to_cpp(this_)) -> pwrite(buf, size, offset);
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2__Filesystem__IOProxy_filename(
    OIIO_Filesystem_IOProxy_t const * this_
    , std___cxx11_string_t const * * return_)
{
    try {
        to_c(return_, (to_cpp(this_)) -> filename());
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2__Filesystem__IOProxy_seek_1(
    OIIO_Filesystem_IOProxy_t * this_
    , _Bool * return_
    , long offset
    , int origin)
{
    try {
        *(return_) = (to_cpp(this_)) -> seek(offset, origin);
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2__Filesystem__IOMemReader_proxytype(
    OIIO_Filesystem_IOMemReader_t const * this_
    , char const * * return_)
{
    try {
        *(return_) = (to_cpp(this_)) -> proxytype();
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2__Filesystem__IOMemReader_close(
    OIIO_Filesystem_IOMemReader_t * this_)
{
    try {
        (to_cpp(this_)) -> close();
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2__Filesystem__IOMemReader_opened(
    OIIO_Filesystem_IOMemReader_t const * this_
    , _Bool * return_)
{
    try {
        *(return_) = (to_cpp(this_)) -> opened();
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2__Filesystem__IOMemReader_tell(
    OIIO_Filesystem_IOMemReader_t * this_
    , long * return_)
{
    try {
        *(return_) = (to_cpp(this_)) -> tell();
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2__Filesystem__IOMemReader_seek(
    OIIO_Filesystem_IOMemReader_t * this_
    , _Bool * return_
    , long offset)
{
    try {
        *(return_) = (to_cpp(this_)) -> seek(offset);
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2__Filesystem__IOMemReader_read(
    OIIO_Filesystem_IOMemReader_t * this_
    , unsigned long * return_
    , void * buf
    , unsigned long size)
{
    try {
        *(return_) = (to_cpp(this_)) -> read(buf, size);
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2__Filesystem__IOMemReader_write(
    OIIO_Filesystem_IOMemReader_t * this_
    , unsigned long * return_
    , void const * buf
    , unsigned long size)
{
    try {
        *(return_) = (to_cpp(this_)) -> write(buf, size);
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2__Filesystem__IOMemReader_pread(
    OIIO_Filesystem_IOMemReader_t * this_
    , unsigned long * return_
    , void * buf
    , unsigned long size
    , long offset)
{
    try {
        *(return_) = (to_cpp(this_)) -> pread(buf, size, offset);
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2__Filesystem__IOMemReader_pwrite(
    OIIO_Filesystem_IOMemReader_t * this_
    , unsigned long * return_
    , void const * buf
    , unsigned long size
    , long offset)
{
    try {
        *(return_) = (to_cpp(this_)) -> pwrite(buf, size, offset);
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2__Filesystem__IOMemReader_seek_1(
    OIIO_Filesystem_IOMemReader_t * this_
    , _Bool * return_
    , long offset
    , int origin)
{
    try {
        *(return_) = (to_cpp(this_)) -> seek(offset, origin);
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2__Filesystem__IOMemReader_new(
    OIIO_Filesystem_IOMemReader_t * * this_
    , void * buf
    , unsigned long size)
{
    try {
        to_c(this_, new OpenImageIO_v2_2::Filesystem::IOMemReader(buf, size));
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2__Filesystem__IOMemReader_delete(
    OIIO_Filesystem_IOMemReader_t * this_)
{
    try {
        delete to_cpp(this_);
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2_Filesystem_filename(
    std___cxx11_string_t * * return_
    , std___cxx11_string_t const * filepath)
{
    try {
        to_c_copy(return_, OpenImageIO_v2_2::Filesystem::filename(to_cpp_ref(filepath)));
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2_Filesystem_extension(
    std___cxx11_string_t * * return_
    , std___cxx11_string_t const * filepath
    , _Bool include_dot)
{
    try {
        to_c_copy(return_, OpenImageIO_v2_2::Filesystem::extension(to_cpp_ref(filepath), include_dot));
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2_Filesystem_parent_path(
    std___cxx11_string_t * * return_
    , std___cxx11_string_t const * filepath)
{
    try {
        to_c_copy(return_, OpenImageIO_v2_2::Filesystem::parent_path(to_cpp_ref(filepath)));
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2_Filesystem_replace_extension(
    std___cxx11_string_t * * return_
    , std___cxx11_string_t const * filepath
    , std___cxx11_string_t const * new_extension)
{
    try {
        to_c_copy(return_, OpenImageIO_v2_2::Filesystem::replace_extension(to_cpp_ref(filepath), to_cpp_ref(new_extension)));
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
