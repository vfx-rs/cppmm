#include <imf_header_private_.h>

#include <imath_box_private_.h>
#include <imath_vec_private_.h>
#include <imf_attribute_private_.h>
#include <imf_channellist_private_.h>
#include <imf_io_private_.h>
#include <imf_previewimage_private_.h>
#include <imf_tiledescription_private_.h>
#include <new>


void Imf_2_5_Header_dtor(
    Imf_2_5_Header * this_)
{
    (to_cpp(this_)) -> Imf_2_5::Header::~Header();
}

void Imf_2_5_Header_insert(
    Imf_2_5_Header * this_
    , char const * name
    , Imf_2_5_Attribute const * attribute)
{
    (to_cpp(this_)) -> insert(name, to_cpp_ref(attribute));
}

void Imf_2_5_Header_erase(
    Imf_2_5_Header * this_
    , char const * name)
{
    (to_cpp(this_)) -> erase(name);
}

Imf_2_5_Attribute * Imf_2_5_Header__index(
    Imf_2_5_Header * this_
    , char const * name)
{
    return to_c((to_cpp(this_)) -> operator[](name));
}

Imf_2_5_Attribute const * Imf_2_5_Header__index_1(
    Imf_2_5_Header const * this_
    , char const * name)
{
    return to_c((to_cpp(this_)) -> operator[](name));
}

Imf_2_5_Header_Iterator Imf_2_5_Header_begin(
    Imf_2_5_Header * this_)
{
    return to_c_copy((to_cpp(this_)) -> begin());
}

Imf_2_5_Header_ConstIterator Imf_2_5_Header_begin_1(
    Imf_2_5_Header const * this_)
{
    return to_c_copy((to_cpp(this_)) -> begin());
}

Imf_2_5_Header_Iterator Imf_2_5_Header_end(
    Imf_2_5_Header * this_)
{
    return to_c_copy((to_cpp(this_)) -> end());
}

Imf_2_5_Header_ConstIterator Imf_2_5_Header_end_1(
    Imf_2_5_Header const * this_)
{
    return to_c_copy((to_cpp(this_)) -> end());
}

Imf_2_5_Header_Iterator Imf_2_5_Header_find(
    Imf_2_5_Header * this_
    , char const * name)
{
    return to_c_copy((to_cpp(this_)) -> find(name));
}

Imf_2_5_Header_ConstIterator Imf_2_5_Header_find_1(
    Imf_2_5_Header const * this_
    , char const * name)
{
    return to_c_copy((to_cpp(this_)) -> find(name));
}

Imath_2_5_Box2i * Imf_2_5_Header_displayWindow(
    Imf_2_5_Header * this_)
{
    return to_c((to_cpp(this_)) -> displayWindow());
}

Imath_2_5_Box2i const * Imf_2_5_Header_displayWindow_1(
    Imf_2_5_Header const * this_)
{
    return to_c((to_cpp(this_)) -> displayWindow());
}

Imath_2_5_Box2i * Imf_2_5_Header_dataWindow(
    Imf_2_5_Header * this_)
{
    return to_c((to_cpp(this_)) -> dataWindow());
}

Imath_2_5_Box2i const * Imf_2_5_Header_dataWindow_1(
    Imf_2_5_Header const * this_)
{
    return to_c((to_cpp(this_)) -> dataWindow());
}

float * Imf_2_5_Header_pixelAspectRatio(
    Imf_2_5_Header * this_)
{
    return &((to_cpp(this_)) -> pixelAspectRatio());
}

float const * Imf_2_5_Header_pixelAspectRatio_1(
    Imf_2_5_Header const * this_)
{
    return &((to_cpp(this_)) -> pixelAspectRatio());
}

Imath_2_5_V2f * Imf_2_5_Header_screenWindowCenter(
    Imf_2_5_Header * this_)
{
    return to_c((to_cpp(this_)) -> screenWindowCenter());
}

Imath_2_5_V2f const * Imf_2_5_Header_screenWindowCenter_1(
    Imf_2_5_Header const * this_)
{
    return to_c((to_cpp(this_)) -> screenWindowCenter());
}

float * Imf_2_5_Header_screenWindowWidth(
    Imf_2_5_Header * this_)
{
    return &((to_cpp(this_)) -> screenWindowWidth());
}

float const * Imf_2_5_Header_screenWindowWidth_1(
    Imf_2_5_Header const * this_)
{
    return &((to_cpp(this_)) -> screenWindowWidth());
}

Imf_2_5_ChannelList * Imf_2_5_Header_channels(
    Imf_2_5_Header * this_)
{
    return to_c((to_cpp(this_)) -> channels());
}

Imf_2_5_ChannelList const * Imf_2_5_Header_channels_1(
    Imf_2_5_Header const * this_)
{
    return to_c((to_cpp(this_)) -> channels());
}

_Bool Imf_2_5_Header_hasName(
    Imf_2_5_Header const * this_)
{
    return (to_cpp(this_)) -> hasName();
}

_Bool Imf_2_5_Header_hasType(
    Imf_2_5_Header const * this_)
{
    return (to_cpp(this_)) -> hasType();
}

void Imf_2_5_Header_setVersion(
    Imf_2_5_Header * this_
    , int const version)
{
    (to_cpp(this_)) -> setVersion(version);
}

int * Imf_2_5_Header_version(
    Imf_2_5_Header * this_)
{
    return &((to_cpp(this_)) -> version());
}

int const * Imf_2_5_Header_version_1(
    Imf_2_5_Header const * this_)
{
    return &((to_cpp(this_)) -> version());
}

_Bool Imf_2_5_Header_hasVersion(
    Imf_2_5_Header const * this_)
{
    return (to_cpp(this_)) -> hasVersion();
}

