#pragma once

// Stolen this setup from OIIO
#if defined(_WIN32) || defined(__CYGWIN__)
#    ifdef ARRAY_PARAMS_STATIC_DEFINE
#        define ARRAY_PARAMS_CPPMM_IMPORT
#        define ARRAY_PARAMS_CPPMM_EXPORT
#    else
#        define ARRAY_PARAMS_CPPMM_IMPORT __declspec(dllimport)
#        define ARRAY_PARAMS_CPPMM_EXPORT __declspec(dllexport)
#    endif
#    define ARRAY_PARAMS_LOCAL
#else
#    define ARRAY_PARAMS_CPPMM_IMPORT __attribute__((visibility("default")))
#    define ARRAY_PARAMS_CPPMM_EXPORT __attribute__((visibility("default")))
#    define ARRAY_PARAMS_CPPMM_LOCAL __attribute__((visibility("hidden")))
#endif

#if defined(ARRAY_PARAMS_CPPMM_BUILD_EXPORT)
#    define ARRAY_PARAMS_CPPMM_API ARRAY_PARAMS_CPPMM_EXPORT
#else
#    define ARRAY_PARAMS_CPPMM_API ARRAY_PARAMS_CPPMM_IMPORT
#endif

// Alignment
#if defined(_WIN32) || defined(__CYGWIN__)
    #define ARRAY_PARAMS_CPPMM_ALIGN(x) __declspec(align(x))
#else
    #define ARRAY_PARAMS_CPPMM_ALIGN(x) __attribute__((aligned(x)))
#endif


