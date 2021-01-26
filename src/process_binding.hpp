#include <clang/AST/ASTConsumer.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/ASTMatchers/ASTMatchFinder.h>
#include <clang/ASTMatchers/ASTMatchers.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendAction.h>

#include "exports.hpp"

namespace cppmm {

class ProcessBindingCallback : public clang::ast_matchers::MatchFinder::MatchCallback {
    virtual void run(const clang::ast_matchers::MatchFinder::MatchResult& result);
};

class ProcessBindingConsumer : public clang::ASTConsumer {
    clang::ast_matchers::MatchFinder _match_finder;
    ProcessBindingCallback _handler;

public:
    explicit ProcessBindingConsumer(clang::ASTContext* context);
    virtual void HandleTranslationUnit(clang::ASTContext& context);
};

class ProcessBindingAction : public clang::ASTFrontendAction {
public:
    virtual std::unique_ptr<clang::ASTConsumer>
    CreateASTConsumer(clang::CompilerInstance& compiler, llvm::StringRef in_file) {
        return std::unique_ptr<clang::ASTConsumer>(
            new ProcessBindingConsumer(&compiler.getASTContext()));
    }
};

}
