#pragma once

#ifdef __cplusplus
extern "C" {
#endif

enum OpenImageIO_v2_2__TypeDesc__BASETYPE_e {
    OIIO_TypeDesc_BASETYPE_CHAR = 3,
    OIIO_TypeDesc_BASETYPE_DOUBLE = 12,
    OIIO_TypeDesc_BASETYPE_FLOAT = 11,
    OIIO_TypeDesc_BASETYPE_HALF = 10,
    OIIO_TypeDesc_BASETYPE_INT = 7,
    OIIO_TypeDesc_BASETYPE_INT16 = 5,
    OIIO_TypeDesc_BASETYPE_INT32 = 7,
    OIIO_TypeDesc_BASETYPE_INT64 = 9,
    OIIO_TypeDesc_BASETYPE_INT8 = 3,
    OIIO_TypeDesc_BASETYPE_LASTBASE = 15,
    OIIO_TypeDesc_BASETYPE_LONGLONG = 9,
    OIIO_TypeDesc_BASETYPE_NONE = 1,
    OIIO_TypeDesc_BASETYPE_PTR = 14,
    OIIO_TypeDesc_BASETYPE_SHORT = 5,
    OIIO_TypeDesc_BASETYPE_STRING = 13,
    OIIO_TypeDesc_BASETYPE_UCHAR = 2,
    OIIO_TypeDesc_BASETYPE_UINT = 6,
    OIIO_TypeDesc_BASETYPE_UINT16 = 4,
    OIIO_TypeDesc_BASETYPE_UINT32 = 6,
    OIIO_TypeDesc_BASETYPE_UINT64 = 8,
    OIIO_TypeDesc_BASETYPE_UINT8 = 2,
    OIIO_TypeDesc_BASETYPE_ULONGLONG = 8,
    OIIO_TypeDesc_BASETYPE_UNKNOWN = 0,
    OIIO_TypeDesc_BASETYPE_USHORT = 4,
};
typedef unsigned int OIIO_TypeDesc_BASETYPE;
enum OpenImageIO_v2_2__TypeDesc__AGGREGATE_e {
    OIIO_TypeDesc_AGGREGATE_MATRIX33 = 9,
    OIIO_TypeDesc_AGGREGATE_MATRIX44 = 16,
    OIIO_TypeDesc_AGGREGATE_SCALAR = 1,
    OIIO_TypeDesc_AGGREGATE_VEC2 = 2,
    OIIO_TypeDesc_AGGREGATE_VEC3 = 3,
    OIIO_TypeDesc_AGGREGATE_VEC4 = 4,
};
typedef unsigned int OIIO_TypeDesc_AGGREGATE;
enum OpenImageIO_v2_2__TypeDesc__VECSEMANTICS_e {
    OIIO_TypeDesc_VECSEMANTICS_COLOR = 1,
    OIIO_TypeDesc_VECSEMANTICS_KEYCODE = 6,
    OIIO_TypeDesc_VECSEMANTICS_NORMAL = 4,
    OIIO_TypeDesc_VECSEMANTICS_NOSEMANTICS = 0,
    OIIO_TypeDesc_VECSEMANTICS_NOXFORM = 0,
    OIIO_TypeDesc_VECSEMANTICS_POINT = 2,
    OIIO_TypeDesc_VECSEMANTICS_RATIONAL = 7,
    OIIO_TypeDesc_VECSEMANTICS_TIMECODE = 5,
    OIIO_TypeDesc_VECSEMANTICS_VECTOR = 3,
};
typedef unsigned int OIIO_TypeDesc_VECSEMANTICS;

typedef struct OpenImageIO_v2_2__TypeDesc_t_s {
    unsigned char basetype;
    unsigned char aggregate;
    unsigned char vecsemantics;
    unsigned char reserved;
    int arraylen;
} __attribute__((aligned(4))) OpenImageIO_v2_2__TypeDesc_t;
typedef OpenImageIO_v2_2__TypeDesc_t OIIO_TypeDesc_t;





































#ifdef __cplusplus
}
#endif
