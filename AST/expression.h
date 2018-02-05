
#ifndef H_EXPRESSION
#define H_EXPRESSION

class ExpressionList : public Visitable {

public:
    
    ExpressionList(const Expression* expression, const ExpressionList* other_expressions)
        : expression_(expression), other_expressions_(other_expressions) {}

    virtual void accept(Visitor* visitor) const override {
        visitor->visit(this);
    }

    const Expression* expression_;
    const ExpressionList* other_expressions_;
};

class Expression : public Visitable {};

enum class BinaryOperator {
    ADD_, SUB_, MUL_, DIV_, AND_, LESS_
};

class BinaryExpression : public Expression {

public:
    
    BinaryExpression(const Expression* lhs_expression, BinaryOperator binary_operator,
        const Expression* rhs_expression, Position pos)
        : lhs_expression_(lhs_expression), 
        binary_operator_(binary_operator), 
        rhs_expression_(rhs_expression) { this->pos = pos; }

    virtual void accept(Visitor* visitor) const override {
        visitor->visit(this);
    }

    const Expression* lhs_expression_;
    BinaryOperator binary_operator_;
    const Expression* rhs_expression_;
};

class SubscriptExpression : public Expression {

public:
    
    SubscriptExpression(const Expression* expression, const Expression* subscript, Position pos)
        : expression_(expression), subscript_(subscript) { this->pos = pos; }

    virtual void accept(Visitor* visitor) const override {
        visitor->visit(this);
    }

    const Expression* expression_;
    const Expression* subscript_;
};

class LengthExpression : public Expression {

public:
    
    LengthExpression(const Expression* expression, Position pos) : expression_(expression) { this->pos = pos; }

    virtual void accept(Visitor* visitor) const override {
        visitor->visit(this);
    }

    const Expression* expression_;
};

class MethodCallExpression : public Expression {

public:

    MethodCallExpression(const Expression* expression, const SymbolTable::Symbol* method_id,
        const ExpressionList* other_expressions, Position pos)
        : expression_(expression), 
        method_id_(method_id), 
        other_expressions_(other_expressions) { this->pos = pos; }

    virtual void accept(Visitor* visitor) const override {
        visitor->visit(this);
    }

    const Expression* expression_;
    const SymbolTable::Symbol* method_id_;
    const ExpressionList* other_expressions_;
};

class IntExpression : public Expression {

public:
    
    IntExpression(int val_, Position pos) : val(val_) { this->pos = pos; }

    virtual void accept(Visitor* visitor) const override {
        visitor->visit(this);
    }

    int val;
};

class BoolExpression : public Expression {

public:
    
    BoolExpression(bool b, Position pos) : b_(b) { this->pos = pos; }

    virtual void accept(Visitor* visitor) const override {
        visitor->visit(this);
    }

    bool b_;
};

class IdExpression : public Expression {

public:
    
    IdExpression(const SymbolTable::Symbol* id, Position pos) : id_(id) { this->pos = pos; }

    virtual void accept(Visitor* visitor) const override {
        visitor->visit(this);
    }

    const SymbolTable::Symbol* id_;
};

class ThisExpression : public Expression {

public:

    virtual void accept(Visitor* visitor) const override {
        visitor->visit(this);
    }
};

class NewIntArrayExpression : public Expression {

public:
    
    NewIntArrayExpression(const Expression* subscript_expression, Position pos)
        : subscript_expression_(subscript_expression) { this->pos = pos; }

    virtual void accept(Visitor* visitor) const override {
        visitor->visit(this);
    }

    const Expression* subscript_expression_;
};

class NewObjectExpression : public Expression {

public:
    
    NewObjectExpression(SymbolTable::Symbol* type, Position pos) : new_object_type_(type) { 
        this->pos = pos; 
    }

    virtual void accept(Visitor* visitor) const override {
        visitor->visit(this);
    }

    SymbolTable::Symbol* new_object_type_;
};

class NegationExpression : public Expression {

public:
    
    NegationExpression(const Expression* expression, Position pos) : expression_to_negate_(expression) { this->pos = pos; }

    virtual void accept(Visitor* visitor) const override {
        visitor->visit(this);
    }

    const Expression* expression_to_negate_;
};

#endif