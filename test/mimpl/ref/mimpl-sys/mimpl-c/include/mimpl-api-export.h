#pragma once

// Stolen this setup from OIIO
#if defined(_WIN32) || defined(__CYGWIN__)
#    ifdef MIMPL_STATIC_DEFINE
#        define MIMPL_CPPMM_IMPORT
#        define MIMPL_CPPMM_EXPORT
#    else
#        define MIMPL_CPPMM_IMPORT __declspec(dllimport)
#        define MIMPL_CPPMM_EXPORT __declspec(dllexport)
#    endif
#    define MIMPL_LOCAL
#else
#    define MIMPL_CPPMM_IMPORT __attribute__((visibility("default")))
#    define MIMPL_CPPMM_EXPORT __attribute__((visibility("default")))
#    define MIMPL_CPPMM_LOCAL __attribute__((visibility("hidden")))
#endif

#if defined(MIMPL_CPPMM_BUILD_EXPORT)
#    define MIMPL_CPPMM_API MIMPL_CPPMM_EXPORT
#else
#    define MIMPL_CPPMM_API MIMPL_CPPMM_IMPORT
#endif

// Alignment
#if defined(_WIN32) || defined(__CYGWIN__)
    #define MIMPL_CPPMM_ALIGN(x) __declspec(align(x))
#else
    #define MIMPL_CPPMM_ALIGN(x) __attribute__((aligned(x)))
#endif


