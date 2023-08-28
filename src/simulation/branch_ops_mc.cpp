//
// Created by MAC BOOK on 28/08/23.
//

#include "call_ops.h"
#include "branch_ops.h"
#include "environment.h"
#include "decoder.h"
#include "types.h"
#include "branch_ops_mc.h"

bool BranchOpsMc::CPSE(Environ &env, FiveBit reg1Addr, FiveBit reg2Addr, InstrnEnum nextInstrn) {
    uchar_t value1 = env.read_reg_byte(reg1Addr);
    uchar_t value2 = env.read_reg_byte(reg2Addr);
    bool toSkip = value1 == value2;
    return SkipNextInstrn(env, toSkip, nextInstrn);
}

bool BranchOpsMc::SBRC(Environ &env, FiveBit regAddr, ThreeBit bitNum, InstrnEnum nextInstrn) {
    uchar_t regVal = env.read_reg_byte(regAddr);
    auto toSkip = (bool) (is_nbi(regVal,bitNum));
    return SkipNextInstrn(env, toSkip, nextInstrn);
}

bool BranchOpsMc::SBRS(Environ &env, FiveBit regAddr, ThreeBit bitNum, InstrnEnum nextInstrn) {
    uchar_t regVal = env.read_reg_byte(regAddr);
    auto toSkip = (bool) (is_bi(regVal,bitNum));
    return SkipNextInstrn(env, toSkip, nextInstrn);
}

bool BranchOpsMc::SBIC(Environ &env, FiveBit portAddr, ThreeBit bitNum, InstrnEnum nextInstrn) {
    uchar_t regVal = env.read_reg_byte(portAddr);
    auto toSkip = (bool) (is_nbi(regVal,bitNum));
    return SkipNextInstrn(env, toSkip, nextInstrn);
}

bool BranchOpsMc::SBIS(Environ &env, FiveBit portAddr, ThreeBit bitNum, InstrnEnum nextInstrn) {
    uchar_t regVal = env.read_reg_byte(portAddr);
    auto toSkip = (bool) (is_bi(regVal,bitNum));
    return SkipNextInstrn(env, toSkip, nextInstrn);
}

bool BranchOpsMc::SkipNextInstrn(Environ& env, bool skip, InstrnEnum nextInstrn) {
    uchar_t bytesToSkip = 0;
    if (skip)
        bytesToSkip = isLongInstrn(nextInstrn) ? 8 : 4;
    env.PC = env.PC + 4 + bytesToSkip;
    return true;
}

bool BranchOpsMc::BRBS(Environ &env, SevenBit offset, ThreeBit regBit) {
    uchar_t status = env.sReg.getFlags();
    bool isSet = is_bi(status, regBit);
    return Branchif(env, isSet, offset);
}

bool BranchOpsMc::BRBC(Environ &env, SevenBit offset, ThreeBit regBit) {
    uchar_t status = env.sReg.getFlags();
    bool isSet = is_nbi(status, regBit);
    return Branchif(env, isSet, offset);
}

bool BranchOpsMc::BREQ(Environ &env, SevenBit offset) {
    return BRBS(env, offset, ZBit);
}

bool BranchOpsMc::BRNE(Environ &env, SevenBit offset) {
    return BRBS(env, offset, ZBit);
}

bool BranchOpsMc::BRCS(Environ &env, SevenBit offset) {
    return BRBS(env, offset, CBit);
}

bool BranchOpsMc::BRCC(Environ &env, SevenBit offset) {
    return BRBC(env, offset, CBit);
}

bool BranchOpsMc::BRLO(Environ &env, SevenBit offset) {
    return BRBS(env, offset, CBit);
}

bool BranchOpsMc::BRSH(Environ &env, SevenBit offset) {
    return BRBC(env, offset, CBit);
}

bool BranchOpsMc::BRMI(Environ &env, SevenBit offset) {
    return BRBS(env, offset, NBit);
}

bool BranchOpsMc::BRPL(Environ &env, SevenBit offset) {
    return BRBC(env, offset, NBit);
}

bool BranchOpsMc::BRVS(Environ &env, SevenBit offset) {
    return BRBS(env, offset, VBit);
}

bool BranchOpsMc::BRVC(Environ &env, SevenBit offset) {
    return BRBC(env, offset, VBit);
}

bool BranchOpsMc::BRLT(Environ &env, SevenBit offset) {
    return BRBS(env, offset, SBit);
}

bool BranchOpsMc::BRGE(Environ &env, SevenBit offset) {
    return BRBC(env, offset, SBit);
}

bool BranchOpsMc::BRHS(Environ &env, SevenBit offset) {
    return BRBS(env, offset, HBit);
}

bool BranchOpsMc::BRHC(Environ &env, SevenBit offset) {
    return BRBC(env, offset, HBit);
}

bool BranchOpsMc::BRTS(Environ &env, SevenBit offset) {
    return BRBS(env, offset, TBit);
}

bool BranchOpsMc::BRTC(Environ &env, SevenBit offset) {
    return BRBC(env, offset, TBit);
}

bool BranchOpsMc::BRIE(Environ &env, SevenBit offset) {
    return BRBS(env, offset, IBit);
}

bool BranchOpsMc::BRID(Environ &env, SevenBit offset) {
    return BRBC(env, offset, IBit);
}

bool BranchOpsMc::Branchif(Environ& env, bool toSkip, SevenBit offset) {
    if (toSkip) {
        env.PC = env.PC + offset;
        return true;
    } else {
        env.PC = env.PC + 2;
        return true;
    }
}