#include "decoder.h"
#include "environment.h"
#include "branch_ops.h"
#include "call_ops.h"


void BranchOps::CPSE(Environ &env, uint32_t instrn) {
    FiveBit regAddr1, regAddr2;
    ArgsDecode::TwoReg5(instrn, regAddr1, regAddr2);
    CPSE(env, regAddr1, regAddr2);
}

void BranchOps::CPSE(Environ &env, FiveBit &reg1Addr, FiveBit &reg2Addr) {
    uchar_t value1 = env.read_reg_byte(reg1Addr);
    uchar_t value2 = env.read_reg_byte(reg2Addr);
    if (value1 == value2)
        ;
}

