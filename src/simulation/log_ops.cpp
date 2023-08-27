#include "log_ops.h"
#include "decoder.h"
#include "alu_ops.h"

bool LogOps::AND(Environ &env, uint32_t instrn) {
    FiveBit tgtAddr, srcAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    return AND(env, tgtAddr, srcAddr);
}

bool LogOps::AND(Environ &env, FiveBit tgtAddr, FiveBit srcAddr) {
    uchar_t tgtVal = env.read_reg_byte(tgtAddr);
    uchar_t srcVal = env.read_reg_byte(srcAddr);

    uchar_t result = tgtVal & srcVal;

    env.sReg
        .setZ(is_zero(result))
        .setN(is_b7(result))
        .setV(0)
        .setS();

    env.write_reg_byte(tgtAddr, result);
    return false;
}

bool LogOps::ANDI(Environ &env, uint32_t instrn) {
    FourBit tgtId; EightBit immData;
    ArgsDecode::Reg4Imm8(instrn, tgtId, immData);
    FiveBit tgtAddr = tgtId + 0x10;
    return ANDI(env, tgtAddr, immData);
}

bool LogOps::ANDI(Environ &env, FiveBit tgtAddr, uchar_t immData) {
    uchar_t tgtVal = env.read_reg_byte(tgtAddr);

    uchar_t result = tgtVal & immData;

    env.sReg
            .setZ(is_zero(result))
            .setN(is_b7(result))
            .setV(false)
            .setS();

    env.write_reg_byte(tgtAddr, result);
    return false;
}

bool LogOps::OR(Environ &env, uint32_t instrn) {
    FiveBit tgtAddr, srcAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    return OR(env, tgtAddr, srcAddr);
}

bool LogOps::OR(Environ &env, FiveBit tgtAddr, FiveBit srcAddr) {
    uchar_t tgtVal = env.read_reg_byte(tgtAddr);
    uchar_t srcVal = env.read_reg_byte(srcAddr);

    uchar_t result = tgtVal | srcVal;

    env.sReg
            .setZ(is_zero(result))
            .setN(is_b7(result))
            .setV(0)
            .setS();

    env.write_reg_byte(tgtAddr, result);
    return false;
}

bool LogOps::ORI(Environ &env, uint32_t instrn) {
    FourBit tgtId; EightBit immData;
    ArgsDecode::Reg4Imm8(instrn, tgtId, immData);
    FiveBit tgtAddr = tgtId + 0x10;
    return ORI(env, tgtId, immData);
}

bool LogOps::ORI(Environ &env, FiveBit tgtAddr, EightBit immData) {
    uchar_t tgtVal = env.read_reg_byte(tgtAddr);

    uchar_t result = tgtVal | immData;

    env.sReg
            .setZ(is_zero(result))
            .setN(is_b7(result))
            .setV(false)
            .setS();

    env.write_reg_byte(tgtAddr, result);
    return false;
}

bool LogOps::EOR(Environ &env, uint32_t instrn) {
    FiveBit tgtAddr, srcAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    return EOR(env, tgtAddr, srcAddr);
}

bool LogOps::EOR(Environ &env, FiveBit tgtAddr, FiveBit srcAddr) {
    uchar_t tgtVal = env.read_reg_byte(tgtAddr);
    uchar_t srcVal = env.read_reg_byte(srcAddr);

    uchar_t result = tgtVal ^ srcVal;

    env.sReg
            .setZ(is_zero(result))
            .setN(is_b7(result))
            .setV(0)
            .setS();

    env.write_reg_byte(tgtAddr, result);
    return false;
}

bool LogOps::COM(Environ &env, uint32_t instrn) {
    FiveBit tgtAddr;
    ArgsDecode::Reg5(instrn, tgtAddr);
    return COM(env, tgtAddr);
}

bool LogOps::COM(Environ &env, FiveBit tgtAddr) {
    uchar_t tgtVal = env.read_reg_byte(tgtAddr);
    uchar_t result = ~tgtVal;

    env.sReg
            .setC(true)
            .setZ(is_zero(result))
            .setN(is_b7(result))
            .setV(0)
            .setS();

    env.write_reg_byte(tgtAddr, result);
    return false;
}

bool LogOps::SBR(Environ &env, uint32_t instrn) {
    return ORI(env, instrn);
}

bool LogOps::SBR(Environ &env, FiveBit tgtAddr, EightBit immData) {
    return ORI(env, tgtAddr, immData);
}


bool LogOps::CBR(Environ &env, uint32_t instrn) {
    return ANDI(env, instrn);
}

bool LogOps::CBR(Environ &env, FiveBit tgtAddr, EightBit immData) {
    return ANDI(env, tgtAddr, immData);
}

bool LogOps::SER(Environ &env, uint32_t instrn) {
    FourBit tgtId;
    ArgsDecode::Reg4(instrn, tgtId);
    FiveBit tgtAddr = tgtId + 0x10;

    return SER(env, tgtAddr);
}

bool LogOps::SER(Environ &env, FiveBit tgtAddr) {
    // uchar_t tgtVal = env.mem[tgtAddr];
    uchar_t result = 0xFF;
    env.write_reg_byte(tgtAddr, result);
    return false;
}


bool LogOps::CLR(Environ &env, uint32_t instrn) {
    return EOR(env, instrn);
}

bool LogOps::CLR(Environ &env, FiveBit tgtAddr) {
    return EOR(env, tgtAddr, tgtAddr);
}

bool LogOps::LSL(Environ &env, uint32_t instrn) {
    return AluOps::ADD(env, instrn);
}

bool LogOps::LSL(Environ &env, FiveBit tgtAddr) {
    return AluOps::ADD(env, tgtAddr, tgtAddr);
}

bool LogOps::LSR(Environ &env, uint32_t instrn) {
    FiveBit tgtAddr;
    ArgsDecode::Reg5(instrn, tgtAddr);
    return LSR(env, tgtAddr);
}

bool LogOps::LSR(Environ &env, FiveBit tgtAddr) {
    uchar_t tgtVal = env.read_reg_byte(tgtAddr);
    uchar_t result = tgtVal >> 1;

    env.sReg
        .setC(is_b0(tgtVal))
        .setZ(is_zero(result))
        .setN(0)
        .setV(env.sReg.N() ^ env.sReg.C())
        .setS();

    env.write_reg_byte(tgtAddr, result);
    return false;
}

bool LogOps::ROL(Environ &env, uint32_t instrn) {
    FiveBit tgtAddr, srcAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    return ROL(env, tgtAddr);
}

bool LogOps::ROL(Environ &env, FiveBit tgtAddr) {
    return AluOps::ADC(env, tgtAddr, tgtAddr);
}

bool LogOps::ROR(Environ &env, uint32_t instrn) {
    FiveBit tgtAddr;
    ArgsDecode::Reg5(instrn, tgtAddr);
    return ROR(env, tgtAddr);
}

bool LogOps::ROR(Environ &env, FiveBit tgtAddr) {
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
    return false;
}
