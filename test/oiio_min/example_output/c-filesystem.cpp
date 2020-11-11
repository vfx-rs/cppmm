//
#include "c-filesystem.h"
#include <OpenImageIO/filesystem.h>

namespace {
#include "casts.h"

CPPMM_DEFINE_POINTER_CASTS(OIIO::Filesystem::IOMemReader, OIIO_Filesystem_IOMemReader)
CPPMM_DEFINE_POINTER_CASTS(OIIO::Filesystem::IOProxy, OIIO_Filesystem_IOProxy)

#undef CPPMM_DEFINE_POINTER_CASTS
}

extern "C" {

int OIIO_Filesystem_replace_extension(const char* filepath, const char* new_extension, char* _result_buffer_ptr, int _result_buffer_len) {
    const std::string result = OIIO::Filesystem::replace_extension(filepath, new_extension);
    safe_strcpy(_result_buffer_ptr, result, _result_buffer_len);
    return result.size();
}



int OIIO_Filesystem_parent_path(const char* filepath, char* _result_buffer_ptr, int _result_buffer_len) {
    const std::string result = OIIO::Filesystem::parent_path(filepath);
    safe_strcpy(_result_buffer_ptr, result, _result_buffer_len);
    return result.size();
}



int OIIO_Filesystem_filename(const char* filepath, char* _result_buffer_ptr, int _result_buffer_len) {
    const std::string result = OIIO::Filesystem::filename(filepath);
    safe_strcpy(_result_buffer_ptr, result, _result_buffer_len);
    return result.size();
}



int OIIO_Filesystem_extension(const char* filepath, bool include_dot, char* _result_buffer_ptr, int _result_buffer_len) {
    const std::string result = OIIO::Filesystem::extension(filepath, include_dot);
    safe_strcpy(_result_buffer_ptr, result, _result_buffer_len);
    return result.size();
}



void OIIO_Filesystem_IOMemReader_delete(OIIO_Filesystem_IOMemReader* self) {
    to_cpp(self)->~IOMemReader();
}



unsigned long OIIO_Filesystem_IOMemReader_pread(OIIO_Filesystem_IOMemReader* self, void* buf, unsigned long size, long offset) {
    return to_cpp(self)->pread(buf, size, offset);
}



unsigned long OIIO_Filesystem_IOMemReader_read(OIIO_Filesystem_IOMemReader* self, void* buf, unsigned long size) {
    return to_cpp(self)->read(buf, size);
}



OIIO_Filesystem_IOMemReader* OIIO_Filesystem_IOMemReader_new(void* buf, unsigned long size) {
    return to_c(new OIIO::Filesystem::IOMemReader(buf, size));
}



bool OIIO_Filesystem_IOMemReader_seek(OIIO_Filesystem_IOMemReader* self, long offset) {
    return to_cpp(self)->seek(offset);
}



const char* OIIO_Filesystem_IOMemReader_proxytype(const OIIO_Filesystem_IOMemReader* self) {
    return to_cpp(self)->proxytype();
}



const char* OIIO_Filesystem_IOProxy_filename(const OIIO_Filesystem_IOProxy* self) {
    return to_cpp(self)->filename().c_str();
}



unsigned long OIIO_Filesystem_IOProxy_pwrite(OIIO_Filesystem_IOProxy* self, const void* buf, unsigned long size, long offset) {
    return to_cpp(self)->pwrite(buf, size, offset);
}



unsigned long OIIO_Filesystem_IOProxy_pread(OIIO_Filesystem_IOProxy* self, void* buf, unsigned long size, long offset) {
    return to_cpp(self)->pread(buf, size, offset);
}



unsigned long OIIO_Filesystem_IOProxy_read(OIIO_Filesystem_IOProxy* self, void* buf, unsigned long size) {
    return to_cpp(self)->read(buf, size);
}



const char* OIIO_Filesystem_IOProxy_proxytype(const OIIO_Filesystem_IOProxy* self) {
    return to_cpp(self)->proxytype();
}



unsigned long OIIO_Filesystem_IOProxy_write(OIIO_Filesystem_IOProxy* self, const void* buf, unsigned long size) {
    return to_cpp(self)->write(buf, size);
}



bool OIIO_Filesystem_IOProxy_seek(OIIO_Filesystem_IOProxy* self, long offset) {
    return to_cpp(self)->seek(offset);
}



void OIIO_Filesystem_IOProxy_delete(OIIO_Filesystem_IOProxy* self) {
    to_cpp(self)->~IOProxy();
}



void OIIO_Filesystem_IOProxy_close(OIIO_Filesystem_IOProxy* self) {
    to_cpp(self)->close();
}



bool OIIO_Filesystem_IOProxy_opened(const OIIO_Filesystem_IOProxy* self) {
    return to_cpp(self)->opened();
}



long OIIO_Filesystem_IOProxy_tell(OIIO_Filesystem_IOProxy* self) {
    return to_cpp(self)->tell();
}



}
    