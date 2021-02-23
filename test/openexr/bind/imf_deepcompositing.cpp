#include <OpenEXR/ImfDeepCompositing.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

struct DeepCompositing {
    using BoundType = Imf::DeepCompositing;
    IMF_EXPORT
    DeepCompositing();
    IMF_EXPORT
    virtual ~DeepCompositing();

    IMF_EXPORT
    virtual void composite_pixel(float outputs[], const float* inputs[],
                                 const char* channel_names[], int num_channels,
                                 int num_samples, int sources);

    IMF_EXPORT
    virtual void sort(int order[], const float* inputs[],
                      const char* channel_names[], int num_channels,
                      int num_samples, int sources);
} CPPMM_OPAQUEBYTES;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
