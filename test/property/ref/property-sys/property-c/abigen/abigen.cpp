#include <fstream>

#include "prop.hpp"

int main() {
    std::ofstream os("abigen.txt");

    abi_gen_prop(os);
}
