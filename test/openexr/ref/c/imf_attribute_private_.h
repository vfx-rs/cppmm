#pragma once
#include <imf_attribute_.h>


#include <OpenEXR/ImfAttribute.h>
#include <OpenEXR/ImfBoxAttribute.h>
#include <OpenEXR/ImfChannelListAttribute.h>
#include <OpenEXR/ImfChromaticitiesAttribute.h>
#include <OpenEXR/ImfCompressionAttribute.h>
#include <OpenEXR/ImfDeepImageStateAttribute.h>
#include <OpenEXR/ImfEnvmapAttribute.h>
#include <OpenEXR/ImfFloatVectorAttribute.h>
#include <OpenEXR/ImfKeyCodeAttribute.h>
#include <OpenEXR/ImfLineOrderAttribute.h>
#include <OpenEXR/ImfMatrixAttribute.h>
#include <OpenEXR/ImfPreviewImageAttribute.h>
#include <OpenEXR/ImfRationalAttribute.h>
#include <OpenEXR/ImfStringAttribute.h>
#include <OpenEXR/ImfStringVectorAttribute.h>
#include <OpenEXR/ImfTileDescriptionAttribute.h>
#include <OpenEXR/ImfTimeCodeAttribute.h>
#include <OpenEXR/ImfVecAttribute.h>
#include <cppmm_bind.hpp>
#include <vector>








inline Imf_2_5::Attribute const & to_cpp_ref(
    Imf_2_5_Attribute const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::Attribute const * >(rhs));
}


inline Imf_2_5::Attribute & to_cpp_ref(
    Imf_2_5_Attribute * rhs)
{
    return *(reinterpret_cast<Imf_2_5::Attribute * >(rhs));
}


inline Imf_2_5::Attribute const * to_cpp(
    Imf_2_5_Attribute const * rhs)
{
    return reinterpret_cast<Imf_2_5::Attribute const * >(rhs);
}


inline Imf_2_5::Attribute * to_cpp(
    Imf_2_5_Attribute * rhs)
{
    return reinterpret_cast<Imf_2_5::Attribute * >(rhs);
}


inline Imf_2_5_Attribute const * to_c(
    Imf_2_5::Attribute const & rhs)
{
    return reinterpret_cast<Imf_2_5_Attribute const * >(&(rhs));
}


inline Imf_2_5_Attribute const * to_c(
    Imf_2_5::Attribute const * rhs)
{
    return reinterpret_cast<Imf_2_5_Attribute const * >(rhs);
}


inline Imf_2_5_Attribute * to_c(
    Imf_2_5::Attribute & rhs)
{
    return reinterpret_cast<Imf_2_5_Attribute * >(&(rhs));
}


inline Imf_2_5_Attribute * to_c(
    Imf_2_5::Attribute * rhs)
{
    return reinterpret_cast<Imf_2_5_Attribute * >(rhs);
}












inline Imf_2_5::TypedAttribute<int> const & to_cpp_ref(
    Imf_2_5_IntAttribute const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<int> const * >(rhs));
}


inline Imf_2_5::TypedAttribute<int> & to_cpp_ref(
    Imf_2_5_IntAttribute * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<int> * >(rhs));
}


inline Imf_2_5::TypedAttribute<int> const * to_cpp(
    Imf_2_5_IntAttribute const * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<int> const * >(rhs);
}


inline Imf_2_5::TypedAttribute<int> * to_cpp(
    Imf_2_5_IntAttribute * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<int> * >(rhs);
}


inline Imf_2_5_IntAttribute const * to_c(
    Imf_2_5::TypedAttribute<int> const & rhs)
{
    return reinterpret_cast<Imf_2_5_IntAttribute const * >(&(rhs));
}


inline Imf_2_5_IntAttribute const * to_c(
    Imf_2_5::TypedAttribute<int> const * rhs)
{
    return reinterpret_cast<Imf_2_5_IntAttribute const * >(rhs);
}


inline Imf_2_5_IntAttribute * to_c(
    Imf_2_5::TypedAttribute<int> & rhs)
{
    return reinterpret_cast<Imf_2_5_IntAttribute * >(&(rhs));
}


inline Imf_2_5_IntAttribute * to_c(
    Imf_2_5::TypedAttribute<int> * rhs)
{
    return reinterpret_cast<Imf_2_5_IntAttribute * >(rhs);
}












inline Imf_2_5::TypedAttribute<float> const & to_cpp_ref(
    Imf_2_5_FloatAttribute const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<float> const * >(rhs));
}


inline Imf_2_5::TypedAttribute<float> & to_cpp_ref(
    Imf_2_5_FloatAttribute * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<float> * >(rhs));
}


inline Imf_2_5::TypedAttribute<float> const * to_cpp(
    Imf_2_5_FloatAttribute const * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<float> const * >(rhs);
}


inline Imf_2_5::TypedAttribute<float> * to_cpp(
    Imf_2_5_FloatAttribute * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<float> * >(rhs);
}


inline Imf_2_5_FloatAttribute const * to_c(
    Imf_2_5::TypedAttribute<float> const & rhs)
{
    return reinterpret_cast<Imf_2_5_FloatAttribute const * >(&(rhs));
}


inline Imf_2_5_FloatAttribute const * to_c(
    Imf_2_5::TypedAttribute<float> const * rhs)
{
    return reinterpret_cast<Imf_2_5_FloatAttribute const * >(rhs);
}


inline Imf_2_5_FloatAttribute * to_c(
    Imf_2_5::TypedAttribute<float> & rhs)
{
    return reinterpret_cast<Imf_2_5_FloatAttribute * >(&(rhs));
}


inline Imf_2_5_FloatAttribute * to_c(
    Imf_2_5::TypedAttribute<float> * rhs)
{
    return reinterpret_cast<Imf_2_5_FloatAttribute * >(rhs);
}












inline Imf_2_5::TypedAttribute<double> const & to_cpp_ref(
    Imf_2_5_DoubleAttribute const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<double> const * >(rhs));
}


