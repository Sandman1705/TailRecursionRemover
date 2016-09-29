#include "clang/AST/AST.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "clang/Lex/Lexer.h"
#include "clang/Basic/SourceLocation.h"
#include "clang/Basic/LangOptions.h"
#include <string>
#include <vector>

using namespace clang;

class FunctionVisitor : public RecursiveASTVisitor<FunctionVisitor> {
private:
    ASTContext *m_ast_context; // used for getting additional AST info

public:
    explicit FunctionVisitor(CompilerInstance *CI);

    virtual bool VisitFunctionDecl(FunctionDecl *func);

};
