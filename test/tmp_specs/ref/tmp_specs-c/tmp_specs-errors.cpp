#include "/home/anders/code/cppmm/build/test/tmp_specs/output/tmp_specs-c/tmp_specs-errors.h"
#include "/home/anders/code/cppmm/build/test/tmp_specs/output/tmp_specs-c/tmp_specs-errors-private.h"

thread_local std::string TLG_EXCEPTION_STRING;

const char* tmp_specs_get_exception_string() {
    return TLG_EXCEPTION_STRING.c_str();
}

