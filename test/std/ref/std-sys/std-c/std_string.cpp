#include <std_string_private.h>

#include <new>

#include <stdexcept>

unsigned int std____cxx11__basic_string_char__sizeof()
{
        return sizeof(std::__cxx11::basic_string<char>);
}

unsigned int std____cxx11__basic_string_char__alignof()
{
        return alignof(std::__cxx11::basic_string<char>);
}

unsigned int std____cxx11__basic_string_char__assign(
    std_string_t * this_
    , std_string_t * * return_
    , char const * s
    , unsigned long count)
{
    try {
        to_c(return_, (to_cpp(this_)) -> assign(s, count));
        return 0;
    } catch (std::exception& e) {
        TLG_EXCEPTION_STRING = e.what();
        return -1;
    }
}

unsigned int std____cxx11__basic_string_char__c_str(
    std_string_t const * this_
    , char const * * return_)
{
        *(return_) = (to_cpp(this_)) -> c_str();
        return 0;
}

unsigned int std__vector_std__string__sizeof()
{
        return sizeof(std::vector<std::string>);
}

unsigned int std__vector_std__string__alignof()
{
        return alignof(std::vector<std::string>);
}

unsigned int std__vector_std__string__ctor(
    std_vector_string_t * this_)
{
    try {
        new (this_) std::vector<std::string>();
        return 0;
    } catch (std::exception& e) {
        TLG_EXCEPTION_STRING = e.what();
        return -1;
    }
}

unsigned int std__vector_std__string__dtor(
    std_vector_string_t * this_)
{
        (to_cpp(this_)) -> std::vector<std::__cxx11::basic_string<char>, std::allocator<std::__cxx11::basic_string<char> > >::~vector();
        return 0;
}

