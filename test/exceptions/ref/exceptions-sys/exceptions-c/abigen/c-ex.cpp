#include <ex.hpp>
#include <abigen/c-ex.hpp>

void abi_gen_c_ex(std::ostream& os) {
	os << "ex::Struct" << "|" << sizeof(ex::Struct) << "|" << alignof(ex::Struct) << "\n";
}
