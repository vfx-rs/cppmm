#pragma once

#include "decls.hpp"
#include "exports.hpp"

namespace cppmm {

class Generator {
public:
    virtual ~Generator() {}
    virtual void
    generate(const std::string& output_dir, const ExportedFileMap& ex_files,
             const FileMap& files, const RecordMap& records,
             const EnumMap& enums, const VectorMap& vectors,
             const std::vector<std::string>& project_includes,
             const std::vector<std::string>& project_libraries) = 0;
};

} // namespace cppmm
