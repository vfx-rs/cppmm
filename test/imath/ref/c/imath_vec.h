
typedef struct Imath_2_5_V3f_s {
    char data[12];
} __attribute__((aligned(4))) Imath_2_5_V3f;


void Imath_2_5_V3f_Vec3(
    Imath_2_5_V3f * self);


void Imath_2_5_V3f_Vec3(
    Imath_2_5_V3f * self
    , Imath_2_5_V3f const * v);


void Imath_2_5_V3f_setValue(
    Imath_2_5_V3f * self
    , float a
    , float b
    , float c);


float Imath_2_5_V3f_dot(
    Imath_2_5_V3f const * self
    , Imath_2_5_V3f const * v);


Imath_2_5_V3f Imath_2_5_V3f_cross(
    Imath_2_5_V3f const * self
    , Imath_2_5_V3f const * v);


Imath_2_5_V3f const * Imath_2_5_V3f_operator+=(
    Imath_2_5_V3f * self
    , Imath_2_5_V3f const * v);


float Imath_2_5_V3f_length(
    Imath_2_5_V3f const * self);


float Imath_2_5_V3f_length2(
    Imath_2_5_V3f const * self);


Imath_2_5_V3f const * Imath_2_5_V3f_normalize(
    Imath_2_5_V3f * self);


Imath_2_5_V3f Imath_2_5_V3f_normalized(
    Imath_2_5_V3f const * self);









