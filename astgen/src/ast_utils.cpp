#include "ast_utils.hpp"
#include "pystring.h"
namespace ps = pystring;
#include "base64.hpp"

#include <clang/AST/ASTContext.h>
#include <clang/AST/Attr.h>
#include <clang/Basic/ExceptionSpecificationType.h>
#include <clang/Basic/SourceManager.h>

#define SPDLOG_ACTIVE_LEVEL TRACE
#include <spdlog/fmt/fmt.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>

using namespace clang;

namespace cppmm {

/// Get any annotation attributes on the given Decl and return their values as
/// a vector of strings
std::vector<std::string> get_attrs(const clang::Decl* decl) {
    std::vector<std::string> attrs;
    if (decl->hasAttrs()) {
        clang::ASTContext& ctx = decl->getASTContext();
        for (const auto& attr : decl->attrs()) {
            const clang::AnnotateAttr* ann =
                clang::dyn_cast<const clang::AnnotateAttr>(attr);
            if (ann) {
                attrs.push_back(ann->getAnnotation().str());
            }
        }
    }
    return attrs;
}

/// Strip the type kinds off the front of a type name in the given string
std::string strip_name_kinds(std::string s) {
    s = pystring::replace(s, "class ", "");
    s = pystring::replace(s, "struct ", "");
    s = pystring::replace(s, "enum ", "");
    s = pystring::replace(s, "union ", "");

    return s;
}

/// Get a nice, qualified name for the given record
std::string get_record_name(const CXXRecordDecl* crd) {
    // we have to do this dance to get the template parameters in the name,
    // otherwise they're omitted
    return strip_name_kinds(crd->getCanonicalDecl()
                                ->getTypeForDecl()
                                ->getCanonicalTypeInternal()
                                .getAsString());
}

/// Get the full namespace path as a string
std::string get_namespace_path(const DeclContext* dc) {
    std::string result;
    auto* parent = dc->getParent();
    while (parent) {
        if (parent->isNamespace()) {
            const clang::NamespaceDecl* ns =
                static_cast<const clang::NamespaceDecl*>(parent);
            result = ns->getNameAsString() + "::" + result;
        } else if (parent->isRecord()) {
            const clang::CXXRecordDecl* crd =
                static_cast<const clang::CXXRecordDecl*>(parent);
            result = crd->getNameAsString() + "::" + result;
        }

        parent = parent->getParent();
    }
    return result;
}

std::string mangle_type(const QualType& qt) {
    std::string const_ = "";
    if (qt.isConstQualified()) {
        const_ = "const ";
    }

    if (qt->isPointerType() || qt->isReferenceType()) {
        std::string pointee = mangle_type(qt->getPointeeType());
        std::string ptr = "*";
        if (qt->isReferenceType()) {
            ptr = "&";
        } else if (qt->isRValueReferenceType()) {
            ptr = "&&";
        }
        return fmt::format("{}{}{}", const_, pointee, ptr);
    } else if (qt->isConstantArrayType()) {
        const ConstantArrayType* cat =
            dyn_cast<ConstantArrayType>(qt.getTypePtr());
        std::string element = mangle_type(cat->getElementType());
        return fmt::format("{}{}[{}]", const_, element,
                           cat->getSize().getLimitedValue());
    } else if (qt->isRecordType()) {
        auto crd = qt->getAsCXXRecordDecl();
        return fmt::format("{}{}", const_, mangle_decl(crd));
    } else if (qt->isBuiltinType()) {
        return fmt::format("{}{}", const_,
                           qt.getUnqualifiedType().getAsString());
    } else if (qt->isEnumeralType()) {
        auto ed = qt->getAsTagDecl();
        return fmt::format("{}{}", const_, mangle_decl(ed));
    } else if (qt->isFunctionProtoType()) {
        const auto type_name = qt.getUnqualifiedType().getAsString();
        return fmt::format("{}{}", const_, type_name);
    } else {
        const auto type_name = qt.getUnqualifiedType().getAsString();
        SPDLOG_WARN("Unhandled type in mangling {}", type_name);
        return fmt::format("{}{}", const_, type_name);
    }
}

std::vector<std::string>
mangle_template_args(const TemplateArgumentList& args) {
    std::vector<std::string> result;
    for (int i = 0; i < args.size(); ++i) {
        const auto& arg = args[i];
        if (arg.getKind() == TemplateArgument::ArgKind::Null) {
            result.push_back("Null");
        } else if (arg.getKind() == TemplateArgument::ArgKind::Type) {
            result.push_back(mangle_type(arg.getAsType()));
        } else if (arg.getKind() == TemplateArgument::ArgKind::Declaration) {
            result.push_back("Declaration");
        } else if (arg.getKind() == TemplateArgument::ArgKind::NullPtr) {
            result.push_back("NullPtr");
        } else if (arg.getKind() == TemplateArgument::ArgKind::Integral) {
            result.push_back(
                ps::replace(std::to_string(arg.getAsIntegral().getExtValue()), "-", "neg"));
        } else if (arg.getKind() == TemplateArgument::ArgKind::Template) {
            result.push_back("Template");
        } else if (arg.getKind() ==
                   TemplateArgument::ArgKind::TemplateExpansion) {
            result.push_back("TemplateExpansion");
        } else if (arg.getKind() == TemplateArgument::ArgKind::Expression) {
            result.push_back("Expression");
        } else {
            result.push_back("Pack");
        }
    }

    return result;
}

std::string mangle_decl(const TagDecl* crd) {
    std::string namespace_path = get_namespace_path(crd);

    if (const auto* ctd = dyn_cast<ClassTemplateSpecializationDecl>(crd)) {
        auto args = mangle_template_args(ctd->getTemplateArgs());
        return fmt::format("{}::{}<{}>", namespace_path, ctd->getNameAsString(),
                           ps::join(", ", args));
    } else {
        return fmt::format("{}::{}", namespace_path, crd->getNameAsString());
    }
}

std::string get_comment(const clang::Decl* decl) {
    ASTContext& ctx = decl->getASTContext();
    SourceManager& sm = ctx.getSourceManager();

    const RawComment* rc = ctx.getRawCommentForDeclNoCache(decl);
    if (rc) {
        // Found comment!
        SourceRange range = rc->getSourceRange();

        PresumedLoc startPos = sm.getPresumedLoc(range.getBegin());
        PresumedLoc endPos = sm.getPresumedLoc(range.getEnd());

        return rc->getFormattedText(sm, sm.getDiagnostics());
    }
    return "";
}

std::string get_comment_base64(const clang::Decl* decl) {
    return base64::base64_encode(get_comment(decl));
}

bool is_noexcept(const clang::FunctionDecl* fd) {
    return isNoexceptExceptionSpec(fd->getExceptionSpecType());
}

} // namespace cppmm
