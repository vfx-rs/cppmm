#include <fstream>

#include "c-dtor.hpp"
#include "std_string.hpp"

int main() {
    std::ofstream os("abigen.txt");

    abi_gen_c_dtor(os);
    abi_gen_std_string(os);
}
