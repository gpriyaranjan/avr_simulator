//
// Created by MAC BOOK on 28/08/23.
//

#include "../gen1/call_ops.h"
#include "../gen1/branch_ops.h"
#include "../environment.h"
#include "../types.h"
#include "../gen1/branch_ops_impl.h"

class BranchOpsImplP {
public:
    static bool Branchif(Environ& env, bool toSkip, SevenBit offset);
    static bool SkipNextInstrn(Environ& env, bool skip, InstrnEnum nextInstrn);
};

bool BranchOpsImplP::SkipNextInstrn(Environ& env, bool skip, InstrnEnum nextInstrn) {
    uchar_t bytesToSkip = 0;
    if (skip)
        bytesToSkip = isLongInstrn(nextInstrn) ? 8 : 4;
    env.PC = env.PC + 4 + bytesToSkip;
    return true;
}

bool BranchOpsImplP::Branchif(Environ& env, bool toSkip, SevenBit offset) {
    if (toSkip) {
        env.PC = env.PC + offset;
        return true;
    } else {
        env.PC = env.PC + 2;
        return true;
    }
}

bool BranchOpsImpl::CPSE(Environ &env, FiveBit reg1Addr, FiveBit reg2Addr, InstrnEnum nextInstrn) {
    uchar_t value1 = env.read_reg_byte(reg1Addr);
    uchar_t value2 = env.read_reg_byte(reg2Addr);
    bool toSkip = value1 == value2;
    return BranchOpsImplP::SkipNextInstrn(env, toSkip, nextInstrn);
}

bool BranchOpsImpl::SBRC(Environ &env, FiveBit regAddr, ThreeBit bitNum, InstrnEnum nextInstrn) {
    uchar_t regVal = env.read_reg_byte(regAddr);
    auto toSkip = (bool) (is_nbi(regVal,bitNum));
    return BranchOpsImplP::SkipNextInstrn(env, toSkip, nextInstrn);
}

bool BranchOpsImpl::SBRS(Environ &env, FiveBit regAddr, ThreeBit bitNum, InstrnEnum nextInstrn) {
    uchar_t regVal = env.read_reg_byte(regAddr);
    auto toSkip = (bool) (is_bi(regVal,bitNum));
    return BranchOpsImplP::SkipNextInstrn(env, toSkip, nextInstrn);
}

bool BranchOpsImpl::SBIC(Environ &env, FiveBit portAddr, ThreeBit bitNum, InstrnEnum nextInstrn) {
    uchar_t regVal = env.read_reg_byte(portAddr);
    auto toSkip = (bool) (is_nbi(regVal,bitNum));
    return BranchOpsImplP::SkipNextInstrn(env, toSkip, nextInstrn);
}

bool BranchOpsImpl::SBIS(Environ &env, FiveBit portAddr, ThreeBit bitNum, InstrnEnum nextInstrn) {
    uchar_t regVal = env.read_reg_byte(portAddr);
    auto toSkip = (bool) (is_bi(regVal,bitNum));
    return BranchOpsImplP::SkipNextInstrn(env, toSkip, nextInstrn);
}

bool BranchOpsImpl::BRBS(Environ &env, SevenBit offset, ThreeBit regBit) {
    uchar_t status = env.sReg.getFlags();
    bool isSet = is_bi(status, regBit);
    return BranchOpsImplP::Branchif(env, isSet, offset);
}

bool BranchOpsImpl::BRBC(Environ &env, SevenBit offset, ThreeBit regBit) {
    uchar_t status = env.sReg.getFlags();
    bool isSet = is_nbi(status, regBit);
    return BranchOpsImplP::Branchif(env, isSet, offset);
}

bool BranchOpsImpl::BREQ(Environ &env, SevenBit offset) {
    return BRBS(env, offset, ZBit);
}

bool BranchOpsImpl::BRNE(Environ &env, SevenBit offset) {
    return BRBS(env, offset, ZBit);
}

bool BranchOpsImpl::BRCS(Environ &env, SevenBit offset) {
    return BRBS(env, offset, CBit);
}

bool BranchOpsImpl::BRCC(Environ &env, SevenBit offset) {
    return BRBC(env, offset, CBit);
}

bool BranchOpsImpl::BRLO(Environ &env, SevenBit offset) {
    return BRBS(env, offset, CBit);
}

bool BranchOpsImpl::BRSH(Environ &env, SevenBit offset) {
    return BRBC(env, offset, CBit);
}

bool BranchOpsImpl::BRMI(Environ &env, SevenBit offset) {
    return BRBS(env, offset, NBit);
}

bool BranchOpsImpl::BRPL(Environ &env, SevenBit offset) {
    return BRBC(env, offset, NBit);
}

bool BranchOpsImpl::BRVS(Environ &env, SevenBit offset) {
    return BRBS(env, offset, VBit);
}

bool BranchOpsImpl::BRVC(Environ &env, SevenBit offset) {
    return BRBC(env, offset, VBit);
}

bool BranchOpsImpl::BRLT(Environ &env, SevenBit offset) {
    return BRBS(env, offset, SBit);
}

bool BranchOpsImpl::BRGE(Environ &env, SevenBit offset) {
    return BRBC(env, offset, SBit);
}

bool BranchOpsImpl::BRHS(Environ &env, SevenBit offset) {
    return BRBS(env, offset, HBit);
}

bool BranchOpsImpl::BRHC(Environ &env, SevenBit offset) {
    return BRBC(env, offset, HBit);
}

bool BranchOpsImpl::BRTS(Environ &env, SevenBit offset) {
    return BRBS(env, offset, TBit);
}

bool BranchOpsImpl::BRTC(Environ &env, SevenBit offset) {
    return BRBC(env, offset, TBit);
}

bool BranchOpsImpl::BRIE(Environ &env, SevenBit offset) {
    return BRBS(env, offset, IBit);
}

bool BranchOpsImpl::BRID(Environ &env, SevenBit offset) {
    return BRBC(env, offset, IBit);
}

