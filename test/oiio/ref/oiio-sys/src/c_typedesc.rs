#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]
#![allow(unused_imports)]
use crate::*;
use std::os::raw::*;

/// //////////////////////////////////////////////////////////////////////////
///  A TypeDesc describes simple data types.
/// 
///  It frequently comes up (in my experience, with renderers and image
///  handling programs) that you want a way to describe data that is passed
///  through APIs through blind pointers.  These are some simple classes
///  that provide a simple type descriptor system.  This is not meant to
///  be comprehensive -- for example, there is no provision for structs,
///  unions, pointers, const, or 'nested' type definitions.  Just simple
///  integer and floating point, *common* aggregates such as 3-points,
///  and reasonably-lengthed arrays thereof.
/// 
/// //////////////////////////////////////////////////////////////////////////
#[repr(C, align(4))]
#[derive(Clone)]
pub struct OpenImageIO_v2_2__TypeDesc_t {
    pub basetype: c_uchar,
    pub aggregate: c_uchar,
    pub vecsemantics: c_uchar,
    pub reserved: c_uchar,
    pub arraylen: c_int,
}


/// BASETYPE is a simple enum describing the base data types that
/// correspond (mostly) to the C/C++ built-in types.
#[repr(transparent)]
#[derive(Debug, Copy, Clone, PartialEq, Eq)]
pub struct OpenImageIO_v2_2__TypeDesc__BASETYPE_e(pub u32);
pub const OIIO_TypeDesc_BASETYPE_UNKNOWN: OpenImageIO_v2_2__TypeDesc__BASETYPE_e = OpenImageIO_v2_2__TypeDesc__BASETYPE_e(0);
pub const OIIO_TypeDesc_BASETYPE_NONE: OpenImageIO_v2_2__TypeDesc__BASETYPE_e = OpenImageIO_v2_2__TypeDesc__BASETYPE_e(1);
pub const OIIO_TypeDesc_BASETYPE_UINT8: OpenImageIO_v2_2__TypeDesc__BASETYPE_e = OpenImageIO_v2_2__TypeDesc__BASETYPE_e(2);
pub const OIIO_TypeDesc_BASETYPE_UCHAR: OpenImageIO_v2_2__TypeDesc__BASETYPE_e = OpenImageIO_v2_2__TypeDesc__BASETYPE_e(2);
pub const OIIO_TypeDesc_BASETYPE_CHAR: OpenImageIO_v2_2__TypeDesc__BASETYPE_e = OpenImageIO_v2_2__TypeDesc__BASETYPE_e(3);
pub const OIIO_TypeDesc_BASETYPE_INT8: OpenImageIO_v2_2__TypeDesc__BASETYPE_e = OpenImageIO_v2_2__TypeDesc__BASETYPE_e(3);
pub const OIIO_TypeDesc_BASETYPE_USHORT: OpenImageIO_v2_2__TypeDesc__BASETYPE_e = OpenImageIO_v2_2__TypeDesc__BASETYPE_e(4);
pub const OIIO_TypeDesc_BASETYPE_UINT16: OpenImageIO_v2_2__TypeDesc__BASETYPE_e = OpenImageIO_v2_2__TypeDesc__BASETYPE_e(4);
pub const OIIO_TypeDesc_BASETYPE_INT16: OpenImageIO_v2_2__TypeDesc__BASETYPE_e = OpenImageIO_v2_2__TypeDesc__BASETYPE_e(5);
pub const OIIO_TypeDesc_BASETYPE_SHORT: OpenImageIO_v2_2__TypeDesc__BASETYPE_e = OpenImageIO_v2_2__TypeDesc__BASETYPE_e(5);
pub const OIIO_TypeDesc_BASETYPE_UINT: OpenImageIO_v2_2__TypeDesc__BASETYPE_e = OpenImageIO_v2_2__TypeDesc__BASETYPE_e(6);
pub const OIIO_TypeDesc_BASETYPE_UINT32: OpenImageIO_v2_2__TypeDesc__BASETYPE_e = OpenImageIO_v2_2__TypeDesc__BASETYPE_e(6);
pub const OIIO_TypeDesc_BASETYPE_INT32: OpenImageIO_v2_2__TypeDesc__BASETYPE_e = OpenImageIO_v2_2__TypeDesc__BASETYPE_e(7);
pub const OIIO_TypeDesc_BASETYPE_INT: OpenImageIO_v2_2__TypeDesc__BASETYPE_e = OpenImageIO_v2_2__TypeDesc__BASETYPE_e(7);
pub const OIIO_TypeDesc_BASETYPE_ULONGLONG: OpenImageIO_v2_2__TypeDesc__BASETYPE_e = OpenImageIO_v2_2__TypeDesc__BASETYPE_e(8);
pub const OIIO_TypeDesc_BASETYPE_UINT64: OpenImageIO_v2_2__TypeDesc__BASETYPE_e = OpenImageIO_v2_2__TypeDesc__BASETYPE_e(8);
pub const OIIO_TypeDesc_BASETYPE_INT64: OpenImageIO_v2_2__TypeDesc__BASETYPE_e = OpenImageIO_v2_2__TypeDesc__BASETYPE_e(9);
pub const OIIO_TypeDesc_BASETYPE_LONGLONG: OpenImageIO_v2_2__TypeDesc__BASETYPE_e = OpenImageIO_v2_2__TypeDesc__BASETYPE_e(9);
pub const OIIO_TypeDesc_BASETYPE_HALF: OpenImageIO_v2_2__TypeDesc__BASETYPE_e = OpenImageIO_v2_2__TypeDesc__BASETYPE_e(10);
pub const OIIO_TypeDesc_BASETYPE_FLOAT: OpenImageIO_v2_2__TypeDesc__BASETYPE_e = OpenImageIO_v2_2__TypeDesc__BASETYPE_e(11);
pub const OIIO_TypeDesc_BASETYPE_DOUBLE: OpenImageIO_v2_2__TypeDesc__BASETYPE_e = OpenImageIO_v2_2__TypeDesc__BASETYPE_e(12);
pub const OIIO_TypeDesc_BASETYPE_STRING: OpenImageIO_v2_2__TypeDesc__BASETYPE_e = OpenImageIO_v2_2__TypeDesc__BASETYPE_e(13);
pub const OIIO_TypeDesc_BASETYPE_PTR: OpenImageIO_v2_2__TypeDesc__BASETYPE_e = OpenImageIO_v2_2__TypeDesc__BASETYPE_e(14);
pub const OIIO_TypeDesc_BASETYPE_LASTBASE: OpenImageIO_v2_2__TypeDesc__BASETYPE_e = OpenImageIO_v2_2__TypeDesc__BASETYPE_e(15);

