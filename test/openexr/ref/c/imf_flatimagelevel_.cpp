#include <imf_flatimagelevel_private_.h>

#include <imath_box_private_.h>
#include <imf_flatimagechannel_private_.h>
#include <imf_image_private_.h>
#include <new>


Imf_2_5_Image * Imf_2_5_FlatImageLevel_image(
    Imf_2_5_FlatImageLevel * this_)
{
    return to_c((to_cpp(this_)) -> image());
}

Imf_2_5_Image const * Imf_2_5_FlatImageLevel_image_1(
    Imf_2_5_FlatImageLevel const * this_)
{
    return to_c((to_cpp(this_)) -> image());
}

int Imf_2_5_FlatImageLevel_xLevelNumber(
    Imf_2_5_FlatImageLevel const * this_)
{
    return (to_cpp(this_)) -> xLevelNumber();
}

int Imf_2_5_FlatImageLevel_yLevelNumber(
    Imf_2_5_FlatImageLevel const * this_)
{
    return (to_cpp(this_)) -> yLevelNumber();
}

Imath_2_5_Box2i const * Imf_2_5_FlatImageLevel_dataWindow(
    Imf_2_5_FlatImageLevel const * this_)
{
    return to_c((to_cpp(this_)) -> dataWindow());
}

Imf_2_5_FlatImageLevel_Iterator Imf_2_5_FlatImageLevel_begin(
    Imf_2_5_FlatImageLevel * this_)
{
    return to_c_copy((to_cpp(this_)) -> begin());
}

Imf_2_5_FlatImageLevel_ConstIterator Imf_2_5_FlatImageLevel_begin_1(
    Imf_2_5_FlatImageLevel const * this_)
{
    return to_c_copy((to_cpp(this_)) -> begin());
}

Imf_2_5_FlatImageLevel_Iterator Imf_2_5_FlatImageLevel_end(
    Imf_2_5_FlatImageLevel * this_)
{
    return to_c_copy((to_cpp(this_)) -> end());
}

Imf_2_5_FlatImageLevel_ConstIterator Imf_2_5_FlatImageLevel_end_1(
    Imf_2_5_FlatImageLevel const * this_)
{
    return to_c_copy((to_cpp(this_)) -> end());
}

void Imf_2_5_FlatImageLevel_Iterator_Iterator(
    Imf_2_5_FlatImageLevel_Iterator * this_)
{
    new (this_) Imf_2_5::FlatImageLevel::Iterator();
}

Imf_2_5_FlatImageLevel_Iterator * Imf_2_5_FlatImageLevel_Iterator__op_inc(
    Imf_2_5_FlatImageLevel_Iterator * this_)
{
    return to_c((to_cpp(this_)) -> operator++());
}

Imf_2_5_FlatImageLevel_Iterator Imf_2_5_FlatImageLevel_Iterator__op_inc_1(
    Imf_2_5_FlatImageLevel_Iterator * this_
    , int )
{
    return to_c_copy((to_cpp(this_)) -> operator++());
}

Imf_2_5_FlatImageChannel * Imf_2_5_FlatImageLevel_Iterator_channel(
    Imf_2_5_FlatImageLevel_Iterator const * this_)
{
    return to_c((to_cpp(this_)) -> channel());
}

void Imf_2_5_FlatImageLevel_Iterator_Iterator_1(
    Imf_2_5_FlatImageLevel_Iterator * this_
    , Imf_2_5_FlatImageLevel_Iterator const * rhs)
{
    new (this_) Imf_2_5::FlatImageLevel::Iterator(to_cpp_ref(rhs));
}

void Imf_2_5_FlatImageLevel_ConstIterator_ConstIterator(
    Imf_2_5_FlatImageLevel_ConstIterator * this_)
{
    new (this_) Imf_2_5::FlatImageLevel::ConstIterator();
}

Imf_2_5_FlatImageLevel_ConstIterator * Imf_2_5_FlatImageLevel_ConstIterator__op_inc(
    Imf_2_5_FlatImageLevel_ConstIterator * this_)
{
    return to_c((to_cpp(this_)) -> operator++());
}

Imf_2_5_FlatImageLevel_ConstIterator Imf_2_5_FlatImageLevel_ConstIterator__op_inc_1(
    Imf_2_5_FlatImageLevel_ConstIterator * this_
    , int )
{
    return to_c_copy((to_cpp(this_)) -> operator++());
}

Imf_2_5_FlatImageChannel const * Imf_2_5_FlatImageLevel_ConstIterator_channel(
    Imf_2_5_FlatImageLevel_ConstIterator const * this_)
{
    return to_c((to_cpp(this_)) -> channel());
}

void Imf_2_5_FlatImageLevel_ConstIterator_ConstIterator_1(
    Imf_2_5_FlatImageLevel_ConstIterator * this_
    , Imf_2_5_FlatImageLevel_ConstIterator const * rhs)
{
    new (this_) Imf_2_5::FlatImageLevel::ConstIterator(to_cpp_ref(rhs));
}
