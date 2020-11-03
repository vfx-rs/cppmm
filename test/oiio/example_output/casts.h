#pragma once

// Macro to define short conversion functions between C and C++ API types to
// save us from eye-gougingly verbose casts everywhere
#define CPPMM_DEFINE_POINTER_CASTS(CPPTYPE, CTYPE)          \
CPPTYPE* to_cpp(CTYPE* ptr) {                               \
    return retinterpret_cast<CPPTYPE*>(ptr)                 \
}                                                           \
                                                            \
const CPPTYPE* to_cpp(const CTYPE* ptr) {                   \
    return retinterpret_cast<const CPPTYPE*>(ptr)           \
}                                                           \
                                                            \
CTYPE* to_c(CPPTYPE* ptr) {                                 \
    return retinterpret_cast<CTYPE*>(ptr)                   \
}                                                           \
                                                            \
const CTYPE* to_c(const CPPTYPE* ptr) {                     \
    return retinterpret_cast<const CTYPE*>(ptr)             \
}                                                           \
                                                            \

    