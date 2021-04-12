#pragma once
#include <imath_vec_.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imath_2_5_V3f_s Imath_2_5_V3f;
typedef struct Imath_2_5_V3i_s Imath_2_5_V3i;
typedef struct Imath_2_5_V3d_s Imath_2_5_V3d;
typedef struct Imath_2_5_V2i_s Imath_2_5_V2i;
typedef struct Imath_2_5_V2d_s Imath_2_5_V2d;
typedef struct Imath_2_5_V3s_s Imath_2_5_V3s;
typedef struct Imath_2_5_V2f_s Imath_2_5_V2f;
typedef struct Imath_2_5_V2s_s Imath_2_5_V2s;
typedef struct Imath_2_5_Box2s_s {
    char data[8];
} __attribute__((aligned(2))) Imath_2_5_Box2s;
typedef struct Imath_2_5_Box2i_s {
    char data[16];
} __attribute__((aligned(4))) Imath_2_5_Box2i;
typedef struct Imath_2_5_Box2f_s {
    char data[16];
} __attribute__((aligned(4))) Imath_2_5_Box2f;
typedef struct Imath_2_5_Box2d_s {
    char data[32];
} __attribute__((aligned(8))) Imath_2_5_Box2d;
typedef struct Imath_2_5_Box3s_s {
    char data[12];
} __attribute__((aligned(2))) Imath_2_5_Box3s;
typedef struct Imath_2_5_Box3i_s {
    char data[24];
} __attribute__((aligned(4))) Imath_2_5_Box3i;
typedef struct Imath_2_5_Box3f_s {
    char data[24];
} __attribute__((aligned(4))) Imath_2_5_Box3f;
typedef struct Imath_2_5_Box3d_s {
    char data[48];
} __attribute__((aligned(8))) Imath_2_5_Box3d;


void Imath_2_5_Box2s_Box(
    Imath_2_5_Box2s * this_);


void Imath_2_5_Box2s_Box_1(
    Imath_2_5_Box2s * this_
    , Imath_2_5_V2s const * point);


void Imath_2_5_Box2s_Box_2(
    Imath_2_5_Box2s * this_
    , Imath_2_5_V2s const * minV
    , Imath_2_5_V2s const * maxV);


void Imath_2_5_Box2s_makeEmpty(
    Imath_2_5_Box2s * this_);


void Imath_2_5_Box2s_extendBy(
    Imath_2_5_Box2s * this_
    , Imath_2_5_V2s const * point);


void Imath_2_5_Box2s_makeInfinite(
    Imath_2_5_Box2s * this_);


Imath_2_5_V2s Imath_2_5_Box2s_size(
    Imath_2_5_Box2s const * this_);


Imath_2_5_V2s Imath_2_5_Box2s_center(
    Imath_2_5_Box2s const * this_);


_Bool Imath_2_5_Box2s_intersects(
    Imath_2_5_Box2s const * this_
    , Imath_2_5_V2s const * point);


unsigned int Imath_2_5_Box2s_majorAxis(
    Imath_2_5_Box2s const * this_);


_Bool Imath_2_5_Box2s_isEmpty(
    Imath_2_5_Box2s const * this_);


_Bool Imath_2_5_Box2s_hasVolume(
    Imath_2_5_Box2s const * this_);


_Bool Imath_2_5_Box2s_isInfinite(
    Imath_2_5_Box2s const * this_);


void Imath_2_5_Box2s_Box_3(
    Imath_2_5_Box2s * this_
    , Imath_2_5_Box2s const * rhs);











void Imath_2_5_Box2i_Box(
    Imath_2_5_Box2i * this_);


void Imath_2_5_Box2i_Box_1(
    Imath_2_5_Box2i * this_
    , Imath_2_5_V2i const * point);


void Imath_2_5_Box2i_Box_2(
    Imath_2_5_Box2i * this_
    , Imath_2_5_V2i const * minV
    , Imath_2_5_V2i const * maxV);