inline Imf_2_5::TypedAttribute<double> & to_cpp_ref(
    Imf_2_5_DoubleAttribute * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<double> * >(rhs));
}


inline Imf_2_5::TypedAttribute<double> const * to_cpp(
    Imf_2_5_DoubleAttribute const * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<double> const * >(rhs);
}


inline Imf_2_5::TypedAttribute<double> * to_cpp(
    Imf_2_5_DoubleAttribute * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<double> * >(rhs);
}


inline Imf_2_5_DoubleAttribute const * to_c(
    Imf_2_5::TypedAttribute<double> const & rhs)
{
    return reinterpret_cast<Imf_2_5_DoubleAttribute const * >(&(rhs));
}


inline Imf_2_5_DoubleAttribute const * to_c(
    Imf_2_5::TypedAttribute<double> const * rhs)
{
    return reinterpret_cast<Imf_2_5_DoubleAttribute const * >(rhs);
}


inline Imf_2_5_DoubleAttribute * to_c(
    Imf_2_5::TypedAttribute<double> & rhs)
{
    return reinterpret_cast<Imf_2_5_DoubleAttribute * >(&(rhs));
}


inline Imf_2_5_DoubleAttribute * to_c(
    Imf_2_5::TypedAttribute<double> * rhs)
{
    return reinterpret_cast<Imf_2_5_DoubleAttribute * >(rhs);
}












inline Imf_2_5::TypedAttribute<Imath::Box2i> const & to_cpp_ref(
    Imf_2_5_Box2iAttribute const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imath::Box2i> const * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imath::Box2i> & to_cpp_ref(
    Imf_2_5_Box2iAttribute * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imath::Box2i> * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imath::Box2i> const * to_cpp(
    Imf_2_5_Box2iAttribute const * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imath::Box2i> const * >(rhs);
}


inline Imf_2_5::TypedAttribute<Imath::Box2i> * to_cpp(
    Imf_2_5_Box2iAttribute * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imath::Box2i> * >(rhs);
}


inline Imf_2_5_Box2iAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imath::Box2i> const & rhs)
{
    return reinterpret_cast<Imf_2_5_Box2iAttribute const * >(&(rhs));
}


inline Imf_2_5_Box2iAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imath::Box2i> const * rhs)
{
    return reinterpret_cast<Imf_2_5_Box2iAttribute const * >(rhs);
}


inline Imf_2_5_Box2iAttribute * to_c(
    Imf_2_5::TypedAttribute<Imath::Box2i> & rhs)
{
    return reinterpret_cast<Imf_2_5_Box2iAttribute * >(&(rhs));
}


inline Imf_2_5_Box2iAttribute * to_c(
    Imf_2_5::TypedAttribute<Imath::Box2i> * rhs)
{
    return reinterpret_cast<Imf_2_5_Box2iAttribute * >(rhs);
}












inline Imf_2_5::TypedAttribute<Imath::Box2f> const & to_cpp_ref(
    Imf_2_5_Box2fAttribute const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imath::Box2f> const * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imath::Box2f> & to_cpp_ref(
    Imf_2_5_Box2fAttribute * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imath::Box2f> * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imath::Box2f> const * to_cpp(
    Imf_2_5_Box2fAttribute const * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imath::Box2f> const * >(rhs);
}


inline Imf_2_5::TypedAttribute<Imath::Box2f> * to_cpp(
    Imf_2_5_Box2fAttribute * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imath::Box2f> * >(rhs);
}


inline Imf_2_5_Box2fAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imath::Box2f> const & rhs)
{
    return reinterpret_cast<Imf_2_5_Box2fAttribute const * >(&(rhs));
}


inline Imf_2_5_Box2fAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imath::Box2f> const * rhs)
{
    return reinterpret_cast<Imf_2_5_Box2fAttribute const * >(rhs);
}


inline Imf_2_5_Box2fAttribute * to_c(
    Imf_2_5::TypedAttribute<Imath::Box2f> & rhs)
{
    return reinterpret_cast<Imf_2_5_Box2fAttribute * >(&(rhs));
}


inline Imf_2_5_Box2fAttribute * to_c(
    Imf_2_5::TypedAttribute<Imath::Box2f> * rhs)
{
    return reinterpret_cast<Imf_2_5_Box2fAttribute * >(rhs);
}












inline Imf_2_5::TypedAttribute<Imf::ChannelList> const & to_cpp_ref(
    Imf_2_5_ChannelListAttribute const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imf::ChannelList> const * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imf::ChannelList> & to_cpp_ref(
    Imf_2_5_ChannelListAttribute * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imf::ChannelList> * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imf::ChannelList> const * to_cpp(
    Imf_2_5_ChannelListAttribute const * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imf::ChannelList> const * >(rhs);
}


inline Imf_2_5::TypedAttribute<Imf::ChannelList> * to_cpp(
    Imf_2_5_ChannelListAttribute * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imf::ChannelList> * >(rhs);
}


inline Imf_2_5_ChannelListAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imf::ChannelList> const & rhs)
{
    return reinterpret_cast<Imf_2_5_ChannelListAttribute const * >(&(rhs));
}


inline Imf_2_5_ChannelListAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imf::ChannelList> const * rhs)
{
    return reinterpret_cast<Imf_2_5_ChannelListAttribute const * >(rhs);
}


inline Imf_2_5_ChannelListAttribute * to_c(
    Imf_2_5::TypedAttribute<Imf::ChannelList> & rhs)
{
    return reinterpret_cast<Imf_2_5_ChannelListAttribute * >(&(rhs));
}


inline Imf_2_5_ChannelListAttribute * to_c(
    Imf_2_5::TypedAttribute<Imf::ChannelList> * rhs)
{
    return reinterpret_cast<Imf_2_5_ChannelListAttribute * >(rhs);
}












