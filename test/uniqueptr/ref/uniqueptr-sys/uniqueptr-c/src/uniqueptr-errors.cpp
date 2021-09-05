#include "uniqueptr-errors.h"
#include "uniqueptr-errors-private.h"

thread_local std::string TLG_EXCEPTION_STRING;

UNIQUEPTR_CPPMM_API const char* uniqueptr_get_exception_string() {
    return TLG_EXCEPTION_STRING.c_str();
}

