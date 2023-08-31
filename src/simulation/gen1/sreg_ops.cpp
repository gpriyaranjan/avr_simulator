#include "../infra/decoder.h"
#include "sreg_ops.h"
#include "sreg_ops_impl.h"

bool SRegOps::BSET(Environ &env, ShortInstrn instrn) {
    ThreeBit regNum;
    ArgsDecode::SBit3(instrn, regNum);
    return SRegOpsImpl::BSET(env, regNum, true);
}

bool SRegOps::BCLR(Environ &env, ShortInstrn instrn) {
    ThreeBit regNum;
    ArgsDecode::SBit3(instrn, regNum);
    return SRegOpsImpl::BCLR(env, regNum, true);
}

bool SRegOps::SEC(Environ &env, ShortInstrn instrn) {
    return SRegOpsImpl::SEC(env);
}

bool SRegOps::CLC(Environ &env, ShortInstrn instrn) {
    return SRegOpsImpl::CLC(env);
}

bool SRegOps::SEZ(Environ &env, ShortInstrn instrn) {
    return SRegOpsImpl::SEZ(env);
}

bool SRegOps::CLZ(Environ &env, ShortInstrn instrn) {
    return SRegOpsImpl::CLZ(env);
}

bool SRegOps::SEN(Environ &env, ShortInstrn instrn) {
    return SRegOpsImpl::SEN(env);
}

bool SRegOps::CLN(Environ &env, ShortInstrn instrn) {
    return SRegOpsImpl::CLN(env);
}

bool SRegOps::SEV(Environ &env, ShortInstrn instrn) {
    return SRegOpsImpl::SEV(env);
}

bool SRegOps::CLV(Environ &env, ShortInstrn instrn) {
    return SRegOpsImpl::CLV(env);
}

bool SRegOps::SES(Environ &env, ShortInstrn instrn) {
    return SRegOpsImpl::SES(env);
}

bool SRegOps::CLS(Environ &env, ShortInstrn instrn) {
    return SRegOpsImpl::CLS(env);
}

bool SRegOps::SEH(Environ &env, ShortInstrn instrn) {
    return SRegOpsImpl::SEH(env);
}

bool SRegOps::CLH(Environ &env, ShortInstrn instrn) {
    return SRegOpsImpl::CLH(env);
}

bool SRegOps::SET(Environ &env, ShortInstrn instrn) {
    return SRegOpsImpl::SET(env);
}

bool SRegOps::CLT(Environ &env, ShortInstrn instrn) {
    return SRegOpsImpl::CLT(env);
}

bool SRegOps::BST(Environ &env, ShortInstrn instrn) {
    FiveBit tgtReg; ThreeBit bitNum;
    ArgsDecode::Reg5SBit3(instrn, tgtReg, bitNum);
    return SRegOpsImpl::BST(env, tgtReg, bitNum);
}

bool SRegOps::BLD(Environ &env, ShortInstrn instrn) {
    FiveBit tgtReg; ThreeBit bitNum;
    ArgsDecode::Reg5SBit3(instrn, tgtReg, bitNum);
    return SRegOpsImpl::BLD(env, tgtReg, bitNum);
}

