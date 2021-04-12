#include <imf_attribute_private_.h>

#include <imath_box_private_.h>
#include <imath_matrix_private_.h>
#include <imath_vec_private_.h>
#include <imf_channellist_private_.h>
#include <imf_chromaticities_private_.h>
#include <imf_io_private_.h>
#include <imf_keycode_private_.h>
#include <imf_previewimage_private_.h>
#include <imf_rational_private_.h>
#include <imf_tiledescription_private_.h>
#include <imf_timecode_private_.h>
#include <new>


void Imf_2_5_Attribute_dtor(
    Imf_2_5_Attribute * this_)
{
    (to_cpp(this_)) -> Imf_2_5::Attribute::~Attribute();
}

char const * Imf_2_5_Attribute_typeName(
    Imf_2_5_Attribute const * this_)
{
    return (to_cpp(this_)) -> typeName();
}

Imf_2_5_Attribute * Imf_2_5_Attribute_copy(
    Imf_2_5_Attribute const * this_)
{
    return to_c((to_cpp(this_)) -> copy());
}

void Imf_2_5_Attribute_writeValueTo(
    Imf_2_5_Attribute const * this_
    , Imf_2_5_OStream * os
    , int version)
{
    (to_cpp(this_)) -> writeValueTo(to_cpp_ref(os), version);
}

void Imf_2_5_Attribute_readValueFrom(
    Imf_2_5_Attribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version)
{
    (to_cpp(this_)) -> readValueFrom(to_cpp_ref(is), size, version);
}

void Imf_2_5_Attribute_copyValueFrom(
    Imf_2_5_Attribute * this_
    , Imf_2_5_Attribute const * other)
{
    (to_cpp(this_)) -> copyValueFrom(to_cpp_ref(other));
}

char const * Imf_2_5_IntAttribute_typeName(
    Imf_2_5_IntAttribute const * this_)
{
    return (to_cpp(this_)) -> typeName();
}

Imf_2_5_Attribute * Imf_2_5_IntAttribute_copy(
    Imf_2_5_IntAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> copy());
}

void Imf_2_5_IntAttribute_writeValueTo(
    Imf_2_5_IntAttribute const * this_
    , Imf_2_5_OStream * os
    , int version)
{
    (to_cpp(this_)) -> writeValueTo(to_cpp_ref(os), version);
}

void Imf_2_5_IntAttribute_readValueFrom(
    Imf_2_5_IntAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version)
{
    (to_cpp(this_)) -> readValueFrom(to_cpp_ref(is), size, version);
}

void Imf_2_5_IntAttribute_copyValueFrom(
    Imf_2_5_IntAttribute * this_
    , Imf_2_5_Attribute const * other)
{
    (to_cpp(this_)) -> copyValueFrom(to_cpp_ref(other));
}

void Imf_2_5_IntAttribute_TypedAttribute(
    Imf_2_5_IntAttribute * this_)
{
    new (this_) Imf_2_5::TypedAttribute<int>();
}

void Imf_2_5_IntAttribute_TypedAttribute_1(
    Imf_2_5_IntAttribute * this_
    , int const * value)
{
    new (this_) Imf_2_5::TypedAttribute<int>(*(value));
}

void Imf_2_5_IntAttribute_dtor(
    Imf_2_5_IntAttribute * this_)
{
    (to_cpp(this_)) -> Imf_2_5::TypedAttribute<int>::~TypedAttribute();
}

int * Imf_2_5_IntAttribute_value(
    Imf_2_5_IntAttribute * this_)
{
    return &((to_cpp(this_)) -> value());
}

int const * Imf_2_5_IntAttribute_value_1(
    Imf_2_5_IntAttribute const * this_)
{
    return &((to_cpp(this_)) -> value());
}

char const * Imf_2_5_FloatAttribute_typeName(
    Imf_2_5_FloatAttribute const * this_)
{
    return (to_cpp(this_)) -> typeName();
}

Imf_2_5_Attribute * Imf_2_5_FloatAttribute_copy(
    Imf_2_5_FloatAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> copy());
}

void Imf_2_5_FloatAttribute_writeValueTo(
    Imf_2_5_FloatAttribute const * this_
    , Imf_2_5_OStream * os
    , int version)
{
    (to_cpp(this_)) -> writeValueTo(to_cpp_ref(os), version);
}

void Imf_2_5_FloatAttribute_readValueFrom(
    Imf_2_5_FloatAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version)
{
    (to_cpp(this_)) -> readValueFrom(to_cpp_ref(is), size, version);
}

void Imf_2_5_FloatAttribute_copyValueFrom(
    Imf_2_5_FloatAttribute * this_
    , Imf_2_5_Attribute const * other)
{
    (to_cpp(this_)) -> copyValueFrom(to_cpp_ref(other));
}

void Imf_2_5_FloatAttribute_TypedAttribute(
    Imf_2_5_FloatAttribute * this_)
{
    new (this_) Imf_2_5::TypedAttribute<float>();
}

void Imf_2_5_FloatAttribute_TypedAttribute_1(
    Imf_2_5_FloatAttribute * this_
    , float const * value)
{
    new (this_) Imf_2_5::TypedAttribute<float>(*(value));
}

void Imf_2_5_FloatAttribute_dtor(
    Imf_2_5_FloatAttribute * this_)
{
    (to_cpp(this_)) -> Imf_2_5::TypedAttribute<float>::~TypedAttribute();
}

float * Imf_2_5_FloatAttribute_value(
    Imf_2_5_FloatAttribute * this_)
{
    return &((to_cpp(this_)) -> value());
}

float const * Imf_2_5_FloatAttribute_value_1(
    Imf_2_5_FloatAttribute const * this_)
{
    return &((to_cpp(this_)) -> value());
}

char const * Imf_2_5_DoubleAttribute_typeName(
    Imf_2_5_DoubleAttribute const * this_)
{
    return (to_cpp(this_)) -> typeName();
}

Imf_2_5_Attribute * Imf_2_5_DoubleAttribute_copy(
    Imf_2_5_DoubleAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> copy());
}

void Imf_2_5_DoubleAttribute_writeValueTo(
    Imf_2_5_DoubleAttribute const * this_
    , Imf_2_5_OStream * os
    , int version)
{
    (to_cpp(this_)) -> writeValueTo(to_cpp_ref(os), version);
}

void Imf_2_5_DoubleAttribute_readValueFrom(
    Imf_2_5_DoubleAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version)
{
    (to_cpp(this_)) -> readValueFrom(to_cpp_ref(is), size, version);
}

void Imf_2_5_DoubleAttribute_copyValueFrom(
    Imf_2_5_DoubleAttribute * this_
    , Imf_2_5_Attribute const * other)
{
    (to_cpp(this_)) -> copyValueFrom(to_cpp_ref(other));
}

void Imf_2_5_DoubleAttribute_TypedAttribute(
    Imf_2_5_DoubleAttribute * this_)
{
    new (this_) Imf_2_5::TypedAttribute<double>();
}

void Imf_2_5_DoubleAttribute_TypedAttribute_1(
    Imf_2_5_DoubleAttribute * this_
    , double const * value)
{
    new (this_) Imf_2_5::TypedAttribute<double>(*(value));
}

void Imf_2_5_DoubleAttribute_dtor(
    Imf_2_5_DoubleAttribute * this_)
{
    (to_cpp(this_)) -> Imf_2_5::TypedAttribute<double>::~TypedAttribute();
}

double * Imf_2_5_DoubleAttribute_value(
    Imf_2_5_DoubleAttribute * this_)
{
    return &((to_cpp(this_)) -> value());
}

