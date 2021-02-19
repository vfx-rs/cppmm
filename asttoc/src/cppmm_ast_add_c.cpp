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
// TypeRegistry
//------------------------------------------------------------------------------
class TypeRegistry
{
    struct Records
    {
        NodePtr m_cpp;
        NodePtr m_c;
    };

    // The node entries are sparse, so store them in a map for the moment.
    using Mapping = std::unordered_map<NodeId, Records>;
    using Namespaces = std::unordered_map<NodeId, std::string>;

    Mapping m_mapping;
    Namespaces m_namespaces;

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

    void add_namespace(NodeId id, const std::string & ns)
    {
        // TODO LT: Assert for double entries
        m_namespaces[id] = ns;
    }

    const char * find_namespace(NodeId id) const
    {
        auto result = m_namespaces.find(id);
        if(result == m_namespaces.end())
        {
            return ""; // TODO LT: optional return with error would be better
        }
        else
        {
            return result->second.c_str();
        }
    }

    NodeRecord & edit_c(NodeId id)
    {
        auto & node = m_mapping[id].m_c; // TODO LT: Check existance + return optional
        // TODO LT: Assert kind is record

        return static_cast<NodeRecord&>(*node);
    }

    NodePtr find_c(NodeId id) const
    {
        auto entry = m_mapping.find(id);

        if (entry == m_mapping.end())
        {
            return NodePtr(); // TODO LT: Turn this into optional
        }
        else
        {
            return entry->second.m_c;
        }
    }
};

