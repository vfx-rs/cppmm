#pragma once
#include "dtor-api-export.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct std____cxx11__basic_string_char__t_s {
    char data[32];
} DTOR_CPPMM_ALIGN(8) std____cxx11__basic_string_char__t;
typedef std____cxx11__basic_string_char__t std___cxx11_string_t;


/** returns the size of this type in bytes */
DTOR_CPPMM_API unsigned int std____cxx11__basic_string_char__sizeof();
#define std___cxx11_string_sizeof std____cxx11__basic_string_char__sizeof


/** returns the size of this type in bytes */
DTOR_CPPMM_API unsigned int std____cxx11__basic_string_char__alignof();
#define std___cxx11_string_alignof std____cxx11__basic_string_char__alignof


DTOR_CPPMM_API unsigned int std____cxx11__basic_string_char__ctor(
    std___cxx11_string_t * this_);
#define std___cxx11_string_ctor std____cxx11__basic_string_char__ctor


DTOR_CPPMM_API unsigned int std____cxx11__basic_string_char__copy(
    std___cxx11_string_t * this_
    , std___cxx11_string_t const * rhs);
#define std___cxx11_string_copy std____cxx11__basic_string_char__copy


DTOR_CPPMM_API unsigned int std____cxx11__basic_string_char__dtor(
    std___cxx11_string_t * this_);
#define std___cxx11_string_dtor std____cxx11__basic_string_char__dtor


DTOR_CPPMM_API unsigned int std____cxx11__basic_string_char__assign(
    std___cxx11_string_t * this_
    , std___cxx11_string_t * * return_
    , char const * s
    , size_t count);
#define std___cxx11_string_assign std____cxx11__basic_string_char__assign


DTOR_CPPMM_API unsigned int std____cxx11__basic_string_char__c_str(
    std___cxx11_string_t const * this_
    , char const * * return_);
#define std___cxx11_string_c_str std____cxx11__basic_string_char__c_str


#ifdef __cplusplus
}
#endif