double const * Imf_2_5_DoubleAttribute_value_1(
    Imf_2_5_DoubleAttribute const * this_)
{
    return &((to_cpp(this_)) -> value());
}

char const * Imf_2_5_Box2iAttribute_typeName(
    Imf_2_5_Box2iAttribute const * this_)
{
    return (to_cpp(this_)) -> typeName();
}

Imf_2_5_Attribute * Imf_2_5_Box2iAttribute_copy(
    Imf_2_5_Box2iAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> copy());
}

void Imf_2_5_Box2iAttribute_writeValueTo(
    Imf_2_5_Box2iAttribute const * this_
    , Imf_2_5_OStream * os
    , int version)
{
    (to_cpp(this_)) -> writeValueTo(to_cpp_ref(os), version);
}

void Imf_2_5_Box2iAttribute_readValueFrom(
    Imf_2_5_Box2iAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version)
{
    (to_cpp(this_)) -> readValueFrom(to_cpp_ref(is), size, version);
}

void Imf_2_5_Box2iAttribute_copyValueFrom(
    Imf_2_5_Box2iAttribute * this_
    , Imf_2_5_Attribute const * other)
{
    (to_cpp(this_)) -> copyValueFrom(to_cpp_ref(other));
}

void Imf_2_5_Box2iAttribute_TypedAttribute(
    Imf_2_5_Box2iAttribute * this_)
{
    new (this_) Imf_2_5::TypedAttribute<Imath::Box2i>();
}

void Imf_2_5_Box2iAttribute_TypedAttribute_1(
    Imf_2_5_Box2iAttribute * this_
    , Imath_2_5_Box2i const * value)
{
    new (this_) Imf_2_5::TypedAttribute<Imath::Box2i>(to_cpp_ref(value));
}

void Imf_2_5_Box2iAttribute_dtor(
    Imf_2_5_Box2iAttribute * this_)
{
    (to_cpp(this_)) -> Imf_2_5::TypedAttribute<Imath_2_5::Box<Imath_2_5::Vec2<int> > >::~TypedAttribute();
}

Imath_2_5_Box2i * Imf_2_5_Box2iAttribute_value(
    Imf_2_5_Box2iAttribute * this_)
{
    return to_c((to_cpp(this_)) -> value());
}

Imath_2_5_Box2i const * Imf_2_5_Box2iAttribute_value_1(
    Imf_2_5_Box2iAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> value());
}

char const * Imf_2_5_Box2fAttribute_typeName(
    Imf_2_5_Box2fAttribute const * this_)
{
    return (to_cpp(this_)) -> typeName();
}

Imf_2_5_Attribute * Imf_2_5_Box2fAttribute_copy(
    Imf_2_5_Box2fAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> copy());
}

void Imf_2_5_Box2fAttribute_writeValueTo(
    Imf_2_5_Box2fAttribute const * this_
    , Imf_2_5_OStream * os
    , int version)
{
    (to_cpp(this_)) -> writeValueTo(to_cpp_ref(os), version);
}

void Imf_2_5_Box2fAttribute_readValueFrom(
    Imf_2_5_Box2fAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version)
{
    (to_cpp(this_)) -> readValueFrom(to_cpp_ref(is), size, version);
}

void Imf_2_5_Box2fAttribute_copyValueFrom(
    Imf_2_5_Box2fAttribute * this_
    , Imf_2_5_Attribute const * other)
{
    (to_cpp(this_)) -> copyValueFrom(to_cpp_ref(other));
}

void Imf_2_5_Box2fAttribute_TypedAttribute(
    Imf_2_5_Box2fAttribute * this_)
{
    new (this_) Imf_2_5::TypedAttribute<Imath::Box2f>();
}

void Imf_2_5_Box2fAttribute_TypedAttribute_1(
    Imf_2_5_Box2fAttribute * this_
    , Imath_2_5_Box2f const * value)
{
    new (this_) Imf_2_5::TypedAttribute<Imath::Box2f>(to_cpp_ref(value));
}

void Imf_2_5_Box2fAttribute_dtor(
    Imf_2_5_Box2fAttribute * this_)
{
    (to_cpp(this_)) -> Imf_2_5::TypedAttribute<Imath_2_5::Box<Imath_2_5::Vec2<float> > >::~TypedAttribute();
}

Imath_2_5_Box2f * Imf_2_5_Box2fAttribute_value(
    Imf_2_5_Box2fAttribute * this_)
{
    return to_c((to_cpp(this_)) -> value());
}

Imath_2_5_Box2f const * Imf_2_5_Box2fAttribute_value_1(
    Imf_2_5_Box2fAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> value());
}

char const * Imf_2_5_ChannelListAttribute_typeName(
    Imf_2_5_ChannelListAttribute const * this_)
{
    return (to_cpp(this_)) -> typeName();
}

Imf_2_5_Attribute * Imf_2_5_ChannelListAttribute_copy(
    Imf_2_5_ChannelListAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> copy());
}

void Imf_2_5_ChannelListAttribute_writeValueTo(
    Imf_2_5_ChannelListAttribute const * this_
    , Imf_2_5_OStream * os
    , int version)
{
    (to_cpp(this_)) -> writeValueTo(to_cpp_ref(os), version);
}

void Imf_2_5_ChannelListAttribute_readValueFrom(
    Imf_2_5_ChannelListAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version)
{
    (to_cpp(this_)) -> readValueFrom(to_cpp_ref(is), size, version);
}

void Imf_2_5_ChannelListAttribute_copyValueFrom(
    Imf_2_5_ChannelListAttribute * this_
    , Imf_2_5_Attribute const * other)
{
    (to_cpp(this_)) -> copyValueFrom(to_cpp_ref(other));
}

void Imf_2_5_ChannelListAttribute_TypedAttribute(
    Imf_2_5_ChannelListAttribute * this_)
{
    new (this_) Imf_2_5::TypedAttribute<Imf::ChannelList>();
}

void Imf_2_5_ChannelListAttribute_TypedAttribute_1(
    Imf_2_5_ChannelListAttribute * this_
    , Imf_2_5_ChannelList const * value)
{
    new (this_) Imf_2_5::TypedAttribute<Imf::ChannelList>(to_cpp_ref(value));
}

void Imf_2_5_ChannelListAttribute_dtor(
    Imf_2_5_ChannelListAttribute * this_)
{
    (to_cpp(this_)) -> Imf_2_5::TypedAttribute<Imf_2_5::ChannelList>::~TypedAttribute();
}

Imf_2_5_ChannelList * Imf_2_5_ChannelListAttribute_value(
    Imf_2_5_ChannelListAttribute * this_)
{
    return to_c((to_cpp(this_)) -> value());
}

Imf_2_5_ChannelList const * Imf_2_5_ChannelListAttribute_value_1(
    Imf_2_5_ChannelListAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> value());
}

char const * Imf_2_5_ChromaticitiesAttribute_typeName(
    Imf_2_5_ChromaticitiesAttribute const * this_)
{
    return (to_cpp(this_)) -> typeName();
}

Imf_2_5_Attribute * Imf_2_5_ChromaticitiesAttribute_copy(
    Imf_2_5_ChromaticitiesAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> copy());
}

void Imf_2_5_ChromaticitiesAttribute_writeValueTo(
    Imf_2_5_ChromaticitiesAttribute const * this_
    , Imf_2_5_OStream * os
    , int version)
{
    (to_cpp(this_)) -> writeValueTo(to_cpp_ref(os), version);
}

void Imf_2_5_ChromaticitiesAttribute_readValueFrom(
    Imf_2_5_ChromaticitiesAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version)
{
    (to_cpp(this_)) -> readValueFrom(to_cpp_ref(is), size, version);
}

