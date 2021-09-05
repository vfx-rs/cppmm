#include <b/neste.hpp>
#include <abigen/b/neste.hpp>

void abi_gen_b_neste(std::ostream& os) {
	os << "nest::NestBE" << "|" << sizeof(nest::NestBE) << "|" << alignof(nest::NestBE) << "\n";
}
