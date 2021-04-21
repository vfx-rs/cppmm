#include "process_binding.hpp"
#include "pystring.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/Decl.h"
#include "clang/AST/DeclCXX.h"
#include "clang/AST/DeclTemplate.h"
#include "clang/AST/GlobalDecl.h"
#include "clang/AST/Mangle.h"
#include "clang/AST/Type.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/Basic/LLVM.h"
#include "llvm/Support/Casting.h"
#include <cassert>
#include <cstdint>
#include <memory>
#include <unordered_map>

#define SPDLOG_ACTIVE_LEVEL TRACE
#include <spdlog/fmt/fmt.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>

#include <iomanip>
#include <iostream>

#include "filesystem.hpp"
namespace fs = ghc::filesystem;

#include "ast.hpp"
#include "ast_utils.hpp"

using namespace clang;
using namespace clang::ast_matchers;
namespace ps = pystring;

extern std::unordered_map<std::string, std::vector<std::string>>
    source_includes;
extern std::vector<std::string> project_includes;

bool WARN_UNMATCHED = false;

namespace cppmm {

/// Get the size and alignment for the given decl. Returns true if the info
/// could be ascertained, false otherwise.
bool get_abi_info(const TypeDecl* td, ASTContext& ctx, uint32_t& size,
                  uint32_t& align) {
    if (td) {
        const clang::Type* ty = td->getTypeForDecl();
        if (!ty->isIncompleteType()) {
            const clang::TypeInfo& ti = ctx.getTypeInfo(ty);
            size = ti.Width;
            align = ti.Align;
            return true;
        } else {
            SPDLOG_TRACE("    is incomplete type");
        }
    } else {
        SPDLOG_TRACE("    is not a TypeDecl");
    }

    return false;
}

QType process_qtype(const QualType& qt);

/// Create a new NodeFunctionProtoType from the given FunctionProtoType and
/// return its id.
NodeId process_function_proto_type(const FunctionProtoType* fpt,
                                   std::string type_name,
                                   std::string type_node_name) {
    SPDLOG_TRACE("Got FPT {}", type_name);
    auto it = NODE_MAP.find(type_node_name);
    if (it != NODE_MAP.end()) {
        // already have an entry for this
        return it->second;
    } else {
        QType return_type = process_qtype(fpt->getReturnType());
        if (return_type.ty == -1) {
            SPDLOG_ERROR("processing return type of FunctionProtoType {}",
                         type_name);
        }
        std::vector<QType> params;
        for (const QualType& pqt : fpt->param_types()) {
            auto pt = process_qtype(pqt);
            if (pt.ty == -1) {
                SPDLOG_ERROR("processing parameter of FunctionProtoType {}",
                             type_name);
            }
            params.push_back(pt);
        }

        // See if we've got a typedef for this funtion pointer type
        NodeId typedef_id = -1;
        const auto it = NODE_MAP.find(type_name);
        if (it != NODE_MAP.end()) {
            typedef_id = it->second;
        }

        NodeId id = NODES.size();
        auto node_ptr = std::make_unique<NodeFunctionProtoType>(
            type_node_name, id, 0, std::move(type_name), std::move(return_type),
            std::move(params), typedef_id);
        NODES.emplace_back(std::move(node_ptr));
        NODE_MAP[type_node_name] = id;
        return id;
    }
}

/// Create a QType from the given QualType. Recursively processes the contained
/// types.
QType process_qtype(const QualType& qt) {
    if (const auto* dt = qt->getAs<DecayedType>()) {
        // if it's a decayed type, get back the original type if it's a
        // constant array
        const auto ot = dt->getOriginalType();
        if (ot->isConstantArrayType()) {
            return process_qtype(ot);
        } else {
            return process_qtype(dt->getDecayedType());
        }
    } else if (qt->isConstantArrayType()) {
        // e.g. float[3]
        const std::string type_name = qt.getCanonicalType().getAsString();
        const std::string type_node_name = "TYPE:" + type_name;
        auto it = NODE_MAP.find(type_node_name);
        NodeId id;
        if (it == NODE_MAP.end()) {
            const ConstantArrayType* cat =
                dyn_cast<ConstantArrayType>(qt.getTypePtr());
            QType element_type = process_qtype(cat->getElementType());
            id = NODES.size();
            auto node_type = std::make_unique<NodeConstantArrayType>(
                type_node_name, id, 0, type_name, element_type,
                cat->getSize().getLimitedValue());
            NODES.emplace_back(std::move(node_type));
            NODE_MAP[type_node_name] = id;
        } else {
            id = it->second;
        }

        return QType{id, qt.isConstQualified()};
    } else if (qt->isPointerType() || qt->isReferenceType()) {
        // first, figure out what kind of pointer we have
        auto pointer_kind = PointerKind::Pointer;
        if (qt->isRValueReferenceType()) {
            pointer_kind = PointerKind::RValueReference;
        } else if (qt->isReferenceType()) {
            pointer_kind = PointerKind::Reference;
        }

        // first check if we've got the pointer type already
        const std::string pointer_type_name =
            qt.getCanonicalType().getAsString();
        const std::string pointer_type_node_name = "TYPE:" + pointer_type_name;

        auto it = NODE_MAP.find(pointer_type_name);
        NodeId id;
        if (it == NODE_MAP.end()) {
            // need to create the pointer type, create the pointee type first
            QType pointee_qtype =
                process_qtype(qt->getPointeeType().getCanonicalType());
            // now create the pointer type
            id = NODES.size();
            auto node_pointer_type = std::make_unique<NodePointerType>(
                pointer_type_node_name, id, 0, pointer_type_name, pointer_kind,
                pointee_qtype);
            NODES.emplace_back(std::move(node_pointer_type));
            NODE_MAP[pointer_type_name] = id;
        } else {
            // already done this type
            id = it->second;
        }

        return QType{id, qt.isConstQualified()};
    } else {
        // regular type, let's get a nice name for it by removing the
        // class/struct/enum/union qualifier clang adds
        std::string type_name = strip_name_kinds(
            qt.getCanonicalType().getUnqualifiedType().getAsString());
        // We need to store type nodes for later access, since we might process
        // the corresponding record decl after processing this type node, and
        // will need to look it up later to set the appropriate id.
        // to get around the fact that the type and the record it refers to will
        // have the same name, we just prepend "TYPE:" to the type node name
        // here.
        // FIXME: we might want to stores types in a completely separate data
        // structure
        std::string type_node_name = "TYPE:" + type_name;
        if (qt->isRecordType()) {
            auto crd = qt->getAsCXXRecordDecl();
            // auto mng_ctx = crd->getASTContext().createMangleContext();
            // std::string s;
            // llvm::raw_string_ostream os(s);
            // mng_ctx->mangleCXXName(crd, os);
            // std::string mangled_name = os.str();
            std::string mangled_name = mangle_decl(crd);
            type_node_name = "TYPE:" + mangled_name;
        }

        // see if we've proessed this type already
        auto it = NODE_MAP.find(type_node_name);
        NodeId id;
        if (it == NODE_MAP.end()) {
            // haven't done this type yet we'll need to create a new node for it
            id = NODES.size();
            if (qt->isBuiltinType()) {
                // It's just a builtin. We store its name
                auto node_type = std::make_unique<NodeBuiltinType>(
                    type_node_name, id, 0, type_name);
                NODES.emplace_back(std::move(node_type));
                NODE_MAP[type_node_name] = id;
            } else if (qt->isRecordType()) {
                auto crd = qt->getAsCXXRecordDecl();
                assert(crd && "CRD from Type is null");
                crd = crd->getCanonicalDecl();
                assert(crd && "CRD canonical decl is null");

                // See if we've already processed a record matching this type
                // and get its id if we have. If not we'll store -1 until we
                // come back and process the decl later.
                const std::string record_name = crd->getQualifiedNameAsString();
                NodeId id_rec = -1;
                // auto mng_ctx = crd->getASTContext().createMangleContext();
                // std::string s;
                // llvm::raw_string_ostream os(s);
                // mng_ctx->mangleCXXName(crd, os);
                // std::string mangled_name = os.str();
                std::string mangled_name = mangle_decl(crd);
                auto it_rec = NODE_MAP.find(mangled_name);
                if (it_rec != NODE_MAP.end()) {
                    SPDLOG_DEBUG("Found record {} from {}",
                                 crd->getQualifiedNameAsString(), mangled_name);
                    id_rec = it_rec->second;
                } else {
                    // SPDLOG_DEBUG("Couldn't find a record for {} ({})",
                    //              record_name, mangled_name);
                }

                auto node_record_type = std::make_unique<NodeRecordType>(
                    type_node_name, id, 0, type_name, id_rec);
                NODES.emplace_back(std::move(node_record_type));
                NODE_MAP[type_node_name] = id;
            } else if (qt->isEnumeralType()) {
                const auto* et = qt->getAs<EnumType>();
                assert(et && "Could not get EnumType from Type");
                const auto* ed = et->getDecl();
                assert(ed && "Could not get EnumDecl from EnumType");
                ed = ed->getCanonicalDecl();
                assert(ed && "Could not get canonical EnumDecl from EnumType");

                // see if we've already processed an enum matching this type
                // and get its id if we have. If not we'll store -1 until we
                // come back and process the decl later.
                const std::string enum_qual_name =
                    ed->getQualifiedNameAsString();
                NodeId id_enum = -1;
                auto it_enum = NODE_MAP.find(enum_qual_name);
                if (it_enum != NODE_MAP.end()) {
                    id_enum = it_enum->second;
                }

                auto node_enum_type = std::make_unique<NodeEnumType>(
                    type_node_name, id, 0, type_name, id_enum);
                NODES.emplace_back(std::move(node_enum_type));
                NODE_MAP[type_node_name] = id;
            } else if (qt->isFunctionProtoType()) {
                const auto* fpt = qt->getAs<FunctionProtoType>();
                assert(fpt && "Could not get FunctionProtoType from QualType");

                id =
                    process_function_proto_type(fpt, type_name, type_node_name);
            } else if (const auto* pet = qt->getAs<PackExpansionType>()) {
                SPDLOG_WARN("Got PackExpansionType");
                id = NodeId(-1);
            } else {
                SPDLOG_WARN("Unhandled type {}", type_node_name);
                qt->dump();
                id = NodeId(-1);
            }
        } else {
            id = it->second;
        }

        return QType{id, qt.isConstQualified()};
    }
}

std::string get_decl_location(const Decl* d) {
    ASTContext& ctx = d->getASTContext();
    SourceManager& sm = ctx.getSourceManager();
    const auto& loc = d->getLocation();

    std::string filename = sm.getFilename(loc).str();
    return fmt::format("{}:{}", filename, sm.getSpellingLineNumber(loc));
}

/// Create nodes for the function return type and parameters
void process_function_parameters(const FunctionDecl* fd, QType& return_qtype,
                                 std::vector<Param>& params) {
    SPDLOG_TRACE("    -> {}", fd->getReturnType().getAsString());
    return_qtype = process_qtype(fd->getReturnType());
    if (return_qtype.ty == -1) {
        SPDLOG_ERROR("processing return type of FunctionDecl {} ({})",
                     fd->getQualifiedNameAsString(), get_decl_location(fd));
    }

    for (const ParmVarDecl* pvd : fd->parameters()) {
        int index = pvd->getFunctionScopeIndex();
        SPDLOG_TRACE("        {}: {}", pvd->getQualifiedNameAsString(),
                     pvd->getType().getCanonicalType().getAsString());
        QType qtype = process_qtype(pvd->getType());
        if (qtype.ty == -1) {
            SPDLOG_ERROR("processing parameter {}:{} of FunctionDecl {} ({})",
                         index, pvd->getNameAsString(),
                         fd->getQualifiedNameAsString(), get_decl_location(fd));
        }

        // handle unnamed parameters
        auto param_name = pvd->getNameAsString();
        if (param_name.empty()) {
            if (fd->getNumParams() == 1) {
                // if it's a single parameter call it "rhs" as we're probably in
                // a copy constructor or assignment operator etc.
                param_name = "rhs";
            } else {
                param_name = fmt::format("_param{}", index);
            }
        }

        params.emplace_back(Param{param_name, qtype, index, get_attrs(pvd)});

        if (const auto* vtd = pvd->getDescribedVarTemplate()) {
            SPDLOG_TRACE("            GOT VTD");
        }
        if (const auto* td = pvd->getDescribedTemplate()) {
            SPDLOG_TRACE("            GOT TD");
        }
    }
}

/// Create a new node for the given method decl and return it
NodePtr process_method_decl(const CXXMethodDecl* cmd,
                            std::vector<std::string> attrs,
                            bool is_specialization = false) {
    const std::string method_name = cmd->getQualifiedNameAsString();
    const std::string method_short_name = cmd->getNameAsString();

    QType return_qtype;
    std::vector<Param> params;
    process_function_parameters(cmd, return_qtype, params);

    auto node_function = std::make_unique<NodeMethod>(
        method_name, 0, 0, std::move(attrs), method_short_name, return_qtype,
        std::move(params), cmd->isStatic(), get_comment_base64(cmd));

    NodeMethod* m = (NodeMethod*)node_function.get();
    m->is_user_provided = cmd->isUserProvided();
    m->is_const = cmd->isConst();
    m->is_virtual = cmd->isVirtual();
    m->is_overloaded_operator = cmd->isOverloadedOperator();
    m->is_copy_assignment_operator = cmd->isCopyAssignmentOperator();
    m->is_move_assignment_operator = cmd->isMoveAssignmentOperator();
    m->is_noexcept = is_noexcept(cmd);

    if (const auto* ccd = dyn_cast<CXXConstructorDecl>(cmd)) {
        m->is_constructor = true;
        m->is_copy_constructor = ccd->isCopyConstructor();
        m->is_move_constructor = ccd->isMoveConstructor();
    } else if (const auto* cdd = dyn_cast<CXXDestructorDecl>(cmd)) {
        m->is_destructor = true;
    } else if (const auto* ccd = dyn_cast<CXXConversionDecl>(cmd)) {
        m->is_conversion_decl = true;
    }

    m->is_specialization = is_specialization;

    SPDLOG_TRACE("Processed method {}", *m);

    return node_function;
}
//
/// Determine if two functions are equivalent. Equivalent in this case means
/// that their return types and parameters are the same and they have the
/// same short (not qualified) name
bool match_function(const NodeFunction* a, const NodeFunction* b) {
    SPDLOG_TRACE("        matching {} with {}", a->qualified_name,
                 b->qualified_name);
    if (a->short_name != b->short_name) {
        return false;
    }

    if (a->return_type != b->return_type) {
        SPDLOG_TRACE("        match failed because return types do not match");
        return false;
    }

    if (a->params.size() != b->params.size()) {
        SPDLOG_TRACE(
            "        match failed because number of params do not match");
        return false;
    }

    for (int i = 0; i < a->params.size(); ++i) {
        if (a->params[i].qty != b->params[i].qty) {
            Node* n_a = NODES.at(a->params[i].qty.ty).get();
            Node* n_b = NODES.at(b->params[i].qty.ty).get();
            SPDLOG_TRACE("        match failed because param {} does "
                         "not match. {} {} != {} {}",
                         i, a->params[i].qty.ty, n_a->qualified_name,
                         b->params[i].qty.ty, n_b->qualified_name);
            return false;
        }
    }

    return true;
}

/// Determine if two methods are equivalent. In addition to function equivalence
/// this also checks whether the methods have the same const-ness and
/// static-ness
bool match_method(const NodeMethod* a, const NodeMethod* b) {

    if (a->is_const != b->is_const) {
        return false;
    }

    if (a->is_static != b->is_static) {
        return false;
    }

    if (a->is_specialization != b->is_specialization) {
        return false;
    }

    if (!match_function(a, b)) {
        return false;
    }

    return true;
}

void add_method_to_list(NodePtr method,
                        std::vector<NodePtr>& existing_methods) {
    auto it = std::find_if(existing_methods.begin(), existing_methods.end(),
                           [&](const NodePtr& em) {
                               return match_method((NodeMethod*)method.get(),
                                                   (NodeMethod*)em.get());
                           });
    if (it == existing_methods.end()) {
        existing_methods.emplace_back(std::move(method));
    } else {
        *it = std::move(method);
    }
}

/// Extract all the public methods on a decl and return them for later use.
/// The resulting methods are NOT inserted in the AST or stored in the global
/// node tables.
std::vector<NodePtr> process_methods(const CXXRecordDecl* crd, bool is_base) {
    std::vector<NodePtr> result;
    SPDLOG_TRACE("process_methods({})", get_record_name(crd));

    // get all the public base classes of this record, and process those methods
    SPDLOG_TRACE("class has {} bases", crd->getNumBases());
    for (const auto base : crd->bases()) {
        if (const CXXRecordDecl* base_crd =
                base.getType()->getAsCXXRecordDecl()) {
            SPDLOG_TRACE("found base {}", get_record_name(crd));
            auto base_methods = process_methods(base_crd, true);
            for (auto&& m : base_methods) {
                result.emplace_back(std::move(m));
            }
        }
    }

    // FIXME: need to replace existing methods from the base class
    // for overrides
    for (const Decl* d : crd->decls()) {
        // we want to ignore anything that's not public for obvious reasons
        // since we're using this function for getting methods both from the
        // library type and the binding type, this does mean we need to add a
        // "public" specifier to the binding type, but eh...
        if (d->getAccess() != AS_public) {
            continue;
        }

        // if we're processing a base class, ignore ctor/dtor
        if (is_base && (dyn_cast<CXXConstructorDecl>(d) ||
                        dyn_cast<CXXDestructorDecl>(d))) {
            continue;
        }

        // A FunctionTemplateDecl represents methods that are dependent on
        // their own template parameters (aside from the Record template
        // parameter list).
        if (const FunctionTemplateDecl* ftd =
                dyn_cast<FunctionTemplateDecl>(d)) {
            for (const FunctionDecl* fd : ftd->specializations()) {
                std::vector<std::string> attrs = get_attrs(fd);
                if (const auto* cmd = dyn_cast<CXXMethodDecl>(fd)) {
                    auto node_function = process_method_decl(cmd, attrs, true);
                    add_method_to_list(std::move(node_function), result);
                } else {
                    // shouldn't get here
                    assert(false && "method spec couldn't be converted to CMD");
                    const std::string function_name =
                        ftd->getQualifiedNameAsString();
                    const std::string method_short_name = fd->getNameAsString();
                    QType return_qtype;
                    std::vector<Param> params;
                    process_function_parameters(fd, return_qtype, params);

                    auto node_function = std::make_unique<NodeMethod>(
                        function_name, -1, -1, std::move(attrs),
                        method_short_name, return_qtype, std::move(params),
                        fd->isStatic(), get_comment_base64(ftd));
                    node_function->is_noexcept = is_noexcept(fd);
                    add_method_to_list(std::move(node_function), result);
                }
            }
        } else if (const auto* cmd = dyn_cast<CXXMethodDecl>(d)) {
            // just a regular boring old method
            std::vector<std::string> attrs = get_attrs(d);
            auto node_function = process_method_decl(cmd, attrs);
            add_method_to_list(std::move(node_function), result);
        }
    }

    return result;
}

/// Check if the given method, `m`, has an equivalent method in
/// `binding_methods` If `m` does match, its attrs field is set to `attrs`
/// FIXME: modifying m here is a bit nasty
bool method_in_list(NodeMethod* m, std::vector<NodePtr>& binding_methods,
                    std::vector<std::string>& attrs) {
    for (auto& n : binding_methods) {
        auto* b = (NodeMethod*)n.get();
        if (match_method(m, b)) {
            attrs = b->attrs;
            m->params = b->params;
            b->in_library = true;
            return true;
        }
    }
    SPDLOG_TRACE("Method {} did not match", m->qualified_name);
    return false;
}

/// Get the full set of namespaces (including parent records) that lead to
/// a given decl. The decl passed here is expected to be the *parent* of the
/// decl we care about, as in `get_namespaces(target_decl->getParent())`
std::vector<NodeId> get_namespaces(const clang::DeclContext* parent,
                                   NodeTranslationUnit* node_tu) {
    std::vector<NodeId> result;

    while (parent) {
        if (parent->isNamespace()) {
            const clang::NamespaceDecl* ns =
                static_cast<const clang::NamespaceDecl*>(parent);

            auto qualified_name = ns->getQualifiedNameAsString();
            auto short_name = ns->getNameAsString();
            if (short_name == "cppmm_bind") {
                break;
            }

            // see if there's an alias for this namespace already
            auto alias = short_name;
            bool collapse = false;
            auto it_alias = NAMESPACE_ALIASES.find(short_name);
            if (it_alias != NAMESPACE_ALIASES.end()) {
                alias = it_alias->second.first;
                collapse = it_alias->second.second;
            }

            // Add the id of this namespace to our list of namespaces, creating
            // a new NodeNamespace if it doesn't exist yet
            auto it = NODE_MAP.find(qualified_name);
            NodeId id;
            if (it == NODE_MAP.end()) {
                id = NODES.size();
                SPDLOG_TRACE("Inserting namespace {} woth id {}",
                             qualified_name, id);
                auto node = std::make_unique<NodeNamespace>(
                    qualified_name, id, 0, short_name, alias);
                node->collapse = collapse;
                NODES.emplace_back(std::move(node));
                NODE_MAP[qualified_name] = id;

            } else {
                id = it->second;
            }

            // add this node to the TU if it's not there already
            if (node_tu &&
                std::find(node_tu->children.begin(), node_tu->children.end(),
                          id) == node_tu->children.end()) {
                SPDLOG_TRACE("Adding namespace id {} to tu {}", id,
                             node_tu->qualified_name);
                node_tu->children.push_back(id);
            }
            result.push_back(id);

            parent = parent->getParent();
        } else if (parent->isRecord()) {
            // Parent is a Record type. We should have created the record
            // already by the time we get here...
            const clang::CXXRecordDecl* crd =
                static_cast<const clang::CXXRecordDecl*>(parent);

            auto record_name = get_record_name(crd);
            std::string mangled_name = mangle_decl(crd);
            auto it = NODE_MAP.find(mangled_name);
            if (it == NODE_MAP.end()) {
                SPDLOG_CRITICAL(
                    "Could not find record {} ({}) when processing namespaces",
                    record_name, mangled_name);
            } else {
                result.push_back(it->second);
            }

            parent = parent->getParent();
        } else {
            break;
        }
    }

    std::reverse(result.begin(), result.end());
    return result;
}

/// Create a NodeEnum for the given EnumDecl contained in the given file and
/// store it in the AST.
void process_enum_decl(const EnumDecl* ed, std::string filename) {
    ed = ed->getCanonicalDecl();
    assert(ed && "canonical decl is null");
    const std::string enum_name = ed->getQualifiedNameAsString();
    const std::string enum_short_name = ed->getNameAsString();

    if (NODE_MAP.find(enum_name) != NODE_MAP.end()) {
        // already done this one
        return;
    }

    // Get the translation unit node we're going to add this Enum to
    auto* node_tu = get_translation_unit(filename);
    const std::vector<NodeId> namespaces =
        get_namespaces(ed->getParent(), node_tu);
    ASTContext& ctx = ed->getASTContext();
    uint32_t size, align;
    if (!get_abi_info(dyn_cast<TypeDecl>(ed), ctx, size, align)) {
        SPDLOG_CRITICAL("Could not get ABI info for {}", enum_name);
    }

    std::vector<std::pair<std::string, std::string>> variants;
    for (const auto& ecd : ed->enumerators()) {
        SPDLOG_DEBUG("        {}", ecd->getNameAsString());
        variants.push_back(std::make_pair(ecd->getNameAsString(),
                                          ecd->getInitVal().toString(10)));
    }

    std::vector<std::string> attrs = get_attrs(ed);

    NodeId new_id = NODES.size();
    auto node_enum = std::make_unique<NodeEnum>(
        enum_name, new_id, 0, std::move(attrs), std::move(enum_short_name),
        std::move(namespaces), variants, size, align, get_comment_base64(ed));
    NODES.emplace_back(std::move(node_enum));
    NODE_MAP[enum_name] = new_id;
    // add this record to the TU
    node_tu->children.push_back(new_id);

    // Find any EnumType nodes that need the new id
    auto it_enum_type = NODE_MAP.find("TYPE:" + enum_name);
    if (it_enum_type != NODE_MAP.end()) {
        auto* node_enum_type =
            (NodeEnumType*)NODES.at(it_enum_type->second).get();
        node_enum_type->enm = new_id;
    }
}

/// Create a NodeVar for the given VarDecl contained in the given file and
/// store it in the AST.
void process_var_decl(const VarDecl* vd, std::string filename) {
    vd = vd->getCanonicalDecl();
    assert(vd && "canonical decl is null");
    const std::string var_name = vd->getQualifiedNameAsString();
    const std::string var_short_name = vd->getNameAsString();

    if (NODE_MAP.find(var_name) != NODE_MAP.end()) {
        // already done this one
        return;
    }

    std::vector<std::string> attrs = get_attrs(vd);

    auto qtype = process_qtype(vd->getType());
    if (qtype.ty == -1) {
        SPDLOG_ERROR("processing type of VarDecl {}",
                     vd->getQualifiedNameAsString());
    }

    // Get the translation unit node we're going to add this Var to
    auto* node_tu = get_translation_unit(filename);
    // const std::vector<NodeId> namespaces =
    //     get_namespaces(vd->getParent(), node_tu);
    std::vector<NodeId> namespaces{};
    ASTContext& ctx = vd->getASTContext();

    NodeId new_id = NODES.size();
    auto node_var = std::make_unique<NodeVar>(
        var_name, new_id, 0, std::move(attrs), std::move(var_short_name), qtype,
        get_comment_base64(vd));
    NODES.emplace_back(std::move(node_var));
    NODE_MAP[var_name] = new_id;
    // add this record to the TU
    node_tu->children.push_back(new_id);
}

void process_fields(const CXXRecordDecl* crd, NodeRecord* node_record_ptr) {
    // recurse through all bases and grab their fields
    for (const auto& base : crd->bases()) {
        if (const auto* base_crd = base.getType()->getAsCXXRecordDecl()) {
            process_fields(base_crd, node_record_ptr);
        }
    }

    // Now grab the fields for this decl
    for (const Decl* d : crd->decls()) {
        const auto record_name = get_record_name(crd);
        if (const auto* fd = dyn_cast<FieldDecl>(d)) {
            const std::string field_name = fd->getNameAsString();
            SPDLOG_TRACE("    FIELD {}::{}", record_name, field_name);
            QType qtype = process_qtype(fd->getType());
            node_record_ptr->fields.push_back(Field{field_name, qtype.ty});
        }
    }
}

std::unordered_map<std::string, std::string> pending_aliases;

void handle_typealias_decl(const TypeAliasDecl* tad, const CXXRecordDecl* crd) {
    std::string mangled_name = mangle_decl(crd);
    auto record_qualified_name = get_record_name(crd);
    auto alias_name = tad->getNameAsString();
    if (alias_name == "BoundType") {
        // skip this because it's the type "pointer" we use on the class
        // TODO AL - there's got to be a cleaner way of not getting this
        // in the first place - on the matcher?
        return;
    }

    // First of all, make sure we have already processed the Record that this
    // alias refers to. I *think* this should always have happened, but not sure
    // yet
    auto it = NODE_MAP.find(mangled_name);
    if (it == NODE_MAP.end()) {
        SPDLOG_DEBUG("Storing alias {} for {}", alias_name,
                     record_qualified_name);
        pending_aliases[mangled_name] = alias_name;
    } else {
        NodeId id_rec = it->second;
        NodeRecord* node_rec = (NodeRecord*)NODES[id_rec].get();
        node_rec->alias = alias_name;
    }
}

/// Create a new NodeRecord for the given record decl and store it in the AST.
/// `crd` must represent a "concrete" record - i.e. it must not be dependent
/// on any template parameters. This is done in the binding file by explicitly
/// instantiating a template decl with the desired parameters.
void process_concrete_record(const CXXRecordDecl* crd, std::string filename,
                             std::vector<std::string> attrs,
                             std::vector<NodePtr> binding_methods,
                             std::vector<std::string> child_enums) {
    ASTContext& ctx = crd->getASTContext();
    SourceManager& sm = ctx.getSourceManager();
    const auto& loc = crd->getLocation();

    const auto* can_rd =
        crd->getCanonicalDecl()
            ->getDefinition(); // TODO: this seems to do what we want... but
                               // does it? Can you imagine a world in which
                               // Clang was actually documented?
    if (can_rd != nullptr) {
        crd = can_rd;
    } else {
        SPDLOG_ERROR("Could not get canonical decl definition from {}",
                     crd->getQualifiedNameAsString());
        SPDLOG_ERROR("can def is {}", (void*)crd->getCanonicalDecl());
        crd->dump();
    }

    const std::string record_name = get_record_name(crd);
    const std::string short_name = crd->getNameAsString();

    SPDLOG_TRACE("Processing concrete record {}", record_name);

    // Get the translation unit node we're going to add this Record to
    auto* node_tu = get_translation_unit(filename);
    std::vector<NodeId> namespaces = get_namespaces(crd->getParent(), node_tu);

    // Get the size and alignment of the Record
    uint32_t size, align;
    if (!get_abi_info(dyn_cast<TypeDecl>(crd), ctx, size, align)) {
        SPDLOG_CRITICAL("Could not get ABI info for {}", record_name);
    }

    // Get the mangled version of the record name
    std::string mangled_name = mangle_decl(crd);
    SPDLOG_DEBUG("Record {} mangles to {}", crd->getQualifiedNameAsString(),
                 mangled_name);

    // Add the new Record node
    NodeId new_id = NODES.size();
    auto node_record = std::make_unique<NodeRecord>(
        record_name, new_id, node_tu->id, std::move(attrs),
        std::move(short_name), std::move(namespaces), RecordKind::OpaquePtr,
        crd->isAbstract(), crd->isTriviallyCopyable(), size, align,
        get_comment_base64(crd));

    auto* node_record_ptr = node_record.get();
    NODES.emplace_back(std::move(node_record));
    NODE_MAP[mangled_name] = new_id;

    // add this record to the TU
    node_tu->children.push_back(new_id);

    // grab all the methods that are specified in the binding
    std::vector<NodePtr> methods = process_methods(crd, false);
    SPDLOG_TRACE("record {} has {} methods", record_name, methods.size());
    for (NodePtr& method : methods) {
        NodeMethod* mptr = (NodeMethod*)method.get();
        if (method_in_list(mptr, binding_methods, attrs)) {
            mptr->attrs = std::move(attrs);
            mptr->in_binding = true;
        } else {
            // TODO: decide what we really want to do here.
            // For now, ignoring unmatched methods makes dev easier by cutting
            // out noise
            continue;
        }

        NodeId id = NODES.size();
        NODE_MAP[method->qualified_name] = id;
        NODES.emplace_back(std::move(method));
        node_record_ptr->methods.push_back(id);
    }

    if (WARN_UNMATCHED) {
        for (const auto& n : methods) {
            const auto* m = (NodeMethod*)n.get();
            if (m && !m->in_binding) {
                SPDLOG_WARN(
                    "Method {} is present in the library but not declared "
                    "in the binding",
                    *m);
            }
        }

        for (const auto& n : binding_methods) {
            const auto* m = (NodeMethod*)n.get();
            if (m && m->is_user_provided && !m->in_library) {
                SPDLOG_WARN(
                    "Method {} is declared in the binding but not present "
                    "in the library",
                    *m);
            }
        }
    }
    // process remaining children
    // first process (recursively) the fields from this decl and all bases
    process_fields(crd, node_record_ptr);

    // now get other child decls
    for (const Decl* d : crd->decls()) {
        if (const auto* md = dyn_cast<CXXMethodDecl>(d)) {
            // pass
        } else if (const auto* fd = dyn_cast<FunctionDecl>(d)) {
            SPDLOG_TRACE(" FUNCTION {}", fd->getQualifiedNameAsString());
        } else if (const auto* ed = dyn_cast<EnumDecl>(d)) {
            SPDLOG_TRACE("Got enum decl {}", ed->getNameAsString());
            if (std::find(child_enums.begin(), child_enums.end(),
                          ed->getNameAsString()) != child_enums.end()) {
                process_enum_decl(ed, filename);
            }
        }
    }

    // Finally...
    // if there's an existing RecordType node referring to this Record, then
    // set its record id to our new id
    auto it_record_type = NODE_MAP.find("TYPE:" + mangled_name);
    if (it_record_type != NODE_MAP.end()) {
        auto* node_record_type =
            (NodeRecordType*)NODES.at(it_record_type->second).get();
        node_record_type->record = new_id;
    }

    // and if we have a pending alias rename for this record, set it
    auto alias_it = pending_aliases.find(mangled_name);
    if (alias_it != pending_aliases.end()) {
        SPDLOG_DEBUG("Found alias {} for {}", alias_it->second, record_name);
        node_record_ptr->alias = alias_it->second;
    } else {
        SPDLOG_TRACE("No alias found for {}", record_name);
    }
}

/// This function handles a CXXRecordDecl match. This will be called with the
/// Record from the binding file, so we need to do a bit of preprocessing to
/// make sure it's the right kind, then get the actual type we're interested in
/// from the library by inspecting the `using BoundType = XXX` decl on this
/// Record. We'll also need to get any attributes from here, as well as
/// pre-generating a list of matched methods
void handle_cxx_record_decl(const CXXRecordDecl* crd) {
    ASTContext& ctx = crd->getASTContext();
    SourceManager& sm = ctx.getSourceManager();
    const auto& loc = crd->getLocation();

    const auto mng_ctx = ctx.createMangleContext();

    crd = dyn_cast<CXXRecordDecl>(crd->getCanonicalDecl());
    if (crd == nullptr) {
        SPDLOG_ERROR("Could not get canonical decl from CXRecordDecl");
    }

    std::string filename = sm.getFilename(loc).str();

    SPDLOG_DEBUG("CXXRecordDecl {:p} {} ({}:{})", (void*)crd,
                 crd->getQualifiedNameAsString(), filename,
                 sm.getSpellingLineNumber(loc));

    const clang::Type* ty = crd->getTypeForDecl();
    if (ty->isIncompleteType()) {
        // We can't process an incomplete type
        SPDLOG_DEBUG("    incomplete");
        return;
    } else if (ty->isDependentType()) {
        // type is dependent on a template parameter
        // this probably means it's the template definition, which we want to
        // ignore and have the user explicitly instantiate the types they want
        if (const ClassTemplateDecl* ctd = crd->getDescribedClassTemplate()) {
            SPDLOG_DEBUG("    dependent on {:p}", (void*)ctd);
        } else {
            SPDLOG_DEBUG("    dependent on unknown?");
        }
        return;
    }

    // if we get down here then we have a concrete, sized type we can
    // process

    // first get the attrs
    std::vector<std::string> attrs = get_attrs(crd);

    // now get the methods so we can match
    std::vector<NodePtr> methods = process_methods(crd, false);
    for (const auto& n : methods) {
        const auto& m = *(NodeMethod*)n.get();
        SPDLOG_DEBUG("Adding binding method {}", m);
    }

    // see if there's a BoundType typedef, and if so process the type that it
    // points to instead
    std::vector<std::string> child_enums;
    const CXXRecordDecl* bound_rd = nullptr;
    for (const auto* decl : crd->decls()) {
        if (const auto* tad = dyn_cast<TypeAliasDecl>(decl)) {
            SPDLOG_DEBUG("TAD {}", tad->getNameAsString());
            const auto* bound_nd = tad->getUnderlyingDecl();
            if (tad->getNameAsString() == "BoundType") {
                bound_rd = tad->getUnderlyingType()->getAsCXXRecordDecl();
                // std::string s;
                // llvm::raw_string_ostream os(s);
                // mng_ctx->mangleCXXName(bound_rd, os);
                // auto mangled_name = os.str();
                std::string mangled_name = mangle_decl(bound_rd);
                SPDLOG_DEBUG(
                    "Found BoundType {}\n    - {}\n    - {}",
                    get_record_name(bound_rd),
                    bound_rd->getCanonicalDecl()->getQualifiedNameAsString(),
                    mangled_name);
            }
        } else if (const auto* ed = dyn_cast<EnumDecl>(decl)) {
            // this gets `using Enum = Library::Class::Enum`
            SPDLOG_DEBUG("got bound enum decl {}",
                         ed->getQualifiedNameAsString());
            child_enums.push_back(ed->getNameAsString());
        }
    }

    if (bound_rd) {
        process_concrete_record(bound_rd, filename, std::move(attrs),
                                std::move(methods), std::move(child_enums));
        return;
    }

    // Don't *think* we should ever get here, but we'll leave this log in in
    // case we do because we'll want to figure out what case we didn't consider
    SPDLOG_CRITICAL("Fell through on handle_cxx_record");
    crd->dump();
}

std::unordered_map<std::string, std::vector<NodeFunction>> binding_functions;
std::unordered_map<std::string, NodeEnum> binding_enums;
std::unordered_map<std::string, NodeVar> binding_vars;

/// This function is responsible for storing the description of the given
/// FunctionDecl so that we can match against it later. Only functions that
/// are explicitly declared in the bindings have AST output for them.
void handle_binding_function(const FunctionDecl* fd) {
    const std::string function_qual_name =
        pystring::replace(fd->getQualifiedNameAsString(), "cppmm_bind::", "");
    const std::string function_short_name = fd->getNameAsString();
    SPDLOG_DEBUG("    BIND FUNCTION {}", function_qual_name);

    ASTContext& ctx = fd->getASTContext();
    SourceManager& sm = ctx.getSourceManager();
    const auto& loc = fd->getLocation();
    std::string filename = sm.getFilename(loc).str();

    // Get the translation unit node we're going to add this Function to
    auto* node_tu = get_translation_unit(filename);

    auto attrs = get_attrs(fd);

    QType return_qtype;
    std::vector<Param> params;
    process_function_parameters(fd, return_qtype, params);
    // NodeId id = NODES.size();

    const std::vector<NodeId> namespaces =
        get_namespaces(fd->getParent(), node_tu);

    auto it = binding_functions.find(function_qual_name);
    auto node_function =
        NodeFunction(function_qual_name, 0, node_tu->id, std::move(attrs),
                     function_short_name, return_qtype, std::move(params),
                     std::move(namespaces), get_comment_base64(fd));

    SPDLOG_DEBUG("Adding binding function {}", node_function);

    if (it != binding_functions.end()) {
        it->second.emplace_back(std::move(node_function));
    } else {
        binding_functions[function_qual_name] = {node_function};
    }
}

/// Store a description of the given EnumDecl so we can match it against a
/// corresponding decl in the library later to decide whether we want to
/// process said library decl
void handle_binding_enum(const EnumDecl* ed) {
    const std::string enum_qual_name =
        pystring::replace(ed->getQualifiedNameAsString(), "cppmm_bind::", "");
    const std::string enum_short_name = ed->getNameAsString();
    SPDLOG_DEBUG("    BIND ENUM {}", enum_qual_name);

    ASTContext& ctx = ed->getASTContext();
    SourceManager& sm = ctx.getSourceManager();
    const auto& loc = ed->getLocation();
    std::string filename = sm.getFilename(loc).str();

    // Get the translation unit node we're going to add this Enum to
    auto* node_tu = get_translation_unit(filename);

    auto attrs = get_attrs(ed);

    auto node_enum =
        NodeEnum(enum_qual_name, -1, node_tu->id, std::move(attrs),
                 enum_short_name, {}, {}, 0, 0, get_comment_base64(ed));
    binding_enums.insert(std::make_pair(enum_qual_name, std::move(node_enum)));
}

/// Store a description of the given VarDecl so we can match it against a
/// corresponding decl in the library later to decide whether we want to
/// process said library decl
void handle_binding_var(const VarDecl* vd) {
    const std::string var_qual_name =
        pystring::replace(vd->getQualifiedNameAsString(), "cppmm_bind::", "");
    const std::string var_short_name = vd->getNameAsString();
    SPDLOG_DEBUG("    BIND VAR {}", var_qual_name);

    ASTContext& ctx = vd->getASTContext();
    SourceManager& sm = ctx.getSourceManager();
    const auto& loc = vd->getLocation();
    std::string filename = sm.getFilename(loc).str();

    // Get the translation unit node we're going to add this Enum to
    auto* node_tu = get_translation_unit(filename);

    auto attrs = get_attrs(vd);

    auto qtype = process_qtype(vd->getType());
    if (qtype.ty == -1) {
        SPDLOG_ERROR("processing type of VarDecl {}",
                     vd->getQualifiedNameAsString());
    }

    auto node_var = NodeVar(var_qual_name, -1, node_tu->id, std::move(attrs),
                            var_short_name, qtype, get_comment_base64(vd));
    binding_vars.insert(std::make_pair(var_qual_name, std::move(node_var)));
}

/// Decide if we want to store the given library FunctionDecl in the AST by
/// matching it against a decl from the bindings. If so, create the new
/// NodeFunction and store it in the AST
void handle_library_function(const FunctionDecl* fd) {
    const std::string function_qual_name = fd->getQualifiedNameAsString();
    const std::string function_short_name = fd->getNameAsString();

    auto it = binding_functions.find(function_qual_name);
    if (it == binding_functions.end()) {
        SPDLOG_TRACE(
            "function {} matched but is not present in binding functions table",
            function_qual_name);
        return;
    }

    QType return_qtype;
    std::vector<Param> params;
    process_function_parameters(fd, return_qtype, params);

    const std::vector<NodeId> namespaces =
        get_namespaces(fd->getParent(), nullptr);
    auto node_function = NodeFunction(
        function_qual_name, 0, 0, {}, function_short_name, return_qtype,
        std::move(params), std::move(namespaces), get_comment_base64(fd));
    node_function.is_noexcept = is_noexcept(fd);

    // find a match in the overloads
    for (auto& binding_fn : it->second) {
        if (!binding_fn.processed &&
            match_function(&node_function, &binding_fn)) {
            // we have a match. copy over the attributes and store this function
            node_function.attrs = binding_fn.attrs;
            node_function.context = binding_fn.context;
            auto fnptr =
                std::make_unique<NodeFunction>(std::move(node_function));
            NodeId id = NODES.size();
            fnptr->id = id;
            // add the function to its TU
            SPDLOG_DEBUG("MATCHED {}", function_qual_name);
            auto* node_tu =
                (NodeTranslationUnit*)NODES.at(node_function.context).get();
            // process the namespaces again to make sure we've got the
            // namespaces in the TU
            const std::vector<NodeId> namespaces =
                get_namespaces(fd->getParent(), node_tu);
            fnptr->context = node_tu->id;
            node_tu->children.push_back(id);
            NODES.emplace_back(std::move(fnptr));
            binding_fn.processed = true;
        }
    }
}

/// Decide if we want to store the given library EnumDecl in the AST by
/// matching it against a decl from the bindings. If so, create the new NodeEnum
/// and store it in the AST
void handle_library_enum(const EnumDecl* ed) {
    const std::string enum_qual_name = ed->getQualifiedNameAsString();
    auto it = binding_enums.find(enum_qual_name);
    if (it == binding_enums.end()) {
        return;
    }

    const std::string filename =
        ((NodeTranslationUnit*)NODES.at(it->second.context).get())
            ->qualified_name;

    process_enum_decl(ed, std::move(filename));
}

/// Decide if we want to store the given library VarDecl in the AST by
/// matching it against a decl from the bindings. If so, create the new NodeVar
/// and store it in the AST
void handle_library_var(const VarDecl* vd) {
    const std::string var_qual_name = vd->getQualifiedNameAsString();
    auto it = binding_vars.find(var_qual_name);
    if (it == binding_vars.end()) {
        return;
    }

    const std::string filename =
        ((NodeTranslationUnit*)NODES.at(it->second.context).get())
            ->qualified_name;

    process_var_decl(vd, std::move(filename));
}

void handle_function_pointer_typedef(const QualType& ty,
                                     const TypedefNameDecl* tdd) {
    tdd = tdd->getCanonicalDecl();
    const auto qname = tdd->getQualifiedNameAsString();
    const auto* fpt = ty->getPointeeType()->getAs<FunctionProtoType>();

    const auto fp_name = ty->getPointeeType().getAsString();

    const auto it = NODE_MAP.find(fp_name);
    if (it != NODE_MAP.end()) {
        return;
    }

    ASTContext& ctx = tdd->getASTContext();
    SourceManager& sm = ctx.getSourceManager();
    const auto& loc = tdd->getLocation();
    std::string filename = sm.getFilename(loc).str();

    // Get the translation unit node we're going to add this function pointer to
    auto* node_tu = get_translation_unit(filename);
    SPDLOG_DEBUG("Got FPT Typedef {} -> {} in {}", fp_name, qname,
                 (void*)node_tu);

    auto decl_ctx = tdd->getDeclContext();

    auto namespaces = get_namespaces(decl_ctx, node_tu);

    QType return_type = process_qtype(fpt->getReturnType());
    if (return_type.ty == -1) {
        SPDLOG_ERROR("processing return type of FunctionPointerTypedef {}",
                     qname);
    }
    std::vector<QType> params;
    for (const QualType& pqt : fpt->param_types()) {
        auto qtype = process_qtype(pqt);
        params.push_back(qtype);
        if (qtype.ty == -1) {
            SPDLOG_ERROR("processing param of FunctionPointerTypedef {}",
                         qname);
        }
    }

    const auto id = NODES.size();
    auto node_fpt = std::make_unique<NodeFunctionPointerTypedef>(
        qname, id, -1, std::vector<std::string>{}, tdd->getNameAsString(),
        namespaces, get_comment_base64(tdd), return_type, params);
    NODES.emplace_back(std::move(node_fpt));
    NODE_MAP[fp_name] = id;

    node_tu->children.push_back(id);
}

/// Clang AST matcher that matches on the decls we're interested in in the
/// bindings and dispatches to our handling functions
void ProcessBindingCallback::run(const MatchFinder::MatchResult& result) {
    if (const CXXRecordDecl* rec_decl =
            result.Nodes.getNodeAs<CXXRecordDecl>("recordDecl")) {
        handle_cxx_record_decl(rec_decl);
    } else if (const TypeAliasDecl* tad =
                   result.Nodes.getNodeAs<TypeAliasDecl>("typeAliasDecl")) {
        if (const auto* crd = tad->getUnderlyingType()->getAsCXXRecordDecl()) {
            handle_typealias_decl(tad, crd);
        } else {
            // SPDLOG_DEBUG("Got other TAD");
            // tad->dump();
            QualType ty = tad->getUnderlyingType();
            if (ty->isPointerType() &&
                ty->getPointeeType()->isFunctionProtoType()) {
                FPT_TYPEDEFS[ty->getPointeeType().getAsString()] =
                    tad->getNameAsString();
                handle_function_pointer_typedef(ty, tad);
            }
        }
    } else if (const auto* tdd =
                   result.Nodes.getNodeAs<TypedefDecl>("typedefDecl")) {
        SPDLOG_DEBUG("Got TDD");
        tdd->dump();
        QualType ty = tdd->getUnderlyingType();
        if (ty->isPointerType() &&
            ty->getPointeeType()->isFunctionProtoType()) {
            FPT_TYPEDEFS[ty->getPointeeType().getAsString()] =
                tdd->getNameAsString();
            handle_function_pointer_typedef(ty, tdd);
        }

    } else if (const FunctionDecl* function =
                   result.Nodes.getNodeAs<FunctionDecl>("functionDecl")) {
        handle_binding_function(function);
    } else if (const EnumDecl* enum_decl =
                   result.Nodes.getNodeAs<EnumDecl>("enumDecl")) {
        handle_binding_enum(enum_decl);
    } else if (const VarDecl* var_decl =
                   result.Nodes.getNodeAs<VarDecl>("varDecl")) {
        handle_binding_var(var_decl);
    } else if (const auto* nad = result.Nodes.getNodeAs<NamespaceAliasDecl>(
                   "namespaceAliasDecl")) {
        const auto alias = nad->getNameAsString();
        const auto short_name = nad->getNamespace()->getNameAsString();
        // if the namespace we're targeting is a child namespace, then assume
        // we want to collapse that down to a single namespace
        const auto collapse = nad->getNamespace()->getParent() &&
                              nad->getNamespace()->getParent()->isNamespace();
        NAMESPACE_ALIASES[short_name] = std::make_pair(alias, collapse);

        // iterate over all namespaces we've created so far and add the alias to
        // them
        for (auto& node : NODES) {
            if (node->node_kind == NodeKind::Namespace) {
                auto* node_ns = static_cast<NodeNamespace*>(node.get());
                if (node_ns->short_name == short_name) {
                    node_ns->alias = alias;
                    node_ns->collapse = collapse;
                }
            }
        }
    }
}

/// Clang AST matcher that matches on the decls we're interested in in the
/// library and dispatches to our handling functions
void ProcessLibraryCallback::run(const MatchFinder::MatchResult& result) {
    if (const FunctionDecl* fd =
            result.Nodes.getNodeAs<FunctionDecl>("libraryFunctionDecl")) {
        handle_library_function(fd);
    } else if (const EnumDecl* ed =
                   result.Nodes.getNodeAs<EnumDecl>("libraryEnumDecl")) {
        handle_library_enum(ed);
    } else if (const VarDecl* vd =
                   result.Nodes.getNodeAs<VarDecl>("libraryVarDecl")) {
        handle_library_var(vd);
    }
}

ProcessBindingConsumer::ProcessBindingConsumer(ASTContext* context) {
    // match all record declrations in the cppmm_bind namespace
    DeclarationMatcher record_decl_matcher =
        cxxRecordDecl(hasAncestor(namespaceDecl(hasName("cppmm_bind"))),
                      unless(isImplicit()))
            .bind("recordDecl");
    _match_finder.addMatcher(record_decl_matcher, &_handler);

    // match all typedef declrations in the cppmm_bind namespace
    DeclarationMatcher type_alias_decl_matcher =
        typeAliasDecl(hasAncestor(namespaceDecl(hasName("cppmm_bind"))),
                      unless(hasAncestor(recordDecl())), unless(isImplicit()))
            .bind("typeAliasDecl");
    _match_finder.addMatcher(type_alias_decl_matcher, &_handler);

    DeclarationMatcher typedef_decl_matcher =
        typedefDecl(hasAncestor(namespaceDecl(hasName("cppmm_bind"))),
                    unless(hasAncestor(recordDecl())), unless(isImplicit()))
            .bind("typedefDecl");
    _match_finder.addMatcher(typedef_decl_matcher, &_handler);

    // match all function declarations
    DeclarationMatcher function_decl_matcher =
        functionDecl(hasAncestor(namespaceDecl(hasName("cppmm_bind"))),
                     unless(hasAncestor(recordDecl())))
            .bind("functionDecl");
    _match_finder.addMatcher(function_decl_matcher, &_handler);

    // match all enum declrations in the cppmm_bind namespace
    DeclarationMatcher enum_decl_matcher =
        enumDecl(hasAncestor(namespaceDecl(hasName("cppmm_bind"))),
                 unless(isImplicit()))
            .bind("enumDecl");
    _match_finder.addMatcher(enum_decl_matcher, &_handler);

    // match all variable declrations in the cppmm_bind namespace
    DeclarationMatcher var_decl_matcher =
        varDecl(hasAncestor(namespaceDecl(hasName("cppmm_bind"))),
                unless(anyOf(isImplicit(), parmVarDecl())))
            .bind("varDecl");
    _match_finder.addMatcher(var_decl_matcher, &_handler);

    // match all namespace alias declrations in the cppmm_bind namespace
    DeclarationMatcher namespace_alias_decl_matcher =
        namespaceAliasDecl(hasAncestor(namespaceDecl(hasName("cppmm_bind"))),
                           unless(anyOf(isImplicit(), parmVarDecl())))
            .bind("namespaceAliasDecl");
    _match_finder.addMatcher(namespace_alias_decl_matcher, &_handler);
}

/// Run the binding AST matcher, then run secondary matchers to find functions
/// and enums we're interested in from the bindings (stored in the first pass)
void ProcessBindingConsumer::HandleTranslationUnit(ASTContext& context) {
    _match_finder.matchAST(context);
    SPDLOG_DEBUG("--- finished matching");
    for (const auto& fn : binding_functions) {
        SPDLOG_DEBUG("    {}", fn.first);
    }

    // add a matcher for each function we found in the binding
    for (const auto& kv : binding_functions) {
        for (const auto& fn : kv.second) {
            SPDLOG_DEBUG("Adding matcher for function {}", fn.short_name);
            DeclarationMatcher function_decl_matcher =
                functionDecl(
                    hasName(fn.short_name),
                    unless(hasAncestor(namespaceDecl(hasName("cppmm_bind")))),
                    unless(hasAncestor(recordDecl())))
                    .bind("libraryFunctionDecl");
            _library_finder.addMatcher(function_decl_matcher,
                                       &_library_handler);
        }
    }

    // and a matcher for each enum
    for (const auto& kv : binding_enums) {
        SPDLOG_DEBUG("Adding matcher for enum {}", kv.first);
        DeclarationMatcher enum_decl_matcher =
            enumDecl(hasName(kv.second.short_name),
                     unless(hasAncestor(namespaceDecl(hasName("cppmm_bind")))),
                     unless(hasAncestor(recordDecl())))
                .bind("libraryEnumDecl");
        _library_finder.addMatcher(enum_decl_matcher, &_library_handler);
    }

    // and a matcher for each var
    for (const auto& kv : binding_vars) {
        SPDLOG_DEBUG("Adding matcher for var {}", kv.first);
        DeclarationMatcher var_decl_matcher =
            varDecl(hasName(kv.second.short_name),
                    unless(hasAncestor(namespaceDecl(hasName("cppmm_bind")))))
                .bind("libraryVarDecl");
        _library_finder.addMatcher(var_decl_matcher, &_library_handler);
    }

    _library_finder.matchAST(context);
}

} // namespace cppmm
