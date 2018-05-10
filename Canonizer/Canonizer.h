#pragma once

#include "../IR/IRTree_classes.h"
#include "IRTreeVisitor.h"

class Canonizer: public IRTreeVisitor {
public:

	const IStm* body;

	Canonizer(const IStm* stm): body(stm) {};

	void visit(const ExpList*) override;
	void visit(const StmList*) override;
	void visit(const ConstExp*) override;
	void visit(const NameExp*) override;
	void visit(const TempExp*) override;
	void visit(const BinopExp*) override;
	void visit(const CallExp*) override;
	void visit(const EseqExp*) override;
	void visit(const MoveStm*) override;
	void visit(const JumpStm*) override;
	void visit(const CJumpStm*) override;
	void visit(const SeqStm*) override;
	void visit(const LabelStm*) override {}
};