#include <fstream>

#include "imath_vec.hpp"
#include "imath_box.hpp"

int main() {
    std::ofstream os("abigen.txt");

    abi_gen_imath_vec(os);
    abi_gen_imath_box(os);
}
