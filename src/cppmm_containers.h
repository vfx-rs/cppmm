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


typedef struct cppmm_Vector_string cppmm_Vector_string;

const char* cppmm_Vector_string_get(const cppmm_Vector_string* vec, int index);
int cppmm_Vector_string_size(const cppmm_Vector_string* vec);


#ifdef __cplusplus
}
#endif
