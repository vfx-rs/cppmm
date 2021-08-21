#pragma once

// Stolen this setup from OIIO
#if defined(_WIN32) || defined(__CYGWIN__)
#    ifdef TMP_SPECS_STATIC_DEFINE
#        define TMP_SPECS_CPPMM_IMPORT
#        define TMP_SPECS_CPPMM_EXPORT
#    else
#        define TMP_SPECS_CPPMM_IMPORT __declspec(dllimport)
#        define TMP_SPECS_CPPMM_EXPORT __declspec(dllexport)
#    endif
#    define TMP_SPECS_LOCAL
#else
#    define TMP_SPECS_CPPMM_IMPORT __attribute__((visibility("default")))
#    define TMP_SPECS_CPPMM_EXPORT __attribute__((visibility("default")))
#    define TMP_SPECS_CPPMM_LOCAL __attribute__((visibility("hidden")))
#endif

#if defined(TMP_SPECS_CPPMM_BUILD_EXPORT)
#    define TMP_SPECS_CPPMM_API TMP_SPECS_CPPMM_EXPORT
#else
#    define TMP_SPECS_CPPMM_API TMP_SPECS_CPPMM_IMPORT
#endif

// Alignment
#if defined(_WIN32) || defined(__CYGWIN__)
    #define TMP_SPECS_CPPMM_ALIGN(x) __declspec(align(x))
#else
    #define TMP_SPECS_CPPMM_ALIGN(x) __attribute__((aligned(x)))
#endif


