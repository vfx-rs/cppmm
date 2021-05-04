#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct specs__Attribute_int__t_s {
    char _unused;
} __attribute__((aligned(4))) specs__Attribute_int__t;
typedef specs__Attribute_int__t specs_IntAttribute_t;

typedef struct specs__Attribute_float__t_s {
    char _unused;
} __attribute__((aligned(4))) specs__Attribute_float__t;
typedef specs__Attribute_float__t specs_FloatAttribute_t;

typedef struct specs__Specs_t_s {
    char _unused;
} __attribute__((aligned(1))) specs__Specs_t;
typedef specs__Specs_t specs_Specs_t;



unsigned int specs__Attribute_int__value(
    specs_IntAttribute_t * this_
    , int const * * return_);
#define specs_IntAttribute_value specs__Attribute_int__value











unsigned int specs__Attribute_float__value(
    specs_FloatAttribute_t * this_
    , float const * * return_);
#define specs_FloatAttribute_value specs__Attribute_float__value











unsigned int specs__Specs_findAttribute_int(
    specs_Specs_t * this_
    , specs_IntAttribute_t * * return_
    , char const * name);
#define specs_Specs_findAttribute_int specs__Specs_findAttribute_int


unsigned int specs__Specs_findAttribute_float(
    specs_Specs_t * this_
    , specs_FloatAttribute_t * * return_
    , char const * name);
#define specs_Specs_findAttribute_float specs__Specs_findAttribute_float


unsigned int specs__Specs_findAttribute_int_const(
    specs_Specs_t const * this_
    , specs_IntAttribute_t const * * return_
    , char const * name);
#define specs_Specs_findAttribute_int_const specs__Specs_findAttribute_int_const


unsigned int specs__Specs_findAttribute_float_const(
    specs_Specs_t const * this_
    , specs_FloatAttribute_t const * * return_
    , char const * name);
#define specs_Specs_findAttribute_float_const specs__Specs_findAttribute_float_const










#ifdef __cplusplus
}
#endif
