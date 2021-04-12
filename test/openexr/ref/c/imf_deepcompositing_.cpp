#include <imf_deepcompositing_private_.h>

#include <new>


void Imf_2_5_DeepCompositing_DeepCompositing(
    Imf_2_5_DeepCompositing * this_)
{
    new (this_) Imf_2_5::DeepCompositing();
}

void Imf_2_5_DeepCompositing_dtor(
    Imf_2_5_DeepCompositing * this_)
{
    (to_cpp(this_)) -> Imf_2_5::DeepCompositing::~DeepCompositing();
}

void Imf_2_5_DeepCompositing_composite_pixel(
    Imf_2_5_DeepCompositing * this_
    , float * outputs
    , float const * * inputs
    , char const * * channel_names
    , int num_channels
    , int num_samples
    , int sources)
{
    (to_cpp(this_)) -> composite_pixel(outputs, inputs, channel_names, num_channels, num_samples, sources);
}

void Imf_2_5_DeepCompositing_sort(
    Imf_2_5_DeepCompositing * this_
    , int * order
    , float const * * inputs
    , char const * * channel_names
    , int num_channels
    , int num_samples
    , int sources)
{
    (to_cpp(this_)) -> sort(order, inputs, channel_names, num_channels, num_samples, sources);
}
