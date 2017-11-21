all: parser

parser: parser.o lex.o visitor.o
	g++ --std=c++11 -Wno-write-strings -o parser visitor.o lex.o parser.o

parser.o:  bison_code
	bison --graph -dt --verbose bison_code && mv bison_code.tab.h tokens.h && mv bison_code.tab.c parser.cpp && g++ -c --std=c++11 parser.cpp -o parser.o

lex.o: flex_code
	flex++ flex_code && g++ -c --std=c++11 lex.yy.cc -o lex.o

visitor.o: treeserializer.cpp 
	g++ -c --std=c++11 treeserializer.cpp -o visitor.o

clean:
	rm  lex.yy.cc parser.cpp tokens.h lex.o visitor.o parser.o parser