#include "Linerizer.h"

void Linerizer::Linerize(ISubtreeWrapper* wrapper, std::vector<IStm*> stms) {
    isPreviousDetached = false;
    statements = stms;

    // wrapper->accept(this);
}

void Linerizer::visit(SeqStm* node) {
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

void Linerizer::visit(StmWrapper* node) {
    IStm* stm = node->to_stmt();
    stm->accept(this);
}

void Linerizer::visit(ExpWrapper* node) {
    IStm* stm = node->to_stmt();
    stm->accept(this);
}

void Linerizer::addToStatements(IStm* stm) {
    statements.push_back(stm);
    isPreviousDetached = true;
}