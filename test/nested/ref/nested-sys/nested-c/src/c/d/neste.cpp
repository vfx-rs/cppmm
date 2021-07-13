#include "neste_private.h"


#include <stdexcept>

unsigned int nest__NestCDE_do_something(
    nest_NestCDE_t * this_)
{
    try {
        (to_cpp(this_)) -> do_something();
        return 0;
    } catch (std::exception& e) {
        TLG_EXCEPTION_STRING = e.what();
        return -1;
    }
}

