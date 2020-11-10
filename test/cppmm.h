#pragma once

#ifdef __cplusplus
extern "C" {
#else
#include <stdbool.h>
#endif

#if defined(_WIN32) || defined(__CYGWIN__)
#define CPPMM_ALIGN(x) __declspec(align(x))
#else
#define CPPMM_ALIGN(x) __attribute__((aligned(x)))
#endif

#if defined(_WIN32) || defined(__CYGWIN__)
#if defined(CPPMM_EXPORT)
#define CPPMM_API __declspec(dllexport)
#else
#define CPPMM_API __declspec(dllimport)
#endif
#else
#define CPPMM_API __attribute__((visbility("default")))
#endif

struct cppmm_Vec_string {
    char _private[24];
} CPPMM_ALIGN(8);

CPPMM_API int cppmm_Vec_string_size(cppmm_Vec_string* self);
CPPMM_API const char* cppmm_Vec_string_get(cppmm_Vec_string* self, int index);
CPPMM_API void cppmm_Vec_string_destroy(cppmm_Vec_string* self);


#undef CPPMM_ALIGN

#ifdef __cplusplus
}
#endif
