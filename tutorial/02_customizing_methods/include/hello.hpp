#pragma once

#include <iostream>

namespace hello {

class Hello {
public:
    void hello(const char* msg) const {
        std::cout << "Hello, " << msg << "!\n";
    }
    void hello(const int msg) const { std::cout << "Hello, " << msg << "!\n"; }
    void hello(const float msg) const {
        std::cout << "Hello, " << msg << "!\n";
    }
};

} // namespace hello
