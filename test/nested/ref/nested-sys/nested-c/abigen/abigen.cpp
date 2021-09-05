#include <fstream>

#include "a/neste.hpp"
#include "b/neste.hpp"
#include "c/d/neste.hpp"

int main() {
    std::ofstream os("abigen.txt");

    abi_gen_a_neste(os);
    abi_gen_b_neste(os);
    abi_gen_c_d_neste(os);
}
