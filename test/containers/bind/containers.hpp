#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace containers {

class CustomVT {
public:
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
    static void takes_const_vec_string_ref(const std::vector<std::string>& vec) {
        for (const auto& s: vec) {
            std::cout << s << std::endl;
        }
    }

    static std::vector<std::string> returns_vec_string() {
        return std::vector<std::string>{"one", "two", "three"};
    }

    static void takes_mut_vec_string_ref(std::vector<std::string>& vec) {
        vec.push_back("four");
        vec.push_back("five");
        vec.push_back("six");
    }

    void takes_const_vec_custom_ref(const std::vector<CustomElement>& vec) {}
    void testint(int a) { std::cout << a; }
};

} // namespace containers
