#pragma once 

#include "../IR/IRTree_classes.h"
#include <vector.h>

class IInstruction {
public:
    virtual ~IInstruction() {}

    const std::string AsmCode() const { return asmCode; }

    const std::vector<Temp> UsedVars() const { return src; }
    const std::vector<Temp> DefinedVars() const { return dst; }
    const std::vector<Label> JumpTargets() const { return labelList; }

    virtual std::string Format() const {
        std::string s = asmCode;
        std::string instructionString;
        unsigned int pos;
        while ((pos = s.find("%")) < s.size()) {
            instructionString += s.substr(0, pos);
            if(s[pos+1] == 'l') {
                instructionString += labelList.at(0)->GetName();
            } else if(s[pos+1] - '0' < dst.size()) {
                assert(dst.size() > 0);
                instructionString += "r" + dst[0]->Name() + std::to_string(dst[0]->Id);
            } else {
                unsigned int srcPos = s[pos+1] - '0' - dst.size();
                assert(src.size() > srcPos);
                instructionString += "r" + src[srcPos]->Name() + std::to_string(src[srcPos]->Id);
            }
            s.erase(0, pos + 2);
        }
        instructionString += s;
        instructionString += "\tUsed:";
        for(auto& tmp: src) {
            instructionString += " r" + tmp->Name() + std::to_string(tmp->Id) + ";";
        }
        instructionString += "\tDefined:";
        for(auto& tmp: dst) {
            instructionString += " r" + tmp->Name() + std::to_string(tmp->Id) + ";";
        }
        return instructionString;
    }

protected:
    std::vector<Temp> src;
    std::vector<Temp> dst;
    std::vector<Label> labelList;
    std::string asmCode;
};

class MoveInstruction : public IInstruction {
public:
    MoveInstruction(const Temp* from, const Temp* to): fromConst(0) {
        src.push_back(from);
        dst.push_back(to);
    }
    MoveInstruction(const std::vector<TempList>&& from) {
        src = from;
    }
    MoveInstruction(const Const* from, const Temp* to): fromConst(from) { dst.push_back(to); }

private:
    const Const* fromConst;
};

class LabelInstruction: public IInstruction {
public:
    LabelInstruction( const Label* l ) { labelList.push_back(l); }
    virtual std::string Format() const override {
        return labelList[0]->GetName() + ":";
    }
};

struct InstructionList {
    std::vector<std::unique_ptr<const IInstruction>> Instructions;
    std::vector<std::unique_ptr<const Temp>> Registers;
};