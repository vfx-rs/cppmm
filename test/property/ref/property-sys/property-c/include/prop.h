#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct prop__Bar_t_s {
    char _unused;
} __attribute__((aligned(4))) prop__Bar_t;
typedef prop__Bar_t prop_Bar_t;

typedef struct prop__Foo_t_s {
    char _unused;
} __attribute__((aligned(4))) prop__Foo_t;
typedef prop__Foo_t prop_Foo_t;


unsigned int prop__Foo_get_a(
    prop_Foo_t const * this_
    , int const * * return_);
#define prop_Foo_get_a prop__Foo_get_a


unsigned int prop__Foo_set_a(
    prop_Foo_t * this_
    , int const * value);
#define prop_Foo_set_a prop__Foo_set_a


unsigned int prop__Foo_get_b(
    prop_Foo_t const * this_
    , float const * * return_);
#define prop_Foo_get_b prop__Foo_get_b


unsigned int prop__Foo_set_b(
    prop_Foo_t * this_
    , float const * value);
#define prop_Foo_set_b prop__Foo_set_b


unsigned int prop__Foo_get_bar(
    prop_Foo_t const * this_
    , prop_Bar_t const * * return_);
#define prop_Foo_get_bar prop__Foo_get_bar


unsigned int prop__Foo_set_bar(
    prop_Foo_t * this_
    , prop_Bar_t const * value);
#define prop_Foo_set_bar prop__Foo_set_bar


#ifdef __cplusplus
}
#endif
