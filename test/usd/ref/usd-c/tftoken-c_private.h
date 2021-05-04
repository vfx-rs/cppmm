#pragma once
#include <tftoken-c.h>


#include <cstring>
#include <pxr/base/tf/token.h>


/** Copy constructor. */

/** Copy assignment. */

/** Destructor. */

/** Acquire a token for the given string. */


/** Return the size of the string that this token represents. */

/** Return the text that this token represents.

\note The returned pointer value is not valid after this TfToken
object has been destroyed. */

/** Synonym for GetText(). */

/** Equality operator */

/** Equality operator */

/** Equality operator for \c char strings.  Not as fast as direct
token to token equality testing */

/** Inequality operator for \c char strings.  Not as fast as direct
token to token equality testing */

/** Less-than operator that compares tokenized strings lexicographically.
Allows \c TfToken to be used in \c std::set */

/** Returns \c true iff this token contains the empty string \c "" */

/** Returns \c true iff this is an immortal token. */

inline pxrInternal_v0_20__pxrReserved__::TfToken const & to_cpp_ref(
    pxr_TfToken_t const * rhs)
{
        return *(reinterpret_cast<pxrInternal_v0_20__pxrReserved__::TfToken const * >(rhs));
}

inline pxrInternal_v0_20__pxrReserved__::TfToken & to_cpp_ref(
    pxr_TfToken_t * rhs)
{
        return *(reinterpret_cast<pxrInternal_v0_20__pxrReserved__::TfToken * >(rhs));
}

inline pxrInternal_v0_20__pxrReserved__::TfToken const * to_cpp(
    pxr_TfToken_t const * rhs)
{
        return reinterpret_cast<pxrInternal_v0_20__pxrReserved__::TfToken const * >(rhs);
}

inline pxrInternal_v0_20__pxrReserved__::TfToken * to_cpp(
    pxr_TfToken_t * rhs)
{
        return reinterpret_cast<pxrInternal_v0_20__pxrReserved__::TfToken * >(rhs);
}

inline void to_c(
    pxr_TfToken_t const * * lhs
    , pxrInternal_v0_20__pxrReserved__::TfToken const & rhs)
{
        *(lhs) = reinterpret_cast<pxr_TfToken_t const * >(&(rhs));
}

inline void to_c(
    pxr_TfToken_t const * * lhs
    , pxrInternal_v0_20__pxrReserved__::TfToken const * rhs)
{
        *(lhs) = reinterpret_cast<pxr_TfToken_t const * >(rhs);
}

inline void to_c(
    pxr_TfToken_t * * lhs
    , pxrInternal_v0_20__pxrReserved__::TfToken & rhs)
{
        *(lhs) = reinterpret_cast<pxr_TfToken_t * >(&(rhs));
}

inline void to_c(
    pxr_TfToken_t * * lhs
    , pxrInternal_v0_20__pxrReserved__::TfToken * rhs)
{
        *(lhs) = reinterpret_cast<pxr_TfToken_t * >(rhs);
}

inline void to_c_copy(
    pxr_TfToken_t * * lhs
    , pxrInternal_v0_20__pxrReserved__::TfToken const & rhs)
{
        pxrInternal_v0_20__pxrReserved____TfToken_copy(lhs, reinterpret_cast<pxr_TfToken_t const * >(&(rhs)));
}
