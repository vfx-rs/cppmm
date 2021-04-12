#pragma once
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

enum OpenImageIO_v2_2__Filesystem__IOProxy__Mode_e {
    OIIO_Filesystem_IOProxy_Mode_Closed = 0,
    OIIO_Filesystem_IOProxy_Mode_Read = 114,
    OIIO_Filesystem_IOProxy_Mode_Write = 119,
};
typedef unsigned int OIIO_Filesystem_IOProxy_Mode;

typedef struct OpenImageIO_v2_2__Filesystem__IOProxy_t_s {
    char data[88];
} __attribute__((aligned(8))) OpenImageIO_v2_2__Filesystem__IOProxy_t;
typedef OpenImageIO_v2_2__Filesystem__IOProxy_t OIIO_Filesystem_IOProxy_t;

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









#ifdef __cplusplus
}
#endif
