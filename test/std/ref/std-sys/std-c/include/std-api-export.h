#pragma once

// Stolen this setup from OIIO
#if defined(_WIN32) || defined(__CYGWIN__)
#    ifdef STD_STATIC_DEFINE
#        define STD_CPPMM_IMPORT
#        define STD_CPPMM_EXPORT
#    else
#        define STD_CPPMM_IMPORT __declspec(dllimport)
#        define STD_CPPMM_EXPORT __declspec(dllexport)
#    endif
#    define STD_LOCAL
#else
#    define STD_CPPMM_IMPORT __attribute__((visibility("default")))
#    define STD_CPPMM_EXPORT __attribute__((visibility("default")))
#    define STD_CPPMM_LOCAL __attribute__((visibility("hidden")))
#endif

#if defined(STD_CPPMM_BUILD_EXPORT)
#    define STD_CPPMM_API STD_CPPMM_EXPORT
#else
#    define STD_CPPMM_API STD_CPPMM_IMPORT
#endif

// Alignment
#if defined(_WIN32) || defined(__CYGWIN__)
    #define STD_CPPMM_ALIGN(x) __declspec(align(x))
#else
    #define STD_CPPMM_ALIGN(x) __attribute__((aligned(x)))
#endif


