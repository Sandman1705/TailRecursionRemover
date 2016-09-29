#include "clang/Frontend/ASTConsumers.h"
#include "clang/Frontend/CompilerInstance.h"

#include "FunctionVisitor.h"

using namespace clang;

class TailRecursionASTConsumer : public ASTConsumer {
private:
    FunctionVisitor *visitor;

public:
    // override the constructor in order to pass CI
    explicit TailRecursionASTConsumer(CompilerInstance *CI);

    // override this to call our FunctionVisitor on each top-level Decl
    virtual bool HandleTopLevelDecl(DeclGroupRef DG);

};