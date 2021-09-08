#pragma once

// Stolen this setup from OIIO
#if defined(_WIN32) || defined(__CYGWIN__)
#    ifdef OPAQUEPTR_STATIC_DEFINE
#        define OPAQUEPTR_CPPMM_IMPORT
#        define OPAQUEPTR_CPPMM_EXPORT
#    else
#        define OPAQUEPTR_CPPMM_IMPORT __declspec(dllimport)
#        define OPAQUEPTR_CPPMM_EXPORT __declspec(dllexport)
#    endif
#    define OPAQUEPTR_LOCAL
#else
#    define OPAQUEPTR_CPPMM_IMPORT __attribute__((visibility("default")))
#    define OPAQUEPTR_CPPMM_EXPORT __attribute__((visibility("default")))
#    define OPAQUEPTR_CPPMM_LOCAL __attribute__((visibility("hidden")))
#endif

#if defined(OPAQUEPTR_CPPMM_BUILD_EXPORT)
#    define OPAQUEPTR_CPPMM_API OPAQUEPTR_CPPMM_EXPORT
#else
#    define OPAQUEPTR_CPPMM_API OPAQUEPTR_CPPMM_IMPORT
#endif

// Alignment
#if defined(_WIN32) || defined(__CYGWIN__)
    #define OPAQUEPTR_CPPMM_ALIGN(x) __declspec(align(x))
#else
    #define OPAQUEPTR_CPPMM_ALIGN(x) __attribute__((aligned(x)))
#endif


