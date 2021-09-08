#include <fstream>

#include "foo.hpp"
#include "uptr.hpp"

int main() {
    std::ofstream os("abigen.txt");

    abi_gen_foo(os);
    abi_gen_uptr(os);
}
