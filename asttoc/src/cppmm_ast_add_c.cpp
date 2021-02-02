//------------------------------------------------------------------------------
// vfx-rs
//------------------------------------------------------------------------------
#include "cppmm_ast_add_c.hpp"
#include "pystring.h"
#include <cassert>

namespace cppmm {
namespace transform {

//------------------------------------------------------------------------------
namespace generate
{

const NodeId PLACEHOLDER_ID = 0;

//------------------------------------------------------------------------------
std::string compute_c_filepath(const std::string & outdir,
                                const std::string & cpp_filepath)
{
    std::string cpp_filename = pystring::os::path::basename(cpp_filepath);
    return pystring::os::path::join(outdir, cpp_filename);
}

//------------------------------------------------------------------------------
std::string compute_c_record_name(const std::string & cpp_record_name)
{
    std::string result;
    for( auto const & c : cpp_record_name )
    {
        switch (c)
        {
            case ':':
            case '<':
            case '>':
                result.push_back('_');
                break;
            default:
                result.push_back(c);
        }
    }
    return result;
}

//------------------------------------------------------------------------------
void record_opaquebytes(NodeRecord & c_record)
{
}

//------------------------------------------------------------------------------
void record(TranslationUnit & c_tu, const NodePtr & cpp_node)
{
    // Most simple record implementation is the opaque bytes.
    // Least safe and most restrictive in use, but easiest to implement.
    // So doing that first.

    const auto & cpp_record =\
        *static_cast<const NodeRecord*>(cpp_node.get());

    const auto c_record_name = compute_c_record_name(cpp_record.name);

    auto c_record =\
        std::make_unique<NodeRecord>(
                   c_record_name, PLACEHOLDER_ID, cpp_record.attrs,
                   cpp_record.size, cpp_record.align);

    record_opaquebytes(*c_record);

    c_tu.decls.push_back(std::move(c_record));
}

} // namespace generate


//------------------------------------------------------------------------------
void add_c(const std::string & output_directory, Root & root)
{
    const auto tu_count = root.tus.size();

    // Loop over all the translation units adding c equivalents
    for (size_t i=0; i != tu_count; ++i)
    {
        // For each cpp translation unit we add a c equivalent
        const auto filepath =
            generate::compute_c_filepath(output_directory,
                                         root.tus[i].filename);
        auto c_tu = TranslationUnit(filepath);

        // Then we loop over the declarations converting the declarations
        for (const auto & node : root.tus[i].decls)
        {
            // Handle the record
            if (node->kind == NodeKind::Record)
            {
                generate::record(c_tu, node);
            }
        }

        // Finally add the new translation unit
        root.tus.push_back(std::move(c_tu));
    }
}

} // namespace transform
} // namespace cppmm
