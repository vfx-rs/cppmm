#pragma once

namespace imath {

template <typename T> struct Matrix44 {
    T data[4][4];

    Matrix44(const T a[4][4]) {
        for (int r = 0; r < 4; ++r) {
            for (int c = 0; c < 4; ++c) {
                data[r][c] = a[r][c];
            }
        }
    }
};

} // namespace imath
