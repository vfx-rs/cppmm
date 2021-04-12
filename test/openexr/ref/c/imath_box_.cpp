#include <imath_box_private_.h>

#include <imath_vec_private_.h>
#include <new>


void Imath_2_5_Box2s_Box(
    Imath_2_5_Box2s * this_)
{
    new (this_) Imath_2_5::Box<Imath_2_5::Vec2<short> >();
}

void Imath_2_5_Box2s_Box_1(
    Imath_2_5_Box2s * this_
    , Imath_2_5_V2s const * point)
{
    new (this_) Imath_2_5::Box<Imath_2_5::Vec2<short> >(to_cpp_ref(point));
}

void Imath_2_5_Box2s_Box_2(
    Imath_2_5_Box2s * this_
    , Imath_2_5_V2s const * minV
    , Imath_2_5_V2s const * maxV)
{
    new (this_) Imath_2_5::Box<Imath_2_5::Vec2<short> >(to_cpp_ref(minV), to_cpp_ref(maxV));
}

void Imath_2_5_Box2s_makeEmpty(
    Imath_2_5_Box2s * this_)
{
    (to_cpp(this_)) -> makeEmpty();
}

void Imath_2_5_Box2s_extendBy(
    Imath_2_5_Box2s * this_
    , Imath_2_5_V2s const * point)
{
    (to_cpp(this_)) -> extendBy(to_cpp_ref(point));
}

void Imath_2_5_Box2s_makeInfinite(
    Imath_2_5_Box2s * this_)
{
    (to_cpp(this_)) -> makeInfinite();
}

Imath_2_5_V2s Imath_2_5_Box2s_size(
    Imath_2_5_Box2s const * this_)
{
    return to_c_copy((to_cpp(this_)) -> size());
}

Imath_2_5_V2s Imath_2_5_Box2s_center(
    Imath_2_5_Box2s const * this_)
{
    return to_c_copy((to_cpp(this_)) -> center());
}

_Bool Imath_2_5_Box2s_intersects(
    Imath_2_5_Box2s const * this_
    , Imath_2_5_V2s const * point)
{
    return (to_cpp(this_)) -> intersects(to_cpp_ref(point));
}

unsigned int Imath_2_5_Box2s_majorAxis(
    Imath_2_5_Box2s const * this_)
{
    return (to_cpp(this_)) -> majorAxis();
}

_Bool Imath_2_5_Box2s_isEmpty(
    Imath_2_5_Box2s const * this_)
{
    return (to_cpp(this_)) -> isEmpty();
}

_Bool Imath_2_5_Box2s_hasVolume(
    Imath_2_5_Box2s const * this_)
{
    return (to_cpp(this_)) -> hasVolume();
}

_Bool Imath_2_5_Box2s_isInfinite(
    Imath_2_5_Box2s const * this_)
{
    return (to_cpp(this_)) -> isInfinite();
}

void Imath_2_5_Box2s_Box_3(
    Imath_2_5_Box2s * this_
    , Imath_2_5_Box2s const * rhs)
{
    new (this_) Imath_2_5::Box<Imath_2_5::Vec2<short> >(to_cpp_ref(rhs));
}

void Imath_2_5_Box2i_Box(
    Imath_2_5_Box2i * this_)
{
    new (this_) Imath_2_5::Box<Imath_2_5::Vec2<int> >();
}

void Imath_2_5_Box2i_Box_1(
    Imath_2_5_Box2i * this_
    , Imath_2_5_V2i const * point)
{
    new (this_) Imath_2_5::Box<Imath_2_5::Vec2<int> >(to_cpp_ref(point));
}

void Imath_2_5_Box2i_Box_2(
    Imath_2_5_Box2i * this_
    , Imath_2_5_V2i const * minV
    , Imath_2_5_V2i const * maxV)
{
    new (this_) Imath_2_5::Box<Imath_2_5::Vec2<int> >(to_cpp_ref(minV), to_cpp_ref(maxV));
}

