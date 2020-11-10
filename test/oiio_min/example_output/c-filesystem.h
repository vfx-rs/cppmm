#pragma once



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

typedef struct OIIO_Filesystem_IOMemReader OIIO_Filesystem_IOMemReader;

typedef struct OIIO_Filesystem_IOProxy OIIO_Filesystem_IOProxy;

enum OIIO_Filesystem_IOProxy_Mode {
    OIIO_Filesystem_IOProxy_Mode_Closed = 0,
    OIIO_Filesystem_IOProxy_Mode_Read = 114,
    OIIO_Filesystem_IOProxy_Mode_Write = 119,
};


/// Replace the file extension of a filename or filepath. Does not alter
/// filepath, just returns a new string.  Note that the new_extension
/// should contain a leading '.' dot.
int OIIO_Filesystem_replace_extension(const char* filepath, const char* new_extension, char* _result_buffer_ptr, int _result_buffer_len);

/// Return all but the last part of the path, for example,
/// parent_path("foo/bar") returns "foo", and parent_path("foo")
/// returns "".
int OIIO_Filesystem_parent_path(const char* filepath, char* _result_buffer_ptr, int _result_buffer_len);

/// Return the filename (excluding any directories, but including the
/// file extension, if any) of a filepath.
int OIIO_Filesystem_filename(const char* filepath, char* _result_buffer_ptr, int _result_buffer_len);

/// Return the file extension (including the last '.' if
/// include_dot=true) of a filename or filepath.
int OIIO_Filesystem_extension(const char* filepath, bool include_dot, char* _result_buffer_ptr, int _result_buffer_len);


void  OIIO_Filesystem_IOMemReader_delete(OIIO_Filesystem_IOMemReader* self);


unsigned long  OIIO_Filesystem_IOMemReader_pread(OIIO_Filesystem_IOMemReader* self, void* buf, unsigned long size, long offset);


unsigned long  OIIO_Filesystem_IOMemReader_read(OIIO_Filesystem_IOMemReader* self, void* buf, unsigned long size);


OIIO_Filesystem_IOMemReader* OIIO_Filesystem_IOMemReader_new(void* buf, unsigned long size);


bool  OIIO_Filesystem_IOMemReader_seek(OIIO_Filesystem_IOMemReader* self, long offset);


const char*  OIIO_Filesystem_IOMemReader_proxytype(const OIIO_Filesystem_IOMemReader* self);


const char*  OIIO_Filesystem_IOProxy_filename(const OIIO_Filesystem_IOProxy* self);


unsigned long  OIIO_Filesystem_IOProxy_pwrite(OIIO_Filesystem_IOProxy* self, const void* buf, unsigned long size, long offset);


unsigned long  OIIO_Filesystem_IOProxy_pread(OIIO_Filesystem_IOProxy* self, void* buf, unsigned long size, long offset);


unsigned long  OIIO_Filesystem_IOProxy_read(OIIO_Filesystem_IOProxy* self, void* buf, unsigned long size);


const char*  OIIO_Filesystem_IOProxy_proxytype(const OIIO_Filesystem_IOProxy* self);


unsigned long  OIIO_Filesystem_IOProxy_write(OIIO_Filesystem_IOProxy* self, const void* buf, unsigned long size);


bool  OIIO_Filesystem_IOProxy_seek(OIIO_Filesystem_IOProxy* self, long offset);


void  OIIO_Filesystem_IOProxy_delete(OIIO_Filesystem_IOProxy* self);


void  OIIO_Filesystem_IOProxy_close(OIIO_Filesystem_IOProxy* self);


bool  OIIO_Filesystem_IOProxy_opened(const OIIO_Filesystem_IOProxy* self);


long  OIIO_Filesystem_IOProxy_tell(OIIO_Filesystem_IOProxy* self);


#undef CPPMM_ALIGN

#ifdef __cplusplus
}
#endif
    