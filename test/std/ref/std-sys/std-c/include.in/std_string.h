#pragma once
#include "std-api-export.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct std__string_t_s {
    char data[%SIZEstd::string%];
} STD_CPPMM_ALIGN(%ALIGNstd::string%) std__string_t;
typedef std__string_t std_string_t;

typedef struct std__vector_std__string__t_s {
    char data[%SIZEstd::vector<std::string>%];
} STD_CPPMM_ALIGN(%ALIGNstd::vector<std::string>%) std__vector_std__string__t;
typedef std__vector_std__string__t std_vector_string_t;


/** returns the size of this type in bytes */
STD_CPPMM_API unsigned int std__string_sizeof();
#define std_string_sizeof std__string_sizeof


/** returns the size of this type in bytes */
STD_CPPMM_API unsigned int std__string_alignof();
#define std_string_alignof std__string_alignof


STD_CPPMM_API unsigned int std__string_assign(
    std_string_t * this_
    , std_string_t * * return_
    , char const * s
    , size_t count);
#define std_string_assign std__string_assign


STD_CPPMM_API unsigned int std__string_c_str(
    std_string_t const * this_
    , char const * * return_);
#define std_string_c_str std__string_c_str


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
