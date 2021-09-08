#include <c/d/neste.hpp>
#include <abigen/c/d/neste.hpp>

void abi_gen_c_d_neste(std::ostream& os) {
	os << "nest::NestCDE" << "|" << sizeof(nest::NestCDE) << "|" << alignof(nest::NestCDE) << "\n";
}
