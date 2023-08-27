#include "log_ops.h"
#include "decoder.h"
#include "alu_ops.h"

void LogOps::AND(Environ &env, uint32_t instrn) {
    FiveBit tgtAddr, srcAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    AND(env, tgtAddr, srcAddr);
}

void LogOps::AND(Environ &env, FiveBit tgtAddr, FiveBit srcAddr) {
    uchar_t tgtVal = env.read_reg_byte(tgtAddr);
    uchar_t srcVal = env.read_reg_byte(srcAddr);

    uchar_t result = tgtVal & srcVal;

    env.sReg
        .setZ(is_zero(result))
        .setN(is_b7(result))
        .setV(0)
        .setS();

    env.write_reg_byte(tgtAddr, result);
}

void LogOps::ANDI(Environ &env, uint32_t instrn) {
    FourBit tgtId; EightBit immData;
    ArgsDecode::Reg4Imm8(instrn, tgtId, immData);
    FiveBit tgtAddr = tgtId + 0x10;
    ANDI(env, tgtAddr, immData);
}

void LogOps::ANDI(Environ &env, FiveBit tgtAddr, uchar_t immData) {
    uchar_t tgtVal = env.read_reg_byte(tgtAddr);

    uchar_t result = tgtVal & immData;

    env.sReg
            .setZ(is_zero(result))
            .setN(is_b7(result))
            .setV(false)
            .setS();

    env.write_reg_byte(tgtAddr, result);
}

void LogOps::OR(Environ &env, uint32_t instrn) {
    FiveBit tgtAddr, srcAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    OR(env, tgtAddr, srcAddr);
}

void LogOps::OR(Environ &env, FiveBit tgtAddr, FiveBit srcAddr) {
    uchar_t tgtVal = env.read_reg_byte(tgtAddr);
    uchar_t srcVal = env.read_reg_byte(srcAddr);

    uchar_t result = tgtVal | srcVal;

    env.sReg
            .setZ(is_zero(result))
            .setN(is_b7(result))
            .setV(0)
            .setS();

    env.write_reg_byte(tgtAddr, result);
}

void LogOps::ORI(Environ &env, uint32_t instrn) {
    FourBit tgtId; EightBit immData;
    ArgsDecode::Reg4Imm8(instrn, tgtId, immData);
    FiveBit tgtAddr = tgtId + 0x10;
    ORI(env, tgtId, immData);
}

void LogOps::ORI(Environ &env, FiveBit tgtAddr, EightBit immData) {
    uchar_t tgtVal = env.read_reg_byte(tgtAddr);

    uchar_t result = tgtVal | immData;

    env.sReg
            .setZ(is_zero(result))
            .setN(is_b7(result))
            .setV(false)
            .setS();

    env.write_reg_byte(tgtAddr, result);
}

void LogOps::EOR(Environ &env, uint32_t instrn) {
    FiveBit tgtAddr, srcAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    EOR(env, tgtAddr, srcAddr);
}

void LogOps::EOR(Environ &env, FiveBit tgtAddr, FiveBit srcAddr) {
    uchar_t tgtVal = env.read_reg_byte(tgtAddr);
    uchar_t srcVal = env.read_reg_byte(srcAddr);

    uchar_t result = tgtVal ^ srcVal;

    env.sReg
            .setZ(is_zero(result))
            .setN(is_b7(result))
            .setV(0)
            .setS();

    env.write_reg_byte(tgtAddr, result);
}

void LogOps::COM(Environ &env, uint32_t instrn) {
    FiveBit tgtAddr;
    ArgsDecode::Reg5(instrn, tgtAddr);
    COM(env, tgtAddr);
}

void LogOps::COM(Environ &env, FiveBit tgtAddr) {
    uchar_t tgtVal = env.read_reg_byte(tgtAddr);
    uchar_t result = ~tgtVal;

    env.sReg
            .setC(true)
            .setZ(is_zero(result))
            .setN(is_b7(result))
            .setV(0)
            .setS();

    env.write_reg_byte(tgtAddr, result);
}

void LogOps::SBR(Environ &env, uint32_t instrn) {
    ORI(env, instrn);
}

void LogOps::SBR(Environ &env, FiveBit tgtAddr, EightBit immData) {
    ORI(env, tgtAddr, immData);
}


void LogOps::CBR(Environ &env, uint32_t instrn) {
    ANDI(env, instrn);
}

void LogOps::CBR(Environ &env, FiveBit tgtAddr, EightBit immData) {
    ANDI(env, tgtAddr, immData);
}

void LogOps::SER(Environ &env, uint32_t instrn) {
    FourBit tgtId;
    ArgsDecode::Reg4(instrn, tgtId);
    FiveBit tgtAddr = tgtId + 0x10;

    SER(env, tgtAddr);
}

void LogOps::SER(Environ &env, FiveBit tgtAddr) {
    // uchar_t tgtVal = env.mem[tgtAddr];
    uchar_t result = 0xFF;
    env.write_reg_byte(tgtAddr, result);
}


void LogOps::CLR(Environ &env, uint32_t instrn) {
    EOR(env, instrn);
}

void LogOps::CLR(Environ &env, FiveBit tgtAddr) {
    EOR(env, tgtAddr, tgtAddr);
}

void LogOps::LSL(Environ &env, uint32_t instrn) {
    AluOps::ADD(env, instrn);
}

void LogOps::LSL(Environ &env, FiveBit tgtAddr) {
    AluOps::ADD(env, tgtAddr, tgtAddr);
}

void LogOps::LSR(Environ &env, uint32_t instrn) {
    FiveBit tgtAddr;
    ArgsDecode::Reg5(instrn, tgtAddr);
    LSR(env, tgtAddr);
}

void LogOps::LSR(Environ &env, FiveBit tgtAddr) {
    uchar_t tgtVal = env.read_reg_byte(tgtAddr);
    uchar_t result = tgtVal >> 1;

    env.sReg
        .setC(is_b0(tgtVal))
        .setZ(is_zero(result))
        .setN(0)
        .setV(env.sReg.N() ^ env.sReg.C())
        .setS();

    env.write_reg_byte(tgtAddr, result);
}

void LogOps::ROL(Environ &env, uint32_t instrn) {
    FiveBit tgtAddr, srcAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    ROL(env, tgtAddr);
}

void LogOps::ROL(Environ &env, FiveBit tgtAddr) {
    AluOps::ADC(env, tgtAddr, tgtAddr);
}

void LogOps::ROR(Environ &env, uint32_t instrn) {
    FiveBit tgtAddr;
    ArgsDecode::Reg5(instrn, tgtAddr);
    ROR(env, tgtAddr);
}

void LogOps::ROR(Environ &env, FiveBit tgtAddr) {
    uchar_t tgtVal = env.read_reg_byte(tgtAddr);
    bool carry = env.sReg.C();
    uchar_t result = (tgtVal >> 1) | (carry ? 0x80 : 0x00);

    env.sReg
        .setC(is_b0(tgtVal))
        .setZ(is_zero(result))
        .setN(is_b7(result))
        .setV(env.sReg.N() ^ env.sReg.C())
        .setS();
    env.write_reg_byte(tgtVal, result);
}
