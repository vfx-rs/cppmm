#include <imath_vec_private_.h>

#include <new>


short * Imath_2_5_V2s__index(
    Imath_2_5_V2s * this_
    , int i)
{
    return &((to_cpp(this_)) -> operator[](i));
}

short const * Imath_2_5_V2s__index_1(
    Imath_2_5_V2s const * this_
    , int i)
{
    return &((to_cpp(this_)) -> operator[](i));
}

void Imath_2_5_V2s_Vec2(
    Imath_2_5_V2s * this_)
{
    new (this_) Imath_2_5::Vec2<short>();
}

void Imath_2_5_V2s_Vec2_1(
    Imath_2_5_V2s * this_
    , short a)
{
    new (this_) Imath_2_5::Vec2<short>(a);
}

void Imath_2_5_V2s_Vec2_2(
    Imath_2_5_V2s * this_
    , short a
    , short b)
{
    new (this_) Imath_2_5::Vec2<short>(a, b);
}

void Imath_2_5_V2s_Vec2_3(
    Imath_2_5_V2s * this_
    , Imath_2_5_V2s const * v)
{
    new (this_) Imath_2_5::Vec2<short>(to_cpp_ref(v));
}

Imath_2_5_V2s const * Imath_2_5_V2s__assign(
    Imath_2_5_V2s * this_
    , Imath_2_5_V2s const * v)
{
    return to_c((to_cpp(this_)) -> operator=(to_cpp_ref(v)));
}

void Imath_2_5_V2s_dtor(
    Imath_2_5_V2s * this_)
{
    (to_cpp(this_)) -> Imath_2_5::Vec2<short>::~Vec2();
}

short * Imath_2_5_V2s_getValue(
    Imath_2_5_V2s * this_)
{
    return (to_cpp(this_)) -> getValue();
}

short const * Imath_2_5_V2s_getValue_1(
    Imath_2_5_V2s const * this_)
{
    return (to_cpp(this_)) -> getValue();
}

_Bool Imath_2_5_V2s_equalWithAbsError(
    Imath_2_5_V2s const * this_
    , Imath_2_5_V2s const * v
    , short e)
{
    return (to_cpp(this_)) -> equalWithAbsError(to_cpp_ref(v), e);
}

_Bool Imath_2_5_V2s_equalWithRelError(
    Imath_2_5_V2s const * this_
    , Imath_2_5_V2s const * v
    , short e)
{
    return (to_cpp(this_)) -> equalWithRelError(to_cpp_ref(v), e);
}

short Imath_2_5_V2s_dot(
    Imath_2_5_V2s const * this_
    , Imath_2_5_V2s const * v)
{
    return (to_cpp(this_)) -> dot(to_cpp_ref(v));
}

short Imath_2_5_V2s_operator^(
    Imath_2_5_V2s const * this_
    , Imath_2_5_V2s const * v)
{
    return (to_cpp(this_)) -> operator^(to_cpp_ref(v));
}

short Imath_2_5_V2s_cross(
    Imath_2_5_V2s const * this_
    , Imath_2_5_V2s const * v)
{
    return (to_cpp(this_)) -> cross(to_cpp_ref(v));
}

short Imath_2_5_V2s_operator%(
    Imath_2_5_V2s const * this_
    , Imath_2_5_V2s const * v)
{
    return (to_cpp(this_)) -> operator%(to_cpp_ref(v));
}

Imath_2_5_V2s const * Imath_2_5_V2s__op_iadd(
    Imath_2_5_V2s * this_
    , Imath_2_5_V2s const * v)
{
    return to_c((to_cpp(this_)) -> operator+=(to_cpp_ref(v)));
}

Imath_2_5_V2s Imath_2_5_V2s__op_add(
    Imath_2_5_V2s const * this_
    , Imath_2_5_V2s const * v)
{
    return to_c_copy((to_cpp(this_)) -> operator+(to_cpp_ref(v)));
}

Imath_2_5_V2s const * Imath_2_5_V2s__op_isub(
    Imath_2_5_V2s * this_
    , Imath_2_5_V2s const * v)
{
    return to_c((to_cpp(this_)) -> operator-=(to_cpp_ref(v)));
}

Imath_2_5_V2s Imath_2_5_V2s__op_sub(
    Imath_2_5_V2s const * this_
    , Imath_2_5_V2s const * v)
{
    return to_c_copy((to_cpp(this_)) -> operator-(to_cpp_ref(v)));
}

