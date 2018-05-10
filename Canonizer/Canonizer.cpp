#include "Canonizer.h"

#include "Temp.h"
#include <iostream>

void Canonizer::visit(const ExpList* e) {
	IExp* cur = e->cur;
	ExpList* others = e->others;

	cur->accept(this);
	others->accept(this);
}

void Canonizer::visit(const StmList* e) {
	IStm* cur = e->cur;
	StmList* others = e->others;

	cur->accept(this);
	others->accept(this);
}

void Canonizer::visit(const ConstExp* e) {
	int v = e->value;
}

void Canonizer::visit(const NameExp* e) {
	Label l = e->label_class;
}

void Canonizer::visit(const TempExp* e) {
	Temp t = e->temp;
}

void Canonizer::visit(const BinopExp* e) {
	IRTree_OP::OP_BIN op = e->binop;
	IExp* left = e->left;
	IExp* right = e->right;

	left->accept(this);
	right->accept(this);
}

void Canonizer::visit(const MemExp* e) {
	IExp* pointer = e->exp;
	int size = e->size; 
}


void Canonizer::visit(const CallExp* e) {
	IExp* func = e->func;
	ExpList* args = e->args;

	func->accept(this);
	args->accept(this);
}

void Canonizer::visit(const EseqExp* e) {
	IStm* stm = e->stm;
	IExp* exp = e->exp;

	stm->accept(this);
	exp->accept(this);
}

void Canonizer::visit(const MoveStm* e) {
	IExp* left = e->left;
	IExp* right = e->right;

	left->accept(this);
	right->accept(this);
}

void Canonizer::visit(const ExpStm* e) {
	IExp* exp = e->exp;

	exp->accept(this);
}

void Canonizer::visit(const JumpStm* e) {
	IExp* exp = e->exp;
	std::vector<Label> targets = e->targets; // not necassery

	exp->accept(this);
}

void Canonizer::visit(const CJumpStm* e) {
	IRTree_OP::OP_COMPARE op = e->relop;
	IExp* left = e->left;
	IExp* right = e->right;
	Label iftrue = e->iftrue;
	Label iffalse = e->iffalse;

	left->accept(this);
	right->accept(this);
}

void Canonizer::visit(const SeqStm* e) {
	IStm* left = e->left;
	IStm* right = e->right;

	left->accept(this);
	right->accept(this);
}




