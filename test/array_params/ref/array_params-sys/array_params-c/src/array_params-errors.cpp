#include "array_params-errors.h"
#include "array_params-errors-private.h"

thread_local std::string TLG_EXCEPTION_STRING;

ARRAY_PARAMS_CPPMM_API const char* array_params_get_exception_string() {
    return TLG_EXCEPTION_STRING.c_str();
}

