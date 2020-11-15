#pragma once

#include "decls.hpp"
#include "exports.hpp"

namespace cppmm {

class Generator {
protected:
    std::string _output_dir;
public:
    Generator(std::string output_dir) : _output_dir(output_dir) {}
    virtual ~Generator() {}
    virtual void
    generate(const ExportedFileMap& ex_files,
             const FileMap& files, const RecordMap& records,
             const EnumMap& enums, const VectorMap& vectors,
             const std::vector<std::string>& project_includes,
             const std::vector<std::string>& project_libraries) = 0;
};

} // namespace cppmm
