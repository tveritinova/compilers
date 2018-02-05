
#include "AST/grammar.h"
#include "SymbolTable/tablevisitor.h"
#include "SymbolTable/typechecker.h"
#include "IR/IRTranslate.h"

extern Program *program;
extern int yyparse();

int main( int argc, char* argv[] ) {

	yyparse();

	TableVisitor* visitor = new TableVisitor();

    try {

        //std::cout << "heree" << std::endl;

        visitor->visit(program);

        //std::cout << "heree2" << std::endl;

        Table table = visitor->get_table();

        //std::cout << "before checker" << std::endl;
        
        TypeChecker checker(visitor->get_table());

        //std::cout << "before checker parse" << std::endl;

        checker.ParseProgram(program);

        //std::cout << "after parse" << std::endl;

        //ActivationRecords::FrameFiller frameFiller(&table);        

        //std::cout << "before fill" << std::endl;

		//frameFiller.Fill();

		IRTranslate* translator = new IRTranslate(&table);

        //std::cout << "before translate" << std::endl;

        program->accept(translator);

        //translator->print_tree();

    } catch(DeclarationException e) {

        std::cout << std::endl << "Declaration error: " << e.what() << std::endl;
    }

    //Printer p;
	//p.visit(prog);
}