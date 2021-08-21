#include "opaqueptr-errors.h"
#include "opaqueptr-errors-private.h"

thread_local std::string TLG_EXCEPTION_STRING;

const char* OPAQUEPTR_CPPMM_API opaqueptr_get_exception_string() {
    return TLG_EXCEPTION_STRING.c_str();
}

