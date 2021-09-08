#pragma once

// Stolen this setup from OIIO
#if defined(_WIN32) || defined(__CYGWIN__)
#    ifdef IMATH_STATIC_DEFINE
#        define IMATH_CPPMM_IMPORT
#        define IMATH_CPPMM_EXPORT
#    else
#        define IMATH_CPPMM_IMPORT __declspec(dllimport)
#        define IMATH_CPPMM_EXPORT __declspec(dllexport)
#    endif
#    define IMATH_LOCAL
#else
#    define IMATH_CPPMM_IMPORT __attribute__((visibility("default")))
#    define IMATH_CPPMM_EXPORT __attribute__((visibility("default")))
#    define IMATH_CPPMM_LOCAL __attribute__((visibility("hidden")))
#endif

#if defined(IMATH_CPPMM_BUILD_EXPORT)
#    define IMATH_CPPMM_API IMATH_CPPMM_EXPORT
#else
#    define IMATH_CPPMM_API IMATH_CPPMM_IMPORT
#endif

// Alignment
#if defined(_WIN32) || defined(__CYGWIN__)
    #define IMATH_CPPMM_ALIGN(x) __declspec(align(x))
#else
    #define IMATH_CPPMM_ALIGN(x) __attribute__((aligned(x)))
#endif


