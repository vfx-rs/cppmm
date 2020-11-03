//
#include <OpenImageIO/filesystem.h>
#include <OpenImageIO/imageio.h>

namespace {
#include "casts.h"
CPPMM_DEFINE_POINTER_CASTS(OIIO::ImageSpec, OIIO_ImageSpec)
CPPMM_DEFINE_POINTER_CASTS(OIIO::ImageInput, OIIO_ImageInput)

#undef CPPMM_DEFINE_POINTER_CASTS
}

extern "C" {

OIIO_ImageSpec*  OIIO_ImageSpec_assign(OIIO_ImageSpec* self, const OIIO_ImageSpec* ) {
    return to_c(to_cpp(self)->operator=(*to_cpp()));
}



void  OIIO_ImageSpec_erase_attribute(OIIO_ImageSpec* self, const char* name, OIIO_TypeDesc searchtype, _Bool casesensitive) {
    return to_cpp(self)->erase_attribute(name, to_cpp(searchtype), casesensitive);
}



char*  OIIO_ImageSpec_serialize(const OIIO_ImageSpec* self, OIIO_ImageSpec_SerialFormat format, OIIO_ImageSpec_SerialVerbose verbose) {
    return to_cpp(self)->serialize(format, verbose);
}



unsigned long  OIIO_ImageSpec_image_bytes(const OIIO_ImageSpec* self, _Bool native) {
    return to_cpp(self)->image_bytes(native);
}



_Bool  OIIO_ImageSpec_valid_tile_range(OIIO_ImageSpec* self, int xbegin, int xend, int ybegin, int yend, int zbegin, int zend) {
    return to_cpp(self)->valid_tile_range(xbegin, xend, ybegin, yend, zbegin, zend);
}



unsigned long  OIIO_ImageSpec_channel_bytes(const OIIO_ImageSpec* self) {
    return to_cpp(self)->channel_bytes();
}



unsigned long  OIIO_ImageSpec_image_pixels(const OIIO_ImageSpec* self) {
    return to_cpp(self)->image_pixels();
}



void  OIIO_ImageSpec_auto_stride(long* xstride, long* ystride, long* zstride, long channelsize, int nchannels, int width, int height) {
    return OIIO::ImageSpec::auto_stride(*xstride, *ystride, *zstride, channelsize, nchannels, width, height);
}



unsigned long  OIIO_ImageSpec_tile_pixels(const OIIO_ImageSpec* self) {
    return to_cpp(self)->tile_pixels();
}



unsigned long  OIIO_ImageSpec_scanline_bytes(const OIIO_ImageSpec* self, _Bool native) {
    return to_cpp(self)->scanline_bytes(native);
}



OIIO_ParamValue*  OIIO_ImageSpec_find_attribute(OIIO_ImageSpec* self, const char* name, OIIO_TypeDesc searchtype, _Bool casesensitive) {
    return to_c(to_cpp(self)->find_attribute(name, to_cpp(searchtype), casesensitive));
}



void  OIIO_ImageSpec_default_channel_names(OIIO_ImageSpec* self) {
    return to_cpp(self)->default_channel_names();
}



void  OIIO_ImageSpec_set_format(OIIO_ImageSpec* self, OIIO_TypeDesc fmt) {
    return to_cpp(self)->set_format(to_cpp(fmt));
}



void  OIIO_ImageSpec_auto_stride_x(long* xstride, OIIO_TypeDesc format, int nchannels) {
    return OIIO::ImageSpec::auto_stride(*xstride, to_cpp(format), nchannels);
}



_Bool  OIIO_ImageSpec_size_t_safe(const OIIO_ImageSpec* self) {
    return to_cpp(self)->size_t_safe();
}



void  OIIO_ImageSpec_copy(OIIO_ImageSpec* self, const OIIO_ImageSpec* ) {
    return to_cpp(self)->ImageSpec(*to_cpp());
}



void  OIIO_ImageSpec_attribute(OIIO_ImageSpec* self, const char* name, OIIO_TypeDesc type, const void* value) {
    return to_cpp(self)->attribute(name, to_cpp(type), value);
}



unsigned long  OIIO_ImageSpec_tile_bytes(const OIIO_ImageSpec* self, _Bool native) {
    return to_cpp(self)->tile_bytes(native);
}



unsigned long  OIIO_ImageSpec_pixel_bytes(const OIIO_ImageSpec* self, _Bool native) {
    return to_cpp(self)->pixel_bytes(native);
}



_Bool  OIIO_ImageSpec_getattribute(const OIIO_ImageSpec* self, const char* name, OIIO_TypeDesc type, void* value, _Bool casesensitive) {
    return to_cpp(self)->getattribute(name, to_cpp(type), value, casesensitive);
}



void  OIIO_ImageSpec_copy_dimensions(OIIO_ImageSpec* self, const OIIO_ImageSpec* other) {
    return to_cpp(self)->copy_dimensions(*to_cpp(other));
}



unsigned long  OIIO_ImageSpec_pixel_bytes_for(const OIIO_ImageSpec* self, int chbegin, int chend, _Bool native) {
    return to_cpp(self)->pixel_bytes(chbegin, chend, native);
}



const OIIO_ParamValue*  OIIO_ImageSpec_find_attribute_or(const OIIO_ImageSpec* self, const char* name, OIIO_ParamValue* tmpparam, OIIO_TypeDesc searchtype, _Bool casesensitive) {
    return to_c(to_cpp(self)->find_attribute(name, *to_cpp(tmpparam), to_cpp(searchtype), casesensitive));
}



OIIO_TypeDesc  OIIO_ImageSpec_getattributetype(const OIIO_ImageSpec* self, const char* name, _Bool casesensitive) {
    return to_c(to_cpp(self)->getattributetype(name, casesensitive));
}



char*  OIIO_ImageSpec_metadata_val(const OIIO_ParamValue* p, _Bool human) {
    return OIIO::ImageSpec::metadata_val(*to_cpp(p), human);
}



void  OIIO_ImageSpec_from_xml(OIIO_ImageSpec* self, const char* xml) {
    return to_cpp(self)->from_xml(xml);
}



void  OIIO_ImageSpec_set_roi(OIIO_ImageSpec* self, const OIIO_ROI* r) {
    return to_cpp(self)->set_roi(*to_cpp(r));
}



char*  OIIO_ImageSpec_to_xml(const OIIO_ImageSpec* self) {
    return to_cpp(self)->to_xml();
}



OIIO_TypeDesc  OIIO_ImageSpec_channelformat(const OIIO_ImageSpec* self, int chan) {
    return to_c(to_cpp(self)->channelformat(chan));
}



const char*  OIIO_ImageSpec_channel_name(const OIIO_ImageSpec* self, int chan) {
    return to_cpp(self)->channel_name(chan);
}



void  OIIO_ImageSpec_get_channelformats(const OIIO_ImageSpec* self, std_vector* formats) {
    return to_cpp(self)->get_channelformats(*to_cpp(formats));
}



int  OIIO_ImageSpec_channelindex(const OIIO_ImageSpec* self, const char* name) {
    return to_cpp(self)->channelindex(name);
}



unsigned long  OIIO_ImageSpec_channel_bytes_for(const OIIO_ImageSpec* self, int chan, _Bool native) {
    return to_cpp(self)->channel_bytes(chan, native);
}



void  OIIO_ImageSpec_set_roi_full(OIIO_ImageSpec* self, const OIIO_ROI* r) {
    return to_cpp(self)->set_roi_full(*to_cpp(r));
}



OIIO_ROI  OIIO_ImageSpec_roi_full(const OIIO_ImageSpec* self) {
    return to_c(to_cpp(self)->roi_full());
}



OIIO_ROI  OIIO_ImageSpec_roi(const OIIO_ImageSpec* self) {
    return to_c(to_cpp(self)->roi());
}



_Bool  OIIO_ImageSpec_undefined(const OIIO_ImageSpec* self) {
    return to_cpp(self)->undefined();
}



void  OIIO_ImageInput_copy(OIIO_ImageInput* self, const OIIO_ImageInput* ) {
    return to_cpp(self)->ImageInput(*to_cpp());
}



OIIO_ImageInput*  OIIO_ImageInput_assign(OIIO_ImageInput* self, const OIIO_ImageInput* ) {
    return to_c(to_cpp(self)->operator=(*to_cpp()));
}



_Bool  OIIO_ImageInput_try_lock(OIIO_ImageInput* self) {
    return to_cpp(self)->try_lock();
}



int  OIIO_ImageInput_threads(const OIIO_ImageInput* self) {
    return to_cpp(self)->threads();
}



_Bool  OIIO_ImageInput_read_native_deep_tiles(OIIO_ImageInput* self, int subimage, int miplevel, int xbegin, int xend, int ybegin, int yend, int zbegin, int zend, int chbegin, int chend, OIIO_DeepData* deepdata) {
    return to_cpp(self)->read_native_deep_tiles(subimage, miplevel, xbegin, xend, ybegin, yend, zbegin, zend, chbegin, chend, *to_cpp(deepdata));
}



_Bool  OIIO_ImageInput_read_native_deep_scanlines(OIIO_ImageInput* self, int subimage, int miplevel, int ybegin, int yend, int z, int chbegin, int chend, OIIO_DeepData* deepdata) {
    return to_cpp(self)->read_native_deep_scanlines(subimage, miplevel, ybegin, yend, z, chbegin, chend, *to_cpp(deepdata));
}



void  OIIO_ImageInput_set_threads(OIIO_ImageInput* self, int n) {
    return to_cpp(self)->threads(n);
}



const OIIO_ImageSpec*  OIIO_ImageInput_spec(const OIIO_ImageInput* self) {
    return to_c(to_cpp(self)->spec());
}



const char*  OIIO_ImageInput_format_name(const OIIO_ImageInput* self) {
    return to_cpp(self)->format_name();
}



_Bool  OIIO_ImageInput_seek_subimage(OIIO_ImageInput* self, int subimage, int miplevel) {
    return to_cpp(self)->seek_subimage(subimage, miplevel);
}



void  OIIO_ImageInput_unlock(OIIO_ImageInput* self) {
    return to_cpp(self)->unlock();
}



int  OIIO_ImageInput_supports(const OIIO_ImageInput* self, const char* feature) {
    return to_cpp(self)->supports(feature);
}



_Bool  OIIO_ImageInput_set_ioproxy(OIIO_ImageInput* self, OIIO_Filesystem_IOProxy* ioproxy) {
    return to_cpp(self)->set_ioproxy(to_cpp(ioproxy));
}



OIIO_ImageInput*  OIIO_ImageInput_open(const char* filename, const OIIO_ImageSpec* config, OIIO_Filesystem_IOProxy* ioproxy) {
    return to_c(OIIO::ImageInput::open(filename, to_cpp(config), to_cpp(ioproxy)).release());
}



OIIO_ImageInput*  OIIO_ImageInput_create(const char* filename, _Bool do_open, const OIIO_ImageSpec* config, OIIO_Filesystem_IOProxy* ioproxy, const char* plugin_searchpath) {
    return to_c(OIIO::ImageInput::create(filename, do_open, to_cpp(config), to_cpp(ioproxy), plugin_searchpath).release());
}



OIIO_ImageSpec  OIIO_ImageInput_spec_copy(OIIO_ImageInput* self, int subimage, int miplevel) {
    return to_c(to_cpp(self)->spec(subimage, miplevel));
}



OIIO_ImageSpec  OIIO_ImageInput_spec_dimensions(OIIO_ImageInput* self, int subimage, int miplevel) {
    return to_c(to_cpp(self)->spec_dimensions(subimage, miplevel));
}



_Bool  OIIO_ImageInput_close(OIIO_ImageInput* self) {
    return to_cpp(self)->close();
}



void  OIIO_ImageInput_lock(OIIO_ImageInput* self) {
    return to_cpp(self)->lock();
}



_Bool  OIIO_ImageInput_read_image(OIIO_ImageInput* self, int subimage, int miplevel, int chbegin, int chend, OIIO_TypeDesc format, void* data, long xstride, long ystride, long zstride, * progress_callback, void* progress_callback_data) {
    return to_cpp(self)->read_image(subimage, miplevel, chbegin, chend, to_cpp(format), data, xstride, ystride, zstride, progress_callback, progress_callback_data);
}



int  OIIO_ImageInput_current_subimage(const OIIO_ImageInput* self) {
    return to_cpp(self)->current_subimage();
}



_Bool  OIIO_ImageInput_read_scanlines(OIIO_ImageInput* self, int subimage, int miplevel, int ybegin, int yend, int z, int chbegin, int chend, OIIO_TypeDesc format, void* data, long xstride, long ystride) {
    return to_cpp(self)->read_scanlines(subimage, miplevel, ybegin, yend, z, chbegin, chend, to_cpp(format), data, xstride, ystride);
}



int  OIIO_ImageInput_current_miplevel(const OIIO_ImageInput* self) {
    return to_cpp(self)->current_miplevel();
}



_Bool  OIIO_ImageInput_read_native_deep_image(OIIO_ImageInput* self, int subimage, int miplevel, OIIO_DeepData* deepdata) {
    return to_cpp(self)->read_native_deep_image(subimage, miplevel, *to_cpp(deepdata));
}



_Bool  OIIO_ImageInput_read_scanline(OIIO_ImageInput* self, int y, int z, OIIO_TypeDesc format, void* data, long xstride) {
    return to_cpp(self)->read_scanline(y, z, to_cpp(format), data, xstride);
}



_Bool  OIIO_ImageInput_valid_file(const OIIO_ImageInput* self, const char* filename) {
    return to_cpp(self)->valid_file(filename);
}



_Bool  OIIO_ImageInput_read_tile(OIIO_ImageInput* self, int x, int y, int z, OIIO_TypeDesc format, void* data, long xstride, long ystride, long zstride) {
    return to_cpp(self)->read_tile(x, y, z, to_cpp(format), data, xstride, ystride, zstride);
}



_Bool  OIIO_ImageInput_read_tiles(OIIO_ImageInput* self, int subimage, int miplevel, int xbegin, int xend, int ybegin, int yend, int zbegin, int zend, int chbegin, int chend, OIIO_TypeDesc format, void* data, long xstride, long ystride, long zstride) {
    return to_cpp(self)->read_tiles(subimage, miplevel, xbegin, xend, ybegin, yend, zbegin, zend, chbegin, chend, to_cpp(format), data, xstride, ystride, zstride);
}



}
    