inline Imf_2_5::TypedAttribute<Imf::Chromaticities> const & to_cpp_ref(
    Imf_2_5_ChromaticitiesAttribute const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imf::Chromaticities> const * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imf::Chromaticities> & to_cpp_ref(
    Imf_2_5_ChromaticitiesAttribute * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imf::Chromaticities> * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imf::Chromaticities> const * to_cpp(
    Imf_2_5_ChromaticitiesAttribute const * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imf::Chromaticities> const * >(rhs);
}


inline Imf_2_5::TypedAttribute<Imf::Chromaticities> * to_cpp(
    Imf_2_5_ChromaticitiesAttribute * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imf::Chromaticities> * >(rhs);
}


inline Imf_2_5_ChromaticitiesAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imf::Chromaticities> const & rhs)
{
    return reinterpret_cast<Imf_2_5_ChromaticitiesAttribute const * >(&(rhs));
}


inline Imf_2_5_ChromaticitiesAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imf::Chromaticities> const * rhs)
{
    return reinterpret_cast<Imf_2_5_ChromaticitiesAttribute const * >(rhs);
}


inline Imf_2_5_ChromaticitiesAttribute * to_c(
    Imf_2_5::TypedAttribute<Imf::Chromaticities> & rhs)
{
    return reinterpret_cast<Imf_2_5_ChromaticitiesAttribute * >(&(rhs));
}


inline Imf_2_5_ChromaticitiesAttribute * to_c(
    Imf_2_5::TypedAttribute<Imf::Chromaticities> * rhs)
{
    return reinterpret_cast<Imf_2_5_ChromaticitiesAttribute * >(rhs);
}









inline Imf_2_5::TypedAttribute<Imf::Compression> const & to_cpp_ref(
    Imf_2_5_CompressionAttribute const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imf::Compression> const * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imf::Compression> & to_cpp_ref(
    Imf_2_5_CompressionAttribute * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imf::Compression> * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imf::Compression> const * to_cpp(
    Imf_2_5_CompressionAttribute const * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imf::Compression> const * >(rhs);
}


inline Imf_2_5::TypedAttribute<Imf::Compression> * to_cpp(
    Imf_2_5_CompressionAttribute * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imf::Compression> * >(rhs);
}


inline Imf_2_5_CompressionAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imf::Compression> const & rhs)
{
    return reinterpret_cast<Imf_2_5_CompressionAttribute const * >(&(rhs));
}


inline Imf_2_5_CompressionAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imf::Compression> const * rhs)
{
    return reinterpret_cast<Imf_2_5_CompressionAttribute const * >(rhs);
}


inline Imf_2_5_CompressionAttribute * to_c(
    Imf_2_5::TypedAttribute<Imf::Compression> & rhs)
{
    return reinterpret_cast<Imf_2_5_CompressionAttribute * >(&(rhs));
}


inline Imf_2_5_CompressionAttribute * to_c(
    Imf_2_5::TypedAttribute<Imf::Compression> * rhs)
{
    return reinterpret_cast<Imf_2_5_CompressionAttribute * >(rhs);
}









inline Imf_2_5::TypedAttribute<Imf::DeepImageState> const & to_cpp_ref(
    Imf_2_5_DeepImageStateAttribute const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imf::DeepImageState> const * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imf::DeepImageState> & to_cpp_ref(
    Imf_2_5_DeepImageStateAttribute * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imf::DeepImageState> * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imf::DeepImageState> const * to_cpp(
    Imf_2_5_DeepImageStateAttribute const * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imf::DeepImageState> const * >(rhs);
}


inline Imf_2_5::TypedAttribute<Imf::DeepImageState> * to_cpp(
    Imf_2_5_DeepImageStateAttribute * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imf::DeepImageState> * >(rhs);
}


inline Imf_2_5_DeepImageStateAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imf::DeepImageState> const & rhs)
{
    return reinterpret_cast<Imf_2_5_DeepImageStateAttribute const * >(&(rhs));
}


inline Imf_2_5_DeepImageStateAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imf::DeepImageState> const * rhs)
{
    return reinterpret_cast<Imf_2_5_DeepImageStateAttribute const * >(rhs);
}


inline Imf_2_5_DeepImageStateAttribute * to_c(
    Imf_2_5::TypedAttribute<Imf::DeepImageState> & rhs)
{
    return reinterpret_cast<Imf_2_5_DeepImageStateAttribute * >(&(rhs));
}


inline Imf_2_5_DeepImageStateAttribute * to_c(
    Imf_2_5::TypedAttribute<Imf::DeepImageState> * rhs)
{
    return reinterpret_cast<Imf_2_5_DeepImageStateAttribute * >(rhs);
}









inline Imf_2_5::TypedAttribute<Imf::Envmap> const & to_cpp_ref(
    Imf_2_5_EnvmapAttribute const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imf::Envmap> const * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imf::Envmap> & to_cpp_ref(
    Imf_2_5_EnvmapAttribute * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imf::Envmap> * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imf::Envmap> const * to_cpp(
    Imf_2_5_EnvmapAttribute const * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imf::Envmap> const * >(rhs);
}


inline Imf_2_5::TypedAttribute<Imf::Envmap> * to_cpp(
    Imf_2_5_EnvmapAttribute * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imf::Envmap> * >(rhs);
}


inline Imf_2_5_EnvmapAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imf::Envmap> const & rhs)
{
    return reinterpret_cast<Imf_2_5_EnvmapAttribute const * >(&(rhs));
}


inline Imf_2_5_EnvmapAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imf::Envmap> const * rhs)
{
    return reinterpret_cast<Imf_2_5_EnvmapAttribute const * >(rhs);
}


inline Imf_2_5_EnvmapAttribute * to_c(
    Imf_2_5::TypedAttribute<Imf::Envmap> & rhs)
{
    return reinterpret_cast<Imf_2_5_EnvmapAttribute * >(&(rhs));
}


inline Imf_2_5_EnvmapAttribute * to_c(
    Imf_2_5::TypedAttribute<Imf::Envmap> * rhs)
{
    return reinterpret_cast<Imf_2_5_EnvmapAttribute * >(rhs);
}












