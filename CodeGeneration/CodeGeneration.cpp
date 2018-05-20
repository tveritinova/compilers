#include "Instruction.h"
#include "../IR/Converters.h"
#include "../IR/IRTree_classes.h"
#include "CodeGeneration.h"
#include "InstructionSet.h"

const InstructionList CodeGeneration::generate() {
    processStm(stm);
    return InstructionList(std::move(instructionsList));
}

void CodeGeneration::processStm(const IStm* s) {

    if (const MoveStm* move = dynamic_cast<const MoveStm*>(s)) {
        processMove(move->left, move->right);
    }
    else if (const JumpStm* jump = dynamic_cast<const JumpStm*>(s)) {
        processJump(jump->targets[0]);
    }
    else if (const CJumpStm* jumpc = dynamic_cast<const CJumpStm*>(s)) {
        processJumpC(jumpc->left, &(jumpc->right), jumpc->iftrue, jumpc->relop);
    }
    else if (const LabelStm* labelstm = dynamic_cast<const LabelStm*>(s)) {
        processLabelStm(labelstm->label_class);
    }
    else {
        assert(false);
    }
}

void CodeGeneration::processMove(const IExp* source, const IExp* destination) {
    if(const Mem* temp = dynamic_cast<const MemExp*>(source)) {
            processMove(temp, destination);
    } else if (const MemExp* temp = dynamic_cast<const MemExp*>(destination)) {
        processMove(source, temp);
    } else if(const TempExp* temp = dynamic_cast<const TempExp*>(destination)) {
        processMove(source, temp);
    } else {
        emit(new RegMove("MOV %0 %1", processExp(source), processExp(destination)));
    }
}

const Temp* CodeGeneration::processExp(const IExp* exp) {
    //MEM
    if(  const MemExp* mem = dynamic_cast<const MemExp*>(exp) ) {
        return processMem(mem);
    }
    //BINOP
    if( const BinopExp* binop = dynamic_cast<const BinopExp*>(exp) ) {
        return processBinop(binop);
    }
    //CONST
    if(const ConstExp* c = dynamic_cast<const ConstExp*>(exp)) {
        Temp* returnedReg = new Temp("Const");
        instructionsList.Registers.push_back(std::unique_ptr<const Temp>(returnedReg));
        emit(new RegMove("MOV %0 " + std::to_string(c->value), c, returnedReg));
        return returnedReg;
    }
    //TEMP
    if(const TempExp* c = dynamic_cast<const TempExp*>(exp)) {
        return &(c->temp);
    }
    //CALL
    if(const CallExp* call = dynamic_cast<const CallExp*>(exp)) {
        return processCall(call);
    }
    //NAME
    if(const NameExp* name = dynamic_cast<const Name*>(exp)) {
        const Temp* result = new Temp("Name");
        instructionsList.Registers.push_back(std::unique_ptr<const Temp>(result));
        const ConstExp* constPtr = nullptr;
        emit(new RegMove("MOV %0" + name->LabelName->GetName(), constPtr, result));
        return result;
    }
    assert(false);
}

const IInstruction* CodeGeneration::emit(const IInstruction* nextInstruction)
{
    instructionsList.Instructions.push_back( std::unique_ptr<const IInstruction>( nextInstruction ) );
    return nextInstruction;
}

void CodeGeneration::processMove(const MemExp* source, const IExp* destination) {
    // MOVE(MEM(BINOP(...))
    const BinopExp* binop = dynamic_cast<const BinopExp*>(source->exp);
    if (binop && (binop->op == IRTree_OP::OP_BIN::PLUS_) ) {
        // MOVE(MEM(BINOP(PLUS, e1, CONST(i))), e2)
        if(const ConstExp* c = dynamic_cast<const ConstExp*>(binop->right)) {
            emit(new RegMove("MOV %0 [%1+" + std::to_string(c->value) + "]",
                              processExp(binop->left), processExp(destination)));
        }
        // MOVE(MEM(BINOP(PLUS, CONST(i), e1)), e2)
        else if(const ConstExp* c = dynamic_cast<const ConstExp*>(binop->left)) {
            emit(new RegMove("MOV %0 [%1+" + std::to_string(c->value) + "]",
                              processExp(binop->right)), processExp(destination)));
        }
        // MOVE(MEM())
        else {
            emit(new RegMove("MOV %0 [%1]",
                              processExp(binop), processExp(destination)));
        }
    }
    // MOVE(MEM(e1), e2)
    else if(const Temp* temp = dynamic_cast<const Temp*>(source->exp) ) {
        emit(new RegMove("MOV %0 %1",
                          temp, processExp(destination)));
    } else {
        emit(new RegMove("MOV %0 [%1]",
                          processExp(source->exp), processExp(destination)));
    }
}

