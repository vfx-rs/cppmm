#include "opaquebytes-errors.h"
#include "opaquebytes-errors-private.h"

thread_local std::string TLG_EXCEPTION_STRING;

OPAQUEBYTES_CPPMM_API const char* opaquebytes_get_exception_string() {
    return TLG_EXCEPTION_STRING.c_str();
}

