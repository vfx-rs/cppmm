#include <fstream>

#include "c-usestd.hpp"
#include "std_list.hpp"
#include "std_set.hpp"
#include "std_string.hpp"

int main() {
    std::ofstream os("abigen.txt");

    abi_gen_c_usestd(os);
    abi_gen_std_list(os);
    abi_gen_std_set(os);
    abi_gen_std_string(os);
}
