#pragma once
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef _Bool  (*fptr_ProgressCallback_t)(void * , float );

unsigned int fptr_takes_ages(
    fptr_ProgressCallback_t cb
    , void * data);
#ifdef __cplusplus
}
#endif
