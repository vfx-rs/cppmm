#include <fstream>

#include "c-fptr.hpp"

int main() {
    std::ofstream os("abigen.txt");

    abi_gen_c_fptr(os);
}
