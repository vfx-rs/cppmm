#include <fstream>

#include "obyte.hpp"

int main() {
    std::ofstream os("abigen.txt");

    abi_gen_obyte(os);
}