Imath_2_5_V2s Imath_2_5_V2s__op_sub_1(
    Imath_2_5_V2s const * this_)
{
    return to_c_copy((to_cpp(this_)) -> operator-());
}

Imath_2_5_V2s const * Imath_2_5_V2s_negate(
    Imath_2_5_V2s * this_)
{
    return to_c((to_cpp(this_)) -> negate());
}

Imath_2_5_V2s const * Imath_2_5_V2s__op_imul(
    Imath_2_5_V2s * this_
    , Imath_2_5_V2s const * v)
{
    return to_c((to_cpp(this_)) -> operator*=(to_cpp_ref(v)));
}

Imath_2_5_V2s const * Imath_2_5_V2s__op_imul_1(
    Imath_2_5_V2s * this_
    , short a)
{
    return to_c((to_cpp(this_)) -> operator*=(a));
}

Imath_2_5_V2s Imath_2_5_V2s__op_mul(
    Imath_2_5_V2s const * this_
    , Imath_2_5_V2s const * v)
{
    return to_c_copy((to_cpp(this_)) -> operator*(to_cpp_ref(v)));
}

Imath_2_5_V2s Imath_2_5_V2s__op_mul_1(
    Imath_2_5_V2s const * this_
    , short a)
{
    return to_c_copy((to_cpp(this_)) -> operator*(a));
}

Imath_2_5_V2s const * Imath_2_5_V2s__op_idiv(
    Imath_2_5_V2s * this_
    , Imath_2_5_V2s const * v)
{
    return to_c((to_cpp(this_)) -> operator/=(to_cpp_ref(v)));
}

Imath_2_5_V2s const * Imath_2_5_V2s__op_idiv_1(
    Imath_2_5_V2s * this_
    , short a)
{
    return to_c((to_cpp(this_)) -> operator/=(a));
}

Imath_2_5_V2s Imath_2_5_V2s__op_div(
    Imath_2_5_V2s const * this_
    , Imath_2_5_V2s const * v)
{
    return to_c_copy((to_cpp(this_)) -> operator/(to_cpp_ref(v)));
}

Imath_2_5_V2s Imath_2_5_V2s__op_div_1(
    Imath_2_5_V2s const * this_
    , short a)
{
    return to_c_copy((to_cpp(this_)) -> operator/(a));
}

short Imath_2_5_V2s_length(
    Imath_2_5_V2s const * this_)
{
    return (to_cpp(this_)) -> length();
}

short Imath_2_5_V2s_length2(
    Imath_2_5_V2s const * this_)
{
    return (to_cpp(this_)) -> length2();
}

Imath_2_5_V2s const * Imath_2_5_V2s_normalize(
    Imath_2_5_V2s * this_)
{
    return to_c((to_cpp(this_)) -> normalize());
}

Imath_2_5_V2s const * Imath_2_5_V2s_normalizeExc(
    Imath_2_5_V2s * this_)
{
    return to_c((to_cpp(this_)) -> normalizeExc());
}

Imath_2_5_V2s const * Imath_2_5_V2s_normalizeNonNull(
    Imath_2_5_V2s * this_)
{
    return to_c((to_cpp(this_)) -> normalizeNonNull());
}

Imath_2_5_V2s Imath_2_5_V2s_normalized(
    Imath_2_5_V2s const * this_)
{
    return to_c_copy((to_cpp(this_)) -> normalized());
}

Imath_2_5_V2s Imath_2_5_V2s_normalizedExc(
    Imath_2_5_V2s const * this_)
{
    return to_c_copy((to_cpp(this_)) -> normalizedExc());
}

Imath_2_5_V2s Imath_2_5_V2s_normalizedNonNull(
    Imath_2_5_V2s const * this_)
{
    return to_c_copy((to_cpp(this_)) -> normalizedNonNull());
}

int * Imath_2_5_V2i__index(
    Imath_2_5_V2i * this_
    , int i)
{
    return &((to_cpp(this_)) -> operator[](i));
}

int const * Imath_2_5_V2i__index_1(
    Imath_2_5_V2i const * this_
    , int i)
{
    return &((to_cpp(this_)) -> operator[](i));
}

void Imath_2_5_V2i_Vec2(
    Imath_2_5_V2i * this_)
{
    new (this_) Imath_2_5::Vec2<int>();
}

void Imath_2_5_V2i_Vec2_1(
    Imath_2_5_V2i * this_
    , int a)
{
    new (this_) Imath_2_5::Vec2<int>(a);
}

