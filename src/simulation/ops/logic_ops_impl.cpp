#include "../gen2/logic_ops.h"
#include "../gen2/logic_ops_impl.h"
#include "../gen2/alu_ops_impl.h"
#include "../infra/environment.h"

void LogicOpsImpl::AND(Environ &env, FiveBit tgtAddr, FiveBit srcAddr) {
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

void LogicOpsImpl::ANDI(Environ &env, FourBit tgtRegId, EightBit immData) {

    FiveBit tgtAddr = tgtRegId | 0x10;
    uchar_t tgtVal = env.read_reg_byte(tgtAddr);

    uchar_t result = tgtVal & immData;

    env.sReg
            .setZ(is_zero(result))
            .setN(is_b7(result))
            .setV(false)
            .setS();

    env.write_reg_byte(tgtAddr, result);
}

void LogicOpsImpl::OR(Environ &env, FiveBit tgtAddr, FiveBit srcAddr) {
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

void LogicOpsImpl::ORI(Environ &env, FourBit tgtRegId, EightBit immData) {

    FiveBit tgtAddr = tgtRegId | 0x10;
    uchar_t tgtVal = env.read_reg_byte(tgtAddr);

    uchar_t result = tgtVal | immData;

    env.sReg
            .setZ(is_zero(result))
            .setN(is_b7(result))
            .setV(false)
            .setS();

    env.write_reg_byte(tgtAddr, result);
}

void LogicOpsImpl::EOR(Environ &env, FiveBit tgtAddr, FiveBit srcAddr) {
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

void LogicOpsImpl::COM(Environ &env, FiveBit tgtAddr) {
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

void LogicOpsImpl::SBR(Environ &env, FourBit tgtAddr, EightBit immData) {
    ORI(env, tgtAddr, immData);
}

void LogicOpsImpl::CBR(Environ &env, FourBit tgtAddr, EightBit immData) {
    ANDI(env, tgtAddr, immData);
}

void LogicOpsImpl::SER(Environ &env, FourBit tgtRegId) {
    FiveBit tgtAddr = tgtRegId | 0x10;
    uchar_t result = 0xFF;
    env.write_reg_byte(tgtAddr, result);
}

void LogicOpsImpl::CLR(Environ &env, FiveBit tgtAddr) {
    EOR(env, tgtAddr, tgtAddr);
}

void LogicOpsImpl::LSL(Environ &env, FiveBit tgtAddr) {
    AluOpsImpl::ADD(env, tgtAddr, tgtAddr);
}

void LogicOpsImpl::LSR(Environ &env, FiveBit tgtAddr) {
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

void LogicOpsImpl::ROL(Environ &env, FiveBit tgtAddr) {
    AluOpsImpl::ADC(env, tgtAddr, tgtAddr);
}

void LogicOpsImpl::ROR(Environ &env, FiveBit tgtAddr) {
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