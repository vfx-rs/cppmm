#pragma once
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/** \class TfToken
\ingroup group_tf_String

Token for efficient comparison, assignment, and hashing of known strings.

A TfToken is a handle for a registered string, and can be compared,
assigned, and hashed in constant time.  It is useful when a bounded number
of strings are used as fixed symbols (but never modified).

For example, the set of avar names in a shot is large but bounded, and
once an avar name is discovered, it is never manipulated.  If these names
were passed around as strings, every comparison and hash would be linear
in the number of characters.  (String assignment itself is sometimes a
constant time operation, but it is sometimes linear in the length of the
string as well as requiring a memory allocation.)

To use TfToken, simply create an instance from a string or const char*.
If the string hasn't been seen before, a copy of it is added to a global
table.  The resulting TfToken is simply a wrapper around an string*,
pointing that canonical copy of the string.  Thus, operations on the token
are very fast.  (The string's hash is simply the address of the canonical
copy, so hashing the string is constant time.)

The free functions \c TfToTokenVector() and \c TfToStringVector() provide
conversions to and from vectors of \c string.

Note: Access to the global table is protected by a mutex.  This is a good
idea as long as clients do not construct tokens from strings too
frequently.  Construct tokens only as often as you must (for example, as
you read data files), and <i>never</i> in inner loops.  Of course, once
you have a token, feel free to compare, assign, and hash it as often as
you like.  (That's what it's for.)  In order to help prevent tokens from
being re-created over and over, auto type conversion from \c string and \c
char* to \c TfToken is disabled (you must use the explicit \c TfToken
constructors).  However, auto conversion from \c TfToken to \c string and
\c char* is provided. */
typedef struct pxrInternal_v0_20__pxrReserved____TfToken_t_s {
    char _unused;
} __attribute__((aligned(8))) pxrInternal_v0_20__pxrReserved____TfToken_t;
typedef pxrInternal_v0_20__pxrReserved____TfToken_t pxr_TfToken_t;



/** Copy constructor. */
unsigned int pxrInternal_v0_20__pxrReserved____TfToken_copy(
    pxr_TfToken_t * * this_
    , pxr_TfToken_t const * rhs);
#define pxr_TfToken_copy pxrInternal_v0_20__pxrReserved____TfToken_copy


/** Copy assignment. */
unsigned int pxrInternal_v0_20__pxrReserved____TfToken_assign(
    pxr_TfToken_t * this_
    , pxr_TfToken_t * * return_
    , pxr_TfToken_t const * rhs);
#define pxr_TfToken_assign pxrInternal_v0_20__pxrReserved____TfToken_assign


/** Destructor. */
unsigned int pxrInternal_v0_20__pxrReserved____TfToken_destruct(
    pxr_TfToken_t * this_);
#define pxr_TfToken_destruct pxrInternal_v0_20__pxrReserved____TfToken_destruct


/** Acquire a token for the given string. */
unsigned int pxrInternal_v0_20__pxrReserved____TfToken_from_string(
    pxr_TfToken_t * * this_
    , char const * s);
#define pxr_TfToken_from_string pxrInternal_v0_20__pxrReserved____TfToken_from_string


unsigned int pxrInternal_v0_20__pxrReserved____TfToken_Hash(
    pxr_TfToken_t const * this_
    , unsigned long * return_);
#define pxr_TfToken_Hash pxrInternal_v0_20__pxrReserved____TfToken_Hash


/** Return the size of the string that this token represents. */
unsigned int pxrInternal_v0_20__pxrReserved____TfToken_size(
    pxr_TfToken_t const * this_
    , unsigned long * return_);
#define pxr_TfToken_size pxrInternal_v0_20__pxrReserved____TfToken_size


/** Return the text that this token represents.

\note The returned pointer value is not valid after this TfToken
object has been destroyed. */
unsigned int pxrInternal_v0_20__pxrReserved____TfToken_GetText(
    pxr_TfToken_t const * this_
    , char const * * return_);
#define pxr_TfToken_GetText pxrInternal_v0_20__pxrReserved____TfToken_GetText


/** Synonym for GetText(). */
unsigned int pxrInternal_v0_20__pxrReserved____TfToken_data(
    pxr_TfToken_t const * this_
    , char const * * return_);
#define pxr_TfToken_data pxrInternal_v0_20__pxrReserved____TfToken_data


/** Equality operator */
unsigned int pxrInternal_v0_20__pxrReserved____TfToken__eq(
    pxr_TfToken_t const * this_
    , _Bool * return_
    , pxr_TfToken_t const * o);
#define pxr_TfToken__eq pxrInternal_v0_20__pxrReserved____TfToken__eq


/** Equality operator */
unsigned int pxrInternal_v0_20__pxrReserved____TfToken__ne(
    pxr_TfToken_t const * this_
    , _Bool * return_
    , pxr_TfToken_t const * o);
#define pxr_TfToken__ne pxrInternal_v0_20__pxrReserved____TfToken__ne


/** Equality operator for \c char strings.  Not as fast as direct
token to token equality testing */
unsigned int pxrInternal_v0_20__pxrReserved____TfToken_eq_string(
    pxr_TfToken_t const * this_
    , _Bool * return_
    , char const * o);
#define pxr_TfToken_eq_string pxrInternal_v0_20__pxrReserved____TfToken_eq_string


/** Inequality operator for \c char strings.  Not as fast as direct
token to token equality testing */
unsigned int pxrInternal_v0_20__pxrReserved____TfToken_neq_string(
    pxr_TfToken_t const * this_
    , _Bool * return_
    , char const * o);
#define pxr_TfToken_neq_string pxrInternal_v0_20__pxrReserved____TfToken_neq_string


/** Less-than operator that compares tokenized strings lexicographically.
Allows \c TfToken to be used in \c std::set */
unsigned int pxrInternal_v0_20__pxrReserved____TfToken_operator_(
    pxr_TfToken_t const * this_
    , _Bool * return_
    , pxr_TfToken_t const * r);
#define pxr_TfToken_operator_ pxrInternal_v0_20__pxrReserved____TfToken_operator_


/** Returns \c true iff this token contains the empty string \c "" */
unsigned int pxrInternal_v0_20__pxrReserved____TfToken_IsEmpty(
    pxr_TfToken_t const * this_
    , _Bool * return_);
#define pxr_TfToken_IsEmpty pxrInternal_v0_20__pxrReserved____TfToken_IsEmpty


/** Returns \c true iff this is an immortal token. */
unsigned int pxrInternal_v0_20__pxrReserved____TfToken_IsImmortal(
    pxr_TfToken_t const * this_
    , _Bool * return_);
#define pxr_TfToken_IsImmortal pxrInternal_v0_20__pxrReserved____TfToken_IsImmortal










#ifdef __cplusplus
}
#endif