void Imath_2_5_V2i_Vec2_2(
    Imath_2_5_V2i * this_
    , int a
    , int b)
{
    new (this_) Imath_2_5::Vec2<int>(a, b);
}

void Imath_2_5_V2i_Vec2_3(
    Imath_2_5_V2i * this_
    , Imath_2_5_V2i const * v)
{
    new (this_) Imath_2_5::Vec2<int>(to_cpp_ref(v));
}

Imath_2_5_V2i const * Imath_2_5_V2i__assign(
    Imath_2_5_V2i * this_
    , Imath_2_5_V2i const * v)
{
    return to_c((to_cpp(this_)) -> operator=(to_cpp_ref(v)));
}

void Imath_2_5_V2i_dtor(
    Imath_2_5_V2i * this_)
{
    (to_cpp(this_)) -> Imath_2_5::Vec2<int>::~Vec2();
}

int * Imath_2_5_V2i_getValue(
    Imath_2_5_V2i * this_)
{
    return (to_cpp(this_)) -> getValue();
}

int const * Imath_2_5_V2i_getValue_1(
    Imath_2_5_V2i const * this_)
{
    return (to_cpp(this_)) -> getValue();
}

_Bool Imath_2_5_V2i_equalWithAbsError(
    Imath_2_5_V2i const * this_
    , Imath_2_5_V2i const * v
    , int e)
{
    return (to_cpp(this_)) -> equalWithAbsError(to_cpp_ref(v), e);
}

_Bool Imath_2_5_V2i_equalWithRelError(
    Imath_2_5_V2i const * this_
    , Imath_2_5_V2i const * v
    , int e)
{
    return (to_cpp(this_)) -> equalWithRelError(to_cpp_ref(v), e);
}

int Imath_2_5_V2i_dot(
    Imath_2_5_V2i const * this_
    , Imath_2_5_V2i const * v)
{
    return (to_cpp(this_)) -> dot(to_cpp_ref(v));
}

int Imath_2_5_V2i_operator^(
    Imath_2_5_V2i const * this_
    , Imath_2_5_V2i const * v)
{
    return (to_cpp(this_)) -> operator^(to_cpp_ref(v));
}

int Imath_2_5_V2i_cross(
    Imath_2_5_V2i const * this_
    , Imath_2_5_V2i const * v)
{
    return (to_cpp(this_)) -> cross(to_cpp_ref(v));
}

int Imath_2_5_V2i_operator%(
    Imath_2_5_V2i const * this_
    , Imath_2_5_V2i const * v)
{
    return (to_cpp(this_)) -> operator%(to_cpp_ref(v));
}

Imath_2_5_V2i const * Imath_2_5_V2i__op_iadd(
    Imath_2_5_V2i * this_
    , Imath_2_5_V2i const * v)
{
    return to_c((to_cpp(this_)) -> operator+=(to_cpp_ref(v)));
}

Imath_2_5_V2i Imath_2_5_V2i__op_add(
    Imath_2_5_V2i const * this_
    , Imath_2_5_V2i const * v)
{
    return to_c_copy((to_cpp(this_)) -> operator+(to_cpp_ref(v)));
}

Imath_2_5_V2i const * Imath_2_5_V2i__op_isub(
    Imath_2_5_V2i * this_
    , Imath_2_5_V2i const * v)
{
    return to_c((to_cpp(this_)) -> operator-=(to_cpp_ref(v)));
}

Imath_2_5_V2i Imath_2_5_V2i__op_sub(
    Imath_2_5_V2i const * this_
    , Imath_2_5_V2i const * v)
{
    return to_c_copy((to_cpp(this_)) -> operator-(to_cpp_ref(v)));
}

Imath_2_5_V2i Imath_2_5_V2i__op_sub_1(
    Imath_2_5_V2i const * this_)
{
    return to_c_copy((to_cpp(this_)) -> operator-());
}

Imath_2_5_V2i const * Imath_2_5_V2i_negate(
    Imath_2_5_V2i * this_)
{
    return to_c((to_cpp(this_)) -> negate());
}

Imath_2_5_V2i const * Imath_2_5_V2i__op_imul(
    Imath_2_5_V2i * this_
    , Imath_2_5_V2i const * v)
{
    return to_c((to_cpp(this_)) -> operator*=(to_cpp_ref(v)));
}

Imath_2_5_V2i const * Imath_2_5_V2i__op_imul_1(
    Imath_2_5_V2i * this_
    , int a)
{
    return to_c((to_cpp(this_)) -> operator*=(a));
}

