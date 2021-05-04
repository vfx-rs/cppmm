#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct std____cxx11__basic_string_char__t_s std____cxx11__basic_string_char__t;
typedef std____cxx11__basic_string_char__t std___cxx11_string_t;
typedef struct std__vector_std__string__t_s std__vector_std__string__t;
typedef std__vector_std__string__t std_vector_string_t;


unsigned int usestd_takes_string(
    std___cxx11_string_t const * s);

unsigned int usestd_takes_vector_string(
    std_vector_string_t const * v);
#ifdef __cplusplus
}
#endif
