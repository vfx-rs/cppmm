#pragma once

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imath_2_5__Vec3_float__t_s Imath_2_5__Vec3_float__t;
typedef Imath_2_5__Vec3_float__t Imath_V3f_t;


typedef struct Imath_2_5__Box_Imath__Vec3_float___t_s {
    char data[24];
} __attribute__((aligned(4))) Imath_2_5__Box_Imath__Vec3_float___t;
typedef Imath_2_5__Box_Imath__Vec3_float___t Imath_Box3f_t;

typedef struct Imath_2_5__Box_Imath__Vec3_int___t_s {
    char data[24];
} __attribute__((aligned(4))) Imath_2_5__Box_Imath__Vec3_int___t;
typedef Imath_2_5__Box_Imath__Vec3_int___t Imath_Box3i_t;




void Imath_2_5__Box_Imath__Vec3_float___extendBy(
    Imath_Box3f_t * this_
    , Imath_V3f_t const * point);

#define Imath_Box3f_extendBy Imath_2_5__Box_Imath__Vec3_float___extendBy



void Imath_2_5__Box_Imath__Vec3_float___extendBy_1(
    Imath_Box3f_t * this_
    , Imath_Box3f_t const * box);

#define Imath_Box3f_extendBy_1 Imath_2_5__Box_Imath__Vec3_float___extendBy_1











void Imath_2_5__Box_Imath__Vec3_int___extendBy(
    Imath_Box3i_t * this_
    , Imath_Box3i_t const * box);

#define Imath_Box3i_extendBy Imath_2_5__Box_Imath__Vec3_int___extendBy









#ifdef __cplusplus
}
#endif
