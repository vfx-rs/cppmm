#pragma once

// Stolen this setup from OIIO
#if defined(_WIN32) || defined(__CYGWIN__)
#    ifdef RUSTIFY_ENUM_STATIC_DEFINE
#        define RUSTIFY_ENUM_CPPMM_IMPORT
#        define RUSTIFY_ENUM_CPPMM_EXPORT
#    else
#        define RUSTIFY_ENUM_CPPMM_IMPORT __declspec(dllimport)
#        define RUSTIFY_ENUM_CPPMM_EXPORT __declspec(dllexport)
#    endif
#    define RUSTIFY_ENUM_LOCAL
#else
#    define RUSTIFY_ENUM_CPPMM_IMPORT __attribute__((visibility("default")))
#    define RUSTIFY_ENUM_CPPMM_EXPORT __attribute__((visibility("default")))
#    define RUSTIFY_ENUM_CPPMM_LOCAL __attribute__((visibility("hidden")))
#endif

#if defined(RUSTIFY_ENUM_CPPMM_BUILD_EXPORT)
#    define RUSTIFY_ENUM_CPPMM_API RUSTIFY_ENUM_CPPMM_EXPORT
#else
#    define RUSTIFY_ENUM_CPPMM_API RUSTIFY_ENUM_CPPMM_IMPORT
#endif

// Alignment
#if defined(_WIN32) || defined(__CYGWIN__)
    #define RUSTIFY_ENUM_CPPMM_ALIGN(x) __declspec(align(x))
#else
    #define RUSTIFY_ENUM_CPPMM_ALIGN(x) __attribute__((aligned(x)))
#endif


