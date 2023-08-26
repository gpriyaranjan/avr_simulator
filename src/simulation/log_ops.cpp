#include "log_ops.h"
#include "decoder.h"
#include "alu_ops.h"

void LogOps::AND(Environ &env, unsigned int instrn) {
    FiveBit tgtAddr, srcAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    AND_(env, tgtAddr, srcAddr);
}

void LogOps::AND_(Environ &env, FiveBit tgtAddr, FiveBit srcAddr) {
    UChar tgtVal = env.mem[tgtAddr];
    UChar srcVal = env.mem[srcAddr];

    UChar result = tgtVal & srcVal;

    env.sReg
        .setZ(is_zero(result))
        .setN(is_b7(result))
        .setV(0)
        .setS();

    env.mem[tgtAddr] = result;
}

void LogOps::ANDI(Environ &env, unsigned int instrn) {
    FourBit tgtId; EightBit immData;
    ArgsDecode::Reg4Imm8(instrn, tgtId, immData);
    FiveBit tgtAddr = tgtId + 0x10;
    ANDI_(env, tgtAddr, immData);
}

void LogOps::ANDI_(Environ &env, FiveBit tgtAddr, EightBit immData) {
    UChar tgtVal = env.mem[tgtAddr];

    UChar result = tgtVal & immData;

    env.sReg
            .setZ(is_zero(result))
            .setN(is_b7(result))
            .setV(false)
            .setS();

    env.mem[tgtAddr] = result;
}

void LogOps::OR(Environ &env, unsigned int instrn) {
    FiveBit tgtAddr, srcAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    OR_(env, tgtAddr, srcAddr);
}

void LogOps::OR_(Environ &env, FiveBit tgtAddr, FiveBit srcAddr) {
    UChar tgtVal = env.mem[tgtAddr];
    UChar srcVal = env.mem[srcAddr];

    UChar result = tgtVal | srcVal;

    env.sReg
            .setZ(is_zero(result))
            .setN(is_b7(result))
            .setV(0)
            .setS();

    env.mem[tgtAddr] = result;
}

void LogOps::ORI(Environ &env, unsigned int instrn) {
    FourBit tgtId; EightBit immData;
    ArgsDecode::Reg4Imm8(instrn, tgtId, immData);
    FiveBit tgtAddr = tgtId + 0x10;
    ORI_(env, tgtId, immData);
}

void LogOps::ORI_(Environ &env, FiveBit tgtAddr, EightBit immData) {
    UChar tgtVal = env.mem[tgtAddr];

    UChar result = tgtVal | immData;

    env.sReg
            .setZ(is_zero(result))
            .setN(is_b7(result))
            .setV(false)
            .setS();

    env.mem[tgtAddr] = result;
}

void LogOps::EOR(Environ &env, unsigned int instrn) {
    FiveBit tgtAddr, srcAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    EOR_(env, tgtAddr, srcAddr);
}

void LogOps::EOR_(Environ &env, FiveBit tgtAddr, FiveBit srcAddr) {
    UChar tgtVal = env.mem[tgtAddr];
    UChar srcVal = env.mem[srcAddr];

    UChar result = tgtVal ^ srcVal;

    env.sReg
            .setZ(is_zero(result))
            .setN(is_b7(result))
            .setV(0)
            .setS();

    env.mem[tgtAddr] = result;
}

void LogOps::COM(Environ &env, unsigned int instrn) {
    FiveBit tgtAddr;
    ArgsDecode::Reg5(instrn, tgtAddr);
    COM_(env, tgtAddr);
}

void LogOps::COM_(Environ &env, FiveBit tgtAddr) {
    UChar tgtVal = env.mem[tgtAddr];
    UChar result = ~tgtVal;

    env.sReg
            .setC(true)
            .setZ(is_zero(result))
            .setN(is_b7(result))
            .setV(0)
            .setS();

    env.mem[tgtAddr] = result;
}

void LogOps::SBR(Environ &env, unsigned int instrn) {
    ORI(env, instrn);
}

void LogOps::SBR_(Environ &env, FiveBit tgtAddr, EightBit immData) {
    ORI_(env, tgtAddr, immData);
}


void LogOps::CBR(Environ &env, unsigned int instrn) {
    ANDI(env, instrn);
}

void LogOps::CBR_(Environ &env, FiveBit tgtAddr, EightBit immData) {
    ANDI_(env, tgtAddr, immData);
}

void LogOps::SER(Environ &env, unsigned int instrn) {
    FourBit tgtId;
    ArgsDecode::Reg4(instrn, tgtId);
    FiveBit tgtAddr = tgtId + 0x10;

    SER_(env, tgtAddr);
}

void LogOps::SER_(Environ &env, FiveBit tgtAddr) {
    // UChar tgtVal = env.mem[tgtAddr];
    UChar result = 0xFF;
    env.sReg.init();
    env.mem[tgtAddr] = result;
}


void LogOps::CLR(Environ &env, unsigned int instrn) {
    EOR(env, instrn);
}

void LogOps::CLR_(Environ &env, FiveBit tgtAddr) {
    EOR_(env, tgtAddr, tgtAddr);
}

void LogOps::LSL(Environ &env, unsigned int instrn) {
    AluOps::ADD(env, instrn);
}

void LogOps::LSL_(Environ &env, FiveBit tgtAddr) {
    AluOps::ADD(env, tgtAddr, tgtAddr);
}

void LogOps::LSR(Environ &env, unsigned int instrn) {
    FiveBit tgtAddr;
    ArgsDecode::Reg5(instrn, tgtAddr);
    LSR_(env, tgtAddr);
}

void LogOps::LSR_(Environ &env, FiveBit tgtAddr) {
    UChar tgtVal = env.mem[tgtAddr];
    UChar result = tgtVal >> 1;

    env.sReg
        .setC(is_b0(tgtVal))
        .setZ(is_zero(result))
        .setN(0)
        .setV(env.sReg.N ^ env.sReg.C)
        .setS();

    env.mem[tgtAddr] = result;
}

void LogOps::ROL(Environ &env, unsigned int instrn) {
    FiveBit tgtAddr, srcAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    ROL_(env, tgtAddr);
}

void LogOps::ROL_(Environ &env, FiveBit tgtAddr) {
    AluOps::ADC(env, tgtAddr, tgtAddr);
}

void LogOps::ROR(Environ &env, unsigned int instrn) {
    FiveBit tgtAddr;
    ArgsDecode::Reg5(instrn, tgtAddr);
    ROR_(env, tgtAddr);
}

void LogOps::ROR_(Environ &env, FiveBit tgtAddr) {
    UChar tgtVal = env.mem[tgtAddr];
    bool carry = env.sReg.C;
    UChar result = (tgtVal >> 1) | (carry ? 0x80 : 0x00);

    env.sReg
        .setC(is_b0(tgtVal))
        .setZ(is_zero(result))
        .setN(is_b7(result))
        .setV(env.sReg.N ^ env.sReg.C)
        .setS();
    env.mem[tgtVal] = result;
}


