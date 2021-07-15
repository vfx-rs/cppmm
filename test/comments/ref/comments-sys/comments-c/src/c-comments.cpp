#include "c-comments_private.h"


#include <stdexcept>

unsigned int comments__Class_method(
    comments_Class_t * this_)
{
    try {
        (to_cpp(this_)) -> method();
        return 0;
    } catch (std::exception& e) {
        TLG_EXCEPTION_STRING = e.what();
        return -1;
    }
}

unsigned int comments_function()
{
    try {
        comments::function();
        return 0;
    } catch (std::exception& e) {
        TLG_EXCEPTION_STRING = e.what();
        return -1;
    }
}