inline Imf_2_5::TypedAttribute<std::vector<float> > const & to_cpp_ref(
    Imf_2_5_FloatVectorAttribute const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<std::vector<float> > const * >(rhs));
}


inline Imf_2_5::TypedAttribute<std::vector<float> > & to_cpp_ref(
    Imf_2_5_FloatVectorAttribute * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<std::vector<float> > * >(rhs));
}


inline Imf_2_5::TypedAttribute<std::vector<float> > const * to_cpp(
    Imf_2_5_FloatVectorAttribute const * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<std::vector<float> > const * >(rhs);
}


inline Imf_2_5::TypedAttribute<std::vector<float> > * to_cpp(
    Imf_2_5_FloatVectorAttribute * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<std::vector<float> > * >(rhs);
}


inline Imf_2_5_FloatVectorAttribute const * to_c(
    Imf_2_5::TypedAttribute<std::vector<float> > const & rhs)
{
    return reinterpret_cast<Imf_2_5_FloatVectorAttribute const * >(&(rhs));
}


inline Imf_2_5_FloatVectorAttribute const * to_c(
    Imf_2_5::TypedAttribute<std::vector<float> > const * rhs)
{
    return reinterpret_cast<Imf_2_5_FloatVectorAttribute const * >(rhs);
}


inline Imf_2_5_FloatVectorAttribute * to_c(
    Imf_2_5::TypedAttribute<std::vector<float> > & rhs)
{
    return reinterpret_cast<Imf_2_5_FloatVectorAttribute * >(&(rhs));
}


inline Imf_2_5_FloatVectorAttribute * to_c(
    Imf_2_5::TypedAttribute<std::vector<float> > * rhs)
{
    return reinterpret_cast<Imf_2_5_FloatVectorAttribute * >(rhs);
}









inline Imf_2_5::TypedAttribute<std::vector<std::string> > const & to_cpp_ref(
    Imf_2_5_StringVectorAttribute const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<std::vector<std::string> > const * >(rhs));
}


inline Imf_2_5::TypedAttribute<std::vector<std::string> > & to_cpp_ref(
    Imf_2_5_StringVectorAttribute * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<std::vector<std::string> > * >(rhs));
}


inline Imf_2_5::TypedAttribute<std::vector<std::string> > const * to_cpp(
    Imf_2_5_StringVectorAttribute const * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<std::vector<std::string> > const * >(rhs);
}


inline Imf_2_5::TypedAttribute<std::vector<std::string> > * to_cpp(
    Imf_2_5_StringVectorAttribute * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<std::vector<std::string> > * >(rhs);
}


inline Imf_2_5_StringVectorAttribute const * to_c(
    Imf_2_5::TypedAttribute<std::vector<std::string> > const & rhs)
{
    return reinterpret_cast<Imf_2_5_StringVectorAttribute const * >(&(rhs));
}


inline Imf_2_5_StringVectorAttribute const * to_c(
    Imf_2_5::TypedAttribute<std::vector<std::string> > const * rhs)
{
    return reinterpret_cast<Imf_2_5_StringVectorAttribute const * >(rhs);
}


inline Imf_2_5_StringVectorAttribute * to_c(
    Imf_2_5::TypedAttribute<std::vector<std::string> > & rhs)
{
    return reinterpret_cast<Imf_2_5_StringVectorAttribute * >(&(rhs));
}


inline Imf_2_5_StringVectorAttribute * to_c(
    Imf_2_5::TypedAttribute<std::vector<std::string> > * rhs)
{
    return reinterpret_cast<Imf_2_5_StringVectorAttribute * >(rhs);
}









inline Imf_2_5::TypedAttribute<std::string> const & to_cpp_ref(
    Imf_2_5_StringAttribute const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<std::string> const * >(rhs));
}


inline Imf_2_5::TypedAttribute<std::string> & to_cpp_ref(
    Imf_2_5_StringAttribute * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<std::string> * >(rhs));
}


inline Imf_2_5::TypedAttribute<std::string> const * to_cpp(
    Imf_2_5_StringAttribute const * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<std::string> const * >(rhs);
}


inline Imf_2_5::TypedAttribute<std::string> * to_cpp(
    Imf_2_5_StringAttribute * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<std::string> * >(rhs);
}


inline Imf_2_5_StringAttribute const * to_c(
    Imf_2_5::TypedAttribute<std::string> const & rhs)
{
    return reinterpret_cast<Imf_2_5_StringAttribute const * >(&(rhs));
}


inline Imf_2_5_StringAttribute const * to_c(
    Imf_2_5::TypedAttribute<std::string> const * rhs)
{
    return reinterpret_cast<Imf_2_5_StringAttribute const * >(rhs);
}


inline Imf_2_5_StringAttribute * to_c(
    Imf_2_5::TypedAttribute<std::string> & rhs)
{
    return reinterpret_cast<Imf_2_5_StringAttribute * >(&(rhs));
}


inline Imf_2_5_StringAttribute * to_c(
    Imf_2_5::TypedAttribute<std::string> * rhs)
{
    return reinterpret_cast<Imf_2_5_StringAttribute * >(rhs);
}












inline Imf_2_5::TypedAttribute<Imf::KeyCode> const & to_cpp_ref(
    Imf_2_5_KeyCodeAttribute const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imf::KeyCode> const * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imf::KeyCode> & to_cpp_ref(
    Imf_2_5_KeyCodeAttribute * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imf::KeyCode> * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imf::KeyCode> const * to_cpp(
    Imf_2_5_KeyCodeAttribute const * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imf::KeyCode> const * >(rhs);
}


inline Imf_2_5::TypedAttribute<Imf::KeyCode> * to_cpp(
    Imf_2_5_KeyCodeAttribute * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imf::KeyCode> * >(rhs);
}


inline Imf_2_5_KeyCodeAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imf::KeyCode> const & rhs)
{
    return reinterpret_cast<Imf_2_5_KeyCodeAttribute const * >(&(rhs));
}


inline Imf_2_5_KeyCodeAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imf::KeyCode> const * rhs)
{
    return reinterpret_cast<Imf_2_5_KeyCodeAttribute const * >(rhs);
}


