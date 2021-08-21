#pragma once

// Stolen this setup from OIIO
#if defined(_WIN32) || defined(__CYGWIN__)
#    ifdef UNIQUEPTR_STATIC_DEFINE
#        define UNIQUEPTR_CPPMM_IMPORT
#        define UNIQUEPTR_CPPMM_EXPORT
#    else
#        define UNIQUEPTR_CPPMM_IMPORT __declspec(dllimport)
#        define UNIQUEPTR_CPPMM_EXPORT __declspec(dllexport)
#    endif
#    define UNIQUEPTR_LOCAL
#else
#    define UNIQUEPTR_CPPMM_IMPORT __attribute__((visibility("default")))
#    define UNIQUEPTR_CPPMM_EXPORT __attribute__((visibility("default")))
#    define UNIQUEPTR_CPPMM_LOCAL __attribute__((visibility("hidden")))
#endif

#if defined(UNIQUEPTR_CPPMM_BUILD_EXPORT)
#    define UNIQUEPTR_CPPMM_API UNIQUEPTR_CPPMM_EXPORT
#else
#    define UNIQUEPTR_CPPMM_API UNIQUEPTR_CPPMM_IMPORT
#endif

// Alignment
#if defined(_WIN32) || defined(__CYGWIN__)
    #define UNIQUEPTR_CPPMM_ALIGN(x) __declspec(align(x))
#else
    #define UNIQUEPTR_CPPMM_ALIGN(x) __attribute__((aligned(x)))
#endif


