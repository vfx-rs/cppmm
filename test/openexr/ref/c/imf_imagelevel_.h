#pragma once

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_Image_s Imf_2_5_Image;
typedef struct Imf_2_5_ImageLevel_s {
    char data[40];
} __attribute__((aligned(8))) Imf_2_5_ImageLevel;


Imf_2_5_Image * Imf_2_5_ImageLevel_image(
    Imf_2_5_ImageLevel * this_);


Imf_2_5_Image const * Imf_2_5_ImageLevel_image_1(
    Imf_2_5_ImageLevel const * this_);








#ifdef __cplusplus
}
#endif
