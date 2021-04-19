#include <c-usestd_private.h>

#include <std_string_private.h>

void _takes_string(
    std___cxx11_string_t const * s)
{
    usestd::takes_string(to_cpp_ref(s));
}
void _takes_vector_string(
    std_vector_string_t const * v)
{
    usestd::takes_vector_string(to_cpp_ref(v));
}
