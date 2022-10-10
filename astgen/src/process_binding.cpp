#include "process_binding.hpp"
#include "pystring.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/Decl.h"
#include "clang/AST/PrettyPrinter.h"
#include "clang/AST/DeclCXX.h"
#include "clang/AST/DeclTemplate.h"
#include "clang/AST/GlobalDecl.h"
#include "clang/AST/Mangle.h"
#include "clang/AST/Type.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/Basic/LLVM.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/raw_ostream.h"
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
#include "base64.hpp"

using namespace clang;
using namespace clang::ast_matchers;
namespace ps = pystring;

extern std::unordered_map<std::string, std::vector<std::string>>
    source_includes;
extern std::vector<std::string> project_includes;

bool WARN_UNMATCHED = false;

namespace cppmm {

std::unordered_map<uint64_t, NodeFunction*> function_map;
std::unordered_map<std::string, unsigned int> EXCEPTION_MAP;
unsigned int EXCEPTION_CODE = 1;

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
                dyn_cast<ConstantArrayType>(qt.getCanonicalType().getTypePtr());
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
            QType pointee_qtype = process_qtype(qt->getPointeeType());

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

        // FIXME: hack to work around unsigned long being different sizes on
        // windows and *nix
        if (qt->isBuiltinType() && type_name == "unsigned long") {
            const auto* tdt = qt->getAs<TypedefType>();
            if (tdt && tdt->getDecl()->getNameAsString() == "uint64_t") {
                type_name = "uint64_t";
                type_node_name = "TYPE:uint64_t";
            } else if (tdt && tdt->getDecl()->getNameAsString() == "size_t") {
                type_name = "size_t";
                type_node_name = "TYPE:size_t";
            } else if (tdt &&
                       tdt->getDecl()->getNameAsString() == "size_type") {
                // FIXME: Nasty hack here to get e.g. std::string::size_type
                // will this bite us?
                type_name = "size_t";
                type_node_name = "TYPE:size_t";
            } else if (tdt) {
                /* SPDLOG_WARN("Unhandled unsigned long typedef {}",
                 * tdt->getDecl()->getNameAsString()); */
                // If we're some other typedef of unsigned long, try desugaring
                // recursively until we get to a typedef we can handle
                QualType ds_type = tdt->desugar();
                return process_qtype(ds_type);
            }
        } else if (qt->isBuiltinType() && type_name == "long") {
            const auto* tdt = qt->getAs<TypedefType>();
            if (tdt && tdt->getDecl()->getNameAsString() == "int64_t") {
                type_name = "int64_t";
                type_node_name = "TYPE:int64_t";
            } else if (tdt &&
                       tdt->getDecl()->getNameAsString() == "ptrdiff_t") {
                type_name = "ptrdiff_t";
                type_node_name = "TYPE:ptrdiff_t";
            }
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

bool match_parameters(const NodeFunction* a, const NodeFunction* b) {
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
                         "not match. \n{} ({}) != \n{} ({})",
                         i, n_a->qualified_name, a->params[i].qty.ty,
                         n_b->qualified_name, b->params[i].qty.ty);
            return false;
        }
    }

    return true;
}

std::vector<QType> get_template_args(const FunctionDecl* fd) {
    std::vector<QType> result;

    const auto* tal = fd->getTemplateSpecializationArgs();
    if (tal) {
        for (int i = 0; i < tal->size(); ++i) {
            // FIXME: we're just ignoring non-type template arguments here which
            // will surely bite us one day
            if (tal->get(i).getKind() == TemplateArgument::ArgKind::Type) {
                result.push_back(process_qtype(tal->get(i).getAsType()));
            }
        }
    }
    return result;
}