void Imath_2_5_Box2i_makeEmpty(
    Imath_2_5_Box2i * this_)
{
    (to_cpp(this_)) -> makeEmpty();
}

void Imath_2_5_Box2i_extendBy(
    Imath_2_5_Box2i * this_
    , Imath_2_5_V2i const * point)
{
    (to_cpp(this_)) -> extendBy(to_cpp_ref(point));
}

void Imath_2_5_Box2i_makeInfinite(
    Imath_2_5_Box2i * this_)
{
    (to_cpp(this_)) -> makeInfinite();
}

Imath_2_5_V2i Imath_2_5_Box2i_size(
    Imath_2_5_Box2i const * this_)
{
    return to_c_copy((to_cpp(this_)) -> size());
}

Imath_2_5_V2i Imath_2_5_Box2i_center(
    Imath_2_5_Box2i const * this_)
{
    return to_c_copy((to_cpp(this_)) -> center());
}

_Bool Imath_2_5_Box2i_intersects(
    Imath_2_5_Box2i const * this_
    , Imath_2_5_V2i const * point)
{
    return (to_cpp(this_)) -> intersects(to_cpp_ref(point));
}

unsigned int Imath_2_5_Box2i_majorAxis(
    Imath_2_5_Box2i const * this_)
{
    return (to_cpp(this_)) -> majorAxis();
}

_Bool Imath_2_5_Box2i_isEmpty(
    Imath_2_5_Box2i const * this_)
{
    return (to_cpp(this_)) -> isEmpty();
}

_Bool Imath_2_5_Box2i_hasVolume(
    Imath_2_5_Box2i const * this_)
{
    return (to_cpp(this_)) -> hasVolume();
}

_Bool Imath_2_5_Box2i_isInfinite(
    Imath_2_5_Box2i const * this_)
{
    return (to_cpp(this_)) -> isInfinite();
}

void Imath_2_5_Box2i_Box_3(
    Imath_2_5_Box2i * this_
    , Imath_2_5_Box2i const * rhs)
{
    new (this_) Imath_2_5::Box<Imath_2_5::Vec2<int> >(to_cpp_ref(rhs));
}

void Imath_2_5_Box2f_Box(
    Imath_2_5_Box2f * this_)
{
    new (this_) Imath_2_5::Box<Imath_2_5::Vec2<float> >();
}

void Imath_2_5_Box2f_Box_1(
    Imath_2_5_Box2f * this_
    , Imath_2_5_V2f const * point)
{
    new (this_) Imath_2_5::Box<Imath_2_5::Vec2<float> >(to_cpp_ref(point));
}

void Imath_2_5_Box2f_Box_2(
    Imath_2_5_Box2f * this_
    , Imath_2_5_V2f const * minV
    , Imath_2_5_V2f const * maxV)
{
    new (this_) Imath_2_5::Box<Imath_2_5::Vec2<float> >(to_cpp_ref(minV), to_cpp_ref(maxV));
}

void Imath_2_5_Box2f_makeEmpty(
    Imath_2_5_Box2f * this_)
{
    (to_cpp(this_)) -> makeEmpty();
}

void Imath_2_5_Box2f_extendBy(
    Imath_2_5_Box2f * this_
    , Imath_2_5_V2f const * point)
{
    (to_cpp(this_)) -> extendBy(to_cpp_ref(point));
}

void Imath_2_5_Box2f_makeInfinite(
    Imath_2_5_Box2f * this_)
{
    (to_cpp(this_)) -> makeInfinite();
}

Imath_2_5_V2f Imath_2_5_Box2f_size(
    Imath_2_5_Box2f const * this_)
{
    return to_c_copy((to_cpp(this_)) -> size());
}

Imath_2_5_V2f Imath_2_5_Box2f_center(
    Imath_2_5_Box2f const * this_)
{
    return to_c_copy((to_cpp(this_)) -> center());
}

