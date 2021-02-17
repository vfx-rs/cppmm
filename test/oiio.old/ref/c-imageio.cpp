//
#include "c-imageio.h"
#include <OpenImageIO/filesystem.h>
#include <OpenImageIO/imageio.h>



namespace {
#include "casts.h"

CPPMM_DEFINE_POINTER_CASTS(OpenImageIO_v2_2::Filesystem::IOProxy, OpenImageIO_v2_2_Filesystem_IOProxy)
CPPMM_DEFINE_POINTER_CASTS(OpenImageIO_v2_2::ImageInput, OpenImageIO_v2_2_ImageInput)
CPPMM_DEFINE_POINTER_CASTS(OpenImageIO_v2_2::ImageSpec, OpenImageIO_v2_2_ImageSpec)
CPPMM_DEFINE_POINTER_CASTS(OpenImageIO_v2_2::ROI, OpenImageIO_v2_2_ROI)
CPPMM_DEFINE_POINTER_CASTS(OpenImageIO_v2_2::TypeDesc, OpenImageIO_v2_2_TypeDesc)
CPPMM_DEFINE_POINTER_CASTS(std::vector<OpenImageIO_v2_2::TypeDesc>, OpenImageIO_v2_2_TypeDesc_vector);

#undef CPPMM_DEFINE_POINTER_CASTS
}

