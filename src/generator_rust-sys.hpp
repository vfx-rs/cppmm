#pragma once

#include "generator.hpp"
#include "generator_c.hpp"

namespace cppmm {

class GeneratorRustSys : public Generator {
    GeneratorC _c_generator;

public:
    GeneratorRustSys(std::string output_dir);

    virtual void
    generate(const FileMap& files, const RecordMap& records,
             const EnumMap& enums, const VectorMap& vectors,
             const std::vector<std::string>& project_includes,
             const std::vector<std::string>& project_libraries) override;
};

} // namespace cppmm
