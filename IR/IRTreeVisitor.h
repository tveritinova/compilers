#pragma once

#include "IRTree_classes.h"

struct IRTreeVisitor {
    virtual ~IRTreeVisitor() {};

    virtual void visit(ExpList*) = 0;
    virtual void visit(StmList*) = 0;
    virtual void visit(ConstExp*) = 0;
    virtual void visit(NameExp*) = 0;
    virtual void visit(TempExp*) = 0;
    virtual void visit(BinopExp*) = 0;
    virtual void visit(CallExp*) = 0;
    virtual void visit(EseqExp*) = 0;
    virtual void visit(MoveStm*) = 0;
    virtual void visit(JumpStm*) = 0;
    virtual void visit(CJumpStm*) = 0;
    virtual void visit(SeqStm*) = 0;
    virtual void visit(LabelStm*) = 0;
    virtual void visit(ExpStm*) = 0;
    virtual void visit(MemExp*) = 0;    
};
