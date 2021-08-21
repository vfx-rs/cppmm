#include "c-usestd_private.h"

#include "std_string_private.h"

#include <stdexcept>

STD_CPPMM_API unsigned int usestd_takes_string(
    std_string_t const * s)
{
    try {
        usestd::takes_string(to_cpp_ref(s));
        return 0;
    } catch (std::exception& e) {
        TLG_EXCEPTION_STRING = e.what();
        return -1;
    }
}

STD_CPPMM_API unsigned int usestd_takes_vector_string(
    std_vector_string_t const * v)
{
    try {
        usestd::takes_vector_string(to_cpp_ref(v));
        return 0;
    } catch (std::exception& e) {
        TLG_EXCEPTION_STRING = e.what();
        return -1;
    }
}

