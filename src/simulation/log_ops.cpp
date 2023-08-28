#include "log_ops.h"
#include "decoder.h"
#include "alu_ops.h"
#include "log_ops_mc.h"

bool LogOps::AND(Environ &env, ShortInstrn instrn) {
    FiveBit tgtAddr, srcAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    return LogOpsMc::AND(env, tgtAddr, srcAddr);
}

bool LogOps::ANDI(Environ &env, ShortInstrn instrn) {
    FourBit tgtId; EightBit immData;
    ArgsDecode::Reg4Imm8(instrn, tgtId, immData);
    FiveBit tgtAddr = tgtId + 0x10;
    return LogOpsMc::ANDI(env, tgtAddr, immData);
}

bool LogOps::OR(Environ &env, ShortInstrn instrn) {
    FiveBit tgtAddr, srcAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    return LogOpsMc::OR(env, tgtAddr, srcAddr);
}

bool LogOps::ORI(Environ &env, ShortInstrn instrn) {
    FourBit tgtId; EightBit immData;
    ArgsDecode::Reg4Imm8(instrn, tgtId, immData);
    FiveBit tgtAddr = tgtId + 0x10;
    return LogOpsMc::ORI(env, tgtAddr, immData);
}

bool LogOps::EOR(Environ &env, ShortInstrn instrn) {
    FiveBit tgtAddr, srcAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    return LogOpsMc::EOR(env, tgtAddr, srcAddr);
}

bool LogOps::COM(Environ &env, ShortInstrn instrn) {
    FiveBit tgtAddr;
    ArgsDecode::Reg5(instrn, tgtAddr);
    return LogOpsMc::COM(env, tgtAddr);
}

bool LogOps::SBR(Environ &env, ShortInstrn instrn) {
    return ORI(env, instrn);
}


bool LogOps::CBR(Environ &env, ShortInstrn instrn) {
    return ANDI(env, instrn);
}

bool LogOps::SER(Environ &env, ShortInstrn instrn) {
    FourBit tgtId;
    ArgsDecode::Reg4(instrn, tgtId);
    FiveBit tgtAddr = tgtId + 0x10;

    return LogOpsMc::SER(env, tgtAddr);
}


bool LogOps::CLR(Environ &env, ShortInstrn instrn) {
    return EOR(env, instrn);
}

bool LogOps::LSL(Environ &env, ShortInstrn instrn) {
    return AluOps::ADD(env, instrn);
}

bool LogOps::LSR(Environ &env, ShortInstrn instrn) {
    FiveBit tgtAddr;
    ArgsDecode::Reg5(instrn, tgtAddr);
    return LogOpsMc::LSR(env, tgtAddr);
}

bool LogOps::ROL(Environ &env, ShortInstrn instrn) {
    FiveBit tgtAddr, srcAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    return LogOpsMc::ROL(env, tgtAddr);
}

bool LogOps::ROR(Environ &env, ShortInstrn instrn) {
    FiveBit tgtAddr;
    ArgsDecode::Reg5(instrn, tgtAddr);
    return LogOpsMc::ROR(env, tgtAddr);
}

