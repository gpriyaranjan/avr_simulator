#include "decoder.h"
#include "environment.h"
#include "branch_ops.h"
#include "call_ops.h"


bool BranchOps::CPSE(Environ &env, uint32_t instrn, bool nextInstrnLong) {
    FiveBit regAddr1, regAddr2;
    ArgsDecode::TwoReg5(instrn, regAddr1, regAddr2);
    return CPSE(env, regAddr1, regAddr2, nextInstrnLong);
}

bool BranchOps::CPSE(Environ &env, FiveBit &reg1Addr, FiveBit &reg2Addr, bool nextInstrnLong) {
    uchar_t value1 = env.read_reg_byte(reg1Addr);
    uchar_t value2 = env.read_reg_byte(reg2Addr);
    long skip = 0;
    if (value1 == value2)
        skip = 4 + (char)nextInstrnLong*4;
    env.PC = env.PC + 4 + skip;
    return true;
}