inline Imf_2_5_KeyCodeAttribute * to_c(
    Imf_2_5::TypedAttribute<Imf::KeyCode> & rhs)
{
    return reinterpret_cast<Imf_2_5_KeyCodeAttribute * >(&(rhs));
}


inline Imf_2_5_KeyCodeAttribute * to_c(
    Imf_2_5::TypedAttribute<Imf::KeyCode> * rhs)
{
    return reinterpret_cast<Imf_2_5_KeyCodeAttribute * >(rhs);
}









inline Imf_2_5::TypedAttribute<Imf::LineOrder> const & to_cpp_ref(
    Imf_2_5_LineOrderAttribute const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imf::LineOrder> const * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imf::LineOrder> & to_cpp_ref(
    Imf_2_5_LineOrderAttribute * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imf::LineOrder> * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imf::LineOrder> const * to_cpp(
    Imf_2_5_LineOrderAttribute const * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imf::LineOrder> const * >(rhs);
}


inline Imf_2_5::TypedAttribute<Imf::LineOrder> * to_cpp(
    Imf_2_5_LineOrderAttribute * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imf::LineOrder> * >(rhs);
}


inline Imf_2_5_LineOrderAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imf::LineOrder> const & rhs)
{
    return reinterpret_cast<Imf_2_5_LineOrderAttribute const * >(&(rhs));
}


inline Imf_2_5_LineOrderAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imf::LineOrder> const * rhs)
{
    return reinterpret_cast<Imf_2_5_LineOrderAttribute const * >(rhs);
}


inline Imf_2_5_LineOrderAttribute * to_c(
    Imf_2_5::TypedAttribute<Imf::LineOrder> & rhs)
{
    return reinterpret_cast<Imf_2_5_LineOrderAttribute * >(&(rhs));
}


inline Imf_2_5_LineOrderAttribute * to_c(
    Imf_2_5::TypedAttribute<Imf::LineOrder> * rhs)
{
    return reinterpret_cast<Imf_2_5_LineOrderAttribute * >(rhs);
}












inline Imf_2_5::TypedAttribute<Imath::M33f> const & to_cpp_ref(
    Imf_2_5_M33fAttribute const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imath::M33f> const * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imath::M33f> & to_cpp_ref(
    Imf_2_5_M33fAttribute * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imath::M33f> * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imath::M33f> const * to_cpp(
    Imf_2_5_M33fAttribute const * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imath::M33f> const * >(rhs);
}


inline Imf_2_5::TypedAttribute<Imath::M33f> * to_cpp(
    Imf_2_5_M33fAttribute * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imath::M33f> * >(rhs);
}


inline Imf_2_5_M33fAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imath::M33f> const & rhs)
{
    return reinterpret_cast<Imf_2_5_M33fAttribute const * >(&(rhs));
}


inline Imf_2_5_M33fAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imath::M33f> const * rhs)
{
    return reinterpret_cast<Imf_2_5_M33fAttribute const * >(rhs);
}


inline Imf_2_5_M33fAttribute * to_c(
    Imf_2_5::TypedAttribute<Imath::M33f> & rhs)
{
    return reinterpret_cast<Imf_2_5_M33fAttribute * >(&(rhs));
}


inline Imf_2_5_M33fAttribute * to_c(
    Imf_2_5::TypedAttribute<Imath::M33f> * rhs)
{
    return reinterpret_cast<Imf_2_5_M33fAttribute * >(rhs);
}












inline Imf_2_5::TypedAttribute<Imath::M33d> const & to_cpp_ref(
    Imf_2_5_M33dAttribute const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imath::M33d> const * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imath::M33d> & to_cpp_ref(
    Imf_2_5_M33dAttribute * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imath::M33d> * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imath::M33d> const * to_cpp(
    Imf_2_5_M33dAttribute const * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imath::M33d> const * >(rhs);
}


inline Imf_2_5::TypedAttribute<Imath::M33d> * to_cpp(
    Imf_2_5_M33dAttribute * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imath::M33d> * >(rhs);
}


inline Imf_2_5_M33dAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imath::M33d> const & rhs)
{
    return reinterpret_cast<Imf_2_5_M33dAttribute const * >(&(rhs));
}


inline Imf_2_5_M33dAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imath::M33d> const * rhs)
{
    return reinterpret_cast<Imf_2_5_M33dAttribute const * >(rhs);
}


inline Imf_2_5_M33dAttribute * to_c(
    Imf_2_5::TypedAttribute<Imath::M33d> & rhs)
{
    return reinterpret_cast<Imf_2_5_M33dAttribute * >(&(rhs));
}


inline Imf_2_5_M33dAttribute * to_c(
    Imf_2_5::TypedAttribute<Imath::M33d> * rhs)
{
    return reinterpret_cast<Imf_2_5_M33dAttribute * >(rhs);
}












inline Imf_2_5::TypedAttribute<Imath::M44f> const & to_cpp_ref(
    Imf_2_5_M44fAttribute const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imath::M44f> const * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imath::M44f> & to_cpp_ref(
    Imf_2_5_M44fAttribute * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imath::M44f> * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imath::M44f> const * to_cpp(
    Imf_2_5_M44fAttribute const * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imath::M44f> const * >(rhs);
}


inline Imf_2_5::TypedAttribute<Imath::M44f> * to_cpp(
    Imf_2_5_M44fAttribute * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imath::M44f> * >(rhs);
}


inline Imf_2_5_M44fAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imath::M44f> const & rhs)
{
    return reinterpret_cast<Imf_2_5_M44fAttribute const * >(&(rhs));
}


inline Imf_2_5_M44fAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imath::M44f> const * rhs)
{
    return reinterpret_cast<Imf_2_5_M44fAttribute const * >(rhs);
}


