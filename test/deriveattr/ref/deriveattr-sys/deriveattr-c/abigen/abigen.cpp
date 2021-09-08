#include <fstream>

#include "dattr.hpp"

int main() {
    std::ofstream os("abigen.txt");

    abi_gen_dattr(os);
}
