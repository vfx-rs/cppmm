#pragma once

// Stolen this setup from OIIO
#if defined(_WIN32) || defined(__CYGWIN__)
#    ifdef DEEP_NAMESPACE_STATIC_DEFINE
#        define DEEP_NAMESPACE_CPPMM_IMPORT
#        define DEEP_NAMESPACE_CPPMM_EXPORT
#    else
#        define DEEP_NAMESPACE_CPPMM_IMPORT __declspec(dllimport)
#        define DEEP_NAMESPACE_CPPMM_EXPORT __declspec(dllexport)
#    endif
#    define DEEP_NAMESPACE_LOCAL
#else
#    define DEEP_NAMESPACE_CPPMM_IMPORT __attribute__((visibility("default")))
#    define DEEP_NAMESPACE_CPPMM_EXPORT __attribute__((visibility("default")))
#    define DEEP_NAMESPACE_CPPMM_LOCAL __attribute__((visibility("hidden")))
#endif

#if defined(DEEP_NAMESPACE_CPPMM_BUILD_EXPORT)
#    define DEEP_NAMESPACE_CPPMM_API DEEP_NAMESPACE_CPPMM_EXPORT
#else
#    define DEEP_NAMESPACE_CPPMM_API DEEP_NAMESPACE_CPPMM_IMPORT
#endif

// Alignment
#if defined(_WIN32) || defined(__CYGWIN__)
    #define DEEP_NAMESPACE_CPPMM_ALIGN(x) __declspec(align(x))
#else
    #define DEEP_NAMESPACE_CPPMM_ALIGN(x) __attribute__((aligned(x)))
#endif