void Imf_2_5_ChromaticitiesAttribute_copyValueFrom(
    Imf_2_5_ChromaticitiesAttribute * this_
    , Imf_2_5_Attribute const * other)
{
    (to_cpp(this_)) -> copyValueFrom(to_cpp_ref(other));
}

void Imf_2_5_ChromaticitiesAttribute_TypedAttribute(
    Imf_2_5_ChromaticitiesAttribute * this_)
{
    new (this_) Imf_2_5::TypedAttribute<Imf::Chromaticities>();
}

void Imf_2_5_ChromaticitiesAttribute_TypedAttribute_1(
    Imf_2_5_ChromaticitiesAttribute * this_
    , Imf_2_5_Chromaticities const * value)
{
    new (this_) Imf_2_5::TypedAttribute<Imf::Chromaticities>(to_cpp_ref(value));
}

void Imf_2_5_ChromaticitiesAttribute_dtor(
    Imf_2_5_ChromaticitiesAttribute * this_)
{
    (to_cpp(this_)) -> Imf_2_5::TypedAttribute<Imf_2_5::Chromaticities>::~TypedAttribute();
}

Imf_2_5_Chromaticities * Imf_2_5_ChromaticitiesAttribute_value(
    Imf_2_5_ChromaticitiesAttribute * this_)
{
    return to_c((to_cpp(this_)) -> value());
}

Imf_2_5_Chromaticities const * Imf_2_5_ChromaticitiesAttribute_value_1(
    Imf_2_5_ChromaticitiesAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> value());
}

char const * Imf_2_5_CompressionAttribute_typeName(
    Imf_2_5_CompressionAttribute const * this_)
{
    return (to_cpp(this_)) -> typeName();
}

Imf_2_5_Attribute * Imf_2_5_CompressionAttribute_copy(
    Imf_2_5_CompressionAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> copy());
}

void Imf_2_5_CompressionAttribute_writeValueTo(
    Imf_2_5_CompressionAttribute const * this_
    , Imf_2_5_OStream * os
    , int version)
{
    (to_cpp(this_)) -> writeValueTo(to_cpp_ref(os), version);
}

void Imf_2_5_CompressionAttribute_readValueFrom(
    Imf_2_5_CompressionAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version)
{
    (to_cpp(this_)) -> readValueFrom(to_cpp_ref(is), size, version);
}

void Imf_2_5_CompressionAttribute_copyValueFrom(
    Imf_2_5_CompressionAttribute * this_
    , Imf_2_5_Attribute const * other)
{
    (to_cpp(this_)) -> copyValueFrom(to_cpp_ref(other));
}

void Imf_2_5_CompressionAttribute_TypedAttribute(
    Imf_2_5_CompressionAttribute * this_)
{
    new (this_) Imf_2_5::TypedAttribute<Imf::Compression>();
}

void Imf_2_5_CompressionAttribute_dtor(
    Imf_2_5_CompressionAttribute * this_)
{
    (to_cpp(this_)) -> Imf_2_5::TypedAttribute<Imf_2_5::Compression>::~TypedAttribute();
}

char const * Imf_2_5_DeepImageStateAttribute_typeName(
    Imf_2_5_DeepImageStateAttribute const * this_)
{
    return (to_cpp(this_)) -> typeName();
}

Imf_2_5_Attribute * Imf_2_5_DeepImageStateAttribute_copy(
    Imf_2_5_DeepImageStateAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> copy());
}

void Imf_2_5_DeepImageStateAttribute_writeValueTo(
    Imf_2_5_DeepImageStateAttribute const * this_
    , Imf_2_5_OStream * os
    , int version)
{
    (to_cpp(this_)) -> writeValueTo(to_cpp_ref(os), version);
}

void Imf_2_5_DeepImageStateAttribute_readValueFrom(
    Imf_2_5_DeepImageStateAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version)
{
    (to_cpp(this_)) -> readValueFrom(to_cpp_ref(is), size, version);
}

void Imf_2_5_DeepImageStateAttribute_copyValueFrom(
    Imf_2_5_DeepImageStateAttribute * this_
    , Imf_2_5_Attribute const * other)
{
    (to_cpp(this_)) -> copyValueFrom(to_cpp_ref(other));
}

void Imf_2_5_DeepImageStateAttribute_TypedAttribute(
    Imf_2_5_DeepImageStateAttribute * this_)
{
    new (this_) Imf_2_5::TypedAttribute<Imf::DeepImageState>();
}

void Imf_2_5_DeepImageStateAttribute_dtor(
    Imf_2_5_DeepImageStateAttribute * this_)
{
    (to_cpp(this_)) -> Imf_2_5::TypedAttribute<Imf_2_5::DeepImageState>::~TypedAttribute();
}

char const * Imf_2_5_EnvmapAttribute_typeName(
    Imf_2_5_EnvmapAttribute const * this_)
{
    return (to_cpp(this_)) -> typeName();
}

Imf_2_5_Attribute * Imf_2_5_EnvmapAttribute_copy(
    Imf_2_5_EnvmapAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> copy());
}

void Imf_2_5_EnvmapAttribute_writeValueTo(
    Imf_2_5_EnvmapAttribute const * this_
    , Imf_2_5_OStream * os
    , int version)
{
    (to_cpp(this_)) -> writeValueTo(to_cpp_ref(os), version);
}

void Imf_2_5_EnvmapAttribute_readValueFrom(
    Imf_2_5_EnvmapAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version)
{
    (to_cpp(this_)) -> readValueFrom(to_cpp_ref(is), size, version);
}

void Imf_2_5_EnvmapAttribute_copyValueFrom(
    Imf_2_5_EnvmapAttribute * this_
    , Imf_2_5_Attribute const * other)
{
    (to_cpp(this_)) -> copyValueFrom(to_cpp_ref(other));
}

void Imf_2_5_EnvmapAttribute_TypedAttribute(
    Imf_2_5_EnvmapAttribute * this_)
{
    new (this_) Imf_2_5::TypedAttribute<Imf::Envmap>();
}

void Imf_2_5_EnvmapAttribute_dtor(
    Imf_2_5_EnvmapAttribute * this_)
{
    (to_cpp(this_)) -> Imf_2_5::TypedAttribute<Imf_2_5::Envmap>::~TypedAttribute();
}

char const * Imf_2_5_FloatVectorAttribute_typeName(
    Imf_2_5_FloatVectorAttribute const * this_)
{
    return (to_cpp(this_)) -> typeName();
}

Imf_2_5_Attribute * Imf_2_5_FloatVectorAttribute_copy(
    Imf_2_5_FloatVectorAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> copy());
}

void Imf_2_5_FloatVectorAttribute_writeValueTo(
    Imf_2_5_FloatVectorAttribute const * this_
    , Imf_2_5_OStream * os
    , int version)
{
    (to_cpp(this_)) -> writeValueTo(to_cpp_ref(os), version);
}

void Imf_2_5_FloatVectorAttribute_readValueFrom(
    Imf_2_5_FloatVectorAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version)
{
    (to_cpp(this_)) -> readValueFrom(to_cpp_ref(is), size, version);
}

void Imf_2_5_FloatVectorAttribute_copyValueFrom(
    Imf_2_5_FloatVectorAttribute * this_
    , Imf_2_5_Attribute const * other)
{
    (to_cpp(this_)) -> copyValueFrom(to_cpp_ref(other));
}

void Imf_2_5_FloatVectorAttribute_TypedAttribute(
    Imf_2_5_FloatVectorAttribute * this_)
{
    new (this_) Imf_2_5::TypedAttribute<std::vector<float> >();
}