void CodeGeneration::processMove(const IExp* source, const MemExp* destination)
{
    // MOVE(MEM(BINOP(...))
    const BinopExp* binop = dynamic_cast<const BinopExp*>(destination->exp);
    if (binop && (binop->Operation == IRTree_OP::OP_BIN::PLUS_) ) {
        // MOVE(MEM(BINOP(PLUS, e1, CONST(i))), e2)
        if(const ConstExp* c = dynamic_cast<const ConstExp*>(binop->right)) {
            emit(new RegMove("MOV [%0 + " + std::to_string(c->value) + "] %1",
                                  std::move(TempList({processExp(source), processExp(binop->left)}))));
        }
        // MOVE(MEM(BINOP(PLUS, CONST(i), e1)), e2)
        else if(const ConstExp* c = dynamic_cast<const ConstExp*>(binop->left)) {
            emit(new RegMove("MOV [%0 + " + std::to_string(c->value) + "] %1",
                              std::move(TempList({processExp(source), processExp(binop->right)}))));
        }
        // MOVE(MEM())
        else {
            emit(new RegMove("MOV [%0] %1",
                              std::move(TempList({processExp(source), processExp(binop)}))));
        }
    }
    // MOVE(MEM(e1), e2)
    else  {
        emit(new RegMove("MOV [%0] %1",
                          std::move(TempList({processExp(source), processExp(destination->exp)}))));
    }
}

void CodeGeneration::processMove(const IExp* source, const Temp* destination) {
    // MOVE(TEMP(t1), e)
    emit(new RegMove("MOV %0 %1", processExp(source), destination));
}

TempList CodeGeneration::processExpList(const ExpList* list)
{
    const IExp* head = list->cur;
    const IExp* tail = list->others;
    TempList temps;
    if(const ExpList* subList = dynamic_cast<const ExpList*>(head)) {
        TempList subTemps = processExpList(subList);
        temps.insert(temps.end(), subTemps.begin(), subTemps.end());
    } else {
        temps.push_back(processExp(head));
    }
    if(const ExpList* subList = dynamic_cast<const ExpList*>(tail)) {
        TempList subTemps = processExpList(subList);
        temps.insert(temps.end(), subTemps.begin(), subTemps.end());
    } else if( tail != nullptr ){
        temps.push_back(processExp(tail));
    }
    return temps;
}

const Temp* CodeGeneration::processMem(const MemExp* mem)
{
    //MEM(BINOP)
    const BinopExp* binop = dynamic_cast<const BinopExp*>(mem->exp);
    if( binop && binop->Operation == IRTree_OP::OP_BIN::PLUS_)
    {
        //MEM(BINOP(PLUS, e1, CONST(i)))
        if(const ConstExp* c = dynamic_cast<const ConstExp*>(binop->right))
        {
            const Temp* left = processExp(binop->left);
            Temp* returnedReg = new Temp("MEM(BINOP(PLUS, e1, CONST(i)))");
            instructionsList.Registers.push_back(std::unique_ptr<const Temp>(returnedReg));
            emit(new RegMove("MOV %0 [%1 + " + std::to_string(c->value) + "]",
                                               left, returnedReg));
            return returnedReg;
        }
        //MEM(BINOP(PLUS, CONST(i), e1))
        else if(const ConstExp* c = dynamic_cast<const ConstExp*>(binop->left))
        {
            const Temp* right = processExp(binop->right);
            Temp* returnedReg = new Temp("MEM(BINOP(PLUS, CONST(i), e1))");
            instructionsList.Registers.push_back(std::unique_ptr<const Temp>(returnedReg));
            emit(new RegMove("MOV %0 [%1 + " + std::to_string(c->value) + "]",
                                               right, returnedReg));
            return returnedReg;
        }
        //MEM(e1)
        else {
            Temp* returnedReg = new Temp("MEM(e1)");
            instructionsList.Registers.push_back(std::unique_ptr<const Temp>(returnedReg));
            emit(new RegMove("MOV %0 [%1]", processExp(binop), returnedReg));
            return returnedReg;
        }
    }

    //MEM(CONST(i))
    else if (const ConstExp* c = dynamic_cast<ConstExp*>(mem->exp)) {
        Temp* returnedReg = new Temp("MEM(Const(i))");
        instructionsList.Registers.push_back(std::unique_ptr<const Temp>(returnedReg));
        emit(new RegMove("MOV %0 [" + std::to_string(c->value) + "]",
                                           c, returnedReg));
        return returnedReg;
    }
    //MEM(e1)
    else {
        const Temp* e1 = processExp(mem->exp);
        Temp* returnedReg = new Temp("MEM(e1)");
        instructionsList.Registers.push_back(std::unique_ptr<const Temp>(returnedReg));
        emit(new RegMove("MOV %0 [%1]", e1, returnedReg));
        return returnedReg;
    }

}

