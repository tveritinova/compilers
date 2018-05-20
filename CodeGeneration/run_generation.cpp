#include "../SymbolTable/tablevisitor.h"
#include "../SymbolTable/typechecker.h"
#include "../IR/IRTranslate.h"
#include "Canonizer.h"

extern Program *program;
extern int yyparse();

int main( int argc, char* argv[] ) {

    yyparse();

    TableVisitor* visitor = new TableVisitor();

    try {

        visitor->visit(program);
        Table table = visitor->get_table();
        TypeChecker checker(visitor->get_table());

        checker.ParseProgram(program);

        IRTranslate* translator = new IRTranslate(&table);

        program->accept(translator);

        CCodeFragment* body = translator->programTranslation;

        std::ofstream fout('code_generated.asm');

        while (body != nullptr) {
            Canonizer* canonizer = new Canonizer(body->body);
            canonizer->tree = translator->tree;
            canonizer->run();

            CodeGeneration* gen = new CodeGeneration(canonizer->body);
            const InstructionList list = gen->generate();

            fout << body->fragmentName << std::endl;
            fout << "---------" << std::endl;

            for(auto& l: list.Instructions) {
                fout  << l->Format() << std::endl;
            }

            body = body->next;
        }

    } catch(DeclarationException e) {

        std::cout << std::endl << "Declaration error: " << e.what() << std::endl;
    }
}