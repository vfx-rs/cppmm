#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/** A test class to make sure we can
grab comments to be injected into C and Rust */
typedef struct comments__Class_t_s {
    char _unused;
} __attribute__((aligned(1))) comments__Class_t;
typedef comments__Class_t comments_Class_t;



/** This method doesn't do anything interesting at all */
unsigned int comments__Class_method(
    comments_Class_t * this_);
#define comments_Class_method comments__Class_method











/** This is a free function that also does nothing interesting */
unsigned int comments_function();
#ifdef __cplusplus
}
#endif
