#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct std____cxx11__basic_string_char__t_s {
    char _unused;
} __attribute__((aligned(8))) std____cxx11__basic_string_char__t;
typedef std____cxx11__basic_string_char__t std_string_t;

typedef struct std__vector_std__string__t_s {
    char _unused;
} __attribute__((aligned(8))) std__vector_std__string__t;
typedef std__vector_std__string__t std_vector_string_t;



unsigned int std____cxx11__basic_string_char__assign(
    std_string_t * this_
    , std_string_t * * return_
    , char const * s
    , unsigned long count);
#define std_string_assign std____cxx11__basic_string_char__assign


unsigned int std____cxx11__basic_string_char__c_str(
    std_string_t const * this_
    , char const * * return_);
#define std_string_c_str std____cxx11__basic_string_char__c_str










unsigned int std__vector_std__string__vector(
    std_vector_string_t * * this_);
#define std_vector_string_vector std__vector_std__string__vector


unsigned int std__vector_std__string__dtor(
    std_vector_string_t * this_);
#define std_vector_string_dtor std__vector_std__string__dtor









#ifdef __cplusplus
}
#endif
