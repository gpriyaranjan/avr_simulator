//
// Created by MAC BOOK on 28/08/23.
//

#include "alu_ops_mc.h"
#include "alu_ops.h"
#include "decoder.h"
#include "log_ops.h"
#include "io_ops_mc.h"

bool IoOpsMc::AND(Environ &env, FiveBit tgtAddr, FiveBit srcAddr) {
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

bool IoOpsMc::ANDI(Environ &env, FiveBit tgtAddr, uchar_t immData) {
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

bool IoOpsMc::OR(Environ &env, FiveBit tgtAddr, FiveBit srcAddr) {
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

bool IoOpsMc::ORI(Environ &env, FiveBit tgtAddr, EightBit immData) {
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

bool IoOpsMc::EOR(Environ &env, FiveBit tgtAddr, FiveBit srcAddr) {
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

bool IoOpsMc::COM(Environ &env, FiveBit tgtAddr) {
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

bool IoOpsMc::SBR(Environ &env, FiveBit tgtAddr, EightBit immData) {
    return ORI(env, tgtAddr, immData);
}

bool IoOpsMc::CBR(Environ &env, FiveBit tgtAddr, EightBit immData) {
    return ANDI(env, tgtAddr, immData);
}

bool IoOpsMc::SER(Environ &env, FiveBit tgtAddr) {
    // uchar_t tgtVal = env.mem[tgtAddr];
    uchar_t result = 0xFF;
    env.write_reg_byte(tgtAddr, result);
    return false;
}

bool IoOpsMc::CLR(Environ &env, FiveBit tgtAddr) {
    return EOR(env, tgtAddr, tgtAddr);
}

bool IoOpsMc::LSL(Environ &env, FiveBit tgtAddr) {
    return AluOpsMc::ADD(env, tgtAddr, tgtAddr);
}

bool IoOpsMc::LSR(Environ &env, FiveBit tgtAddr) {
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

bool IoOpsMc::ROL(Environ &env, FiveBit tgtAddr) {
    return AluOpsMc::ADC(env, tgtAddr, tgtAddr);
}

bool IoOpsMc::ROR(Environ &env, FiveBit tgtAddr) {
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