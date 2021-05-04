#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct std____cxx11__basic_string_char__t_s {
    char _unused;
} __attribute__((aligned(8))) std____cxx11__basic_string_char__t;
typedef std____cxx11__basic_string_char__t std___cxx11_string_t;



unsigned int std____cxx11__basic_string_char__basic_string(
    std___cxx11_string_t * * this_);
#define std___cxx11_string_basic_string std____cxx11__basic_string_char__basic_string


unsigned int std____cxx11__basic_string_char__basic_string_1(
    std___cxx11_string_t * * this_
    , std___cxx11_string_t const * rhs);
#define std___cxx11_string_basic_string_1 std____cxx11__basic_string_char__basic_string_1


unsigned int std____cxx11__basic_string_char__assign(
    std___cxx11_string_t * this_
    , std___cxx11_string_t * * return_
    , char const * s
    , unsigned long count);
#define std___cxx11_string_assign std____cxx11__basic_string_char__assign


unsigned int std____cxx11__basic_string_char__c_str(
    std___cxx11_string_t const * this_
    , char const * * return_);
#define std___cxx11_string_c_str std____cxx11__basic_string_char__c_str










#ifdef __cplusplus
}
#endif
