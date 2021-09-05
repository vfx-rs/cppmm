#include <fstream>

#include "c-comments.hpp"

int main() {
    std::ofstream os("abigen.txt");

    abi_gen_c_comments(os);
}
