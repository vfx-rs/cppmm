#include <imath_matrix_private_.h>

#include <imath_vec_private_.h>
#include <new>


float * Imath_2_5_M33f__index(
    Imath_2_5_M33f * this_
    , int i)
{
    return (to_cpp(this_)) -> operator[](i);
}

float const * Imath_2_5_M33f__index_1(
    Imath_2_5_M33f const * this_
    , int i)
{
    return (to_cpp(this_)) -> operator[](i);
}

void Imath_2_5_M33f_Matrix33(
    Imath_2_5_M33f * this_)
{
    new (this_) Imath_2_5::Matrix33<float>();
}

void Imath_2_5_M33f_Matrix33_1(
    Imath_2_5_M33f * this_
    , float a)
{
    new (this_) Imath_2_5::Matrix33<float>(a);
}

void Imath_2_5_M33f_Matrix33_2(
    Imath_2_5_M33f * this_
    , float a
    , float b
    , float c
    , float d
    , float e
    , float f
    , float g
    , float h
    , float i)
{
    new (this_) Imath_2_5::Matrix33<float>(a, b, c, d, e, f, g, h, i);
}

void Imath_2_5_M33f_Matrix33_3(
    Imath_2_5_M33f * this_
    , Imath_2_5_M33f const * v)
{
    new (this_) Imath_2_5::Matrix33<float>(to_cpp_ref(v));
}

Imath_2_5_M33f const * Imath_2_5_M33f__assign(
    Imath_2_5_M33f * this_
    , Imath_2_5_M33f const * v)
{
    return to_c((to_cpp(this_)) -> operator=(to_cpp_ref(v)));
}

Imath_2_5_M33f const * Imath_2_5_M33f__assign_1(
    Imath_2_5_M33f * this_
    , float a)
{
    return to_c((to_cpp(this_)) -> operator=(a));
}

void Imath_2_5_M33f_dtor(
    Imath_2_5_M33f * this_)
{
    (to_cpp(this_)) -> Imath_2_5::Matrix33<float>::~Matrix33();
}

float * Imath_2_5_M33f_getValue(
    Imath_2_5_M33f * this_)
{
    return (to_cpp(this_)) -> getValue();
}

float const * Imath_2_5_M33f_getValue_1(
    Imath_2_5_M33f const * this_)
{
    return (to_cpp(this_)) -> getValue();
}

void Imath_2_5_M33f_makeIdentity(
    Imath_2_5_M33f * this_)
{
    (to_cpp(this_)) -> makeIdentity();
}

_Bool Imath_2_5_M33f__eq(
    Imath_2_5_M33f const * this_
    , Imath_2_5_M33f const * v)
{
    return (to_cpp(this_)) -> operator==(to_cpp_ref(v));
}

_Bool Imath_2_5_M33f__ne(
    Imath_2_5_M33f const * this_
    , Imath_2_5_M33f const * v)
{
    return (to_cpp(this_)) -> operator!=(to_cpp_ref(v));
}

_Bool Imath_2_5_M33f_equalWithAbsError(
    Imath_2_5_M33f const * this_
    , Imath_2_5_M33f const * v
    , float e)
{
    return (to_cpp(this_)) -> equalWithAbsError(to_cpp_ref(v), e);
}

_Bool Imath_2_5_M33f_equalWithRelError(
    Imath_2_5_M33f const * this_
    , Imath_2_5_M33f const * v
    , float e)
{
    return (to_cpp(this_)) -> equalWithRelError(to_cpp_ref(v), e);
}

Imath_2_5_M33f const * Imath_2_5_M33f__op_iadd(
    Imath_2_5_M33f * this_
    , Imath_2_5_M33f const * v)
{
    return to_c((to_cpp(this_)) -> operator+=(to_cpp_ref(v)));
}

Imath_2_5_M33f const * Imath_2_5_M33f__op_iadd_1(
    Imath_2_5_M33f * this_
    , float a)
{
    return to_c((to_cpp(this_)) -> operator+=(a));
}

Imath_2_5_M33f Imath_2_5_M33f__op_add(
    Imath_2_5_M33f const * this_
    , Imath_2_5_M33f const * v)
{
    return to_c_copy((to_cpp(this_)) -> operator+(to_cpp_ref(v)));
}

Imath_2_5_M33f const * Imath_2_5_M33f__op_isub(
    Imath_2_5_M33f * this_
    , Imath_2_5_M33f const * v)
{
    return to_c((to_cpp(this_)) -> operator-=(to_cpp_ref(v)));
}

