//------------------------------------------------------------------------------
// vfx-rs
//------------------------------------------------------------------------------
#include "cppmm_ast_add_c.hpp"
#include "pystring.h"
#include <iostream>
#include <unordered_map>

#include <cstdlib> // for exit function

#define cassert(C, M) if(!(C)) { std::cerr << M << std::endl; abort(); }

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

    NodeRecord & edit_c(NodeId id)
    {
        auto & node = m_mapping[id].m_c; // TODO LT: Check existance + return optional
        // TODO LT: Assert kind is record

        return static_cast<NodeRecord&>(*node);
    }

    const NodeRecord * find_c(NodeId id) const
    {
        auto entry = m_mapping.find(id);

        if (entry == m_mapping.end())
        {
            return nullptr; // TODO LT: Turn this into optional
        }
        else
        {
            return static_cast<NodeRecord*>(entry->second.m_c.get());
        }
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

NodeTypePtr convert_type(RecordRegistry & record_registry,
                         const NodeTypePtr & t);

//------------------------------------------------------------------------------
NodeTypePtr convert_builtin_type(RecordRegistry & record_registry,
                                 const NodeTypePtr & t)
{
    // TODO LT: Do mapping of c++ builtins to c builtins

    // For now just copy everything one to one.
    return std::make_shared<NodeBuiltinType>(t->name, 0, t->type_name,
                                             t->const_);
}

//------------------------------------------------------------------------------
NodeTypePtr convert_record_type(RecordRegistry & record_registry,
                                const NodeTypePtr & t)
{
    const auto & c_type = record_registry.find_c(t->id);
    if (c_type == nullptr )
    {
        // TODO LT: Produce a warning here and return a failure so that
        // whatever depends on this type can be skipped.
        std::cerr << "Found unsupported type: " << t->type_name << std::endl;
        exit(1);
    }

    return std::make_shared<NodeRecordType>(t->name, 0, c_type->name,
                                            c_type->id, t->const_);
}

//------------------------------------------------------------------------------
NodeTypePtr convert_pointer_type(RecordRegistry & record_registry,
                                 const NodeTypePtr & t)
{
    auto p = static_cast<const NodePointerType*>(t.get());

    // For now just copy everything one to one.
    return std::make_shared<NodePointerType>(p->name, 0, p->type_name,
                                             PointerKind::Pointer,
                                             convert_type(record_registry,
                                                          p->pointee_type),
                                             p->const_);
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
            return convert_pointer_type(record_registry, t);
        default:
            break;
    }

    cassert(false, "Shouldn't get here"); // TODO LT: Clean this up
}