Imath_2_5_V2i Imath_2_5_V2i__op_mul(
    Imath_2_5_V2i const * this_
    , Imath_2_5_V2i const * v)
{
    return to_c_copy((to_cpp(this_)) -> operator*(to_cpp_ref(v)));
}

Imath_2_5_V2i Imath_2_5_V2i__op_mul_1(
    Imath_2_5_V2i const * this_
    , int a)
{
    return to_c_copy((to_cpp(this_)) -> operator*(a));
}

Imath_2_5_V2i const * Imath_2_5_V2i__op_idiv(
    Imath_2_5_V2i * this_
    , Imath_2_5_V2i const * v)
{
    return to_c((to_cpp(this_)) -> operator/=(to_cpp_ref(v)));
}

Imath_2_5_V2i const * Imath_2_5_V2i__op_idiv_1(
    Imath_2_5_V2i * this_
    , int a)
{
    return to_c((to_cpp(this_)) -> operator/=(a));
}

Imath_2_5_V2i Imath_2_5_V2i__op_div(
    Imath_2_5_V2i const * this_
    , Imath_2_5_V2i const * v)
{
    return to_c_copy((to_cpp(this_)) -> operator/(to_cpp_ref(v)));
}

Imath_2_5_V2i Imath_2_5_V2i__op_div_1(
    Imath_2_5_V2i const * this_
    , int a)
{
    return to_c_copy((to_cpp(this_)) -> operator/(a));
}

int Imath_2_5_V2i_length(
    Imath_2_5_V2i const * this_)
{
    return (to_cpp(this_)) -> length();
}

int Imath_2_5_V2i_length2(
    Imath_2_5_V2i const * this_)
{
    return (to_cpp(this_)) -> length2();
}

Imath_2_5_V2i const * Imath_2_5_V2i_normalize(
    Imath_2_5_V2i * this_)
{
    return to_c((to_cpp(this_)) -> normalize());
}

Imath_2_5_V2i const * Imath_2_5_V2i_normalizeExc(
    Imath_2_5_V2i * this_)
{
    return to_c((to_cpp(this_)) -> normalizeExc());
}

Imath_2_5_V2i const * Imath_2_5_V2i_normalizeNonNull(
    Imath_2_5_V2i * this_)
{
    return to_c((to_cpp(this_)) -> normalizeNonNull());
}

Imath_2_5_V2i Imath_2_5_V2i_normalized(
    Imath_2_5_V2i const * this_)
{
    return to_c_copy((to_cpp(this_)) -> normalized());
}

Imath_2_5_V2i Imath_2_5_V2i_normalizedExc(
    Imath_2_5_V2i const * this_)
{
    return to_c_copy((to_cpp(this_)) -> normalizedExc());
}

Imath_2_5_V2i Imath_2_5_V2i_normalizedNonNull(
    Imath_2_5_V2i const * this_)
{
    return to_c_copy((to_cpp(this_)) -> normalizedNonNull());
}

float * Imath_2_5_V2f__index(
    Imath_2_5_V2f * this_
    , int i)
{
    return &((to_cpp(this_)) -> operator[](i));
}

float const * Imath_2_5_V2f__index_1(
    Imath_2_5_V2f const * this_
    , int i)
{
    return &((to_cpp(this_)) -> operator[](i));
}

void Imath_2_5_V2f_Vec2(
    Imath_2_5_V2f * this_)
{
    new (this_) Imath_2_5::Vec2<float>();
}

void Imath_2_5_V2f_Vec2_1(
    Imath_2_5_V2f * this_
    , float a)
{
    new (this_) Imath_2_5::Vec2<float>(a);
}

void Imath_2_5_V2f_Vec2_2(
    Imath_2_5_V2f * this_
    , float a
    , float b)
{
    new (this_) Imath_2_5::Vec2<float>(a, b);
}

void Imath_2_5_V2f_Vec2_3(
    Imath_2_5_V2f * this_
    , Imath_2_5_V2f const * v)
{
    new (this_) Imath_2_5::Vec2<float>(to_cpp_ref(v));
}

Imath_2_5_V2f const * Imath_2_5_V2f__assign(
    Imath_2_5_V2f * this_
    , Imath_2_5_V2f const * v)
{
    return to_c((to_cpp(this_)) -> operator=(to_cpp_ref(v)));
}

void Imath_2_5_V2f_dtor(
    Imath_2_5_V2f * this_)
{
    (to_cpp(this_)) -> Imath_2_5::Vec2<float>::~Vec2();
}

