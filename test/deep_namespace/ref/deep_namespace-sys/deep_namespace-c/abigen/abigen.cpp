#include <fstream>

#include "c-dn.hpp"

int main() {
    std::ofstream os("abigen.txt");

    abi_gen_c_dn(os);
}