inline Imf_2_5_M44fAttribute * to_c(
    Imf_2_5::TypedAttribute<Imath::M44f> & rhs)
{
    return reinterpret_cast<Imf_2_5_M44fAttribute * >(&(rhs));
}


inline Imf_2_5_M44fAttribute * to_c(
    Imf_2_5::TypedAttribute<Imath::M44f> * rhs)
{
    return reinterpret_cast<Imf_2_5_M44fAttribute * >(rhs);
}












inline Imf_2_5::TypedAttribute<Imath::M44d> const & to_cpp_ref(
    Imf_2_5_M44dAttribute const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imath::M44d> const * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imath::M44d> & to_cpp_ref(
    Imf_2_5_M44dAttribute * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imath::M44d> * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imath::M44d> const * to_cpp(
    Imf_2_5_M44dAttribute const * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imath::M44d> const * >(rhs);
}


inline Imf_2_5::TypedAttribute<Imath::M44d> * to_cpp(
    Imf_2_5_M44dAttribute * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imath::M44d> * >(rhs);
}


inline Imf_2_5_M44dAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imath::M44d> const & rhs)
{
    return reinterpret_cast<Imf_2_5_M44dAttribute const * >(&(rhs));
}


inline Imf_2_5_M44dAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imath::M44d> const * rhs)
{
    return reinterpret_cast<Imf_2_5_M44dAttribute const * >(rhs);
}


inline Imf_2_5_M44dAttribute * to_c(
    Imf_2_5::TypedAttribute<Imath::M44d> & rhs)
{
    return reinterpret_cast<Imf_2_5_M44dAttribute * >(&(rhs));
}


inline Imf_2_5_M44dAttribute * to_c(
    Imf_2_5::TypedAttribute<Imath::M44d> * rhs)
{
    return reinterpret_cast<Imf_2_5_M44dAttribute * >(rhs);
}












inline Imf_2_5::TypedAttribute<Imf::PreviewImage> const & to_cpp_ref(
    Imf_2_5_PreviewImageAttribute const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imf::PreviewImage> const * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imf::PreviewImage> & to_cpp_ref(
    Imf_2_5_PreviewImageAttribute * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imf::PreviewImage> * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imf::PreviewImage> const * to_cpp(
    Imf_2_5_PreviewImageAttribute const * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imf::PreviewImage> const * >(rhs);
}


inline Imf_2_5::TypedAttribute<Imf::PreviewImage> * to_cpp(
    Imf_2_5_PreviewImageAttribute * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imf::PreviewImage> * >(rhs);
}


inline Imf_2_5_PreviewImageAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imf::PreviewImage> const & rhs)
{
    return reinterpret_cast<Imf_2_5_PreviewImageAttribute const * >(&(rhs));
}


inline Imf_2_5_PreviewImageAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imf::PreviewImage> const * rhs)
{
    return reinterpret_cast<Imf_2_5_PreviewImageAttribute const * >(rhs);
}


inline Imf_2_5_PreviewImageAttribute * to_c(
    Imf_2_5::TypedAttribute<Imf::PreviewImage> & rhs)
{
    return reinterpret_cast<Imf_2_5_PreviewImageAttribute * >(&(rhs));
}


inline Imf_2_5_PreviewImageAttribute * to_c(
    Imf_2_5::TypedAttribute<Imf::PreviewImage> * rhs)
{
    return reinterpret_cast<Imf_2_5_PreviewImageAttribute * >(rhs);
}












inline Imf_2_5::TypedAttribute<Imf::Rational> const & to_cpp_ref(
    Imf_2_5_RationalAttribute const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imf::Rational> const * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imf::Rational> & to_cpp_ref(
    Imf_2_5_RationalAttribute * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imf::Rational> * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imf::Rational> const * to_cpp(
    Imf_2_5_RationalAttribute const * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imf::Rational> const * >(rhs);
}


inline Imf_2_5::TypedAttribute<Imf::Rational> * to_cpp(
    Imf_2_5_RationalAttribute * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imf::Rational> * >(rhs);
}


inline Imf_2_5_RationalAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imf::Rational> const & rhs)
{
    return reinterpret_cast<Imf_2_5_RationalAttribute const * >(&(rhs));
}


inline Imf_2_5_RationalAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imf::Rational> const * rhs)
{
    return reinterpret_cast<Imf_2_5_RationalAttribute const * >(rhs);
}


inline Imf_2_5_RationalAttribute * to_c(
    Imf_2_5::TypedAttribute<Imf::Rational> & rhs)
{
    return reinterpret_cast<Imf_2_5_RationalAttribute * >(&(rhs));
}


inline Imf_2_5_RationalAttribute * to_c(
    Imf_2_5::TypedAttribute<Imf::Rational> * rhs)
{
    return reinterpret_cast<Imf_2_5_RationalAttribute * >(rhs);
}












inline Imf_2_5::TypedAttribute<Imf::TileDescription> const & to_cpp_ref(
    Imf_2_5_TileDescriptionAttribute const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imf::TileDescription> const * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imf::TileDescription> & to_cpp_ref(
    Imf_2_5_TileDescriptionAttribute * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imf::TileDescription> * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imf::TileDescription> const * to_cpp(
    Imf_2_5_TileDescriptionAttribute const * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imf::TileDescription> const * >(rhs);
}


inline Imf_2_5::TypedAttribute<Imf::TileDescription> * to_cpp(
    Imf_2_5_TileDescriptionAttribute * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imf::TileDescription> * >(rhs);
}


inline Imf_2_5_TileDescriptionAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imf::TileDescription> const & rhs)
{
    return reinterpret_cast<Imf_2_5_TileDescriptionAttribute const * >(&(rhs));
}


inline Imf_2_5_TileDescriptionAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imf::TileDescription> const * rhs)
{
    return reinterpret_cast<Imf_2_5_TileDescriptionAttribute const * >(rhs);
}