float * Imath_2_5_V2f_getValue(
    Imath_2_5_V2f * this_)
{
    return (to_cpp(this_)) -> getValue();
}

float const * Imath_2_5_V2f_getValue_1(
    Imath_2_5_V2f const * this_)
{
    return (to_cpp(this_)) -> getValue();
}

_Bool Imath_2_5_V2f_equalWithAbsError(
    Imath_2_5_V2f const * this_
    , Imath_2_5_V2f const * v
    , float e)
{
    return (to_cpp(this_)) -> equalWithAbsError(to_cpp_ref(v), e);
}

_Bool Imath_2_5_V2f_equalWithRelError(
    Imath_2_5_V2f const * this_
    , Imath_2_5_V2f const * v
    , float e)
{
    return (to_cpp(this_)) -> equalWithRelError(to_cpp_ref(v), e);
}

float Imath_2_5_V2f_dot(
    Imath_2_5_V2f const * this_
    , Imath_2_5_V2f const * v)
{
    return (to_cpp(this_)) -> dot(to_cpp_ref(v));
}

float Imath_2_5_V2f_operator^(
    Imath_2_5_V2f const * this_
    , Imath_2_5_V2f const * v)
{
    return (to_cpp(this_)) -> operator^(to_cpp_ref(v));
}

float Imath_2_5_V2f_cross(
    Imath_2_5_V2f const * this_
    , Imath_2_5_V2f const * v)
{
    return (to_cpp(this_)) -> cross(to_cpp_ref(v));
}

float Imath_2_5_V2f_operator%(
    Imath_2_5_V2f const * this_
    , Imath_2_5_V2f const * v)
{
    return (to_cpp(this_)) -> operator%(to_cpp_ref(v));
}

Imath_2_5_V2f const * Imath_2_5_V2f__op_iadd(
    Imath_2_5_V2f * this_
    , Imath_2_5_V2f const * v)
{
    return to_c((to_cpp(this_)) -> operator+=(to_cpp_ref(v)));
}

Imath_2_5_V2f Imath_2_5_V2f__op_add(
    Imath_2_5_V2f const * this_
    , Imath_2_5_V2f const * v)
{
    return to_c_copy((to_cpp(this_)) -> operator+(to_cpp_ref(v)));
}

Imath_2_5_V2f const * Imath_2_5_V2f__op_isub(
    Imath_2_5_V2f * this_
    , Imath_2_5_V2f const * v)
{
    return to_c((to_cpp(this_)) -> operator-=(to_cpp_ref(v)));
}

Imath_2_5_V2f Imath_2_5_V2f__op_sub(
    Imath_2_5_V2f const * this_
    , Imath_2_5_V2f const * v)
{
    return to_c_copy((to_cpp(this_)) -> operator-(to_cpp_ref(v)));
}

Imath_2_5_V2f Imath_2_5_V2f__op_sub_1(
    Imath_2_5_V2f const * this_)
{
    return to_c_copy((to_cpp(this_)) -> operator-());
}

Imath_2_5_V2f const * Imath_2_5_V2f_negate(
    Imath_2_5_V2f * this_)
{
    return to_c((to_cpp(this_)) -> negate());
}

Imath_2_5_V2f const * Imath_2_5_V2f__op_imul(
    Imath_2_5_V2f * this_
    , Imath_2_5_V2f const * v)
{
    return to_c((to_cpp(this_)) -> operator*=(to_cpp_ref(v)));
}

Imath_2_5_V2f const * Imath_2_5_V2f__op_imul_1(
    Imath_2_5_V2f * this_
    , float a)
{
    return to_c((to_cpp(this_)) -> operator*=(a));
}

Imath_2_5_V2f Imath_2_5_V2f__op_mul(
    Imath_2_5_V2f const * this_
    , Imath_2_5_V2f const * v)
{
    return to_c_copy((to_cpp(this_)) -> operator*(to_cpp_ref(v)));
}

Imath_2_5_V2f Imath_2_5_V2f__op_mul_1(
    Imath_2_5_V2f const * this_
    , float a)
{
    return to_c_copy((to_cpp(this_)) -> operator*(a));
}

Imath_2_5_V2f const * Imath_2_5_V2f__op_idiv(
    Imath_2_5_V2f * this_
    , Imath_2_5_V2f const * v)
{
    return to_c((to_cpp(this_)) -> operator/=(to_cpp_ref(v)));
}

