
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


typedef struct { char _private[24]; } cppmm_string_vector CPPMM_ALIGN(8);

const char* cppmm_string_vector_get(const cppmm_string_vector* vec, int index);
int cppmm_string_vector_size(const cppmm_string_vector* vec);


#ifdef __cplusplus
}
#endif
    