void Imf_2_5_FloatVectorAttribute_TypedAttribute_1(
    Imf_2_5_FloatVectorAttribute * this_
    , std_vector const * value)
{
    new (this_) Imf_2_5::TypedAttribute<std::vector<float> >(to_cpp_ref(value));
}

void Imf_2_5_FloatVectorAttribute_dtor(
    Imf_2_5_FloatVectorAttribute * this_)
{
    (to_cpp(this_)) -> Imf_2_5::TypedAttribute<std::vector<float> >::~TypedAttribute();
}

std_vector * Imf_2_5_FloatVectorAttribute_value(
    Imf_2_5_FloatVectorAttribute * this_)
{
    return to_c((to_cpp(this_)) -> value());
}

std_vector const * Imf_2_5_FloatVectorAttribute_value_1(
    Imf_2_5_FloatVectorAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> value());
}

char const * Imf_2_5_StringVectorAttribute_typeName(
    Imf_2_5_StringVectorAttribute const * this_)
{
    return (to_cpp(this_)) -> typeName();
}

Imf_2_5_Attribute * Imf_2_5_StringVectorAttribute_copy(
    Imf_2_5_StringVectorAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> copy());
}

void Imf_2_5_StringVectorAttribute_writeValueTo(
    Imf_2_5_StringVectorAttribute const * this_
    , Imf_2_5_OStream * os
    , int version)
{
    (to_cpp(this_)) -> writeValueTo(to_cpp_ref(os), version);
}

void Imf_2_5_StringVectorAttribute_readValueFrom(
    Imf_2_5_StringVectorAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version)
{
    (to_cpp(this_)) -> readValueFrom(to_cpp_ref(is), size, version);
}

void Imf_2_5_StringVectorAttribute_copyValueFrom(
    Imf_2_5_StringVectorAttribute * this_
    , Imf_2_5_Attribute const * other)
{
    (to_cpp(this_)) -> copyValueFrom(to_cpp_ref(other));
}

void Imf_2_5_StringVectorAttribute_TypedAttribute(
    Imf_2_5_StringVectorAttribute * this_)
{
    new (this_) Imf_2_5::TypedAttribute<std::vector<std::string> >();
}

void Imf_2_5_StringVectorAttribute_dtor(
    Imf_2_5_StringVectorAttribute * this_)
{
    (to_cpp(this_)) -> Imf_2_5::TypedAttribute<std::vector<std::__cxx11::basic_string<char>, std::allocator<std::__cxx11::basic_string<char> > > >::~TypedAttribute();
}

char const * Imf_2_5_StringAttribute_typeName(
    Imf_2_5_StringAttribute const * this_)
{
    return (to_cpp(this_)) -> typeName();
}

Imf_2_5_Attribute * Imf_2_5_StringAttribute_copy(
    Imf_2_5_StringAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> copy());
}

void Imf_2_5_StringAttribute_writeValueTo(
    Imf_2_5_StringAttribute const * this_
    , Imf_2_5_OStream * os
    , int version)
{
    (to_cpp(this_)) -> writeValueTo(to_cpp_ref(os), version);
}

void Imf_2_5_StringAttribute_readValueFrom(
    Imf_2_5_StringAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version)
{
    (to_cpp(this_)) -> readValueFrom(to_cpp_ref(is), size, version);
}

void Imf_2_5_StringAttribute_copyValueFrom(
    Imf_2_5_StringAttribute * this_
    , Imf_2_5_Attribute const * other)
{
    (to_cpp(this_)) -> copyValueFrom(to_cpp_ref(other));
}

void Imf_2_5_StringAttribute_TypedAttribute(
    Imf_2_5_StringAttribute * this_)
{
    new (this_) Imf_2_5::TypedAttribute<std::string>();
}

void Imf_2_5_StringAttribute_dtor(
    Imf_2_5_StringAttribute * this_)
{
    (to_cpp(this_)) -> Imf_2_5::TypedAttribute<std::__cxx11::basic_string<char> >::~TypedAttribute();
}

char const * Imf_2_5_KeyCodeAttribute_typeName(
    Imf_2_5_KeyCodeAttribute const * this_)
{
    return (to_cpp(this_)) -> typeName();
}

Imf_2_5_Attribute * Imf_2_5_KeyCodeAttribute_copy(
    Imf_2_5_KeyCodeAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> copy());
}

void Imf_2_5_KeyCodeAttribute_writeValueTo(
    Imf_2_5_KeyCodeAttribute const * this_
    , Imf_2_5_OStream * os
    , int version)
{
    (to_cpp(this_)) -> writeValueTo(to_cpp_ref(os), version);
}

void Imf_2_5_KeyCodeAttribute_readValueFrom(
    Imf_2_5_KeyCodeAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version)
{
    (to_cpp(this_)) -> readValueFrom(to_cpp_ref(is), size, version);
}

void Imf_2_5_KeyCodeAttribute_copyValueFrom(
    Imf_2_5_KeyCodeAttribute * this_
    , Imf_2_5_Attribute const * other)
{
    (to_cpp(this_)) -> copyValueFrom(to_cpp_ref(other));
}

void Imf_2_5_KeyCodeAttribute_TypedAttribute(
    Imf_2_5_KeyCodeAttribute * this_)
{
    new (this_) Imf_2_5::TypedAttribute<Imf::KeyCode>();
}

void Imf_2_5_KeyCodeAttribute_TypedAttribute_1(
    Imf_2_5_KeyCodeAttribute * this_
    , Imf_2_5_KeyCode const * value)
{
    new (this_) Imf_2_5::TypedAttribute<Imf::KeyCode>(to_cpp_ref(value));
}

void Imf_2_5_KeyCodeAttribute_dtor(
    Imf_2_5_KeyCodeAttribute * this_)
{
    (to_cpp(this_)) -> Imf_2_5::TypedAttribute<Imf_2_5::KeyCode>::~TypedAttribute();
}

Imf_2_5_KeyCode * Imf_2_5_KeyCodeAttribute_value(
    Imf_2_5_KeyCodeAttribute * this_)
{
    return to_c((to_cpp(this_)) -> value());
}

Imf_2_5_KeyCode const * Imf_2_5_KeyCodeAttribute_value_1(
    Imf_2_5_KeyCodeAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> value());
}

char const * Imf_2_5_LineOrderAttribute_typeName(
    Imf_2_5_LineOrderAttribute const * this_)
{
    return (to_cpp(this_)) -> typeName();
}

Imf_2_5_Attribute * Imf_2_5_LineOrderAttribute_copy(
    Imf_2_5_LineOrderAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> copy());
}

void Imf_2_5_LineOrderAttribute_writeValueTo(
    Imf_2_5_LineOrderAttribute const * this_
    , Imf_2_5_OStream * os
    , int version)
{
    (to_cpp(this_)) -> writeValueTo(to_cpp_ref(os), version);
}

void Imf_2_5_LineOrderAttribute_readValueFrom(
    Imf_2_5_LineOrderAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version)
{
    (to_cpp(this_)) -> readValueFrom(to_cpp_ref(is), size, version);
}

void Imf_2_5_LineOrderAttribute_copyValueFrom(
    Imf_2_5_LineOrderAttribute * this_
    , Imf_2_5_Attribute const * other)
{
    (to_cpp(this_)) -> copyValueFrom(to_cpp_ref(other));
}

void Imf_2_5_LineOrderAttribute_TypedAttribute(
    Imf_2_5_LineOrderAttribute * this_)
{
    new (this_) Imf_2_5::TypedAttribute<Imf::LineOrder>();
}

