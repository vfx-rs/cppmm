#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace containers {

class CustomVT {
    int a;
    int b;
};

class CustomOB {
    int a;
};

class CustomOP {
    int a;
};

class CustomElement {
    int a;
    int b;
};

class Containers {
public:
    void takes_const_vec_string_ref(const std::vector<std::string>& vec) {
        std::cout << vec.size();
    }
    void takes_const_vec_custom_ref(const std::vector<CustomElement>& vec) {}
    void testint(int a) { std::cout << a; }
};

} // namespace containers
