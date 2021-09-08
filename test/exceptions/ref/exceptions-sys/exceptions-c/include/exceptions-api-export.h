#pragma once

// Stolen this setup from OIIO
#if defined(_WIN32) || defined(__CYGWIN__)
#    ifdef EXCEPTIONS_STATIC_DEFINE
#        define EXCEPTIONS_CPPMM_IMPORT
#        define EXCEPTIONS_CPPMM_EXPORT
#    else
#        define EXCEPTIONS_CPPMM_IMPORT __declspec(dllimport)
#        define EXCEPTIONS_CPPMM_EXPORT __declspec(dllexport)
#    endif
#    define EXCEPTIONS_LOCAL
#else
#    define EXCEPTIONS_CPPMM_IMPORT __attribute__((visibility("default")))
#    define EXCEPTIONS_CPPMM_EXPORT __attribute__((visibility("default")))
#    define EXCEPTIONS_CPPMM_LOCAL __attribute__((visibility("hidden")))
#endif

#if defined(EXCEPTIONS_CPPMM_BUILD_EXPORT)
#    define EXCEPTIONS_CPPMM_API EXCEPTIONS_CPPMM_EXPORT
#else
#    define EXCEPTIONS_CPPMM_API EXCEPTIONS_CPPMM_IMPORT
#endif

// Alignment
#if defined(_WIN32) || defined(__CYGWIN__)
    #define EXCEPTIONS_CPPMM_ALIGN(x) __declspec(align(x))
#else
    #define EXCEPTIONS_CPPMM_ALIGN(x) __attribute__((aligned(x)))
#endif


