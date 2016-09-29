CLANG_LIBS := -lclangTooling -lclangFrontendTool -lclangFrontend -lclangDriver -lclangSerialization -lclangCodeGen -lclangParse -lclangSema -lclangStaticAnalyzerFrontend -lclangStaticAnalyzerCheckers -lclangStaticAnalyzerCore -lclangAnalysis -lclangARCMigrate -lclangRewrite -lclangRewriteFrontend -lclangEdit -lclangAST -lclangLex -lclangBasic -lclang

tool : tool.cpp TailRecursionEliminator.o FunctionVisitor.o TailRecursionASTConsumer.o
	g++ `llvm-config --cxxflags --ldflags` tool.cpp $(CLANG_LIBS) `llvm-config --libs --system-libs` -std=c++11 -o tool TailRecursionEliminator.o FunctionVisitor.o TailRecursionASTConsumer.o

TailRecursionEliminator.o : TailRecursionEliminator.h TailRecursionEliminator.cpp
	 g++ `llvm-config --cxxflags --ldflags` TailRecursionEliminator.cpp `llvm-config --libs --system-libs` -std=c++11 -o TailRecursionEliminator.o -c

FunctionVisitor.o : FunctionVisitor.h FunctionVisitor.cpp
	g++ `llvm-config --cxxflags --ldflags` FunctionVisitor.cpp `llvm-config --libs --system-libs` -std=c++11 -o FunctionVisitor.o -c

TailRecursionASTConsumer.o : TailRecursionASTConsumer.h TailRecursionASTConsumer.cpp
	g++ `llvm-config --cxxflags --ldflags` TailRecursionASTConsumer.cpp `llvm-config --libs --system-libs` -std=c++11 -o TailRecursionASTConsumer.o -c

.PHONY: clean

clean: 
	rm *.o tool