std::vector<Exception> get_exceptions(const std::vector<std::string>& attrs) {
    std::vector<std::string> toks;
    toks.reserve(4);
    std::vector<Exception> result;
    for (const auto& a : attrs) {
        ps::split(a, toks, "|");
        if (toks.size() == 4 && toks[0] == "cppmm" && toks[1] == "throws") {
            auto cpp_name = toks[2];
            auto c_name = toks[3];
            unsigned error_code = -1;
            auto it = EXCEPTION_MAP.find(c_name);
            if (it == EXCEPTION_MAP.end()) {
                error_code = EXCEPTION_CODE++;
                EXCEPTION_MAP[c_name] = error_code;
            } else {
                error_code = it->second;
            }

            result.push_back(Exception{cpp_name, c_name, error_code});
        }
    }

    return result;
}

bool has_noexcept_attr(const std::vector<std::string>& attrs) {
    return std::find(attrs.begin(), attrs.end(), "cppmm|noexcept") !=
           attrs.end();
}

bool has_copy_ctor_attr(const std::vector<std::string>& attrs) {
    return std::find(attrs.begin(), attrs.end(), "cppmm|copy_constructor") !=
           attrs.end();
}

bool has_move_ctor_attr(const std::vector<std::string>& attrs) {
    return std::find(attrs.begin(), attrs.end(), "cppmm|move_constructor") !=
           attrs.end();
}

bool has_manual_attr(const std::vector<std::string>& attrs) {
    return std::find(attrs.begin(), attrs.end(), "cppmm|manual") != attrs.end();
}

/// Create a new node for the given method decl and return it
NodePtr process_method_decl(const CXXMethodDecl* cmd,
                            std::vector<std::string> attrs,
                            const CXXRecordDecl* final_crd,
                            bool is_specialization = false) {
    const std::string method_name = cmd->getQualifiedNameAsString();
    const std::string method_short_name = cmd->getNameAsString();

    QType return_qtype;
    std::vector<Param> params;
    process_function_parameters(cmd, return_qtype, params);

    auto exceptions = get_exceptions(attrs);

    auto node_function = std::make_unique<NodeMethod>(
        method_name, 0, 0, std::move(attrs), method_short_name, return_qtype,
        std::move(params), cmd->isStatic(), get_comment_base64(cmd),
        std::move(exceptions));

    NodeMethod* m = (NodeMethod*)node_function.get();
    m->is_user_provided = cmd->isUserProvided();
    m->is_const = cmd->isConst();
    m->is_virtual = cmd->isVirtual();
    m->is_overloaded_operator = cmd->isOverloadedOperator();
    m->is_copy_assignment_operator = cmd->isCopyAssignmentOperator();
    m->is_move_assignment_operator = cmd->isMoveAssignmentOperator();
    m->is_noexcept = is_noexcept(cmd);
    m->is_deleted = cmd->isDeleted();
    m->_function_id = (uint64_t)cmd;
    m->template_args = get_template_args(cmd);

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

    if (final_crd) {
        // check if this method is shadowed in the final derived class
        const auto* dcmd = cmd->getCorrespondingMethodInClass(final_crd);
        if (dcmd) {
            NodePtr dm = process_method_decl(dcmd, {}, nullptr, false);
            if (!match_parameters(m, (NodeMethod*)dm.get())) {
                m->is_shadowed = true;
                SPDLOG_DEBUG("Method {} is shadowed", *m);
            }
        }
    }

    SPDLOG_DEBUG("Processed method {}", *m);

    return node_function;
}