void Imf_2_5_LineOrderAttribute_dtor(
    Imf_2_5_LineOrderAttribute * this_)
{
    (to_cpp(this_)) -> Imf_2_5::TypedAttribute<Imf_2_5::LineOrder>::~TypedAttribute();
}

char const * Imf_2_5_M33fAttribute_typeName(
    Imf_2_5_M33fAttribute const * this_)
{
    return (to_cpp(this_)) -> typeName();
}

Imf_2_5_Attribute * Imf_2_5_M33fAttribute_copy(
    Imf_2_5_M33fAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> copy());
}

void Imf_2_5_M33fAttribute_writeValueTo(
    Imf_2_5_M33fAttribute const * this_
    , Imf_2_5_OStream * os
    , int version)
{
    (to_cpp(this_)) -> writeValueTo(to_cpp_ref(os), version);
}

void Imf_2_5_M33fAttribute_readValueFrom(
    Imf_2_5_M33fAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version)
{
    (to_cpp(this_)) -> readValueFrom(to_cpp_ref(is), size, version);
}

void Imf_2_5_M33fAttribute_copyValueFrom(
    Imf_2_5_M33fAttribute * this_
    , Imf_2_5_Attribute const * other)
{
    (to_cpp(this_)) -> copyValueFrom(to_cpp_ref(other));
}

void Imf_2_5_M33fAttribute_TypedAttribute(
    Imf_2_5_M33fAttribute * this_)
{
    new (this_) Imf_2_5::TypedAttribute<Imath::M33f>();
}

void Imf_2_5_M33fAttribute_TypedAttribute_1(
    Imf_2_5_M33fAttribute * this_
    , Imath_2_5_M33f const * value)
{
    new (this_) Imf_2_5::TypedAttribute<Imath::M33f>(to_cpp_ref(value));
}

void Imf_2_5_M33fAttribute_dtor(
    Imf_2_5_M33fAttribute * this_)
{
    (to_cpp(this_)) -> Imf_2_5::TypedAttribute<Imath_2_5::Matrix33<float> >::~TypedAttribute();
}

Imath_2_5_M33f * Imf_2_5_M33fAttribute_value(
    Imf_2_5_M33fAttribute * this_)
{
    return to_c((to_cpp(this_)) -> value());
}

Imath_2_5_M33f const * Imf_2_5_M33fAttribute_value_1(
    Imf_2_5_M33fAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> value());
}

char const * Imf_2_5_M33dAttribute_typeName(
    Imf_2_5_M33dAttribute const * this_)
{
    return (to_cpp(this_)) -> typeName();
}

Imf_2_5_Attribute * Imf_2_5_M33dAttribute_copy(
    Imf_2_5_M33dAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> copy());
}

void Imf_2_5_M33dAttribute_writeValueTo(
    Imf_2_5_M33dAttribute const * this_
    , Imf_2_5_OStream * os
    , int version)
{
    (to_cpp(this_)) -> writeValueTo(to_cpp_ref(os), version);
}

void Imf_2_5_M33dAttribute_readValueFrom(
    Imf_2_5_M33dAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version)
{
    (to_cpp(this_)) -> readValueFrom(to_cpp_ref(is), size, version);
}

void Imf_2_5_M33dAttribute_copyValueFrom(
    Imf_2_5_M33dAttribute * this_
    , Imf_2_5_Attribute const * other)
{
    (to_cpp(this_)) -> copyValueFrom(to_cpp_ref(other));
}

void Imf_2_5_M33dAttribute_TypedAttribute(
    Imf_2_5_M33dAttribute * this_)
{
    new (this_) Imf_2_5::TypedAttribute<Imath::M33d>();
}

void Imf_2_5_M33dAttribute_TypedAttribute_1(
    Imf_2_5_M33dAttribute * this_
    , Imath_2_5_M33d const * value)
{
    new (this_) Imf_2_5::TypedAttribute<Imath::M33d>(to_cpp_ref(value));
}

void Imf_2_5_M33dAttribute_dtor(
    Imf_2_5_M33dAttribute * this_)
{
    (to_cpp(this_)) -> Imf_2_5::TypedAttribute<Imath_2_5::Matrix33<double> >::~TypedAttribute();
}

Imath_2_5_M33d * Imf_2_5_M33dAttribute_value(
    Imf_2_5_M33dAttribute * this_)
{
    return to_c((to_cpp(this_)) -> value());
}

Imath_2_5_M33d const * Imf_2_5_M33dAttribute_value_1(
    Imf_2_5_M33dAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> value());
}

char const * Imf_2_5_M44fAttribute_typeName(
    Imf_2_5_M44fAttribute const * this_)
{
    return (to_cpp(this_)) -> typeName();
}

Imf_2_5_Attribute * Imf_2_5_M44fAttribute_copy(
    Imf_2_5_M44fAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> copy());
}

void Imf_2_5_M44fAttribute_writeValueTo(
    Imf_2_5_M44fAttribute const * this_
    , Imf_2_5_OStream * os
    , int version)
{
    (to_cpp(this_)) -> writeValueTo(to_cpp_ref(os), version);
}

void Imf_2_5_M44fAttribute_readValueFrom(
    Imf_2_5_M44fAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version)
{
    (to_cpp(this_)) -> readValueFrom(to_cpp_ref(is), size, version);
}

void Imf_2_5_M44fAttribute_copyValueFrom(
    Imf_2_5_M44fAttribute * this_
    , Imf_2_5_Attribute const * other)
{
    (to_cpp(this_)) -> copyValueFrom(to_cpp_ref(other));
}

void Imf_2_5_M44fAttribute_TypedAttribute(
    Imf_2_5_M44fAttribute * this_)
{
    new (this_) Imf_2_5::TypedAttribute<Imath::M44f>();
}

void Imf_2_5_M44fAttribute_TypedAttribute_1(
    Imf_2_5_M44fAttribute * this_
    , Imath_2_5_M44f const * value)
{
    new (this_) Imf_2_5::TypedAttribute<Imath::M44f>(to_cpp_ref(value));
}

void Imf_2_5_M44fAttribute_dtor(
    Imf_2_5_M44fAttribute * this_)
{
    (to_cpp(this_)) -> Imf_2_5::TypedAttribute<Imath_2_5::Matrix44<float> >::~TypedAttribute();
}

Imath_2_5_M44f * Imf_2_5_M44fAttribute_value(
    Imf_2_5_M44fAttribute * this_)
{
    return to_c((to_cpp(this_)) -> value());
}

Imath_2_5_M44f const * Imf_2_5_M44fAttribute_value_1(
    Imf_2_5_M44fAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> value());
}

char const * Imf_2_5_M44dAttribute_typeName(
    Imf_2_5_M44dAttribute const * this_)
{
    return (to_cpp(this_)) -> typeName();
}

Imf_2_5_Attribute * Imf_2_5_M44dAttribute_copy(
    Imf_2_5_M44dAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> copy());
}

void Imf_2_5_M44dAttribute_writeValueTo(
    Imf_2_5_M44dAttribute const * this_
    , Imf_2_5_OStream * os
    , int version)
{
    (to_cpp(this_)) -> writeValueTo(to_cpp_ref(os), version);
}

void Imf_2_5_M44dAttribute_readValueFrom(
    Imf_2_5_M44dAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version)
{
    (to_cpp(this_)) -> readValueFrom(to_cpp_ref(is), size, version);
}

void Imf_2_5_M44dAttribute_copyValueFrom(
    Imf_2_5_M44dAttribute * this_
    , Imf_2_5_Attribute const * other)
{
    (to_cpp(this_)) -> copyValueFrom(to_cpp_ref(other));
}