Imath_2_5_M33f const * Imath_2_5_M33f__op_isub_1(
    Imath_2_5_M33f * this_
    , float a)
{
    return to_c((to_cpp(this_)) -> operator-=(a));
}

Imath_2_5_M33f Imath_2_5_M33f__op_sub(
    Imath_2_5_M33f const * this_
    , Imath_2_5_M33f const * v)
{
    return to_c_copy((to_cpp(this_)) -> operator-(to_cpp_ref(v)));
}

Imath_2_5_M33f Imath_2_5_M33f__op_sub_1(
    Imath_2_5_M33f const * this_)
{
    return to_c_copy((to_cpp(this_)) -> operator-());
}

Imath_2_5_M33f const * Imath_2_5_M33f_negate(
    Imath_2_5_M33f * this_)
{
    return to_c((to_cpp(this_)) -> negate());
}

Imath_2_5_M33f const * Imath_2_5_M33f__op_imul(
    Imath_2_5_M33f * this_
    , float a)
{
    return to_c((to_cpp(this_)) -> operator*=(a));
}

Imath_2_5_M33f Imath_2_5_M33f__op_mul(
    Imath_2_5_M33f const * this_
    , float a)
{
    return to_c_copy((to_cpp(this_)) -> operator*(a));
}

Imath_2_5_M33f const * Imath_2_5_M33f__op_imul_1(
    Imath_2_5_M33f * this_
    , Imath_2_5_M33f const * v)
{
    return to_c((to_cpp(this_)) -> operator*=(to_cpp_ref(v)));
}

Imath_2_5_M33f Imath_2_5_M33f__op_mul_1(
    Imath_2_5_M33f const * this_
    , Imath_2_5_M33f const * v)
{
    return to_c_copy((to_cpp(this_)) -> operator*(to_cpp_ref(v)));
}

Imath_2_5_M33f const * Imath_2_5_M33f__op_idiv(
    Imath_2_5_M33f * this_
    , float a)
{
    return to_c((to_cpp(this_)) -> operator/=(a));
}

Imath_2_5_M33f Imath_2_5_M33f__op_div(
    Imath_2_5_M33f const * this_
    , float a)
{
    return to_c_copy((to_cpp(this_)) -> operator/(a));
}

Imath_2_5_M33f const * Imath_2_5_M33f_transpose(
    Imath_2_5_M33f * this_)
{
    return to_c((to_cpp(this_)) -> transpose());
}

Imath_2_5_M33f Imath_2_5_M33f_transposed(
    Imath_2_5_M33f const * this_)
{
    return to_c_copy((to_cpp(this_)) -> transposed());
}

Imath_2_5_M33f const * Imath_2_5_M33f_invert(
    Imath_2_5_M33f * this_
    , _Bool singExc)
{
    return to_c((to_cpp(this_)) -> invert(singExc));
}

Imath_2_5_M33f Imath_2_5_M33f_inverse(
    Imath_2_5_M33f const * this_
    , _Bool singExc)
{
    return to_c_copy((to_cpp(this_)) -> inverse(singExc));
}

Imath_2_5_M33f const * Imath_2_5_M33f_gjInvert(
    Imath_2_5_M33f * this_
    , _Bool singExc)
{
    return to_c((to_cpp(this_)) -> gjInvert(singExc));
}

Imath_2_5_M33f Imath_2_5_M33f_gjInverse(
    Imath_2_5_M33f const * this_
    , _Bool singExc)
{
    return to_c_copy((to_cpp(this_)) -> gjInverse(singExc));
}

float Imath_2_5_M33f_minorOf(
    Imath_2_5_M33f const * this_
    , int const r
    , int const c)
{
    return (to_cpp(this_)) -> minorOf(r, c);
}

float Imath_2_5_M33f_fastMinor(
    Imath_2_5_M33f const * this_
    , int const r0
    , int const r1
    , int const c0
    , int const c1)
{
    return (to_cpp(this_)) -> fastMinor(r0, r1, c0, c1);
}

float Imath_2_5_M33f_determinant(
    Imath_2_5_M33f const * this_)
{
    return (to_cpp(this_)) -> determinant();
}

Imath_2_5_M33f const * Imath_2_5_M33f_setScale(
    Imath_2_5_M33f * this_
    , float s)
{
    return to_c((to_cpp(this_)) -> setScale(s));
}

Imath_2_5_V2f Imath_2_5_M33f_translation(
    Imath_2_5_M33f const * this_)
{
    return to_c_copy((to_cpp(this_)) -> translation());
}

double * Imath_2_5_M33d__index(
    Imath_2_5_M33d * this_
    , int i)
{
    return (to_cpp(this_)) -> operator[](i);
}

