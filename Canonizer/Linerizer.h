#pragma once

#include "../IR/IRTree_classes.h"
#include "IRTreeVisitor.h"

class Linerizer: public IRTreeVisitor {
public:

    void Linerize(ISubtreeWrapper* wrapper, std::vector<IStm*> stms);

    void visit(const ExpList*) override {}
    void visit(const MemExp*) override {}
    void visit(const ExpStm*) override { addToStatements(node); }
    void visit(const StmList*) override {}
    void visit(const ConstExp*) override {}
    void visit(const NameExp*) override {}
    void visit(const TempExp*) override {}
    void visit(const BinopExp*) override {}
    void visit(const CallExp*) override {}
    void visit(const EseqExp*) override {}
    void visit(const MoveStm*) override { addToStatements(node); }
    void visit(const JumpStm*) override { addToStatements(node); }
    void visit(const CJumpStm*) override { addToStatements(node); }
    void visit(const SeqStm*) override;
    void visit(const LabelStm*) override { addToStatements(node); }

    bool isPreviousDetached;
    std::vector<IStm*> statements;

    void addToStatements(IStm* stm);
};