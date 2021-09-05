#include "opaqueptr-errors.h"
#include "opaqueptr-errors-private.h"

thread_local std::string TLG_EXCEPTION_STRING;

OPAQUEPTR_CPPMM_API const char* opaqueptr_get_exception_string() {
    return TLG_EXCEPTION_STRING.c_str();
}

