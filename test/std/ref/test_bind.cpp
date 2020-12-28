//
#include "test_bind.h"
#include "test.hpp"



namespace {
#include "casts.h"

CPPMM_DEFINE_POINTER_CASTS(test::Test, test_Test)

CPPMM_DEFINE_POINTER_CASTS(std::string, std_string)
#undef CPPMM_DEFINE_POINTER_CASTS
}

extern "C" {

std_string* test_Test_edit_value(test_Test* self) {
    return to_c(&(to_cpp(self)->edit_value()));
}



const std_string* test_Test_get_value(const test_Test* self) {
    return to_c(&(to_cpp(self)->get_value()));
}



void test_Test_set_value(test_Test* self, const std_string* value) {
    to_cpp(self)->set_value(*to_cpp(value));
}



std_string test_Test_clone_value(const test_Test* self) {
    std::string tmp = to_cpp(self)->clone_value();
    std_string ret;
    new (&ret) std::string(std::move(tmp));
    return ret;
}



test_Test* test_Test_Test(const std_string* value) {
    return to_c(new test::Test(*to_cpp(value)));
}



}
    