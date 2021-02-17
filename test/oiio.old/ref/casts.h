#pragma once
#include <string.h>
// Macro to define short conversion functions between C and C++ API types to
// save us from eye-gougingly verbose casts everywhere
#define CPPMM_DEFINE_POINTER_CASTS(CPPTYPE, CTYPE)          \
CPPTYPE* to_cpp(CTYPE* ptr) {                               \
    return reinterpret_cast<CPPTYPE*>(ptr);                 \
}                                                           \
                                                            \
const CPPTYPE* to_cpp(const CTYPE* ptr) {                   \
    return reinterpret_cast<const CPPTYPE*>(ptr);           \
}                                                           \
                                                            \
CTYPE* to_c(CPPTYPE* ptr) {                                 \
    return reinterpret_cast<CTYPE*>(ptr);                   \
}                                                           \
                                                            \
const CTYPE* to_c(const CPPTYPE* ptr) {                     \
    return reinterpret_cast<const CTYPE*>(ptr);             \
}                                                           \
                                                            \

template <typename TO, typename FROM>
TO bit_cast(FROM f) {
    static_assert(sizeof(TO) == sizeof(FROM), "sizes do not match");
    static_assert(alignof(TO) == alignof(FROM), "alignments do not match");

    TO result;
    memcpy((void*)&result, (void*)&f, sizeof(f));
    return result;
}

void safe_strcpy(char* dst, const std::string& str, int buffer_size) {
    size_t last_char = std::min((size_t)buffer_size - 1, str.size());
    memcpy(dst, str.c_str(), last_char);
    dst[last_char] = '\0';
}
    