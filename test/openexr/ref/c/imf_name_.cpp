#include <imf_name_private_.h>

#include <new>


void Imf_2_5_Name_Name(
    Imf_2_5_Name * this_)
{
    new (this_) Imf_2_5::Name();
}

void Imf_2_5_Name_Name_1(
    Imf_2_5_Name * this_
    , char const * text)
{
    new (this_) Imf_2_5::Name(text);
}

Imf_2_5_Name * Imf_2_5_Name__assign(
    Imf_2_5_Name * this_
    , char const * text)
{
    return to_c((to_cpp(this_)) -> operator=(text));
}
