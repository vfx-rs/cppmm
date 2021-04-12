#pragma once

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_FrameBuffer_s Imf_2_5_FrameBuffer;
typedef struct Imath_2_5_Box2i_s Imath_2_5_Box2i;
typedef struct Imf_2_5_DeepCompositing_s Imf_2_5_DeepCompositing;
typedef struct Imf_2_5_DeepScanLineInputPart_s Imf_2_5_DeepScanLineInputPart;
typedef struct Imf_2_5_DeepScanLineInputFile_s Imf_2_5_DeepScanLineInputFile;
typedef struct Imf_2_5_CompositeDeepScanLine_s {
    char data[16];
} __attribute__((aligned(8))) Imf_2_5_CompositeDeepScanLine;


void Imf_2_5_CompositeDeepScanLine_CompositeDeepScanLine(
    Imf_2_5_CompositeDeepScanLine * this_);


void Imf_2_5_CompositeDeepScanLine_dtor(
    Imf_2_5_CompositeDeepScanLine * this_);


void Imf_2_5_CompositeDeepScanLine_addSource(
    Imf_2_5_CompositeDeepScanLine * this_
    , Imf_2_5_DeepScanLineInputPart * part);


void Imf_2_5_CompositeDeepScanLine_addSource_1(
    Imf_2_5_CompositeDeepScanLine * this_
    , Imf_2_5_DeepScanLineInputFile * file);


void Imf_2_5_CompositeDeepScanLine_setFrameBuffer(
    Imf_2_5_CompositeDeepScanLine * this_
    , Imf_2_5_FrameBuffer const * fr);


Imf_2_5_FrameBuffer const * Imf_2_5_CompositeDeepScanLine_frameBuffer(
    Imf_2_5_CompositeDeepScanLine const * this_);


void Imf_2_5_CompositeDeepScanLine_readPixels(
    Imf_2_5_CompositeDeepScanLine * this_
    , int start
    , int end);


int Imf_2_5_CompositeDeepScanLine_sources(
    Imf_2_5_CompositeDeepScanLine const * this_);


Imath_2_5_Box2i const * Imf_2_5_CompositeDeepScanLine_dataWindow(
    Imf_2_5_CompositeDeepScanLine const * this_);


void Imf_2_5_CompositeDeepScanLine_setCompositing(
    Imf_2_5_CompositeDeepScanLine * this_
    , Imf_2_5_DeepCompositing * compositing);








#ifdef __cplusplus
}
#endif
