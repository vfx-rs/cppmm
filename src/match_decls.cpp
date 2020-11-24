#include "match_decls.hpp"
#include "decls.hpp"
#include "exports.hpp"
#include "namespaces.hpp"

#include <fmt/format.h>

using namespace clang;
using namespace clang::ast_matchers;

namespace cppmm {

void MatchDeclsHandler::run(const MatchFinder::MatchResult& result) {
    if (const EnumDecl* enum_decl =
                   result.Nodes.getNodeAs<EnumDecl>("enumDecl")) {
        handle_enum(enum_decl);
    } else if (const FunctionDecl* function =
                   result.Nodes.getNodeAs<FunctionDecl>("functionDecl")) {
        handle_function(function);
    } else if (const CXXRecordDecl* record =
                   result.Nodes.getNodeAs<CXXRecordDecl>("recordDecl")) {
        handle_record(record);
    }
}

void MatchDeclsHandler::handle_record(const CXXRecordDecl* record) {
    process_record(record);
}
void MatchDeclsHandler::handle_enum(const EnumDecl* enum_decl) {
    process_enum(enum_decl);
}

void MatchDeclsHandler::handle_function(const FunctionDecl* function) {
    // convert this method so we can match it against our stored ones
    auto namespaces = get_namespaces(function->getParent());
    ASTContext& ctx = function->getASTContext();
    SourceManager& sm = ctx.getSourceManager();
    std::string filename = sm.getFilename(function->getBeginLoc());
    const auto this_ex_function =
        cppmm::ExportedFunction(function, filename, {}, namespaces);

    // now see if we can find the function in the exported functions on
    // the exported class
    const cppmm::ExportedFunction* matched_ex_function = nullptr;
    std::string matched_file;
    bool rejected = true;
    for (const auto& ex_file : cppmm::ex_files) {
        for (const auto& ex_function : ex_file.second.functions) {
            if (this_ex_function.cpp_name == ex_function.cpp_name &&
                cppmm::match_namespaces(this_ex_function.namespaces,
                                        ex_function.namespaces)) {
                fmt::print("matched {}\n", ex_function.cpp_name);
                matched_file = ex_file.first;
            } else {
                continue;
            }

            if (this_ex_function == ex_function) {
                // found a matching exported function (but may still be
                // ignored)
                rejected = false;
                if (!(ex_function.is_ignored() || ex_function.is_manual())) {
                    // not ignored, this is the one we'll use
                    matched_ex_function = &ex_function;
                    break;
                }
                // } else {
                // if (this_ex_function.cpp_name == ex_function.cpp_name) {
                //     fmt::print("REJECTED {}\n", this_ex_function);
                // }
            } else {
                fmt::print("  but sig does not match\n");
            }
        }
    }

    // store the rejected function on the class so we can warn that we
    // didn't find a match
    if (rejected) {
        ex_files[matched_file].rejected_functions.push_back(this_ex_function);
    }

    // we don't want to bind this function so bail
    if (matched_ex_function == nullptr) {
        return;
    }

    process_function(function, *matched_ex_function, namespaces);
}

MatchDeclsConsumer::MatchDeclsConsumer(ASTContext* context) {
    // match all record (custom type) declarations in all files
    for (const auto& ex_file : cppmm::ex_files) {
        for (const auto& record : ex_file.second.records) {
            DeclarationMatcher record_decl_matcher =
                cxxRecordDecl(
                    hasName(record.second->cpp_name),
                    unless(hasAncestor(namespaceDecl(hasName("cppmm_bind")))),
                    unless(isImplicit()))
                    .bind("recordDecl");
            _match_finder.addMatcher(record_decl_matcher, &_handler);
        }
    }

    for (const auto& ex_enum : cppmm::ex_enums) {
        DeclarationMatcher enum_decl_matcher =
            enumDecl(hasName(ex_enum.second.cpp_name),
                     unless(hasAncestor(namespaceDecl(hasName("cppmm_bind")))),
                     unless(isImplicit()))
                .bind("enumDecl");
        _match_finder.addMatcher(enum_decl_matcher, &_handler);
    }

    // match all function declarations
    DeclarationMatcher function_decl_matcher =
        functionDecl(unless(hasAncestor(namespaceDecl(hasName("cppmm_bind")))),
                     unless(hasAncestor(recordDecl())))
            .bind("functionDecl");
    _match_finder.addMatcher(function_decl_matcher, &_handler);
}

void MatchDeclsConsumer::HandleTranslationUnit(ASTContext& context) {
    _match_finder.matchAST(context);
}

} // namespace cppmm
