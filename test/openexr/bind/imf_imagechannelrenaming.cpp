#include <OpenEXR/ImfImageChannelRenaming.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

typedef std::map<std::string, std::string> RenamingMap;

template <class ChannelMap>
void renameChannelsInMap(const RenamingMap oldToNewNames,
                         ChannelMap& channels) CPPMM_IGNORE;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
