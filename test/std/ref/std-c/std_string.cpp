#include <std_string_private.h>

#include <new>

std___cxx11_string_t * std____cxx11__basic_string_char__assign(
    std___cxx11_string_t * this_
    , char const * s
    , unsigned long count)
{
    return to_c((to_cpp(this_)) -> assign(s, count));
}
char const * std____cxx11__basic_string_char__c_str(
    std___cxx11_string_t const * this_)
{
    return (to_cpp(this_)) -> c_str();
}
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