void Imf_2_5_M44dAttribute_TypedAttribute(
    Imf_2_5_M44dAttribute * this_)
{
    new (this_) Imf_2_5::TypedAttribute<Imath::M44d>();
}

void Imf_2_5_M44dAttribute_TypedAttribute_1(
    Imf_2_5_M44dAttribute * this_
    , Imath_2_5_M44d const * value)
{
    new (this_) Imf_2_5::TypedAttribute<Imath::M44d>(to_cpp_ref(value));
}

void Imf_2_5_M44dAttribute_dtor(
    Imf_2_5_M44dAttribute * this_)
{
    (to_cpp(this_)) -> Imf_2_5::TypedAttribute<Imath_2_5::Matrix44<double> >::~TypedAttribute();
}

Imath_2_5_M44d * Imf_2_5_M44dAttribute_value(
    Imf_2_5_M44dAttribute * this_)
{
    return to_c((to_cpp(this_)) -> value());
}

Imath_2_5_M44d const * Imf_2_5_M44dAttribute_value_1(
    Imf_2_5_M44dAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> value());
}

char const * Imf_2_5_PreviewImageAttribute_typeName(
    Imf_2_5_PreviewImageAttribute const * this_)
{
    return (to_cpp(this_)) -> typeName();
}

Imf_2_5_Attribute * Imf_2_5_PreviewImageAttribute_copy(
    Imf_2_5_PreviewImageAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> copy());
}

void Imf_2_5_PreviewImageAttribute_writeValueTo(
    Imf_2_5_PreviewImageAttribute const * this_
    , Imf_2_5_OStream * os
    , int version)
{
    (to_cpp(this_)) -> writeValueTo(to_cpp_ref(os), version);
}

void Imf_2_5_PreviewImageAttribute_readValueFrom(
    Imf_2_5_PreviewImageAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version)
{
    (to_cpp(this_)) -> readValueFrom(to_cpp_ref(is), size, version);
}

void Imf_2_5_PreviewImageAttribute_copyValueFrom(
    Imf_2_5_PreviewImageAttribute * this_
    , Imf_2_5_Attribute const * other)
{
    (to_cpp(this_)) -> copyValueFrom(to_cpp_ref(other));
}

void Imf_2_5_PreviewImageAttribute_TypedAttribute(
    Imf_2_5_PreviewImageAttribute * this_)
{
    new (this_) Imf_2_5::TypedAttribute<Imf::PreviewImage>();
}

void Imf_2_5_PreviewImageAttribute_TypedAttribute_1(
    Imf_2_5_PreviewImageAttribute * this_
    , Imf_2_5_PreviewImage const * value)
{
    new (this_) Imf_2_5::TypedAttribute<Imf::PreviewImage>(to_cpp_ref(value));
}

void Imf_2_5_PreviewImageAttribute_dtor(
    Imf_2_5_PreviewImageAttribute * this_)
{
    (to_cpp(this_)) -> Imf_2_5::TypedAttribute<Imf_2_5::PreviewImage>::~TypedAttribute();
}

Imf_2_5_PreviewImage * Imf_2_5_PreviewImageAttribute_value(
    Imf_2_5_PreviewImageAttribute * this_)
{
    return to_c((to_cpp(this_)) -> value());
}

Imf_2_5_PreviewImage const * Imf_2_5_PreviewImageAttribute_value_1(
    Imf_2_5_PreviewImageAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> value());
}

char const * Imf_2_5_RationalAttribute_typeName(
    Imf_2_5_RationalAttribute const * this_)
{
    return (to_cpp(this_)) -> typeName();
}

Imf_2_5_Attribute * Imf_2_5_RationalAttribute_copy(
    Imf_2_5_RationalAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> copy());
}

void Imf_2_5_RationalAttribute_writeValueTo(
    Imf_2_5_RationalAttribute const * this_
    , Imf_2_5_OStream * os
    , int version)
{
    (to_cpp(this_)) -> writeValueTo(to_cpp_ref(os), version);
}

void Imf_2_5_RationalAttribute_readValueFrom(
    Imf_2_5_RationalAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version)
{
    (to_cpp(this_)) -> readValueFrom(to_cpp_ref(is), size, version);
}

void Imf_2_5_RationalAttribute_copyValueFrom(
    Imf_2_5_RationalAttribute * this_
    , Imf_2_5_Attribute const * other)
{
    (to_cpp(this_)) -> copyValueFrom(to_cpp_ref(other));
}

void Imf_2_5_RationalAttribute_TypedAttribute(
    Imf_2_5_RationalAttribute * this_)
{
    new (this_) Imf_2_5::TypedAttribute<Imf::Rational>();
}

void Imf_2_5_RationalAttribute_TypedAttribute_1(
    Imf_2_5_RationalAttribute * this_
    , Imf_2_5_Rational const * value)
{
    new (this_) Imf_2_5::TypedAttribute<Imf::Rational>(to_cpp_ref(value));
}

void Imf_2_5_RationalAttribute_dtor(
    Imf_2_5_RationalAttribute * this_)
{
    (to_cpp(this_)) -> Imf_2_5::TypedAttribute<Imf_2_5::Rational>::~TypedAttribute();
}

Imf_2_5_Rational * Imf_2_5_RationalAttribute_value(
    Imf_2_5_RationalAttribute * this_)
{
    return to_c((to_cpp(this_)) -> value());
}

Imf_2_5_Rational const * Imf_2_5_RationalAttribute_value_1(
    Imf_2_5_RationalAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> value());
}

char const * Imf_2_5_TileDescriptionAttribute_typeName(
    Imf_2_5_TileDescriptionAttribute const * this_)
{
    return (to_cpp(this_)) -> typeName();
}

Imf_2_5_Attribute * Imf_2_5_TileDescriptionAttribute_copy(
    Imf_2_5_TileDescriptionAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> copy());
}

void Imf_2_5_TileDescriptionAttribute_writeValueTo(
    Imf_2_5_TileDescriptionAttribute const * this_
    , Imf_2_5_OStream * os
    , int version)
{
    (to_cpp(this_)) -> writeValueTo(to_cpp_ref(os), version);
}

void Imf_2_5_TileDescriptionAttribute_readValueFrom(
    Imf_2_5_TileDescriptionAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version)
{
    (to_cpp(this_)) -> readValueFrom(to_cpp_ref(is), size, version);
}

void Imf_2_5_TileDescriptionAttribute_copyValueFrom(
    Imf_2_5_TileDescriptionAttribute * this_
    , Imf_2_5_Attribute const * other)
{
    (to_cpp(this_)) -> copyValueFrom(to_cpp_ref(other));
}

void Imf_2_5_TileDescriptionAttribute_TypedAttribute(
    Imf_2_5_TileDescriptionAttribute * this_)
{
    new (this_) Imf_2_5::TypedAttribute<Imf::TileDescription>();
}

void Imf_2_5_TileDescriptionAttribute_TypedAttribute_1(
    Imf_2_5_TileDescriptionAttribute * this_
    , Imf_2_5_TileDescription const * value)
{
    new (this_) Imf_2_5::TypedAttribute<Imf::TileDescription>(to_cpp_ref(value));
}

void Imf_2_5_TileDescriptionAttribute_dtor(
    Imf_2_5_TileDescriptionAttribute * this_)
{
    (to_cpp(this_)) -> Imf_2_5::TypedAttribute<Imf_2_5::TileDescription>::~TypedAttribute();
}

Imf_2_5_TileDescription * Imf_2_5_TileDescriptionAttribute_value(
    Imf_2_5_TileDescriptionAttribute * this_)
{
    return to_c((to_cpp(this_)) -> value());
}

