#include "TailRecursionASTConsumer.h"

// override the constructor in order to pass CI
TailRecursionASTConsumer::TailRecursionASTConsumer(CompilerInstance *CI)
    : visitor(new FunctionVisitor(CI)) // initialize the visitor
{ }

// override this to call our FunctionVisitor on each top-level Decl
bool TailRecursionASTConsumer::HandleTopLevelDecl(DeclGroupRef DG) {
    // a DeclGroupRef may have multiple Decls, so we iterate through each one
    for (DeclGroupRef::iterator i = DG.begin(), e = DG.end(); i != e; i++) {
        Decl *D = *i;    
        visitor->TraverseDecl(D); // recursively visit each AST node in Decl "D"
    }
    return true;
}
