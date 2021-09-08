#pragma once

// Stolen this setup from OIIO
#if defined(_WIN32) || defined(__CYGWIN__)
#    ifdef DTOR_STATIC_DEFINE
#        define DTOR_CPPMM_IMPORT
#        define DTOR_CPPMM_EXPORT
#    else
#        define DTOR_CPPMM_IMPORT __declspec(dllimport)
#        define DTOR_CPPMM_EXPORT __declspec(dllexport)
#    endif
#    define DTOR_LOCAL
#else
#    define DTOR_CPPMM_IMPORT __attribute__((visibility("default")))
#    define DTOR_CPPMM_EXPORT __attribute__((visibility("default")))
#    define DTOR_CPPMM_LOCAL __attribute__((visibility("hidden")))
#endif

#if defined(DTOR_CPPMM_BUILD_EXPORT)
#    define DTOR_CPPMM_API DTOR_CPPMM_EXPORT
#else
#    define DTOR_CPPMM_API DTOR_CPPMM_IMPORT
#endif

// Alignment
#if defined(_WIN32) || defined(__CYGWIN__)
    #define DTOR_CPPMM_ALIGN(x) __declspec(align(x))
#else
    #define DTOR_CPPMM_ALIGN(x) __attribute__((aligned(x)))
#endif