Imath_2_5_V2f const * Imath_2_5_V2f__op_idiv_1(
    Imath_2_5_V2f * this_
    , float a)
{
    return to_c((to_cpp(this_)) -> operator/=(a));
}

Imath_2_5_V2f Imath_2_5_V2f__op_div(
    Imath_2_5_V2f const * this_
    , Imath_2_5_V2f const * v)
{
    return to_c_copy((to_cpp(this_)) -> operator/(to_cpp_ref(v)));
}

Imath_2_5_V2f Imath_2_5_V2f__op_div_1(
    Imath_2_5_V2f const * this_
    , float a)
{
    return to_c_copy((to_cpp(this_)) -> operator/(a));
}

float Imath_2_5_V2f_length(
    Imath_2_5_V2f const * this_)
{
    return (to_cpp(this_)) -> length();
}

float Imath_2_5_V2f_length2(
    Imath_2_5_V2f const * this_)
{
    return (to_cpp(this_)) -> length2();
}

Imath_2_5_V2f const * Imath_2_5_V2f_normalize(
    Imath_2_5_V2f * this_)
{
    return to_c((to_cpp(this_)) -> normalize());
}

Imath_2_5_V2f const * Imath_2_5_V2f_normalizeExc(
    Imath_2_5_V2f * this_)
{
    return to_c((to_cpp(this_)) -> normalizeExc());
}

Imath_2_5_V2f const * Imath_2_5_V2f_normalizeNonNull(
    Imath_2_5_V2f * this_)
{
    return to_c((to_cpp(this_)) -> normalizeNonNull());
}

Imath_2_5_V2f Imath_2_5_V2f_normalized(
    Imath_2_5_V2f const * this_)
{
    return to_c_copy((to_cpp(this_)) -> normalized());
}

Imath_2_5_V2f Imath_2_5_V2f_normalizedExc(
    Imath_2_5_V2f const * this_)
{
    return to_c_copy((to_cpp(this_)) -> normalizedExc());
}

Imath_2_5_V2f Imath_2_5_V2f_normalizedNonNull(
    Imath_2_5_V2f const * this_)
{
    return to_c_copy((to_cpp(this_)) -> normalizedNonNull());
}

double * Imath_2_5_V2d__index(
    Imath_2_5_V2d * this_
    , int i)
{
    return &((to_cpp(this_)) -> operator[](i));
}

double const * Imath_2_5_V2d__index_1(
    Imath_2_5_V2d const * this_
    , int i)
{
    return &((to_cpp(this_)) -> operator[](i));
}

void Imath_2_5_V2d_Vec2(
    Imath_2_5_V2d * this_)
{
    new (this_) Imath_2_5::Vec2<double>();
}

void Imath_2_5_V2d_Vec2_1(
    Imath_2_5_V2d * this_
    , double a)
{
    new (this_) Imath_2_5::Vec2<double>(a);
}

void Imath_2_5_V2d_Vec2_2(
    Imath_2_5_V2d * this_
    , double a
    , double b)
{
    new (this_) Imath_2_5::Vec2<double>(a, b);
}

void Imath_2_5_V2d_Vec2_3(
    Imath_2_5_V2d * this_
    , Imath_2_5_V2d const * v)
{
    new (this_) Imath_2_5::Vec2<double>(to_cpp_ref(v));
}

Imath_2_5_V2d const * Imath_2_5_V2d__assign(
    Imath_2_5_V2d * this_
    , Imath_2_5_V2d const * v)
{
    return to_c((to_cpp(this_)) -> operator=(to_cpp_ref(v)));
}

void Imath_2_5_V2d_dtor(
    Imath_2_5_V2d * this_)
{
    (to_cpp(this_)) -> Imath_2_5::Vec2<double>::~Vec2();
}

double * Imath_2_5_V2d_getValue(
    Imath_2_5_V2d * this_)
{
    return (to_cpp(this_)) -> getValue();
}

double const * Imath_2_5_V2d_getValue_1(
    Imath_2_5_V2d const * this_)
{
    return (to_cpp(this_)) -> getValue();
}

_Bool Imath_2_5_V2d_equalWithAbsError(
    Imath_2_5_V2d const * this_
    , Imath_2_5_V2d const * v
    , double e)
{
    return (to_cpp(this_)) -> equalWithAbsError(to_cpp_ref(v), e);
}

_Bool Imath_2_5_V2d_equalWithRelError(
    Imath_2_5_V2d const * this_
    , Imath_2_5_V2d const * v
    , double e)
{
    return (to_cpp(this_)) -> equalWithRelError(to_cpp_ref(v), e);
}

