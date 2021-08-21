#include "c-dn_private.h"


#include <stdexcept>

DEEP_NAMESPACE_CPPMM_API unsigned int DN__v2_2__Class__Struct_structMethod(
    DN_Class_Struct_t * this_)
{
    try {
        (to_cpp(this_)) -> structMethod();
        return 0;
    } catch (std::exception& e) {
        TLG_EXCEPTION_STRING = e.what();
        return -1;
    }
}

DEEP_NAMESPACE_CPPMM_API unsigned int DN_v2_2_someFunction()
{
    try {
        DN::v2_2::someFunction();
        return 0;
    } catch (std::exception& e) {
        TLG_EXCEPTION_STRING = e.what();
        return -1;
    }
}