double const * Imath_2_5_M33d__index_1(
    Imath_2_5_M33d const * this_
    , int i)
{
    return (to_cpp(this_)) -> operator[](i);
}

void Imath_2_5_M33d_Matrix33(
    Imath_2_5_M33d * this_)
{
    new (this_) Imath_2_5::Matrix33<double>();
}

void Imath_2_5_M33d_Matrix33_1(
    Imath_2_5_M33d * this_
    , double a)
{
    new (this_) Imath_2_5::Matrix33<double>(a);
}

void Imath_2_5_M33d_Matrix33_2(
    Imath_2_5_M33d * this_
    , double a
    , double b
    , double c
    , double d
    , double e
    , double f
    , double g
    , double h
    , double i)
{
    new (this_) Imath_2_5::Matrix33<double>(a, b, c, d, e, f, g, h, i);
}

void Imath_2_5_M33d_Matrix33_3(
    Imath_2_5_M33d * this_
    , Imath_2_5_M33d const * v)
{
    new (this_) Imath_2_5::Matrix33<double>(to_cpp_ref(v));
}

Imath_2_5_M33d const * Imath_2_5_M33d__assign(
    Imath_2_5_M33d * this_
    , Imath_2_5_M33d const * v)
{
    return to_c((to_cpp(this_)) -> operator=(to_cpp_ref(v)));
}

Imath_2_5_M33d const * Imath_2_5_M33d__assign_1(
    Imath_2_5_M33d * this_
    , double a)
{
    return to_c((to_cpp(this_)) -> operator=(a));
}

void Imath_2_5_M33d_dtor(
    Imath_2_5_M33d * this_)
{
    (to_cpp(this_)) -> Imath_2_5::Matrix33<double>::~Matrix33();
}

double * Imath_2_5_M33d_getValue(
    Imath_2_5_M33d * this_)
{
    return (to_cpp(this_)) -> getValue();
}

double const * Imath_2_5_M33d_getValue_1(
    Imath_2_5_M33d const * this_)
{
    return (to_cpp(this_)) -> getValue();
}

void Imath_2_5_M33d_makeIdentity(
    Imath_2_5_M33d * this_)
{
    (to_cpp(this_)) -> makeIdentity();
}

_Bool Imath_2_5_M33d__eq(
    Imath_2_5_M33d const * this_
    , Imath_2_5_M33d const * v)
{
    return (to_cpp(this_)) -> operator==(to_cpp_ref(v));
}

_Bool Imath_2_5_M33d__ne(
    Imath_2_5_M33d const * this_
    , Imath_2_5_M33d const * v)
{
    return (to_cpp(this_)) -> operator!=(to_cpp_ref(v));
}

_Bool Imath_2_5_M33d_equalWithAbsError(
    Imath_2_5_M33d const * this_
    , Imath_2_5_M33d const * v
    , double e)
{
    return (to_cpp(this_)) -> equalWithAbsError(to_cpp_ref(v), e);
}

_Bool Imath_2_5_M33d_equalWithRelError(
    Imath_2_5_M33d const * this_
    , Imath_2_5_M33d const * v
    , double e)
{
    return (to_cpp(this_)) -> equalWithRelError(to_cpp_ref(v), e);
}

Imath_2_5_M33d const * Imath_2_5_M33d__op_iadd(
    Imath_2_5_M33d * this_
    , Imath_2_5_M33d const * v)
{
    return to_c((to_cpp(this_)) -> operator+=(to_cpp_ref(v)));
}

Imath_2_5_M33d const * Imath_2_5_M33d__op_iadd_1(
    Imath_2_5_M33d * this_
    , double a)
{
    return to_c((to_cpp(this_)) -> operator+=(a));
}

Imath_2_5_M33d Imath_2_5_M33d__op_add(
    Imath_2_5_M33d const * this_
    , Imath_2_5_M33d const * v)
{
    return to_c_copy((to_cpp(this_)) -> operator+(to_cpp_ref(v)));
}

Imath_2_5_M33d const * Imath_2_5_M33d__op_isub(
    Imath_2_5_M33d * this_
    , Imath_2_5_M33d const * v)
{
    return to_c((to_cpp(this_)) -> operator-=(to_cpp_ref(v)));
}

Imath_2_5_M33d const * Imath_2_5_M33d__op_isub_1(
    Imath_2_5_M33d * this_
    , double a)
{
    return to_c((to_cpp(this_)) -> operator-=(a));
}

