#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct nest__NestAE_t_s {
    int a;
} __attribute__((aligned(4))) nest__NestAE_t;
typedef nest__NestAE_t nest_NestAE_t;


unsigned int nest__NestAE_do_something(
    nest_NestAE_t * this_);
#define nest_NestAE_do_something nest__NestAE_do_something


#ifdef __cplusplus
}
#endif
