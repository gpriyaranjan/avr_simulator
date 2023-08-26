#include "decoder.h"
#include "sreg_ops.h"

void SRegOps::WriteBit(Environ &env, ThreeBit regNum, bool value) {

    auto regBit = (SMasks)(1 << regNum);

    switch(regBit) {
        case CMask:
            env.sReg.C = true;
            break;
        case ZMask:
            env.sReg.Z = true;
            break;
        case NMask:
            env.sReg.N = true;
            break;
        case VMask:
            env.sReg.V = true;
            break;
        case SMask:
            env.sReg.S = true;
            break;
        case HMask:
            env.sReg.H = true;
            break;
        case TMask:
            env.sReg.T = true;
            break;
        case IMask:
            env.sReg.I = true;
            break;
        default:
            break;
    }
}

void SRegOps::BSET(Environ &env, u_int32_t instrn) {
    ThreeBit regNum;
    ArgsDecode::SBit3(instrn, regNum);
    BSET_(env, regNum);
}

void SRegOps::BSET_(Environ &env, ThreeBit regNum) {
    WriteBit(env, regNum, true);
}

void SRegOps::BCLR(Environ &env, u_int32_t instrn) {
    ThreeBit regNum;
    ArgsDecode::SBit3(instrn, regNum);
    BCLR_(env, regNum);
}

void SRegOps::BCLR_(Environ &env, ThreeBit regNum) {
    WriteBit(env, regNum, false);
}

void SRegOps::SEC(Environ &env, u_int32_t instrn) {
    SEC_(env);
}

void SRegOps::SEC_(Environ &env) {
    BSET_(env, CBit);
}

void SRegOps::CLC(Environ &env, u_int32_t instrn) {
    CLC_(env);
}

void SRegOps::CLC_(Environ &env) {
    BCLR_(env, CBit);
}

void SRegOps::SEZ(Environ &env, u_int32_t instrn) {
    SEZ_(env);
}

void SRegOps::SEZ_(Environ &env) {
    BSET_(env, ZBit);
}

void SRegOps::CLZ(Environ &env, u_int32_t instrn) {
    CLZ_(env);
}

void SRegOps::CLZ_(Environ &env) {
    BCLR_(env, ZBit);
}

void SRegOps::SEN(Environ &env, u_int32_t instrn) {
    SEN_(env);
}

void SRegOps::SEN_(Environ &env) {
    BSET_(env, NBit);
}

void SRegOps::CLN(Environ &env, u_int32_t instrn) {
    CLN_(env);
}

void SRegOps::CLN_(Environ &env) {
    BCLR_(env, NBit);
}

void SRegOps::SEV(Environ &env, uint32_t instrn) {
    SEV_(env);
}

void SRegOps::SEV_(Environ &env) {
    BSET_(env, VBit);
}

void SRegOps::CLV(Environ &env, uint32_t instrn) {
    CLV_(env);
}

void SRegOps::CLV_(Environ &env) {
    BCLR_(env, VBit);
}

void SRegOps::SES(Environ &env, uint32_t instrn) {
    SES_(env);
}

void SRegOps::SES_(Environ &env) {
    BSET_(env, SBit);
}

void SRegOps::CLS(Environ &env, uint32_t instrn) {
    CLS_(env);
}

void SRegOps::CLS_(Environ &env) {
    BCLR_(env, SBit);
}

void SRegOps::SEH(Environ &env, uint32_t instrn) {
    SEH_(env);
}

void SRegOps::SEH_(Environ &env) {
    BSET_(env, HBit);
}

void SRegOps::CLH(Environ &env, uint32_t instrn) {
    CLH_(env);
}

void SRegOps::CLH_(Environ &env) {
    BCLR_(env, HBit);
}

void SRegOps::SET(Environ &env, uint32_t instrn) {
    SET_(env);
}

void SRegOps::SET_(Environ &env) {
    BSET_(env, SBit);
}

void SRegOps::CLT(Environ &env, uint32_t instrn) {
    CLT_(env);
}

void SRegOps::CLT_(Environ &env) {
    BCLR_(env, TBit);
}

void SRegOps::BST(Environ &env, uint32_t instrn) {
    FiveBit tgtReg; ThreeBit bitNum;
    ArgsDecode::Reg5SBit3(instrn, tgtReg, bitNum);
    BST_(env, tgtReg, bitNum);
}

void SRegOps::BST_(Environ &env, FiveBit tgtAddr, ThreeBit bitNum) {
    uchar_t tgtValue = env.read_register(tgtAddr);
    bool tBit = is_bi(tgtValue, bitNum);
    env.sReg.T = tBit;
}

void SRegOps::BLD(Environ &env, uint32_t instrn) {
    FiveBit tgtReg; ThreeBit bitNum;
    ArgsDecode::Reg5SBit3(instrn, tgtReg, bitNum);
    BLD_(env, tgtReg, bitNum);
}

void SRegOps::BLD_(Environ &env, FiveBit tgtAddr, ThreeBit bitNum) {
    uchar_t tgtValue = env.read_register(tgtAddr);
    uchar_t tBitMask = ((env.sReg.T) ? 0 : 1) << bitNum;
    uchar_t result = tgtValue | tBitMask;
    env.write_register(tgtAddr, result);
}

