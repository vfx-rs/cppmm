#pragma once

// Stolen this setup from OIIO
#if defined(_WIN32) || defined(__CYGWIN__)
#    ifdef FUNCTION_POINTERS_STATIC_DEFINE
#        define FUNCTION_POINTERS_CPPMM_IMPORT
#        define FUNCTION_POINTERS_CPPMM_EXPORT
#    else
#        define FUNCTION_POINTERS_CPPMM_IMPORT __declspec(dllimport)
#        define FUNCTION_POINTERS_CPPMM_EXPORT __declspec(dllexport)
#    endif
#    define FUNCTION_POINTERS_LOCAL
#else
#    define FUNCTION_POINTERS_CPPMM_IMPORT __attribute__((visibility("default")))
#    define FUNCTION_POINTERS_CPPMM_EXPORT __attribute__((visibility("default")))
#    define FUNCTION_POINTERS_CPPMM_LOCAL __attribute__((visibility("hidden")))
#endif

#if defined(FUNCTION_POINTERS_CPPMM_BUILD_EXPORT)
#    define FUNCTION_POINTERS_CPPMM_API FUNCTION_POINTERS_CPPMM_EXPORT
#else
#    define FUNCTION_POINTERS_CPPMM_API FUNCTION_POINTERS_CPPMM_IMPORT
#endif

// Alignment
#if defined(_WIN32) || defined(__CYGWIN__)
    #define FUNCTION_POINTERS_CPPMM_ALIGN(x) __declspec(align(x))
#else
    #define FUNCTION_POINTERS_CPPMM_ALIGN(x) __attribute__((aligned(x)))
#endif