void Imath_2_5_Box2i_makeEmpty(
    Imath_2_5_Box2i * this_);


void Imath_2_5_Box2i_extendBy(
    Imath_2_5_Box2i * this_
    , Imath_2_5_V2i const * point);


void Imath_2_5_Box2i_makeInfinite(
    Imath_2_5_Box2i * this_);


Imath_2_5_V2i Imath_2_5_Box2i_size(
    Imath_2_5_Box2i const * this_);


Imath_2_5_V2i Imath_2_5_Box2i_center(
    Imath_2_5_Box2i const * this_);


_Bool Imath_2_5_Box2i_intersects(
    Imath_2_5_Box2i const * this_
    , Imath_2_5_V2i const * point);


unsigned int Imath_2_5_Box2i_majorAxis(
    Imath_2_5_Box2i const * this_);


_Bool Imath_2_5_Box2i_isEmpty(
    Imath_2_5_Box2i const * this_);


_Bool Imath_2_5_Box2i_hasVolume(
    Imath_2_5_Box2i const * this_);


_Bool Imath_2_5_Box2i_isInfinite(
    Imath_2_5_Box2i const * this_);


void Imath_2_5_Box2i_Box_3(
    Imath_2_5_Box2i * this_
    , Imath_2_5_Box2i const * rhs);











void Imath_2_5_Box2f_Box(
    Imath_2_5_Box2f * this_);


void Imath_2_5_Box2f_Box_1(
    Imath_2_5_Box2f * this_
    , Imath_2_5_V2f const * point);


void Imath_2_5_Box2f_Box_2(
    Imath_2_5_Box2f * this_
    , Imath_2_5_V2f const * minV
    , Imath_2_5_V2f const * maxV);


void Imath_2_5_Box2f_makeEmpty(
    Imath_2_5_Box2f * this_);


void Imath_2_5_Box2f_extendBy(
    Imath_2_5_Box2f * this_
    , Imath_2_5_V2f const * point);


void Imath_2_5_Box2f_makeInfinite(
    Imath_2_5_Box2f * this_);


Imath_2_5_V2f Imath_2_5_Box2f_size(
    Imath_2_5_Box2f const * this_);


Imath_2_5_V2f Imath_2_5_Box2f_center(
    Imath_2_5_Box2f const * this_);


_Bool Imath_2_5_Box2f_intersects(
    Imath_2_5_Box2f const * this_
    , Imath_2_5_V2f const * point);


unsigned int Imath_2_5_Box2f_majorAxis(
    Imath_2_5_Box2f const * this_);


_Bool Imath_2_5_Box2f_isEmpty(
    Imath_2_5_Box2f const * this_);


_Bool Imath_2_5_Box2f_hasVolume(
    Imath_2_5_Box2f const * this_);


_Bool Imath_2_5_Box2f_isInfinite(
    Imath_2_5_Box2f const * this_);


void Imath_2_5_Box2f_Box_3(
    Imath_2_5_Box2f * this_
    , Imath_2_5_Box2f const * rhs);











void Imath_2_5_Box2d_Box(
    Imath_2_5_Box2d * this_);


void Imath_2_5_Box2d_Box_1(
    Imath_2_5_Box2d * this_
    , Imath_2_5_V2d const * point);


void Imath_2_5_Box2d_Box_2(
    Imath_2_5_Box2d * this_
    , Imath_2_5_V2d const * minV
    , Imath_2_5_V2d const * maxV);


void Imath_2_5_Box2d_makeEmpty(
    Imath_2_5_Box2d * this_);


void Imath_2_5_Box2d_extendBy(
    Imath_2_5_Box2d * this_
    , Imath_2_5_V2d const * point);


void Imath_2_5_Box2d_makeInfinite(
    Imath_2_5_Box2d * this_);


Imath_2_5_V2d Imath_2_5_Box2d_size(
    Imath_2_5_Box2d const * this_);


