#pragma once
#include "mimpl-api-export.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct mimpl__Number_t_s {
    char _unused;
} MIMPL_CPPMM_ALIGN(4) mimpl__Number_t;
typedef mimpl__Number_t mimpl_Number_t;


MIMPL_CPPMM_API unsigned int mimpl__Number_ctor(
    mimpl_Number_t * * this_);
#define mimpl_Number_ctor mimpl__Number_ctor


MIMPL_CPPMM_API unsigned int mimpl__Number_get_number(
    mimpl_Number_t const * this_
    , int * return_);
#define mimpl_Number_get_number mimpl__Number_get_number


MIMPL_CPPMM_API unsigned int Number_do_get_number(
    int * return_
    , mimpl_Number_t const * self);

#ifdef __cplusplus
}
#endif
