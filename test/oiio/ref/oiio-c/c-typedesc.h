#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/** BASETYPE is a simple enum describing the base data types that
correspond (mostly) to the C/C++ built-in types. */
enum OpenImageIO_v2_2__TypeDesc__BASETYPE_e {
    OIIO_TypeDesc_BASETYPE_UNKNOWN = 0,
    OIIO_TypeDesc_BASETYPE_NONE = 1,
    OIIO_TypeDesc_BASETYPE_UINT8 = 2,
    OIIO_TypeDesc_BASETYPE_UCHAR = 2,
    OIIO_TypeDesc_BASETYPE_CHAR = 3,
    OIIO_TypeDesc_BASETYPE_INT8 = 3,
    OIIO_TypeDesc_BASETYPE_USHORT = 4,
    OIIO_TypeDesc_BASETYPE_UINT16 = 4,
    OIIO_TypeDesc_BASETYPE_INT16 = 5,
    OIIO_TypeDesc_BASETYPE_SHORT = 5,
    OIIO_TypeDesc_BASETYPE_UINT = 6,
    OIIO_TypeDesc_BASETYPE_UINT32 = 6,
    OIIO_TypeDesc_BASETYPE_INT32 = 7,
    OIIO_TypeDesc_BASETYPE_INT = 7,
    OIIO_TypeDesc_BASETYPE_ULONGLONG = 8,
    OIIO_TypeDesc_BASETYPE_UINT64 = 8,
    OIIO_TypeDesc_BASETYPE_INT64 = 9,
    OIIO_TypeDesc_BASETYPE_LONGLONG = 9,
    OIIO_TypeDesc_BASETYPE_HALF = 10,
    OIIO_TypeDesc_BASETYPE_FLOAT = 11,
    OIIO_TypeDesc_BASETYPE_DOUBLE = 12,
    OIIO_TypeDesc_BASETYPE_STRING = 13,
    OIIO_TypeDesc_BASETYPE_PTR = 14,
    OIIO_TypeDesc_BASETYPE_LASTBASE = 15,
};
typedef unsigned int OIIO_TypeDesc_BASETYPE;
/** AGGREGATE describes whether our TypeDesc is a simple scalar of one
of the BASETYPE's, or one of several simple aggregates.

Note that aggregates and arrays are different. A `TypeDesc(FLOAT,3)`
is an array of three floats, a `TypeDesc(FLOAT,VEC3)` is a single
3-component vector comprised of floats, and `TypeDesc(FLOAT,3,VEC3)`
is an array of 3 vectors, each of which is comprised of 3 floats. */
enum OpenImageIO_v2_2__TypeDesc__AGGREGATE_e {
    OIIO_TypeDesc_AGGREGATE_SCALAR = 1,
    OIIO_TypeDesc_AGGREGATE_VEC2 = 2,
    OIIO_TypeDesc_AGGREGATE_VEC3 = 3,
    OIIO_TypeDesc_AGGREGATE_VEC4 = 4,
    OIIO_TypeDesc_AGGREGATE_MATRIX33 = 9,
    OIIO_TypeDesc_AGGREGATE_MATRIX44 = 16,
};
typedef unsigned int OIIO_TypeDesc_AGGREGATE;
/** VECSEMANTICS gives hints about what the data represent (for example,
if a spatial vector quantity should transform as a point, direction
vector, or surface normal). */
enum OpenImageIO_v2_2__TypeDesc__VECSEMANTICS_e {
    OIIO_TypeDesc_VECSEMANTICS_NOSEMANTICS = 0,
    OIIO_TypeDesc_VECSEMANTICS_NOXFORM = 0,
    OIIO_TypeDesc_VECSEMANTICS_COLOR = 1,
    OIIO_TypeDesc_VECSEMANTICS_POINT = 2,
    OIIO_TypeDesc_VECSEMANTICS_VECTOR = 3,
    OIIO_TypeDesc_VECSEMANTICS_NORMAL = 4,
    OIIO_TypeDesc_VECSEMANTICS_TIMECODE = 5,
    OIIO_TypeDesc_VECSEMANTICS_KEYCODE = 6,
    OIIO_TypeDesc_VECSEMANTICS_RATIONAL = 7,
};
typedef unsigned int OIIO_TypeDesc_VECSEMANTICS;

/** //////////////////////////////////////////////////////////////////////////
 A TypeDesc describes simple data types.

 It frequently comes up (in my experience, with renderers and image
 handling programs) that you want a way to describe data that is passed
 through APIs through blind pointers.  These are some simple classes
 that provide a simple type descriptor system.  This is not meant to
 be comprehensive -- for example, there is no provision for structs,
 unions, pointers, const, or 'nested' type definitions.  Just simple
 integer and floating point, *common* aggregates such as 3-points,
 and reasonably-lengthed arrays thereof.

////////////////////////////////////////////////////////////////////////// */
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
