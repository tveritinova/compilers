#pragma once

#include "../IR/IRTree_classes.h"

struct IRTreeVisitor {
    virtual ~IRTreeVisitor() {};

    virtual void visit(const ExpList*) = 0;
    virtual void visit(const StmList*) = 0;
    virtual void visit(const ConstExp*) = 0;
    virtual void visit(const NameExp*) = 0;
    virtual void visit(const TempExp*) = 0;
    virtual void visit(const BinopExp*) = 0;
    virtual void visit(const CallExp*) = 0;
    virtual void visit(const EseqExp*) = 0;
    virtual void visit(const MoveStm*) = 0;
    virtual void visit(const JumpStm*) = 0;
    virtual void visit(const CJumpStm*) = 0;
    virtual void visit(const SeqStm*) = 0;
    virtual void visit(const LabelStm*) = 0;
    virtual void visit(const ExpStm*) = 0;
    virtual void visit(const MemExp*) = 0;    
};
