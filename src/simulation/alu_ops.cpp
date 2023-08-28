#include "types.h"
#include "decoder.h"
#include "alu_ops.h"
#include "log_ops.h"
#include "alu_ops_mc.h"

using namespace M;

bool AluOps::ADD(Environ& env, ShortInstrn instrn) {
    FiveBit srcAddr, tgtAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    return AluOpsMc::ADD(env, tgtAddr, srcAddr);
}

bool AluOps::ADC(Environ& env, ShortInstrn instrn) {
    FiveBit srcAddr, tgtAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    return AluOpsMc::ADC(env, tgtAddr, srcAddr);
}

bool AluOps::ADIW(Environ& env, ShortInstrn instrn) {
    TwoBit tgtId;
    SixBit immData;
    ArgsDecode::Reg2Imm6(instrn, tgtId, immData);
    FiveBit tgtAddr = 24 + 2 * tgtId;
    return AluOpsMc::ADIW(env, tgtAddr, immData);
}

bool AluOps::SUB(Environ& env, ShortInstrn instrn) {
    FiveBit srcAddr, tgtAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    return AluOpsMc::SUB(env, tgtAddr, srcAddr);
}

bool AluOps::SBC(Environ& env, ShortInstrn instrn) {
    FiveBit srcAddr, tgtAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    return AluOpsMc::SBC(env, tgtAddr, srcAddr);
}

bool AluOps::SUBI(Environ& env, ShortInstrn instrn) {
    FourBit tgtId;
    EightBit immData;
    ArgsDecode::Reg4Imm8(instrn, tgtId, immData);
    FiveBit tgtAddr = tgtId + 0x10;
    return AluOpsMc::SUBI(env, tgtAddr, immData);
}

bool AluOps::SBCI(Environ& env, ShortInstrn instrn) {
    FourBit tgtId;
    EightBit immData;
    ArgsDecode::Reg4Imm8(instrn, tgtId, immData);
    FiveBit tgtAddr = tgtId + 0x10;
    return AluOpsMc::SBCI(env, tgtAddr, immData);
}

bool AluOps::SBIW(Environ& env, ShortInstrn instrn) {
    TwoBit tgtId;
    SixBit immData;
    ArgsDecode::Reg2Imm6(instrn, tgtId, immData);
    FiveBit tgtAddr = 24 + 2 * tgtId;
    return AluOpsMc::SBIW(env, tgtAddr, immData);
}

bool AluOps::NEG(Environ& env, ShortInstrn instrn) {
    FiveBit tgtAddr;
    ArgsDecode::Reg5(instrn, tgtAddr);
    return AluOpsMc::NEG(env, tgtAddr);
}

bool AluOps::INC(Environ& env, ShortInstrn instrn) {
    FiveBit tgtAddr;
    ArgsDecode::Reg5(instrn, tgtAddr);
    return AluOpsMc::INC(env, tgtAddr);
}

bool AluOps::DEC(Environ& env, ShortInstrn instrn) {
    FiveBit tgtAddr;
    ArgsDecode::Reg5(instrn, tgtAddr);
    return AluOpsMc::DEC(env, tgtAddr);
}

bool AluOps::ASR(Environ& env, ShortInstrn instrn) {
    FiveBit tgtAddr;
    ArgsDecode::Reg5(instrn, tgtAddr);
    return AluOpsMc::ASR(env, tgtAddr);
}

bool AluOps::MUL(Environ& env, ShortInstrn instrn) {
    FiveBit srcAddr, tgtAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    return AluOpsMc::MUL(env, tgtAddr, srcAddr);
}

bool AluOps::MULS(Environ& env, ShortInstrn instrn) {
    FiveBit srcAddr, tgtAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    return AluOpsMc::MULS(env, tgtAddr, srcAddr);
}


bool AluOps::MULSU(Environ& env, ShortInstrn instrn) {
    FiveBit srcAddr, tgtAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    return AluOpsMc::MULSU(env, tgtAddr, srcAddr);
}

bool AluOps::FMUL(Environ& env, ShortInstrn instrn) {
    FiveBit srcAddr, tgtAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    return AluOpsMc::FMUL(env, tgtAddr, srcAddr);
}

bool AluOps::FMULS(Environ& env, ShortInstrn instrn) {
    FiveBit srcAddr, tgtAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    return AluOpsMc::FMULS(env, tgtAddr, srcAddr);
}


bool AluOps::FMULSU(Environ& env, ShortInstrn instrn) {
    FiveBit srcAddr, tgtAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    return AluOpsMc::FMULSU(env, tgtAddr, srcAddr);
}

bool AluOps::TST(Environ &env, ShortInstrn instrn) {
    FiveBit srcAddr, tgtAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    return AluOpsMc::TST(env, tgtAddr);
}

bool AluOps::CP(Environ &env, ShortInstrn instrn) {
    FiveBit tgtAddr, srcAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    return AluOpsMc::CP(env, tgtAddr, srcAddr);
}

bool AluOps::CPC(Environ &env, ShortInstrn instrn) {
    FiveBit tgtAddr, srcAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    return AluOpsMc::CPC(env, tgtAddr, srcAddr);
}

bool AluOps::CPI(Environ &env, ShortInstrn instrn) {
    FourBit tgtId; EightBit immData;
    ArgsDecode::Reg4Imm8(instrn, tgtId, immData);
    FiveBit tgtAddr = tgtId + 0x100;
    return AluOpsMc::CPI(env, tgtAddr, immData);
}


