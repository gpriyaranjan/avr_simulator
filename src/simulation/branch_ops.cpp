#include "types.h"
#include "decoder.h"
#include "environment.h"
#include "branch_ops.h"
#include "call_ops.h"

bool BranchOps::CPSE(Environ &env, uint16_t instrn, InstrnEnum nextInstrn) {
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

bool BranchOps::SBRC(Environ &env, uint16_t instrn, InstrnEnum nextInstrn) {
    FiveBit regAddr; ThreeBit bitNum;
    ArgsDecode::Reg5SBit3(instrn, regAddr, bitNum);
    return SBRC(env, regAddr, bitNum, nextInstrn);
}

bool BranchOps::SBRC(Environ &env, FiveBit regAddr, ThreeBit bitNum, InstrnEnum nextInstrn) {
    uchar_t regVal = env.read_reg_byte(regAddr);
    auto toSkip = (bool) (is_nbi(regVal,bitNum));
    return SkipNextInstrn(env, toSkip, nextInstrn);
}

bool BranchOps::SBRS(Environ &env, uint16_t instrn, InstrnEnum nextInstrn) {
    FiveBit regAddr; ThreeBit bitNum;
    ArgsDecode::Reg5SBit3(instrn, regAddr, bitNum);
    return SBRS(env, regAddr, bitNum, nextInstrn);
}

bool BranchOps::SBRS(Environ &env, FiveBit regAddr, ThreeBit bitNum, InstrnEnum nextInstrn) {
    uchar_t regVal = env.read_reg_byte(regAddr);
    auto toSkip = (bool) (is_bi(regVal,bitNum));
    return SkipNextInstrn(env, toSkip, nextInstrn);
}

bool BranchOps::SBIC(Environ &env, uint16_t instrn, InstrnEnum nextInstrn) {
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

bool BranchOps::SBIS(Environ &env, uint16_t instrn, InstrnEnum nextInstrn) {
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

bool BranchOps::BRBS(Environ &env, uint16_t instrn) {
    SevenBit offset; ThreeBit regBit;
    ArgsDecode::Addr7Bit3(instrn, offset, regBit);
    return BRBS(env, offset, regBit);
}

bool BranchOps::BRBS(Environ &env, SevenBit offset, ThreeBit regBit) {
    uchar_t status = env.sReg.getFlags();
    bool isSet = is_bi(status, regBit);
    return Branchif(env, isSet, offset);
}

bool BranchOps::BRBC(Environ &env, uint16_t instrn) {
    SevenBit offset; ThreeBit regBit;
    ArgsDecode::Addr7Bit3(instrn, offset, regBit);
    return BRBC(env, offset, regBit);
}

bool BranchOps::BRBC(Environ &env, SevenBit offset, ThreeBit regBit) {
    uchar_t status = env.sReg.getFlags();
    bool isSet = is_nbi(status, regBit);
    return Branchif(env, isSet, offset);
}

bool BranchOps::BREQ(Environ &env, uint16_t instrn) {
    return BRBS(env, instrn);
}

bool BranchOps::BREQ(Environ &env, SevenBit offset) {
    return BRBS(env, offset, ZBit);
}

bool BranchOps::BRNE(Environ &env, uint16_t instrn) {
    return BRBC(env, instrn);
}

bool BranchOps::BRNE(Environ &env, SevenBit offset) {
    return BRBS(env, offset, ZBit);
}

bool BranchOps::BRCS(Environ &env, uint16_t instrn) {
    return BRBS(env, instrn);
}

bool BranchOps::BRCS(Environ &env, SevenBit offset) {
    return BRBS(env, offset, CBit);
}

bool BranchOps::BRCC(Environ &env, uint16_t instrn) {
    return BRBC(env, instrn);
}

bool BranchOps::BRCC(Environ &env, SevenBit offset) {
    return BRBC(env, offset, CBit);
}

bool BranchOps::BRLO(Environ &env, uint16_t instrn) {
    return BRBS(env, instrn);
}

bool BranchOps::BRLO(Environ &env, SevenBit offset) {
    return BRBS(env, offset, CBit);
}

bool BranchOps::BRSH(Environ &env, uint16_t instrn) {
    return BRBC(env, instrn);
}

bool BranchOps::BRSH(Environ &env, SevenBit offset) {
    return BRBC(env, offset, CBit);
}

bool BranchOps::BRMI(Environ &env, uint16_t instrn) {
    return BRBS(env, instrn);
}

bool BranchOps::BRMI(Environ &env, SevenBit offset) {
    return BRBS(env, offset, NBit);
}

bool BranchOps::BRPL(Environ &env, uint16_t instrn) {
    return BRBC(env, instrn);
}

bool BranchOps::BRPL(Environ &env, SevenBit offset) {
    return BRBC(env, offset, NBit);
}

bool BranchOps::BRVS(Environ &env, uint16_t instrn) {
    return BRBS(env, instrn);
}

bool BranchOps::BRVS(Environ &env, SevenBit offset) {
    return BRBS(env, offset, VBit);
}

bool BranchOps::BRVC(Environ &env, uint16_t instrn) {
    return BRBC(env, instrn);
}

bool BranchOps::BRVC(Environ &env, SevenBit offset) {
    return BRBC(env, offset, VBit);
}

bool BranchOps::BRLT(Environ &env, uint16_t instrn) {
    return BRBS(env, instrn);
}

bool BranchOps::BRLT(Environ &env, SevenBit offset) {
    return BRBS(env, offset, SBit);
}

bool BranchOps::BRGE(Environ &env, uint16_t instrn) {
    return BRBC(env, instrn);
}

bool BranchOps::BRGE(Environ &env, SevenBit offset) {
    return BRBC(env, offset, SBit);
}

bool BranchOps::BRHS(Environ &env, uint16_t instrn) {
    return BRBS(env, instrn);
}

bool BranchOps::BRHS(Environ &env, SevenBit offset) {
    return BRBS(env, offset, HBit);
}

bool BranchOps::BRHC(Environ &env, uint16_t instrn) {
    return BRBC(env, instrn);
}

bool BranchOps::BRHC(Environ &env, SevenBit offset) {
    return BRBC(env, offset, HBit);
}

bool BranchOps::BRTS(Environ &env, uint16_t instrn) {
    return BRBS(env, instrn);
}

bool BranchOps::BRTS(Environ &env, SevenBit offset) {
    return BRBS(env, offset, TBit);
}

bool BranchOps::BRTC(Environ &env, uint16_t instrn) {
    return BRBC(env, instrn);
}

bool BranchOps::BRTC(Environ &env, SevenBit offset) {
    return BRBC(env, offset, TBit);
}

bool BranchOps::BRIE(Environ &env, uint16_t instrn) {
    return BRBS(env, instrn);
}

bool BranchOps::BRIE(Environ &env, SevenBit offset) {
    return BRBS(env, offset, IBit);
}

bool BranchOps::BRID(Environ &env, uint16_t instrn) {
    return BRBC(env, instrn);
}

bool BranchOps::BRID(Environ &env, SevenBit offset) {
    return BRBC(env, offset, IBit);
}

bool BranchOps::Branchif(Environ& env, bool toSkip, SevenBit offset) {
    if (toSkip) {
        env.PC = env.PC + offset;
        return true;
    } else {
        env.PC = env.PC + 2;
        return true;
    }
}