/// Determine if two functions are equivalent. Equivalent in this case means
/// that their return types and parameters are the same and they have the
/// same short (not qualified) name
bool match_function(const NodeFunction* a, const NodeFunction* b) {
    SPDLOG_TRACE("        matching:\n     [lib] {}\n    with\n     [bin] {}",
                 *a, *b);
    if (a->short_name != b->short_name) {
        return false;
    }

    bool matched = match_parameters(a, b);
    if (matched) {
        SPDLOG_TRACE("    MATCHED");
    }
    return matched;
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

    // if (a->is_specialization != b->is_specialization) {
    //     return false;
    // }

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
std::vector<NodePtr> process_methods(const CXXRecordDecl* crd, bool is_base,
                                     const CXXRecordDecl* final_crd) {
    std::vector<NodePtr> result;
    SPDLOG_TRACE("process_methods({})", get_record_name(crd));

    // get all the public base classes of this record, and process those methods
    SPDLOG_TRACE("class has {} bases", crd->getNumBases());
    for (const auto base : crd->bases()) {
        if (const CXXRecordDecl* base_crd =
                base.getType()->getAsCXXRecordDecl()) {
            SPDLOG_TRACE("found base {}", get_record_name(crd));
            auto base_methods =
                process_methods(base_crd, true, final_crd ? final_crd : crd);
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
                    SPDLOG_DEBUG("FTSD {}: {}", cmd->getQualifiedNameAsString(),
                                 (void*)cmd);
                    auto node_function =
                        process_method_decl(cmd, attrs, final_crd, true);
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
                    auto exceptions = get_exceptions(attrs);

                    auto node_function = std::make_unique<NodeMethod>(
                        function_name, -1, -1, std::move(attrs),
                        method_short_name, return_qtype, std::move(params),
                        fd->isStatic(), get_comment_base64(ftd),
                        std::move(exceptions));
                    node_function->is_noexcept = is_noexcept(fd);
                    add_method_to_list(std::move(node_function), result);
                }
            }
        } else if (const auto* cmd = dyn_cast<CXXMethodDecl>(d)) {
            SPDLOG_DEBUG("CMD {}: {}", cmd->getQualifiedNameAsString(),
                         (void*)cmd);
            if (is_base && cmd->isCopyAssignmentOperator() ||
                cmd->isMoveAssignmentOperator()) {
                continue;
            }

            // just a regular boring old method
            std::vector<std::string> attrs = get_attrs(d);
            auto node_function = process_method_decl(cmd, attrs, final_crd);
            add_method_to_list(std::move(node_function), result);
        }
    }

    return result;
} // namespace cppmm

/// Check if the given method, `m`, has an equivalent method in
/// `binding_methods` If `m` does match, its attrs field is set to `attrs`
/// FIXME: modifying m here is a bit nasty
bool method_in_list(NodeMethod* m, std::vector<NodePtr>& binding_methods,
                    std::vector<std::string>& attrs) {
    for (auto& n : binding_methods) {
        auto* b = (NodeMethod*)n.get();
        if (match_method(m, b)) {
            if (m->is_deleted && !b->is_deleted) {
                SPDLOG_WARN("Method {} is specified in the binding but is "
                            "deleted in the library.",
                            *b);
            } else {
                attrs = b->attrs;
                m->params = b->params;
                m->_function_id = b->_function_id;
                b->in_library = true;
                m->exceptions = b->exceptions;
                return true;
            }
        }
    }
    SPDLOG_DEBUG("Method {} did not match", m->qualified_name);
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
                throw std::runtime_error("whut");
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
                                          std::to_string(ecd->getInitVal().getExtValue())));
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

void process_library_enum_decl(const EnumDecl* ed, std::string filename,
                               NodeEnum& binding_enum) {
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
                                          std::to_string(ecd->getInitVal().getExtValue())));
    }

    NodeId new_id = NODES.size();
    auto node_enum = std::make_unique<NodeEnum>(
        enum_name, new_id, 0, binding_enum.attrs, std::move(enum_short_name),
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

            if (fd->getAccess() != AccessSpecifier::AS_public) {
                // don't want to inspect private fields as they may involve
                // types we don't care about
                continue;
            }
            const std::string field_name = fd->getNameAsString();
            SPDLOG_TRACE("    FIELD {}::{}", record_name, field_name);
            QType qtype = process_qtype(fd->getType());
            if (qtype.ty == -1) {
                SPDLOG_ERROR("processing field {} of CXXRecordDecl {}",
                             field_name, crd->getQualifiedNameAsString());
            }

            auto attrs = get_attrs(fd);
            Field f;
            f.name = field_name;
            f.qtype = qtype;
            f.attrs = attrs;
            node_record_ptr->fields.emplace_back(f);
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

    auto attrs = get_attrs(tad);

    // First of all, make sure we have already processed the Record that this
    // alias refers to. I *think* this should always have happened, but not sure
    // yet
    auto it = NODE_MAP.find(mangled_name);
    if (it == NODE_MAP.end()) {
        SPDLOG_DEBUG("Storing alias {} for {}", alias_name,
                     record_qualified_name);
        pending_aliases[mangled_name] = alias_name;

        // TODO LT: Add pending_attrs
    } else {
        NodeId id_rec = it->second;
        NodeRecord* node_rec = (NodeRecord*)NODES[id_rec].get();
        node_rec->alias = alias_name;

        // Add the typedef attributes to the node record.
        for (auto i : attrs) {
            node_rec->attrs.push_back(i);
        }
    }
}

