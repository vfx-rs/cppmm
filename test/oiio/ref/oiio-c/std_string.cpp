#include <std_string_private.h>

#include <new>

unsigned int std____cxx11__basic_string_char__basic_string(
    std___cxx11_string_t * * this_)
{
    try {
        to_c(this_, new std::__cxx11::basic_string<char>());
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int std____cxx11__basic_string_char__basic_string_1(
    std___cxx11_string_t * * this_
    , std___cxx11_string_t const * rhs)
{
    try {
        to_c(this_, new std::__cxx11::basic_string<char>(to_cpp_ref(rhs)));
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int std____cxx11__basic_string_char__assign(
    std___cxx11_string_t * this_
    , std___cxx11_string_t * * return_
    , char const * s
    , unsigned long count)
{
    try {
        to_c(return_, (to_cpp(this_)) -> assign(s, count));
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int std____cxx11__basic_string_char__c_str(
    std___cxx11_string_t const * this_
    , char const * * return_)
{
    try {
        *(return_) = (to_cpp(this_)) -> c_str();
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
