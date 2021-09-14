#include "mimpl-errors.h"
#include "mimpl-errors-private.h"

thread_local std::string TLG_EXCEPTION_STRING;

MIMPL_CPPMM_API const char* mimpl_get_exception_string() {
    return TLG_EXCEPTION_STRING.c_str();
}

