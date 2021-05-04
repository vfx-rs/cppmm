#include "/home/anders/code/cppmm/build/test/imath/output/imath-c/imath-errors.h"
#include "/home/anders/code/cppmm/build/test/imath/output/imath-c/imath-errors-private.h"

thread_local std::string TLG_EXCEPTION_STRING;

const char* imath_get_exception_string() {
    return TLG_EXCEPTION_STRING.c_str();
}

