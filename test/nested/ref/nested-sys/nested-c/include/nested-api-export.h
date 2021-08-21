#pragma once

// Stolen this setup from OIIO
#if defined(_WIN32) || defined(__CYGWIN__)
#    ifdef NESTED_STATIC_DEFINE
#        define NESTED_CPPMM_IMPORT
#        define NESTED_CPPMM_EXPORT
#    else
#        define NESTED_CPPMM_IMPORT __declspec(dllimport)
#        define NESTED_CPPMM_EXPORT __declspec(dllexport)
#    endif
#    define NESTED_LOCAL
#else
#    define NESTED_CPPMM_IMPORT __attribute__((visibility("default")))
#    define NESTED_CPPMM_EXPORT __attribute__((visibility("default")))
#    define NESTED_CPPMM_LOCAL __attribute__((visibility("hidden")))
#endif

#if defined(NESTED_CPPMM_BUILD_EXPORT)
#    define NESTED_CPPMM_API NESTED_CPPMM_EXPORT
#else
#    define NESTED_CPPMM_API NESTED_CPPMM_IMPORT
#endif

// Alignment
#if defined(_WIN32) || defined(__CYGWIN__)
    #define NESTED_CPPMM_ALIGN(x) __declspec(align(x))
#else
    #define NESTED_CPPMM_ALIGN(x) __attribute__((aligned(x)))
#endif


