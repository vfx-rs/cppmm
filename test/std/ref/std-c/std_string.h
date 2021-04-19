#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct std____cxx11__basic_string_char__t_s {
    char data[32];
} __attribute__((aligned(8))) std____cxx11__basic_string_char__t;
typedef std____cxx11__basic_string_char__t std___cxx11_string_t;

typedef struct std__vector_std__string__t_s {
    char data[24];
} __attribute__((aligned(8))) std__vector_std__string__t;
typedef std__vector_std__string__t std_vector_string_t;



std___cxx11_string_t * std____cxx11__basic_string_char__assign(
    std___cxx11_string_t * this_
    , char const * s
    , unsigned long count);
#define std___cxx11_string_assign std____cxx11__basic_string_char__assign


char const * std____cxx11__basic_string_char__c_str(
    std___cxx11_string_t const * this_);
#define std___cxx11_string_c_str std____cxx11__basic_string_char__c_str










void std__vector_std__string__vector(
    std_vector_string_t * this_);
#define std_vector_string_vector std__vector_std__string__vector


void std__vector_std__string__dtor(
    std_vector_string_t * this_);
#define std_vector_string_dtor std__vector_std__string__dtor









#ifdef __cplusplus
}
#endif
