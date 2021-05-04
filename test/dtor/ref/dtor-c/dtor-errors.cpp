#include "/home/anders/code/cppmm/build/test/dtor/output/dtor-c/dtor-errors.h"
#include "/home/anders/code/cppmm/build/test/dtor/output/dtor-c/dtor-errors-private.h"

thread_local std::string TLG_EXCEPTION_STRING;

const char* dtor_get_exception_string() {
    return TLG_EXCEPTION_STRING.c_str();
}