Imath_2_5_M33d Imath_2_5_M33d__op_sub(
    Imath_2_5_M33d const * this_
    , Imath_2_5_M33d const * v)
{
    return to_c_copy((to_cpp(this_)) -> operator-(to_cpp_ref(v)));
}

Imath_2_5_M33d Imath_2_5_M33d__op_sub_1(
    Imath_2_5_M33d const * this_)
{
    return to_c_copy((to_cpp(this_)) -> operator-());
}

Imath_2_5_M33d const * Imath_2_5_M33d_negate(
    Imath_2_5_M33d * this_)
{
    return to_c((to_cpp(this_)) -> negate());
}

Imath_2_5_M33d const * Imath_2_5_M33d__op_imul(
    Imath_2_5_M33d * this_
    , double a)
{
    return to_c((to_cpp(this_)) -> operator*=(a));
}

Imath_2_5_M33d Imath_2_5_M33d__op_mul(
    Imath_2_5_M33d const * this_
    , double a)
{
    return to_c_copy((to_cpp(this_)) -> operator*(a));
}

Imath_2_5_M33d const * Imath_2_5_M33d__op_imul_1(
    Imath_2_5_M33d * this_
    , Imath_2_5_M33d const * v)
{
    return to_c((to_cpp(this_)) -> operator*=(to_cpp_ref(v)));
}

Imath_2_5_M33d Imath_2_5_M33d__op_mul_1(
    Imath_2_5_M33d const * this_
    , Imath_2_5_M33d const * v)
{
    return to_c_copy((to_cpp(this_)) -> operator*(to_cpp_ref(v)));
}

Imath_2_5_M33d const * Imath_2_5_M33d__op_idiv(
    Imath_2_5_M33d * this_
    , double a)
{
    return to_c((to_cpp(this_)) -> operator/=(a));
}

Imath_2_5_M33d Imath_2_5_M33d__op_div(
    Imath_2_5_M33d const * this_
    , double a)
{
    return to_c_copy((to_cpp(this_)) -> operator/(a));
}

Imath_2_5_M33d const * Imath_2_5_M33d_transpose(
    Imath_2_5_M33d * this_)
{
    return to_c((to_cpp(this_)) -> transpose());
}

Imath_2_5_M33d Imath_2_5_M33d_transposed(
    Imath_2_5_M33d const * this_)
{
    return to_c_copy((to_cpp(this_)) -> transposed());
}

Imath_2_5_M33d const * Imath_2_5_M33d_invert(
    Imath_2_5_M33d * this_
    , _Bool singExc)
{
    return to_c((to_cpp(this_)) -> invert(singExc));
}

Imath_2_5_M33d Imath_2_5_M33d_inverse(
    Imath_2_5_M33d const * this_
    , _Bool singExc)
{
    return to_c_copy((to_cpp(this_)) -> inverse(singExc));
}

Imath_2_5_M33d const * Imath_2_5_M33d_gjInvert(
    Imath_2_5_M33d * this_
    , _Bool singExc)
{
    return to_c((to_cpp(this_)) -> gjInvert(singExc));
}

Imath_2_5_M33d Imath_2_5_M33d_gjInverse(
    Imath_2_5_M33d const * this_
    , _Bool singExc)
{
    return to_c_copy((to_cpp(this_)) -> gjInverse(singExc));
}

double Imath_2_5_M33d_minorOf(
    Imath_2_5_M33d const * this_
    , int const r
    , int const c)
{
    return (to_cpp(this_)) -> minorOf(r, c);
}

double Imath_2_5_M33d_fastMinor(
    Imath_2_5_M33d const * this_
    , int const r0
    , int const r1
    , int const c0
    , int const c1)
{
    return (to_cpp(this_)) -> fastMinor(r0, r1, c0, c1);
}

double Imath_2_5_M33d_determinant(
    Imath_2_5_M33d const * this_)
{
    return (to_cpp(this_)) -> determinant();
}

Imath_2_5_M33d const * Imath_2_5_M33d_setScale(
    Imath_2_5_M33d * this_
    , double s)
{
    return to_c((to_cpp(this_)) -> setScale(s));
}

Imath_2_5_V2d Imath_2_5_M33d_translation(
    Imath_2_5_M33d const * this_)
{
    return to_c_copy((to_cpp(this_)) -> translation());
}

float * Imath_2_5_M44f__index(
    Imath_2_5_M44f * this_
    , int i)
{
    return (to_cpp(this_)) -> operator[](i);
}

float const * Imath_2_5_M44f__index_1(
    Imath_2_5_M44f const * this_
    , int i)
{
    return (to_cpp(this_)) -> operator[](i);
}

