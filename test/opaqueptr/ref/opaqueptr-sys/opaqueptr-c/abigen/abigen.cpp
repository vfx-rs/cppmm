#include <fstream>

#include "c-optr.hpp"

int main() {
    std::ofstream os("abigen.txt");

    abi_gen_c_optr(os);
}
