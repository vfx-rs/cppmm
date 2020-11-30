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

typedef struct { char _private[8]; } pxrInternal_v0_20__pxrReserved___TfToken CPPMM_ALIGN(8);

/// Returns \c true iff this token contains the empty string \c ""
bool pxrInternal_v0_20__pxrReserved___TfToken_IsEmpty(const pxrInternal_v0_20__pxrReserved___TfToken* self);

/// Inequality operator for \c char strings.  Not as fast as direct
/// token to token equality testing
bool pxrInternal_v0_20__pxrReserved___TfToken_neq_string(const pxrInternal_v0_20__pxrReserved___TfToken* self, const char* o);

/// Equality operator for \c char strings.  Not as fast as direct
/// token to token equality testing
bool pxrInternal_v0_20__pxrReserved___TfToken_eq_string(const pxrInternal_v0_20__pxrReserved___TfToken* self, const char* o);

/// Equality operator
bool pxrInternal_v0_20__pxrReserved___TfToken_op_neq(const pxrInternal_v0_20__pxrReserved___TfToken* self, const pxrInternal_v0_20__pxrReserved___TfToken* o);

/// Equality operator
bool pxrInternal_v0_20__pxrReserved___TfToken_op_eq(const pxrInternal_v0_20__pxrReserved___TfToken* self, const pxrInternal_v0_20__pxrReserved___TfToken* o);

/// Synonym for GetText().
const char* pxrInternal_v0_20__pxrReserved___TfToken_data(const pxrInternal_v0_20__pxrReserved___TfToken* self);

/// Copy assignment.
pxrInternal_v0_20__pxrReserved___TfToken* pxrInternal_v0_20__pxrReserved___TfToken_assign(pxrInternal_v0_20__pxrReserved___TfToken* self, const pxrInternal_v0_20__pxrReserved___TfToken* other);

/// Destructor.
void pxrInternal_v0_20__pxrReserved___TfToken_destruct(pxrInternal_v0_20__pxrReserved___TfToken* self);

/// Returns \c true iff this is an immortal token.
bool pxrInternal_v0_20__pxrReserved___TfToken_IsImmortal(const pxrInternal_v0_20__pxrReserved___TfToken* self);

/// Less-than operator that compares tokenized strings lexicographically.
/// Allows \c TfToken to be used in \c std::set
bool pxrInternal_v0_20__pxrReserved___TfToken_op_lt(const pxrInternal_v0_20__pxrReserved___TfToken* self, const pxrInternal_v0_20__pxrReserved___TfToken* r);

/// Copy constructor.
void pxrInternal_v0_20__pxrReserved___TfToken_copy(pxrInternal_v0_20__pxrReserved___TfToken* self, const pxrInternal_v0_20__pxrReserved___TfToken* other);

/// Acquire a token for the given string.
void pxrInternal_v0_20__pxrReserved___TfToken_from_string(pxrInternal_v0_20__pxrReserved___TfToken* self, const char* s);

/// Return the text that this token represents.
///
/// \note The returned pointer value is not valid after this TfToken
/// object has been destroyed.
///
const char* pxrInternal_v0_20__pxrReserved___TfToken_GetText(const pxrInternal_v0_20__pxrReserved___TfToken* self);


unsigned long pxrInternal_v0_20__pxrReserved___TfToken_Hash(const pxrInternal_v0_20__pxrReserved___TfToken* self);

/// Return the size of the string that this token represents.
unsigned long pxrInternal_v0_20__pxrReserved___TfToken_size(const pxrInternal_v0_20__pxrReserved___TfToken* self);


#undef CPPMM_ALIGN

#define pxr_TfToken pxrInternal_v0_20__pxrReserved___TfToken
#define pxr_TfToken_IsEmpty pxrInternal_v0_20__pxrReserved___TfToken_IsEmpty
#define pxr_TfToken_neq_string pxrInternal_v0_20__pxrReserved___TfToken_neq_string
#define pxr_TfToken_eq_string pxrInternal_v0_20__pxrReserved___TfToken_eq_string
#define pxr_TfToken_op_neq pxrInternal_v0_20__pxrReserved___TfToken_op_neq
#define pxr_TfToken_op_eq pxrInternal_v0_20__pxrReserved___TfToken_op_eq
#define pxr_TfToken_data pxrInternal_v0_20__pxrReserved___TfToken_data
#define pxr_TfToken_assign pxrInternal_v0_20__pxrReserved___TfToken_assign
#define pxr_TfToken_destruct pxrInternal_v0_20__pxrReserved___TfToken_destruct
#define pxr_TfToken_IsImmortal pxrInternal_v0_20__pxrReserved___TfToken_IsImmortal
#define pxr_TfToken_op_lt pxrInternal_v0_20__pxrReserved___TfToken_op_lt
#define pxr_TfToken_copy pxrInternal_v0_20__pxrReserved___TfToken_copy
#define pxr_TfToken_from_string pxrInternal_v0_20__pxrReserved___TfToken_from_string
#define pxr_TfToken_GetText pxrInternal_v0_20__pxrReserved___TfToken_GetText
#define pxr_TfToken_Hash pxrInternal_v0_20__pxrReserved___TfToken_Hash
#define pxr_TfToken_size pxrInternal_v0_20__pxrReserved___TfToken_size

#ifdef __cplusplus
}
#endif
    