#pragma once

namespace DN {

namespace v2_2 {

class Class {
public:
    int i;
    float f;

    enum Enum { One, Two, Three };

    struct Struct {
        int a;
        float b;
        void structMethod() {}
    };
};

void someFunction() {}

} // namespace v2_2

using namespace v2_2;

} // namespace DN
