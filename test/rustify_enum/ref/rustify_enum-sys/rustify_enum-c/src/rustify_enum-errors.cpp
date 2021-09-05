#include "rustify_enum-errors.h"
#include "rustify_enum-errors-private.h"

thread_local std::string TLG_EXCEPTION_STRING;

RUSTIFY_ENUM_CPPMM_API const char* rustify_enum_get_exception_string() {
    return TLG_EXCEPTION_STRING.c_str();
}

