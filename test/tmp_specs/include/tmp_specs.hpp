#pragma once

namespace specs {

template <typename T> struct Attribute { T t; };

using IntAttribute = Attribute<int>;
using FloatAttribute = Attribute<float>;

struct Specs {
    void doSomething(int) {}
    template <typename T> T* findAttribute(const char* name) { return nullptr; }
};

} // namespace specs
