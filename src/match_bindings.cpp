#include <fmt/format.h>

#include "attributes.hpp"
#include "match_bindings.hpp"
#include "namespaces.hpp"
#include "pystring.h"

using namespace clang;
using namespace clang::ast_matchers;
namespace ps = pystring;

namespace cppmm {
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

void MatchBindingsCallback::run(const MatchFinder::MatchResult& result) {
    if (const TypeAliasDecl* tdecl =
            result.Nodes.getNodeAs<TypeAliasDecl>("typeAliasDecl")) {
        handle_typealias(tdecl);
    } else if (const CXXRecordDecl* record =
                   result.Nodes.getNodeAs<CXXRecordDecl>("recordDecl")) {
        handle_record(record);
    } else if (const EnumDecl* enum_decl =
                   result.Nodes.getNodeAs<EnumDecl>("enumDecl")) {
        handle_enum(enum_decl);
    } else if (const CXXMethodDecl* method =
                   result.Nodes.getNodeAs<CXXMethodDecl>("methodDecl")) {
        handle_method(method);
    } else if (const FunctionDecl* function =
                   result.Nodes.getNodeAs<FunctionDecl>("functionDecl")) {
        handle_function(function);
    }
}

void MatchBindingsCallback::handle_typealias(const TypeAliasDecl* alias) {
    fmt::print("GOT typeAliasDecl: {}\n", alias->getNameAsString());
    const QualType qtype = alias->getUnderlyingType();
    if (const CXXRecordDecl* record = qtype->getAsCXXRecordDecl()) {
        if (isa<ClassTemplateSpecializationDecl>(record)) {
            const ClassTemplateSpecializationDecl* ctsd =
                cast<ClassTemplateSpecializationDecl>(record);
            ClassTemplateDecl* ctd = ctsd->getSpecializedTemplate();
            CXXRecordDecl* scrd = ctd->getTemplatedDecl();

            std::string record_cpp_qname =
                prefix_from_namespaces(get_namespaces(scrd->getParent()), "::") + scrd->getNameAsString();

            if (ex_records.find(record_cpp_qname) == ex_records.end()) {
                // we only want to process specializations for types we care about
                return;
            }

            fmt::print("record is CTSD\n");
            std::vector<std::string> typelist;
            for (const auto& targ : ctsd->getTemplateArgs().asArray()) {
                if (!targ.getAsType()->isBuiltinType()) {
                    throw std::runtime_error(fmt::format(
                        "template argument {} on {} is not a builtin.",
                        targ.getAsType().getAsString(),
                        record->getNameAsString()));
                }
                typelist.push_back(targ.getAsType().getAsString());
            }

            ExportedSpecialization ex_spec;
            ex_spec.record_cpp_qname;

            // ex_record.dependent_qname = ex_record.cpp_qname;
            // ex_record.cpp_qname +=
            //     fmt::format("<{}>", ps::join(", ", typelist));
            // ex_record.c_qname += fmt::format("_{}", ps::join("_", typelist));
            // fmt::print("Got template specialization {}\n",
            // ex_record.cpp_qname);
            fmt::print("ctd: {:p}\nscrd: {:p}\n", (void*)ctd, (void*)scrd);
            ex_spec.template_args = typelist;
            ex_spec.alias = alias->getNameAsString();
            ex_spec.record_cpp_qname;
            ex_specs[record_cpp_qname].push_back(ex_spec);
        }
    }
}

void MatchBindingsCallback::handle_enum(const EnumDecl* enum_decl) {
    const auto ns = get_namespaces(enum_decl->getParent());
    std::vector<std::pair<std::string, uint64_t>> enumerators;

    ASTContext& ctx = enum_decl->getASTContext();
    SourceManager& sm = ctx.getSourceManager();
    const auto& loc = enum_decl->getLocation();
    std::string filename = sm.getFilename(loc);

    ExportedEnum ex_enum;
    ex_enum.cpp_name = enum_decl->getNameAsString();
    ex_enum.c_name = ex_enum.cpp_name;
    ex_enum.c_qname = prefix_from_namespaces(ns, "_") + ex_enum.c_name;
    ex_enum.cpp_qname = prefix_from_namespaces(ns, "::") + ex_enum.cpp_name;

    // fmt::print("Found enum: {}\n", ex_enum.c_qname);
    ex_enum.namespaces = ns;
    ex_enum.filename = filename;

    if (ex_enums.find(ex_enum.cpp_qname) != ex_enums.end()) {
        fmt::print("WARNING: Ignoring duplicate definition for {}\n",
                   ex_enum.c_qname);
        return;
    }

    ex_enums[ex_enum.cpp_qname] = ex_enum;

    if (ex_files.find(filename) == ex_files.end()) {
        ex_files[filename] = {};
    }

    auto& ex_file = ex_files[filename];
    if (ex_file.enums.find(ex_enum.cpp_qname) == ex_file.enums.end()) {
        ex_file.enums[ex_enum.cpp_qname] = &ex_enums[ex_enum.cpp_qname];
        // fmt::print("GOT TYPE: {}\n", ex_record);
    }
}

void MatchBindingsCallback::handle_record(const CXXRecordDecl* record) {
    ExportedRecord ex_record;

    ex_record.cpp_name = record->getNameAsString();
    ex_record.c_name = ex_record.cpp_name;
    ex_record.namespaces = get_namespaces(record->getParent());
    ex_record.c_qname =
        prefix_from_namespaces(ex_record.namespaces, "_") + ex_record.c_name;
    ex_record.cpp_qname =
        prefix_from_namespaces(ex_record.namespaces, "::") + ex_record.cpp_name;

    if (isa<ClassTemplateSpecializationDecl>(record)) {
        return;
        /*
        const ClassTemplateSpecializationDecl* ctsd =
            cast<ClassTemplateSpecializationDecl>(record);
        fmt::print("record is CTSD\n");
        std::vector<std::string> typelist;
        for (const auto& targ : ctsd->getTemplateArgs().asArray()) {
            if (!targ.getAsType()->isBuiltinType()) {
                throw std::runtime_error(fmt::format(
                    "template argument {} on {} is not a builtin.",
                    targ.getAsType().getAsString(),
        record->getNameAsString()));
            }
            typelist.push_back(targ.getAsType().getAsString());
        }
        */
        // ex_record.dependent_qname = ex_record.cpp_qname;
        // ex_record.cpp_qname += fmt::format("<{}>", ps::join(", ",
        // typelist)); ex_record.c_qname += fmt::format("_{}", ps::join("_",
        // typelist)); fmt::print("Got template specialization {}\n",
        // ex_record.cpp_qname); ClassTemplateDecl* ctd =
        // ctsd->getSpecializedTemplate(); CXXRecordDecl* scrd =
        // ctd->getTemplatedDecl(); fmt::print("ctd: {:p}\nscrd: {:p}\n",
        // (void*)ctd, (void*)scrd); ex_record.template_args = typelist;
        // std::vector<AttrDesc> attrs = get_attrs(scrd);
        // ex_record.kind = RecordKind::OpaquePtr;
        // for (const auto& attr : attrs) {
        //     if (attr.kind == AttrDesc::Kind::ValueType) {
        //         ex_record.kind = RecordKind::ValueType;
        //     } else if (attr.kind == AttrDesc::Kind::OpaqueBytes) {
        //         ex_record.kind = RecordKind::OpaqueBytes;
        //     }
        // }
        // fmt::print("{} is a {}\n", ex_record.c_qname, ex_record.kind);

    } else if (record->isDependentContext()) {
        // this is the template type
        fmt::print("{} ({:p}) is dependent\n", ex_record.cpp_qname,
                   (void*)record);
        ex_record.is_dependent = true;
    }

    std::vector<AttrDesc> attrs = get_attrs(record);
    ex_record.kind = RecordKind::OpaquePtr;
    for (const auto& attr : attrs) {
        if (attr.kind == AttrDesc::Kind::ValueType) {
            ex_record.kind = RecordKind::ValueType;
        } else if (attr.kind == AttrDesc::Kind::OpaqueBytes) {
            ex_record.kind = RecordKind::OpaqueBytes;
        }
    }
    fmt::print("{} is a {}\n", ex_record.c_qname, ex_record.kind);

    if (ex_records.find(ex_record.cpp_qname) != ex_records.end()) {
        fmt::print("WARNING: Ignoring duplicate definition for {}\n",
                   ex_record.cpp_qname);
        return;
    }

    // fmt::print("record {}\n", ex_record.cpp_name);
    // record->dump();
    ASTContext& ctx = record->getASTContext();
    SourceManager& sm = ctx.getSourceManager();
    const auto& loc = record->getLocation();
    std::string filename = sm.getFilename(loc);
    // fmt::print("    {}:{}:{}\n", filename, sm.getSpellingLineNumber(loc),
    //            sm.getSpellingColumnNumber(loc));

    ex_record.filename = filename;

    ex_records[ex_record.cpp_qname] = ex_record;
    ExportedRecord* ex_record_ptr = &ex_records[ex_record.cpp_qname];

    if (ex_files.find(filename) == ex_files.end()) {
        ex_files[filename] = {};
    }

    auto& ex_file = ex_files[filename];
    if (ex_file.records.find(ex_record.cpp_qname) == ex_file.records.end()) {
        ex_file.records[ex_record.cpp_qname] = ex_record_ptr;
        // fmt::print("GOT TYPE: {}\n", ex_record);
    }
}

void MatchBindingsCallback::handle_function(const FunctionDecl* function) {
    // fmt::print("GOT FUNCTION: {}\n", function->getNameAsString());
    std::vector<AttrDesc> attrs = get_attrs(function);

    // figure out which file we're in
    ASTContext& ctx = function->getASTContext();
    SourceManager& sm = ctx.getSourceManager();
    std::string filename = sm.getFilename(function->getBeginLoc());

    auto namespaces = get_namespaces(function->getParent());

    ExportedFunction ex_function(function, filename, attrs, namespaces);

    if (ex_files.find(filename) == ex_files.end()) {
        ex_files[filename] = {};
    }
    ex_files[filename].functions.push_back(ex_function);
}

void MatchBindingsCallback::handle_method(const CXXMethodDecl* method) {
    // If there are attributes, parse them looking for cppmm annotations
    std::vector<AttrDesc> attrs = get_attrs(method);
    ExportedMethod ex_method(method, attrs);
    const auto class_name = method->getParent()->getNameAsString();

    // check if we've seen the class this method belongs to before, and
    // if not process it
    if (ex_classes.find(class_name) == ex_classes.end()) {
        ASTContext& ctx = method->getASTContext();
        SourceManager& sm = ctx.getSourceManager();

        std::string filename = sm.getFilename(method->getBeginLoc());

        auto namespaces = get_namespaces(method->getParent()->getParent());
        ex_classes[class_name] =
            ExportedClass{class_name, filename, namespaces, {}};

        if (ex_files.find(filename) == ex_files.end()) {
            ex_files[filename] = {};
        }
        ex_files[filename].classes.push_back(class_name);
    }

    // store this method signiature to match against in the second pass
    ex_classes[class_name].methods.push_back(ex_method);
}

MatchBindingsConsumer::MatchBindingsConsumer(ASTContext* context) {
    // match all record declrations in the cppmm_bind namespace
    DeclarationMatcher enum_decl_matcher =
        enumDecl(hasAncestor(namespaceDecl(hasName("cppmm_bind"))),
                 unless(isImplicit()))
            .bind("enumDecl");
    _match_finder.addMatcher(enum_decl_matcher, &_handler);

    // match all record declrations in the cppmm_bind namespace
    DeclarationMatcher record_decl_matcher =
        cxxRecordDecl(hasAncestor(namespaceDecl(hasName("cppmm_bind"))),
                      unless(isImplicit()))
            .bind("recordDecl");
    _match_finder.addMatcher(record_decl_matcher, &_handler);

    // match all typedef declrations in the cppmm_bind namespace
    DeclarationMatcher typedef_decl_matcher =
        typeAliasDecl(hasAncestor(namespaceDecl(hasName("cppmm_bind"))),
                      unless(isImplicit()))
            .bind("typeAliasDecl");
    _match_finder.addMatcher(typedef_decl_matcher, &_handler);

    // match all method declrations in the cppmm_bind namespace
    DeclarationMatcher method_decl_matcher =
        cxxMethodDecl(hasAncestor(namespaceDecl(hasName("cppmm_bind"))))
            .bind("methodDecl");
    _match_finder.addMatcher(method_decl_matcher, &_handler);

    // match all function declarations
    DeclarationMatcher function_decl_matcher =
        functionDecl(hasAncestor(namespaceDecl(hasName("cppmm_bind"))),
                     unless(hasAncestor(recordDecl())))
            .bind("functionDecl");
    _match_finder.addMatcher(function_decl_matcher, &_handler);
}

void MatchBindingsConsumer::HandleTranslationUnit(ASTContext& context) {
    _match_finder.matchAST(context);
}

} // namespace cppmm
