
typedef struct {
    char data[704];
    char data[704];
} __attribute__((aligned(64))) OpenImageIO_v2_2_Filesystem_IOProxy;
typedef struct {
    char data[832];
    char data[832];
} __attribute__((aligned(64))) OpenImageIO_v2_2_Filesystem_IOMemReader;


void OpenImageIO_v2_2_Filesystem_IOProxy_~IOProxy(
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










void OpenImageIO_v2_2_Filesystem_IOMemReader_IOMemReader(
    OpenImageIO_v2_2_Filesystem_IOMemReader * self
    , void * buf
    , unsigned long size);


char * OpenImageIO_v2_2_Filesystem_IOMemReader_proxytype(
    OpenImageIO_v2_2_Filesystem_IOMemReader const * self);


_Bool OpenImageIO_v2_2_Filesystem_IOMemReader_seek(
    OpenImageIO_v2_2_Filesystem_IOMemReader * self
    , long offset);


unsigned long OpenImageIO_v2_2_Filesystem_IOMemReader_read(
    OpenImageIO_v2_2_Filesystem_IOMemReader * self
    , void * buf
    , unsigned long size);


unsigned long OpenImageIO_v2_2_Filesystem_IOMemReader_pread(
    OpenImageIO_v2_2_Filesystem_IOMemReader * self
    , void * buf
    , unsigned long size
    , long offset);


void OpenImageIO_v2_2_Filesystem_IOMemReader_~IOMemReader(
    OpenImageIO_v2_2_Filesystem_IOMemReader * self);








