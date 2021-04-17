#include <std_vector_private.h>

#include <new>


void std__vector_std__string__vector(
    std_vector_string_t * this_)
{
    new (this_) std::vector<std::string>();
}

void std__vector_std__string__dtor(
    std_vector_string_t * this_)
{
    (to_cpp(this_)) -> std::vector<std::__cxx11::basic_string<char>, std::allocator<std::__cxx11::basic_string<char> > >::~vector();
}
