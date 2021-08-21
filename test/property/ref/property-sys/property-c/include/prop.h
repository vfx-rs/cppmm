#pragma once
#include "property-api-export.h"

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct prop__Bar_t_s {
    char _unused;
} PROPERTY_CPPMM_ALIGN(4) prop__Bar_t;
typedef prop__Bar_t prop_Bar_t;

typedef struct prop__Foo_t_s {
    char _unused;
} PROPERTY_CPPMM_ALIGN(8) prop__Foo_t;
typedef prop__Foo_t prop_Foo_t;


PROPERTY_CPPMM_API unsigned int prop__Foo_bum();
#define prop_Foo_bum prop__Foo_bum


PROPERTY_CPPMM_API unsigned int prop__Foo_get_a(
    prop_Foo_t const * this_
    , int const * * return_);
#define prop_Foo_get_a prop__Foo_get_a


PROPERTY_CPPMM_API unsigned int prop__Foo_set_a(
    prop_Foo_t * this_
    , int const * value);
#define prop_Foo_set_a prop__Foo_set_a


PROPERTY_CPPMM_API unsigned int prop__Foo_get_b(
    prop_Foo_t const * this_
    , float const * * return_);
#define prop_Foo_get_b prop__Foo_get_b


PROPERTY_CPPMM_API unsigned int prop__Foo_set_b(
    prop_Foo_t * this_
    , float const * value);
#define prop_Foo_set_b prop__Foo_set_b


PROPERTY_CPPMM_API unsigned int prop__Foo_get_bar(
    prop_Foo_t const * this_
    , prop_Bar_t const * * return_);
#define prop_Foo_get_bar prop__Foo_get_bar


PROPERTY_CPPMM_API unsigned int prop__Foo_set_bar(
    prop_Foo_t * this_
    , prop_Bar_t const * value);
#define prop_Foo_set_bar prop__Foo_set_bar


PROPERTY_CPPMM_API unsigned int prop__Foo_get_u(
    prop_Foo_t const * this_
    , uint64_t const * * return_);
#define prop_Foo_get_u prop__Foo_get_u


PROPERTY_CPPMM_API unsigned int prop__Foo_set_u(
    prop_Foo_t * this_
    , uint64_t const * value);
#define prop_Foo_set_u prop__Foo_set_u


PROPERTY_CPPMM_API unsigned int prop_fuz(
    uint64_t * return_
    , uint64_t * a
    , uint64_t * b
    , uint64_t c);

#ifdef __cplusplus
}
#endif
