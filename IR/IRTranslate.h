
#ifndef H_TRANSLATE
#define H_TRANSLATE

#include <string>
#include <vector>

static int WORD_SIZE = 4;
static int MAX_IN_REG = 4;

static int intSize = 1 * WORD_SIZE;
static int booleanSize = 1 * WORD_SIZE;
static int referenceSize = 1 * WORD_SIZE;

#include "../AST/grammar.h"
#include "../AST/statement.h"
#include "../AST/expression.h"
#include "../AST/visitor.h"
#include "CCodeFragment.h"
#include "Converters.h"
#include "../SymbolTable/Table.h"
#include "../ActivationRecords/X86MiniJavaFrame.h"
#include "binary_operations/AndExpWrapper.h"
#include "binary_operations/OrExpWrapper.h"
#include "binary_operations/EqualExpWrapper.h"
#include "binary_operations/GreaterExpWrapper.h"
#include "binary_operations/LessExpWrapper.h"



class IRTranslate : public Visitor {
public:

	IRTranslate(Table* _table): table(_table), irtree() {}

	CCodeFragment* programTranslation;

	void visit(const SymbolTable::Symbol*) {}
	void visit(const ArgumentList*) {}

	void visit(const Program*);
	void visit(const MainClass*);
	void visit(const ClassDecl*);
	void visit(const ClassDeclList*);
	void visit(const VarDecl*) {}
	void visit(const VarDeclList*) {}
	void visit(const MethodDecl*);
	void visit(const MethodDeclList*);

	void visit(const StatementList*);
	void visit(const IfStatement*);
	void visit(const WhileStatement*);
	void visit(const PrintStatement*);
	void visit(const AssignStatement*);
	void visit(const AssignSubscriptStatement*);

	void visit(const ExpressionList*);
	void visit(const BinaryExpression*);
	void visit(const SubscriptExpression*);
	void visit(const LengthExpression*);
	void visit(const MethodCallExpression*);
	void visit(const IntExpression*);
	void visit(const BoolExpression*);
	void visit(const IdExpression*);
	void visit(const ThisExpression*);
	void visit(const NewIntArrayExpression*);
	void visit(const NewObjectExpression*);
	void visit(const NegationExpression*);


	IRTree irtree;

public:

	ISubtreeWrapper* lastWrapper = nullptr;
	std::vector<IStm*> lastStmtListBody;
	ExpList* lastExpListBody = nullptr;
	CCodeFragment* lastTranslation = nullptr;
	CCodeFragment* resultTranslation = nullptr;

	const Table* table;
	const SymbolTable::Symbol* currentClassName;
	const SymbolTable::Symbol* currentMethodName;

	std::vector<const AR::IFrame*> classFrames;

	const AR::IFrame* currentFrame;

	AR::IFrame* get_frame_for_method(const SymbolTable::Symbol*);
	IExp* get_class_var_exp(const SymbolTable::Symbol* varName);
};

#endif





