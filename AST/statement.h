
#ifndef H_STATEMENT
#define H_STATEMENT


#include "../SymbolTable/Symbol.h"

class Statement : public Visitable {};

class StatementList : public Statement {

public:

    StatementList(Statement* statement, StatementList* other_statements)
        : statement_(statement), other_statements_(other_statements) {}

    virtual void accept(Visitor* visitor) const override {
        visitor->visit(this);
    }

    std::vector<Statement*> getVector() {

        std::vector<Statement*>* res = new std::vector<Statement*>();

        StatementList* cur = this->other_statements_;

        while (cur != nullptr) {
            res->push_back(cur->statement_);
            cur = cur->other_statements_;
        }

        return *res;
    }

    Statement* statement_;
    StatementList* other_statements_;
};

class IfStatement : public Statement {

public:

    IfStatement(const Expression* if_condition, const Statement* statement_if_true,
        const Statement* statement_if_false, Position _pos)
        : if_condition_(if_condition), 
        statement_if_true_(statement_if_true), 
        statement_if_false_(statement_if_false) { pos = _pos; }

    virtual void accept(Visitor* visitor) const override {
        visitor->visit(this);
    }

    const Expression* if_condition_;
    const Statement* statement_if_true_;
    const Statement* statement_if_false_;
};

class WhileStatement : public Statement {

public:

    WhileStatement(const Expression* loop_condition, const Statement* inloop_statement, Position _pos)
        : loop_condition_(loop_condition), inloop_statement_(inloop_statement) { pos = _pos; }

    virtual void accept(Visitor* visitor) const override {
        visitor->visit(this);
    }

    const Expression* loop_condition_;
    const Statement* inloop_statement_;
};

class PrintStatement : public Statement {

public:

    PrintStatement(const Expression* expression_to_print, Position _pos) : expression_to_print_(expression_to_print) {
         pos = _pos; 
    }

    virtual void accept(Visitor* visitor) const override {
        visitor->visit(this);
    }

    const Expression* expression_to_print_;
};

class AssignStatement : public Statement {

public:

    AssignStatement(const SymbolTable::Symbol* lhs_var_id, const Expression* rhs_expression, Position _pos)
        : lhs_var_id_(lhs_var_id), rhs_expression_(rhs_expression) { pos = _pos; }

    virtual void accept(Visitor* visitor) const override {
        visitor->visit(this);
    }

    const SymbolTable::Symbol* lhs_var_id_;
    const Expression* rhs_expression_;
};

class AssignSubscriptStatement : public Statement {

public:

    AssignSubscriptStatement(const SymbolTable::Symbol* lhs_array_id, const Expression* subscript,
        const Expression* rhs_expression, Position _pos)
        : lhs_array_id_(lhs_array_id), subscript_(subscript), rhs_expression_(rhs_expression) { pos = _pos; }

    virtual void accept(Visitor* visitor) const override {
        visitor->visit(this);
    }

    const SymbolTable::Symbol* lhs_array_id_;
    const Expression* subscript_;
    const Expression* rhs_expression_;
};

#endif