double Imath_2_5_V2d_dot(
    Imath_2_5_V2d const * this_
    , Imath_2_5_V2d const * v)
{
    return (to_cpp(this_)) -> dot(to_cpp_ref(v));
}

double Imath_2_5_V2d_operator^(
    Imath_2_5_V2d const * this_
    , Imath_2_5_V2d const * v)
{
    return (to_cpp(this_)) -> operator^(to_cpp_ref(v));
}

double Imath_2_5_V2d_cross(
    Imath_2_5_V2d const * this_
    , Imath_2_5_V2d const * v)
{
    return (to_cpp(this_)) -> cross(to_cpp_ref(v));
}

double Imath_2_5_V2d_operator%(
    Imath_2_5_V2d const * this_
    , Imath_2_5_V2d const * v)
{
    return (to_cpp(this_)) -> operator%(to_cpp_ref(v));
}

Imath_2_5_V2d const * Imath_2_5_V2d__op_iadd(
    Imath_2_5_V2d * this_
    , Imath_2_5_V2d const * v)
{
    return to_c((to_cpp(this_)) -> operator+=(to_cpp_ref(v)));
}

Imath_2_5_V2d Imath_2_5_V2d__op_add(
    Imath_2_5_V2d const * this_
    , Imath_2_5_V2d const * v)
{
    return to_c_copy((to_cpp(this_)) -> operator+(to_cpp_ref(v)));
}

Imath_2_5_V2d const * Imath_2_5_V2d__op_isub(
    Imath_2_5_V2d * this_
    , Imath_2_5_V2d const * v)
{
    return to_c((to_cpp(this_)) -> operator-=(to_cpp_ref(v)));
}

Imath_2_5_V2d Imath_2_5_V2d__op_sub(
    Imath_2_5_V2d const * this_
    , Imath_2_5_V2d const * v)
{
    return to_c_copy((to_cpp(this_)) -> operator-(to_cpp_ref(v)));
}

Imath_2_5_V2d Imath_2_5_V2d__op_sub_1(
    Imath_2_5_V2d const * this_)
{
    return to_c_copy((to_cpp(this_)) -> operator-());
}

Imath_2_5_V2d const * Imath_2_5_V2d_negate(
    Imath_2_5_V2d * this_)
{
    return to_c((to_cpp(this_)) -> negate());
}

Imath_2_5_V2d const * Imath_2_5_V2d__op_imul(
    Imath_2_5_V2d * this_
    , Imath_2_5_V2d const * v)
{
    return to_c((to_cpp(this_)) -> operator*=(to_cpp_ref(v)));
}

Imath_2_5_V2d const * Imath_2_5_V2d__op_imul_1(
    Imath_2_5_V2d * this_
    , double a)
{
    return to_c((to_cpp(this_)) -> operator*=(a));
}

Imath_2_5_V2d Imath_2_5_V2d__op_mul(
    Imath_2_5_V2d const * this_
    , Imath_2_5_V2d const * v)
{
    return to_c_copy((to_cpp(this_)) -> operator*(to_cpp_ref(v)));
}

Imath_2_5_V2d Imath_2_5_V2d__op_mul_1(
    Imath_2_5_V2d const * this_
    , double a)
{
    return to_c_copy((to_cpp(this_)) -> operator*(a));
}

Imath_2_5_V2d const * Imath_2_5_V2d__op_idiv(
    Imath_2_5_V2d * this_
    , Imath_2_5_V2d const * v)
{
    return to_c((to_cpp(this_)) -> operator/=(to_cpp_ref(v)));
}

Imath_2_5_V2d const * Imath_2_5_V2d__op_idiv_1(
    Imath_2_5_V2d * this_
    , double a)
{
    return to_c((to_cpp(this_)) -> operator/=(a));
}

Imath_2_5_V2d Imath_2_5_V2d__op_div(
    Imath_2_5_V2d const * this_
    , Imath_2_5_V2d const * v)
{
    return to_c_copy((to_cpp(this_)) -> operator/(to_cpp_ref(v)));
}

Imath_2_5_V2d Imath_2_5_V2d__op_div_1(
    Imath_2_5_V2d const * this_
    , double a)
{
    return to_c_copy((to_cpp(this_)) -> operator/(a));
}

double Imath_2_5_V2d_length(
    Imath_2_5_V2d const * this_)
{
    return (to_cpp(this_)) -> length();
}

