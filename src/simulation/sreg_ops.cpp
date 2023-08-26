#include "decoder.h"
#include "sreg_ops.h"

void SRegOps::WriteBit(Environ &env, ThreeBit regNum, bool value) {

    UChar regBit = 1 << regNum;

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

void SRegOps::BSET(Environ &env, unsigned int instrn) {
    ThreeBit regNum;
    ArgsDecode::SBit3(instrn, regNum);
    BSET_(env, regNum);
}

void SRegOps::BSET_(Environ &env, ThreeBit regNum) {
    WriteBit(env, regNum, true);
}

void SRegOps::BCLR(Environ &env, unsigned int instrn) {
    ThreeBit regNum;
    ArgsDecode::SBit3(instrn, regNum);
    BCLR_(env, regNum);
}

void SRegOps::BCLR_(Environ &env, ThreeBit regNum) {
    WriteBit(env, regNum, false);
}

void SRegOps::SEC(Environ &env, unsigned int instrn) {
    SEC_(env);
}

void SRegOps::SEC_(Environ &env) {
    BSET_(env, CBit);
}

void SRegOps::CLC(Environ &env, unsigned int instrn) {
    CLC_(env);
}

void SRegOps::CLC_(Environ &env) {
    BCLR_(env, CBit);
}

void SRegOps::SEZ(Environ &env, unsigned int instrn) {
    SEZ_(env);
}

void SRegOps::SEZ_(Environ &env) {
    BSET_(env, ZBit);
}

void SRegOps::CLZ(Environ &env, unsigned int instrn) {
    CLZ_(env);
}

void SRegOps::CLZ_(Environ &env) {
    BCLR_(env, ZBit);
}

void SRegOps::SEN(Environ &env, unsigned int instrn) {
    SEN_(env);
}

void SRegOps::SEN_(Environ &env) {
    BSET_(env, NBit);
}

void SRegOps::CLN(Environ &env, unsigned int instrn) {
    CLN_(env);
}

void SRegOps::CLN_(Environ &env) {
    BCLR_(env, NBit);
}

void SRegOps::SEV(Environ &env, unsigned int instrn) {
    SEV_(env);
}

void SRegOps::SEV_(Environ &env) {
    BSET_(env, VBit);
}

void SRegOps::CLV(Environ &env, unsigned int instrn) {
    CLV_(env);
}

void SRegOps::CLV_(Environ &env) {
    BCLR_(env, VBit);
}

void SRegOps::SES(Environ &env, unsigned int instrn) {
    SES_(env);
}

void SRegOps::SES_(Environ &env) {
    BSET_(env, SBit);
}

void SRegOps::CLS(Environ &env, unsigned int instrn) {
    CLS_(env);
}

void SRegOps::CLS_(Environ &env) {
    BCLR_(env, SBit);
}

void SRegOps::SEH(Environ &env, unsigned int instrn) {
    SEH_(env);
}

void SRegOps::SEH_(Environ &env) {
    BSET_(env, HBit);
}

void SRegOps::CLH(Environ &env, unsigned int instrn) {
    CLH_(env);
}

void SRegOps::CLH_(Environ &env) {
    BCLR_(env, HBit);
}

void SRegOps::SET(Environ &env, unsigned int instrn) {
    SET_(env);
}

void SRegOps::SET_(Environ &env) {
    BSET_(env, SBit);
}

void SRegOps::CLT(Environ &env, unsigned int instrn) {
    CLT_(env);
}

void SRegOps::CLT_(Environ &env) {
    BCLR_(env, TBit);
}

void SRegOps::BST(Environ &env, unsigned int instrn) {
    FiveBit tgtReg; ThreeBit bitNum;
    ArgsDecode::Reg5SBit3(instrn, tgtReg, bitNum);
    BST_(env, tgtReg, bitNum);
}

void SRegOps::BST_(Environ &env, FiveBit tgtAddr, ThreeBit bitNum) {
    UChar tgtValue = env.mem[tgtAddr];
    bool tBit = is_bi(tgtValue, bitNum);
    env.sReg.T = tBit;
}

void SRegOps::BLD(Environ &env, unsigned int instrn) {
    FiveBit tgtReg; ThreeBit bitNum;
    ArgsDecode::Reg5SBit3(instrn, tgtReg, bitNum);
    BLD_(env, tgtReg, bitNum);
}

void SRegOps::BLD_(Environ &env, FiveBit tgtAddr, ThreeBit bitNum) {
    UChar tgtValue = env.mem[tgtAddr];
    UChar tBitMask = ((env.sReg.T) ? 0 : 1) << bitNum;
    UChar result = tgtValue | tBitMask;
    env.mem[tgtAddr] = result;
}

