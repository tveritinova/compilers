
all: parser 

parser: parser.o lex.o visitor.o tree.o 
	g++ --std=c++14 -Wno-write-strings -o parser visitor.o parser.o lex.o tree.o

tree.o: 
	g++ -g -c --std=c++14 tree.cpp -o tree.o

parser.o:  bison_code
	bison --graph -dt --verbose bison_code && mv bison_code.tab.h tokens.h && mv bison_code.tab.c parser.cpp && g++ -g -c --std=c++11 parser.cpp -o parser.o

lex.o: flex_code
	flex++ flex_code && g++ -g --std=c++14 -c lex.yy.cc -o lex.o

visitor.o: AST/treeserializer.cpp 
	g++ -g -c --std=c++14 AST/treeserializer.cpp -o visitor.o

clean:
	rm  lex.yy.cc parser.cpp tokens.h lex.o visitor.o parser.o parser Table.o Symbol.o ClassInfo.o MethodInfo.o table_.o