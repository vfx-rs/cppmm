#include <imf_samplecountchannel_private_.h>

#include <imf_deepimagelevel_private_.h>
#include <imf_framebuffer_private_.h>
#include <new>


Imf_2_5_Slice Imf_2_5_SampleCountChannel_slice(
    Imf_2_5_SampleCountChannel const * this_)
{
    return to_c_copy((to_cpp(this_)) -> slice());
}

Imf_2_5_DeepImageLevel * Imf_2_5_SampleCountChannel_deepLevel(
    Imf_2_5_SampleCountChannel * this_)
{
    return to_c((to_cpp(this_)) -> deepLevel());
}

Imf_2_5_DeepImageLevel const * Imf_2_5_SampleCountChannel_deepLevel_1(
    Imf_2_5_SampleCountChannel const * this_)
{
    return to_c((to_cpp(this_)) -> deepLevel());
}

unsigned int const * Imf_2_5_SampleCountChannel_operator()(
    Imf_2_5_SampleCountChannel const * this_
    , int x
    , int y)
{
    return &((to_cpp(this_)) -> operator()(x, y));
}

unsigned int const * Imf_2_5_SampleCountChannel_at(
    Imf_2_5_SampleCountChannel const * this_
    , int x
    , int y)
{
    return &((to_cpp(this_)) -> at(x, y));
}

unsigned int const * Imf_2_5_SampleCountChannel_row(
    Imf_2_5_SampleCountChannel const * this_
    , int r)
{
    return (to_cpp(this_)) -> row(r);
}

void Imf_2_5_SampleCountChannel_set(
    Imf_2_5_SampleCountChannel * this_
    , int x
    , int y
    , unsigned int newNumSamples)
{
    (to_cpp(this_)) -> set(x, y, newNumSamples);
}

void Imf_2_5_SampleCountChannel_set_1(
    Imf_2_5_SampleCountChannel * this_
    , int r
    , unsigned int * newNumSamples)
{
    (to_cpp(this_)) -> set(r, newNumSamples);
}

void Imf_2_5_SampleCountChannel_clear(
    Imf_2_5_SampleCountChannel * this_)
{
    (to_cpp(this_)) -> clear();
}

unsigned int * Imf_2_5_SampleCountChannel_beginEdit(
    Imf_2_5_SampleCountChannel * this_)
{
    return (to_cpp(this_)) -> beginEdit();
}

void Imf_2_5_SampleCountChannel_endEdit(
    Imf_2_5_SampleCountChannel * this_)
{
    (to_cpp(this_)) -> endEdit();
}

unsigned int const * Imf_2_5_SampleCountChannel_numSamples(
    Imf_2_5_SampleCountChannel const * this_)
{
    return (to_cpp(this_)) -> numSamples();
}

unsigned int const * Imf_2_5_SampleCountChannel_sampleListSizes(
    Imf_2_5_SampleCountChannel const * this_)
{
    return (to_cpp(this_)) -> sampleListSizes();
}

unsigned long const * Imf_2_5_SampleCountChannel_sampleListPositions(
    Imf_2_5_SampleCountChannel const * this_)
{
    return (to_cpp(this_)) -> sampleListPositions();
}

unsigned long Imf_2_5_SampleCountChannel_sampleBufferSize(
    Imf_2_5_SampleCountChannel const * this_)
{
    return (to_cpp(this_)) -> sampleBufferSize();
}

void Imf_2_5_SampleCountChannel_Edit_Edit(
    Imf_2_5_SampleCountChannel_Edit * this_
    , Imf_2_5_SampleCountChannel * level)
{
    new (this_) Imf_2_5::SampleCountChannel::Edit(to_cpp_ref(level));
}

void Imf_2_5_SampleCountChannel_Edit_dtor(
    Imf_2_5_SampleCountChannel_Edit * this_)
{
    (to_cpp(this_)) -> Imf_2_5::SampleCountChannel::Edit::~Edit();
}

unsigned int * Imf_2_5_SampleCountChannel_Edit_sampleCounts(
    Imf_2_5_SampleCountChannel_Edit const * this_)
{
    return (to_cpp(this_)) -> sampleCounts();
}
