#include <dattr.hpp>
#include <abigen/dattr.hpp>

void abi_gen_dattr(std::ostream& os) {
	os << "foo::Foo" << "|" << sizeof(foo::Foo) << "|" << alignof(foo::Foo) << "\n";
}
