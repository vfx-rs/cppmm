#pragma once
#include "tmp_specs-api-export.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct std____cxx11__basic_string_char__t_s std____cxx11__basic_string_char__t;
typedef std____cxx11__basic_string_char__t std_string_t;

typedef struct specs__Attribute_int__t_s {
    char _unused;
} TMP_SPECS_CPPMM_ALIGN(4) specs__Attribute_int__t;
typedef specs__Attribute_int__t specs_IntAttribute_t;

typedef struct specs__Attribute_float__t_s {
    char _unused;
} TMP_SPECS_CPPMM_ALIGN(4) specs__Attribute_float__t;
typedef specs__Attribute_float__t specs_FloatAttribute_t;

typedef struct specs__Attribute_std__string__t_s {
    char _unused;
} TMP_SPECS_CPPMM_ALIGN(8) specs__Attribute_std__string__t;
typedef specs__Attribute_std__string__t specs_StringAttribute_t;

typedef struct specs__Specs_t_s {
    char _unused;
} TMP_SPECS_CPPMM_ALIGN(1) specs__Specs_t;
typedef specs__Specs_t specs_Specs_t;


TMP_SPECS_CPPMM_API unsigned int specs__Attribute_int__value(
    specs_IntAttribute_t * this_
    , int const * * return_);
#define specs_IntAttribute_value specs__Attribute_int__value


TMP_SPECS_CPPMM_API unsigned int specs__Attribute_int__do_something(
    int * v);
#define specs_IntAttribute_do_something specs__Attribute_int__do_something


TMP_SPECS_CPPMM_API unsigned int specs__Attribute_int__ctor(
    specs_IntAttribute_t * * this_);
#define specs_IntAttribute_ctor specs__Attribute_int__ctor


TMP_SPECS_CPPMM_API unsigned int specs__Attribute_float__value(
    specs_FloatAttribute_t * this_
    , float const * * return_);
#define specs_FloatAttribute_value specs__Attribute_float__value


TMP_SPECS_CPPMM_API unsigned int specs__Attribute_float__do_something(
    float * v);
#define specs_FloatAttribute_do_something specs__Attribute_float__do_something


TMP_SPECS_CPPMM_API unsigned int specs__Attribute_float__ctor(
    specs_FloatAttribute_t * * this_);
#define specs_FloatAttribute_ctor specs__Attribute_float__ctor


TMP_SPECS_CPPMM_API unsigned int specs__Attribute_std__string__value(
    specs_StringAttribute_t * this_
    , std_string_t const * * return_);
#define specs_StringAttribute_value specs__Attribute_std__string__value


TMP_SPECS_CPPMM_API unsigned int specs__Attribute_std__string__do_something(
    std_string_t * v);
#define specs_StringAttribute_do_something specs__Attribute_std__string__do_something


TMP_SPECS_CPPMM_API unsigned int specs__Attribute_std__string__ctor(
    specs_StringAttribute_t * * this_);
#define specs_StringAttribute_ctor specs__Attribute_std__string__ctor


TMP_SPECS_CPPMM_API unsigned int specs__Attribute_std__string__dtor(
    specs_StringAttribute_t * this_);
#define specs_StringAttribute_dtor specs__Attribute_std__string__dtor


TMP_SPECS_CPPMM_API unsigned int specs__Specs_findAttribute_int(
    specs_Specs_t * this_
    , specs_IntAttribute_t * * return_
    , char const * name);
#define specs_Specs_findAttribute_int specs__Specs_findAttribute_int


TMP_SPECS_CPPMM_API unsigned int specs__Specs_findAttribute_float(
    specs_Specs_t * this_
    , specs_FloatAttribute_t * * return_
    , char const * name);
#define specs_Specs_findAttribute_float specs__Specs_findAttribute_float


TMP_SPECS_CPPMM_API unsigned int specs__Specs_findAttribute_int_const(
    specs_Specs_t const * this_
    , specs_IntAttribute_t const * * return_
    , char const * name);
#define specs_Specs_findAttribute_int_const specs__Specs_findAttribute_int_const


TMP_SPECS_CPPMM_API unsigned int specs__Specs_findAttribute_float_const(
    specs_Specs_t const * this_
    , specs_FloatAttribute_t const * * return_
    , char const * name);
#define specs_Specs_findAttribute_float_const specs__Specs_findAttribute_float_const


#ifdef __cplusplus
}
#endif
