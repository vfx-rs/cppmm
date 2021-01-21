#pragma once

#include "cppmm_containers.h"


#ifdef __cplusplus
extern "C" {
#else
#include <stdbool.h>
#endif

#if defined(_WIN32) || defined(__CYGWIN__)
#define CPPMM_ALIGN(x) __declspec(align(x))
#else
#define CPPMM_ALIGN(x) __attribute__((aligned(x)))
#endif

typedef struct OpenImageIO_v2_2_Filesystem_IOMemReader OpenImageIO_v2_2_Filesystem_IOMemReader;

typedef struct OpenImageIO_v2_2_Filesystem_IOProxy OpenImageIO_v2_2_Filesystem_IOProxy;

enum OpenImageIO_v2_2_Filesystem_IOProxy_Mode {
    OIIO_Filesystem_IOProxy_Mode_Closed = 0,
    OIIO_Filesystem_IOProxy_Mode_Read = 114,
    OIIO_Filesystem_IOProxy_Mode_Write = 119,
};


/// Replace the file extension of a filename or filepath. Does not alter
/// filepath, just returns a new string.  Note that the new_extension
/// should contain a leading '.' dot.
int OpenImageIO_v2_2_Filesystem_replace_extension(const char* filepath, const char* new_extension, char* _result_buffer_ptr, int _result_buffer_len);

/// Return all but the last part of the path, for example,
/// parent_path("foo/bar") returns "foo", and parent_path("foo")
/// returns "".
int OpenImageIO_v2_2_Filesystem_parent_path(const char* filepath, char* _result_buffer_ptr, int _result_buffer_len);

/// Return the filename (excluding any directories, but including the
/// file extension, if any) of a filepath.
int OpenImageIO_v2_2_Filesystem_filename(const char* filepath, char* _result_buffer_ptr, int _result_buffer_len);

/// Return the file extension (including the last '.' if
/// include_dot=true) of a filename or filepath.
int OpenImageIO_v2_2_Filesystem_extension(const char* filepath, bool include_dot, char* _result_buffer_ptr, int _result_buffer_len);


void OpenImageIO_v2_2_Filesystem_IOMemReader_delete(OpenImageIO_v2_2_Filesystem_IOMemReader* self);


unsigned long OpenImageIO_v2_2_Filesystem_IOMemReader_pread(OpenImageIO_v2_2_Filesystem_IOMemReader* self, void* buf, unsigned long size, long offset);


unsigned long OpenImageIO_v2_2_Filesystem_IOMemReader_read(OpenImageIO_v2_2_Filesystem_IOMemReader* self, void* buf, unsigned long size);


OpenImageIO_v2_2_Filesystem_IOMemReader* OpenImageIO_v2_2_Filesystem_IOMemReader_new(void* buf, unsigned long size);


bool OpenImageIO_v2_2_Filesystem_IOMemReader_seek(OpenImageIO_v2_2_Filesystem_IOMemReader* self, long offset);


const char* OpenImageIO_v2_2_Filesystem_IOMemReader_proxytype(const OpenImageIO_v2_2_Filesystem_IOMemReader* self);


const char* OpenImageIO_v2_2_Filesystem_IOProxy_filename(const OpenImageIO_v2_2_Filesystem_IOProxy* self);


unsigned long OpenImageIO_v2_2_Filesystem_IOProxy_pwrite(OpenImageIO_v2_2_Filesystem_IOProxy* self, const void* buf, unsigned long size, long offset);


unsigned long OpenImageIO_v2_2_Filesystem_IOProxy_pread(OpenImageIO_v2_2_Filesystem_IOProxy* self, void* buf, unsigned long size, long offset);


unsigned long OpenImageIO_v2_2_Filesystem_IOProxy_read(OpenImageIO_v2_2_Filesystem_IOProxy* self, void* buf, unsigned long size);


const char* OpenImageIO_v2_2_Filesystem_IOProxy_proxytype(const OpenImageIO_v2_2_Filesystem_IOProxy* self);


unsigned long OpenImageIO_v2_2_Filesystem_IOProxy_write(OpenImageIO_v2_2_Filesystem_IOProxy* self, const void* buf, unsigned long size);


bool OpenImageIO_v2_2_Filesystem_IOProxy_seek(OpenImageIO_v2_2_Filesystem_IOProxy* self, long offset);


void OpenImageIO_v2_2_Filesystem_IOProxy_delete(OpenImageIO_v2_2_Filesystem_IOProxy* self);


void OpenImageIO_v2_2_Filesystem_IOProxy_close(OpenImageIO_v2_2_Filesystem_IOProxy* self);


bool OpenImageIO_v2_2_Filesystem_IOProxy_opened(const OpenImageIO_v2_2_Filesystem_IOProxy* self);


long OpenImageIO_v2_2_Filesystem_IOProxy_tell(OpenImageIO_v2_2_Filesystem_IOProxy* self);


#undef CPPMM_ALIGN

#define OIIO_Filesystem_IOMemReader OpenImageIO_v2_2_Filesystem_IOMemReader
#define OIIO_Filesystem_IOProxy OpenImageIO_v2_2_Filesystem_IOProxy
#define OIIO_Filesystem_IOProxy_Mode OpenImageIO_v2_2_Filesystem_IOProxy_Mode
#define OIIO_Filesystem_replace_extension OpenImageIO_v2_2_Filesystem_replace_extension
#define OIIO_Filesystem_parent_path OpenImageIO_v2_2_Filesystem_parent_path
#define OIIO_Filesystem_filename OpenImageIO_v2_2_Filesystem_filename
#define OIIO_Filesystem_extension OpenImageIO_v2_2_Filesystem_extension
#define OIIO_Filesystem_IOMemReader_delete OpenImageIO_v2_2_Filesystem_IOMemReader_delete
#define OIIO_Filesystem_IOMemReader_pread OpenImageIO_v2_2_Filesystem_IOMemReader_pread
#define OIIO_Filesystem_IOMemReader_read OpenImageIO_v2_2_Filesystem_IOMemReader_read
#define OIIO_Filesystem_IOMemReader_new OpenImageIO_v2_2_Filesystem_IOMemReader_new
#define OIIO_Filesystem_IOMemReader_seek OpenImageIO_v2_2_Filesystem_IOMemReader_seek
#define OIIO_Filesystem_IOMemReader_proxytype OpenImageIO_v2_2_Filesystem_IOMemReader_proxytype
#define OIIO_Filesystem_IOProxy_filename OpenImageIO_v2_2_Filesystem_IOProxy_filename
#define OIIO_Filesystem_IOProxy_pwrite OpenImageIO_v2_2_Filesystem_IOProxy_pwrite
#define OIIO_Filesystem_IOProxy_pread OpenImageIO_v2_2_Filesystem_IOProxy_pread
#define OIIO_Filesystem_IOProxy_read OpenImageIO_v2_2_Filesystem_IOProxy_read
#define OIIO_Filesystem_IOProxy_proxytype OpenImageIO_v2_2_Filesystem_IOProxy_proxytype
#define OIIO_Filesystem_IOProxy_write OpenImageIO_v2_2_Filesystem_IOProxy_write
#define OIIO_Filesystem_IOProxy_seek OpenImageIO_v2_2_Filesystem_IOProxy_seek
#define OIIO_Filesystem_IOProxy_delete OpenImageIO_v2_2_Filesystem_IOProxy_delete
#define OIIO_Filesystem_IOProxy_close OpenImageIO_v2_2_Filesystem_IOProxy_close
#define OIIO_Filesystem_IOProxy_opened OpenImageIO_v2_2_Filesystem_IOProxy_opened
#define OIIO_Filesystem_IOProxy_tell OpenImageIO_v2_2_Filesystem_IOProxy_tell

#ifdef __cplusplus
}
#endif
    