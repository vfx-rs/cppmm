#include <OpenEXR/ImfCompositeDeepScanLine.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

class CompositeDeepScanLine {
public:
    using BoundType = Imf::CompositeDeepScanLine;

    IMF_EXPORT
    CompositeDeepScanLine();
    IMF_EXPORT
    virtual ~CompositeDeepScanLine();

    /// set the source data as a part
    ///@note all parts must remain valid until after last interaction with
    /// DeepComp
    IMF_EXPORT
    void addSource(Imf::DeepScanLineInputPart* part);

    /// set the source data as a file
    ///@note all file must remain valid until after last interaction with
    /// DeepComp
    IMF_EXPORT
    void addSource(Imf::DeepScanLineInputFile* file);

    /////////////////////////////////////////
    //
    // set the frame buffer for output values
    // the buffers specified must be large enough
    // to handle the dataWindow()
    //
    /////////////////////////////////////////
    IMF_EXPORT
    void setFrameBuffer(const Imf::FrameBuffer& fr);

    /////////////////////////////////////////
    //
    // retrieve frameBuffer
    //
    ////////////////////////////////////////
    IMF_EXPORT
    const Imf::FrameBuffer& frameBuffer() const;

    //////////////////////////////////////////////////
    //
    // read scanlines start to end from the source(s)
    // storing the result in the frame buffer provided
    //
    //////////////////////////////////////////////////

    IMF_EXPORT
    void readPixels(int start, int end);

    IMF_EXPORT
    int sources() const; // return number of sources

    /////////////////////////////////////////////////
    //
    // retrieve the datawindow
    // If multiple parts are specified, this will
    // be the union of the dataWindow of all parts
    //
    ////////////////////////////////////////////////

    IMF_EXPORT
    const IMATH_NAMESPACE::Box2i& dataWindow() const;

    //
    // override default sorting/compositing operation
    // (otherwise an instance of the base class will be used)
    //

    IMF_EXPORT
    void setCompositing(Imf::DeepCompositing*);
} CPPMM_OPAQUEBYTES;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
