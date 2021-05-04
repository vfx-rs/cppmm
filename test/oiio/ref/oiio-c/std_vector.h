#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct std__vector_std__string__t_s {
    char _unused;
} __attribute__((aligned(8))) std__vector_std__string__t;
typedef std__vector_std__string__t std_vector_string_t;



unsigned int std__vector_std__string__vector(
    std_vector_string_t * * this_);
#define std_vector_string_vector std__vector_std__string__vector


unsigned int std__vector_std__string__dtor(
    std_vector_string_t * this_);
#define std_vector_string_dtor std__vector_std__string__dtor









#ifdef __cplusplus
}
#endif
