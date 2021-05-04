#include "/home/anders/code/cppmm/build/test/array_params/output/array_params-c/array_params-errors.h"
#include "/home/anders/code/cppmm/build/test/array_params/output/array_params-c/array_params-errors-private.h"

thread_local std::string TLG_EXCEPTION_STRING;

const char* array_params_get_exception_string() {
    return TLG_EXCEPTION_STRING.c_str();
}

