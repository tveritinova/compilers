#include "Instruction.h"
#include "../IR/Converters.h"
#include "../IR/IRTree_classes.h"
#include "InstructionSet.h"

class CodeGeneration {
public:
    CodeGeneration(IStm* tree): stm(tree) {}
    const InstructionList generate();

private:
    const IStm* stm;
    InstructionList instructionsList;

    void processStm(const IStm* s);
    const Temp* processExp(const IExp* exp);
    
    void processMove(const IExp* source, const IExp* destination);
    void processMove(const MemExp* source, const IExp* destination);
    void processMove(const IExp* source, const MemExp* destination);
    void processMove(const IExp* source, const TempExp* destination);

    std::vector<Temp> processExpList(const ExpList* list);
    const Temp* processMem(const MemExp* mem);
    const Temp* processCall(const CallExp* call);
    const Temp* processBinop(const BinopExp* binop);
    const Temp* processBinopRegular(const BinopExp* binop, const std::string& prefix);
    const Temp* processBinopMul(const BinopExp* binop);
    const Temp* processBinopDiv(const BinopExp* binop);
    void processJump(const Label* LabelToJump);
    void processJumpC(const IExp* conditionLeftExpression, const IExp* conditionRightExpression, const Label* trueLabel, IRTree_OP::OP_COMPARE jumpType);
    void processLabelStm(const Label* LabelName);

    const IInstruction* emit(const IInstruction* nextInstruction);

};
