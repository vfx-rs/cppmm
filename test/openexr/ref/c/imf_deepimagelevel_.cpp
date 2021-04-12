#include <imf_deepimagelevel_private_.h>

#include <imath_box_private_.h>
#include <imf_deepimage_private_.h>
#include <imf_deepimagechannel_private_.h>
#include <imf_image_private_.h>
#include <imf_samplecountchannel_private_.h>
#include <new>


Imf_2_5_Image * Imf_2_5_DeepImageLevel_image(
    Imf_2_5_DeepImageLevel * this_)
{
    return to_c((to_cpp(this_)) -> image());
}

Imf_2_5_Image const * Imf_2_5_DeepImageLevel_image_1(
    Imf_2_5_DeepImageLevel const * this_)
{
    return to_c((to_cpp(this_)) -> image());
}

int Imf_2_5_DeepImageLevel_xLevelNumber(
    Imf_2_5_DeepImageLevel const * this_)
{
    return (to_cpp(this_)) -> xLevelNumber();
}

int Imf_2_5_DeepImageLevel_yLevelNumber(
    Imf_2_5_DeepImageLevel const * this_)
{
    return (to_cpp(this_)) -> yLevelNumber();
}

Imath_2_5_Box2i const * Imf_2_5_DeepImageLevel_dataWindow(
    Imf_2_5_DeepImageLevel const * this_)
{
    return to_c((to_cpp(this_)) -> dataWindow());
}

Imf_2_5_DeepImage * Imf_2_5_DeepImageLevel_deepImage(
    Imf_2_5_DeepImageLevel * this_)
{
    return to_c((to_cpp(this_)) -> deepImage());
}

Imf_2_5_DeepImage const * Imf_2_5_DeepImageLevel_deepImage_1(
    Imf_2_5_DeepImageLevel const * this_)
{
    return to_c((to_cpp(this_)) -> deepImage());
}

Imf_2_5_DeepImageLevel_Iterator Imf_2_5_DeepImageLevel_begin(
    Imf_2_5_DeepImageLevel * this_)
{
    return to_c_copy((to_cpp(this_)) -> begin());
}

Imf_2_5_DeepImageLevel_ConstIterator Imf_2_5_DeepImageLevel_begin_1(
    Imf_2_5_DeepImageLevel const * this_)
{
    return to_c_copy((to_cpp(this_)) -> begin());
}

Imf_2_5_DeepImageLevel_Iterator Imf_2_5_DeepImageLevel_end(
    Imf_2_5_DeepImageLevel * this_)
{
    return to_c_copy((to_cpp(this_)) -> end());
}

Imf_2_5_DeepImageLevel_ConstIterator Imf_2_5_DeepImageLevel_end_1(
    Imf_2_5_DeepImageLevel const * this_)
{
    return to_c_copy((to_cpp(this_)) -> end());
}

Imf_2_5_SampleCountChannel * Imf_2_5_DeepImageLevel_sampleCounts(
    Imf_2_5_DeepImageLevel * this_)
{
    return to_c((to_cpp(this_)) -> sampleCounts());
}

Imf_2_5_SampleCountChannel const * Imf_2_5_DeepImageLevel_sampleCounts_1(
    Imf_2_5_DeepImageLevel const * this_)
{
    return to_c((to_cpp(this_)) -> sampleCounts());
}

void Imf_2_5_DeepImageLevel_Iterator_Iterator(
    Imf_2_5_DeepImageLevel_Iterator * this_)
{
    new (this_) Imf_2_5::DeepImageLevel::Iterator();
}

Imf_2_5_DeepImageLevel_Iterator * Imf_2_5_DeepImageLevel_Iterator__op_inc(
    Imf_2_5_DeepImageLevel_Iterator * this_)
{
    return to_c((to_cpp(this_)) -> operator++());
}

Imf_2_5_DeepImageLevel_Iterator Imf_2_5_DeepImageLevel_Iterator__op_inc_1(
    Imf_2_5_DeepImageLevel_Iterator * this_
    , int )
{
    return to_c_copy((to_cpp(this_)) -> operator++());
}

Imf_2_5_DeepImageChannel * Imf_2_5_DeepImageLevel_Iterator_channel(
    Imf_2_5_DeepImageLevel_Iterator const * this_)
{
    return to_c((to_cpp(this_)) -> channel());
}

void Imf_2_5_DeepImageLevel_Iterator_Iterator_1(
    Imf_2_5_DeepImageLevel_Iterator * this_
    , Imf_2_5_DeepImageLevel_Iterator const * rhs)
{
    new (this_) Imf_2_5::DeepImageLevel::Iterator(to_cpp_ref(rhs));
}

void Imf_2_5_DeepImageLevel_ConstIterator_ConstIterator(
    Imf_2_5_DeepImageLevel_ConstIterator * this_)
{
    new (this_) Imf_2_5::DeepImageLevel::ConstIterator();
}

Imf_2_5_DeepImageLevel_ConstIterator * Imf_2_5_DeepImageLevel_ConstIterator__op_inc(
    Imf_2_5_DeepImageLevel_ConstIterator * this_)
{
    return to_c((to_cpp(this_)) -> operator++());
}

Imf_2_5_DeepImageLevel_ConstIterator Imf_2_5_DeepImageLevel_ConstIterator__op_inc_1(
    Imf_2_5_DeepImageLevel_ConstIterator * this_
    , int )
{
    return to_c_copy((to_cpp(this_)) -> operator++());
}

Imf_2_5_DeepImageChannel const * Imf_2_5_DeepImageLevel_ConstIterator_channel(
    Imf_2_5_DeepImageLevel_ConstIterator const * this_)
{
    return to_c((to_cpp(this_)) -> channel());
}

void Imf_2_5_DeepImageLevel_ConstIterator_ConstIterator_1(
    Imf_2_5_DeepImageLevel_ConstIterator * this_
    , Imf_2_5_DeepImageLevel_ConstIterator const * rhs)
{
    new (this_) Imf_2_5::DeepImageLevel::ConstIterator(to_cpp_ref(rhs));
}
