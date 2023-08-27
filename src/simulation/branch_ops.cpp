#include "types.h"
#include "decoder.h"
#include "environment.h"
#include "branch_ops.h"
#include "call_ops.h"

bool BranchOps::CPSE(Environ &env, uint32_t instrn, InstrnEnum nextInstrn) {
    FiveBit regAddr1, regAddr2;
    ArgsDecode::TwoReg5(instrn, regAddr1, regAddr2);
    return CPSE(env, regAddr1, regAddr2, nextInstrn);
}

bool BranchOps::CPSE(Environ &env, FiveBit reg1Addr, FiveBit reg2Addr, InstrnEnum nextInstrn) {
    uchar_t value1 = env.read_reg_byte(reg1Addr);
    uchar_t value2 = env.read_reg_byte(reg2Addr);
    bool toSkip = value1 == value2;
    return SkipNextInstrn(env, toSkip, nextInstrn);
}

bool BranchOps::SBRC(Environ &env, uint32_t instrn, InstrnEnum nextInstrn) {
    FiveBit regAddr; ThreeBit bitNum;
    ArgsDecode::Reg5SBit3(instrn, regAddr, bitNum);
    return SBRC(env, regAddr, bitNum, nextInstrn);
}

bool BranchOps::SBRC(Environ &env, FiveBit regAddr, ThreeBit bitNum, InstrnEnum nextInstrn) {
    uchar_t regVal = env.read_reg_byte(regAddr);
    auto toSkip = (bool) (is_nbi(regVal,bitNum));
    return SkipNextInstrn(env, toSkip, nextInstrn);
}

bool BranchOps::SBRS(Environ &env, uint32_t instrn, InstrnEnum nextInstrn) {
    FiveBit regAddr; ThreeBit bitNum;
    ArgsDecode::Reg5SBit3(instrn, regAddr, bitNum);
    return SBRS(env, regAddr, bitNum, nextInstrn);
}

bool BranchOps::SBRS(Environ &env, FiveBit regAddr, ThreeBit bitNum, InstrnEnum nextInstrn) {
    uchar_t regVal = env.read_reg_byte(regAddr);
    auto toSkip = (bool) (is_bi(regVal,bitNum));
    return SkipNextInstrn(env, toSkip, nextInstrn);
}

bool BranchOps::SBIC(Environ &env, uint32_t instrn, InstrnEnum nextInstrn) {
    FiveBit portNum; ThreeBit bitNum;
    ArgsDecode::IO5Bit3(instrn, portNum, bitNum);
    FiveBit portAddr = portNum + 0x20;
    return SBRC(env, portAddr, bitNum, nextInstrn);
}

bool BranchOps::SBIC(Environ &env, FiveBit portAddr, ThreeBit bitNum, InstrnEnum nextInstrn) {
    uchar_t regVal = env.read_reg_byte(portAddr);
    auto toSkip = (bool) (is_nbi(regVal,bitNum));
    return SkipNextInstrn(env, toSkip, nextInstrn);
}

bool BranchOps::SBIS(Environ &env, uint32_t instrn, InstrnEnum nextInstrn) {
    FiveBit portNum; ThreeBit bitNum;
    ArgsDecode::IO5Bit3(instrn, portNum, bitNum);
    FiveBit portAddr = portNum + 0x20;
    return SBRC(env, portAddr, bitNum, nextInstrn);
}

bool BranchOps::SBIS(Environ &env, FiveBit portAddr, ThreeBit bitNum, InstrnEnum nextInstrn) {
    uchar_t regVal = env.read_reg_byte(portAddr);
    auto toSkip = (bool) (is_bi(regVal,bitNum));
    return SkipNextInstrn(env, toSkip, nextInstrn);
}

bool BranchOps::SkipNextInstrn(Environ& env, bool skip, InstrnEnum nextInstrn) {
    uchar_t bytesToSkip = 0;
    if (skip)
        bytesToSkip = isLongInstrn(nextInstrn) ? 8 : 4;
    env.PC = env.PC + 4 + bytesToSkip;
    return true;
}

bool BranchOps::BRBS(Environ &env, uint32_t instrn) {
    SevenBit offset; ThreeBit regBit;
    ArgsDecode::Addr7Bit3(instrn, offset, regBit);
    return BRBS(env, offset, regBit);
}

bool BranchOps::BRBS(Environ &env, SevenBit offset, ThreeBit regBit) {
    uchar_t status = env.sReg.getFlags();
    bool isSet = is_bi(status, regBit);
    if (isSet) {
        env.PC = env.PC + offset;
        return true;
    } else {
        env.PC = env.PC + 2;
        return true;
    }
}

