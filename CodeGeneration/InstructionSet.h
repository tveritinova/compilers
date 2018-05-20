#pragma once

#include "Instruction.h"
#include "../IR/Temp.h"

enum Regs {
    EAX,
    EBX,
    ECX,
    EDX
};

class CISCOperation: public IInstruction {
public:
    CISCOperation(std::string code, const std::vector<Temp> srcList,
                  const std::vector<Temp> dstList, const std::vector<Label> targetLabels)
    {
        src = srcList;
        dst = dstList;
        labelList = targetLabels;
        asmCode = code;
    }

    CISCOperation(std::string code, const std::vector<Temp>  srcList,
                  const std::vector<Temp> dstList)
    {
        src = srcList;
        dst = dstList;
        asmCode = code;
    }
};

class RegMove: public MoveInstruction {
public:
    RegMove(const std::string code, const Temp* from, const Temp* to);
    RegMove(const std::string code, const std::vector<Temp> from);
    RegMove(const std::string code, const ConstExp* from, const Temp* to);
};