#pragma once

#include <stdexcept>

namespace ex {

struct Struct {

    void m1() { throw std::runtime_error("It's runtime, this is an error!"); }

    float m2(float b) {
        if (b < 0.0f) {
            throw std::runtime_error("It's runtime, this is an error!");
        } else {
            throw std::logic_error(
                "Your logic is bad. And you should feel bad");
        }
    }

    float m3(int a) const noexcept { return 1.0f; }
    float m4(int a) const { return 1.0f; }

private:
    bool _first = true;
};

float f1(int a) {
    throw std::invalid_argument("Your argument is invalid. I win.");
}

void f2() { throw std::invalid_argument("Your argument is invalid. I win."); }

} // namespace ex
