#include "process_binding.hpp"
#include "attributes.hpp"
#include "namespaces.hpp"
#include "pystring.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/Decl.h"
#include "clang/AST/DeclCXX.h"
#include "clang/AST/DeclTemplate.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/Basic/LLVM.h"
#include "llvm/Support/Casting.h"

#define SPDLOG_ACTIVE_LEVEL TRACE
#include <spdlog/fmt/fmt.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>

using namespace clang;
using namespace clang::ast_matchers;
namespace ps = pystring;

namespace cppmm {

namespace {

std::vector<AttrDesc> get_attrs(const clang::Decl* decl) {
    std::vector<AttrDesc> attrs;
    if (decl->hasAttrs()) {
        clang::ASTContext& ctx = decl->getASTContext();
        for (const auto& attr : decl->attrs()) {
            const clang::AnnotateAttr* ann =
                clang::cast<const clang::AnnotateAttr>(attr);
            if (ann) {
                if (auto opt = parse_attributes(ann->getAnnotation().str())) {
                    attrs.push_back(*opt);
                }
            }
        }
    }

    return attrs;
}

} // namespace

void print_abi_info(const TypeDecl* td, ASTContext& ctx) {
    if (td) {
        const clang::Type* ty = td->getTypeForDecl();
        if (!ty->isIncompleteType()) {
            const clang::TypeInfo& ti = ctx.getTypeInfo(ty);
            SPDLOG_DEBUG("    width: {}", ti.Width);
            SPDLOG_DEBUG("    align: {}", ti.Align);
        } else {
            SPDLOG_DEBUG("    is incomplete type");
        }
    } else {
        SPDLOG_DEBUG("    is not a TypeDecl");
    }
}

void handle_class_template_decl(const ClassTemplateDecl* ctd) {
    ASTContext& ctx = ctd->getASTContext();
    SourceManager& sm = ctx.getSourceManager();
    const auto& loc = ctd->getLocation();

    SPDLOG_DEBUG("ClassTemplateDecl {:p} {} ({}:{})", (void*)ctd, ctd->getNameAsString(),
                 sm.getFilename(loc).str(), sm.getSpellingLineNumber(loc));

    const TemplateParameterList* tpl = ctd->getTemplateParameters();
    for (const NamedDecl* nd: *tpl) {
        SPDLOG_DEBUG("        {}", nd->getNameAsString());
    }
}

void process_function_parameters(const FunctionDecl* fd) {
    SPDLOG_DEBUG("    -> {}", fd->getReturnType().getAsString());
    for (const ParmVarDecl* pvd: fd->parameters()) {
        SPDLOG_DEBUG("        {}: {}", pvd->getNameAsString(), pvd->getType().getCanonicalType().getAsString());
    }
}
                        

void process_concrete_decl(const CXXRecordDecl* crd) {
    ASTContext& ctx = crd->getASTContext();
    SourceManager& sm = ctx.getSourceManager();
    const auto& loc = crd->getLocation();

    print_abi_info(dyn_cast<TypeDecl>(crd), ctx);

    for (const FieldDecl* field: crd->fields()) {
        SPDLOG_DEBUG("    FIELD {}", field->getNameAsString());
    }

    for (const CXXMethodDecl* method: crd->methods()) {
        SPDLOG_DEBUG("    METHOD {}", method->getNameAsString());
        process_function_parameters(method);
    }
}

void handle_cxx_record_decl(const CXXRecordDecl* crd) {
    ASTContext& ctx = crd->getASTContext();
    SourceManager& sm = ctx.getSourceManager();
    const auto& loc = crd->getLocation();

    SPDLOG_DEBUG("CXXRecordDecl {:p} {} ({}:{})", (void*)crd, crd->getNameAsString(),
                 sm.getFilename(loc).str(), sm.getSpellingLineNumber(loc));

    const clang::Type* ty = crd->getTypeForDecl();
    if (ty->isIncompleteType()) {
        // type cannot be sized
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

    if (const ClassTemplateSpecializationDecl* ctsd =
            dyn_cast<ClassTemplateSpecializationDecl>(crd)) {
        SPDLOG_DEBUG("    is ClassTemplateSpecializationDecl");
        process_concrete_decl(crd);
    } else {
        // if we get down here then we have a concrete, sized type we can process
        process_concrete_decl(crd);
    }
}

void ProcessBindingCallback::run(const MatchFinder::MatchResult& result) {
    // if (const TypeAliasDecl* tdecl =
    //         result.Nodes.getNodeAs<TypeAliasDecl>("typeAliasDecl")) {
    //     handle_typealias(tdecl);
    // } else if (const CXXRecordDecl* record =
    //                result.Nodes.getNodeAs<CXXRecordDecl>("recordDecl")) {
    //     handle_record(record);
    // } else if (const EnumDecl* enum_decl =
    //                result.Nodes.getNodeAs<EnumDecl>("enumDecl")) {
    //     handle_enum(enum_decl);
    // } else if (const FunctionDecl* function =
    //                result.Nodes.getNodeAs<FunctionDecl>("functionDecl")) {
    //     handle_function(function);
    // }
    if (const ClassTemplateDecl* class_template_decl =
            result.Nodes.getNodeAs<ClassTemplateDecl>("classTemplateDecl")) {
        handle_class_template_decl(class_template_decl);
    }
    if (const CXXRecordDecl* rec_decl =
            result.Nodes.getNodeAs<CXXRecordDecl>("recordDecl")) {
        handle_cxx_record_decl(rec_decl);
    }
}

ProcessBindingConsumer::ProcessBindingConsumer(ASTContext* context) {
    // match all record declrations in the cppmm_bind namespace
    DeclarationMatcher record_decl_matcher =
        cxxRecordDecl(hasAncestor(namespaceDecl(hasName("cppmm_bind"))),
                      unless(isImplicit()))
            .bind("recordDecl");
    _match_finder.addMatcher(record_decl_matcher, &_handler);

    // match all record declrations in the cppmm_bind namespace
    DeclarationMatcher class_template_decl_matcher =
        classTemplateDecl(hasAncestor(namespaceDecl(hasName("cppmm_bind"))))
            .bind("classTemplateDecl");
    _match_finder.addMatcher(class_template_decl_matcher, &_handler);

    /*
    // match all record declrations in the cppmm_bind namespace
    DeclarationMatcher enum_decl_matcher =
        enumDecl(hasAncestor(namespaceDecl(hasName("cppmm_bind"))),
                 unless(isImplicit()))
            .bind("enumDecl");
    _match_finder.addMatcher(enum_decl_matcher, &_handler);

    // match all typedef declrations in the cppmm_bind namespace
    DeclarationMatcher typedef_decl_matcher =
        typeAliasDecl(hasAncestor(namespaceDecl(hasName("cppmm_bind"))),
                      unless(isImplicit()))
            .bind("typeAliasDecl");
    _match_finder.addMatcher(typedef_decl_matcher, &_handler);

    // match all function declarations
    DeclarationMatcher function_decl_matcher =
        functionDecl(hasAncestor(namespaceDecl(hasName("cppmm_bind"))),
                     unless(hasAncestor(recordDecl())))
            .bind("functionDecl");
    _match_finder.addMatcher(function_decl_matcher, &_handler);
    */
}

void ProcessBindingConsumer::HandleTranslationUnit(ASTContext& context) {
    _match_finder.matchAST(context);
}

} // namespace cppmm
