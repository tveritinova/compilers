#ifndef TREESERIALIZER_H
#define TREESERIALIZER_H


#include <string>
#include <array>
#include <fstream>
#include <queue>

#include "visitor.h"
#include "grammar_declaration.h"
#include "../SymbolTable/Symbol.h"

class TreeSerializer: public Visitor {
public:
    TreeSerializer(std::string path);
    ~TreeSerializer();

    //std::string ast_tree_to_dot(const Program* program);

    void visit(const Program*) override;
    void visit(const SymbolTable::Symbol*) override;

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
    void visit(const IdExpression*) override;
    void visit(const ThisExpression*) override;
    void visit(const IntExpression*) override;
    void visit(const BoolExpression*) override;
    void visit(const MethodCallExpression*) override;
    void visit(const SubscriptExpression*) override;
    void visit(const NewIntArrayExpression*) override;
    void visit(const NewObjectExpression*) override;
    void visit(const BinaryExpression*) override;
    void visit(const NegationExpression*) override;

private:
    enum SyntaxType
    {
        PROGRAM,
        SYMBOL,
        INTEGER,
        MAIN_CLASS,
        CLASS_DECL_LIST,
        CLASS_DECL,
        VAR_DECL_LIST,
        VAR_DECL,
        METHOD_DECL_LIST,
        METHOD_DECL,
        ARGUMENT_LIST,
        STATEMENT_LIST,
        ASSIGN_SUBSCRIPT_STATEMENT,
        PRINT_STATEMENT,
        IF_STATEMENT,
        WHILE_STATEMENT,
        ASSIGN_STATEMENT,
        SCOPED_STATEMENT,
        EXPRESSION_LIST,
        LENGTH_EXPRESSION,
        ID_EXPRESSION,
        THIS_EXPRESSION,
        INT_EXPRESSION,
        BOOL_EXPRESSION,
        METHOD_CALL_EXPRESSION,
        SUBSCRIPT_EXPRESSION,
        PARENTHESIZED_EXPRESSION,
        NEW_ARRAY_EXPRESSION,
        NEW_OBJECT_EXPRESSION,
        BINARY_EXPRESSION,
        NEGATION_EXPRESSION,
    };

    static const std::size_t NUM_SYNTAX_TYPES = NEGATION_EXPRESSION + 1;

    std::ofstream dot_stream_;
    SyntaxType parent_;
    std::array<std::size_t, NUM_SYNTAX_TYPES> syntax_counter_;
    std::array<std::string, NUM_SYNTAX_TYPES> syntax_label_;

    void add_edge_(SyntaxType from, SyntaxType to);
    void add_vertex_(SyntaxType syntax_type);
};

#endif //TREESERIALIZER_H