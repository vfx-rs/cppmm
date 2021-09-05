#include <fstream>

#include "c-renum.hpp"

int main() {
    std::ofstream os("abigen.txt");

    abi_gen_c_renum(os);
}
