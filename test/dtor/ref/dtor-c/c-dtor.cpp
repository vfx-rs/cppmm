#include <c-dtor_private.h>

#include <new>

void dtor__Struct_Struct(
    dtor_Struct_t * this_)
{
    new (this_) dtor::Struct();
}
void dtor__Struct_dtor(
    dtor_Struct_t * this_)
{
    (to_cpp(this_)) -> dtor::Struct::~Struct();
}