double Imath_2_5_V2d_length2(
    Imath_2_5_V2d const * this_)
{
    return (to_cpp(this_)) -> length2();
}

Imath_2_5_V2d const * Imath_2_5_V2d_normalize(
    Imath_2_5_V2d * this_)
{
    return to_c((to_cpp(this_)) -> normalize());
}

Imath_2_5_V2d const * Imath_2_5_V2d_normalizeExc(
    Imath_2_5_V2d * this_)
{
    return to_c((to_cpp(this_)) -> normalizeExc());
}

Imath_2_5_V2d const * Imath_2_5_V2d_normalizeNonNull(
    Imath_2_5_V2d * this_)
{
    return to_c((to_cpp(this_)) -> normalizeNonNull());
}

Imath_2_5_V2d Imath_2_5_V2d_normalized(
    Imath_2_5_V2d const * this_)
{
    return to_c_copy((to_cpp(this_)) -> normalized());
}

Imath_2_5_V2d Imath_2_5_V2d_normalizedExc(
    Imath_2_5_V2d const * this_)
{
    return to_c_copy((to_cpp(this_)) -> normalizedExc());
}

Imath_2_5_V2d Imath_2_5_V2d_normalizedNonNull(
    Imath_2_5_V2d const * this_)
{
    return to_c_copy((to_cpp(this_)) -> normalizedNonNull());
}

void Imath_2_5_V3s_Vec3(
    Imath_2_5_V3s * this_)
{
    new (this_) Imath_2_5::Vec3<short>();
}

void Imath_2_5_V3s_Vec3_1(
    Imath_2_5_V3s * this_
    , Imath_2_5_V3s const * v)
{
    new (this_) Imath_2_5::Vec3<short>(to_cpp_ref(v));
}

void Imath_2_5_V3i_Vec3(
    Imath_2_5_V3i * this_)
{
    new (this_) Imath_2_5::Vec3<int>();
}

void Imath_2_5_V3i_Vec3_1(
    Imath_2_5_V3i * this_
    , Imath_2_5_V3i const * v)
{
    new (this_) Imath_2_5::Vec3<int>(to_cpp_ref(v));
}

void Imath_2_5_V3f_Vec3(
    Imath_2_5_V3f * this_)
{
    new (this_) Imath_2_5::Vec3<float>();
}

void Imath_2_5_V3f_Vec3_1(
    Imath_2_5_V3f * this_
    , Imath_2_5_V3f const * v)
{
    new (this_) Imath_2_5::Vec3<float>(to_cpp_ref(v));
}

void Imath_2_5_V3d_Vec3(
    Imath_2_5_V3d * this_)
{
    new (this_) Imath_2_5::Vec3<double>();
}

void Imath_2_5_V3d_Vec3_1(
    Imath_2_5_V3d * this_
    , Imath_2_5_V3d const * v)
{
    new (this_) Imath_2_5::Vec3<double>(to_cpp_ref(v));
}

void Imath_2_5_V4s_Vec4(
    Imath_2_5_V4s * this_)
{
    new (this_) Imath_2_5::Vec4<short>();
}

void Imath_2_5_V4s_Vec4_1(
    Imath_2_5_V4s * this_
    , Imath_2_5_V4s const * v)
{
    new (this_) Imath_2_5::Vec4<short>(to_cpp_ref(v));
}

void Imath_2_5_V4i_Vec4(
    Imath_2_5_V4i * this_)
{
    new (this_) Imath_2_5::Vec4<int>();
}

void Imath_2_5_V4i_Vec4_1(
    Imath_2_5_V4i * this_
    , Imath_2_5_V4i const * v)
{
    new (this_) Imath_2_5::Vec4<int>(to_cpp_ref(v));
}

void Imath_2_5_V4f_Vec4(
    Imath_2_5_V4f * this_)
{
    new (this_) Imath_2_5::Vec4<float>();
}

void Imath_2_5_V4f_Vec4_1(
    Imath_2_5_V4f * this_
    , Imath_2_5_V4f const * v)
{
    new (this_) Imath_2_5::Vec4<float>(to_cpp_ref(v));
}

void Imath_2_5_V4d_Vec4(
    Imath_2_5_V4d * this_)
{
    new (this_) Imath_2_5::Vec4<double>();
}

void Imath_2_5_V4d_Vec4_1(
    Imath_2_5_V4d * this_
    , Imath_2_5_V4d const * v)
{
    new (this_) Imath_2_5::Vec4<double>(to_cpp_ref(v));
}
