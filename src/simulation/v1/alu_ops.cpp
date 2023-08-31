#include "../types.h"
#include "../decoder.h"
#include "alu_ops.h"
#include "logic_ops.h"
#include "alu_ops_impl.h"

using namespace M;

bool AluOps::ADD(Environ& env, ShortInstrn instrn) {
    FiveBit srcAddr, tgtAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    return AluOpsImpl::ADD(env, tgtAddr, srcAddr);
}

bool AluOps::ADC(Environ& env, ShortInstrn instrn) {
    FiveBit srcAddr, tgtAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    return AluOpsImpl::ADC(env, tgtAddr, srcAddr);
}

bool AluOps::ADIW(Environ& env, ShortInstrn instrn) {
    TwoBit tgtId;
    SixBit immData;
    ArgsDecode::Reg2Imm6(instrn, tgtId, immData);
    FiveBit tgtAddr = 24 + 2 * tgtId;
    return AluOpsImpl::ADIW(env, tgtAddr, immData);
}

bool AluOps::SUB(Environ& env, ShortInstrn instrn) {
    FiveBit srcAddr, tgtAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    return AluOpsImpl::SUB(env, tgtAddr, srcAddr);
}

bool AluOps::SBC(Environ& env, ShortInstrn instrn) {
    FiveBit srcAddr, tgtAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    return AluOpsImpl::SBC(env, tgtAddr, srcAddr);
}

bool AluOps::SUBI(Environ& env, ShortInstrn instrn) {
    FourBit tgtId;
    EightBit immData;
    ArgsDecode::Reg4Imm8(instrn, tgtId, immData);
    FiveBit tgtAddr = tgtId + 0x10;
    return AluOpsImpl::SUBI(env, tgtAddr, immData);
}

bool AluOps::SBCI(Environ& env, ShortInstrn instrn) {
    FourBit tgtId;
    EightBit immData;
    ArgsDecode::Reg4Imm8(instrn, tgtId, immData);
    FiveBit tgtAddr = tgtId + 0x10;
    return AluOpsImpl::SBCI(env, tgtAddr, immData);
}

bool AluOps::SBIW(Environ& env, ShortInstrn instrn) {
    TwoBit tgtId;
    SixBit immData;
    ArgsDecode::Reg2Imm6(instrn, tgtId, immData);
    FiveBit tgtAddr = 24 + 2 * tgtId;
    return AluOpsImpl::SBIW(env, tgtAddr, immData);
}

bool AluOps::NEG(Environ& env, ShortInstrn instrn) {
    FiveBit tgtAddr;
    ArgsDecode::Reg5(instrn, tgtAddr);
    return AluOpsImpl::NEG(env, tgtAddr);
}

bool AluOps::INC(Environ& env, ShortInstrn instrn) {
    FiveBit tgtAddr;
    ArgsDecode::Reg5(instrn, tgtAddr);
    return AluOpsImpl::INC(env, tgtAddr);
}

bool AluOps::DEC(Environ& env, ShortInstrn instrn) {
    FiveBit tgtAddr;
    ArgsDecode::Reg5(instrn, tgtAddr);
    return AluOpsImpl::DEC(env, tgtAddr);
}

bool AluOps::ASR(Environ& env, ShortInstrn instrn) {
    FiveBit tgtAddr;
    ArgsDecode::Reg5(instrn, tgtAddr);
    return AluOpsImpl::ASR(env, tgtAddr);
}

bool AluOps::MUL(Environ& env, ShortInstrn instrn) {
    FiveBit srcAddr, tgtAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    return AluOpsImpl::MUL(env, tgtAddr, srcAddr);
}

bool AluOps::MULS(Environ& env, ShortInstrn instrn) {
    FiveBit srcAddr, tgtAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    return AluOpsImpl::MULS(env, tgtAddr, srcAddr);
}


bool AluOps::MULSU(Environ& env, ShortInstrn instrn) {
    FiveBit srcAddr, tgtAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    return AluOpsImpl::MULSU(env, tgtAddr, srcAddr);
}

bool AluOps::FMUL(Environ& env, ShortInstrn instrn) {
    FiveBit srcAddr, tgtAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    return AluOpsImpl::FMUL(env, tgtAddr, srcAddr);
}

bool AluOps::FMULS(Environ& env, ShortInstrn instrn) {
    FiveBit srcAddr, tgtAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    return AluOpsImpl::FMULS(env, tgtAddr, srcAddr);
}


bool AluOps::FMULSU(Environ& env, ShortInstrn instrn) {
    FiveBit srcAddr, tgtAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    return AluOpsImpl::FMULSU(env, tgtAddr, srcAddr);
}

bool AluOps::TST(Environ &env, ShortInstrn instrn) {
    FiveBit srcAddr, tgtAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    return AluOpsImpl::TST(env, tgtAddr);
}

bool AluOps::CP(Environ &env, ShortInstrn instrn) {
    FiveBit tgtAddr, srcAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    return AluOpsImpl::CP(env, tgtAddr, srcAddr);
}

bool AluOps::CPC(Environ &env, ShortInstrn instrn) {
    FiveBit tgtAddr, srcAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    return AluOpsImpl::CPC(env, tgtAddr, srcAddr);
}

bool AluOps::CPI(Environ &env, ShortInstrn instrn) {
    FourBit tgtId; EightBit immData;
    ArgsDecode::Reg4Imm8(instrn, tgtId, immData);
    FiveBit tgtAddr = tgtId + 0x100;
    return AluOpsImpl::CPI(env, tgtAddr, immData);
}


