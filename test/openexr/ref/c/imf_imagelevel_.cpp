#include <imf_imagelevel_private_.h>

#include <imf_image_private_.h>


Imf_2_5_Image * Imf_2_5_ImageLevel_image(
    Imf_2_5_ImageLevel * this_)
{
    return to_c((to_cpp(this_)) -> image());
}

Imf_2_5_Image const * Imf_2_5_ImageLevel_image_1(
    Imf_2_5_ImageLevel const * this_)
{
    return to_c((to_cpp(this_)) -> image());
}
