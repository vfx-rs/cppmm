#include <fstream>

#include "c-ex.hpp"

int main() {
    std::ofstream os("abigen.txt");

    abi_gen_c_ex(os);
}
