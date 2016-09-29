#include "clang/Driver/Options.h"
#include "clang/AST/AST.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/ASTConsumers.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "clang/Lex/Lexer.h"
#include "clang/Basic/SourceLocation.h"
#include "clang/Basic/LangOptions.h"
#include <string>
#include <sstream>
#include <vector>

#include "TailRecursionASTConsumer.h"

using namespace std;
using namespace clang;
using namespace clang::driver;
using namespace clang::tooling;
using namespace llvm;

Rewriter rewriter;
static llvm::cl::OptionCategory MyToolCategory("my-tool options");
clang::SourceManager *sm;
clang::LangOptions lang_opts;
clang::PrintingPolicy Policy(lang_opts);


class TailRecursionFrontendAction : public ASTFrontendAction {
public:
    virtual std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &CI, StringRef file) {
        return std::unique_ptr<TailRecursionASTConsumer> (new TailRecursionASTConsumer(&CI)); // pass CI pointer to ASTConsumer
    }
};

class TailRecursionFrontendActionFactory : public FrontendActionFactory
{
public:
	clang::FrontendAction* create()
	{
		return new TailRecursionFrontendAction();
	}
};

int main(int argc, const char **argv)
{
    // parse the command-line args passed to our code
    CommonOptionsParser op(argc, argv, MyToolCategory);        
    // create a new Clang Tool instance (a LibTooling environment)
    ClangTool Tool(op.getCompilations(), op.getSourcePathList());

    // run the Clang Tool, creating a new FrontendAction
    int result = Tool.run(new TailRecursionFrontendActionFactory());

    // print out the rewritten source code
    rewriter.getEditBuffer(rewriter.getSourceMgr().getMainFileID()).write(outs());

    return result;
}