Imath_2_5_V2d Imath_2_5_Box2d_center(
    Imath_2_5_Box2d const * this_);


_Bool Imath_2_5_Box2d_intersects(
    Imath_2_5_Box2d const * this_
    , Imath_2_5_V2d const * point);


unsigned int Imath_2_5_Box2d_majorAxis(
    Imath_2_5_Box2d const * this_);


_Bool Imath_2_5_Box2d_isEmpty(
    Imath_2_5_Box2d const * this_);


_Bool Imath_2_5_Box2d_hasVolume(
    Imath_2_5_Box2d const * this_);


_Bool Imath_2_5_Box2d_isInfinite(
    Imath_2_5_Box2d const * this_);


void Imath_2_5_Box2d_Box_3(
    Imath_2_5_Box2d * this_
    , Imath_2_5_Box2d const * rhs);











void Imath_2_5_Box3s_Box(
    Imath_2_5_Box3s * this_);


void Imath_2_5_Box3s_Box_1(
    Imath_2_5_Box3s * this_
    , Imath_2_5_V3s const * point);


void Imath_2_5_Box3s_Box_2(
    Imath_2_5_Box3s * this_
    , Imath_2_5_V3s const * minV
    , Imath_2_5_V3s const * maxV);


void Imath_2_5_Box3s_makeEmpty(
    Imath_2_5_Box3s * this_);


void Imath_2_5_Box3s_extendBy(
    Imath_2_5_Box3s * this_
    , Imath_2_5_V3s const * point);


void Imath_2_5_Box3s_makeInfinite(
    Imath_2_5_Box3s * this_);


Imath_2_5_V3s Imath_2_5_Box3s_size(
    Imath_2_5_Box3s const * this_);


Imath_2_5_V3s Imath_2_5_Box3s_center(
    Imath_2_5_Box3s const * this_);


_Bool Imath_2_5_Box3s_intersects(
    Imath_2_5_Box3s const * this_
    , Imath_2_5_V3s const * point);


unsigned int Imath_2_5_Box3s_majorAxis(
    Imath_2_5_Box3s const * this_);


_Bool Imath_2_5_Box3s_isEmpty(
    Imath_2_5_Box3s const * this_);


_Bool Imath_2_5_Box3s_hasVolume(
    Imath_2_5_Box3s const * this_);


_Bool Imath_2_5_Box3s_isInfinite(
    Imath_2_5_Box3s const * this_);


void Imath_2_5_Box3s_Box_3(
    Imath_2_5_Box3s * this_
    , Imath_2_5_Box3s const * rhs);











void Imath_2_5_Box3i_Box(
    Imath_2_5_Box3i * this_);


void Imath_2_5_Box3i_Box_1(
    Imath_2_5_Box3i * this_
    , Imath_2_5_V3i const * point);


void Imath_2_5_Box3i_Box_2(
    Imath_2_5_Box3i * this_
    , Imath_2_5_V3i const * minV
    , Imath_2_5_V3i const * maxV);


void Imath_2_5_Box3i_makeEmpty(
    Imath_2_5_Box3i * this_);


void Imath_2_5_Box3i_extendBy(
    Imath_2_5_Box3i * this_
    , Imath_2_5_V3i const * point);


void Imath_2_5_Box3i_makeInfinite(
    Imath_2_5_Box3i * this_);


Imath_2_5_V3i Imath_2_5_Box3i_size(
    Imath_2_5_Box3i const * this_);


Imath_2_5_V3i Imath_2_5_Box3i_center(
    Imath_2_5_Box3i const * this_);


_Bool Imath_2_5_Box3i_intersects(
    Imath_2_5_Box3i const * this_
    , Imath_2_5_V3i const * point);


unsigned int Imath_2_5_Box3i_majorAxis(
    Imath_2_5_Box3i const * this_);


