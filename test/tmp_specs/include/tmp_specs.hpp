#pragma once

#include <string>

namespace specs {

template <typename T> struct Attribute {
    T t;
    const T& value();
    static void do_something(T& v){}
    Attribute(){}
};

using IntAttribute = Attribute<int>;
using FloatAttribute = Attribute<float>;

struct Specs {
    void doSomething(int) {}
    template <typename T> T* findAttribute(const char* name) { return nullptr; }
    template <typename T> const T* findAttribute(const char* name) const {
        return nullptr;
    }
};

} // namespace specs