bool has_ignore_unbound_attr(const std::vector<std::string>& attrs) {
    return std::find(attrs.begin(), attrs.end(), "cppmm|ignore_unbound") !=
           attrs.end();
}

bool has_trivially_copyable_attr(const std::vector<std::string>& attrs) {
    return std::find(attrs.begin(), attrs.end(), "cppmm|trivially_copyable") !=
           attrs.end();
}

bool has_trivially_movable_attr(const std::vector<std::string>& attrs) {
    return std::find(attrs.begin(), attrs.end(), "cppmm|trivially_movable") !=
           attrs.end();
}

bool has_opaquetype_attr(const std::vector<std::string>& attrs) {
    return std::find(attrs.begin(), attrs.end(), "cppmm|opaquetype") !=
           attrs.end();
}

bool has_opaquebytes_attr(const std::vector<std::string>& attrs) {
    return std::find(attrs.begin(), attrs.end(), "cppmm|opaquebytes") !=
           attrs.end();
}

bool has_impl_attr(const std::vector<std::string>& attrs) {
    return std::find(attrs.begin(), attrs.end(), "cppmm|impl") != attrs.end();
}

bool is_public_copy_ctor(const Decl* cmd) {
    if (const CXXConstructorDecl* cd = dyn_cast<CXXConstructorDecl>(cmd)) {
        SPDLOG_DEBUG("ctor {}", cd->getQualifiedNameAsString());
        SPDLOG_DEBUG("    is copy: {}", cd->isCopyConstructor());
        SPDLOG_DEBUG("    is public: {}", cd->getAccess() == AS_public);
        SPDLOG_DEBUG("    is deleted: {}", cd->isDeleted());
        return cd->isCopyConstructor() && cd->getAccess() == AS_public &&
               !cd->isDeleted();
    } else {
        return false;
    }
}

bool is_inaccessible_copy_ctor(const Decl* cmd) {
    if (const CXXConstructorDecl* cd = dyn_cast<CXXConstructorDecl>(cmd)) {
        return cd->isCopyConstructor() && (cd->getAccess() != AS_public ||
               cd->isDeleted());
    } else {
        return false;
    }
}

bool is_inaccessible_move_ctor(const Decl* cmd) {
    if (const CXXConstructorDecl* cd = dyn_cast<CXXConstructorDecl>(cmd)) {
        return cd->isMoveConstructor() && (cd->getAccess() != AS_public ||
               cd->isDeleted());
    } else {
        return false;
    }
}

bool is_public_move_ctor(const Decl* cmd) {
    if (const CXXConstructorDecl* cd = dyn_cast<CXXConstructorDecl>(cmd)) {
        SPDLOG_DEBUG("ctor {}", cd->getQualifiedNameAsString());
        SPDLOG_DEBUG("    is move: {}", cd->isMoveConstructor());
        SPDLOG_DEBUG("    is public: {}", cd->getAccess() == AS_public);
        SPDLOG_DEBUG("    is deleted: {}", cd->isDeleted());
        return cd->isMoveConstructor() && cd->getAccess() == AS_public &&
               !cd->isDeleted();
    } else {
        return false;
    }
}

bool has_forbidden_copy_ctor(const CXXRecordDecl* crd) {
    for (const Decl* d: crd->decls()) {
        if (is_inaccessible_copy_ctor(d)) {
            return true;
        }
    }


    for (const auto base : crd->bases()) {
        if (const CXXRecordDecl* base_crd =
                base.getType()->getAsCXXRecordDecl()) {
            if (has_forbidden_copy_ctor(base_crd)) {
                return true;
            }
        }
    }
    
    return false;
}

