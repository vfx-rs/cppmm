#include <std_vector_private.h>

#include <new>

void std__vector_std__string__vector(
    std_vector_string_t * * this_)
{
    *this_ = to_c(new std::vector<std::string>());
}
void std__vector_std__string__dtor(
    std_vector_string_t * this_)
{
    delete this_;
}