//------------------------------------------------------------------------------
void parameter(RecordRegistry & record_registry,
                std::vector<Param> & params, const Param & param)
{
    params.push_back(
            Param( std::string(param.name),
                   convert_type(record_registry, param.type),
                   params.size() )
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
Param self_param(const NodeRecord & c_record, bool const_)
{

    auto record = std::make_shared<NodeRecordType>(
                                                "",
                                                0,
                                                c_record.name,
                                                c_record.id,
                                                const_
                                           );

    auto pointer = std::make_shared<NodePointerType>("", 0,
                                           "",
                                           PointerKind::Pointer,
                                           std::move(record), false // TODO LT: Maybe references should be const pointers
                                           );

    return Param("self", std::move(pointer), 0);
}

//------------------------------------------------------------------------------
NodeExprPtr this_reference(const NodeRecord & cpp_record, bool const_)
{
    auto record = std::make_shared<NodeRecordType>(
                    "", 0, cpp_record.name, cpp_record.id, const_
    );
    auto type = std::make_shared<NodePointerType>(
                    "", 0, "", PointerKind::Pointer,
                    std::move(record), false 
    );
    auto self = std::make_shared<NodeVarRefExpr>("self");
    auto cast = std::make_shared<NodeCastExpr>(std::move(self),
                                               std::move(type),
                                               "reinterpret");

    return cast;
}

NodeExprPtr convert_argument(const NodeTypePtr & t, const std::string & name);

//------------------------------------------------------------------------------
NodeExprPtr convert_builtin_arg(const NodeTypePtr & t, const std::string & name)
{
    // TODO LT: Map c++ builtins to c ones. Likely static cast directly
    auto variable = std::make_shared<NodeVarRefExpr>(name);
    auto type = NodeTypePtr(t);
    return std::make_shared<NodeCastExpr>(std::move(variable),
                                          std::move(type),
                                          "static");
}

//------------------------------------------------------------------------------
NodeExprPtr convert_record_arg(const NodeTypePtr & t, const std::string & name)
{
    // TODO LT: Assuming opaquebytes at the moment, opaqueptr will have a
    // different implementation.
    //
    auto variable = std::make_shared<NodeVarRefExpr>(name);
    auto reference = std::make_shared<NodeRefExpr>(std::move(variable));
    auto type =\
        std::make_shared<NodePointerType>(
            "", 0, "", PointerKind::Pointer,
            std::move(NodeTypePtr(t)),
            false
    );
    auto inner = std::make_shared<NodeCastExpr>(
        std::move(reference), std::move(type), "reinterpret");
    return std::make_shared<NodeDerefExpr>(std::move(inner));

    /*
    // Above code could look like this later.
    return DerefExpr::new_(
        CastExpr::new_(
            RefExpr::new_(
                VarRefExpr::new_( name ) ),
            PointerType::new_( t, false ))
    )
    */
}

//------------------------------------------------------------------------------
NodeExprPtr convert_pointer_arg(const NodeTypePtr & t, const std::string & name)
{
    // TODO LT: Assuming opaquebytes at the moment, opaqueptr will have a
    // different implementation.
    //
    auto p = static_cast<const NodePointerType*>(t.get());

    switch (p->pointer_kind)
    {
        case PointerKind::Pointer:
            {
                auto variable = std::make_shared<NodeVarRefExpr>(name);
                auto type = NodeTypePtr(t);
                return std::make_shared<NodeCastExpr>(std::move(variable),
                                                      std::move(type),
                                                      "reinterpret");
            }
        case PointerKind::Reference:
            {
                auto variable = std::make_shared<NodeVarRefExpr>(name);
                auto pointee = NodeTypePtr(p->pointee_type);
                auto type =\
                    std::make_shared<NodePointerType>(
                        "", 0, "", PointerKind::Pointer,
                        std::move(pointee),
                        p->const_
                );
                auto inner = std::make_shared<NodeCastExpr>(
                    std::move(variable), std::move(type), "reinterpret");
                return std::make_shared<NodeDerefExpr>(std::move(inner));
            }
        default:
            break;
    }
    
    cassert(false, "Shouldn't get here"); // TODO LT: Clean this up
}

//------------------------------------------------------------------------------
NodeExprPtr convert_argument(const NodeTypePtr & t, const std::string & name)
{
    switch (t->kind)
    {
        case NodeKind::BuiltinType:
            return convert_builtin_arg(t, name);
        case NodeKind::RecordType:
            return convert_record_arg(t, name);
        case NodeKind::PointerType:
            return convert_pointer_arg(t, name);
        default:
            break;
    }

    cassert(false, "Shouldn't get here"); // TODO LT: Clean this up
}

//------------------------------------------------------------------------------
void argument(std::vector<NodeExprPtr> & args, const Param & param)
{
    auto argument = convert_argument(param.type, param.name);
    args.push_back(argument);
}

//------------------------------------------------------------------------------
NodeExprPtr opaquebytes_method_body(RecordRegistry & record_registry,
                                    TranslationUnit & c_tu,
                                    const NodeRecord & cpp_record,
                                    const NodeRecord & c_record,
                                    const NodeMethod & cpp_method)
{
    // Create the reference to this
    auto this_ = this_reference(cpp_record, false); // TODO LT: Missing cpp_method.const_

    // Loop over the parameters, creating arguments for the method call
    auto args = std::vector<NodeExprPtr>();
    for(const auto & p : cpp_method.params)
    {
        argument(args, p);
    }

    // Create the method call expression
    return std::make_shared<NodeMethodCallExpr>(std::move(this_),
                                                cpp_method.short_name,
                                                args
    );
}

//------------------------------------------------------------------------------
void opaquebytes_method(RecordRegistry & record_registry,
                           TranslationUnit & c_tu,
                           const NodeRecord & cpp_record,
                           const NodeRecord & c_record,
                           const NodeMethod & cpp_method)
{
    // Convert params
    auto c_params = std::vector<Param>();
    c_params.push_back(self_param(c_record, false)); // TODO LT: Const needs to be passed in here
    for(const auto & p : cpp_method.params)
    {
        parameter(record_registry, c_params, p);
    }

    // Convert return type
    auto c_return = convert_type(record_registry, cpp_method.return_type);

    // Creation function body
    auto c_function_body =
        opaquebytes_method_body(record_registry, c_tu, cpp_record, c_record,
                                cpp_method);

    // Add the new function to the translation unit
    auto c_function = std::make_shared<NodeFunction>(
                        compute_c_name(cpp_method.name), PLACEHOLDER_ID,
                        cpp_method.attrs, "", std::move(c_return),
                        std::move(c_params));

    c_function->body = c_function_body;

    c_tu.decls.push_back(std::move(c_function));
}

//------------------------------------------------------------------------------
void opaquebytes_methods(RecordRegistry & record_registry,
                         TranslationUnit & c_tu, const NodeRecord & cpp_record,
                         const NodeRecord & c_record)
{
    for(const auto & m: cpp_record.methods)
    {
        opaquebytes_method(record_registry, c_tu, cpp_record, c_record, m);
    }
}

//------------------------------------------------------------------------------
void record_entry(NodeId & record_id,
                  RecordRegistry & record_registry, TranslationUnit & c_tu,
                  NodePtr & cpp_node)
{
    const auto & cpp_record =\
        *static_cast<const NodeRecord*>(cpp_node.get());

    const auto c_record_name = compute_c_name(cpp_record.name);

    // Create the c record
    auto c_record =\
        std::make_shared<NodeRecord>(
                   c_record_name, record_id++, cpp_record.attrs,
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
        *static_cast<NodeRecord*>(cpp_node.get());

    // Most simple record implementation is the opaque bytes.
    // Least safe and most restrictive in use, but easiest to implement.
    // So doing that first. Later will switch depending on the cppm attributes.
    auto & c_record = record_registry.edit_c(cpp_record.id); // TODO LT: Return optional for error
    opaquebytes_record(c_record);

    // Most simple record implementation is the opaque bytes.
    // Least safe and most restrictive in use, but easiest to implement.
    // So doing that first. Later will switch depending on the cppm attributes.

    opaquebytes_methods(record_registry, c_tu, cpp_record, c_record);
}

//------------------------------------------------------------------------------
NodeId find_record_id_upper_bound(const Root & root)
{
    // Loop through all the record ids and find the largest one.
    // This will be used as the starting point for creating new ids.
    NodeId upper_bound = 0;
    for(const auto & t: root.tus)
    {
        for (const auto & node : t.decls)
        {
            if (node->kind == NodeKind::Record)
            {
                upper_bound = std::max(upper_bound, node->id);
            }
        }
    }

    return upper_bound;
}

//------------------------------------------------------------------------------
void translation_unit_entries(
    NodeId & new_record_id,
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
            generate::record_entry(new_record_id, record_registry, c_tu, node);
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


    // The starting id for newly created records
    NodeId current_record_id = generate::find_record_id_upper_bound(root) + 1;

    // When we iterate we dont want to loop over newly added c translation units
    const auto tu_count = root.tus.size();
    for (size_t i=0; i != tu_count; ++i)
    {
        generate::translation_unit_entries(
            current_record_id,
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
