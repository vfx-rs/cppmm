//------------------------------------------------------------------------------
// vfx-rs
//------------------------------------------------------------------------------
#include "cppmm_ast_add_c.hpp"
#include "pystring.h"
#include <cassert>
#include <iostream>

namespace cppmm {
namespace transform {

// The node entries are sparse, so store them in a map for the moment.
//using CppToC = std::unordered_map<NodeId, >;

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
void opaquebytes_record(NodeRecord & c_record)
{
    auto is_const = false;
    auto array_type =\
        std::make_unique<NodeArrayType>(
            "", PLACEHOLDER_ID, "",
            std::make_unique<NodeBuiltinType>("", PLACEHOLDER_ID, "char",
                                              is_const),
            c_record.size, is_const);

    c_record.force_alignment = true;
    c_record.fields.push_back(Field{ "data", std::move(array_type) });
}

//------------------------------------------------------------------------------
void opaquebytes_method(TranslationUnit & c_tu, const NodeRecord & cpp_record,
                        const NodeMethod & cpp_method)
{
    // Convert params
    auto params = std::vector<Param>();
    for(const auto & p : cpp_method.params)
    {
    }

    // Convert return type
    // Add opaquebytes body

    // Add the new function to the translation unit
}

//------------------------------------------------------------------------------
void opaquebytes_methods(TranslationUnit & c_tu, const NodeRecord & cpp_record)
{
    for(const auto & m: cpp_record.methods)
    {
        std::cerr << "handling method " << m.name << std::endl;
    }
}

//------------------------------------------------------------------------------
void record_entry(TranslationUnit & c_tu, const NodePtr & cpp_node)
{
    const auto & cpp_record =\
        *static_cast<const NodeRecord*>(cpp_node.get());

    const auto c_record_name = compute_c_record_name(cpp_record.name);

    auto c_record =\
        std::make_unique<NodeRecord>(
                   c_record_name, PLACEHOLDER_ID, cpp_record.attrs,
                   cpp_record.size, cpp_record.align);

    // Most simple record implementation is the opaque bytes.
    // Least safe and most restrictive in use, but easiest to implement.
    // So doing that first. Later will switch depending on the cppm attributes.

    opaquebytes_record(*c_record); // TODO LT: This needs to move into the record_detail function, so that it can have fields that reference other records.

    // Finally add the record to the translation unit
    c_tu.decls.push_back(std::move(c_record));
}

//------------------------------------------------------------------------------
void record_detail(TranslationUnit & c_tu, const NodePtr & cpp_node)
{
    const auto & cpp_record =\
        *static_cast<const NodeRecord*>(cpp_node.get());

    // Most simple record implementation is the opaque bytes.
    // Least safe and most restrictive in use, but easiest to implement.
    // So doing that first. Later will switch depending on the cppm attributes.

    opaquebytes_methods(c_tu, cpp_record);
    //opaquebytes_record(*c_record); // TODO LT: This needs to move into the record_detail function, so that it can have fields that reference other records.
}

//------------------------------------------------------------------------------
void translation_unit_entries(
    const std::string & output_directory, Root & root, const size_t cpp_tu)
{
    // Create a new translation unit
    const auto filepath =
        generate::compute_c_filepath(output_directory,
                                     root.tus[cpp_tu].filename);
    auto c_tu = TranslationUnit(filepath);

    // cpp records -> c records
    for (const auto & node : root.tus[cpp_tu].decls)
    {
        if (node->kind == NodeKind::Record)
        {
            generate::record_entry(c_tu, node);
        }
    }

    root.tus.push_back(std::move(c_tu));
}

//------------------------------------------------------------------------------
void translation_unit_details(
    Root & root, const size_t cpp_tu_size, const size_t cpp_tu)
{
    auto & c_tu = root.tus[cpp_tu_size+cpp_tu];

    // cpp methods -> c functions
    for (const auto & node : root.tus[cpp_tu].decls)
    {
        if (node->kind == NodeKind::Record)
        {
            generate::record_detail(c_tu, node);
        }
    }
}

} // namespace generate


//------------------------------------------------------------------------------
void add_c(const std::string & output_directory, Root & root)
{
    const auto tu_count = root.tus.size();

    // Add records
    for (size_t i=0; i != tu_count; ++i)
    {
        generate::translation_unit_entries(output_directory, root, i);
    }

    // Implement the records
    for (size_t i=0; i != tu_count; ++i)
    {
        generate::translation_unit_details(root, tu_count, i);
    }
}

} // namespace transform
} // namespace cppmm
