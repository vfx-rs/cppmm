#pragma once
#include <std_string.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct std____cxx11__basic_string_char__t_s std____cxx11__basic_string_char__t;
typedef std____cxx11__basic_string_char__t std___cxx11_string_t;

enum OpenImageIO_v2_2__Filesystem__IOProxy__Mode_e {
    OIIO_Filesystem_IOProxy_Mode_Closed = 0,
    OIIO_Filesystem_IOProxy_Mode_Read = 114,
    OIIO_Filesystem_IOProxy_Mode_Write = 119,
};
typedef unsigned int OIIO_Filesystem_IOProxy_Mode;

/** Proxy class for I/O. This provides a simplified interface for file I/O
that can have custom overrides. */
typedef struct OpenImageIO_v2_2__Filesystem__IOProxy_t_s {
    char data[88];
} __attribute__((aligned(8))) OpenImageIO_v2_2__Filesystem__IOProxy_t;
typedef OpenImageIO_v2_2__Filesystem__IOProxy_t OIIO_Filesystem_IOProxy_t;

/** IOProxy subclass for reading that wraps an cspan<char>. */
typedef struct OpenImageIO_v2_2__Filesystem__IOMemReader_t_s {
    char data[104];
} __attribute__((aligned(8))) OpenImageIO_v2_2__Filesystem__IOMemReader_t;
typedef OpenImageIO_v2_2__Filesystem__IOMemReader_t OIIO_Filesystem_IOMemReader_t;












void OpenImageIO_v2_2__Filesystem__IOProxy_delete(
    OIIO_Filesystem_IOProxy_t * this_);
#define OIIO_Filesystem_IOProxy_delete OpenImageIO_v2_2__Filesystem__IOProxy_delete


char const * OpenImageIO_v2_2__Filesystem__IOProxy_proxytype(
    OIIO_Filesystem_IOProxy_t const * this_);
#define OIIO_Filesystem_IOProxy_proxytype OpenImageIO_v2_2__Filesystem__IOProxy_proxytype


void OpenImageIO_v2_2__Filesystem__IOProxy_close(
    OIIO_Filesystem_IOProxy_t * this_);
#define OIIO_Filesystem_IOProxy_close OpenImageIO_v2_2__Filesystem__IOProxy_close


_Bool OpenImageIO_v2_2__Filesystem__IOProxy_opened(
    OIIO_Filesystem_IOProxy_t const * this_);
#define OIIO_Filesystem_IOProxy_opened OpenImageIO_v2_2__Filesystem__IOProxy_opened


long OpenImageIO_v2_2__Filesystem__IOProxy_tell(
    OIIO_Filesystem_IOProxy_t * this_);
#define OIIO_Filesystem_IOProxy_tell OpenImageIO_v2_2__Filesystem__IOProxy_tell


_Bool OpenImageIO_v2_2__Filesystem__IOProxy_seek(
    OIIO_Filesystem_IOProxy_t * this_
    , long offset);
#define OIIO_Filesystem_IOProxy_seek OpenImageIO_v2_2__Filesystem__IOProxy_seek


unsigned long OpenImageIO_v2_2__Filesystem__IOProxy_read(
    OIIO_Filesystem_IOProxy_t * this_
    , void * buf
    , unsigned long size);
#define OIIO_Filesystem_IOProxy_read OpenImageIO_v2_2__Filesystem__IOProxy_read


unsigned long OpenImageIO_v2_2__Filesystem__IOProxy_write(
    OIIO_Filesystem_IOProxy_t * this_
    , void const * buf
    , unsigned long size);
#define OIIO_Filesystem_IOProxy_write OpenImageIO_v2_2__Filesystem__IOProxy_write


unsigned long OpenImageIO_v2_2__Filesystem__IOProxy_pread(
    OIIO_Filesystem_IOProxy_t * this_
    , void * buf
    , unsigned long size
    , long offset);
#define OIIO_Filesystem_IOProxy_pread OpenImageIO_v2_2__Filesystem__IOProxy_pread


unsigned long OpenImageIO_v2_2__Filesystem__IOProxy_pwrite(
    OIIO_Filesystem_IOProxy_t * this_
    , void const * buf
    , unsigned long size
    , long offset);
#define OIIO_Filesystem_IOProxy_pwrite OpenImageIO_v2_2__Filesystem__IOProxy_pwrite


std___cxx11_string_t const * OpenImageIO_v2_2__Filesystem__IOProxy_filename(
    OIIO_Filesystem_IOProxy_t const * this_);
#define OIIO_Filesystem_IOProxy_filename OpenImageIO_v2_2__Filesystem__IOProxy_filename


_Bool OpenImageIO_v2_2__Filesystem__IOProxy_seek_1(
    OIIO_Filesystem_IOProxy_t * this_
    , long offset
    , int origin);
#define OIIO_Filesystem_IOProxy_seek_1 OpenImageIO_v2_2__Filesystem__IOProxy_seek_1










