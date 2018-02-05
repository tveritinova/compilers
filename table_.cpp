#include "SymbolTable/tablevisitor.h"
#include "SymbolTable/typechecker.h"
#include "bison_code.tab.h"
#include "AST/grammar.h"
#include "SymbolTable/DeclarationException.h"

extern Program *program;
extern int yyparse();

int main(void) {
    yyparse();

    TableVisitor* visitor = new TableVisitor();

    try {
        visitor->visit(program);
        
        TypeChecker checker(visitor->get_table());

        checker.ParseProgram(program);

    } catch(DeclarationException e) {
        std::cout << std::endl << "Declaration error: " << e.what() << std::endl;
    }

}