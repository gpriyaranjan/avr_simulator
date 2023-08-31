#include "logic_ops.h"
#include "../infra/decoder.h"
#include "alu_ops.h"
#include "logic_ops_impl.h"

bool LogicOps::AND(Environ &env, ShortInstrn instrn) {
    FiveBit tgtAddr, srcAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    return LogicOpsImpl::AND(env, tgtAddr, srcAddr);
}

bool LogicOps::ANDI(Environ &env, ShortInstrn instrn) {
    FourBit tgtId; EightBit immData;
    ArgsDecode::Reg4Imm8(instrn, tgtId, immData);
    FiveBit tgtAddr = tgtId + 0x10;
    return LogicOpsImpl::ANDI(env, tgtAddr, immData);
}

bool LogicOps::OR(Environ &env, ShortInstrn instrn) {
    FiveBit tgtAddr, srcAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    return LogicOpsImpl::OR(env, tgtAddr, srcAddr);
}

bool LogicOps::ORI(Environ &env, ShortInstrn instrn) {
    FourBit tgtId; EightBit immData;
    ArgsDecode::Reg4Imm8(instrn, tgtId, immData);
    FiveBit tgtAddr = tgtId + 0x10;
    return LogicOpsImpl::ORI(env, tgtAddr, immData);
}

bool LogicOps::EOR(Environ &env, ShortInstrn instrn) {
    FiveBit tgtAddr, srcAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    return LogicOpsImpl::EOR(env, tgtAddr, srcAddr);
}

bool LogicOps::COM(Environ &env, ShortInstrn instrn) {
    FiveBit tgtAddr;
    ArgsDecode::Reg5(instrn, tgtAddr);
    return LogicOpsImpl::COM(env, tgtAddr);
}

bool LogicOps::SBR(Environ &env, ShortInstrn instrn) {
    return ORI(env, instrn);
}


bool LogicOps::CBR(Environ &env, ShortInstrn instrn) {
    return ANDI(env, instrn);
}

bool LogicOps::SER(Environ &env, ShortInstrn instrn) {
    FourBit tgtId;
    ArgsDecode::Reg4(instrn, tgtId);
    FiveBit tgtAddr = tgtId + 0x10;

    return LogicOpsImpl::SER(env, tgtAddr);
}


bool LogicOps::CLR(Environ &env, ShortInstrn instrn) {
    return EOR(env, instrn);
}

bool LogicOps::LSL(Environ &env, ShortInstrn instrn) {
    return AluOps::ADD(env, instrn);
}

bool LogicOps::LSR(Environ &env, ShortInstrn instrn) {
    FiveBit tgtAddr;
    ArgsDecode::Reg5(instrn, tgtAddr);
    return LogicOpsImpl::LSR(env, tgtAddr);
}

bool LogicOps::ROL(Environ &env, ShortInstrn instrn) {
    FiveBit tgtAddr, srcAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    return LogicOpsImpl::ROL(env, tgtAddr);
}

bool LogicOps::ROR(Environ &env, ShortInstrn instrn) {
    FiveBit tgtAddr;
    ArgsDecode::Reg5(instrn, tgtAddr);
    return LogicOpsImpl::ROR(env, tgtAddr);
}

