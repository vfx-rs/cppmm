//------------------------------------------------------------------------------
// vfx-rs
//------------------------------------------------------------------------------
#include "cppmm_ast_add_c.hpp"
#include "pystring.h"
#include <cassert>
#include <iostream>
#include <unordered_map>

namespace cppmm {
namespace transform {

//------------------------------------------------------------------------------
// RecordRegistry
//------------------------------------------------------------------------------
class RecordRegistry
{
    struct Records
    {
        NodePtr m_cpp;
        NodePtr m_c;
    };

    // The node entries are sparse, so store them in a map for the moment.
    using Mapping = std::unordered_map<NodeId, Records>;

    Mapping m_mapping;

public:
    void add(NodeId id, NodePtr cpp, NodePtr c)
    {
        // TODO LT: Assert for double entries
        // TODO LT: Assert for RecordKind in cpp and c
        m_mapping.insert(std::make_pair( id, Records{ std::move(cpp),
                                                      std::move(c)
                                              }
        ));
    }

    NodeRecord & edit_c(NodeId id) {
        auto & node = m_mapping[id].m_c; // TODO LT: Check existance + return optional
        // TODO LT: Assert kind is record

        return static_cast<NodeRecord&>(*node);
    }
};

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
std::string compute_c_name(const std::string & cpp_record_name)
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
NodeTypePtr convert_builtin_type(RecordRegistry & record_registry,
                                 const NodeTypePtr & t)
{
}

//------------------------------------------------------------------------------
NodeTypePtr convert_record_type(RecordRegistry & record_registry,
                                const NodeTypePtr & t)
{
}

//------------------------------------------------------------------------------
NodeTypePtr convert_reference_type(RecordRegistry & record_registry,
                                   const NodeTypePtr & t)
{
}

//------------------------------------------------------------------------------
NodeTypePtr convert_type(RecordRegistry & record_registry,
                         const NodeTypePtr & t)
{
    switch (t->kind)
    {
        case NodeKind::BuiltinType:
            return convert_builtin_type(record_registry, t);
        case NodeKind::RecordType:
            return convert_record_type(record_registry, t);
        case NodeKind::PointerType:
            return convert_reference_type(record_registry, t);
        default:
            break;
    }

    assert("Shouldn't get here"); // TODO LT: Clean this up
}

//------------------------------------------------------------------------------
void parameter(RecordRegistry & record_registry,
                std::vector<Param> & params, const Param & param)
{
    params.push_back(
            Param( std::string(param.name),
                   convert_type(record_registry, param.type),
                   param.index )
    );
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
NodePtr opaquebytes_method(RecordRegistry & record_registry,
                           TranslationUnit & c_tu,
                           const NodeRecord & cpp_record,
                           const NodeMethod & cpp_method)
{
    // Convert params
    auto c_params = std::vector<Param>();
    for(const auto & p : cpp_method.params)
    {
        parameter(record_registry, c_params, p);
    }

    // Convert return type
    auto c_return = convert_type(record_registry, cpp_method.return_type);

    // Add opaquebytes body

    // TODO LT: This is where the casting and pointer/reference wrangling will
    // happen

    // Add the new function to the translation unit
    return std::make_shared<NodeFunction>(
                compute_c_name(cpp_method.name), PLACEHOLDER_ID,
                cpp_method.attrs, "", std::move(c_return), std::move(c_params));
}

//------------------------------------------------------------------------------
void opaquebytes_methods(RecordRegistry & record_registry,
                         TranslationUnit & c_tu, const NodeRecord & cpp_record)
{
    for(const auto & m: cpp_record.methods)
    {
        std::cerr << "handling method " << m.name << std::endl;
    }
}

//------------------------------------------------------------------------------
void record_entry(RecordRegistry & record_registry, TranslationUnit & c_tu,
                  NodePtr & cpp_node)
{
    const auto & cpp_record =\
        *static_cast<const NodeRecord*>(cpp_node.get());

    const auto c_record_name = compute_c_name(cpp_record.name);

    // Create the c record
    auto c_record =\
        std::make_shared<NodeRecord>(
                   c_record_name, PLACEHOLDER_ID, cpp_record.attrs,
                   cpp_record.size, cpp_record.align);

    // Add the cpp and c record to the registry
    record_registry.add(cpp_node->id, cpp_node, c_record);

    // Finally add the record to the translation unit
    c_tu.decls.push_back(std::move(c_record));
}

//------------------------------------------------------------------------------
void record_detail(RecordRegistry & record_registry, TranslationUnit & c_tu,
                   const NodePtr & cpp_node)
{
    const auto & cpp_record =\
        *static_cast<const NodeRecord*>(cpp_node.get());

    // Most simple record implementation is the opaque bytes.
    // Least safe and most restrictive in use, but easiest to implement.
    // So doing that first. Later will switch depending on the cppm attributes.
    auto c_record = record_registry.edit_c(cpp_record.id); // TODO LT: Return optional for error
    opaquebytes_record(c_record);

    // Most simple record implementation is the opaque bytes.
    // Least safe and most restrictive in use, but easiest to implement.
    // So doing that first. Later will switch depending on the cppm attributes.

    opaquebytes_methods(record_registry, c_tu, cpp_record);
}

//------------------------------------------------------------------------------
void translation_unit_entries(
    RecordRegistry & record_registry,
    const std::string & output_directory, Root & root, const size_t cpp_tu)
{
    // Create a new translation unit
    const auto filepath =
        generate::compute_c_filepath(output_directory,
                                     root.tus[cpp_tu].filename);
    auto c_tu = TranslationUnit(filepath);

    // cpp records -> c records
    for (auto & node : root.tus[cpp_tu].decls)
    {
        if (node->kind == NodeKind::Record)
        {
            generate::record_entry(record_registry, c_tu, node);
        }
    }

    root.tus.push_back(std::move(c_tu));
}

//------------------------------------------------------------------------------
void translation_unit_details(
    RecordRegistry & record_registry,
    Root & root, const size_t cpp_tu_size, const size_t cpp_tu)
{
    auto & c_tu = root.tus[cpp_tu_size+cpp_tu];

    // cpp methods -> c functions
    for (const auto & node : root.tus[cpp_tu].decls)
    {
        if (node->kind == NodeKind::Record)
        {
            generate::record_detail(record_registry, c_tu, node);
        }
    }
}

} // namespace generate


//------------------------------------------------------------------------------
void add_c(const std::string & output_directory, Root & root)
{
    // For storing the mappings between cpp and c records
    auto record_registry = RecordRegistry();

    // When we iterate we dont want to loop over newly added c translation units
    const auto tu_count = root.tus.size();

    // Add records
    for (size_t i=0; i != tu_count; ++i)
    {
        generate::translation_unit_entries(
            record_registry, output_directory, root, i);
    }

    // Implement the records
    for (size_t i=0; i != tu_count; ++i)
    {
        generate::translation_unit_details(record_registry, root, tu_count, i);
    }
}

} // namespace transform
} // namespace cppmm
