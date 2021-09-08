#include "property-errors.h"
#include "property-errors-private.h"

thread_local std::string TLG_EXCEPTION_STRING;

PROPERTY_CPPMM_API const char* property_get_exception_string() {
    return TLG_EXCEPTION_STRING.c_str();
}

