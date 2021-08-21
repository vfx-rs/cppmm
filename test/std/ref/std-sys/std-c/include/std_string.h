#pragma once
#include "std-api-export.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct std____cxx11__basic_string_char__t_s {
    char data[32];
} STD_CPPMM_ALIGN(8) std____cxx11__basic_string_char__t;
typedef std____cxx11__basic_string_char__t std_string_t;

typedef struct std__vector_std__string__t_s {
    char data[24];
} STD_CPPMM_ALIGN(8) std__vector_std__string__t;
typedef std__vector_std__string__t std_vector_string_t;


/** returns the size of this type in bytes */
STD_CPPMM_API unsigned int std____cxx11__basic_string_char__sizeof();
#define std_string_sizeof std____cxx11__basic_string_char__sizeof


/** returns the size of this type in bytes */
STD_CPPMM_API unsigned int std____cxx11__basic_string_char__alignof();
#define std_string_alignof std____cxx11__basic_string_char__alignof


STD_CPPMM_API unsigned int std____cxx11__basic_string_char__assign(
    std_string_t * this_
    , std_string_t * * return_
    , char const * s
    , size_t count);
#define std_string_assign std____cxx11__basic_string_char__assign


STD_CPPMM_API unsigned int std____cxx11__basic_string_char__c_str(
    std_string_t const * this_
    , char const * * return_);
#define std_string_c_str std____cxx11__basic_string_char__c_str


/** returns the size of this type in bytes */
STD_CPPMM_API unsigned int std__vector_std__string__sizeof();
#define std_vector_string_sizeof std__vector_std__string__sizeof


/** returns the size of this type in bytes */
STD_CPPMM_API unsigned int std__vector_std__string__alignof();
#define std_vector_string_alignof std__vector_std__string__alignof


STD_CPPMM_API unsigned int std__vector_std__string__ctor(
    std_vector_string_t * this_);
#define std_vector_string_ctor std__vector_std__string__ctor


STD_CPPMM_API unsigned int std__vector_std__string__dtor(
    std_vector_string_t * this_);
#define std_vector_string_dtor std__vector_std__string__dtor


#ifdef __cplusplus
}
#endif
