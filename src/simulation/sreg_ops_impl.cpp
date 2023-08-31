//
// Created by MAC BOOK on 28/08/23.
//

#include "v1/sreg_ops.h"
#include "decoder.h"
#include "v1/sreg_ops_impl.h"

bool SRegOpsImpl::WriteBit(Environ &env, ThreeBit regNum, bool value) {

    auto regBit = (SMasks)(1 << regNum);

    switch(regBit) {
        case CMask:
            env.sReg.setC(true);
            break;
        case ZMask:
            env.sReg.setZ(true);
            break;
        case NMask:
            env.sReg.setN(true);
            break;
        case VMask:
            env.sReg.setV(true);
            break;
        case SMask:
            env.sReg.setS(true);
            break;
        case HMask:
            env.sReg.setH(true);
            break;
        case TMask:
            env.sReg.setT(true);
            break;
        case IMask:
            env.sReg.setI(true);
            break;
        default:
            break;
    }
    return false;
}

bool SRegOpsImpl::BSET(Environ &env, ThreeBit regNum, bool dummy) {
    return WriteBit(env, regNum, true);
}

bool SRegOpsImpl::BCLR(Environ &env, ThreeBit regNum, bool dummy) {
    return WriteBit(env, regNum, false);
}

bool SRegOpsImpl::SEC(Environ &env) {
    return SRegOps::BSET(env, CBit);
}

bool SRegOpsImpl::CLC(Environ &env) {
    return SRegOps::BCLR(env, CBit);
}

bool SRegOpsImpl::SEZ(Environ &env) {
    return SRegOps::BSET(env, ZBit);
}

bool SRegOpsImpl::CLZ(Environ &env) {
    return SRegOps::BCLR(env, ZBit);
}

bool SRegOpsImpl::SEN(Environ &env) {
    return SRegOps::BSET(env, NBit);
}

bool SRegOpsImpl::CLN(Environ &env) {
    return SRegOps::BCLR(env, NBit);
}

bool SRegOpsImpl::SEV(Environ &env) {
    return SRegOps::BSET(env, VBit);
}

bool SRegOpsImpl::CLV(Environ &env) {
    return SRegOps::BCLR(env, VBit);
}

bool SRegOpsImpl::SES(Environ &env) {
    return SRegOps::BSET(env, SBit);
}

bool SRegOpsImpl::CLS(Environ &env) {
    return SRegOps::BCLR(env, SBit);
}

bool SRegOpsImpl::SEH(Environ &env) {
    return SRegOps::BSET(env, HBit);
}

bool SRegOpsImpl::CLH(Environ &env) {
    return SRegOps::BCLR(env, HBit);
}

bool SRegOpsImpl::SET(Environ &env) {
    return SRegOps::BSET(env, SBit);
}

bool SRegOpsImpl::CLT(Environ &env) {
    return SRegOps::BCLR(env, TBit);
}

bool SRegOpsImpl::BST(Environ &env, FiveBit tgtAddr, ThreeBit regNum) {
    uchar_t tgtValue = env.read_reg_byte(tgtAddr);
    bool tBit = is_bi(tgtValue, regNum);
    env.sReg.setT(tBit);
    return false;
}

bool SRegOpsImpl::BLD(Environ &env, FiveBit tgtAddr, ThreeBit regNum) {
    uchar_t tgtValue = env.read_reg_byte(tgtAddr);
    uchar_t tBitMask = env.sReg.T() << regNum;
    uchar_t result = tgtValue | tBitMask;
    env.write_reg_byte(tgtAddr, result);
    return false;
}