#include "../types.h"
#include "../infra/decoder.h"
#include "../environment.h"
#include "branch_ops.h"
#include "call_ops.h"
#include "branch_ops_impl.h"

bool BranchOps::CPSE(Environ &env, ShortInstrn instrn, InstrnEnum nextInstrn) {
    FiveBit regAddr1, regAddr2;
    ArgsDecode::TwoReg5(instrn, regAddr1, regAddr2);
    return BranchOpsImpl::CPSE(env, regAddr1, regAddr2, nextInstrn);
}

bool BranchOps::SBRC(Environ &env, ShortInstrn instrn, InstrnEnum nextInstrn) {
    FiveBit regAddr; ThreeBit bitNum;
    ArgsDecode::Reg5SBit3(instrn, regAddr, bitNum);
    return BranchOpsImpl::SBRC(env, regAddr, bitNum, nextInstrn);
}

bool BranchOps::SBRS(Environ &env, ShortInstrn instrn, InstrnEnum nextInstrn) {
    FiveBit regAddr; ThreeBit bitNum;
    ArgsDecode::Reg5SBit3(instrn, regAddr, bitNum);
    return BranchOpsImpl::SBRS(env, regAddr, bitNum, nextInstrn);
}

bool BranchOps::SBIC(Environ &env, ShortInstrn instrn, InstrnEnum nextInstrn) {
    FiveBit portNum; ThreeBit bitNum;
    ArgsDecode::IO5Bit3(instrn, portNum, bitNum);
    FiveBit portAddr = portNum + 0x20;
    return BranchOpsImpl::SBRC(env, portAddr, bitNum, nextInstrn);
}

bool BranchOps::SBIS(Environ &env, ShortInstrn instrn, InstrnEnum nextInstrn) {
    FiveBit portNum; ThreeBit bitNum;
    ArgsDecode::IO5Bit3(instrn, portNum, bitNum);
    FiveBit portAddr = portNum + 0x20;
    return BranchOpsImpl::SBRC(env, portAddr, bitNum, nextInstrn);
}

bool BranchOps::BRBS(Environ &env, ShortInstrn instrn) {
    SevenBit offset; ThreeBit regBit;
    ArgsDecode::Addr7Bit3(instrn, offset, regBit);
    return BranchOpsImpl::BRBS(env, offset, regBit);
}

bool BranchOps::BRBC(Environ &env, ShortInstrn instrn) {
    SevenBit offset; ThreeBit regBit;
    ArgsDecode::Addr7Bit3(instrn, offset, regBit);
    return BranchOpsImpl::BRBC(env, offset, regBit);
}

bool BranchOps::BREQ(Environ &env, ShortInstrn instrn) {
    return BRBS(env, instrn);
}

bool BranchOps::BRNE(Environ &env, ShortInstrn instrn) {
    return BRBC(env, instrn);
}

bool BranchOps::BRCS(Environ &env, ShortInstrn instrn) {
    return BRBS(env, instrn);
}

bool BranchOps::BRCC(Environ &env, ShortInstrn instrn) {
    return BRBC(env, instrn);
}

bool BranchOps::BRLO(Environ &env, ShortInstrn instrn) {
    return BRBS(env, instrn);
}

bool BranchOps::BRSH(Environ &env, ShortInstrn instrn) {
    return BRBC(env, instrn);
}

bool BranchOps::BRMI(Environ &env, ShortInstrn instrn) {
    return BRBS(env, instrn);
}

bool BranchOps::BRPL(Environ &env, ShortInstrn instrn) {
    return BRBC(env, instrn);
}

bool BranchOps::BRVS(Environ &env, ShortInstrn instrn) {
    return BRBS(env, instrn);
}

bool BranchOps::BRVC(Environ &env, ShortInstrn instrn) {
    return BRBC(env, instrn);
}

bool BranchOps::BRLT(Environ &env, ShortInstrn instrn) {
    return BRBS(env, instrn);
}

bool BranchOps::BRGE(Environ &env, ShortInstrn instrn) {
    return BRBC(env, instrn);
}

bool BranchOps::BRHS(Environ &env, ShortInstrn instrn) {
    return BRBS(env, instrn);
}

bool BranchOps::BRHC(Environ &env, ShortInstrn instrn) {
    return BRBC(env, instrn);
}

bool BranchOps::BRTS(Environ &env, ShortInstrn instrn) {
    return BRBS(env, instrn);
}

bool BranchOps::BRTC(Environ &env, ShortInstrn instrn) {
    return BRBC(env, instrn);
}

bool BranchOps::BRIE(Environ &env, ShortInstrn instrn) {
    return BRBS(env, instrn);
}

bool BranchOps::BRID(Environ &env, ShortInstrn instrn) {
    return BRBC(env, instrn);
}

