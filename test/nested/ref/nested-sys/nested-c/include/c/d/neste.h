#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct nest__NestCDE_t_s {
    int cd;
} __attribute__((aligned(4))) nest__NestCDE_t;
typedef nest__NestCDE_t nest_NestCDE_t;


unsigned int nest__NestCDE_do_something(
    nest_NestCDE_t * this_);
#define nest_NestCDE_do_something nest__NestCDE_do_something


#ifdef __cplusplus
}
#endif
