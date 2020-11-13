//
#include "c-imageio.h"
#include <OpenImageIO/filesystem.h>
#include <OpenImageIO/imageio.h>

namespace {
#include "casts.h"

CPPMM_DEFINE_POINTER_CASTS(OIIO::Filesystem::IOProxy, OIIO_Filesystem_IOProxy)
CPPMM_DEFINE_POINTER_CASTS(OIIO::ImageInput, OIIO_ImageInput)
CPPMM_DEFINE_POINTER_CASTS(OIIO::ImageSpec, OIIO_ImageSpec)
CPPMM_DEFINE_POINTER_CASTS(OIIO::ROI, OIIO_ROI)
CPPMM_DEFINE_POINTER_CASTS(OIIO::TypeDesc, OIIO_TypeDesc)
CPPMM_DEFINE_POINTER_CASTS(std::vector<OIIO::TypeDesc>, OIIO_TypeDesc_vector);

#undef CPPMM_DEFINE_POINTER_CASTS
}

extern "C" {
static_assert(sizeof(OIIO::ROI) == sizeof(OIIO_ROI), "sizes do not match");
static_assert(alignof(OIIO::ROI) == alignof(OIIO_ROI), "alignments do not match");
static_assert(offsetof(OIIO::ROI, xbegin) == offsetof(OIIO_ROI, xbegin), "field offset does not match");
static_assert(offsetof(OIIO::ROI, xend) == offsetof(OIIO_ROI, xend), "field offset does not match");
static_assert(offsetof(OIIO::ROI, ybegin) == offsetof(OIIO_ROI, ybegin), "field offset does not match");
static_assert(offsetof(OIIO::ROI, yend) == offsetof(OIIO_ROI, yend), "field offset does not match");
static_assert(offsetof(OIIO::ROI, zbegin) == offsetof(OIIO_ROI, zbegin), "field offset does not match");
static_assert(offsetof(OIIO::ROI, zend) == offsetof(OIIO_ROI, zend), "field offset does not match");
static_assert(offsetof(OIIO::ROI, chbegin) == offsetof(OIIO_ROI, chbegin), "field offset does not match");
static_assert(offsetof(OIIO::ROI, chend) == offsetof(OIIO_ROI, chend), "field offset does not match");


bool OIIO_getattribute(const char* name, OIIO_TypeDesc type, void* val) {
    return OIIO::getattribute(name, bit_cast<OIIO::TypeDesc>(type), val);
}



OIIO_ROI OIIO_roi_union(const OIIO_ROI* A, const OIIO_ROI* B) {
    return bit_cast<OIIO_ROI>(OIIO::roi_union(*to_cpp(A), *to_cpp(B)));
}



OIIO_ROI OIIO_roi_intersection(const OIIO_ROI* A, const OIIO_ROI* B) {
    return bit_cast<OIIO_ROI>(OIIO::roi_intersection(*to_cpp(A), *to_cpp(B)));
}



int OIIO_ImageInput_geterror(const OIIO_ImageInput* self, char* _result_buffer_ptr, int _result_buffer_len) {
    const std::string result = to_cpp(self)->geterror();
    safe_strcpy(_result_buffer_ptr, result, _result_buffer_len);
    return result.size();
}



OIIO_ImageInput* OIIO_ImageInput_open(const char* filename, const OIIO_ImageSpec* config, OIIO_Filesystem_IOProxy* ioproxy) {
    return to_c(OIIO::ImageInput::open(filename, to_cpp(config), to_cpp(ioproxy)).release());
}



const char* OIIO_ImageInput_format_name(const OIIO_ImageInput* self) {
    return to_cpp(self)->format_name();
}



OIIO_ROI OIIO_ROI_All() {
    return bit_cast<OIIO_ROI>(OIIO::ROI::All());
}



unsigned long OIIO_ROI_npixels(const OIIO_ROI* self) {
    return to_cpp(self)->npixels();
}



void OIIO_ROI_default(OIIO_ROI* self) {
    self = to_c(new (self) OIIO::ROI());
}



int OIIO_ROI_nchannels(const OIIO_ROI* self) {
    return to_cpp(self)->nchannels();
}



int OIIO_ROI_width(const OIIO_ROI* self) {
    return to_cpp(self)->width();
}



int OIIO_ROI_height(const OIIO_ROI* self) {
    return to_cpp(self)->height();
}



bool OIIO_ROI_defined(const OIIO_ROI* self) {
    return to_cpp(self)->defined();
}



int OIIO_ROI_depth(const OIIO_ROI* self) {
    return to_cpp(self)->depth();
}



void OIIO_ImageSpec_get_channelformats(const OIIO_ImageSpec* self, OIIO_TypeDesc_vector * formats) {
    to_cpp(self)->get_channelformats(*to_cpp(formats));
}



OIIO_ImageSpec* OIIO_ImageSpec_copy(const OIIO_ImageSpec* other) {
    return to_c(new OIIO::ImageSpec(*to_cpp(other)));
}



int OIIO_ImageSpec_serialize(const OIIO_ImageSpec* self, int format, int verbose, char* _result_buffer_ptr, int _result_buffer_len) {
    const std::string result = to_cpp(self)->serialize((OIIO::ImageSpec::SerialFormat)format, (OIIO::ImageSpec::SerialVerbose)verbose);
    safe_strcpy(_result_buffer_ptr, result, _result_buffer_len);
    return result.size();
}



void OIIO_ImageSpec_auto_stride(long* xstride, long* ystride, long* zstride, long channelsize, int nchannels, int width, int height) {
    OIIO::ImageSpec::auto_stride(*xstride, *ystride, *zstride, channelsize, nchannels, width, height);
}



OIIO_ImageSpec* OIIO_ImageSpec_new_with_dimensions(int xres, int yres, int nchans, OIIO_TypeDesc fmt) {
    return to_c(new OIIO::ImageSpec(xres, yres, nchans, bit_cast<OIIO::TypeDesc>(fmt)));
}



unsigned long OIIO_ImageSpec_channel_bytes(const OIIO_ImageSpec* self) {
    return to_cpp(self)->channel_bytes();
}



unsigned long OIIO_ImageSpec_scanline_bytes(const OIIO_ImageSpec* self, bool native) {
    return to_cpp(self)->scanline_bytes(native);
}



OIIO_ImageSpec* OIIO_ImageSpec_new(OIIO_TypeDesc format) {
    return to_c(new OIIO::ImageSpec(bit_cast<OIIO::TypeDesc>(format)));
}



void OIIO_ImageSpec_default_channel_names(OIIO_ImageSpec* self) {
    to_cpp(self)->default_channel_names();
}



OIIO_ImageSpec* OIIO_ImageSpec_assign(OIIO_ImageSpec* self, const OIIO_ImageSpec* other) {
    *to_cpp(self) = *to_cpp(other);
    return self;
}



void OIIO_ImageSpec_set_format(OIIO_ImageSpec* self, OIIO_TypeDesc fmt) {
    to_cpp(self)->set_format(bit_cast<OIIO::TypeDesc>(fmt));
}



void OIIO_ImageSpec_attribute(OIIO_ImageSpec* self, const char* name, OIIO_TypeDesc type, const void* value) {
    to_cpp(self)->attribute(name, bit_cast<OIIO::TypeDesc>(type), value);
}



unsigned long OIIO_ImageSpec_channel_bytes_for(const OIIO_ImageSpec* self, int chan, bool native) {
    return to_cpp(self)->channel_bytes(chan, native);
}



}
    