_Bool Imath_2_5_Box2f_intersects(
    Imath_2_5_Box2f const * this_
    , Imath_2_5_V2f const * point)
{
    return (to_cpp(this_)) -> intersects(to_cpp_ref(point));
}

unsigned int Imath_2_5_Box2f_majorAxis(
    Imath_2_5_Box2f const * this_)
{
    return (to_cpp(this_)) -> majorAxis();
}

_Bool Imath_2_5_Box2f_isEmpty(
    Imath_2_5_Box2f const * this_)
{
    return (to_cpp(this_)) -> isEmpty();
}

_Bool Imath_2_5_Box2f_hasVolume(
    Imath_2_5_Box2f const * this_)
{
    return (to_cpp(this_)) -> hasVolume();
}

_Bool Imath_2_5_Box2f_isInfinite(
    Imath_2_5_Box2f const * this_)
{
    return (to_cpp(this_)) -> isInfinite();
}

void Imath_2_5_Box2f_Box_3(
    Imath_2_5_Box2f * this_
    , Imath_2_5_Box2f const * rhs)
{
    new (this_) Imath_2_5::Box<Imath_2_5::Vec2<float> >(to_cpp_ref(rhs));
}

void Imath_2_5_Box2d_Box(
    Imath_2_5_Box2d * this_)
{
    new (this_) Imath_2_5::Box<Imath_2_5::Vec2<double> >();
}

void Imath_2_5_Box2d_Box_1(
    Imath_2_5_Box2d * this_
    , Imath_2_5_V2d const * point)
{
    new (this_) Imath_2_5::Box<Imath_2_5::Vec2<double> >(to_cpp_ref(point));
}

void Imath_2_5_Box2d_Box_2(
    Imath_2_5_Box2d * this_
    , Imath_2_5_V2d const * minV
    , Imath_2_5_V2d const * maxV)
{
    new (this_) Imath_2_5::Box<Imath_2_5::Vec2<double> >(to_cpp_ref(minV), to_cpp_ref(maxV));
}

void Imath_2_5_Box2d_makeEmpty(
    Imath_2_5_Box2d * this_)
{
    (to_cpp(this_)) -> makeEmpty();
}

void Imath_2_5_Box2d_extendBy(
    Imath_2_5_Box2d * this_
    , Imath_2_5_V2d const * point)
{
    (to_cpp(this_)) -> extendBy(to_cpp_ref(point));
}

void Imath_2_5_Box2d_makeInfinite(
    Imath_2_5_Box2d * this_)
{
    (to_cpp(this_)) -> makeInfinite();
}

Imath_2_5_V2d Imath_2_5_Box2d_size(
    Imath_2_5_Box2d const * this_)
{
    return to_c_copy((to_cpp(this_)) -> size());
}

Imath_2_5_V2d Imath_2_5_Box2d_center(
    Imath_2_5_Box2d const * this_)
{
    return to_c_copy((to_cpp(this_)) -> center());
}

_Bool Imath_2_5_Box2d_intersects(
    Imath_2_5_Box2d const * this_
    , Imath_2_5_V2d const * point)
{
    return (to_cpp(this_)) -> intersects(to_cpp_ref(point));
}

unsigned int Imath_2_5_Box2d_majorAxis(
    Imath_2_5_Box2d const * this_)
{
    return (to_cpp(this_)) -> majorAxis();
}

_Bool Imath_2_5_Box2d_isEmpty(
    Imath_2_5_Box2d const * this_)
{
    return (to_cpp(this_)) -> isEmpty();
}

_Bool Imath_2_5_Box2d_hasVolume(
    Imath_2_5_Box2d const * this_)
{
    return (to_cpp(this_)) -> hasVolume();
}

_Bool Imath_2_5_Box2d_isInfinite(
    Imath_2_5_Box2d const * this_)
{
    return (to_cpp(this_)) -> isInfinite();
}

void Imath_2_5_Box2d_Box_3(
    Imath_2_5_Box2d * this_
    , Imath_2_5_Box2d const * rhs)
{
    new (this_) Imath_2_5::Box<Imath_2_5::Vec2<double> >(to_cpp_ref(rhs));
}

