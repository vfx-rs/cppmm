#include "c-fptr_private.h"


#include <stdexcept>

unsigned int fptr_takes_ages(
    fptr_ProgressCallback_t cb
    , void * data)
{
    try {
        fptr::takes_ages(cb, data);
        return 0;
    } catch (std::exception& e) {
        TLG_EXCEPTION_STRING = e.what();
        return -1;
    }
}

