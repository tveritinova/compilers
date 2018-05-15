#include "Canonizer.h"

#include "../IR/Temp.h"
#include <iostream>


// поднимает вверх eseq
const IStm* Canonizer::reorder(IExp** exp) {
    (*exp)->accept(this);
    decomposeEseq();
    *exp = lastEseq->exp;
    return lastEseq->stm;
}

void Canonizer::decomposeEseq() {
    if (lastEseq->stm == nullptr || lastEseq->exp == nullptr) {
        return;
    }

    if (lastEseq->exp->IsCommutative()) {
        return;
    }

    lastEseq->stm = new SeqStm(tree, lastEseq->stm,
                                      new MoveStm(tree,
                                      	new TempExp(tree, Temp("TempHolderLocalId")),
                                      	lastEseq->exp));

    lastEseq->exp = new MemExp(tree, new TempExp(tree, Temp("TempHolderLocalId")), 4);
}

void Canonizer::visit(const ExpList* e) {
	const IExp* cur = e->cur;
	const ExpList* others = e->others;

	cur->accept(this);
	others->accept(this);
}

void Canonizer::visit(const StmList* e) {
	const IStm* cur = e->cur;
	const StmList* others = e->others;

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
	//Temp t = e->temp;
}

void Canonizer::visit(const BinopExp* e) {
	IRTree_OP::OP_BIN op = e->binop;
	const IExp* left = e->left;
	const IExp* right = e->right;

	IStm* leftStatements = reorder(left);
	IStm* rightStatements = reorder(right);

	// check left change

	e->left = left;
	e->right = right;

   	lastEseq->stm = new SeqStm(tree, leftStatements, rightStatements);
    lastEseq->exp = node;
}

void Canonizer::visit(const MemExp* e) {
	const IExp* pointer = e->exp;
	int size = e->size; 
}


void Canonizer::visit(const CallExp* e) {
	const IExp* func = e->func;
	ExpList* args = e->args;

	func->accept(this);
	args->accept(this);
}

void Canonizer::visit(const EseqExp* e) {
	const IStm* stm = e->stm;
	const IExp* exp = e->exp;

	stm->accept(this);
	exp->accept(this);
}

void Canonizer::visit(const MoveStm* e) {
	const IExp* left = e->left;
	const IExp* right = e->right;

	left->accept(this);
	right->accept(this);
}

void Canonizer::visit(const ExpStm* e) {
	const IExp* exp = e->exp;

	exp->accept(this);
}

void Canonizer::visit(const JumpStm* e) {
	const IExp* exp = e->exp;
	std::vector<Label> targets = e->targets; // not necassery

	exp->accept(this);
}

void Canonizer::visit(const CJumpStm* e) {
	IRTree_OP::OP_COMPARE op = e->relop;
	const IExp* left = e->left;
	const IExp* right = e->right;
	Label iftrue = e->iftrue;
	Label iffalse = e->iffalse;

	left->accept(this);
	right->accept(this);
}

void Canonizer::visit(const SeqStm* e) {
	const IStm* left = e->left;
	const IStm* right = e->right;

	left->accept(this);
	right->accept(this);
}




