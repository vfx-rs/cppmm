#pragma once

#include <memory>
#include <stdio.h>

namespace foo {

struct Foo {
    Foo() { printf("Foo()\n"); }
    ~Foo() { printf("~Foo()\n"); }

    static std::unique_ptr<Foo> create() { return std::make_unique<Foo>(); }
};

} // namespace foo
