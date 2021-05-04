#include <c-optr_private.h>

#include <new>

#include <stdexcept>

unsigned int optr__PubCtor_ctor(
    optr_PubCtor_t * * this_)
{
    try {
        to_c(this_, new optr::PubCtor());
        return 0;
    } catch (std::exception& e) {
        TLG_EXCEPTION_STRING = e.what();
        return -1;
    }
}
unsigned int optr__PubCtor_dtor(
    optr_PubCtor_t * this_)
{
    try {
        delete to_cpp(this_);
        return 0;
    } catch (std::exception& e) {
        TLG_EXCEPTION_STRING = e.what();
        return -1;
    }
}
unsigned int optr__PubCtor_doit(
    optr_PubCtor_t * this_)
{
    try {
        (to_cpp(this_)) -> doit();
        return 0;
    } catch (std::exception& e) {
        TLG_EXCEPTION_STRING = e.what();
        return -1;
    }
}
unsigned int optr__PrvCtor_doit(
    optr_PrvCtor_t * this_)
{
    try {
        (to_cpp(this_)) -> doit();
        return 0;
    } catch (std::exception& e) {
        TLG_EXCEPTION_STRING = e.what();
        return -1;
    }
}