inline Imf_2_5_TileDescriptionAttribute * to_c(
    Imf_2_5::TypedAttribute<Imf::TileDescription> & rhs)
{
    return reinterpret_cast<Imf_2_5_TileDescriptionAttribute * >(&(rhs));
}


inline Imf_2_5_TileDescriptionAttribute * to_c(
    Imf_2_5::TypedAttribute<Imf::TileDescription> * rhs)
{
    return reinterpret_cast<Imf_2_5_TileDescriptionAttribute * >(rhs);
}












inline Imf_2_5::TypedAttribute<Imf::TimeCode> const & to_cpp_ref(
    Imf_2_5_TimeCodeAttribute const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imf::TimeCode> const * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imf::TimeCode> & to_cpp_ref(
    Imf_2_5_TimeCodeAttribute * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imf::TimeCode> * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imf::TimeCode> const * to_cpp(
    Imf_2_5_TimeCodeAttribute const * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imf::TimeCode> const * >(rhs);
}


inline Imf_2_5::TypedAttribute<Imf::TimeCode> * to_cpp(
    Imf_2_5_TimeCodeAttribute * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imf::TimeCode> * >(rhs);
}


inline Imf_2_5_TimeCodeAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imf::TimeCode> const & rhs)
{
    return reinterpret_cast<Imf_2_5_TimeCodeAttribute const * >(&(rhs));
}


inline Imf_2_5_TimeCodeAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imf::TimeCode> const * rhs)
{
    return reinterpret_cast<Imf_2_5_TimeCodeAttribute const * >(rhs);
}


inline Imf_2_5_TimeCodeAttribute * to_c(
    Imf_2_5::TypedAttribute<Imf::TimeCode> & rhs)
{
    return reinterpret_cast<Imf_2_5_TimeCodeAttribute * >(&(rhs));
}


inline Imf_2_5_TimeCodeAttribute * to_c(
    Imf_2_5::TypedAttribute<Imf::TimeCode> * rhs)
{
    return reinterpret_cast<Imf_2_5_TimeCodeAttribute * >(rhs);
}












inline Imf_2_5::TypedAttribute<Imath::V2i> const & to_cpp_ref(
    Imf_2_5_V2iAttribute const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imath::V2i> const * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imath::V2i> & to_cpp_ref(
    Imf_2_5_V2iAttribute * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imath::V2i> * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imath::V2i> const * to_cpp(
    Imf_2_5_V2iAttribute const * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imath::V2i> const * >(rhs);
}


inline Imf_2_5::TypedAttribute<Imath::V2i> * to_cpp(
    Imf_2_5_V2iAttribute * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imath::V2i> * >(rhs);
}


inline Imf_2_5_V2iAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imath::V2i> const & rhs)
{
    return reinterpret_cast<Imf_2_5_V2iAttribute const * >(&(rhs));
}


inline Imf_2_5_V2iAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imath::V2i> const * rhs)
{
    return reinterpret_cast<Imf_2_5_V2iAttribute const * >(rhs);
}


inline Imf_2_5_V2iAttribute * to_c(
    Imf_2_5::TypedAttribute<Imath::V2i> & rhs)
{
    return reinterpret_cast<Imf_2_5_V2iAttribute * >(&(rhs));
}


inline Imf_2_5_V2iAttribute * to_c(
    Imf_2_5::TypedAttribute<Imath::V2i> * rhs)
{
    return reinterpret_cast<Imf_2_5_V2iAttribute * >(rhs);
}












inline Imf_2_5::TypedAttribute<Imath::V2f> const & to_cpp_ref(
    Imf_2_5_V2fAttribute const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imath::V2f> const * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imath::V2f> & to_cpp_ref(
    Imf_2_5_V2fAttribute * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imath::V2f> * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imath::V2f> const * to_cpp(
    Imf_2_5_V2fAttribute const * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imath::V2f> const * >(rhs);
}


inline Imf_2_5::TypedAttribute<Imath::V2f> * to_cpp(
    Imf_2_5_V2fAttribute * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imath::V2f> * >(rhs);
}


inline Imf_2_5_V2fAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imath::V2f> const & rhs)
{
    return reinterpret_cast<Imf_2_5_V2fAttribute const * >(&(rhs));
}


inline Imf_2_5_V2fAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imath::V2f> const * rhs)
{
    return reinterpret_cast<Imf_2_5_V2fAttribute const * >(rhs);
}


inline Imf_2_5_V2fAttribute * to_c(
    Imf_2_5::TypedAttribute<Imath::V2f> & rhs)
{
    return reinterpret_cast<Imf_2_5_V2fAttribute * >(&(rhs));
}


inline Imf_2_5_V2fAttribute * to_c(
    Imf_2_5::TypedAttribute<Imath::V2f> * rhs)
{
    return reinterpret_cast<Imf_2_5_V2fAttribute * >(rhs);
}












inline Imf_2_5::TypedAttribute<Imath::V2d> const & to_cpp_ref(
    Imf_2_5_V2dAttribute const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imath::V2d> const * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imath::V2d> & to_cpp_ref(
    Imf_2_5_V2dAttribute * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imath::V2d> * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imath::V2d> const * to_cpp(
    Imf_2_5_V2dAttribute const * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imath::V2d> const * >(rhs);
}


inline Imf_2_5::TypedAttribute<Imath::V2d> * to_cpp(
    Imf_2_5_V2dAttribute * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imath::V2d> * >(rhs);
}


inline Imf_2_5_V2dAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imath::V2d> const & rhs)
{
    return reinterpret_cast<Imf_2_5_V2dAttribute const * >(&(rhs));
}


inline Imf_2_5_V2dAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imath::V2d> const * rhs)
{
    return reinterpret_cast<Imf_2_5_V2dAttribute const * >(rhs);
}


inline Imf_2_5_V2dAttribute * to_c(
    Imf_2_5::TypedAttribute<Imath::V2d> & rhs)
{
    return reinterpret_cast<Imf_2_5_V2dAttribute * >(&(rhs));
}


