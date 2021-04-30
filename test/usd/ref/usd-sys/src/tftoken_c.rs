#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]
#![allow(unused_imports)]
use crate::*;
use std::os::raw::*;

/// \class TfToken
/// \ingroup group_tf_String
/// 
/// Token for efficient comparison, assignment, and hashing of known strings.
/// 
/// A TfToken is a handle for a registered string, and can be compared,
/// assigned, and hashed in constant time.  It is useful when a bounded number
/// of strings are used as fixed symbols (but never modified).
/// 
/// For example, the set of avar names in a shot is large but bounded, and
/// once an avar name is discovered, it is never manipulated.  If these names
/// were passed around as strings, every comparison and hash would be linear
/// in the number of characters.  (String assignment itself is sometimes a
/// constant time operation, but it is sometimes linear in the length of the
/// string as well as requiring a memory allocation.)
/// 
/// To use TfToken, simply create an instance from a string or const char*.
/// If the string hasn't been seen before, a copy of it is added to a global
/// table.  The resulting TfToken is simply a wrapper around an string*,
/// pointing that canonical copy of the string.  Thus, operations on the token
/// are very fast.  (The string's hash is simply the address of the canonical
/// copy, so hashing the string is constant time.)
/// 
/// The free functions \c TfToTokenVector() and \c TfToStringVector() provide
/// conversions to and from vectors of \c string.
/// 
/// Note: Access to the global table is protected by a mutex.  This is a good
/// idea as long as clients do not construct tokens from strings too
/// frequently.  Construct tokens only as often as you must (for example, as
/// you read data files), and <i>never</i> in inner loops.  Of course, once
/// you have a token, feel free to compare, assign, and hash it as often as
/// you like.  (That's what it's for.)  In order to help prevent tokens from
/// being re-created over and over, auto type conversion from \c string and \c
/// char* to \c TfToken is disabled (you must use the explicit \c TfToken
/// constructors).  However, auto conversion from \c TfToken to \c string and
/// \c char* is provided.
#[repr(C)]
pub struct pxrInternal_v0_20__pxrReserved____TfToken_t {
    _unused: [u8; 0],
}


extern "C" {

/// Copy constructor.
pub fn pxrInternal_v0_20__pxrReserved____TfToken_copy(this_: *mut *mut pxr_TfToken_t, rhs: *const pxr_TfToken_t) -> c_void;

/// Copy assignment.
pub fn pxrInternal_v0_20__pxrReserved____TfToken_assign(this_: *mut pxr_TfToken_t, rhs: *const pxr_TfToken_t) -> *mut pxr_TfToken_t;

/// Destructor.
pub fn pxrInternal_v0_20__pxrReserved____TfToken_destruct(this_: *mut pxr_TfToken_t) -> c_void;

/// Acquire a token for the given string.
pub fn pxrInternal_v0_20__pxrReserved____TfToken_from_string(this_: *mut *mut pxr_TfToken_t, s: *const c_char) -> c_void;

pub fn pxrInternal_v0_20__pxrReserved____TfToken_Hash(this_: *const pxr_TfToken_t) -> c_ulong;

/// Return the size of the string that this token represents.
pub fn pxrInternal_v0_20__pxrReserved____TfToken_size(this_: *const pxr_TfToken_t) -> c_ulong;

/// Return the text that this token represents.
/// 
/// \note The returned pointer value is not valid after this TfToken
/// object has been destroyed.
pub fn pxrInternal_v0_20__pxrReserved____TfToken_GetText(this_: *const pxr_TfToken_t) -> *const c_char;

/// Synonym for GetText().
pub fn pxrInternal_v0_20__pxrReserved____TfToken_data(this_: *const pxr_TfToken_t) -> *const c_char;

/// Equality operator
pub fn pxrInternal_v0_20__pxrReserved____TfToken__eq(this_: *const pxr_TfToken_t, o: *const pxr_TfToken_t) -> bool;

/// Equality operator
pub fn pxrInternal_v0_20__pxrReserved____TfToken__ne(this_: *const pxr_TfToken_t, o: *const pxr_TfToken_t) -> bool;

/// Equality operator for \c char strings.  Not as fast as direct
/// token to token equality testing
pub fn pxrInternal_v0_20__pxrReserved____TfToken_eq_string(this_: *const pxr_TfToken_t, o: *const c_char) -> bool;

/// Inequality operator for \c char strings.  Not as fast as direct
/// token to token equality testing
pub fn pxrInternal_v0_20__pxrReserved____TfToken_neq_string(this_: *const pxr_TfToken_t, o: *const c_char) -> bool;

/// Less-than operator that compares tokenized strings lexicographically.
/// Allows \c TfToken to be used in \c std::set
pub fn pxrInternal_v0_20__pxrReserved____TfToken_operator_(this_: *const pxr_TfToken_t, r: *const pxr_TfToken_t) -> bool;

/// Returns \c true iff this token contains the empty string \c ""
pub fn pxrInternal_v0_20__pxrReserved____TfToken_IsEmpty(this_: *const pxr_TfToken_t) -> bool;

/// Returns \c true iff this is an immortal token.
pub fn pxrInternal_v0_20__pxrReserved____TfToken_IsImmortal(this_: *const pxr_TfToken_t) -> bool;


} // extern "C"
