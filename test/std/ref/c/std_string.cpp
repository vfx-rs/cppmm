#include <std_string.h>

#include <cppmm_bind.hpp>
#include <string>
#include <std_string_private.h>


std___cxx11_string * std___cxx11_string_assign(
    std___cxx11_string * self
    , char * s
    , unsigned long count)
{
    return to_c((to_cpp(self)) -> assign(to_cpp(s), count));
}

char * std___cxx11_string_c_str(
    std___cxx11_string const * self)
{
    return to_c((to_cpp(self)) -> c_str());
}
