#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct std____cxx11__basic_string_char__t_s {
    char data[32];
} __attribute__((aligned(8))) std____cxx11__basic_string_char__t;
typedef std____cxx11__basic_string_char__t std___cxx11_string_t;



/** returns the size of this type in bytes */
unsigned int std____cxx11__basic_string_char__sizeof();
#define std___cxx11_string_sizeof std____cxx11__basic_string_char__sizeof


/** returns the size of this type in bytes */
unsigned int std____cxx11__basic_string_char__alignof();
#define std___cxx11_string_alignof std____cxx11__basic_string_char__alignof


unsigned int std____cxx11__basic_string_char__ctor(
    std___cxx11_string_t * this_);
#define std___cxx11_string_ctor std____cxx11__basic_string_char__ctor


unsigned int std____cxx11__basic_string_char__copy(
    std___cxx11_string_t * this_
    , std___cxx11_string_t const * rhs);
#define std___cxx11_string_copy std____cxx11__basic_string_char__copy


unsigned int std____cxx11__basic_string_char__dtor(
    std___cxx11_string_t * this_);
#define std___cxx11_string_dtor std____cxx11__basic_string_char__dtor


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
