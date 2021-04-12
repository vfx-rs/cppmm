#include <half_private_.h>

#include <new>


void Imath_2_5_half_half(
    Imath_2_5_half * this_)
{
    new (this_) half();
}

void Imath_2_5_half_half_1(
    Imath_2_5_half * this_
    , float f)
{
    new (this_) half(f);
}

void Imath_2_5_half_dtor(
    Imath_2_5_half * this_)
{
    (to_cpp(this_)) -> half::~half();
}

void Imath_2_5_half_half_2(
    Imath_2_5_half * this_
    , Imath_2_5_half const * rhs)
{
    new (this_) half(to_cpp_ref(rhs));
}

void Imath_2_5_half_half_3(
    Imath_2_5_half * this_
    , Imath_2_5_half * )
{
    new (this_) half(to_cpp_ref());
}

float Imath_2_5_half_operatorfloat(
    Imath_2_5_half const * this_)
{
    return (to_cpp(this_)) -> operator float();
}

Imath_2_5_half Imath_2_5_half__op_sub(
    Imath_2_5_half const * this_)
{
    return to_c_copy((to_cpp(this_)) -> operator-());
}

Imath_2_5_half * Imath_2_5_half__assign(
    Imath_2_5_half * this_
    , Imath_2_5_half const * h)
{
    return to_c((to_cpp(this_)) -> operator=(to_cpp_ref(h)));
}

Imath_2_5_half * Imath_2_5_half__assign_1(
    Imath_2_5_half * this_
    , Imath_2_5_half * h)
{
    return to_c((to_cpp(this_)) -> operator=(to_cpp_ref(h)));
}

Imath_2_5_half * Imath_2_5_half__assign_2(
    Imath_2_5_half * this_
    , float f)
{
    return to_c((to_cpp(this_)) -> operator=(f));
}

Imath_2_5_half * Imath_2_5_half__op_iadd(
    Imath_2_5_half * this_
    , Imath_2_5_half h)
{
    return to_c((to_cpp(this_)) -> operator+=(to_cpp_ref(&(h))));
}

Imath_2_5_half * Imath_2_5_half__op_iadd_1(
    Imath_2_5_half * this_
    , float f)
{
    return to_c((to_cpp(this_)) -> operator+=(f));
}

Imath_2_5_half * Imath_2_5_half__op_isub(
    Imath_2_5_half * this_
    , Imath_2_5_half h)
{
    return to_c((to_cpp(this_)) -> operator-=(to_cpp_ref(&(h))));
}

Imath_2_5_half * Imath_2_5_half__op_isub_1(
    Imath_2_5_half * this_
    , float f)
{
    return to_c((to_cpp(this_)) -> operator-=(f));
}

Imath_2_5_half * Imath_2_5_half__op_imul(
    Imath_2_5_half * this_
    , Imath_2_5_half h)
{
    return to_c((to_cpp(this_)) -> operator*=(to_cpp_ref(&(h))));
}

Imath_2_5_half * Imath_2_5_half__op_imul_1(
    Imath_2_5_half * this_
    , float f)
{
    return to_c((to_cpp(this_)) -> operator*=(f));
}

Imath_2_5_half * Imath_2_5_half__op_idiv(
    Imath_2_5_half * this_
    , Imath_2_5_half h)
{
    return to_c((to_cpp(this_)) -> operator/=(to_cpp_ref(&(h))));
}

Imath_2_5_half * Imath_2_5_half__op_idiv_1(
    Imath_2_5_half * this_
    , float f)
{
    return to_c((to_cpp(this_)) -> operator/=(f));
}

Imath_2_5_half Imath_2_5_half_round(
    Imath_2_5_half const * this_
    , unsigned int n)
{
    return to_c_copy((to_cpp(this_)) -> round(n));
}

_Bool Imath_2_5_half_isFinite(
    Imath_2_5_half const * this_)
{
    return (to_cpp(this_)) -> isFinite();
}

_Bool Imath_2_5_half_isNormalized(
    Imath_2_5_half const * this_)
{
    return (to_cpp(this_)) -> isNormalized();
}

_Bool Imath_2_5_half_isDenormalized(
    Imath_2_5_half const * this_)
{
    return (to_cpp(this_)) -> isDenormalized();
}

_Bool Imath_2_5_half_isZero(
    Imath_2_5_half const * this_)
{
    return (to_cpp(this_)) -> isZero();
}

_Bool Imath_2_5_half_isNan(
    Imath_2_5_half const * this_)
{
    return (to_cpp(this_)) -> isNan();
}

_Bool Imath_2_5_half_isInfinity(
    Imath_2_5_half const * this_)
{
    return (to_cpp(this_)) -> isInfinity();
}

_Bool Imath_2_5_half_isNegative(
    Imath_2_5_half const * this_)
{
    return (to_cpp(this_)) -> isNegative();
}

unsigned short Imath_2_5_half_bits(
    Imath_2_5_half const * this_)
{
    return (to_cpp(this_)) -> bits();
}

void Imath_2_5_half_setBits(
    Imath_2_5_half * this_
    , unsigned short bits)
{
    (to_cpp(this_)) -> setBits(bits);
}
