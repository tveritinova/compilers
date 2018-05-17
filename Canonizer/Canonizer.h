#pragma once

#include "../IR/IRTree_classes.h"
#include "../IR/IRTreeVisitor.h"

class Canonizer: public IRTreeVisitor {
public:

	IStm* body;

	Canonizer(IStm* stm): body(stm) {};

	void run() { body->accept(this); }

	IStm* reorder(IExp** exp);
	void decomposeEseq();
	IStm* addSeqIfRequired(IStm* stm);

	void visit(ExpList*) override;
	void visit(MemExp*) override;
	void visit(ExpStm*) override;
	void visit(StmList*) override {};
	void visit(ConstExp*) override;
	void visit(NameExp*) override;
	void visit(TempExp*) override;
	void visit(BinopExp*) override;
	void visit(CallExp*) override;
	void visit(EseqExp*) override;
	void visit(MoveStm*) override;
	void visit(JumpStm*) override;
	void visit(CJumpStm*) override;
	void visit(SeqStm*) override;
	void visit(LabelStm*) override {};

	EseqExp* lastEseq;

	IRTree tree;
};