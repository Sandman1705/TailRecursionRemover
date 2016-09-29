#include "TailRecursionEliminator.h"
#include "FunctionVisitor.h"

extern Rewriter rewriter;

std::string cut_out(std::string str_to_cut)
{
	size_t pos = str_to_cut.find_last_of(" *&");
	return std::string(str_to_cut,++pos);
}

std::string source_to_string(clang::SourceRange sr, clang::SourceManager &sm) {
    std::string text = Lexer::getSourceText(CharSourceRange::getTokenRange(sr), sm, LangOptions(), 0);
    if (text.at(text.size()-1) == ',')
        return Lexer::getSourceText(CharSourceRange::getCharRange(sr), sm, LangOptions(), 0);
    return text;
}

FunctionVisitor::FunctionVisitor(CompilerInstance *CI) 
  : m_ast_context(&(CI->getASTContext())) // initialize private members
{
    rewriter.setSourceMgr(m_ast_context->getSourceManager(), m_ast_context->getLangOpts());
}

bool FunctionVisitor::VisitFunctionDecl(FunctionDecl *func) 
{
	      
	if (func->getDefinition() == nullptr)  // If its only function definition then skip
		return true;

    std::string func_name = func->getNameInfo().getName().getAsString(); 
    //Geting vector of parametar names
	std::vector<std::string> param_names;
	for (auto i=func->param_begin(); i!=func->param_end(); ++i)
	{
		std::string param_str = cut_out(source_to_string((*i)->getSourceRange(),m_ast_context->getSourceManager()));
		param_names.push_back(param_str);
	}

	errs() << "* Visiting function " << func_name << "\n";
	
	TailRecursionEliminator tre(m_ast_context,func_name,param_names);
	tre.TraverseDecl(func);

	if (tre.hadTailRecursion()) // if visited function had tail recursions
	{
		if ( clang::CompoundStmt *block = dyn_cast<clang::CompoundStmt>(func->getBody()) )
		{ 
			//errs() << "Cast to CompoundStmt success" << std::endl;
			rewriter.InsertText(block->body_front()->getLocStart(),"/*START OF FUNCTION*/\nint repeat;\ndo\n{\nrepeat = 0;\n/*DONE*/\n",true,true);
			rewriter.InsertText(func->getDefinition()->getLocEnd(),"\t/*END OF FUNCTION*/\n\t}\n\twhile(repeat);\n\t/*DONE*/\n",true,true);
		}
		else
		{
			//errs() << "Cast to CompoundStmt fail" << std::endl;
		}
	}

	errs() << "* Visiting function end " << func_name << "\n";
    return true;
}