void Imath_2_5_M44f_Matrix44(
    Imath_2_5_M44f * this_)
{
    new (this_) Imath_2_5::Matrix44<float>();
}

void Imath_2_5_M44f_Matrix44_1(
    Imath_2_5_M44f * this_
    , float a)
{
    new (this_) Imath_2_5::Matrix44<float>(a);
}

void Imath_2_5_M44f_Matrix44_2(
    Imath_2_5_M44f * this_
    , float a
    , float b
    , float c
    , float d
    , float e
    , float f
    , float g
    , float h
    , float i
    , float j
    , float k
    , float l
    , float m
    , float n
    , float o
    , float p)
{
    new (this_) Imath_2_5::Matrix44<float>(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p);
}

void Imath_2_5_M44f_Matrix44_3(
    Imath_2_5_M44f * this_
    , Imath_2_5_M33f r
    , Imath_2_5_V3f t)
{
    new (this_) Imath_2_5::Matrix44<float>(to_cpp_ref(&(r)), to_cpp_ref(&(t)));
}

void Imath_2_5_M44f_dtor(
    Imath_2_5_M44f * this_)
{
    (to_cpp(this_)) -> Imath_2_5::Matrix44<float>::~Matrix44();
}

void Imath_2_5_M44f_Matrix44_4(
    Imath_2_5_M44f * this_
    , Imath_2_5_M44f const * v)
{
    new (this_) Imath_2_5::Matrix44<float>(to_cpp_ref(v));
}

Imath_2_5_M44f const * Imath_2_5_M44f__assign(
    Imath_2_5_M44f * this_
    , Imath_2_5_M44f const * v)
{
    return to_c((to_cpp(this_)) -> operator=(to_cpp_ref(v)));
}

Imath_2_5_M44f const * Imath_2_5_M44f__assign_1(
    Imath_2_5_M44f * this_
    , float a)
{
    return to_c((to_cpp(this_)) -> operator=(a));
}

float * Imath_2_5_M44f_getValue(
    Imath_2_5_M44f * this_)
{
    return (to_cpp(this_)) -> getValue();
}

float const * Imath_2_5_M44f_getValue_1(
    Imath_2_5_M44f const * this_)
{
    return (to_cpp(this_)) -> getValue();
}

void Imath_2_5_M44f_makeIdentity(
    Imath_2_5_M44f * this_)
{
    (to_cpp(this_)) -> makeIdentity();
}

_Bool Imath_2_5_M44f__eq(
    Imath_2_5_M44f const * this_
    , Imath_2_5_M44f const * v)
{
    return (to_cpp(this_)) -> operator==(to_cpp_ref(v));
}

_Bool Imath_2_5_M44f__ne(
    Imath_2_5_M44f const * this_
    , Imath_2_5_M44f const * v)
{
    return (to_cpp(this_)) -> operator!=(to_cpp_ref(v));
}

_Bool Imath_2_5_M44f_equalWithAbsError(
    Imath_2_5_M44f const * this_
    , Imath_2_5_M44f const * v
    , float e)
{
    return (to_cpp(this_)) -> equalWithAbsError(to_cpp_ref(v), e);
}

_Bool Imath_2_5_M44f_equalWithRelError(
    Imath_2_5_M44f const * this_
    , Imath_2_5_M44f const * v
    , float e)
{
    return (to_cpp(this_)) -> equalWithRelError(to_cpp_ref(v), e);
}

Imath_2_5_M44f const * Imath_2_5_M44f__op_iadd(
    Imath_2_5_M44f * this_
    , Imath_2_5_M44f const * v)
{
    return to_c((to_cpp(this_)) -> operator+=(to_cpp_ref(v)));
}

Imath_2_5_M44f const * Imath_2_5_M44f__op_iadd_1(
    Imath_2_5_M44f * this_
    , float a)
{
    return to_c((to_cpp(this_)) -> operator+=(a));
}

Imath_2_5_M44f Imath_2_5_M44f__op_add(
    Imath_2_5_M44f const * this_
    , Imath_2_5_M44f const * v)
{
    return to_c_copy((to_cpp(this_)) -> operator+(to_cpp_ref(v)));
}

Imath_2_5_M44f const * Imath_2_5_M44f__op_isub(
    Imath_2_5_M44f * this_
    , Imath_2_5_M44f const * v)
{
    return to_c((to_cpp(this_)) -> operator-=(to_cpp_ref(v)));
}

Imath_2_5_M44f const * Imath_2_5_M44f__op_isub_1(
    Imath_2_5_M44f * this_
    , float a)
{
    return to_c((to_cpp(this_)) -> operator-=(a));
}

