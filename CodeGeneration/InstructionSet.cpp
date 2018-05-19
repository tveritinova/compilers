#include "InstructionSet.h"

RegMove::RegMove(const std::string code, const Temp* from, const Temp* to):
    MoveInstruction(from, to)
{
    asmCode = code;
}

RegMove::RegMove(const std::string code, const TempList&& from):
    MoveInstruction(std::move(from))
{
    asmCode = code;
}

RegMove::RegMove(const std::string code, const Const* from, const Temp* to):
    MoveInstruction(from, to)
{
    asmCode = code;
}