Imf_2_5_TileDescription const * Imf_2_5_TileDescriptionAttribute_value_1(
    Imf_2_5_TileDescriptionAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> value());
}

char const * Imf_2_5_TimeCodeAttribute_typeName(
    Imf_2_5_TimeCodeAttribute const * this_)
{
    return (to_cpp(this_)) -> typeName();
}

Imf_2_5_Attribute * Imf_2_5_TimeCodeAttribute_copy(
    Imf_2_5_TimeCodeAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> copy());
}

void Imf_2_5_TimeCodeAttribute_writeValueTo(
    Imf_2_5_TimeCodeAttribute const * this_
    , Imf_2_5_OStream * os
    , int version)
{
    (to_cpp(this_)) -> writeValueTo(to_cpp_ref(os), version);
}

void Imf_2_5_TimeCodeAttribute_readValueFrom(
    Imf_2_5_TimeCodeAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version)
{
    (to_cpp(this_)) -> readValueFrom(to_cpp_ref(is), size, version);
}

void Imf_2_5_TimeCodeAttribute_copyValueFrom(
    Imf_2_5_TimeCodeAttribute * this_
    , Imf_2_5_Attribute const * other)
{
    (to_cpp(this_)) -> copyValueFrom(to_cpp_ref(other));
}

void Imf_2_5_TimeCodeAttribute_TypedAttribute(
    Imf_2_5_TimeCodeAttribute * this_)
{
    new (this_) Imf_2_5::TypedAttribute<Imf::TimeCode>();
}

void Imf_2_5_TimeCodeAttribute_TypedAttribute_1(
    Imf_2_5_TimeCodeAttribute * this_
    , Imf_2_5_TimeCode const * value)
{
    new (this_) Imf_2_5::TypedAttribute<Imf::TimeCode>(to_cpp_ref(value));
}

void Imf_2_5_TimeCodeAttribute_dtor(
    Imf_2_5_TimeCodeAttribute * this_)
{
    (to_cpp(this_)) -> Imf_2_5::TypedAttribute<Imf_2_5::TimeCode>::~TypedAttribute();
}

Imf_2_5_TimeCode * Imf_2_5_TimeCodeAttribute_value(
    Imf_2_5_TimeCodeAttribute * this_)
{
    return to_c((to_cpp(this_)) -> value());
}

Imf_2_5_TimeCode const * Imf_2_5_TimeCodeAttribute_value_1(
    Imf_2_5_TimeCodeAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> value());
}

char const * Imf_2_5_V2iAttribute_typeName(
    Imf_2_5_V2iAttribute const * this_)
{
    return (to_cpp(this_)) -> typeName();
}

Imf_2_5_Attribute * Imf_2_5_V2iAttribute_copy(
    Imf_2_5_V2iAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> copy());
}

void Imf_2_5_V2iAttribute_writeValueTo(
    Imf_2_5_V2iAttribute const * this_
    , Imf_2_5_OStream * os
    , int version)
{
    (to_cpp(this_)) -> writeValueTo(to_cpp_ref(os), version);
}

void Imf_2_5_V2iAttribute_readValueFrom(
    Imf_2_5_V2iAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version)
{
    (to_cpp(this_)) -> readValueFrom(to_cpp_ref(is), size, version);
}

void Imf_2_5_V2iAttribute_copyValueFrom(
    Imf_2_5_V2iAttribute * this_
    , Imf_2_5_Attribute const * other)
{
    (to_cpp(this_)) -> copyValueFrom(to_cpp_ref(other));
}

void Imf_2_5_V2iAttribute_TypedAttribute(
    Imf_2_5_V2iAttribute * this_)
{
    new (this_) Imf_2_5::TypedAttribute<Imath::V2i>();
}

void Imf_2_5_V2iAttribute_TypedAttribute_1(
    Imf_2_5_V2iAttribute * this_
    , Imath_2_5_V2i const * value)
{
    new (this_) Imf_2_5::TypedAttribute<Imath::V2i>(to_cpp_ref(value));
}

void Imf_2_5_V2iAttribute_dtor(
    Imf_2_5_V2iAttribute * this_)
{
    (to_cpp(this_)) -> Imf_2_5::TypedAttribute<Imath_2_5::Vec2<int> >::~TypedAttribute();
}

Imath_2_5_V2i * Imf_2_5_V2iAttribute_value(
    Imf_2_5_V2iAttribute * this_)
{
    return to_c((to_cpp(this_)) -> value());
}

Imath_2_5_V2i const * Imf_2_5_V2iAttribute_value_1(
    Imf_2_5_V2iAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> value());
}

char const * Imf_2_5_V2fAttribute_typeName(
    Imf_2_5_V2fAttribute const * this_)
{
    return (to_cpp(this_)) -> typeName();
}

Imf_2_5_Attribute * Imf_2_5_V2fAttribute_copy(
    Imf_2_5_V2fAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> copy());
}

void Imf_2_5_V2fAttribute_writeValueTo(
    Imf_2_5_V2fAttribute const * this_
    , Imf_2_5_OStream * os
    , int version)
{
    (to_cpp(this_)) -> writeValueTo(to_cpp_ref(os), version);
}

void Imf_2_5_V2fAttribute_readValueFrom(
    Imf_2_5_V2fAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version)
{
    (to_cpp(this_)) -> readValueFrom(to_cpp_ref(is), size, version);
}

void Imf_2_5_V2fAttribute_copyValueFrom(
    Imf_2_5_V2fAttribute * this_
    , Imf_2_5_Attribute const * other)
{
    (to_cpp(this_)) -> copyValueFrom(to_cpp_ref(other));
}

void Imf_2_5_V2fAttribute_TypedAttribute(
    Imf_2_5_V2fAttribute * this_)
{
    new (this_) Imf_2_5::TypedAttribute<Imath::V2f>();
}

void Imf_2_5_V2fAttribute_TypedAttribute_1(
    Imf_2_5_V2fAttribute * this_
    , Imath_2_5_V2f const * value)
{
    new (this_) Imf_2_5::TypedAttribute<Imath::V2f>(to_cpp_ref(value));
}

void Imf_2_5_V2fAttribute_dtor(
    Imf_2_5_V2fAttribute * this_)
{
    (to_cpp(this_)) -> Imf_2_5::TypedAttribute<Imath_2_5::Vec2<float> >::~TypedAttribute();
}

Imath_2_5_V2f * Imf_2_5_V2fAttribute_value(
    Imf_2_5_V2fAttribute * this_)
{
    return to_c((to_cpp(this_)) -> value());
}

Imath_2_5_V2f const * Imf_2_5_V2fAttribute_value_1(
    Imf_2_5_V2fAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> value());
}

char const * Imf_2_5_V2dAttribute_typeName(
    Imf_2_5_V2dAttribute const * this_)
{
    return (to_cpp(this_)) -> typeName();
}

Imf_2_5_Attribute * Imf_2_5_V2dAttribute_copy(
    Imf_2_5_V2dAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> copy());
}

void Imf_2_5_V2dAttribute_writeValueTo(
    Imf_2_5_V2dAttribute const * this_
    , Imf_2_5_OStream * os
    , int version)
{
    (to_cpp(this_)) -> writeValueTo(to_cpp_ref(os), version);
}

void Imf_2_5_V2dAttribute_readValueFrom(
    Imf_2_5_V2dAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version)
{
    (to_cpp(this_)) -> readValueFrom(to_cpp_ref(is), size, version);
}

void Imf_2_5_V2dAttribute_copyValueFrom(
    Imf_2_5_V2dAttribute * this_
    , Imf_2_5_Attribute const * other)
{
    (to_cpp(this_)) -> copyValueFrom(to_cpp_ref(other));
}