Imath_2_5_M44f Imath_2_5_M44f__op_sub(
    Imath_2_5_M44f const * this_
    , Imath_2_5_M44f const * v)
{
    return to_c_copy((to_cpp(this_)) -> operator-(to_cpp_ref(v)));
}

Imath_2_5_M44f Imath_2_5_M44f__op_sub_1(
    Imath_2_5_M44f const * this_)
{
    return to_c_copy((to_cpp(this_)) -> operator-());
}

Imath_2_5_M44f const * Imath_2_5_M44f_negate(
    Imath_2_5_M44f * this_)
{
    return to_c((to_cpp(this_)) -> negate());
}

Imath_2_5_M44f const * Imath_2_5_M44f__op_imul(
    Imath_2_5_M44f * this_
    , float a)
{
    return to_c((to_cpp(this_)) -> operator*=(a));
}

Imath_2_5_M44f Imath_2_5_M44f__op_mul(
    Imath_2_5_M44f const * this_
    , float a)
{
    return to_c_copy((to_cpp(this_)) -> operator*(a));
}

Imath_2_5_M44f const * Imath_2_5_M44f__op_imul_1(
    Imath_2_5_M44f * this_
    , Imath_2_5_M44f const * v)
{
    return to_c((to_cpp(this_)) -> operator*=(to_cpp_ref(v)));
}

Imath_2_5_M44f Imath_2_5_M44f__op_mul_1(
    Imath_2_5_M44f const * this_
    , Imath_2_5_M44f const * v)
{
    return to_c_copy((to_cpp(this_)) -> operator*(to_cpp_ref(v)));
}

Imath_2_5_M44f const * Imath_2_5_M44f__op_idiv(
    Imath_2_5_M44f * this_
    , float a)
{
    return to_c((to_cpp(this_)) -> operator/=(a));
}

Imath_2_5_M44f Imath_2_5_M44f__op_div(
    Imath_2_5_M44f const * this_
    , float a)
{
    return to_c_copy((to_cpp(this_)) -> operator/(a));
}

Imath_2_5_M44f const * Imath_2_5_M44f_transpose(
    Imath_2_5_M44f * this_)
{
    return to_c((to_cpp(this_)) -> transpose());
}

Imath_2_5_M44f Imath_2_5_M44f_transposed(
    Imath_2_5_M44f const * this_)
{
    return to_c_copy((to_cpp(this_)) -> transposed());
}

Imath_2_5_M44f const * Imath_2_5_M44f_invert(
    Imath_2_5_M44f * this_
    , _Bool singExc)
{
    return to_c((to_cpp(this_)) -> invert(singExc));
}

Imath_2_5_M44f Imath_2_5_M44f_inverse(
    Imath_2_5_M44f const * this_
    , _Bool singExc)
{
    return to_c_copy((to_cpp(this_)) -> inverse(singExc));
}

Imath_2_5_M44f const * Imath_2_5_M44f_gjInvert(
    Imath_2_5_M44f * this_
    , _Bool singExc)
{
    return to_c((to_cpp(this_)) -> gjInvert(singExc));
}

Imath_2_5_M44f Imath_2_5_M44f_gjInverse(
    Imath_2_5_M44f const * this_
    , _Bool singExc)
{
    return to_c_copy((to_cpp(this_)) -> gjInverse(singExc));
}

float Imath_2_5_M44f_minorOf(
    Imath_2_5_M44f const * this_
    , int const r
    , int const c)
{
    return (to_cpp(this_)) -> minorOf(r, c);
}

float Imath_2_5_M44f_fastMinor(
    Imath_2_5_M44f const * this_
    , int const r0
    , int const r1
    , int const r2
    , int const c0
    , int const c1
    , int const c2)
{
    return (to_cpp(this_)) -> fastMinor(r0, r1, r2, c0, c1, c2);
}

float Imath_2_5_M44f_determinant(
    Imath_2_5_M44f const * this_)
{
    return (to_cpp(this_)) -> determinant();
}

Imath_2_5_M44f const * Imath_2_5_M44f_setScale(
    Imath_2_5_M44f * this_
    , float s)
{
    return to_c((to_cpp(this_)) -> setScale(s));
}

Imath_2_5_V3f const Imath_2_5_M44f_translation(
    Imath_2_5_M44f const * this_)
{
    return to_c_copy((to_cpp(this_)) -> translation());
}

double * Imath_2_5_M44d__index(
    Imath_2_5_M44d * this_
    , int i)
{
    return (to_cpp(this_)) -> operator[](i);
}

