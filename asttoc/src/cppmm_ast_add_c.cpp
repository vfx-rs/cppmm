//------------------------------------------------------------------------------
// vfx-rs
//------------------------------------------------------------------------------
#include "cppmm_ast_add_c.hpp"
#include "pystring.h"
#include <cassert>

namespace cppmm {
namespace transform {

namespace {
//    const char * ALIGN = "align";
//    const char * CHILDREN = "children";
//    const char * CONST = "const";
//    const char * DECLS = "decls";
//    const char * FIELDS = "fields";
//    const char * FILENAME = "filename";
//    const char * ID = "id";
//    const char * INDEX = "index";
//    const char * KIND = "kind";
//    const char * METHODS = "methods";
//    const char * NAME = "name";
//    const char * QUALIFIED_NAME = "qualified_name";
//    const char * SHORT_NAME = "short_name";
//    const char * PARAMS = "params";
//    const char * SIZE = "size";
//    const char * STATIC = "static";
    const char * RECORD_C = "Record";
//    const char * RECORD_L = "record";
//    const char * TYPE = "type";
//    const char * POINTEE = "pointee";
//    const char * RETURN = "return";
}

//------------------------------------------------------------------------------
namespace generate
{
    NodePtr record(NodePtr & cpp_record)
    {
    }
}

//------------------------------------------------------------------------------
std::string compute_c_filepath(const std::string & outdir,
                                const std::string & cpp_filepath)
{
    std::string cpp_filename = pystring::os::path::basename(cpp_filepath);
    return pystring::os::path::join(outdir, cpp_filename);
}

//------------------------------------------------------------------------------
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
            // Handle the record
            if (node.kind == RECORD_C)
            {
                c_tu.decls.push_back(generate_record(node));
            }
        }

        root.tus.push_back(std::move(c_tu));
    }
}

} // namespace transform
} // namespace cppmm
