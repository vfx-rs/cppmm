#include <fstream>

#include "c-array_params.hpp"

int main() {
    std::ofstream os("abigen.txt");

    abi_gen_c_array_params(os);
}
