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

IStm* Canonizer::addSeqIfRequired(IStm* stm) {

    if (lastEseq->stm == nullptr) {
        return stm;
    }
    return new Seq(tree, lastEseq->stm, stm);
}

void Canonizer::visit(const ExpList* e) {

    if (e->cur != nullptr) {
        IStm* stm = reorder(&(e->cur));
        if (stm != nullptr) {
            lastEseq->stm = addSeqIfRequired(stm);
        }
    }

    if (e->others != nullptr) {
        e->others->accept(this);
        e->others = lastEseq->exp;
    }

    lastEseq->exp = e;
}

/*void Canonizer::visit(const StmList* e) {

    const IStm* cur = e->cur;
    const StmList* others = e->others;

    cur->accept(this);
    others->accept(this);
}*/

void Canonizer::visit(const ConstExp* e) {
    lastEseq->exp = exp;
}

void Canonizer::visit(const NameExp* e) {
    lastEseq->exp = exp;
}

void Canonizer::visit(const TempExp* e) {
    lastEseq->exp = exp;
}

void Canonizer::visit(const BinopExp* e) {

    IStm* leftStatements = reorder(&(e->left));
    IStm* rightStatements = reorder(&(e->right));

    lastEseq->stm = new SeqStm(tree, leftStatements, rightStatements);
    lastEseq->exp = e;
}

void Canonizer::visit(const MemExp* e) {
    const IExp* pointer = e->exp;
    int size = e->size;

    e->exp->accept(this);
    e->exp = lastEseq->exp;
    lastEseq->exp = e;
}


void Canonizer::visit(const CallExp* e) {
    const IExp* func = e->func;
    ExpList* args = e->args;

    e->args->accept(this);
    e->args = new ExpList(lastEseq->exp, nullptr);
    lastEseq->stm = reorder(&(e->func));
    lastEseq->exp = e;
}

void Canonizer::visit(const EseqExp* e) {

    e->stm->accept(this);
    lastEseq->stm = reorder(&(e->exp));
    lastEseq->exp = e->exp;
}

void Canonizer::visit(const MoveStm* e) {
    const IExp* left = e->left;
    const IExp* right = e->right;


    IStm* src = reorder(&(e->left));
    IStm* dst = reorder(&(e->right));

    if (src != nullptr) {
        lastEseq->stm = addSeqIfRequired(src);
    }
    if (dst != nullptr) {
        lastEseq->stm = addSeqIfRequired(dst);
    }

    lastEseq->stm = addSeqIfRequired(e);
}

void Canonizer::visit(const ExpStm* e) {

    IStm* stm = reorder(&(e->exp));

    if (stm != nullptr) {
        lastEseq->stm = addSeqIfRequired(stm);
    }

    lastEseq->stm = addSeqIfRequired(e);
}

void Canonizer::visit(const JumpStm* e) {
    lastEseq->stm = addSeqIfRequired(e);
}

void Canonizer::visit(const CJumpStm* e) {

    IStm* leftStatements = = reorder(&(e->left));
    IStm* rightStatements = = reorder(&(e->right));

    if (leftStatements != nullptr) {
        lastEseq->stm = addSeqIfRequired(leftStatements);
    }

    if (rightStatements != nullptr) {
        lastEseq->stm = addSeqIfRequired(rightStatements);
    }

    lastEseq->stm = addSeqIfRequired(e);
}

void Canonizer::visit(const SeqStm* e) {
    const IStm* left = e->left;
    const IStm* right = e->right;

    left->accept(this);
    right->accept(this);
}