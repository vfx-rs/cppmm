#include <dn.hpp>
#include <abigen/c-dn.hpp>

void abi_gen_c_dn(std::ostream& os) {
	os << "DN::v2_2::Class::Struct" << "|" << sizeof(DN::v2_2::Class::Struct) << "|" << alignof(DN::v2_2::Class::Struct) << "\n";
}