const Temp*CodeGeneration::processCall(const Call* call)
{
    const Temp* eax = new Temp("EAX", Coords(), EAX);
    instructionsList.Registers.push_back(std::unique_ptr<const Temp>(eax));
    TempList listArgs(processExpList(call->args));
    if(const MemExp* mem = dynamic_cast<const MemExp*>(call->func)) {
        const Temp* funcAddress = dynamic_cast<const Temp*>(mem->exp);
        assert(funcAddress);
        listArgs.push_back(funcAddress);
        emit(new CISCOperation("CALL [%" + std::to_string(listArgs.size() - 1) +"]", std::move(listArgs),
                                    std::move(TempList())));
        return eax;
    }
    if(const Name* name = dynamic_cast<const Name*>(call->FuncExpression.get())) {
        emit(new CISCOperation("CALL " + name->LabelName->GetName(), std::move(listArgs),
                                    std::move(TempList())));
        return eax;
    }
    assert(false);
}

const Temp* CodeGeneration::processBinop(const BinopExp* binop)
{
    switch (binop->Operation) {
    case IRTree_OP::OP_BIN::PLUS_:
        return processBinopRegular(binop, "ADD ");
    case IRTree_OP::OP_BIN::MINUS:
        return processBinopRegular(binop, "SUB ");
    case IRTree_OP::OP_BIN::OR:
        return processBinopRegular(binop, "OR ");
    case IRTree_OP::OP_BIN::AND:
        return processBinopRegular(binop, "AND ");
    case IRTree_OP::OP_BIN::MOD:
        return processBinopDiv(binop);
    case IRTree_OP::OP_BIN::MUL:
        return processBinopMul(binop);
    default:
        assert(false);
        break;
    }
}

const Temp* CodeGeneration::processBinopRegular(const BinopExp* binop, const std::string& prefix)
{
    Temp* returnReg = new Temp("BINOP(Regular)");
    instructionsList.Registers.push_back(std::unique_ptr<const Temp>(returnReg));
    //BINOP(_, e1, Const)
    if( const ConstExp* left = dynamic_cast<const ConstExp*>(binop->left) ) {
        emit(new RegMove("MOV %0 %1", processExp(binop->right), returnReg));
        emit(new CISCOperation(prefix + "%0 " + std::to_string(left->value),
                                    std::move(TempList({returnReg})), std::move(TempList({returnReg}))));
        return returnReg;
    }
    //BINOP(_, Const, e1)
    else if(const ConstExp* right = dynamic_cast<const ConstExp*>(binop->right)) {
        emit(new RegMove("MOV %0 %1", processExp(binop->left), returnReg));
        emit(new CISCOperation(prefix + "%0 " + std::to_string(right->value),
                                    std::move(TempList({returnReg})), std::move(TempList({returnReg}))));
        return returnReg;
    }
    //BINOP(_, e1, e2)
    else {
        emit(new RegMove("MOV %0 %1", processExp(binop->left), returnReg));
        emit(new CISCOperation(prefix + "%0 %1",
                                    std::move(TempList({processExp(binop->right)})),
                                    std::move(TempList({returnReg}))));
        return returnReg;
    }
}

