#pragma once

// Stolen this setup from OIIO
#if defined(_WIN32) || defined(__CYGWIN__)
#    ifdef PROPERTY_STATIC_DEFINE
#        define PROPERTY_CPPMM_IMPORT
#        define PROPERTY_CPPMM_EXPORT
#    else
#        define PROPERTY_CPPMM_IMPORT __declspec(dllimport)
#        define PROPERTY_CPPMM_EXPORT __declspec(dllexport)
#    endif
#    define PROPERTY_LOCAL
#else
#    define PROPERTY_CPPMM_IMPORT __attribute__((visibility("default")))
#    define PROPERTY_CPPMM_EXPORT __attribute__((visibility("default")))
#    define PROPERTY_CPPMM_LOCAL __attribute__((visibility("hidden")))
#endif

#if defined(PROPERTY_CPPMM_BUILD_EXPORT)
#    define PROPERTY_CPPMM_API PROPERTY_CPPMM_EXPORT
#else
#    define PROPERTY_CPPMM_API PROPERTY_CPPMM_IMPORT
#endif

// Alignment
#if defined(_WIN32) || defined(__CYGWIN__)
    #define PROPERTY_CPPMM_ALIGN(x) __declspec(align(x))
#else
    #define PROPERTY_CPPMM_ALIGN(x) __attribute__((aligned(x)))
#endif


