#include "decoder.h"
#include "sreg_ops.h"

bool SRegOps::WriteBit(Environ &env, ThreeBit regNum, bool value) {

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

bool SRegOps::BSET(Environ &env, u_int32_t instrn) {
    ThreeBit regNum;
    ArgsDecode::SBit3(instrn, regNum);
    return BSET(env, regNum, true);
}

bool SRegOps::BSET(Environ &env, ThreeBit regNum, bool dummy) {
    return WriteBit(env, regNum, true);
}

bool SRegOps::BCLR(Environ &env, u_int32_t instrn) {
    ThreeBit regNum;
    ArgsDecode::SBit3(instrn, regNum);
    return BCLR(env, regNum, true);
}

bool SRegOps::BCLR(Environ &env, ThreeBit regNum, bool dummy) {
    return WriteBit(env, regNum, false);
}

bool SRegOps::SEC(Environ &env, u_int32_t instrn) {
    return SEC(env);
}

bool SRegOps::SEC(Environ &env) {
    return BSET(env, CBit);
}

bool SRegOps::CLC(Environ &env, u_int32_t instrn) {
    return CLC(env);
}

bool SRegOps::CLC(Environ &env) {
    return BCLR(env, CBit);
}

bool SRegOps::SEZ(Environ &env, u_int32_t instrn) {
    return SEZ(env);
}

bool SRegOps::SEZ(Environ &env) {
    return BSET(env, ZBit);
}

bool SRegOps::CLZ(Environ &env, u_int32_t instrn) {
    return CLZ(env);
}

bool SRegOps::CLZ(Environ &env) {
    return BCLR(env, ZBit);
}

bool SRegOps::SEN(Environ &env, u_int32_t instrn) {
    return SEN(env);
}

bool SRegOps::SEN(Environ &env) {
    return BSET(env, NBit);
}

bool SRegOps::CLN(Environ &env, u_int32_t instrn) {
    return CLN(env);
}

bool SRegOps::CLN(Environ &env) {
    return BCLR(env, NBit);
}

bool SRegOps::SEV(Environ &env, uint32_t instrn) {
    return SEV(env);
}

bool SRegOps::SEV(Environ &env) {
    return BSET(env, VBit);
}

bool SRegOps::CLV(Environ &env, uint32_t instrn) {
    return CLV(env);
}

bool SRegOps::CLV(Environ &env) {
    return BCLR(env, VBit);
}

bool SRegOps::SES(Environ &env, uint32_t instrn) {
    return SES(env);
}

bool SRegOps::SES(Environ &env) {
    return BSET(env, SBit);
}

bool SRegOps::CLS(Environ &env, uint32_t instrn) {
    return CLS(env);
}

bool SRegOps::CLS(Environ &env) {
    return BCLR(env, SBit);
}

bool SRegOps::SEH(Environ &env, uint32_t instrn) {
    return SEH(env);
}

bool SRegOps::SEH(Environ &env) {
    return BSET(env, HBit);
}

bool SRegOps::CLH(Environ &env, uint32_t instrn) {
    return CLH(env);
}

bool SRegOps::CLH(Environ &env) {
    return BCLR(env, HBit);
}

bool SRegOps::SET(Environ &env, uint32_t instrn) {
    return SET(env);
}

bool SRegOps::SET(Environ &env) {
    return BSET(env, SBit);
}

bool SRegOps::CLT(Environ &env, uint32_t instrn) {
    return CLT(env);
}

bool SRegOps::CLT(Environ &env) {
    return BCLR(env, TBit);
}

bool SRegOps::BST(Environ &env, uint32_t instrn) {
    FiveBit tgtReg; ThreeBit bitNum;
    ArgsDecode::Reg5SBit3(instrn, tgtReg, bitNum);
    return BST(env, tgtReg, bitNum);
}

bool SRegOps::BST(Environ &env, FiveBit tgtAddr, ThreeBit regNum) {
    uchar_t tgtValue = env.read_reg_byte(tgtAddr);
    bool tBit = is_bi(tgtValue, regNum);
    env.sReg.setT(tBit);
    return false;
}

bool SRegOps::BLD(Environ &env, uint32_t instrn) {
    FiveBit tgtReg; ThreeBit bitNum;
    ArgsDecode::Reg5SBit3(instrn, tgtReg, bitNum);
    return BLD(env, tgtReg, bitNum);
}

bool SRegOps::BLD(Environ &env, FiveBit tgtAddr, ThreeBit regNum) {
    uchar_t tgtValue = env.read_reg_byte(tgtAddr);
    uchar_t tBitMask = env.sReg.T() << regNum;
    uchar_t result = tgtValue | tBitMask;
    env.write_reg_byte(tgtAddr, result);
    return false;
}