void Imath_2_5_Box3s_Box(
    Imath_2_5_Box3s * this_)
{
    new (this_) Imath_2_5::Box<Imath_2_5::Vec3<short> >();
}

void Imath_2_5_Box3s_Box_1(
    Imath_2_5_Box3s * this_
    , Imath_2_5_V3s const * point)
{
    new (this_) Imath_2_5::Box<Imath_2_5::Vec3<short> >(to_cpp_ref(point));
}

void Imath_2_5_Box3s_Box_2(
    Imath_2_5_Box3s * this_
    , Imath_2_5_V3s const * minV
    , Imath_2_5_V3s const * maxV)
{
    new (this_) Imath_2_5::Box<Imath_2_5::Vec3<short> >(to_cpp_ref(minV), to_cpp_ref(maxV));
}

void Imath_2_5_Box3s_makeEmpty(
    Imath_2_5_Box3s * this_)
{
    (to_cpp(this_)) -> makeEmpty();
}

void Imath_2_5_Box3s_extendBy(
    Imath_2_5_Box3s * this_
    , Imath_2_5_V3s const * point)
{
    (to_cpp(this_)) -> extendBy(to_cpp_ref(point));
}

void Imath_2_5_Box3s_makeInfinite(
    Imath_2_5_Box3s * this_)
{
    (to_cpp(this_)) -> makeInfinite();
}

Imath_2_5_V3s Imath_2_5_Box3s_size(
    Imath_2_5_Box3s const * this_)
{
    return to_c_copy((to_cpp(this_)) -> size());
}

Imath_2_5_V3s Imath_2_5_Box3s_center(
    Imath_2_5_Box3s const * this_)
{
    return to_c_copy((to_cpp(this_)) -> center());
}

_Bool Imath_2_5_Box3s_intersects(
    Imath_2_5_Box3s const * this_
    , Imath_2_5_V3s const * point)
{
    return (to_cpp(this_)) -> intersects(to_cpp_ref(point));
}

unsigned int Imath_2_5_Box3s_majorAxis(
    Imath_2_5_Box3s const * this_)
{
    return (to_cpp(this_)) -> majorAxis();
}

_Bool Imath_2_5_Box3s_isEmpty(
    Imath_2_5_Box3s const * this_)
{
    return (to_cpp(this_)) -> isEmpty();
}

_Bool Imath_2_5_Box3s_hasVolume(
    Imath_2_5_Box3s const * this_)
{
    return (to_cpp(this_)) -> hasVolume();
}

_Bool Imath_2_5_Box3s_isInfinite(
    Imath_2_5_Box3s const * this_)
{
    return (to_cpp(this_)) -> isInfinite();
}

void Imath_2_5_Box3s_Box_3(
    Imath_2_5_Box3s * this_
    , Imath_2_5_Box3s const * rhs)
{
    new (this_) Imath_2_5::Box<Imath_2_5::Vec3<short> >(to_cpp_ref(rhs));
}

void Imath_2_5_Box3i_Box(
    Imath_2_5_Box3i * this_)
{
    new (this_) Imath_2_5::Box<Imath_2_5::Vec3<int> >();
}

void Imath_2_5_Box3i_Box_1(
    Imath_2_5_Box3i * this_
    , Imath_2_5_V3i const * point)
{
    new (this_) Imath_2_5::Box<Imath_2_5::Vec3<int> >(to_cpp_ref(point));
}

void Imath_2_5_Box3i_Box_2(
    Imath_2_5_Box3i * this_
    , Imath_2_5_V3i const * minV
    , Imath_2_5_V3i const * maxV)
{
    new (this_) Imath_2_5::Box<Imath_2_5::Vec3<int> >(to_cpp_ref(minV), to_cpp_ref(maxV));
}

void Imath_2_5_Box3i_makeEmpty(
    Imath_2_5_Box3i * this_)
{
    (to_cpp(this_)) -> makeEmpty();
}