extern "C" {
static_assert(sizeof(OpenImageIO_v2_2::ROI) == sizeof(OpenImageIO_v2_2_ROI), "sizes do not match");
static_assert(alignof(OpenImageIO_v2_2::ROI) == alignof(OpenImageIO_v2_2_ROI), "alignments do not match");
static_assert(offsetof(OpenImageIO_v2_2::ROI, xbegin) == offsetof(OpenImageIO_v2_2_ROI, xbegin), "field offset does not match");
static_assert(offsetof(OpenImageIO_v2_2::ROI, xend) == offsetof(OpenImageIO_v2_2_ROI, xend), "field offset does not match");
static_assert(offsetof(OpenImageIO_v2_2::ROI, ybegin) == offsetof(OpenImageIO_v2_2_ROI, ybegin), "field offset does not match");
static_assert(offsetof(OpenImageIO_v2_2::ROI, yend) == offsetof(OpenImageIO_v2_2_ROI, yend), "field offset does not match");
static_assert(offsetof(OpenImageIO_v2_2::ROI, zbegin) == offsetof(OpenImageIO_v2_2_ROI, zbegin), "field offset does not match");
static_assert(offsetof(OpenImageIO_v2_2::ROI, zend) == offsetof(OpenImageIO_v2_2_ROI, zend), "field offset does not match");
static_assert(offsetof(OpenImageIO_v2_2::ROI, chbegin) == offsetof(OpenImageIO_v2_2_ROI, chbegin), "field offset does not match");
static_assert(offsetof(OpenImageIO_v2_2::ROI, chend) == offsetof(OpenImageIO_v2_2_ROI, chend), "field offset does not match");


bool OpenImageIO_v2_2_getattribute(const char* name, OpenImageIO_v2_2_TypeDesc type, void* val) {
    return OpenImageIO_v2_2::getattribute(name, bit_cast<OpenImageIO_v2_2::TypeDesc>(type), val);
}



OpenImageIO_v2_2_ROI OpenImageIO_v2_2_roi_union(const OpenImageIO_v2_2_ROI* A, const OpenImageIO_v2_2_ROI* B) {
    return bit_cast<OpenImageIO_v2_2_ROI>(OpenImageIO_v2_2::roi_union(*to_cpp(A), *to_cpp(B)));
}



OpenImageIO_v2_2_ROI OpenImageIO_v2_2_roi_intersection(const OpenImageIO_v2_2_ROI* A, const OpenImageIO_v2_2_ROI* B) {
    return bit_cast<OpenImageIO_v2_2_ROI>(OpenImageIO_v2_2::roi_intersection(*to_cpp(A), *to_cpp(B)));
}



OpenImageIO_v2_2_ROI OpenImageIO_v2_2_ROI_All() {
    return bit_cast<OpenImageIO_v2_2_ROI>(OpenImageIO_v2_2::ROI::All());
}



unsigned long OpenImageIO_v2_2_ROI_npixels(const OpenImageIO_v2_2_ROI* self) {
    return to_cpp(self)->npixels();
}



void OpenImageIO_v2_2_ROI_default(OpenImageIO_v2_2_ROI* self) {
    self = to_c(new (self) OpenImageIO_v2_2::ROI());
}



int OpenImageIO_v2_2_ROI_nchannels(const OpenImageIO_v2_2_ROI* self) {
    return to_cpp(self)->nchannels();
}



int OpenImageIO_v2_2_ROI_width(const OpenImageIO_v2_2_ROI* self) {
    return to_cpp(self)->width();
}



int OpenImageIO_v2_2_ROI_height(const OpenImageIO_v2_2_ROI* self) {
    return to_cpp(self)->height();
}



bool OpenImageIO_v2_2_ROI_defined(const OpenImageIO_v2_2_ROI* self) {
    return to_cpp(self)->defined();
}



int OpenImageIO_v2_2_ROI_depth(const OpenImageIO_v2_2_ROI* self) {
    return to_cpp(self)->depth();
}



int OpenImageIO_v2_2_ImageInput_geterror(const OpenImageIO_v2_2_ImageInput* self, char* _result_buffer_ptr, int _result_buffer_len) {
    const std::string result = to_cpp(self)->geterror();
    safe_strcpy(_result_buffer_ptr, result, _result_buffer_len);
    return result.size();
}



OpenImageIO_v2_2_ImageInput* OpenImageIO_v2_2_ImageInput_open(const char* filename, const OpenImageIO_v2_2_ImageSpec* config, OpenImageIO_v2_2_Filesystem_IOProxy* ioproxy) {
    return to_c(OpenImageIO_v2_2::ImageInput::open(filename, to_cpp(config), to_cpp(ioproxy)).release());
}



const char* OpenImageIO_v2_2_ImageInput_format_name(const OpenImageIO_v2_2_ImageInput* self) {
    return to_cpp(self)->format_name();
}



void OpenImageIO_v2_2_ImageSpec_get_channelformats(const OpenImageIO_v2_2_ImageSpec* self, OpenImageIO_v2_2_TypeDesc_vector* formats) {
    to_cpp(self)->get_channelformats(*to_cpp(formats));
}



OpenImageIO_v2_2_ImageSpec* OpenImageIO_v2_2_ImageSpec_copy(const OpenImageIO_v2_2_ImageSpec* other) {
    return to_c(new OpenImageIO_v2_2::ImageSpec(*to_cpp(other)));
}



int OpenImageIO_v2_2_ImageSpec_serialize(const OpenImageIO_v2_2_ImageSpec* self, int format, int verbose, char* _result_buffer_ptr, int _result_buffer_len) {
    const std::string result = to_cpp(self)->serialize((OpenImageIO_v2_2::ImageSpec::SerialFormat)format, (OpenImageIO_v2_2::ImageSpec::SerialVerbose)verbose);
    safe_strcpy(_result_buffer_ptr, result, _result_buffer_len);
    return result.size();
}



void OpenImageIO_v2_2_ImageSpec_auto_stride(long* xstride, long* ystride, long* zstride, long channelsize, int nchannels, int width, int height) {
    OpenImageIO_v2_2::ImageSpec::auto_stride(*xstride, *ystride, *zstride, channelsize, nchannels, width, height);
}



OpenImageIO_v2_2_ImageSpec* OpenImageIO_v2_2_ImageSpec_new_with_dimensions(int xres, int yres, int nchans, OpenImageIO_v2_2_TypeDesc fmt) {
    return to_c(new OpenImageIO_v2_2::ImageSpec(xres, yres, nchans, bit_cast<OpenImageIO_v2_2::TypeDesc>(fmt)));
}



unsigned long OpenImageIO_v2_2_ImageSpec_channel_bytes(const OpenImageIO_v2_2_ImageSpec* self) {
    return to_cpp(self)->channel_bytes();
}



unsigned long OpenImageIO_v2_2_ImageSpec_scanline_bytes(const OpenImageIO_v2_2_ImageSpec* self, bool native) {
    return to_cpp(self)->scanline_bytes(native);
}



OpenImageIO_v2_2_ImageSpec* OpenImageIO_v2_2_ImageSpec_new(OpenImageIO_v2_2_TypeDesc format) {
    return to_c(new OpenImageIO_v2_2::ImageSpec(bit_cast<OpenImageIO_v2_2::TypeDesc>(format)));
}



void OpenImageIO_v2_2_ImageSpec_default_channel_names(OpenImageIO_v2_2_ImageSpec* self) {
    to_cpp(self)->default_channel_names();
}



OpenImageIO_v2_2_ImageSpec* OpenImageIO_v2_2_ImageSpec_assign(OpenImageIO_v2_2_ImageSpec* self, const OpenImageIO_v2_2_ImageSpec* other) {
    *to_cpp(self) = *to_cpp(other);
    return self;
}



void OpenImageIO_v2_2_ImageSpec_set_format(OpenImageIO_v2_2_ImageSpec* self, OpenImageIO_v2_2_TypeDesc fmt) {
    to_cpp(self)->set_format(bit_cast<OpenImageIO_v2_2::TypeDesc>(fmt));
}



void OpenImageIO_v2_2_ImageSpec_attribute(OpenImageIO_v2_2_ImageSpec* self, const char* name, OpenImageIO_v2_2_TypeDesc type, const void* value) {
    to_cpp(self)->attribute(name, bit_cast<OpenImageIO_v2_2::TypeDesc>(type), value);
}



unsigned long OpenImageIO_v2_2_ImageSpec_channel_bytes_for(const OpenImageIO_v2_2_ImageSpec* self, int chan, bool native) {
    return to_cpp(self)->channel_bytes(chan, native);
}



}
    