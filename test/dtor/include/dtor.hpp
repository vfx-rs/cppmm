#pragma once

#include <string>

namespace dtor {

struct Struct {
    uint64_t a;
    uint64_t b;
    std::string c;

    Struct() : a(1), b(2), c("") {}
    ~Struct() {}
};

}; // namespace dtor