void Imath_2_5_Box3i_extendBy(
    Imath_2_5_Box3i * this_
    , Imath_2_5_V3i const * point)
{
    (to_cpp(this_)) -> extendBy(to_cpp_ref(point));
}

void Imath_2_5_Box3i_makeInfinite(
    Imath_2_5_Box3i * this_)
{
    (to_cpp(this_)) -> makeInfinite();
}

Imath_2_5_V3i Imath_2_5_Box3i_size(
    Imath_2_5_Box3i const * this_)
{
    return to_c_copy((to_cpp(this_)) -> size());
}

Imath_2_5_V3i Imath_2_5_Box3i_center(
    Imath_2_5_Box3i const * this_)
{
    return to_c_copy((to_cpp(this_)) -> center());
}

_Bool Imath_2_5_Box3i_intersects(
    Imath_2_5_Box3i const * this_
    , Imath_2_5_V3i const * point)
{
    return (to_cpp(this_)) -> intersects(to_cpp_ref(point));
}

unsigned int Imath_2_5_Box3i_majorAxis(
    Imath_2_5_Box3i const * this_)
{
    return (to_cpp(this_)) -> majorAxis();
}

_Bool Imath_2_5_Box3i_isEmpty(
    Imath_2_5_Box3i const * this_)
{
    return (to_cpp(this_)) -> isEmpty();
}

_Bool Imath_2_5_Box3i_hasVolume(
    Imath_2_5_Box3i const * this_)
{
    return (to_cpp(this_)) -> hasVolume();
}

_Bool Imath_2_5_Box3i_isInfinite(
    Imath_2_5_Box3i const * this_)
{
    return (to_cpp(this_)) -> isInfinite();
}

void Imath_2_5_Box3i_Box_3(
    Imath_2_5_Box3i * this_
    , Imath_2_5_Box3i const * rhs)
{
    new (this_) Imath_2_5::Box<Imath_2_5::Vec3<int> >(to_cpp_ref(rhs));
}

void Imath_2_5_Box3f_Box(
    Imath_2_5_Box3f * this_)
{
    new (this_) Imath_2_5::Box<Imath_2_5::Vec3<float> >();
}

void Imath_2_5_Box3f_Box_1(
    Imath_2_5_Box3f * this_
    , Imath_2_5_V3f const * point)
{
    new (this_) Imath_2_5::Box<Imath_2_5::Vec3<float> >(to_cpp_ref(point));
}

void Imath_2_5_Box3f_Box_2(
    Imath_2_5_Box3f * this_
    , Imath_2_5_V3f const * minV
    , Imath_2_5_V3f const * maxV)
{
    new (this_) Imath_2_5::Box<Imath_2_5::Vec3<float> >(to_cpp_ref(minV), to_cpp_ref(maxV));
}

void Imath_2_5_Box3f_makeEmpty(
    Imath_2_5_Box3f * this_)
{
    (to_cpp(this_)) -> makeEmpty();
}

void Imath_2_5_Box3f_extendBy(
    Imath_2_5_Box3f * this_
    , Imath_2_5_V3f const * point)
{
    (to_cpp(this_)) -> extendBy(to_cpp_ref(point));
}

void Imath_2_5_Box3f_makeInfinite(
    Imath_2_5_Box3f * this_)
{
    (to_cpp(this_)) -> makeInfinite();
}

Imath_2_5_V3f Imath_2_5_Box3f_size(
    Imath_2_5_Box3f const * this_)
{
    return to_c_copy((to_cpp(this_)) -> size());
}

Imath_2_5_V3f Imath_2_5_Box3f_center(
    Imath_2_5_Box3f const * this_)
{
    return to_c_copy((to_cpp(this_)) -> center());
}

_Bool Imath_2_5_Box3f_intersects(
    Imath_2_5_Box3f const * this_
    , Imath_2_5_V3f const * point)
{
    return (to_cpp(this_)) -> intersects(to_cpp_ref(point));
}

