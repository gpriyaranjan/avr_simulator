#include "../gen2/call_ops.h"
#include "../gen2/branch_ops.h"
#include "../infra/environment.h"
#include "../ops/instrn_enum.h"
#include "../infra/types.h"
#include "../gen2/branch_ops_impl.h"

void BranchOpsImpl::CPSE(Environ &env, FiveBit reg1Addr, FiveBit reg2Addr) {
    uchar_t value1 = env.read_reg_byte(reg1Addr);
    uchar_t value2 = env.read_reg_byte(reg2Addr);
    bool toSkip = value1 == value2;
    env.CU.setSkipNext(toSkip);
}

void BranchOpsImpl::SBRC(Environ &env, FiveBit regAddr, ThreeBit bitNum) {
    uchar_t regVal = env.read_reg_byte(regAddr);
    auto toSkip = (bool) (is_nbi(regVal,bitNum));
    env.CU.setSkipNext(toSkip);
}

void BranchOpsImpl::SBRS(Environ &env, FiveBit regAddr, ThreeBit bitNum) {
    uchar_t regVal = env.read_reg_byte(regAddr);
    auto toSkip = (bool) (is_bi(regVal,bitNum));
    env.CU.setSkipNext(toSkip);
}

void BranchOpsImpl::SBIC(Environ &env, FiveBit portAddr, ThreeBit bitNum) {
    uchar_t regVal = env.read_reg_byte(portAddr);
    auto toSkip = (bool) (is_nbi(regVal,bitNum));
    env.CU.setSkipNext(toSkip);
}

void BranchOpsImpl::SBIS(Environ &env, FiveBit portAddr, ThreeBit bitNum) {
    uchar_t regVal = env.read_reg_byte(portAddr);
    auto toSkip = (bool) (is_bi(regVal,bitNum));
    env.CU.setSkipNext(toSkip);
}

void BranchOpsImpl::BRBS(Environ &env, SevenBit offset, ThreeBit regBit) {
    uchar_t status = env.sReg.getFlags();
    bool toJump = is_bi(status, regBit);
   env.CU.setRJump(offset, toJump);
}

void BranchOpsImpl::BRBC(Environ &env, SevenBit offset, ThreeBit regBit) {
    uchar_t status = env.sReg.getFlags();
    bool toJump = is_nbi(status, regBit);
    env.CU.setRJump(offset, toJump);
}

void BranchOpsImpl::BREQ(Environ &env, SevenBit offset) {
    BRBS(env, offset, ZBit);
}

void BranchOpsImpl::BRNE(Environ &env, SevenBit offset) {
    BRBC(env, offset, ZBit);
}

void BranchOpsImpl::BRCS(Environ &env, SevenBit offset) {
    BRBS(env, offset, CBit);
}

void BranchOpsImpl::BRCC(Environ &env, SevenBit offset) {
    BRBC(env, offset, CBit);
}

void BranchOpsImpl::BRLO(Environ &env, SevenBit offset) {
    BRBS(env, offset, CBit);
}

void BranchOpsImpl::BRSH(Environ &env, SevenBit offset) {
    BRBC(env, offset, CBit);
}

void BranchOpsImpl::BRMI(Environ &env, SevenBit offset) {
    BRBS(env, offset, NBit);
}

void BranchOpsImpl::BRPL(Environ &env, SevenBit offset) {
    BRBC(env, offset, NBit);
}

void BranchOpsImpl::BRVS(Environ &env, SevenBit offset) {
    BRBS(env, offset, VBit);
}

void BranchOpsImpl::BRVC(Environ &env, SevenBit offset) {
    BRBC(env, offset, VBit);
}

void BranchOpsImpl::BRLT(Environ &env, SevenBit offset) {
    BRBS(env, offset, SBit);
}

void BranchOpsImpl::BRGE(Environ &env, SevenBit offset) {
    BRBC(env, offset, SBit);
}

void BranchOpsImpl::BRHS(Environ &env, SevenBit offset) {
    BRBS(env, offset, HBit);
}

void BranchOpsImpl::BRHC(Environ &env, SevenBit offset) {
    BRBC(env, offset, HBit);
}

void BranchOpsImpl::BRTS(Environ &env, SevenBit offset) {
    BRBS(env, offset, TBit);
}

void BranchOpsImpl::BRTC(Environ &env, SevenBit offset) {
    BRBC(env, offset, TBit);
}

void BranchOpsImpl::BRIE(Environ &env, SevenBit offset) {
    BRBS(env, offset, IBit);
}

void BranchOpsImpl::BRID(Environ &env, SevenBit offset) {
    BRBC(env, offset, IBit);
}
