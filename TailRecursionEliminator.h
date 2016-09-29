#include "clang/AST/AST.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "clang/Lex/Lexer.h"
#include "clang/Basic/SourceLocation.h"
#include "clang/Basic/LangOptions.h"
#include <string>
#include <sstream>
#include <vector>

using namespace clang;
using namespace llvm;

extern clang::Rewriter rewriter;
extern clang::SourceManager *sm;

class TailRecursionEliminator : public clang::RecursiveASTVisitor<TailRecursionEliminator> {
private:
    clang::ASTContext *m_ast_context; // used for getting additional AST info
	std::string m_func_name;
	std::vector<std::string> &m_param_names;
	bool m_tail_recursion;

public:
    explicit TailRecursionEliminator(clang::ASTContext *ast_context, std::string func_name, std::vector<std::string>& param_names);

    virtual bool VisitFunctionDecl(clang::FunctionDecl *func);
	bool ThenElseCheck(clang::Stmt* stmt);
	bool hadTailRecursion();
	void doneTailRecursion();
	virtual bool VisitReturnStmt(ReturnStmt *ret);
	void RemoveReturnExprInCode(clang::SourceLocation ret_start);
    bool ChangeCallExpr(CallExpr *call, bool with_block=false);

};