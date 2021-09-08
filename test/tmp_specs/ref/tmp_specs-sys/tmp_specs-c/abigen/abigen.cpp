#include <fstream>

#include "c-specs.hpp"
#include "std_string.hpp"

int main() {
    std::ofstream os("abigen.txt");

    abi_gen_c_specs(os);
    abi_gen_std_string(os);
}
