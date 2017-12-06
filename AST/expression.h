
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
    ADD_, SUB_, MUL_, DIV_, MOD_, AND_, OR_, LESS_
};

class BinaryExpression : public Expression {

public:
    
    BinaryExpression(const Expression* lhs_expression, BinaryOperator binary_operator,
        const Expression* rhs_expression)
        : lhs_expression_(lhs_expression), 
        binary_operator_(binary_operator), 
        rhs_expression_(rhs_expression) {}

    virtual void accept(Visitor* visitor) const override {
        visitor->visit(this);
    }

    const Expression* lhs_expression_;
    BinaryOperator binary_operator_;
    const Expression* rhs_expression_;
};

class SubscriptExpression : public Expression {

public:
    
    SubscriptExpression(const Expression* expression, const Expression* subscript)
        : expression_(expression), subscript_(subscript) {}

    virtual void accept(Visitor* visitor) const override {
        visitor->visit(this);
    }

    const Expression* expression_;
    const Expression* subscript_;
};

class LengthExpression : public Expression {

public:
    
    LengthExpression(const Expression* expression) : expression_(expression) {}

    virtual void accept(Visitor* visitor) const override {
        visitor->visit(this);
    }

    const Expression* expression_;
};

class MethodCallExpression : public Expression {

public:

    MethodCallExpression(const Expression* expression, const Symbol* method_id,
        const ExpressionList* other_expressions)
        : expression_(expression), 
        method_id_(method_id), 
        other_expressions_(other_expressions) {}

    virtual void accept(Visitor* visitor) const override {
        visitor->visit(this);
    }

    const Expression* expression_;
    const Symbol* method_id_;
    const ExpressionList* other_expressions_;
};

class IntExpression : public Expression {

public:
    
    IntExpression(int val_) : val(val_) {}

    virtual void accept(Visitor* visitor) const override {
        visitor->visit(this);
    }

    int val;
};

class BoolExpression : public Expression {

public:
    
    BoolExpression(bool b) : b_(b) {}

    virtual void accept(Visitor* visitor) const override {
        visitor->visit(this);
    }

    bool b_;
};

class IdExpression : public Expression {

public:
    
    IdExpression(const Symbol* id) : id_(id) {}

    virtual void accept(Visitor* visitor) const override {
        visitor->visit(this);
    }

    const Symbol* id_;
};

class ThisExpression : public Expression {

public:

    virtual void accept(Visitor* visitor) const override {
        visitor->visit(this);
    }
};

class NewIntArrayExpression : public Expression {

public:
    
    NewIntArrayExpression(const Expression* subscript_expression)
        : subscript_expression_(subscript_expression) {}

    virtual void accept(Visitor* visitor) const override {
        visitor->visit(this);
    }

    const Expression* subscript_expression_;
};

class NewObjectExpression : public Expression {

public:
    
    NewObjectExpression(Symbol* type) : new_object_type_(type) {}

    virtual void accept(Visitor* visitor) const override {
        visitor->visit(this);
    }

    Symbol* new_object_type_;
};

class NegationExpression : public Expression {

public:
    
    NegationExpression(const Expression* expression) : expression_to_negate_(expression) {}

    virtual void accept(Visitor* visitor) const override {
        visitor->visit(this);
    }

    const Expression* expression_to_negate_;
};

class UnaryMinusExpression : public Expression {

public:
    
    UnaryMinusExpression(const Expression* expression) : expression_(expression) {}

    virtual void accept(Visitor* visitor) const override {
        visitor->visit(this);
    }

    const Expression* expression_;
};