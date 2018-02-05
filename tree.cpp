#include "AST/treeserializer.h"
#include "AST/grammar.h"
#include "bison_code.tab.h"

extern Program *program;
extern int yyparse();

int main() {
    yyparse();
    TreeSerializer *ts = new TreeSerializer("./SyntaxTree.gv");
    program->accept(ts);
    delete ts;
}
