#include "../gen1/alu_ops_impl.h"
#include "../gen1/alu_ops.h"
#include "../gen1/logic_ops.h"
#include "../gen1/io_ops_impl.h"

bool IoOpsImpl::AND(Environ &env, FiveBit tgtAddr, FiveBit srcAddr) {
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

bool IoOpsImpl::ANDI(Environ &env, FiveBit tgtAddr, uchar_t immData) {
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

bool IoOpsImpl::OR(Environ &env, FiveBit tgtAddr, FiveBit srcAddr) {
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

bool IoOpsImpl::ORI(Environ &env, FiveBit tgtAddr, EightBit immData) {
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

bool IoOpsImpl::EOR(Environ &env, FiveBit tgtAddr, FiveBit srcAddr) {
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

bool IoOpsImpl::COM(Environ &env, FiveBit tgtAddr) {
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

bool IoOpsImpl::SBR(Environ &env, FiveBit tgtAddr, EightBit immData) {
    return ORI(env, tgtAddr, immData);
}

bool IoOpsImpl::CBR(Environ &env, FiveBit tgtAddr, EightBit immData) {
    return ANDI(env, tgtAddr, immData);
}

bool IoOpsImpl::SER(Environ &env, FiveBit tgtAddr) {
    // uchar_t tgtVal = env.mem[tgtAddr];
    uchar_t result = 0xFF;
    env.write_reg_byte(tgtAddr, result);
    return false;
}

bool IoOpsImpl::CLR(Environ &env, FiveBit tgtAddr) {
    return EOR(env, tgtAddr, tgtAddr);
}

bool IoOpsImpl::LSL(Environ &env, FiveBit tgtAddr) {
    return AluOpsImpl::ADD(env, tgtAddr, tgtAddr);
}

bool IoOpsImpl::LSR(Environ &env, FiveBit tgtAddr) {
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

bool IoOpsImpl::ROL(Environ &env, FiveBit tgtAddr) {
    return AluOpsImpl::ADC(env, tgtAddr, tgtAddr);
}

bool IoOpsImpl::ROR(Environ &env, FiveBit tgtAddr) {
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