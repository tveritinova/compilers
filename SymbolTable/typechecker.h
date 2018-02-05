#ifndef TABLEINITIALIZER_H
#define TABLEINITIALIZER_H

#include "../AST/visitor.h"
#include "Table.h"
#include <stack>



class TypeChecker : public Visitor {

public:

    ~TypeChecker() override {}
    TypeChecker(Table _table) : types(), table(_table) {}

    void ParseProgram(const Program* program) { program->accept(this); }


    void visit(const Program*) override;
    void visit(const Symbol*) override {}

    void visit(const MainClass*) override;
    void visit(const ClassDeclList*) override;
    void visit(const ClassDecl*) override;
    void visit(const VarDeclList*) override;
    void visit(const VarDecl*) override;
    void visit(const MethodDeclList*) override;
    void visit(const MethodDecl*) override;
    void visit(const ArgumentList*) override;

    void visit(const StatementList*) override;
    void visit(const AssignSubscriptStatement*) override;
    void visit(const PrintStatement*) override;
    void visit(const IfStatement*) override;
    void visit(const WhileStatement*) override;
    void visit(const AssignStatement*) override;

    void visit(const ExpressionList*) override;
    void visit(const LengthExpression*) override;
    void visit(const NewIntArrayExpression*) override;
    void visit(const NewObjectExpression*) override;
    void visit(const BinaryExpression*) override;
    void visit(const NegationExpression*) override;

    void visit(const IdExpression*) override;
    void visit(const ThisExpression*) override;
    void visit(const IntExpression*) override;
    void visit(const BoolExpression*) override;
    void visit(const MethodCallExpression*) override;
    void visit(const SubscriptExpression*) override;

private:

    Table table;
    std::stack<const Symbol*> types;

    const ClassInfo* current_class;
    const MethodInfo* current_method;
};

#endif //TABLEINITIALIZER_H