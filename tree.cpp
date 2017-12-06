#include "AST/treeserializer.h"
#include "AST/grammar.h"
#include "tokens.h"

extern Program *program;
extern int yyparse();

int main() {
	printf("here\n");
    yyparse();
    TreeSerializer *ts = new TreeSerializer("./SyntaxTree.gv");
    program->accept(ts);
    delete ts;
}