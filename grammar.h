
#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "visitor.h"
#include "grammar_declaration.h"
#include <vector>
#include <string>


class Program : public Visitable {

public:
    Program(const MainClass* main_class, const ClassDeclList* other_classes) :
        _main_class(main_class), _classes(other_classes)
    { }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

    const MainClass* _main_class;
    const ClassDeclList* _classes;
};

class Symbol : public Visitable
{
public:
    Symbol(std::string str) : str_(std::move(str)) {}

    const std::string& to_string() const
    {
        return str_;
    }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

    std::string str_;
};

class MainClass: public Visitable
{
public:
    MainClass(const Symbol* class_id, const Symbol* main_argv_id, const Statement* main_body)
        : _class_id(class_id), _main_argv_id(main_argv_id), _main_body(main_body)
    { }  

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

    const Symbol* _class_id;
    const Symbol* _main_argv_id;
    const Statement* _main_body;
};

class ClassDecl: public Visitable
{
public:
    ClassDecl(const Symbol* class_id, const Symbol* base_class_id,
        const VarDeclList* variables, const MethodDeclList* methods)
        : _class_id(class_id), _base_class_id(base_class_id), _vars(variables), _methods(methods)
    { }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

    const Symbol* _class_id;
    const Symbol* _base_class_id;
    const VarDeclList* _vars;
    const MethodDeclList* _methods;
};

class ClassDeclList: public Visitable
{
public:
    ClassDeclList(const ClassDecl* new_class, const ClassDeclList* other_classes)
        : _new_class(new_class), _other_classes(other_classes)
    { }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }


    const ClassDecl* _new_class;
    const ClassDeclList* _other_classes;
};

class VarDecl: public Visitable
{
public:
    VarDecl(const Type* type, const Symbol* var_id)
        : _type(type), _var_id(var_id)
    { }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

    const Type* _type;
    const Symbol* _var_id;
};

class VarDeclList: public Visitable
{
public:
    VarDeclList(const VarDecl* var_decl, const VarDeclList* other_var_decls)
        : _var_dec(var_decl), _other_var_decs(other_var_decls)
    { }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

    const VarDecl* _var_dec;
    const VarDeclList* _other_var_decs;
};

class MethodDeclList: public Visitable
{
public:
    MethodDeclList(const MethodDecl* method, const MethodDeclList* other_methods_decls)
        : method_decl_(method), other_methods_decls_(other_methods_decls)
    { }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

    const MethodDecl* method_decl_;
    const MethodDeclList* other_methods_decls_;
};

class MethodDecl: public Visitable
{
public:
    MethodDecl(const Type* return_type, const Symbol* method_id, const ArgumentList* arg_list,
        const VarDeclList* var_decls, const StatementList* statements, const Expression* return_expression)
        : return_type_(return_type), method_id_(method_id), arg_list_(arg_list),
          var_decls_(var_decls), statements_(statements), return_expression_(return_expression) {}
    
    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

    const Type* return_type_;
    const Symbol* method_id_;
    const ArgumentList* arg_list_;
    const VarDeclList* var_decls_;
    const StatementList* statements_;
    const Expression* return_expression_;
};

class ArgumentList: public Visitable
{
public:
    ArgumentList(const Type* arg_type, const Symbol* arg_id, const ArgumentList* other_args)
        : arg_type_(arg_type), arg_id_(arg_id), other_args_(other_args)
    { }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

    const Type* arg_type_;
    const Symbol* arg_id_;
    const ArgumentList* other_args_;
};

class Statement : public Visitable
{ };

class StatementList : public Statement
{
public:
    StatementList(Statement* statement, StatementList* other_statements)
        : statement_(statement), other_statements_(other_statements)
    { }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

