#pragma once

// Stolen this setup from OIIO
#if defined(_WIN32) || defined(__CYGWIN__)
#    ifdef COMMENTS_STATIC_DEFINE
#        define COMMENTS_CPPMM_IMPORT
#        define COMMENTS_CPPMM_EXPORT
#    else
#        define COMMENTS_CPPMM_IMPORT __declspec(dllimport)
#        define COMMENTS_CPPMM_EXPORT __declspec(dllexport)
#    endif
#    define COMMENTS_LOCAL
#else
#    define COMMENTS_CPPMM_IMPORT __attribute__((visibility("default")))
#    define COMMENTS_CPPMM_EXPORT __attribute__((visibility("default")))
#    define COMMENTS_CPPMM_LOCAL __attribute__((visibility("hidden")))
#endif

#if defined(COMMENTS_CPPMM_BUILD_EXPORT)
#    define COMMENTS_CPPMM_API COMMENTS_CPPMM_EXPORT
#else
#    define COMMENTS_CPPMM_API COMMENTS_CPPMM_IMPORT
#endif

// Alignment
#if defined(_WIN32) || defined(__CYGWIN__)
    #define COMMENTS_CPPMM_ALIGN(x) __declspec(align(x))
#else
    #define COMMENTS_CPPMM_ALIGN(x) __attribute__((aligned(x)))
#endif


