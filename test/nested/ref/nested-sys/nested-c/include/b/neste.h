#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct nest__NestBE_t_s {
    int b;
} __attribute__((aligned(4))) nest__NestBE_t;
typedef nest__NestBE_t nest_NestBE_t;


unsigned int nest__NestBE_do_something(
    nest_NestBE_t * this_);
#define nest_NestBE_do_something nest__NestBE_do_something


#ifdef __cplusplus
}
#endif
