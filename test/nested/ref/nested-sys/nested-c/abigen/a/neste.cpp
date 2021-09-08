#include <a/neste.hpp>
#include <abigen/a/neste.hpp>

void abi_gen_a_neste(std::ostream& os) {
	os << "nest::NestAE" << "|" << sizeof(nest::NestAE) << "|" << alignof(nest::NestAE) << "\n";
}