bool has_forbidden_move_ctor(const CXXRecordDecl* crd) {
    for (const Decl* d: crd->decls()) {
        if (is_inaccessible_move_ctor(d)) {
            return true;
        }
    }


    for (const auto base : crd->bases()) {
        if (const CXXRecordDecl* base_crd =
                base.getType()->getAsCXXRecordDecl()) {
            if (has_forbidden_move_ctor(base_crd)) {
                return true;
            }
        }
    }
    
    return false;
}

void has_public_copy_move_ctor(const CXXRecordDecl* crd,
                               bool& has_public_copy_ctor,
                               bool& has_public_move_ctor) {
    // for (const Decl* d : crd->decls()) {
    //     // has_public_copy_ctor |= is_public_copy_ctor(d);
    //     // has_public_move_ctor |= is_public_move_ctor(d);
    //     has_public_copy_ctor |= is_inaccessible_copy_ctor(d);
    //     has_public_move_ctor |= is_inaccessible_move_ctor(d);
    // }
    // has_public_copy_ctor = !has_public_copy_ctor;
    // has_public_move_ctor = !has_public_move_ctor;

    // has_public_copy_ctor = crd->hasTrivialCopyConstructor() || crd->hasNonTrivialCopyConstructor();
    has_public_move_ctor = (crd->hasTrivialMoveConstructor() || crd->hasNonTrivialMoveConstructor()) && !has_forbidden_move_ctor(crd);

    has_public_copy_ctor = !has_forbidden_copy_ctor(crd);
    // has_public_move_ctor = !has_forbidden_move_ctor(crd);
}

