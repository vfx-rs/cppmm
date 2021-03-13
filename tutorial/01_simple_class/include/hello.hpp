#pragma once

#include <iostream>

namespace hello {

class Hello {
public:
    void hello() const { std::cout << "Hello, world!\n"; }
};

} // namespace hello