inline Imf_2_5_V2dAttribute * to_c(
    Imf_2_5::TypedAttribute<Imath::V2d> * rhs)
{
    return reinterpret_cast<Imf_2_5_V2dAttribute * >(rhs);
}












inline Imf_2_5::TypedAttribute<Imath::V3i> const & to_cpp_ref(
    Imf_2_5_V3iAttribute const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imath::V3i> const * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imath::V3i> & to_cpp_ref(
    Imf_2_5_V3iAttribute * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imath::V3i> * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imath::V3i> const * to_cpp(
    Imf_2_5_V3iAttribute const * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imath::V3i> const * >(rhs);
}


inline Imf_2_5::TypedAttribute<Imath::V3i> * to_cpp(
    Imf_2_5_V3iAttribute * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imath::V3i> * >(rhs);
}


inline Imf_2_5_V3iAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imath::V3i> const & rhs)
{
    return reinterpret_cast<Imf_2_5_V3iAttribute const * >(&(rhs));
}


inline Imf_2_5_V3iAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imath::V3i> const * rhs)
{
    return reinterpret_cast<Imf_2_5_V3iAttribute const * >(rhs);
}


inline Imf_2_5_V3iAttribute * to_c(
    Imf_2_5::TypedAttribute<Imath::V3i> & rhs)
{
    return reinterpret_cast<Imf_2_5_V3iAttribute * >(&(rhs));
}


inline Imf_2_5_V3iAttribute * to_c(
    Imf_2_5::TypedAttribute<Imath::V3i> * rhs)
{
    return reinterpret_cast<Imf_2_5_V3iAttribute * >(rhs);
}












inline Imf_2_5::TypedAttribute<Imath::V3f> const & to_cpp_ref(
    Imf_2_5_V3fAttribute const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imath::V3f> const * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imath::V3f> & to_cpp_ref(
    Imf_2_5_V3fAttribute * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imath::V3f> * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imath::V3f> const * to_cpp(
    Imf_2_5_V3fAttribute const * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imath::V3f> const * >(rhs);
}


inline Imf_2_5::TypedAttribute<Imath::V3f> * to_cpp(
    Imf_2_5_V3fAttribute * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imath::V3f> * >(rhs);
}


inline Imf_2_5_V3fAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imath::V3f> const & rhs)
{
    return reinterpret_cast<Imf_2_5_V3fAttribute const * >(&(rhs));
}


inline Imf_2_5_V3fAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imath::V3f> const * rhs)
{
    return reinterpret_cast<Imf_2_5_V3fAttribute const * >(rhs);
}


inline Imf_2_5_V3fAttribute * to_c(
    Imf_2_5::TypedAttribute<Imath::V3f> & rhs)
{
    return reinterpret_cast<Imf_2_5_V3fAttribute * >(&(rhs));
}


inline Imf_2_5_V3fAttribute * to_c(
    Imf_2_5::TypedAttribute<Imath::V3f> * rhs)
{
    return reinterpret_cast<Imf_2_5_V3fAttribute * >(rhs);
}












inline Imf_2_5::TypedAttribute<Imath::V3d> const & to_cpp_ref(
    Imf_2_5_V3dAttribute const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imath::V3d> const * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imath::V3d> & to_cpp_ref(
    Imf_2_5_V3dAttribute * rhs)
{
    return *(reinterpret_cast<Imf_2_5::TypedAttribute<Imath::V3d> * >(rhs));
}


inline Imf_2_5::TypedAttribute<Imath::V3d> const * to_cpp(
    Imf_2_5_V3dAttribute const * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imath::V3d> const * >(rhs);
}


inline Imf_2_5::TypedAttribute<Imath::V3d> * to_cpp(
    Imf_2_5_V3dAttribute * rhs)
{
    return reinterpret_cast<Imf_2_5::TypedAttribute<Imath::V3d> * >(rhs);
}


inline Imf_2_5_V3dAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imath::V3d> const & rhs)
{
    return reinterpret_cast<Imf_2_5_V3dAttribute const * >(&(rhs));
}


inline Imf_2_5_V3dAttribute const * to_c(
    Imf_2_5::TypedAttribute<Imath::V3d> const * rhs)
{
    return reinterpret_cast<Imf_2_5_V3dAttribute const * >(rhs);
}


inline Imf_2_5_V3dAttribute * to_c(
    Imf_2_5::TypedAttribute<Imath::V3d> & rhs)
{
    return reinterpret_cast<Imf_2_5_V3dAttribute * >(&(rhs));
}


inline Imf_2_5_V3dAttribute * to_c(
    Imf_2_5::TypedAttribute<Imath::V3d> * rhs)
{
    return reinterpret_cast<Imf_2_5_V3dAttribute * >(rhs);
}


inline std::vector<float> const & to_cpp_ref(
    std_vector const * rhs)
{
    return *(reinterpret_cast<std::vector<float> const * >(rhs));
}


inline std::vector<float> & to_cpp_ref(
    std_vector * rhs)
{
    return *(reinterpret_cast<std::vector<float> * >(rhs));
}


inline std::vector<float> const * to_cpp(
    std_vector const * rhs)
{
    return reinterpret_cast<std::vector<float> const * >(rhs);
}


inline std::vector<float> * to_cpp(
    std_vector * rhs)
{
    return reinterpret_cast<std::vector<float> * >(rhs);
}


inline std_vector const * to_c(
    std::vector<float> const & rhs)
{
    return reinterpret_cast<std_vector const * >(&(rhs));
}


inline std_vector const * to_c(
    std::vector<float> const * rhs)
{
    return reinterpret_cast<std_vector const * >(rhs);
}


inline std_vector * to_c(
    std::vector<float> & rhs)
{
    return reinterpret_cast<std_vector * >(&(rhs));
}


inline std_vector * to_c(
    std::vector<float> * rhs)
{
    return reinterpret_cast<std_vector * >(rhs);
}
