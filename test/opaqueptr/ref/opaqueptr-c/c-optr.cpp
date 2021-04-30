#include <c-optr_private.h>

#include <new>

void optr__PubCtor_ctor(
    optr_PubCtor_t * * this_)
{
    *this_ = to_c(new optr::PubCtor());
}
void optr__PubCtor_dtor(
    optr_PubCtor_t * this_)
{
    delete this_;
}
void optr__PubCtor_doit(
    optr_PubCtor_t * this_)
{
    (to_cpp(this_)) -> doit();
}
void optr__PrvCtor_doit(
    optr_PrvCtor_t * this_)
{
    (to_cpp(this_)) -> doit();
}
