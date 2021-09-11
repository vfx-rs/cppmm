#pragma once
#include "std-api-export.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct std__string_t_s std__string_t;
typedef std__string_t std_string_t;

typedef struct std__list_std__string__t_s {
    char _unused;
} STD_CPPMM_ALIGN(8) std__list_std__string__t;
typedef std__list_std__string__t std_list_string_t;

typedef struct std__list_std__string___iterator_t_s {
    char _unused;
} STD_CPPMM_ALIGN(8) std__list_std__string___iterator_t;
typedef std__list_std__string___iterator_t std_list_string_iterator_t;


STD_CPPMM_API unsigned int std__list_std__string__ctor(
    std_list_string_t * * this_);
#define std_list_string_ctor std__list_std__string__ctor


STD_CPPMM_API unsigned int std__list_std__string___iterator_op_inc(
    std_list_string_iterator_t * this_
    , std_list_string_iterator_t * * return_);
#define std_list_string_iterator_op_inc std__list_std__string___iterator_op_inc


STD_CPPMM_API unsigned int std__list_std__string___iterator_deref(
    std_list_string_iterator_t const * this_
    , std_string_t const * * return_);
#define std_list_string_iterator_deref std__list_std__string___iterator_deref


STD_CPPMM_API unsigned int std__list_std__string___iterator_deref_mut(
    std_list_string_iterator_t * this_
    , std_string_t * * return_);
#define std_list_string_iterator_deref_mut std__list_std__string___iterator_deref_mut


#ifdef __cplusplus
}
#endif
