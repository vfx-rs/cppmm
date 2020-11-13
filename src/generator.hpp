#pragma once

#include "exports.hpp"
#include "decls.hpp"

namespace cppmm {

class Generator {
public:
    virtual ~Generator() {}
    virtual void generate(const ExportedFileMap& ex_files, const FileMap& files,
                          const RecordMap& records, const EnumMap& enums,
                          const VectorMap& vectors) = 0;
};

class CGenerator : public Generator {
public:
    // FIXME: the logic of what things end up in what maps is a bit gnarly here.
    // We should really move everythign that's in ExportedFile into File during
    // the second phase, and clarify what's expected to be in what maps exactly.
    virtual void generate(const ExportedFileMap& ex_files, const FileMap& files,
                          const RecordMap& records, const EnumMap& enums,
                          const VectorMap& vectors) override;
};

} // namespace cppmm
