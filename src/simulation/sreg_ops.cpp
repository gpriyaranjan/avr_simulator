#include "decoder.h"
#include "sreg_ops.h"
#include "sreg_ops_mc.h"

bool SRegOps::BSET(Environ &env, ShortInstrn instrn) {
    ThreeBit regNum;
    ArgsDecode::SBit3(instrn, regNum);
    return SRegOpsMc::BSET(env, regNum, true);
}

bool SRegOps::BCLR(Environ &env, ShortInstrn instrn) {
    ThreeBit regNum;
    ArgsDecode::SBit3(instrn, regNum);
    return SRegOpsMc::BCLR(env, regNum, true);
}

bool SRegOps::SEC(Environ &env, ShortInstrn instrn) {
    return SRegOpsMc::SEC(env);
}

bool SRegOps::CLC(Environ &env, ShortInstrn instrn) {
    return SRegOpsMc::CLC(env);
}

bool SRegOps::SEZ(Environ &env, ShortInstrn instrn) {
    return SRegOpsMc::SEZ(env);
}

bool SRegOps::CLZ(Environ &env, ShortInstrn instrn) {
    return SRegOpsMc::CLZ(env);
}

bool SRegOps::SEN(Environ &env, ShortInstrn instrn) {
    return SRegOpsMc::SEN(env);
}

bool SRegOps::CLN(Environ &env, ShortInstrn instrn) {
    return SRegOpsMc::CLN(env);
}

bool SRegOps::SEV(Environ &env, ShortInstrn instrn) {
    return SRegOpsMc::SEV(env);
}

bool SRegOps::CLV(Environ &env, ShortInstrn instrn) {
    return SRegOpsMc::CLV(env);
}

bool SRegOps::SES(Environ &env, ShortInstrn instrn) {
    return SRegOpsMc::SES(env);
}

bool SRegOps::CLS(Environ &env, ShortInstrn instrn) {
    return SRegOpsMc::CLS(env);
}

bool SRegOps::SEH(Environ &env, ShortInstrn instrn) {
    return SRegOpsMc::SEH(env);
}

bool SRegOps::CLH(Environ &env, ShortInstrn instrn) {
    return SRegOpsMc::CLH(env);
}

bool SRegOps::SET(Environ &env, ShortInstrn instrn) {
    return SRegOpsMc::SET(env);
}

bool SRegOps::CLT(Environ &env, ShortInstrn instrn) {
    return SRegOpsMc::CLT(env);
}

bool SRegOps::BST(Environ &env, ShortInstrn instrn) {
    FiveBit tgtReg; ThreeBit bitNum;
    ArgsDecode::Reg5SBit3(instrn, tgtReg, bitNum);
    return SRegOpsMc::BST(env, tgtReg, bitNum);
}

bool SRegOps::BLD(Environ &env, ShortInstrn instrn) {
    FiveBit tgtReg; ThreeBit bitNum;
    ArgsDecode::Reg5SBit3(instrn, tgtReg, bitNum);
    return SRegOpsMc::BLD(env, tgtReg, bitNum);
}

