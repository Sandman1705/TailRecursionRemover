#include "TailRecursionEliminator.h"

extern clang::LangOptions lang_opts;
extern clang::PrintingPolicy Policy;

std::string source_to_string(clang::SourceLocation start, clang::SourceLocation end, SourceManager &sm) {
	clang::SourceRange sr(start,end);
    std::string text = Lexer::getSourceText(CharSourceRange::getTokenRange(sr), sm, LangOptions(), 0);
    if (text.at(text.size()-1) == ',')
        return Lexer::getSourceText(CharSourceRange::getCharRange(sr), sm, LangOptions(), 0);
    return text;
}

std::string add_tmp(std::string expression, std::string variable)
{
	std::string to_return = expression;
	size_t start_pos = 0;
	size_t pos;
	while ( (pos = to_return.find(variable,start_pos)) != std::string::npos)
	{
		if ( std::isalnum(to_return[pos+variable.length()]) || to_return[pos+variable.length()]=='_')
		{
			do
			{
				pos++;
			} while ( std::isalnum(to_return[pos+variable.length()]) || to_return[pos+variable.length()]=='_');
			start_pos = pos+variable.length();		
		}
		else
		{	
			to_return = to_return.insert(pos,"_tmp_");
			start_pos = pos + 6;
		}
	} 
	return to_return;
}


TailRecursionEliminator::TailRecursionEliminator(ASTContext *ast_context, std::string func_name, std::vector<std::string>& param_names) 
      : m_ast_context(ast_context), // initialize private members
		m_func_name(func_name),
		m_param_names(param_names),
		m_tail_recursion(false)
{
    rewriter.setSourceMgr(m_ast_context->getSourceManager(), m_ast_context->getLangOpts());
}


bool TailRecursionEliminator::VisitFunctionDecl(FunctionDecl *func) 
{     
	if ( clang::CompoundStmt *block = dyn_cast<clang::CompoundStmt>(func->getBody()) )
	{ 
		errs() << "****Cast to CompoundStmt success\n";
		if (clang::CallExpr *call = dyn_cast<clang::CallExpr>(block->body_back()))
		{
			errs() << "****Cast to CallExpr success - this is a tail call\n";
			return ChangeCallExpr(call);
		
		}
		else if (clang::IfStmt *ifstmt = dyn_cast<clang::IfStmt>(block->body_back()))
		{
			errs() << "****Cast to CallIfStmt success\n";
			bool success;
			if ( ifstmt->getThen() )
			{
				success = ThenElseCheck( ifstmt->getThen() );
				if (!success)
					return success;				
			}				
			if ( ifstmt->getElse() )
				return ThenElseCheck( ifstmt->getElse() );
		}
		else
		{
			errs() << "****Cast to CallExpr and CallIfStmt fail - no recursion here\n";
		}
	}
	else
	{
		errs() << "****Cast to CompoundStmt fail\n";
	}
	return true;
}

bool TailRecursionEliminator::ThenElseCheck(clang::Stmt* stmt)
{
	if (clang::CallExpr *call = dyn_cast<clang::CallExpr>(stmt))
	{
		errs() << "****Cast to CallExpr success - this is a tail call\n";
		return ChangeCallExpr(call,true);
	}
	else if ( clang::CompoundStmt *block = dyn_cast<clang::CompoundStmt>(stmt) )
	{ 
		errs() << "****Cast to CompoundStmt success\n";
		if (clang::CallExpr *call = dyn_cast<clang::CallExpr>(block->body_back()))
		{
			errs() << "****Cast to CallExpr success - this is a tail call\n";
			return ChangeCallExpr(call);
		}
		else if (clang::IfStmt *ifstmt = dyn_cast<clang::IfStmt>(block->body_back()))
		{
			errs() << "****Cast to CallIfStmt success\n";
			if ( ifstmt->getThen() )
				ThenElseCheck( ifstmt->getThen() );
			if ( ifstmt->getElse() )
				ThenElseCheck( ifstmt->getElse() );
		}
		else
		{
			errs() << "*Cast to CallExpr and CallIfStmt fail - no recursion here\n";
		}
	}
	return true;
}

bool TailRecursionEliminator::hadTailRecursion()
{
	return m_tail_recursion;
}

void TailRecursionEliminator::doneTailRecursion()
{
	m_tail_recursion=true;
}

bool TailRecursionEliminator::VisitReturnStmt(ReturnStmt *ret) 
{      
    errs() << "** VisitReturnStmt start\n";	

	if (ret->getRetValue() == nullptr )
	{
		return true;
	}
	if ( clang::CallExpr* call = dyn_cast<clang::CallExpr>(ret->getRetValue()) )
	{
		errs() << "***Cast to CallExpr success - this is a tail call\n";
		std::string function_call = source_to_string(call->getLocStart(),call->getLocEnd(),m_ast_context->getSourceManager());

		if ( function_call.compare(0,m_func_name.length(),m_func_name) == 0) // is recursion call
		{
			RemoveReturnExprInCode(ret->getLocStart());
			return ChangeCallExpr(call,true);
		}
	}
    return true;
}


void TailRecursionEliminator::RemoveReturnExprInCode(clang::SourceLocation ret_start)
{
	rewriter.ReplaceText(ret_start, 7, "");
}

bool TailRecursionEliminator::ChangeCallExpr(CallExpr *call, bool with_block) {
    errs() << "** VisitCallExpr start\n";			

	std::string function_call = source_to_string(call->getLocStart(),call->getLocEnd(),m_ast_context->getSourceManager());

	if ( function_call.compare(0,m_func_name.length(),m_func_name) == 0) // is recursion call
	{

		std::stringstream sstr;
		if (with_block)
			sstr << "{\n";
		sstr << "//TAIL RECURSION REMOVED\n";
		auto k=m_param_names.cbegin(); 
		for (int i=0; k!=m_param_names.cend(); ++k, ++i)
		{
			std::string TypeS;
			llvm::raw_string_ostream s(TypeS);
			call->getArg(i)->printPretty(s, 0, Policy);
			sstr << QualType::getAsString(call->getArg(i)->getType().split()) << " _tmp_" << *k << " = " << *k << ";\n"; 
		}
		
		std::vector<std::string> new_param_values;
		for (int i=0, j=call->getNumArgs(); i<j; ++i)
		{
			std::string TypeS;
			llvm::raw_string_ostream s(TypeS);
			call->getArg(i)->printPretty(s, 0, Policy);

			std::string new_string = s.str();
			for (k=m_param_names.cbegin(); k!=m_param_names.cend(); ++k)
			{
				new_string = add_tmp(new_string,*k);
			}
			new_param_values.push_back(new_string);
		}

		k=m_param_names.cbegin();
		for (auto i=new_param_values.cbegin(); k!=m_param_names.cend(); ++k, ++i)
		{
			sstr << *k << " = " << *i << ";\n"; 
		}
		   
		sstr << "repeat = 1;"; 		
		if (with_block)
			sstr << "\n}";
		rewriter.ReplaceText(call->getLocStart(), function_call.length()+1 , "");
		rewriter.InsertText(call->getLocStart(),sstr.str(),true,true);
		doneTailRecursion();
        errs() << "*** Rewrote function\n";
	}  
    return true;
}
