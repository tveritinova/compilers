
all: parser table irtree

irtree: tablevisitor.o Symbol.o MethodInfo.o lex.o parser.o Table.o ClassInfo.o IRTranslate.o X86MiniJavaFrame.o visitor.o tablevisitor.o
	g++ -g --std=c++14 -Wno-write-strings irtree_exec.cpp -o irtree Symbol.o MethodInfo.o lex.o parser.o Table.o ClassInfo.o IRTranslate.o X86MiniJavaFrame.o visitor.o typechecker.o

IRTranslate.o:
	g++ -g --std=c++14 -c IR/IRTranslate.cpp -o IRTranslate.o

X86MiniJavaFrame.o:
	g++ -g --std=c++14  -c ActivationRecords/X86MiniJavaFrame.cpp -o X86MiniJavaFrame.o

table: Table.o Symbol.o ClassInfo.o MethodInfo.o tablevisitor.o parser.o lex.o visitor.o table_.o 
	g++ -g --std=c++14 -Wno-write-strings -o table Table.o Symbol.o ClassInfo.o MethodInfo.o typechecker.o visitor.o parser.o lex.o table_.o 

table_.o:
	g++ -g --std=c++14 -c table_.cpp -o table_.o

Table.o:
	g++ -g --std=c++14  -c SymbolTable/Table.cpp -o Table.o

Symbol.o:
	g++ -g --std=c++14  -c SymbolTable/Symbol.cpp -o Symbol.o

ClassInfo.o:
	g++ -g --std=c++14  -c SymbolTable/ClassInfo.cpp -o ClassInfo.o

MethodInfo.o:
	g++ -g --std=c++14  -c SymbolTable/MethodInfo.cpp -o MethodInfo.o

tablevisitor.o:
	g++ -g --std=c++14  -c SymbolTable/typechecker.cpp -o typechecker.o

parser: parser.o lex.o visitor.o tree.o Symbol.o
	g++ --std=c++14 -Wno-write-strings -o parser visitor.o parser.o lex.o tree.o Symbol.o

tree.o: 
	g++ -g -c --std=c++14 tree.cpp -o tree.o

parser.o:  bison_code
	bison --graph -dt --verbose bison_code && g++ -g -c --std=c++11 bison_code.tab.c -o parser.o

lex.o: flex_code
	flex++ flex_code && g++ -g --std=c++14 -c lex.yy.cc -o lex.o

visitor.o: AST/treeserializer.cpp 
	g++ -g -c --std=c++14 AST/treeserializer.cpp -o visitor.o

clean:
	rm  lex.yy.cc bison_code.tab.c bison_code.tab.h lex.o visitor.o parser.o parser Table.o Symbol.o ClassInfo.o MethodInfo.o table_.o tree.o typechecker.o X86MiniJavaFrame.o irtree table IRTranslate.o






	