#include <obyte.hpp>
#include <abigen/obyte.hpp>

void abi_gen_obyte(std::ostream& os) {
	os << "obyte::Foo" << "|" << sizeof(obyte::Foo) << "|" << alignof(obyte::Foo) << "\n";
}