unsigned int Imath_2_5_Box3f_majorAxis(
    Imath_2_5_Box3f const * this_)
{
    return (to_cpp(this_)) -> majorAxis();
}

_Bool Imath_2_5_Box3f_isEmpty(
    Imath_2_5_Box3f const * this_)
{
    return (to_cpp(this_)) -> isEmpty();
}

_Bool Imath_2_5_Box3f_hasVolume(
    Imath_2_5_Box3f const * this_)
{
    return (to_cpp(this_)) -> hasVolume();
}

_Bool Imath_2_5_Box3f_isInfinite(
    Imath_2_5_Box3f const * this_)
{
    return (to_cpp(this_)) -> isInfinite();
}

void Imath_2_5_Box3f_Box_3(
    Imath_2_5_Box3f * this_
    , Imath_2_5_Box3f const * rhs)
{
    new (this_) Imath_2_5::Box<Imath_2_5::Vec3<float> >(to_cpp_ref(rhs));
}

void Imath_2_5_Box3d_Box(
    Imath_2_5_Box3d * this_)
{
    new (this_) Imath_2_5::Box<Imath_2_5::Vec3<double> >();
}

void Imath_2_5_Box3d_Box_1(
    Imath_2_5_Box3d * this_
    , Imath_2_5_V3d const * point)
{
    new (this_) Imath_2_5::Box<Imath_2_5::Vec3<double> >(to_cpp_ref(point));
}

void Imath_2_5_Box3d_Box_2(
    Imath_2_5_Box3d * this_
    , Imath_2_5_V3d const * minV
    , Imath_2_5_V3d const * maxV)
{
    new (this_) Imath_2_5::Box<Imath_2_5::Vec3<double> >(to_cpp_ref(minV), to_cpp_ref(maxV));
}

void Imath_2_5_Box3d_makeEmpty(
    Imath_2_5_Box3d * this_)
{
    (to_cpp(this_)) -> makeEmpty();
}

void Imath_2_5_Box3d_extendBy(
    Imath_2_5_Box3d * this_
    , Imath_2_5_V3d const * point)
{
    (to_cpp(this_)) -> extendBy(to_cpp_ref(point));
}

void Imath_2_5_Box3d_makeInfinite(
    Imath_2_5_Box3d * this_)
{
    (to_cpp(this_)) -> makeInfinite();
}

Imath_2_5_V3d Imath_2_5_Box3d_size(
    Imath_2_5_Box3d const * this_)
{
    return to_c_copy((to_cpp(this_)) -> size());
}

Imath_2_5_V3d Imath_2_5_Box3d_center(
    Imath_2_5_Box3d const * this_)
{
    return to_c_copy((to_cpp(this_)) -> center());
}

_Bool Imath_2_5_Box3d_intersects(
    Imath_2_5_Box3d const * this_
    , Imath_2_5_V3d const * point)
{
    return (to_cpp(this_)) -> intersects(to_cpp_ref(point));
}

unsigned int Imath_2_5_Box3d_majorAxis(
    Imath_2_5_Box3d const * this_)
{
    return (to_cpp(this_)) -> majorAxis();
}

_Bool Imath_2_5_Box3d_isEmpty(
    Imath_2_5_Box3d const * this_)
{
    return (to_cpp(this_)) -> isEmpty();
}

_Bool Imath_2_5_Box3d_hasVolume(
    Imath_2_5_Box3d const * this_)
{
    return (to_cpp(this_)) -> hasVolume();
}

_Bool Imath_2_5_Box3d_isInfinite(
    Imath_2_5_Box3d const * this_)
{
    return (to_cpp(this_)) -> isInfinite();
}

void Imath_2_5_Box3d_Box_3(
    Imath_2_5_Box3d * this_
    , Imath_2_5_Box3d const * rhs)
{
    new (this_) Imath_2_5::Box<Imath_2_5::Vec3<double> >(to_cpp_ref(rhs));
}
