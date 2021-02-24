
typedef struct OpenImageIO_v2_2_Filesystem_IOProxy_s {
    char data[88];
} __attribute__((aligned(8))) OpenImageIO_v2_2_Filesystem_IOProxy;
typedef struct OpenImageIO_v2_2_Filesystem_IOMemReader_s {
    char data[104];
} __attribute__((aligned(8))) OpenImageIO_v2_2_Filesystem_IOMemReader;


void OpenImageIO_v2_2_Filesystem_IOProxy_delete(
    OpenImageIO_v2_2_Filesystem_IOProxy * self);


char * OpenImageIO_v2_2_Filesystem_IOProxy_proxytype(
    OpenImageIO_v2_2_Filesystem_IOProxy const * self);


void OpenImageIO_v2_2_Filesystem_IOProxy_close(
    OpenImageIO_v2_2_Filesystem_IOProxy * self);


_Bool OpenImageIO_v2_2_Filesystem_IOProxy_opened(
    OpenImageIO_v2_2_Filesystem_IOProxy const * self);


long OpenImageIO_v2_2_Filesystem_IOProxy_tell(
    OpenImageIO_v2_2_Filesystem_IOProxy * self);


_Bool OpenImageIO_v2_2_Filesystem_IOProxy_seek(
    OpenImageIO_v2_2_Filesystem_IOProxy * self
    , long offset);


unsigned long OpenImageIO_v2_2_Filesystem_IOProxy_read(
    OpenImageIO_v2_2_Filesystem_IOProxy * self
    , void * buf
    , unsigned long size);


unsigned long OpenImageIO_v2_2_Filesystem_IOProxy_write(
    OpenImageIO_v2_2_Filesystem_IOProxy * self
    , void * buf
    , unsigned long size);


unsigned long OpenImageIO_v2_2_Filesystem_IOProxy_pread(
    OpenImageIO_v2_2_Filesystem_IOProxy * self
    , void * buf
    , unsigned long size
    , long offset);


unsigned long OpenImageIO_v2_2_Filesystem_IOProxy_pwrite(
    OpenImageIO_v2_2_Filesystem_IOProxy * self
    , void * buf
    , unsigned long size
    , long offset);


_Bool OpenImageIO_v2_2_Filesystem_IOProxy_seek(
    OpenImageIO_v2_2_Filesystem_IOProxy * self
    , long offset
    , int origin);










char * OpenImageIO_v2_2_Filesystem_IOMemReader_proxytype(
    OpenImageIO_v2_2_Filesystem_IOMemReader const * self);


void OpenImageIO_v2_2_Filesystem_IOMemReader_close(
    OpenImageIO_v2_2_Filesystem_IOMemReader * self);


_Bool OpenImageIO_v2_2_Filesystem_IOMemReader_opened(
    OpenImageIO_v2_2_Filesystem_IOMemReader const * self);


long OpenImageIO_v2_2_Filesystem_IOMemReader_tell(
    OpenImageIO_v2_2_Filesystem_IOMemReader * self);


_Bool OpenImageIO_v2_2_Filesystem_IOMemReader_seek(
    OpenImageIO_v2_2_Filesystem_IOMemReader * self
    , long offset);


unsigned long OpenImageIO_v2_2_Filesystem_IOMemReader_read(
    OpenImageIO_v2_2_Filesystem_IOMemReader * self
    , void * buf
    , unsigned long size);


unsigned long OpenImageIO_v2_2_Filesystem_IOMemReader_write(
    OpenImageIO_v2_2_Filesystem_IOMemReader * self
    , void * buf
    , unsigned long size);


unsigned long OpenImageIO_v2_2_Filesystem_IOMemReader_pread(
    OpenImageIO_v2_2_Filesystem_IOMemReader * self
    , void * buf
    , unsigned long size
    , long offset);


unsigned long OpenImageIO_v2_2_Filesystem_IOMemReader_pwrite(
    OpenImageIO_v2_2_Filesystem_IOMemReader * self
    , void * buf
    , unsigned long size
    , long offset);


_Bool OpenImageIO_v2_2_Filesystem_IOMemReader_seek(
    OpenImageIO_v2_2_Filesystem_IOMemReader * self
    , long offset
    , int origin);


void OpenImageIO_v2_2_Filesystem_IOMemReader_new(
    OpenImageIO_v2_2_Filesystem_IOMemReader * self
    , void * buf
    , unsigned long size);


void OpenImageIO_v2_2_Filesystem_IOMemReader_delete(
    OpenImageIO_v2_2_Filesystem_IOMemReader * self);








