#include <clang/AST/ASTConsumer.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/ASTMatchers/ASTMatchFinder.h>
#include <clang/ASTMatchers/ASTMatchers.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendAction.h>

#include "exports.hpp"

namespace cppmm {

class MatchBindingsCallback : public clang::ast_matchers::MatchFinder::MatchCallback {
    virtual void run(const clang::ast_matchers::MatchFinder::MatchResult& result);
    void handle_enum(const clang::EnumDecl* enum_decl);
    void handle_record(const clang::CXXRecordDecl* record);
    void handle_function(const clang::FunctionDecl* function);
    void handle_method(const clang::CXXMethodDecl* method);
    void handle_typealias(const clang::TypeAliasDecl* alias);
};

class MatchBindingsConsumer : public clang::ASTConsumer {
    clang::ast_matchers::MatchFinder _match_finder;
    MatchBindingsCallback _handler;

public:
    explicit MatchBindingsConsumer(clang::ASTContext* context);
    virtual void HandleTranslationUnit(clang::ASTContext& context);
};

class MatchBindingsAction : public clang::ASTFrontendAction {
public:
    virtual std::unique_ptr<clang::ASTConsumer>
    CreateASTConsumer(clang::CompilerInstance& compiler, llvm::StringRef in_file) {
        return std::unique_ptr<clang::ASTConsumer>(
            new MatchBindingsConsumer(&compiler.getASTContext()));
    }
};

}