double const * Imath_2_5_M44d__index_1(
    Imath_2_5_M44d const * this_
    , int i)
{
    return (to_cpp(this_)) -> operator[](i);
}

void Imath_2_5_M44d_Matrix44(
    Imath_2_5_M44d * this_)
{
    new (this_) Imath_2_5::Matrix44<double>();
}

void Imath_2_5_M44d_Matrix44_1(
    Imath_2_5_M44d * this_
    , double a)
{
    new (this_) Imath_2_5::Matrix44<double>(a);
}

void Imath_2_5_M44d_Matrix44_2(
    Imath_2_5_M44d * this_
    , double a
    , double b
    , double c
    , double d
    , double e
    , double f
    , double g
    , double h
    , double i
    , double j
    , double k
    , double l
    , double m
    , double n
    , double o
    , double p)
{
    new (this_) Imath_2_5::Matrix44<double>(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p);
}

void Imath_2_5_M44d_Matrix44_3(
    Imath_2_5_M44d * this_
    , Imath_2_5_M33d r
    , Imath_2_5_V3d t)
{
    new (this_) Imath_2_5::Matrix44<double>(to_cpp_ref(&(r)), to_cpp_ref(&(t)));
}

void Imath_2_5_M44d_dtor(
    Imath_2_5_M44d * this_)
{
    (to_cpp(this_)) -> Imath_2_5::Matrix44<double>::~Matrix44();
}

void Imath_2_5_M44d_Matrix44_4(
    Imath_2_5_M44d * this_
    , Imath_2_5_M44d const * v)
{
    new (this_) Imath_2_5::Matrix44<double>(to_cpp_ref(v));
}

Imath_2_5_M44d const * Imath_2_5_M44d__assign(
    Imath_2_5_M44d * this_
    , Imath_2_5_M44d const * v)
{
    return to_c((to_cpp(this_)) -> operator=(to_cpp_ref(v)));
}

Imath_2_5_M44d const * Imath_2_5_M44d__assign_1(
    Imath_2_5_M44d * this_
    , double a)
{
    return to_c((to_cpp(this_)) -> operator=(a));
}

double * Imath_2_5_M44d_getValue(
    Imath_2_5_M44d * this_)
{
    return (to_cpp(this_)) -> getValue();
}

double const * Imath_2_5_M44d_getValue_1(
    Imath_2_5_M44d const * this_)
{
    return (to_cpp(this_)) -> getValue();
}

void Imath_2_5_M44d_makeIdentity(
    Imath_2_5_M44d * this_)
{
    (to_cpp(this_)) -> makeIdentity();
}

_Bool Imath_2_5_M44d__eq(
    Imath_2_5_M44d const * this_
    , Imath_2_5_M44d const * v)
{
    return (to_cpp(this_)) -> operator==(to_cpp_ref(v));
}

_Bool Imath_2_5_M44d__ne(
    Imath_2_5_M44d const * this_
    , Imath_2_5_M44d const * v)
{
    return (to_cpp(this_)) -> operator!=(to_cpp_ref(v));
}

_Bool Imath_2_5_M44d_equalWithAbsError(
    Imath_2_5_M44d const * this_
    , Imath_2_5_M44d const * v
    , double e)
{
    return (to_cpp(this_)) -> equalWithAbsError(to_cpp_ref(v), e);
}

_Bool Imath_2_5_M44d_equalWithRelError(
    Imath_2_5_M44d const * this_
    , Imath_2_5_M44d const * v
    , double e)
{
    return (to_cpp(this_)) -> equalWithRelError(to_cpp_ref(v), e);
}

Imath_2_5_M44d const * Imath_2_5_M44d__op_iadd(
    Imath_2_5_M44d * this_
    , Imath_2_5_M44d const * v)
{
    return to_c((to_cpp(this_)) -> operator+=(to_cpp_ref(v)));
}

Imath_2_5_M44d const * Imath_2_5_M44d__op_iadd_1(
    Imath_2_5_M44d * this_
    , double a)
{
    return to_c((to_cpp(this_)) -> operator+=(a));
}

Imath_2_5_M44d Imath_2_5_M44d__op_add(
    Imath_2_5_M44d const * this_
    , Imath_2_5_M44d const * v)
{
    return to_c_copy((to_cpp(this_)) -> operator+(to_cpp_ref(v)));
}

Imath_2_5_M44d const * Imath_2_5_M44d__op_isub(
    Imath_2_5_M44d * this_
    , Imath_2_5_M44d const * v)
{
    return to_c((to_cpp(this_)) -> operator-=(to_cpp_ref(v)));
}