std::vector<std::string> get_properties(const std::vector<std::string>& attrs) {
    std::vector<std::string> props;
    for (const auto& attr : attrs) {
        if (attr.find("cppmm|properties|") != 0) {
            continue;
        }

        std::string props_str = attr.substr(17, std::string::npos);
        std::vector<std::string> props_toks;
        ps::split(props_str, props_toks, ";");
        for (const auto& p : props_toks) {
            props.push_back(ps::strip(p));
        }
    }

    return props;
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

    bool is_opaquetype = has_opaquetype_attr(attrs);

    const auto* can_rd =
        crd->getCanonicalDecl()
            ->getDefinition(); // TODO: this seems to do what we want... but
                               // does it? Can you imagine a world in which
                               // Clang was actually documented?
    if (can_rd != nullptr) {
        crd = can_rd;
    } else {
        // we don't expect a canonical definition for an opaque type
        if (!is_opaquetype) {
            SPDLOG_ERROR("Could not get canonical decl definition from {}",
                         crd->getQualifiedNameAsString());
            SPDLOG_ERROR("can def is {}", (void*)crd->getCanonicalDecl());
            crd->dump();
        }
    }

    const std::string record_name = get_record_name(crd);
    const std::string short_name = crd->getNameAsString();

    SPDLOG_DEBUG("Processing concrete record {} with attrs [{}]", record_name,
                 ps::join(", ", attrs));

    // Get the translation unit node we're going to add this Record to
    auto* node_tu = get_translation_unit(filename);
    std::vector<NodeId> namespaces = get_namespaces(crd->getParent(), node_tu);

    // Get the mangled version of the record name
    std::string mangled_name = mangle_decl(crd);
    SPDLOG_DEBUG("Record {} mangles to {}", crd->getQualifiedNameAsString(),
                 mangled_name);

    uint32_t size = 0, align = 0;
    bool is_trivially_movable = false;
    bool is_trivially_copyable = false;
    bool is_abstract = false;
    bool ignore_unbound = has_ignore_unbound_attr(attrs);

    bool has_public_copy_ctor = false;
    bool has_public_move_ctor = false;

    if (!is_opaquetype) {
        // We can only get the detailed info here for a non-opaque type
        // Get the size and alignment of the Record
        if (!get_abi_info(dyn_cast<TypeDecl>(crd), ctx, size, align)) {
            SPDLOG_CRITICAL("Could not get ABI info for {}", record_name);
            // if we can't get ABI info then need to assume it's an untagged
            // opaque type
            is_opaquetype = true;
        } else {
            is_trivially_movable = !(crd->hasNonTrivialMoveAssignment() ||
                                     crd->hasNonTrivialMoveConstructor()) ||
                                   has_trivially_movable_attr(attrs);
            is_trivially_copyable = crd->isTriviallyCopyable() ||
                                    has_trivially_copyable_attr(attrs);
            // we can't trivially move a type if we can't trivially copy it
            is_trivially_movable &= is_trivially_copyable;
            if (!is_trivially_movable && has_opaquebytes_attr(attrs)) {
                SPDLOG_WARN(
                    "Record {} is marked as opaquebytes, but is not trivially "
                    "movable or copyable. You must ensure that the memory "
                    "representation of the bound struct is never moved or very "
                    "bad things will happen.",
                    record_name);
            }
            is_abstract = crd->isAbstract();
        }

        has_public_copy_move_ctor(crd, has_public_copy_ctor, has_public_move_ctor);
    }

    // Add the new Record node
    NodeId new_id = NODES.size();
    auto node_record = std::make_unique<NodeRecord>(
        record_name, new_id, node_tu->id, std::move(attrs),
        std::move(short_name), std::move(namespaces), RecordKind::OpaquePtr,
        is_abstract, is_trivially_copyable, is_trivially_movable, is_opaquetype,
        size, align, get_comment_base64(crd), has_public_copy_ctor,
        has_public_move_ctor);

    auto* node_record_ptr = node_record.get();
    NODES.emplace_back(std::move(node_record));
    NODE_MAP[mangled_name] = new_id;

    // add this record to the TU
    node_tu->children.push_back(new_id);

    if (!is_opaquetype) {
        // grab all the methods that are specified in the binding
        std::vector<NodePtr> methods = process_methods(crd, false, nullptr);
        SPDLOG_TRACE("record {} has {} methods", record_name, methods.size());
        for (NodePtr& method : methods) {
            NodeMethod* mptr = (NodeMethod*)method.get();
            SPDLOG_TRACE("    {}", *mptr);
        }

        for (NodePtr& method : methods) {
            NodeMethod* mptr = (NodeMethod*)method.get();
            if (method_in_list(mptr, binding_methods, attrs) &&
                !mptr->is_deleted) {
                mptr->attrs = std::move(attrs);
                mptr->in_binding = true;
                mptr->is_noexcept |= has_noexcept_attr(mptr->attrs);
            } else {
                // no matching method, skip
                continue;
            }

            // stick this method in the function map so we can find it later if
            // we need to for renaming
            function_map[mptr->_function_id] = mptr;

            NodeId id = NODES.size();
            NODE_MAP[method->qualified_name] = id;
            NODES.emplace_back(std::move(method));
            node_record_ptr->methods.push_back(id);
        }

        // now iterate over the binding methods and see if there's any manual
        // ones we want to stick in
        for (NodePtr& method : binding_methods) {
            NodeMethod* mptr = (NodeMethod*)method.get();
            if (has_manual_attr(mptr->attrs)) {
                mptr->in_binding = true;
                mptr->is_noexcept |= has_noexcept_attr(mptr->attrs);
                function_map[mptr->_function_id] = mptr;

                mptr->is_copy_constructor = has_copy_ctor_attr(mptr->attrs);
                mptr->is_move_constructor = has_move_ctor_attr(mptr->attrs);

                NodeId id = NODES.size();
                NODE_MAP[method->qualified_name] = id;
                NODES.emplace_back(std::move(method));
                node_record_ptr->methods.push_back(id);
            }
        }

        if (WARN_UNMATCHED && !ignore_unbound) {
            for (const auto& n : methods) {
                const auto* m = (NodeMethod*)n.get();
                if (m && !m->in_binding && !m->is_deleted && !m->is_shadowed) {
                    SPDLOG_WARN("[{}]({}) - \n"
                                "{} is present in the library but not declared "
                                "in the binding",
                                record_name, node_tu->qualified_name, *m);
                }
            }
        }

        for (const auto& n : binding_methods) {
            const auto* m = (NodeMethod*)n.get();
            if (m && m->is_user_provided && !m->in_library && !m->is_deleted &&
                !has_manual_attr(m->attrs)) {
                SPDLOG_WARN("[{}]({}) - \n"
                            "{} is declared in the binding but not present "
                            "in the library",
                            record_name, node_tu->qualified_name, *m);
            }
        }

        // process remaining children
        // first process (recursively) the fields from this decl and all bases
        process_fields(crd, node_record_ptr);
        auto props = get_properties(node_record_ptr->attrs);

        // now tag the fields themselves if they've been marked as properties
        for (auto& field : node_record_ptr->fields) {
            for (const auto& p : props) {
                if (p == field.name) {
                    field.attrs.push_back("cppmm|property");
                }
            }
        }

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
    auto loc = crd->getLocation();

    // we don't care about locations in macros, we always want their expansions
    // if we're using macros to generate functions
    if (loc.isMacroID()) {
        auto range = sm.getExpansionRange(loc);
        loc = range.getBegin();
    }

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
    std::vector<NodePtr> methods = process_methods(crd, false, nullptr);
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
    SPDLOG_DEBUG("GOt FD {}", fd->getQualifiedNameAsString());
    if (fd->getTemplatedKind() == 1) {
        // ignore template functions in the binding
        SPDLOG_DEBUG("    Ignoring templated function");
        return;
    }

    if (const auto* cmd = dyn_cast<CXXMethodDecl>(fd)) {
        // don't do out-of-line method declarations
        SPDLOG_DEBUG("    Ignoring out-of-line method declaration");

        // auto attrs = get_attrs(fd);
        // SPDLOG_DEBUG("    attrs: {}", ps::join(", ", attrs));

        // SPDLOG_DEBUG("    Is CMD");
        // if (const auto* ftsi = cmd->getTemplateSpecializationInfo()) {
        //     SPDLOG_DEBUG("    Got ftsi {}", (void*)ftsi->getTemplate());
        //     ftsi->getTemplate()->dump();
        // }
        // if (const auto* tal = cmd->getTemplateSpecializationArgs()) {
        //     SPDLOG_DEBUG("    TAL");
        //     for (int i = 0; i < tal->size(); ++i) {
        //         SPDLOG_DEBUG("        {}",
        //                      tal->get(i).getAsType().getAsString());
        //     }
        // }
        return;
    }

    const std::string function_qual_name =
        pystring::replace(fd->getQualifiedNameAsString(), "cppmm_bind::", "");
    const std::string function_short_name = fd->getNameAsString();
    SPDLOG_DEBUG("    BIND FUNCTION {}", function_qual_name);

    ASTContext& ctx = fd->getASTContext();
    SourceManager& sm = ctx.getSourceManager();
    auto loc = fd->getLocation();
    // we don't care about locations in macros, we always want their expansions
    // if we're using macros to generate functions
    if (loc.isMacroID()) {
        auto range = sm.getExpansionRange(loc);
        loc = range.getBegin();
    }
    std::string filename = sm.getFilename(loc).str();

    // Get the translation unit node we're going to add this Function to
    auto* node_tu = get_translation_unit(filename);

    auto attrs = get_attrs(fd);

    QType return_qtype;
    std::vector<Param> params;
    process_function_parameters(fd, return_qtype, params);
    auto exceptions = get_exceptions(attrs);

    // If we've marked the function as being an implementation with CPPMM_IMPL,
    // and it has a valid function body, grab the entire function definition,
    // base64-encode it and bung it into NodeFunction, then add the node to the
    // translation unit. It will then be picked up in asttoc, and the function
    // body spat out as an inline function that asttoc will wrap.
    std::string body;
    if (has_impl_attr(attrs)) {
        if (fd->isThisDeclarationADefinition()) {
            std::string s;
            llvm::raw_string_ostream sos(s);
            fd->print(sos);

            auto function_spelling = s;
            auto remove_macro = ps::replace(function_spelling, "__attribute__((annotate(\"cppmm|impl\")))", "");
            auto rename_function = ps::replace(remove_macro, function_short_name + "(", function_short_name + "_impl(");
            body = base64::base64_encode(rename_function);

        } else {
            SPDLOG_ERROR("Function {} marked as impl but could not get body",
                         fd->getQualifiedNameAsString());
        }
    }

    const std::vector<NodeId> namespaces =
        get_namespaces(fd->getParent(), node_tu);

    auto it = binding_functions.find(function_qual_name);
    auto node_function = NodeFunction(
        function_qual_name, 0, node_tu->id, std::move(attrs),
        function_short_name, return_qtype, std::move(params),
        std::move(namespaces), get_comment_base64(fd), std::move(exceptions));

    node_function.definition = body;

    if (body.empty()) {
        if (it != binding_functions.end()) {
            it->second.emplace_back(std::move(node_function));
        } else {
            binding_functions[function_qual_name] = {node_function};
        }
    } else {
        // Rename our function to _impl and give the original name to the C 
        // function as an alias
        node_function.attrs.push_back("cppmm|rename|" + node_function.short_name);
        node_function.short_name = node_function.short_name + "_impl";
        node_function.qualified_name = node_function.qualified_name + "_impl";

        auto fnptr =
            std::make_unique<NodeFunction>(std::move(node_function));
        NodeId id = NODES.size();
        fnptr->id = id;
        // add the function to its TU
        auto* node_tu =
            (NodeTranslationUnit*)NODES.at(node_function.context).get();
        // process the namespaces again to make sure we've got the
        // namespaces in the TU
        const std::vector<NodeId> namespaces =
            get_namespaces(fd->getParent(), node_tu);
        fnptr->context = node_tu->id;
        node_tu->children.push_back(id);
        NODES.emplace_back(std::move(fnptr));
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
    SPDLOG_TRACE("    BIND VAR {}", var_qual_name);

    // If it's a ref decl then it might be a reference to a method and in that
    // case we use the name of the var to rename the method
    if (const auto* init = vd->getInit()) {
        if (const auto* uo = dyn_cast<UnaryOperator>(init)) {
            if (const auto* dre = dyn_cast<DeclRefExpr>(uo->getSubExpr())) {
                if (const auto* cmd = dyn_cast<CXXMethodDecl>(dre->getDecl())) {
                    SPDLOG_TRACE("VAR CMD {}", (void*)cmd);
                    const auto rename =
                        fmt::format("cppmm|rename|{}", vd->getNameAsString());

                    auto it = function_map.find((uint64_t)cmd);
                    if (it != function_map.end()) {
                        SPDLOG_TRACE("FOUND FUNCION");
                        it->second->attrs.push_back(rename);
                    } else {
                        SPDLOG_TRACE("NOT FOUND!!");
                    }
                }
            }
            return;
        }
    }

    // }

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
    if (fd->getTemplatedKind() == 1) {
        // ignore template functions in the library
        return;
    }

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
        std::move(params), std::move(namespaces), get_comment_base64(fd), {});
    node_function.is_noexcept = is_noexcept(fd);

    // find a match in the overloads
    for (auto& binding_fn : it->second) {
        if (!binding_fn.processed &&
            match_function(&node_function, &binding_fn)) {
            // we have a match. copy over the attributes and store this function
            node_function.attrs = binding_fn.attrs;
            node_function.context = binding_fn.context;
            node_function.template_args = binding_fn.template_args;
            node_function.exceptions = binding_fn.exceptions;
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

    process_library_enum_decl(ed, std::move(filename), it->second);
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
        functionDecl(hasAncestor(namespaceDecl(hasName("cppmm_bind"))))
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
            SPDLOG_DEBUG("Adding matcher for function {}", fn);
            DeclarationMatcher function_decl_matcher =
                functionDecl(
                    hasName(fn.short_name),
                    unless(hasAncestor(namespaceDecl(hasName("cppmm_bind")))))
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