const Temp*CodeGeneration::processBinopMul(const BinopExp* binop)
{
    Temp* returnReg = new Temp("BINOP(Regular)");
    instructionsList.Registers.push_back(std::unique_ptr<const Temp>(returnReg));
    //BINOP(MUL, e1, Const)
    if( const ConstExp* left = dynamic_cast<const ConstExp*>(binop->left) ) {
        emit(new CISCOperation("IMUL %0 %1 " + std::to_string(left->value),
                                    std::move(TempList({processExp(binop->right)})),
                                    std::move(TempList({returnReg}))));
        return returnReg;
    }
    //BINOP(MUL, Const, e1)
    else if(const ConstExp* right = dynamic_cast<const ConstExp*>(binop->right)) {
        emit(new CISCOperation("IMUL %0 %1 " + std::to_string(right->value),
                                    std::move(TempList({processExp(binop->left)})),
                                    std::move(TempList({returnReg}))));
        return returnReg;
    }
    //BINOP(MUL, e1, e2)
    else {
        emit(new RegMove("MOV %0 %1", processExp(binop->left), returnReg));
        emit(new CISCOperation("IMUL %0 %1",
                                    std::move(TempList({processExp(binop->right)})),
                                    std::move(TempList({returnReg}))));
        return returnReg;
    }
}

const Temp* CodeGeneration::processBinopDiv(const BinopExp* binop)
{
    const Temp* eax = new Temp("EAX", Coords(), EAX);
    instructionsList.Registers.push_back(std::unique_ptr<const Temp>(eax));
    const Temp* edx = new Temp("EDX", Coords(), EDX);
    instructionsList.Registers.push_back(std::unique_ptr<const Temp>(edx));
    emit(new RegMove("MOV %0 %1", processExp(binop->left), eax));
    emit(new CISCOperation("IDIV %1",
                                std::move(TempList({processExp(binop->right), eax})),
                                std::move(TempList({edx}))));
    Temp* returnReg = new Temp("BINOP(Regular)");
    instructionsList.Registers.push_back(std::unique_ptr<const Temp>(returnReg));
    emit(new RegMove("MOV %0 %1", edx, returnReg));
    return returnReg;
}


void CodeGeneration::processJump(const Label* LabelToJump) {
    emit(new CISCOperation("JMP %l", std::move(TempList()),
                                std::move(TempList()), std::move(LabelList({LabelToJump}))));
}

void CodeGeneration::processJumpC(const IExp* conditionLeftExpression, const IExp* conditionRightExpression,
                         const Label* trueLabel,
                         JumpC::TJumpType jumpType)
{
    if(const ConstExp* c = dynamic_cast<const ConstExp*>(conditionLeftExpression)) {
        const Temp* e = processExp(conditionRightExpression);
        emit(new CISCOperation("CMP %0 " + std::to_string(c->value), std::move(TempList({e})), std::move(TempList())));
    }
    else if(const ConstExp* c = dynamic_cast<const ConstExp*>(conditionRightExpression)) {
        const Temp* e = processExp(conditionLeftExpression);
        emit(new CISCOperation("CMP %0 " + std::to_string(c->value), std::move(TempList({e})), std::move(TempList())));
    }
    else {
        const Temp* e1 = processExp(conditionLeftExpression);
        const Temp* e2 = processExp(conditionRightExpression);
        emit(new CISCOperation("CMP %0 %1", std::move(TempList({e1, e2})), std::move(TempList())));
    }
    switch (jumpType) {
    case JumpC::TJ_EQ:
        emit(new CISCOperation("JE %l", std::move(TempList()), std::move(TempList()), std::move(LabelList({trueLabel}))));
        break;
    case JumpC::TJ_LT:
        emit(new CISCOperation("JL %l", std::move(TempList()), std::move(TempList()), std::move(LabelList({trueLabel}))));
        break;
    case JumpC::TJ_NEQ:
        emit(new CISCOperation("JNE %l", std::move(TempList()), std::move(TempList()), std::move(LabelList({trueLabel}))));
        break;
    default:
        break;
    }
}

void CodeGeneration::processLabelStm(const Label* labelName) {
    emit(new LabelInstruction(labelName));
}
