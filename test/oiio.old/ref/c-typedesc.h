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

typedef struct {
    unsigned char basetype;
    unsigned char aggregate;
    unsigned char vecsemantics;
    unsigned char reserved;
    int arraylen;
} OpenImageIO_v2_2_TypeDesc;


typedef struct { char _private[24]; } OpenImageIO_v2_2_TypeDesc_vector CPPMM_ALIGN(8);

void OpenImageIO_v2_2_TypeDesc_vector_ctor(OpenImageIO_v2_2_TypeDesc_vector* vec);
void OpenImageIO_v2_2_TypeDesc_vector_dtor(const OpenImageIO_v2_2_TypeDesc_vector* vec);
int OpenImageIO_v2_2_TypeDesc_vector_size(const OpenImageIO_v2_2_TypeDesc_vector* vec);
OpenImageIO_v2_2_TypeDesc* OpenImageIO_v2_2_TypeDesc_vector_data(OpenImageIO_v2_2_TypeDesc_vector* vec);

void OpenImageIO_v2_2_TypeDesc_vector_get(const OpenImageIO_v2_2_TypeDesc_vector* vec, int index, OpenImageIO_v2_2_TypeDesc* element);
void OpenImageIO_v2_2_TypeDesc_vector_set(OpenImageIO_v2_2_TypeDesc_vector* vec, int index, OpenImageIO_v2_2_TypeDesc* element);
enum OpenImageIO_v2_2_TypeDesc_VECSEMANTICS {
    OIIO_TypeDesc_VECSEMANTICS_NOXFORM = 0,
    OIIO_TypeDesc_VECSEMANTICS_NOSEMANTICS = 0,
    OIIO_TypeDesc_VECSEMANTICS_COLOR = 1,
    OIIO_TypeDesc_VECSEMANTICS_POINT = 2,
    OIIO_TypeDesc_VECSEMANTICS_VECTOR = 3,
    OIIO_TypeDesc_VECSEMANTICS_NORMAL = 4,
    OIIO_TypeDesc_VECSEMANTICS_TIMECODE = 5,
    OIIO_TypeDesc_VECSEMANTICS_KEYCODE = 6,
    OIIO_TypeDesc_VECSEMANTICS_RATIONAL = 7,
};

enum OpenImageIO_v2_2_TypeDesc_BASETYPE {
    OIIO_TypeDesc_BASETYPE_UNKNOWN = 0,
    OIIO_TypeDesc_BASETYPE_NONE = 1,
    OIIO_TypeDesc_BASETYPE_UINT8 = 2,
    OIIO_TypeDesc_BASETYPE_UCHAR = 2,
    OIIO_TypeDesc_BASETYPE_INT8 = 3,
    OIIO_TypeDesc_BASETYPE_CHAR = 3,
    OIIO_TypeDesc_BASETYPE_UINT16 = 4,
    OIIO_TypeDesc_BASETYPE_USHORT = 4,
    OIIO_TypeDesc_BASETYPE_INT16 = 5,
    OIIO_TypeDesc_BASETYPE_SHORT = 5,
    OIIO_TypeDesc_BASETYPE_UINT32 = 6,
    OIIO_TypeDesc_BASETYPE_UINT = 6,
    OIIO_TypeDesc_BASETYPE_INT32 = 7,
    OIIO_TypeDesc_BASETYPE_INT = 7,
    OIIO_TypeDesc_BASETYPE_UINT64 = 8,
    OIIO_TypeDesc_BASETYPE_ULONGLONG = 8,
    OIIO_TypeDesc_BASETYPE_INT64 = 9,
    OIIO_TypeDesc_BASETYPE_LONGLONG = 9,
    OIIO_TypeDesc_BASETYPE_HALF = 10,
    OIIO_TypeDesc_BASETYPE_FLOAT = 11,
    OIIO_TypeDesc_BASETYPE_DOUBLE = 12,
    OIIO_TypeDesc_BASETYPE_STRING = 13,
    OIIO_TypeDesc_BASETYPE_PTR = 14,
    OIIO_TypeDesc_BASETYPE_LASTBASE = 15,
};

enum OpenImageIO_v2_2_TypeDesc_AGGREGATE {
    OIIO_TypeDesc_AGGREGATE_SCALAR = 1,
    OIIO_TypeDesc_AGGREGATE_VEC2 = 2,
    OIIO_TypeDesc_AGGREGATE_VEC3 = 3,
    OIIO_TypeDesc_AGGREGATE_VEC4 = 4,
    OIIO_TypeDesc_AGGREGATE_MATRIX33 = 9,
    OIIO_TypeDesc_AGGREGATE_MATRIX44 = 16,
};



#undef CPPMM_ALIGN

#define OIIO_TypeDesc OpenImageIO_v2_2_TypeDesc
#define OIIO_TypeDesc_VECSEMANTICS OpenImageIO_v2_2_TypeDesc_VECSEMANTICS
#define OIIO_TypeDesc_BASETYPE OpenImageIO_v2_2_TypeDesc_BASETYPE
#define OIIO_TypeDesc_AGGREGATE OpenImageIO_v2_2_TypeDesc_AGGREGATE

#ifdef __cplusplus
}
#endif
    