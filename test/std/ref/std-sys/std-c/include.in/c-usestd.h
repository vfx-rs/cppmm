#pragma once
#include "std-api-export.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct std__string_t_s std__string_t;
typedef std__string_t std_string_t;
typedef struct std__vector_std__string__t_s std__vector_std__string__t;
typedef std__vector_std__string__t std_vector_string_t;

STD_CPPMM_API unsigned int usestd_takes_string(
    std_string_t const * s);

STD_CPPMM_API unsigned int usestd_takes_vector_string(
    std_vector_string_t const * v);

#ifdef __cplusplus
}
#endif
