#pragma once

// Stolen this setup from OIIO
#if defined(_WIN32) || defined(__CYGWIN__)
#    ifdef DERIVEATTR_STATIC_DEFINE
#        define DERIVEATTR_CPPMM_IMPORT
#        define DERIVEATTR_CPPMM_EXPORT
#    else
#        define DERIVEATTR_CPPMM_IMPORT __declspec(dllimport)
#        define DERIVEATTR_CPPMM_EXPORT __declspec(dllexport)
#    endif
#    define DERIVEATTR_LOCAL
#else
#    define DERIVEATTR_CPPMM_IMPORT __attribute__((visibility("default")))
#    define DERIVEATTR_CPPMM_EXPORT __attribute__((visibility("default")))
#    define DERIVEATTR_CPPMM_LOCAL __attribute__((visibility("hidden")))
#endif

#if defined(DERIVEATTR_CPPMM_BUILD_EXPORT)
#    define DERIVEATTR_CPPMM_API DERIVEATTR_CPPMM_EXPORT
#else
#    define DERIVEATTR_CPPMM_API DERIVEATTR_CPPMM_IMPORT
#endif

// Alignment
#if defined(_WIN32) || defined(__CYGWIN__)
    #define DERIVEATTR_CPPMM_ALIGN(x) __declspec(align(x))
#else
    #define DERIVEATTR_CPPMM_ALIGN(x) __attribute__((aligned(x)))
#endif


