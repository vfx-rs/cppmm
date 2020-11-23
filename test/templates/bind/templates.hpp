#pragma once

#include <cmath>
#include <iostream>

namespace templates {

template <typename T> struct Vector3 {
    Vector3(T x, T y, T z) : x(x), y(y), z(z) {}

    T length() const {
        std::cout << "Vector3<int>::length()" << std::endl;
        return sqrt(x * x + y * y + z * z);
    }

    T x;
    T y;
    T z;
};

/* void takes_spec_short(Vector3<short> v) {} */

template <typename T>
void takes_vector3(Vector3<T>& v){}

template <typename T, typename U>
void takes_two_vector3(Vector3<T>& v, Vector3<U>& w){}

template <typename T, typename U>
void takes_vector3_and_t(Vector3<T>& v, U w) {
}

/* template <> */
/* void takes_vector3(Vector3<float>& v){} */

/* template <> */
/* void takes_vector3(Vector3<int>& v){} */

/* struct Vector2 { */
/*     float x; */
/*     float y; */
/* }; */

/* template <> short Vector3<short>::length() const { */
/*     std::cout << "Vector3<short>::length()" << std::endl; */
/*     return sqrtf(x * x + y * y + z * z); */
/* } */

} // namespace templates
