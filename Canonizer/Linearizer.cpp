#include "Linearizer.h"

void Linearizer::Linearize(ISubtreeWrapper* wrapper, std::vector<IStm*> stms) {
    isPreviousDetached = false;
    statements = stms;

    //wrapper->accept(this);
}

void Linearizer::visit(SeqStm* node) {
    if (node->left != nullptr) {
        node->right->accept(this);

        if (isPreviousDetached) {
            isPreviousDetached = false;
        }
    }
    if (node->left != nullptr) {
        node->left->accept(this);

        if (isPreviousDetached) {
            isPreviousDetached = false;
        }
    }
}

void Linearizer::visit(StmWrapper* node) {
    IStm* stm = node->to_stmt();
    stm->accept(this);
}

void Linearizer::visit(ExpWrapper* node) {
    IStm* stm = node->to_stmt();
    stm->accept(this);
}

void Linearizer::addToStatements(IStm* stm) {
    statements.push_back(stm);
    isPreviousDetached = true;
}