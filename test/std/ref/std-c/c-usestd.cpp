#include <c-usestd_private.h>

#include <std_string_private.h>

void usestd_takes_string(
    std___cxx11_string_t const * s)
{
    usestd::takes_string(to_cpp_ref(s));
}
void usestd_takes_vector_string(
    std_vector_string_t const * v)
{
    usestd::takes_vector_string(to_cpp_ref(v));
}
