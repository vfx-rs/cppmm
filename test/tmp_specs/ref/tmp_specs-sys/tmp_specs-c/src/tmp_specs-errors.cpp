#include "tmp_specs-errors.h"
#include "tmp_specs-errors-private.h"

thread_local std::string TLG_EXCEPTION_STRING;

const char* TMP_SPECS_CPPMM_API tmp_specs_get_exception_string() {
    return TLG_EXCEPTION_STRING.c_str();
}

