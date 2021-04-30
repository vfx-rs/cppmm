#include <std_string_private.h>

#include <new>

void std____cxx11__basic_string_char__ctor(
    std___cxx11_string_t * * this_)
{
    *this_ = to_c(new std::__cxx11::basic_string<char>());
}
void std____cxx11__basic_string_char__copy(
    std___cxx11_string_t * * this_
    , std___cxx11_string_t const * rhs)
{
    *this_ = to_c(new std::__cxx11::basic_string<char>(to_cpp_ref(rhs)));
}
void std____cxx11__basic_string_char__dtor(
    std___cxx11_string_t * this_)
{
    delete this_;
}
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
