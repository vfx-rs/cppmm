//------------------------------------------------------------------------------
// vfx-rs
//------------------------------------------------------------------------------
#include "cppmm_ast_add_c.hpp"
#include "pystring.h"
#include <cassert>

namespace cppmm {
namespace transform {

std::string compute_c_filepath(const std::string & outdir,
                                const std::string & cpp_filepath)
{
    std::string cpp_filename = pystring::os::path::basename(cpp_filepath);
    return pystring::os::path::join(outdir, cpp_filename);
}

void add_c(const std::string & output_directory, Root & root)
{
    const auto tu_count = root.tus.size();

    // Loop over all the translation units adding c equivalents
    for (size_t i=0; i != tu_count; ++i)
    {
        // For each cpp translation unit we add a c equivalent
        const auto filepath =
            compute_c_filepath(output_directory, root.tus[i].filename);
        auto c_tu = TranslationUnit(filepath);

        // Then we loop over the declarations 
        for (const auto & node : root.tus[i].decls)
        {
        }

        root.tus.push_back(std::move(c_tu));
    }
}

} // namespace transform
} // namespace cppmm