    std::vector<Statement * > getVector(){

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

class IfStatement : public Statement
{
public:
    IfStatement(const Expression* if_condition, const Statement* statement_if_true,
        const Statement* statement_if_false)
        : if_condition_(if_condition), statement_if_true_(statement_if_true), statement_if_false_(statement_if_false)
    { }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

    const Expression* if_condition_;
    const Statement* statement_if_true_;
    const Statement* statement_if_false_;
};

class WhileStatement : public Statement
{
public:
    WhileStatement(const Expression* loop_condition, const Statement* inloop_statement)
        : loop_condition_(loop_condition), inloop_statement_(inloop_statement)
    { }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

    const Expression* loop_condition_;
    const Statement* inloop_statement_;
};

class PrintStatement : public Statement
{
public:
    PrintStatement(const Expression* expression_to_print) : expression_to_print_(expression_to_print)
    { }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

    const Expression* expression_to_print_;
};

class AssignStatement : public Statement
{
public:
    AssignStatement(const Symbol* lhs_var_id, const Expression* rhs_expression)
        : lhs_var_id_(lhs_var_id), rhs_expression_(rhs_expression)
    { }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

    const Symbol* lhs_var_id_;
    const Expression* rhs_expression_;
};

class AssignSubscriptStatement : public Statement
{
public:
    AssignSubscriptStatement(const Symbol* lhs_array_id, const Expression* subscript,
        const Expression* rhs_expression)
        : lhs_array_id_(lhs_array_id), subscript_(subscript), rhs_expression_(rhs_expression)
    { }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

    const Symbol* lhs_array_id_;
    const Expression* subscript_;
    const Expression* rhs_expression_;
};

class ExpressionList : public Visitable
{
public:
    ExpressionList(const Expression* expression, const ExpressionList* other_expressions)
        : expression_(expression), other_expressions_(other_expressions)
    { }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

/*private:*/
    const Expression* expression_;
    const ExpressionList* other_expressions_;
};

struct Expression : public Visitable
{ };

enum class BinaryOperator 
{
    ADD_, SUB_, MUL_, DIV_, MOD_, AND_, OR_, LESS_
};

class BinaryExpression : public Expression
{
public:
    BinaryExpression(const Expression* lhs_expression, BinaryOperator binary_operator,
        const Expression* rhs_expression)
        : lhs_expression_(lhs_expression), binary_operator_(binary_operator), rhs_expression_(rhs_expression)
    { }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

/*private:*/
    const Expression* lhs_expression_;
    BinaryOperator binary_operator_;
    const Expression* rhs_expression_;
};

class SubscriptExpression : public Expression
{
public:
    SubscriptExpression(const Expression* expression, const Expression* subscript)
        : expression_(expression), subscript_(subscript)
    { }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

/*private:*/
    const Expression* expression_;
    const Expression* subscript_;
};

class LengthExpression : public Expression
{
public:
    LengthExpression(const Expression* expression) : expression_(expression)
    { }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

/*private:*/
    const Expression* expression_;
};

class MethodCallExpression : public Expression
{
public:
    MethodCallExpression(const Expression* expression, const Symbol* method_id,
        const ExpressionList* other_expressions)
        : expression_(expression), method_id_(method_id), other_expressions_(other_expressions)
    { }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

/*private:*/
    const Expression* expression_;
    const Symbol* method_id_;
    const ExpressionList* other_expressions_;
};

class IntExpression : public Expression
{
public:
    IntExpression(int val_) : val(val_)
    { }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

    const int val;
};

class BoolExpression : public Expression
{
public:
    BoolExpression(bool b) : b_(b)
    { }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

/*private:*/
    bool b_;
};

class IdExpression : public Expression
{
public:
    IdExpression(const Symbol* id) : id_(id)
    { }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

/*private:*/
    const Symbol* id_;
};

class ThisExpression : public Expression
{
    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }
};

class NewIntArrayExpression : public Expression
{
public:
    NewIntArrayExpression(const Expression* subscript_expression)
        : subscript_expression_(subscript_expression)
    { }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

    const Expression* subscript_expression_;
};

class NewObjectExpression : public Expression
{
public:
    NewObjectExpression(Symbol* type) : new_object_type_(type)
    { }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

    Symbol* new_object_type_;
};

class NegationExpression : public Expression
{
public:
    NegationExpression(const Expression* expression) : expression_to_negate_(expression)
    { }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

/*private:*/
    const Expression* expression_to_negate_;
};

class UnaryMinusExpression : public Expression
{
public:
    UnaryMinusExpression(const Expression* expression) : expression_(expression)
    { }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

    const Expression* expression_;
};

class Type
{
public:
    std::string label;
};

enum BasicTypes {
    INT_, 
    BOOL_, 
    INT_ARRAY_
};

class BasicType: public Type {
public:

    BasicType(BasicTypes type_): type(type_){
        if (type == INT_) label = "int";
        if (type == BOOL_) label = "bool";
        if (type == INT_ARRAY_) label = "int[]";
    }

    BasicTypes type;
};

class ClassType: public Type {

public:
    ClassType(Symbol * id_): id(id_) {

        label = id->str_;
    
    }
    
    Symbol* id;
};


#endif

