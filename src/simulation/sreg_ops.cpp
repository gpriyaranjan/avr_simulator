#include "decoder.h"
#include "sreg_ops.h"

void SRegOps::WriteBit(Environ &env, ThreeBit regNum, bool value) {

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
}

void SRegOps::BSET(Environ &env, u_int32_t instrn) {
    ThreeBit regNum;
    ArgsDecode::SBit3(instrn, regNum);
    BSET(env, regNum, true);
}

void SRegOps::BSET(Environ &env, ThreeBit regNum, bool dummy) {
    WriteBit(env, regNum, true);
}

void SRegOps::BCLR(Environ &env, u_int32_t instrn) {
    ThreeBit regNum;
    ArgsDecode::SBit3(instrn, regNum);
    BCLR(env, regNum, true);
}

void SRegOps::BCLR(Environ &env, ThreeBit regNum, bool dummy) {
    WriteBit(env, regNum, false);
}

void SRegOps::SEC(Environ &env, u_int32_t instrn) {
    SEC(env);
}

void SRegOps::SEC(Environ &env) {
    BSET(env, CBit);
}

void SRegOps::CLC(Environ &env, u_int32_t instrn) {
    CLC(env);
}

void SRegOps::CLC(Environ &env) {
    BCLR(env, CBit);
}

void SRegOps::SEZ(Environ &env, u_int32_t instrn) {
    SEZ(env);
}

void SRegOps::SEZ(Environ &env) {
    BSET(env, ZBit);
}

void SRegOps::CLZ(Environ &env, u_int32_t instrn) {
    CLZ(env);
}

void SRegOps::CLZ(Environ &env) {
    BCLR(env, ZBit);
}

void SRegOps::SEN(Environ &env, u_int32_t instrn) {
    SEN(env);
}

void SRegOps::SEN(Environ &env) {
    BSET(env, NBit);
}

void SRegOps::CLN(Environ &env, u_int32_t instrn) {
    CLN(env);
}

void SRegOps::CLN(Environ &env) {
    BCLR(env, NBit);
}

void SRegOps::SEV(Environ &env, uint32_t instrn) {
    SEV(env);
}

void SRegOps::SEV(Environ &env) {
    BSET(env, VBit);
}

void SRegOps::CLV(Environ &env, uint32_t instrn) {
    CLV(env);
}

void SRegOps::CLV(Environ &env) {
    BCLR(env, VBit);
}

void SRegOps::SES(Environ &env, uint32_t instrn) {
    SES(env);
}

void SRegOps::SES(Environ &env) {
    BSET(env, SBit);
}

void SRegOps::CLS(Environ &env, uint32_t instrn) {
    CLS(env);
}

void SRegOps::CLS(Environ &env) {
    BCLR(env, SBit);
}

void SRegOps::SEH(Environ &env, uint32_t instrn) {
    SEH(env);
}

void SRegOps::SEH(Environ &env) {
    BSET(env, HBit);
}

void SRegOps::CLH(Environ &env, uint32_t instrn) {
    CLH(env);
}

void SRegOps::CLH(Environ &env) {
    BCLR(env, HBit);
}

void SRegOps::SET(Environ &env, uint32_t instrn) {
    SET(env);
}

void SRegOps::SET(Environ &env) {
    BSET(env, SBit);
}

void SRegOps::CLT(Environ &env, uint32_t instrn) {
    CLT(env);
}

void SRegOps::CLT(Environ &env) {
    BCLR(env, TBit);
}

void SRegOps::BST(Environ &env, uint32_t instrn) {
    FiveBit tgtReg; ThreeBit bitNum;
    ArgsDecode::Reg5SBit3(instrn, tgtReg, bitNum);
    BST(env, tgtReg, bitNum);
}

void SRegOps::BST(Environ &env, FiveBit tgtAddr, ThreeBit regNum) {
    uchar_t tgtValue = env.read_register(tgtAddr);
    bool tBit = is_bi(tgtValue, regNum);
    env.sReg.setT(tBit);
}

void SRegOps::BLD(Environ &env, uint32_t instrn) {
    FiveBit tgtReg; ThreeBit bitNum;
    ArgsDecode::Reg5SBit3(instrn, tgtReg, bitNum);
    BLD(env, tgtReg, bitNum);
}

void SRegOps::BLD(Environ &env, FiveBit tgtAddr, ThreeBit regNum) {
    uchar_t tgtValue = env.read_register(tgtAddr);
    uchar_t tBitMask = env.sReg.T() << regNum;
    uchar_t result = tgtValue | tBitMask;
    env.write_register(tgtAddr, result);
}

