#include <c-ex_private.h>


#include <stdexcept>

unsigned int ex__Struct_m1(
    ex_Struct_t * this_)
{
    try {
        (to_cpp(this_)) -> m1();
        return 0;
    } catch (std::runtime_error& e) {
        return 1;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int ex__Struct_m2(
    ex_Struct_t * this_
    , float * return_
    , float a)
{
    try {
        *(return_) = (to_cpp(this_)) -> m2(a);
        return 0;
    } catch (std::logic_error& e) {
        return 2;
    } catch (std::runtime_error& e) {
        return 1;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int ex_f1(
    float * return_
    , int a)
{
    try {
        *(return_) = ex::f1(a);
        return 0;
    } catch (std::invalid_argument& e) {
        return 3;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int ex_f2()
{
    try {
        ex::f2();
        return 0;
    } catch (std::invalid_argument& e) {
        return 3;
    } catch (std::exception& e) {
        return -1;
    }
}
