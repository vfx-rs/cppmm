#include <fstream>

#include "mimpl.hpp"

int main() {
    std::ofstream os("abigen.txt");

    abi_gen_mimpl(os);
}
