#include "decoder.h"
#include "branch_ops.h"

void BranchOps::RJMP(Environ &env, uint32_t instrn) {
    TwelveBit offset;
    ArgsDecode::Addr12(instrn, offset);
    RJMP(env, offset, true);
}

void BranchOps::RJMP(Environ &env, TwelveBit tgtOffset, bool dummy) {
    uint16_t offset1 = tgtOffset - (1 << 11);
    env.PC = env.PC + offset1;
}

void BranchOps::JMP(Environ &env, uint64_t instrn) {
    TwentyTwoBit jmpAddr;
    ArgsDecode::Addr22(instrn, jmpAddr);
    JMP(env, jmpAddr, false);
}

void BranchOps::JMP(Environ &env, TwentyTwoBit jmpAddr, bool dummy) {
    env.PC = jmpAddr;
}

void BranchOps::IJMP(Environ &env) {

}

void BranchOps::IJMP(Environ &env, bool dummy) {

}









