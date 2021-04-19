#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct std____cxx11__basic_string_char__t_s {
    char data[32];
} __attribute__((aligned(8))) std____cxx11__basic_string_char__t;
typedef std____cxx11__basic_string_char__t std___cxx11_string_t;



void std____cxx11__basic_string_char__basic_string(
    std___cxx11_string_t * this_);
#define std___cxx11_string_basic_string std____cxx11__basic_string_char__basic_string


void std____cxx11__basic_string_char__basic_string_1(
    std___cxx11_string_t * this_
    , std___cxx11_string_t const * rhs);
#define std___cxx11_string_basic_string_1 std____cxx11__basic_string_char__basic_string_1


std___cxx11_string_t * std____cxx11__basic_string_char__assign(
    std___cxx11_string_t * this_
    , char const * s
    , unsigned long count);
#define std___cxx11_string_assign std____cxx11__basic_string_char__assign


char const * std____cxx11__basic_string_char__c_str(
    std___cxx11_string_t const * this_);
#define std___cxx11_string_c_str std____cxx11__basic_string_char__c_str










#ifdef __cplusplus
}
#endif
