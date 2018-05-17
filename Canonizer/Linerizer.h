#pragma once

#include "../IR/IRTree_classes.h"
#include "../IR/Converters.h"
#include "../IR/IRTreeVisitor.h"

class Linerizer: public IRTreeVisitor {
public:

    void Linerize(ISubtreeWrapper* wrapper, std::vector<IStm*> stms);

    void visit(ExpList*) override {}
    void visit(MemExp*) override {}
    void visit(ExpStm* node) override { addToStatements(node); }
    void visit(StmList*) override {}
    void visit(ConstExp*) override {}
    void visit(NameExp*) override {}
    void visit(TempExp*) override {}
    void visit(BinopExp*) override {}
    void visit(CallExp*) override {}
    void visit(StmWrapper*);
    void visit(ExpWrapper*);
    void visit(EseqExp*) override {}
    void visit(MoveStm* node) override { addToStatements(node); }
    void visit(JumpStm* node) override { addToStatements(node); }
    void visit(CJumpStm* node) override { addToStatements(node); }
    void visit(SeqStm*) override;
    void visit(LabelStm* node) override { addToStatements(node); }

    bool isPreviousDetached;
    std::vector<IStm*> statements;

    void addToStatements(IStm* stm);
};