void Imf_2_5_V2dAttribute_TypedAttribute(
    Imf_2_5_V2dAttribute * this_)
{
    new (this_) Imf_2_5::TypedAttribute<Imath::V2d>();
}

void Imf_2_5_V2dAttribute_TypedAttribute_1(
    Imf_2_5_V2dAttribute * this_
    , Imath_2_5_V2d const * value)
{
    new (this_) Imf_2_5::TypedAttribute<Imath::V2d>(to_cpp_ref(value));
}

void Imf_2_5_V2dAttribute_dtor(
    Imf_2_5_V2dAttribute * this_)
{
    (to_cpp(this_)) -> Imf_2_5::TypedAttribute<Imath_2_5::Vec2<double> >::~TypedAttribute();
}

Imath_2_5_V2d * Imf_2_5_V2dAttribute_value(
    Imf_2_5_V2dAttribute * this_)
{
    return to_c((to_cpp(this_)) -> value());
}

Imath_2_5_V2d const * Imf_2_5_V2dAttribute_value_1(
    Imf_2_5_V2dAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> value());
}

char const * Imf_2_5_V3iAttribute_typeName(
    Imf_2_5_V3iAttribute const * this_)
{
    return (to_cpp(this_)) -> typeName();
}

Imf_2_5_Attribute * Imf_2_5_V3iAttribute_copy(
    Imf_2_5_V3iAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> copy());
}

void Imf_2_5_V3iAttribute_writeValueTo(
    Imf_2_5_V3iAttribute const * this_
    , Imf_2_5_OStream * os
    , int version)
{
    (to_cpp(this_)) -> writeValueTo(to_cpp_ref(os), version);
}

void Imf_2_5_V3iAttribute_readValueFrom(
    Imf_2_5_V3iAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version)
{
    (to_cpp(this_)) -> readValueFrom(to_cpp_ref(is), size, version);
}

void Imf_2_5_V3iAttribute_copyValueFrom(
    Imf_2_5_V3iAttribute * this_
    , Imf_2_5_Attribute const * other)
{
    (to_cpp(this_)) -> copyValueFrom(to_cpp_ref(other));
}

void Imf_2_5_V3iAttribute_TypedAttribute(
    Imf_2_5_V3iAttribute * this_)
{
    new (this_) Imf_2_5::TypedAttribute<Imath::V3i>();
}

void Imf_2_5_V3iAttribute_TypedAttribute_1(
    Imf_2_5_V3iAttribute * this_
    , Imath_2_5_V3i const * value)
{
    new (this_) Imf_2_5::TypedAttribute<Imath::V3i>(to_cpp_ref(value));
}

void Imf_2_5_V3iAttribute_dtor(
    Imf_2_5_V3iAttribute * this_)
{
    (to_cpp(this_)) -> Imf_2_5::TypedAttribute<Imath_2_5::Vec3<int> >::~TypedAttribute();
}

Imath_2_5_V3i * Imf_2_5_V3iAttribute_value(
    Imf_2_5_V3iAttribute * this_)
{
    return to_c((to_cpp(this_)) -> value());
}

Imath_2_5_V3i const * Imf_2_5_V3iAttribute_value_1(
    Imf_2_5_V3iAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> value());
}

char const * Imf_2_5_V3fAttribute_typeName(
    Imf_2_5_V3fAttribute const * this_)
{
    return (to_cpp(this_)) -> typeName();
}

Imf_2_5_Attribute * Imf_2_5_V3fAttribute_copy(
    Imf_2_5_V3fAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> copy());
}

void Imf_2_5_V3fAttribute_writeValueTo(
    Imf_2_5_V3fAttribute const * this_
    , Imf_2_5_OStream * os
    , int version)
{
    (to_cpp(this_)) -> writeValueTo(to_cpp_ref(os), version);
}

void Imf_2_5_V3fAttribute_readValueFrom(
    Imf_2_5_V3fAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version)
{
    (to_cpp(this_)) -> readValueFrom(to_cpp_ref(is), size, version);
}

void Imf_2_5_V3fAttribute_copyValueFrom(
    Imf_2_5_V3fAttribute * this_
    , Imf_2_5_Attribute const * other)
{
    (to_cpp(this_)) -> copyValueFrom(to_cpp_ref(other));
}

void Imf_2_5_V3fAttribute_TypedAttribute(
    Imf_2_5_V3fAttribute * this_)
{
    new (this_) Imf_2_5::TypedAttribute<Imath::V3f>();
}

void Imf_2_5_V3fAttribute_TypedAttribute_1(
    Imf_2_5_V3fAttribute * this_
    , Imath_2_5_V3f const * value)
{
    new (this_) Imf_2_5::TypedAttribute<Imath::V3f>(to_cpp_ref(value));
}

void Imf_2_5_V3fAttribute_dtor(
    Imf_2_5_V3fAttribute * this_)
{
    (to_cpp(this_)) -> Imf_2_5::TypedAttribute<Imath_2_5::Vec3<float> >::~TypedAttribute();
}

Imath_2_5_V3f * Imf_2_5_V3fAttribute_value(
    Imf_2_5_V3fAttribute * this_)
{
    return to_c((to_cpp(this_)) -> value());
}

Imath_2_5_V3f const * Imf_2_5_V3fAttribute_value_1(
    Imf_2_5_V3fAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> value());
}

char const * Imf_2_5_V3dAttribute_typeName(
    Imf_2_5_V3dAttribute const * this_)
{
    return (to_cpp(this_)) -> typeName();
}

Imf_2_5_Attribute * Imf_2_5_V3dAttribute_copy(
    Imf_2_5_V3dAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> copy());
}

void Imf_2_5_V3dAttribute_writeValueTo(
    Imf_2_5_V3dAttribute const * this_
    , Imf_2_5_OStream * os
    , int version)
{
    (to_cpp(this_)) -> writeValueTo(to_cpp_ref(os), version);
}

void Imf_2_5_V3dAttribute_readValueFrom(
    Imf_2_5_V3dAttribute * this_
    , Imf_2_5_IStream * is
    , int size
    , int version)
{
    (to_cpp(this_)) -> readValueFrom(to_cpp_ref(is), size, version);
}

void Imf_2_5_V3dAttribute_copyValueFrom(
    Imf_2_5_V3dAttribute * this_
    , Imf_2_5_Attribute const * other)
{
    (to_cpp(this_)) -> copyValueFrom(to_cpp_ref(other));
}

void Imf_2_5_V3dAttribute_TypedAttribute(
    Imf_2_5_V3dAttribute * this_)
{
    new (this_) Imf_2_5::TypedAttribute<Imath::V3d>();
}

void Imf_2_5_V3dAttribute_TypedAttribute_1(
    Imf_2_5_V3dAttribute * this_
    , Imath_2_5_V3d const * value)
{
    new (this_) Imf_2_5::TypedAttribute<Imath::V3d>(to_cpp_ref(value));
}

void Imf_2_5_V3dAttribute_dtor(
    Imf_2_5_V3dAttribute * this_)
{
    (to_cpp(this_)) -> Imf_2_5::TypedAttribute<Imath_2_5::Vec3<double> >::~TypedAttribute();
}

Imath_2_5_V3d * Imf_2_5_V3dAttribute_value(
    Imf_2_5_V3dAttribute * this_)
{
    return to_c((to_cpp(this_)) -> value());
}

Imath_2_5_V3d const * Imf_2_5_V3dAttribute_value_1(
    Imf_2_5_V3dAttribute const * this_)
{
    return to_c((to_cpp(this_)) -> value());
}