//------------------------------------------------------------------------------
namespace generate
{

const NodeId PLACEHOLDER_ID = 0;
const char * IGNORE = "cppmm:ignore";

//------------------------------------------------------------------------------
std::tuple<std::string, std::string, std::string>
             compute_c_filepath(const std::string & outdir,
                               const std::string & cpp_filepath)
{
    std::string root;
    std::string _ext;
    pystring::os::path::splitext(root, _ext,
                                 pystring::os::path::basename(cpp_filepath));

    const auto abs_root = pystring::os::path::join(outdir, root);
    
    return {root + ".h",
            abs_root + ".cpp",
            root + "_private.h",
    };
}

//------------------------------------------------------------------------------
std::string compute_c_name(const std::string & name)
{
    std::string result;
    for( auto const & c : name )
    {
        switch (c)
        {
            case ':':
            case ',':
            case '*':
            case '<':
            case '>':
                result.push_back('_');
                break;
            case ' ':
                break;
            default:
                result.push_back(c);
        }
    }
    return result;
}

//------------------------------------------------------------------------------
std::string compute_record_name(const TypeRegistry & type_registry,
                                const std::vector<NodeId> & namespaces,
                                const std::string & alias)
{
    std::string result;
    for(const auto & ns: namespaces)
    {
        result += type_registry.find_namespace(ns);
        result += "_";
    }

    result += alias;

    return result;
}

NodeTypePtr convert_type(TranslationUnit & c_tu,
                         TypeRegistry & type_registry,
                         const NodeTypePtr & t, bool in_reference);

//------------------------------------------------------------------------------
NodeTypePtr convert_builtin_type(TranslationUnit & c_tu,
                                 TypeRegistry & type_registry,
                                 const NodeTypePtr & t, bool _in_refererence)
{
    // TODO LT: Do mapping of c++ builtins to c builtins

    // For now just copy everything one to one.
    return NodeBuiltinType::n(t->name, 0, t->type_name, t->const_);
}


//------------------------------------------------------------------------------
void add_declaration(TranslationUnit & c_tu, const NodePtr & node_ptr,
                     bool in_reference)
{
    const auto & record = *static_cast<const NodeRecord*>(node_ptr.get());
    if(auto r_tu = record.tu.lock())
    {
        if(r_tu.get() != &c_tu)
        {
            if(in_reference) // Forward declaration
            {
                c_tu.forward_decls.insert(node_ptr);
                c_tu.source_includes.insert(r_tu->header_filename);
            }
            else // Header file
            {
                c_tu.header_includes.insert(r_tu->header_filename);
            }
            c_tu.source_private_includes.insert(r_tu->private_header_filename);
        }
    }
}

//------------------------------------------------------------------------------
NodeTypePtr convert_record_type(TranslationUnit & c_tu,
                                TypeRegistry & type_registry,
                                const NodeTypePtr & t, bool in_reference)
{
    const auto & cpp_record_type = *static_cast<const NodeRecordType*>(t.get());

    const auto & node_ptr = type_registry.find_c(cpp_record_type.record);
    if (!node_ptr)
    {
        std::cerr << "Found unsupported type: " << t->type_name << std::endl;
        return NodeTypePtr();
    }

    // Add the header file or forward declaration needed for this type
    // to be available.
    add_declaration(c_tu, node_ptr, in_reference);

    const auto & record = *static_cast<const NodeRecord*>(node_ptr.get());

    return NodeRecordType::n(t->name, 0, record.name, record.id, t->const_);
}

//------------------------------------------------------------------------------
NodeTypePtr convert_pointer_type(TranslationUnit & c_tu,
                                 TypeRegistry & type_registry,
                                 const NodeTypePtr & t, bool in_reference)
{
    auto p = static_cast<const NodePointerType*>(t.get());

    auto pointee_type =
        convert_type(c_tu, type_registry, p->pointee_type, true);

    // If we can't convert, then dont bother with this type either
    if(!pointee_type)
    {
        return NodeTypePtr();
    }

    // For now just copy everything one to one.
    return NodePointerType::n(PointerKind::Pointer,
                              std::move(pointee_type),
                              p->const_);
}

//------------------------------------------------------------------------------
NodeTypePtr convert_type(TranslationUnit & c_tu,
                         TypeRegistry & type_registry,
                         const NodeTypePtr & t, bool in_reference=false)
{
    switch (t->kind)
    {
        case NodeKind::BuiltinType:
            return convert_builtin_type(c_tu, type_registry, t, in_reference);
        case NodeKind::RecordType:
            return convert_record_type(c_tu, type_registry, t, in_reference);
        case NodeKind::PointerType:
            return convert_pointer_type(c_tu, type_registry, t, in_reference);
        case NodeKind::EnumType:
            return NodeTypePtr(); // TODO LT: Enum translation
        case NodeKind::FunctionProtoType:
            return NodeTypePtr(); // TODO LT: Function proto type translation
        default:
            break;
    }

    cassert(false, "convert_type: Shouldn't get here"); // TODO LT: Clean this up
}

//------------------------------------------------------------------------------
bool parameter(TranslationUnit & c_tu,
               TypeRegistry & type_registry,
               std::vector<Param> & params, const Param & param)
{
    auto param_type = convert_type(c_tu, type_registry, param.type);
    if(!param_type)
    {
        return false;
    }

    params.push_back(
            Param( std::string(param.name),
                   std::move(param_type),
                   params.size() )
    );

    return true;
}

//------------------------------------------------------------------------------
void opaquebytes_record(NodeRecord & c_record)
{
    constexpr auto sizeof_byte = 8;
    auto size_in_bytes = c_record.size / sizeof_byte;

    auto is_const = false;
    auto array_type =\
        std::make_unique<NodeArrayType>(
            "", PLACEHOLDER_ID, "",
            std::make_unique<NodeBuiltinType>("", PLACEHOLDER_ID, "char",
                                              is_const),
            size_in_bytes, is_const);

    c_record.force_alignment = true;
    c_record.fields.push_back(Field{ "data", std::move(array_type) });
}

//------------------------------------------------------------------------------
Param self_param(const NodeRecord & c_record, bool const_)
{

    auto record = NodeRecordType::n(
                                    "",
                                    0,
                                    c_record.name,
                                    c_record.id,
                                    const_
    );

    auto pointer = NodePointerType::n(PointerKind::Pointer,
                                      std::move(record), false // TODO LT: Maybe references should be const pointers
                                      );

    return Param("self", std::move(pointer), 0);
}

//------------------------------------------------------------------------------
NodeExprPtr this_reference(const NodeRecord & cpp_record, bool const_)
{
    return NodeFunctionCallExpr::n("to_cpp",
                                        std::vector<NodeExprPtr>({
        NodeVarRefExpr::n("self")
    }));
}

//------------------------------------------------------------------------------
bool should_wrap(const NodeMethod & cpp_method)
{
    // Check its not ignored
    for(const auto & a : cpp_method.attrs)
    {
        if(a == IGNORE)
        {
            return false;
        }
    }

    return true;
}

//------------------------------------------------------------------------------
NodeExprPtr convert_builtin_to(const NodeTypePtr & t, const NodeExprPtr & name)
{
    // TODO LT: Will make this smarter
    return NodeExprPtr(name);
}

//------------------------------------------------------------------------------
NodeExprPtr convert_record_to(const NodeTypePtr & t, const NodeExprPtr & name)
{
    // TODO LT: Assuming opaquebytes at the moment, opaqueptr will have a
    // different implementation.
    //
    auto reference = NodeRefExpr::n(NodeExprPtr(name));
    return NodeFunctionCallExpr::n("to_cpp_ref",
                                   std::vector<NodeExprPtr>({ reference })
    );
}

//------------------------------------------------------------------------------
NodeExprPtr convert_pointer_to(const NodeTypePtr & t, const NodeExprPtr & name)
{
    // TODO LT: Assuming opaquebytes at the moment, opaqueptr will have a
    // different implementation.
    //
    auto p = static_cast<const NodePointerType*>(t.get());

    switch (p->pointer_kind)
    {
        case PointerKind::Pointer:
            {
                return NodeFunctionCallExpr::n("to_cpp",
                                               std::vector<NodeExprPtr>({ name })
                );
            }
        case PointerKind::RValueReference: // TODO LT: Add support for rvalue reference
        case PointerKind::Reference:
            {
                return NodeFunctionCallExpr::n("to_cpp_ref",
                                               std::vector<NodeExprPtr>({ name })
                );
            }
        default:
            break;
    }
    
    cassert(false, "convert_pointer_arg Shouldn't get here"); // TODO LT: Clean this up
}

//------------------------------------------------------------------------------
NodeExprPtr convert_to(const NodeTypePtr & t, const NodeExprPtr & name)
{
    switch (t->kind)
    {
        case NodeKind::BuiltinType:
            return convert_builtin_to(t, name);
        case NodeKind::RecordType:
            return convert_record_to(t, name);
        case NodeKind::PointerType:
            return convert_pointer_to(t, name);
        default:
            break;
    }

    cassert(false, "convert_to Shouldn't get here"); // TODO LT: Clean this up
}

//------------------------------------------------------------------------------
NodeExprPtr convert_builtin_from(
                                 const NodeTypePtr & from_ptr,
                                 const NodeTypePtr & to_ptr,
                                 const NodeExprPtr & name)
{
    // TODO LT: Be smarter
    return NodeExprPtr(name);
}

//------------------------------------------------------------------------------
NodeExprPtr convert_record_from(
                                 const NodeTypePtr & from_ptr,
                                 const NodeTypePtr & to_ptr,
                                 const NodeExprPtr & name)
{
    return NodeFunctionCallExpr::n("to_c_copy",
                                   std::vector<NodeExprPtr>({ name }));
}

//------------------------------------------------------------------------------
NodeExprPtr convert_pointer_from(
                                 const NodeTypePtr & from_ptr,
                                 const NodeTypePtr & to_ptr,
                                 const NodeExprPtr & name)
{
    auto from = static_cast<const NodePointerType*>(from_ptr.get());

    switch (from->pointer_kind)
    {
        case PointerKind::RValueReference: // TODO LT: Add support for rvalue reference
        case PointerKind::Pointer:
        case PointerKind::Reference:
            {
                return NodeFunctionCallExpr::n("to_c",
                                               std::vector<NodeExprPtr>({ name })
                );
            }
        default:
            break;
    }
    
    cassert(false, "convert_pointer_arg Shouldn't get here"); // TODO LT: Clean this up
}

//------------------------------------------------------------------------------
NodeExprPtr convert_from(const NodeTypePtr & from,
                         const NodeTypePtr & to,
                         const NodeExprPtr & name)
{
    switch (to->kind)
    {
        case NodeKind::BuiltinType:
            return convert_builtin_from(from, to, name);
        case NodeKind::RecordType:
            return convert_record_from(from, to, name);
        case NodeKind::PointerType:
            return convert_pointer_from(from, to, name);
        default:
            break;
    }

    cassert(false, "convert_to Shouldn't get here"); // TODO LT: Clean this up
}

//------------------------------------------------------------------------------
void argument(std::vector<NodeExprPtr> & args, const Param & param)
{
    auto argument =
        convert_to(param.type,
                   NodeVarRefExpr::n(param.name));
    args.push_back(argument);
}

//------------------------------------------------------------------------------
NodeExprPtr opaquebytes_constructor_body(TypeRegistry & type_registry,
                                         TranslationUnit & c_tu,
                                         const NodeRecord & cpp_record,
                                         const NodeRecord & c_record,
                                         const NodeMethod & cpp_method)
{
    // Loop over the parameters, creating arguments for the method call
    auto args = std::vector<NodeExprPtr>();
    for(const auto & p : cpp_method.params)
    {
        argument(args, p);
    }

    // Create the method call expression
    return NodeBlockExpr::n(
                    std::vector<NodeExprPtr>({
                        NodePlacementNewExpr::n(
                            NodeVarRefExpr::n("self"),
                            NodeFunctionCallExpr::n(cpp_method.short_name, args)
    )}));
}

//------------------------------------------------------------------------------
NodeExprPtr opaquebytes_method_body(TypeRegistry & type_registry,
                                    TranslationUnit & c_tu,
                                    const NodeRecord & cpp_record,
                                    const NodeRecord & c_record,
                                    const NodeTypePtr & c_return,
                                    const NodeMethod & cpp_method)
{
    // Create the reference to this
    auto this_ = this_reference(cpp_record, cpp_method.is_const);

    // Loop over the parameters, creating arguments for the method call
    auto args = std::vector<NodeExprPtr>();
    for(const auto & p : cpp_method.params)
    {
        argument(args, p);
    }

    // Create the method call expression
    auto method_call =
        NodeMethodCallExpr::n(std::move(this_),
                              cpp_method.short_name,
                              args
    );

    // Convert the result
    auto is_void =
        c_return->kind == NodeKind::BuiltinType &&
        static_cast<const NodeBuiltinType*>(c_return.get())->type_name == "void";

    if(is_void)
    {
        return NodeBlockExpr::n(
                    std::vector<NodeExprPtr>({method_call
        }));
    }

    return NodeBlockExpr::n(
                std::vector<NodeExprPtr>({
                    NodeReturnExpr::n(
                        convert_from(cpp_method.return_type,
                                     c_return, method_call))
    }));
}

//------------------------------------------------------------------------------
NodeExprPtr opaquebytes_c_function_body(TypeRegistry & type_registry,
                                        TranslationUnit & c_tu,
                                        const NodeRecord & cpp_record,
                                        const NodeRecord & c_record,
                                        const NodeTypePtr & c_return,
                                        const NodeMethod & cpp_method)
{
    if(cpp_method.is_constructor)
    {
        return opaquebytes_constructor_body(
            type_registry, c_tu, cpp_record, c_record, cpp_method);
    }
    else
    {
        return opaquebytes_method_body(
            type_registry, c_tu, cpp_record, c_record, c_return, cpp_method);
    }
}

//------------------------------------------------------------------------------
void opaquebytes_method(TypeRegistry & type_registry,
                        TranslationUnit & c_tu,
                        const NodeRecord & cpp_record,
                        const NodeRecord & c_record,
                        const NodeMethod & cpp_method,
                        NodePtr & copy_constructor)
{
    // Skip ignored methods
    if(!should_wrap(cpp_method))
    {
        std::cerr << "ignoring method decl: " << cpp_method.name << std::endl;
        return;
    }

    // Convert params
    auto c_params = std::vector<Param>();
    c_params.push_back(self_param(c_record, cpp_method.is_const));
    for(const auto & p : cpp_method.params)
    {
        if(!parameter(c_tu, type_registry, c_params, p))
        {
            std::cerr << "Skipping: " << cpp_method.name << std::endl;
            return;
        }
    }

    // Convert return type
    auto c_return = convert_type(c_tu, type_registry, cpp_method.return_type);
    if(!c_return)
    {
        std::cerr << "Skipping: " << cpp_method.name << std::endl;
        return;
    }

    // Function body
    auto c_function_body =
        opaquebytes_c_function_body(type_registry, c_tu, cpp_record, c_record,
                                    c_return, cpp_method);

    // Add the new function to the translation unit
    std::string method_name = c_record.name;
    method_name += "_";
    method_name += compute_c_name(cpp_method.short_name);
    auto c_function = NodeFunction::n(
                        method_name, PLACEHOLDER_ID,
                        cpp_method.attrs, "", std::move(c_return),
                        std::move(c_params));

    c_function->body = c_function_body;
    c_tu.decls.push_back(NodePtr(c_function));

    // Keep hold of a reference to the copy constructor,
    // we need this later on for implicit conversions.
    //
    // TODO LT: Take the move constructor with priority
    if(cpp_method.is_copy_constructor)
    {
        copy_constructor = c_function;
    }
}

//------------------------------------------------------------------------------
void opaquebytes_methods(TypeRegistry & type_registry,
                         TranslationUnit & c_tu, const NodeRecord & cpp_record,
                         const NodeRecord & c_record,
                         NodePtr & copy_constructor)
{
    for(const auto & m: cpp_record.methods)
    {
        opaquebytes_method(type_registry, c_tu, cpp_record, c_record, m,
                           copy_constructor);
    }
}

//------------------------------------------------------------------------------
void record_entry(NodeId & record_id,
                  TypeRegistry & type_registry, TranslationUnit::Ptr & c_tu,
                  const NodePtr & cpp_node)
{
    const auto & cpp_record =\
        *static_cast<const NodeRecord*>(cpp_node.get());

    const auto c_record_name =
        compute_record_name(type_registry, cpp_record.namespaces,
                            cpp_record.alias);

    // Create the c record
    auto c_record = NodeRecord::n(
                   c_tu,
                   c_record_name, record_id++, cpp_record.attrs,
                   cpp_record.size, cpp_record.align, cpp_record.alias,
                   cpp_record.namespaces);

    // Add the cpp and c record to the registry
    type_registry.add(cpp_node->id, cpp_node, c_record);

    // Finally add the record to the translation unit
    c_tu->decls.push_back(std::move(c_record));
}

//------------------------------------------------------------------------------
void namespace_entry(TypeRegistry & type_registry, const NodePtr & cpp_node)
{
    const auto & cpp_namespace =\
        *static_cast<const NodeNamespace*>(cpp_node.get());

    type_registry.add_namespace(cpp_namespace.id, cpp_namespace.short_name);
}

//------------------------------------------------------------------------------
void opaquebytes_to_cpp(TranslationUnit & c_tu,
                        const NodeRecord & cpp_record,
                        const NodeRecord & c_record,
                        bool const_,
                        PointerKind pointer_kind)
{
    auto rhs =
        NodePointerType::n(
            PointerKind::Pointer,
            NodeRecordType::n("", 0, c_record.name, c_record.id, const_),
            false
    );

    auto cpp_return =
        NodePointerType::n(
            pointer_kind,
                NodeRecordType::n("", 0, cpp_record.name, cpp_record.id,
                                  const_),
    false);

    // Cast type
    NodeExprPtr cast_expr =
        NodeCastExpr::n(
            NodeVarRefExpr::n("rhs"),
            NodePointerType::n(PointerKind::Pointer,
                               NodeRecordType::n("", 0, cpp_record.name,
                                                 cpp_record.id, const_),
                               false
                              ),
            "reinterpret"
        );

    if(pointer_kind == PointerKind::Reference)
    {
        cast_expr = NodeDerefExpr::n(std::move(cast_expr));
    }

    // Function body
    auto c_function_body =
        NodeBlockExpr::n(std::vector<NodeExprPtr>({
            NodeReturnExpr::n(std::move(cast_expr)),
        }));

    // Add the new function to the translation unit
    std::vector<std::string> attrs;
    std::vector<Param> params = {Param("rhs", rhs, 0)};
    std::string function_name = "to_cpp";
    if(pointer_kind == PointerKind::Reference)
    {
        function_name += "_ref";
    }
    auto c_function = NodeFunction::n(
                        function_name, PLACEHOLDER_ID,
                        attrs, "", std::move(cpp_return),
                        std::move(params));

    c_function->body = c_function_body;
    c_function->private_ = true;
    c_function->inline_ = true;

    c_tu.decls.push_back(std::move(c_function));
}

//------------------------------------------------------------------------------
void opaquebytes_to_c(TranslationUnit & c_tu,
                      const NodeRecord & cpp_record,
                      const NodeRecord & c_record,
                      bool const_,
                      PointerKind pointer_kind)
{
    auto rhs =
        NodePointerType::n(
            pointer_kind,
            NodeRecordType::n("", 0, cpp_record.name, cpp_record.id, const_),
            false
    );

    auto c_return =
        NodePointerType::n(
            PointerKind::Pointer,
                NodeRecordType::n("", 0, c_record.name, c_record.id,
                                  const_),
    false);

    NodeExprPtr var_ref_expr = NodeVarRefExpr::n("rhs");
    if(pointer_kind == PointerKind::Reference)
    {
        var_ref_expr = NodeRefExpr::n(std::move(var_ref_expr));
    }

    // Cast type
    NodeExprPtr cast_expr =
        NodeCastExpr::n(
            std::move(var_ref_expr),
            NodePointerType::n(PointerKind::Pointer,
                               NodeRecordType::n("", 0, c_record.name,
                                                 c_record.id, const_),
                               false
                              ),
            "reinterpret"
        );

    // Function body
    auto c_function_body =
        NodeBlockExpr::n(std::vector<NodeExprPtr>({
            NodeReturnExpr::n(std::move(cast_expr)),
        }));

    // Add the new function to the translation unit
    std::vector<std::string> attrs;
    std::vector<Param> params = {Param("rhs", rhs, 0)};
    auto c_function = NodeFunction::n(
                        "to_c", PLACEHOLDER_ID,
                        attrs, "", std::move(c_return),
                        std::move(params));

    c_function->body = c_function_body;
    c_function->private_ = true;
    c_function->inline_ = true;

    c_tu.decls.push_back(std::move(c_function));
}

/*
//------------------------------------------------------------------------------
void opaquebytes_from_cpp(TranslationUnit & c_tu,
                          const NodeRecord & cpp_record,
                          const NodeRecord & c_record)
{
    auto rhs =
        NodePointerType::n(
            PointerKind::Reference,
            NodeRecordType::n("", 0, cpp_record.name, cpp_record.id, true),
            false
    );

    auto c_return = NodeRecordType::n("", 0, c_record.name, c_record.id, false);
    auto bit_cast =
        NodeFunctionCallExpr::n(
            "memcpy",
            std::vector<NodeExprPtr>({
                NodeRefExpr::n(
                    NodeVarRefExpr::n("result")
                ),
                NodeRefExpr::n(
                    NodeVarRefExpr::n("rhs")
                ),
                NodeFunctionCallExpr::n("sizeof",
                                        std::vector<NodeExprPtr>({
                                            NodeVarRefExpr::n("rhs")
                                        })
                )
            })
    );

    // Function body
    auto c_function_body =
        NodeBlockExpr::n(std::vector<NodeExprPtr>({
            // TO result;
            NodeVarDeclExpr::n(
                NodeTypePtr(c_return),
                "result"
            ),

            // memcpy(&result, &rhs, sizeof(rhs))
            NodeFunctionCallExpr::n(
                "memcpy",
                std::vector<NodeExprPtr>({
                    NodeRefExpr::n(
                        NodeVarRefExpr::n("result")
                    ),
                    NodeRefExpr::n(
                        NodeVarRefExpr::n("rhs")
                    ),
                    NodeFunctionCallExpr::n("sizeof",
                                            std::vector<NodeExprPtr>({
                                                NodeVarRefExpr::n("rhs")
                                            })
                    )
                })
            )
        }));

    // Add the new function to the translation unit
    std::vector<std::string> attrs;
    std::vector<Param> params = {Param("rhs", rhs, 0)};
    auto c_function = NodeFunction::n(
                        "from_cpp", PLACEHOLDER_ID,
                        attrs, "", std::move(c_return),
                        std::move(params));

    c_function->body = c_function_body;
    c_function->private_ = true;

    c_tu.decls.push_back(std::move(c_function));
}
*/

//------------------------------------------------------------------------------
void opaquebytes_to_c_copy(TranslationUnit & c_tu,
                               const NodeRecord & cpp_record,
                               const NodeRecord & c_record,
                               const NodePtr & copy_constructor_ptr)
{
    const auto & copy_constructor =\
        *static_cast<const NodeFunction*>(copy_constructor_ptr.get());

    auto rhs =
        NodePointerType::n(
            PointerKind::Reference,
            NodeRecordType::n("", 0, cpp_record.name, cpp_record.id, true),
            false
    );

    auto c_return = NodeRecordType::n("", 0, c_record.name, c_record.id, false);

    // Function body
    auto c_function_body =
        NodeBlockExpr::n(std::vector<NodeExprPtr>({
            // TO result;
            NodeVarDeclExpr::n(
                NodeTypePtr(c_return),
                "result"
            ),

            // copy_constructor(&result, reinterpret_cast<const CTYPE *>(rhs))
            NodeFunctionCallExpr::n(
                copy_constructor.name,
                std::vector<NodeExprPtr>({
                    NodeRefExpr::n(
                        NodeVarRefExpr::n("result")
                    ),
                    NodeCastExpr::n(
                        NodeRefExpr::n(
                            NodeVarRefExpr::n("rhs")
                        ),
                        NodePointerType::n(
                            PointerKind::Pointer,
                            NodeRecordType::n("", 0, c_record.name, c_record.id,
                                              true),
                            false
                        ),
                        "reinterpret"
                    )
                })
            ),

            // Return
            NodeReturnExpr::n(
                NodeVarRefExpr::n("result")
            )
        }));

    // Add the new function to the translation unit
    std::vector<std::string> attrs;
    std::vector<Param> params = {Param("rhs", rhs, 0)};
    auto c_function = NodeFunction::n(
                        "to_c_copy", PLACEHOLDER_ID,
                        attrs, "", std::move(c_return),
                        std::move(params));

    c_function->body = c_function_body;
    c_function->private_ = true;
    c_function->inline_ = true;

    c_tu.decls.push_back(std::move(c_function));
}

//------------------------------------------------------------------------------
void opaquebytes_conversions(TranslationUnit & c_tu,
                             const NodeRecord & cpp_record,
                             const NodeRecord & c_record,
                             const NodePtr & copy_constructor)
{
    // Conversions for going from cpp to c
    opaquebytes_to_cpp(c_tu, cpp_record, c_record, true, PointerKind::Reference);
    opaquebytes_to_cpp(c_tu, cpp_record, c_record, false, PointerKind::Reference);
    opaquebytes_to_cpp(c_tu, cpp_record, c_record, true, PointerKind::Pointer);
    opaquebytes_to_cpp(c_tu, cpp_record, c_record, false, PointerKind::Pointer);

    // We need the copy constructor in order to be able to return records
    // by value
    opaquebytes_to_c(c_tu, cpp_record, c_record, true, PointerKind::Reference);
    opaquebytes_to_c(c_tu, cpp_record, c_record, true, PointerKind::Pointer);
    opaquebytes_to_c(c_tu, cpp_record, c_record, false, PointerKind::Reference);
    opaquebytes_to_c(c_tu, cpp_record, c_record, false, PointerKind::Pointer);

    if(copy_constructor)
    {
        opaquebytes_to_c_copy(c_tu, cpp_record, c_record, copy_constructor);
    }
}

//------------------------------------------------------------------------------
void record_detail(TypeRegistry & type_registry, TranslationUnit & c_tu,
                   const NodePtr & cpp_node)
{
    const auto & cpp_record =\
        *static_cast<NodeRecord*>(cpp_node.get());

    // Most simple record implementation is the opaque bytes.
    // Least safe and most restrictive in use, but easiest to implement.
    // So doing that first. Later will switch depending on the cppm attributes.
    auto & c_record = type_registry.edit_c(cpp_record.id); // TODO LT: Return optional for error
    opaquebytes_record(c_record);

    // Most simple record implementation is the opaque bytes.
    // Least safe and most restrictive in use, but easiest to implement.
    // So doing that first. Later will switch depending on the cppm attributes.

    // Record
    opaquebytes_record(c_record);

    // Methods
    NodePtr copy_constructor;
    opaquebytes_methods(type_registry, c_tu, cpp_record, c_record,
                        copy_constructor);

    // Conversions
    opaquebytes_conversions(c_tu, cpp_record, c_record, copy_constructor);
}

//------------------------------------------------------------------------------
NodeId find_record_id_upper_bound(const Root & root)
{
    // Loop through all the record ids and find the largest one.
    // This will be used as the starting point for creating new ids.
    NodeId upper_bound = 0;
    for(const auto & t: root.tus)
    {
        for (const auto & node : t->decls)
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
std::string header_file_include(std::string header_filename)
{
    std::string result = "#include <";
    result += header_filename;
    result += ">";
    return result;
}

//------------------------------------------------------------------------------
void translation_unit_entries(
    NodeId & new_record_id,
    TypeRegistry & type_registry,
    const std::string & output_directory, Root & root,
    const size_t cpp_tu_index)
{
    const auto & cpp_tu = root.tus[cpp_tu_index];

    // Create a new translation unit
    const auto filepaths =
        generate::compute_c_filepath(output_directory,
                                     cpp_tu->filename);

    enum Outputs {
        Header = 0,
        Source = 1,
        PrivateHeader = 2,
    };

    // Make the new translation unit
    auto c_tu = TranslationUnit::new_(std::get<Source>(filepaths));
    c_tu->header_filename = header_file_include(std::get<Header>(filepaths));
    c_tu->private_header_filename =
        header_file_include(std::get<PrivateHeader>(filepaths));

    // source includes -> source includes
    for (auto & i : cpp_tu->source_includes)
    {
        c_tu->source_includes.insert(i);
    }

    // cpp namespaces
    for (const auto & node : cpp_tu->decls)
    {
        switch (node->kind)
        {
        case NodeKind::Namespace:
            generate::namespace_entry(type_registry, node);
            break;
        default:
            break;
        }
    }

    // cpp records -> c records
    for (const auto & node : cpp_tu->decls)
    {
        switch (node->kind)
        {
        case NodeKind::Record:
            generate::record_entry(new_record_id, type_registry, c_tu, node);
            break;
        default:
            break;
        }
    }

    root.tus.push_back(std::move(c_tu));
}

//------------------------------------------------------------------------------
void translation_unit_details(
    TypeRegistry & type_registry,
    Root & root, const size_t cpp_tu_size, const size_t cpp_tu)
{
    auto & c_tu = *root.tus[cpp_tu_size+cpp_tu];

    // cpp methods -> c functions
    for (const auto & node : root.tus[cpp_tu]->decls)
    {
        if (node->kind == NodeKind::Record)
        {
            generate::record_detail(type_registry, c_tu, node);
        }
    }
}

} // namespace generate


//------------------------------------------------------------------------------
void add_c(const std::string & output_directory, Root & root)
{
    // For storing the mappings between cpp and c records
    auto type_registry = TypeRegistry();

    // The starting id for newly created records
    NodeId current_record_id = generate::find_record_id_upper_bound(root) + 1;

    // When we iterate we dont want to loop over newly added c translation units
    const auto tu_count = root.tus.size();
    for (size_t i=0; i != tu_count; ++i)
    {
        generate::translation_unit_entries(
            current_record_id,
            type_registry, output_directory, root, i);
    }

    // Implement the records
    for (size_t i=0; i != tu_count; ++i)
    {
        generate::translation_unit_details(type_registry, root, tu_count, i);
    }
}

} // namespace transform
} // namespace cppmm
