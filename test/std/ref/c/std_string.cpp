#include <std_string.h>

#include <cppmm_bind.hpp>
#include <string>

std___cxx11_string *std___cxx11_string_assign(
    std___cxx11_string *self
    , char *s
    , unsigned long count)
{
    return reinterpret_cast<std___cxx11_string *>((reinterpret_cast<std::__cxx11::basic_string<char> *>(self)) -> 
        assign(
             reinterpret_cast<char *>(s)
            ,count
            ));
}
char *std___cxx11_string_c_str(
    std___cxx11_string const *self)
{
    return reinterpret_cast<char *>((reinterpret_cast<std::__cxx11::basic_string<char> const *>(self)) -> 
        c_str());
}
