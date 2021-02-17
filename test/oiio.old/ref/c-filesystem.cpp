//
#include "c-filesystem.h"
#include <OpenImageIO/filesystem.h>



namespace {
#include "casts.h"

CPPMM_DEFINE_POINTER_CASTS(OpenImageIO_v2_2::Filesystem::IOMemReader, OpenImageIO_v2_2_Filesystem_IOMemReader)
CPPMM_DEFINE_POINTER_CASTS(OpenImageIO_v2_2::Filesystem::IOProxy, OpenImageIO_v2_2_Filesystem_IOProxy)

#undef CPPMM_DEFINE_POINTER_CASTS
}

extern "C" {

int OpenImageIO_v2_2_Filesystem_replace_extension(const char* filepath, const char* new_extension, char* _result_buffer_ptr, int _result_buffer_len) {
    const std::string result = OpenImageIO_v2_2::Filesystem::replace_extension(filepath, new_extension);
    safe_strcpy(_result_buffer_ptr, result, _result_buffer_len);
    return result.size();
}



int OpenImageIO_v2_2_Filesystem_parent_path(const char* filepath, char* _result_buffer_ptr, int _result_buffer_len) {
    const std::string result = OpenImageIO_v2_2::Filesystem::parent_path(filepath);
    safe_strcpy(_result_buffer_ptr, result, _result_buffer_len);
    return result.size();
}



int OpenImageIO_v2_2_Filesystem_filename(const char* filepath, char* _result_buffer_ptr, int _result_buffer_len) {
    const std::string result = OpenImageIO_v2_2::Filesystem::filename(filepath);
    safe_strcpy(_result_buffer_ptr, result, _result_buffer_len);
    return result.size();
}



int OpenImageIO_v2_2_Filesystem_extension(const char* filepath, bool include_dot, char* _result_buffer_ptr, int _result_buffer_len) {
    const std::string result = OpenImageIO_v2_2::Filesystem::extension(filepath, include_dot);
    safe_strcpy(_result_buffer_ptr, result, _result_buffer_len);
    return result.size();
}



void OpenImageIO_v2_2_Filesystem_IOMemReader_delete(OpenImageIO_v2_2_Filesystem_IOMemReader* self) {
    to_cpp(self)->~IOMemReader();
}



unsigned long OpenImageIO_v2_2_Filesystem_IOMemReader_pread(OpenImageIO_v2_2_Filesystem_IOMemReader* self, void* buf, unsigned long size, long offset) {
    return to_cpp(self)->pread(buf, size, offset);
}



unsigned long OpenImageIO_v2_2_Filesystem_IOMemReader_read(OpenImageIO_v2_2_Filesystem_IOMemReader* self, void* buf, unsigned long size) {
    return to_cpp(self)->read(buf, size);
}



OpenImageIO_v2_2_Filesystem_IOMemReader* OpenImageIO_v2_2_Filesystem_IOMemReader_new(void* buf, unsigned long size) {
    return to_c(new OpenImageIO_v2_2::Filesystem::IOMemReader(buf, size));
}



bool OpenImageIO_v2_2_Filesystem_IOMemReader_seek(OpenImageIO_v2_2_Filesystem_IOMemReader* self, long offset) {
    return to_cpp(self)->seek(offset);
}



const char* OpenImageIO_v2_2_Filesystem_IOMemReader_proxytype(const OpenImageIO_v2_2_Filesystem_IOMemReader* self) {
    return to_cpp(self)->proxytype();
}



const char* OpenImageIO_v2_2_Filesystem_IOProxy_filename(const OpenImageIO_v2_2_Filesystem_IOProxy* self) {
    return to_cpp(self)->filename().c_str();
}



unsigned long OpenImageIO_v2_2_Filesystem_IOProxy_pwrite(OpenImageIO_v2_2_Filesystem_IOProxy* self, const void* buf, unsigned long size, long offset) {
    return to_cpp(self)->pwrite(buf, size, offset);
}



unsigned long OpenImageIO_v2_2_Filesystem_IOProxy_pread(OpenImageIO_v2_2_Filesystem_IOProxy* self, void* buf, unsigned long size, long offset) {
    return to_cpp(self)->pread(buf, size, offset);
}



unsigned long OpenImageIO_v2_2_Filesystem_IOProxy_read(OpenImageIO_v2_2_Filesystem_IOProxy* self, void* buf, unsigned long size) {
    return to_cpp(self)->read(buf, size);
}



const char* OpenImageIO_v2_2_Filesystem_IOProxy_proxytype(const OpenImageIO_v2_2_Filesystem_IOProxy* self) {
    return to_cpp(self)->proxytype();
}



unsigned long OpenImageIO_v2_2_Filesystem_IOProxy_write(OpenImageIO_v2_2_Filesystem_IOProxy* self, const void* buf, unsigned long size) {
    return to_cpp(self)->write(buf, size);
}



bool OpenImageIO_v2_2_Filesystem_IOProxy_seek(OpenImageIO_v2_2_Filesystem_IOProxy* self, long offset) {
    return to_cpp(self)->seek(offset);
}



void OpenImageIO_v2_2_Filesystem_IOProxy_delete(OpenImageIO_v2_2_Filesystem_IOProxy* self) {
    to_cpp(self)->~IOProxy();
}



void OpenImageIO_v2_2_Filesystem_IOProxy_close(OpenImageIO_v2_2_Filesystem_IOProxy* self) {
    to_cpp(self)->close();
}



bool OpenImageIO_v2_2_Filesystem_IOProxy_opened(const OpenImageIO_v2_2_Filesystem_IOProxy* self) {
    return to_cpp(self)->opened();
}



long OpenImageIO_v2_2_Filesystem_IOProxy_tell(OpenImageIO_v2_2_Filesystem_IOProxy* self) {
    return to_cpp(self)->tell();
}



}
    