#include "Linerizer.h"

#include <../IR/Converters.h>
#include <../IR/IRTree_classes.h>

void Linerizer::Linerize(ISubtreeWrapper* wrapper, std::vector<IStm*> stms) {
    isPreviousDetached = false;
    statements = stms;
    wrapper->accept(this);
}

void Linerizer::Visit(Seq* node) {
    if (node->cur != nullptr) {
        node->others->accept(this);

        if (isPreviousDetached) {
            isPreviousDetached = false;
        }
    }
    if (node->cur != nullptr) {
        node->cur->accept(this);

        if (isPreviousDetached) {
            isPreviousDetached = false;
        }
    }
}

void Linerizer::Visit(StmWrapper* node) {
    IStm* stm = node->to_stm();
    stm->accept(this);
}

void Linerizer::Visit(ExpWrapper* node) {
    IStm* stm = node->to_stm();
    stm->accept(this);
}

void Linerizer::addToStatements(IStm* stm) {
    statements->push_back(stm);
    isPreviousDetached = true;
}