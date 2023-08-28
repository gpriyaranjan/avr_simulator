//
// Created by MAC BOOK on 28/08/23.
//

#include "sreg_ops.h"
#include "decoder.h"
#include "sreg_ops_mc.h"

bool SRegOpsMc::WriteBit(Environ &env, ThreeBit regNum, bool value) {

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

bool SRegOpsMc::BSET(Environ &env, ThreeBit regNum, bool dummy) {
    return WriteBit(env, regNum, true);
}

bool SRegOpsMc::BCLR(Environ &env, ThreeBit regNum, bool dummy) {
    return WriteBit(env, regNum, false);
}

bool SRegOpsMc::SEC(Environ &env) {
    return SRegOps::BSET(env, CBit);
}

bool SRegOpsMc::CLC(Environ &env) {
    return SRegOps::BCLR(env, CBit);
}

bool SRegOpsMc::SEZ(Environ &env) {
    return SRegOps::BSET(env, ZBit);
}

bool SRegOpsMc::CLZ(Environ &env) {
    return SRegOps::BCLR(env, ZBit);
}

bool SRegOpsMc::SEN(Environ &env) {
    return SRegOps::BSET(env, NBit);
}

bool SRegOpsMc::CLN(Environ &env) {
    return SRegOps::BCLR(env, NBit);
}

bool SRegOpsMc::SEV(Environ &env) {
    return SRegOps::BSET(env, VBit);
}

bool SRegOpsMc::CLV(Environ &env) {
    return SRegOps::BCLR(env, VBit);
}

bool SRegOpsMc::SES(Environ &env) {
    return SRegOps::BSET(env, SBit);
}

bool SRegOpsMc::CLS(Environ &env) {
    return SRegOps::BCLR(env, SBit);
}

bool SRegOpsMc::SEH(Environ &env) {
    return SRegOps::BSET(env, HBit);
}

bool SRegOpsMc::CLH(Environ &env) {
    return SRegOps::BCLR(env, HBit);
}

bool SRegOpsMc::SET(Environ &env) {
    return SRegOps::BSET(env, SBit);
}

bool SRegOpsMc::CLT(Environ &env) {
    return SRegOps::BCLR(env, TBit);
}

bool SRegOpsMc::BST(Environ &env, FiveBit tgtAddr, ThreeBit regNum) {
    uchar_t tgtValue = env.read_reg_byte(tgtAddr);
    bool tBit = is_bi(tgtValue, regNum);
    env.sReg.setT(tBit);
    return false;
}

bool SRegOpsMc::BLD(Environ &env, FiveBit tgtAddr, ThreeBit regNum) {
    uchar_t tgtValue = env.read_reg_byte(tgtAddr);
    uchar_t tBitMask = env.sReg.T() << regNum;
    uchar_t result = tgtValue | tBitMask;
    env.write_reg_byte(tgtAddr, result);
    return false;
}