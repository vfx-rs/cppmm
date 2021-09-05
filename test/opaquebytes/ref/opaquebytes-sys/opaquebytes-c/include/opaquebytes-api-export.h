#pragma once

// Stolen this setup from OIIO
#if defined(_WIN32) || defined(__CYGWIN__)
#    ifdef OPAQUEBYTES_STATIC_DEFINE
#        define OPAQUEBYTES_CPPMM_IMPORT
#        define OPAQUEBYTES_CPPMM_EXPORT
#    else
#        define OPAQUEBYTES_CPPMM_IMPORT __declspec(dllimport)
#        define OPAQUEBYTES_CPPMM_EXPORT __declspec(dllexport)
#    endif
#    define OPAQUEBYTES_LOCAL
#else
#    define OPAQUEBYTES_CPPMM_IMPORT __attribute__((visibility("default")))
#    define OPAQUEBYTES_CPPMM_EXPORT __attribute__((visibility("default")))
#    define OPAQUEBYTES_CPPMM_LOCAL __attribute__((visibility("hidden")))
#endif

#if defined(OPAQUEBYTES_CPPMM_BUILD_EXPORT)
#    define OPAQUEBYTES_CPPMM_API OPAQUEBYTES_CPPMM_EXPORT
#else
#    define OPAQUEBYTES_CPPMM_API OPAQUEBYTES_CPPMM_IMPORT
#endif

// Alignment
#if defined(_WIN32) || defined(__CYGWIN__)
    #define OPAQUEBYTES_CPPMM_ALIGN(x) __declspec(align(x))
#else
    #define OPAQUEBYTES_CPPMM_ALIGN(x) __attribute__((aligned(x)))
#endif