void Imf_2_5_Header_setChunkCount(
    Imf_2_5_Header * this_
    , int chunks)
{
    (to_cpp(this_)) -> setChunkCount(chunks);
}

_Bool Imf_2_5_Header_hasChunkCount(
    Imf_2_5_Header const * this_)
{
    return (to_cpp(this_)) -> hasChunkCount();
}

int const * Imf_2_5_Header_chunkCount(
    Imf_2_5_Header const * this_)
{
    return &((to_cpp(this_)) -> chunkCount());
}

int * Imf_2_5_Header_chunkCount_1(
    Imf_2_5_Header * this_)
{
    return &((to_cpp(this_)) -> chunkCount());
}

_Bool Imf_2_5_Header_hasView(
    Imf_2_5_Header const * this_)
{
    return (to_cpp(this_)) -> hasView();
}

void Imf_2_5_Header_setTileDescription(
    Imf_2_5_Header * this_
    , Imf_2_5_TileDescription const * td)
{
    (to_cpp(this_)) -> setTileDescription(to_cpp_ref(td));
}

Imf_2_5_TileDescription * Imf_2_5_Header_tileDescription(
    Imf_2_5_Header * this_)
{
    return to_c((to_cpp(this_)) -> tileDescription());
}

Imf_2_5_TileDescription const * Imf_2_5_Header_tileDescription_1(
    Imf_2_5_Header const * this_)
{
    return to_c((to_cpp(this_)) -> tileDescription());
}

_Bool Imf_2_5_Header_hasTileDescription(
    Imf_2_5_Header const * this_)
{
    return (to_cpp(this_)) -> hasTileDescription();
}

void Imf_2_5_Header_setPreviewImage(
    Imf_2_5_Header * this_
    , Imf_2_5_PreviewImage const * p)
{
    (to_cpp(this_)) -> setPreviewImage(to_cpp_ref(p));
}

Imf_2_5_PreviewImage * Imf_2_5_Header_previewImage(
    Imf_2_5_Header * this_)
{
    return to_c((to_cpp(this_)) -> previewImage());
}

Imf_2_5_PreviewImage const * Imf_2_5_Header_previewImage_1(
    Imf_2_5_Header const * this_)
{
    return to_c((to_cpp(this_)) -> previewImage());
}

_Bool Imf_2_5_Header_hasPreviewImage(
    Imf_2_5_Header const * this_)
{
    return (to_cpp(this_)) -> hasPreviewImage();
}

void Imf_2_5_Header_sanityCheck(
    Imf_2_5_Header const * this_
    , _Bool isTiled
    , _Bool isMultipartFile)
{
    (to_cpp(this_)) -> sanityCheck(isTiled, isMultipartFile);
}

_Bool Imf_2_5_Header_readsNothing(
    Imf_2_5_Header * this_)
{
    return (to_cpp(this_)) -> readsNothing();
}

unsigned long Imf_2_5_Header_writeTo(
    Imf_2_5_Header const * this_
    , Imf_2_5_OStream * os
    , _Bool isTiled)
{
    return (to_cpp(this_)) -> writeTo(to_cpp_ref(os), isTiled);
}

void Imf_2_5_Header_readFrom(
    Imf_2_5_Header * this_
    , Imf_2_5_IStream * is
    , int * version)
{
    (to_cpp(this_)) -> readFrom(to_cpp_ref(is), *(version));
}

void Imf_2_5_Header_Iterator_Iterator(
    Imf_2_5_Header_Iterator * this_)
{
    new (this_) Imf_2_5::Header::Iterator();
}

Imf_2_5_Header_Iterator * Imf_2_5_Header_Iterator__op_inc(
    Imf_2_5_Header_Iterator * this_)
{
    return to_c((to_cpp(this_)) -> operator++());
}

Imf_2_5_Header_Iterator Imf_2_5_Header_Iterator__op_inc_1(
    Imf_2_5_Header_Iterator * this_
    , int )
{
    return to_c_copy((to_cpp(this_)) -> operator++());
}

char const * Imf_2_5_Header_Iterator_name(
    Imf_2_5_Header_Iterator const * this_)
{
    return (to_cpp(this_)) -> name();
}

Imf_2_5_Attribute * Imf_2_5_Header_Iterator_attribute(
    Imf_2_5_Header_Iterator const * this_)
{
    return to_c((to_cpp(this_)) -> attribute());
}

void Imf_2_5_Header_Iterator_Iterator_1(
    Imf_2_5_Header_Iterator * this_
    , Imf_2_5_Header_Iterator const * rhs)
{
    new (this_) Imf_2_5::Header::Iterator(to_cpp_ref(rhs));
}

void Imf_2_5_Header_ConstIterator_ConstIterator(
    Imf_2_5_Header_ConstIterator * this_)
{
    new (this_) Imf_2_5::Header::ConstIterator();
}

Imf_2_5_Header_ConstIterator * Imf_2_5_Header_ConstIterator__op_inc(
    Imf_2_5_Header_ConstIterator * this_)
{
    return to_c((to_cpp(this_)) -> operator++());
}

Imf_2_5_Header_ConstIterator Imf_2_5_Header_ConstIterator__op_inc_1(
    Imf_2_5_Header_ConstIterator * this_
    , int )
{
    return to_c_copy((to_cpp(this_)) -> operator++());
}

char const * Imf_2_5_Header_ConstIterator_name(
    Imf_2_5_Header_ConstIterator const * this_)
{
    return (to_cpp(this_)) -> name();
}

void Imf_2_5_Header_ConstIterator_ConstIterator_1(
    Imf_2_5_Header_ConstIterator * this_
    , Imf_2_5_Header_ConstIterator const * rhs)
{
    new (this_) Imf_2_5::Header::ConstIterator(to_cpp_ref(rhs));
}