Imath_2_5_M44d const * Imath_2_5_M44d__op_isub_1(
    Imath_2_5_M44d * this_
    , double a)
{
    return to_c((to_cpp(this_)) -> operator-=(a));
}

Imath_2_5_M44d Imath_2_5_M44d__op_sub(
    Imath_2_5_M44d const * this_
    , Imath_2_5_M44d const * v)
{
    return to_c_copy((to_cpp(this_)) -> operator-(to_cpp_ref(v)));
}

Imath_2_5_M44d Imath_2_5_M44d__op_sub_1(
    Imath_2_5_M44d const * this_)
{
    return to_c_copy((to_cpp(this_)) -> operator-());
}

Imath_2_5_M44d const * Imath_2_5_M44d_negate(
    Imath_2_5_M44d * this_)
{
    return to_c((to_cpp(this_)) -> negate());
}

Imath_2_5_M44d const * Imath_2_5_M44d__op_imul(
    Imath_2_5_M44d * this_
    , double a)
{
    return to_c((to_cpp(this_)) -> operator*=(a));
}

Imath_2_5_M44d Imath_2_5_M44d__op_mul(
    Imath_2_5_M44d const * this_
    , double a)
{
    return to_c_copy((to_cpp(this_)) -> operator*(a));
}

Imath_2_5_M44d const * Imath_2_5_M44d__op_imul_1(
    Imath_2_5_M44d * this_
    , Imath_2_5_M44d const * v)
{
    return to_c((to_cpp(this_)) -> operator*=(to_cpp_ref(v)));
}

Imath_2_5_M44d Imath_2_5_M44d__op_mul_1(
    Imath_2_5_M44d const * this_
    , Imath_2_5_M44d const * v)
{
    return to_c_copy((to_cpp(this_)) -> operator*(to_cpp_ref(v)));
}

Imath_2_5_M44d const * Imath_2_5_M44d__op_idiv(
    Imath_2_5_M44d * this_
    , double a)
{
    return to_c((to_cpp(this_)) -> operator/=(a));
}

Imath_2_5_M44d Imath_2_5_M44d__op_div(
    Imath_2_5_M44d const * this_
    , double a)
{
    return to_c_copy((to_cpp(this_)) -> operator/(a));
}

Imath_2_5_M44d const * Imath_2_5_M44d_transpose(
    Imath_2_5_M44d * this_)
{
    return to_c((to_cpp(this_)) -> transpose());
}

Imath_2_5_M44d Imath_2_5_M44d_transposed(
    Imath_2_5_M44d const * this_)
{
    return to_c_copy((to_cpp(this_)) -> transposed());
}

Imath_2_5_M44d const * Imath_2_5_M44d_invert(
    Imath_2_5_M44d * this_
    , _Bool singExc)
{
    return to_c((to_cpp(this_)) -> invert(singExc));
}

Imath_2_5_M44d Imath_2_5_M44d_inverse(
    Imath_2_5_M44d const * this_
    , _Bool singExc)
{
    return to_c_copy((to_cpp(this_)) -> inverse(singExc));
}

Imath_2_5_M44d const * Imath_2_5_M44d_gjInvert(
    Imath_2_5_M44d * this_
    , _Bool singExc)
{
    return to_c((to_cpp(this_)) -> gjInvert(singExc));
}

Imath_2_5_M44d Imath_2_5_M44d_gjInverse(
    Imath_2_5_M44d const * this_
    , _Bool singExc)
{
    return to_c_copy((to_cpp(this_)) -> gjInverse(singExc));
}

double Imath_2_5_M44d_minorOf(
    Imath_2_5_M44d const * this_
    , int const r
    , int const c)
{
    return (to_cpp(this_)) -> minorOf(r, c);
}

double Imath_2_5_M44d_fastMinor(
    Imath_2_5_M44d const * this_
    , int const r0
    , int const r1
    , int const r2
    , int const c0
    , int const c1
    , int const c2)
{
    return (to_cpp(this_)) -> fastMinor(r0, r1, r2, c0, c1, c2);
}

double Imath_2_5_M44d_determinant(
    Imath_2_5_M44d const * this_)
{
    return (to_cpp(this_)) -> determinant();
}

Imath_2_5_M44d const * Imath_2_5_M44d_setScale(
    Imath_2_5_M44d * this_
    , double s)
{
    return to_c((to_cpp(this_)) -> setScale(s));
}

Imath_2_5_V3d const Imath_2_5_M44d_translation(
    Imath_2_5_M44d const * this_)
{
    return to_c_copy((to_cpp(this_)) -> translation());
}
