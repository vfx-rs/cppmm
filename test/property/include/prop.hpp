#pragma once

#include <stdint.h>

namespace prop {

struct Bar {
    int baz;
};

struct Foo {
    int a;
    float b;
    float c;
    Bar bar;
    uint64_t u;

    static void bum(){}
};

uint64_t fuz(uint64_t& a, uint64_t* b, uint64_t c) {return 0;}

} // namespace prop
