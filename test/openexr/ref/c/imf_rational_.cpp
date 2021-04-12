#include <imf_rational_private_.h>

#include <new>


void Imf_2_5_Rational_Rational(
    Imf_2_5_Rational * this_)
{
    new (this_) Imf_2_5::Rational();
}

void Imf_2_5_Rational_Rational_1(
    Imf_2_5_Rational * this_
    , int n
    , int d)
{
    new (this_) Imf_2_5::Rational(n, d);
}

void Imf_2_5_Rational_Rational_2(
    Imf_2_5_Rational * this_
    , double x)
{
    new (this_) Imf_2_5::Rational(x);
}

double Imf_2_5_Rational_operatordouble(
    Imf_2_5_Rational const * this_)
{
    return (to_cpp(this_)) -> operator double();
}
