#include <OpenEXR/ImfEnvmap.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

enum Envmap {};
enum CubeMapFace {};

namespace LatLongMap {
IMF_EXPORT
IMATH_NAMESPACE::V2f latLong(const IMATH_NAMESPACE::V3f& direction);

IMF_EXPORT
IMATH_NAMESPACE::V2f latLong(const IMATH_NAMESPACE::Box2i& dataWindow,
                             const IMATH_NAMESPACE::V2f& pixelPosition)
    CPPMM_RENAME(latLong_pixel_position);

IMF_EXPORT
IMATH_NAMESPACE::V2f pixelPosition(const IMATH_NAMESPACE::Box2i& dataWindow,
                                   const IMATH_NAMESPACE::V2f& latLong)
    CPPMM_RENAME(pixelPosition_latlong);

IMF_EXPORT
IMATH_NAMESPACE::V2f pixelPosition(const IMATH_NAMESPACE::Box2i& dataWindow,
                                   const IMATH_NAMESPACE::V3f& direction);

IMF_EXPORT
IMATH_NAMESPACE::V3f direction(const IMATH_NAMESPACE::Box2i& dataWindow,
                               const IMATH_NAMESPACE::V2f& pixelPosition);
} // namespace LatLongMap

namespace CubeMap {
IMF_EXPORT
int sizeOfFace(const IMATH_NAMESPACE::Box2i& dataWindow);

IMF_EXPORT
IMATH_NAMESPACE::Box2i
dataWindowForFace(Imf::CubeMapFace face,
                  const IMATH_NAMESPACE::Box2i& dataWindow);

IMF_EXPORT
IMATH_NAMESPACE::V2f pixelPosition(Imf::CubeMapFace face,
                                   const IMATH_NAMESPACE::Box2i& dataWindow,
                                   IMATH_NAMESPACE::V2f positionInFace);

IMF_EXPORT
void faceAndPixelPosition(const IMATH_NAMESPACE::V3f& direction,
                          const IMATH_NAMESPACE::Box2i& dataWindow,
                          Imf::CubeMapFace& face,
                          IMATH_NAMESPACE::V2f& positionInFace);

IMF_EXPORT
IMATH_NAMESPACE::V3f direction(Imf::CubeMapFace face,
                               const IMATH_NAMESPACE::Box2i& dataWindow,
                               const IMATH_NAMESPACE::V2f& positionInFace);
} // namespace CubeMap
} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