/// AGGREGATE describes whether our TypeDesc is a simple scalar of one
/// of the BASETYPE's, or one of several simple aggregates.
/// 
/// Note that aggregates and arrays are different. A `TypeDesc(FLOAT,3)`
/// is an array of three floats, a `TypeDesc(FLOAT,VEC3)` is a single
/// 3-component vector comprised of floats, and `TypeDesc(FLOAT,3,VEC3)`
/// is an array of 3 vectors, each of which is comprised of 3 floats.
#[repr(transparent)]
#[derive(Debug, Copy, Clone, PartialEq, Eq)]
pub struct OpenImageIO_v2_2__TypeDesc__AGGREGATE_e(pub u32);
pub const OIIO_TypeDesc_AGGREGATE_SCALAR: OpenImageIO_v2_2__TypeDesc__AGGREGATE_e = OpenImageIO_v2_2__TypeDesc__AGGREGATE_e(1);
pub const OIIO_TypeDesc_AGGREGATE_VEC2: OpenImageIO_v2_2__TypeDesc__AGGREGATE_e = OpenImageIO_v2_2__TypeDesc__AGGREGATE_e(2);
pub const OIIO_TypeDesc_AGGREGATE_VEC3: OpenImageIO_v2_2__TypeDesc__AGGREGATE_e = OpenImageIO_v2_2__TypeDesc__AGGREGATE_e(3);
pub const OIIO_TypeDesc_AGGREGATE_VEC4: OpenImageIO_v2_2__TypeDesc__AGGREGATE_e = OpenImageIO_v2_2__TypeDesc__AGGREGATE_e(4);
pub const OIIO_TypeDesc_AGGREGATE_MATRIX33: OpenImageIO_v2_2__TypeDesc__AGGREGATE_e = OpenImageIO_v2_2__TypeDesc__AGGREGATE_e(9);
pub const OIIO_TypeDesc_AGGREGATE_MATRIX44: OpenImageIO_v2_2__TypeDesc__AGGREGATE_e = OpenImageIO_v2_2__TypeDesc__AGGREGATE_e(16);

/// VECSEMANTICS gives hints about what the data represent (for example,
/// if a spatial vector quantity should transform as a point, direction
/// vector, or surface normal).
#[repr(transparent)]
#[derive(Debug, Copy, Clone, PartialEq, Eq)]
pub struct OpenImageIO_v2_2__TypeDesc__VECSEMANTICS_e(pub u32);
pub const OIIO_TypeDesc_VECSEMANTICS_NOSEMANTICS: OpenImageIO_v2_2__TypeDesc__VECSEMANTICS_e = OpenImageIO_v2_2__TypeDesc__VECSEMANTICS_e(0);
pub const OIIO_TypeDesc_VECSEMANTICS_NOXFORM: OpenImageIO_v2_2__TypeDesc__VECSEMANTICS_e = OpenImageIO_v2_2__TypeDesc__VECSEMANTICS_e(0);
pub const OIIO_TypeDesc_VECSEMANTICS_COLOR: OpenImageIO_v2_2__TypeDesc__VECSEMANTICS_e = OpenImageIO_v2_2__TypeDesc__VECSEMANTICS_e(1);
pub const OIIO_TypeDesc_VECSEMANTICS_POINT: OpenImageIO_v2_2__TypeDesc__VECSEMANTICS_e = OpenImageIO_v2_2__TypeDesc__VECSEMANTICS_e(2);
pub const OIIO_TypeDesc_VECSEMANTICS_VECTOR: OpenImageIO_v2_2__TypeDesc__VECSEMANTICS_e = OpenImageIO_v2_2__TypeDesc__VECSEMANTICS_e(3);
pub const OIIO_TypeDesc_VECSEMANTICS_NORMAL: OpenImageIO_v2_2__TypeDesc__VECSEMANTICS_e = OpenImageIO_v2_2__TypeDesc__VECSEMANTICS_e(4);
pub const OIIO_TypeDesc_VECSEMANTICS_TIMECODE: OpenImageIO_v2_2__TypeDesc__VECSEMANTICS_e = OpenImageIO_v2_2__TypeDesc__VECSEMANTICS_e(5);
pub const OIIO_TypeDesc_VECSEMANTICS_KEYCODE: OpenImageIO_v2_2__TypeDesc__VECSEMANTICS_e = OpenImageIO_v2_2__TypeDesc__VECSEMANTICS_e(6);
pub const OIIO_TypeDesc_VECSEMANTICS_RATIONAL: OpenImageIO_v2_2__TypeDesc__VECSEMANTICS_e = OpenImageIO_v2_2__TypeDesc__VECSEMANTICS_e(7);


extern "C" {


} // extern "C"
