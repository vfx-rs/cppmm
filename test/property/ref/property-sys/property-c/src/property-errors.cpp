#include "property-errors.h"
#include "property-errors-private.h"

thread_local std::string TLG_EXCEPTION_STRING;

const char* property_get_exception_string() {
    return TLG_EXCEPTION_STRING.c_str();
}