_Bool Imath_2_5_Box3i_isEmpty(
    Imath_2_5_Box3i const * this_);


_Bool Imath_2_5_Box3i_hasVolume(
    Imath_2_5_Box3i const * this_);


_Bool Imath_2_5_Box3i_isInfinite(
    Imath_2_5_Box3i const * this_);


void Imath_2_5_Box3i_Box_3(
    Imath_2_5_Box3i * this_
    , Imath_2_5_Box3i const * rhs);











void Imath_2_5_Box3f_Box(
    Imath_2_5_Box3f * this_);


void Imath_2_5_Box3f_Box_1(
    Imath_2_5_Box3f * this_
    , Imath_2_5_V3f const * point);


void Imath_2_5_Box3f_Box_2(
    Imath_2_5_Box3f * this_
    , Imath_2_5_V3f const * minV
    , Imath_2_5_V3f const * maxV);


void Imath_2_5_Box3f_makeEmpty(
    Imath_2_5_Box3f * this_);


void Imath_2_5_Box3f_extendBy(
    Imath_2_5_Box3f * this_
    , Imath_2_5_V3f const * point);


void Imath_2_5_Box3f_makeInfinite(
    Imath_2_5_Box3f * this_);


Imath_2_5_V3f Imath_2_5_Box3f_size(
    Imath_2_5_Box3f const * this_);


Imath_2_5_V3f Imath_2_5_Box3f_center(
    Imath_2_5_Box3f const * this_);


_Bool Imath_2_5_Box3f_intersects(
    Imath_2_5_Box3f const * this_
    , Imath_2_5_V3f const * point);


unsigned int Imath_2_5_Box3f_majorAxis(
    Imath_2_5_Box3f const * this_);


_Bool Imath_2_5_Box3f_isEmpty(
    Imath_2_5_Box3f const * this_);


_Bool Imath_2_5_Box3f_hasVolume(
    Imath_2_5_Box3f const * this_);


_Bool Imath_2_5_Box3f_isInfinite(
    Imath_2_5_Box3f const * this_);


void Imath_2_5_Box3f_Box_3(
    Imath_2_5_Box3f * this_
    , Imath_2_5_Box3f const * rhs);











void Imath_2_5_Box3d_Box(
    Imath_2_5_Box3d * this_);


void Imath_2_5_Box3d_Box_1(
    Imath_2_5_Box3d * this_
    , Imath_2_5_V3d const * point);


void Imath_2_5_Box3d_Box_2(
    Imath_2_5_Box3d * this_
    , Imath_2_5_V3d const * minV
    , Imath_2_5_V3d const * maxV);


void Imath_2_5_Box3d_makeEmpty(
    Imath_2_5_Box3d * this_);


void Imath_2_5_Box3d_extendBy(
    Imath_2_5_Box3d * this_
    , Imath_2_5_V3d const * point);


void Imath_2_5_Box3d_makeInfinite(
    Imath_2_5_Box3d * this_);


Imath_2_5_V3d Imath_2_5_Box3d_size(
    Imath_2_5_Box3d const * this_);


Imath_2_5_V3d Imath_2_5_Box3d_center(
    Imath_2_5_Box3d const * this_);


_Bool Imath_2_5_Box3d_intersects(
    Imath_2_5_Box3d const * this_
    , Imath_2_5_V3d const * point);


unsigned int Imath_2_5_Box3d_majorAxis(
    Imath_2_5_Box3d const * this_);


_Bool Imath_2_5_Box3d_isEmpty(
    Imath_2_5_Box3d const * this_);


_Bool Imath_2_5_Box3d_hasVolume(
    Imath_2_5_Box3d const * this_);


_Bool Imath_2_5_Box3d_isInfinite(
    Imath_2_5_Box3d const * this_);


void Imath_2_5_Box3d_Box_3(
    Imath_2_5_Box3d * this_
    , Imath_2_5_Box3d const * rhs);









#ifdef __cplusplus
}
#endif