char const * OpenImageIO_v2_2__Filesystem__IOMemReader_proxytype(
    OIIO_Filesystem_IOMemReader_t const * this_);
#define OIIO_Filesystem_IOMemReader_proxytype OpenImageIO_v2_2__Filesystem__IOMemReader_proxytype


void OpenImageIO_v2_2__Filesystem__IOMemReader_close(
    OIIO_Filesystem_IOMemReader_t * this_);
#define OIIO_Filesystem_IOMemReader_close OpenImageIO_v2_2__Filesystem__IOMemReader_close


_Bool OpenImageIO_v2_2__Filesystem__IOMemReader_opened(
    OIIO_Filesystem_IOMemReader_t const * this_);
#define OIIO_Filesystem_IOMemReader_opened OpenImageIO_v2_2__Filesystem__IOMemReader_opened


long OpenImageIO_v2_2__Filesystem__IOMemReader_tell(
    OIIO_Filesystem_IOMemReader_t * this_);
#define OIIO_Filesystem_IOMemReader_tell OpenImageIO_v2_2__Filesystem__IOMemReader_tell


_Bool OpenImageIO_v2_2__Filesystem__IOMemReader_seek(
    OIIO_Filesystem_IOMemReader_t * this_
    , long offset);
#define OIIO_Filesystem_IOMemReader_seek OpenImageIO_v2_2__Filesystem__IOMemReader_seek


unsigned long OpenImageIO_v2_2__Filesystem__IOMemReader_read(
    OIIO_Filesystem_IOMemReader_t * this_
    , void * buf
    , unsigned long size);
#define OIIO_Filesystem_IOMemReader_read OpenImageIO_v2_2__Filesystem__IOMemReader_read


unsigned long OpenImageIO_v2_2__Filesystem__IOMemReader_write(
    OIIO_Filesystem_IOMemReader_t * this_
    , void const * buf
    , unsigned long size);
#define OIIO_Filesystem_IOMemReader_write OpenImageIO_v2_2__Filesystem__IOMemReader_write


unsigned long OpenImageIO_v2_2__Filesystem__IOMemReader_pread(
    OIIO_Filesystem_IOMemReader_t * this_
    , void * buf
    , unsigned long size
    , long offset);
#define OIIO_Filesystem_IOMemReader_pread OpenImageIO_v2_2__Filesystem__IOMemReader_pread


unsigned long OpenImageIO_v2_2__Filesystem__IOMemReader_pwrite(
    OIIO_Filesystem_IOMemReader_t * this_
    , void const * buf
    , unsigned long size
    , long offset);
#define OIIO_Filesystem_IOMemReader_pwrite OpenImageIO_v2_2__Filesystem__IOMemReader_pwrite


_Bool OpenImageIO_v2_2__Filesystem__IOMemReader_seek_1(
    OIIO_Filesystem_IOMemReader_t * this_
    , long offset
    , int origin);
#define OIIO_Filesystem_IOMemReader_seek_1 OpenImageIO_v2_2__Filesystem__IOMemReader_seek_1


void OpenImageIO_v2_2__Filesystem__IOMemReader_new(
    OIIO_Filesystem_IOMemReader_t * this_
    , void * buf
    , unsigned long size);
#define OIIO_Filesystem_IOMemReader_new OpenImageIO_v2_2__Filesystem__IOMemReader_new


void OpenImageIO_v2_2__Filesystem__IOMemReader_delete(
    OIIO_Filesystem_IOMemReader_t * this_);
#define OIIO_Filesystem_IOMemReader_delete OpenImageIO_v2_2__Filesystem__IOMemReader_delete










/** Return the filename (excluding any directories, but including the
file extension, if any) of a filepath. */
std___cxx11_string_t OpenImageIO_v2_2_Filesystem_filename(
    std___cxx11_string_t const * filepath);
#define OIIO_Filesystem_filename OpenImageIO_v2_2_Filesystem_filename


/** Return the file extension (including the last '.' if
include_dot=true) of a filename or filepath. */
std___cxx11_string_t OpenImageIO_v2_2_Filesystem_extension(
    std___cxx11_string_t const * filepath
    , _Bool include_dot);
#define OIIO_Filesystem_extension OpenImageIO_v2_2_Filesystem_extension


/** Return all but the last part of the path, for example,
parent_path("foo/bar") returns "foo", and parent_path("foo")
returns "". */
std___cxx11_string_t OpenImageIO_v2_2_Filesystem_parent_path(
    std___cxx11_string_t const * filepath);
#define OIIO_Filesystem_parent_path OpenImageIO_v2_2_Filesystem_parent_path


/** Replace the file extension of a filename or filepath. Does not alter
filepath, just returns a new string.  Note that the new_extension
should contain a leading '.' dot. */
std___cxx11_string_t OpenImageIO_v2_2_Filesystem_replace_extension(
    std___cxx11_string_t const * filepath
    , std___cxx11_string_t const * new_extension);
#define OIIO_Filesystem_replace_extension OpenImageIO_v2_2_Filesystem_replace_extension

#ifdef __cplusplus
}
#endif
