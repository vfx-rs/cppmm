#include <OpenEXR/ImfRgbaYca.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

namespace RgbaYca {
static const int N = 27;
static const int N2 = N / 2;

IMF_EXPORT
IMATH_NAMESPACE::V3f computeYw(const Imf::Chromaticities& cr);

IMF_EXPORT
void RGBAtoYCA(const IMATH_NAMESPACE::V3f& yw, int n, bool aIsValid,
               const Imf::Rgba rgbaIn[/*n*/], Imf::Rgba ycaOut[/*n*/]);

IMF_EXPORT
void decimateChromaHoriz(int n, const Imf::Rgba ycaIn[/*n+N-1*/],
                         Imf::Rgba ycaOut[/*n*/]);

IMF_EXPORT
void decimateChromaVert(int n, const Imf::Rgba* const ycaIn[N],
                        Imf::Rgba ycaOut[/*n*/]);

IMF_EXPORT
void roundYCA(int n, unsigned int roundY, unsigned int roundC,
              const Imf::Rgba ycaIn[/*n*/], Imf::Rgba ycaOut[/*n*/]);

IMF_EXPORT
void reconstructChromaHoriz(int n, const Imf::Rgba ycaIn[/*n+N-1*/],
                            Imf::Rgba ycaOut[/*n*/]);

IMF_EXPORT
void reconstructChromaVert(int n, const Imf::Rgba* const ycaIn[N],
                           Imf::Rgba ycaOut[/*n*/]);

IMF_EXPORT
void YCAtoRGBA(const IMATH_NAMESPACE::V3f& yw, int n,
               const Imf::Rgba ycaIn[/*n*/], Imf::Rgba rgbaOut[/*n*/]);

IMF_EXPORT
void fixSaturation(const IMATH_NAMESPACE::V3f& yw, int n,
                   const Imf::Rgba* const rgbaIn[3], Imf::Rgba rgbaOut[/*n*/]);
} // namespace RgbaYca

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
