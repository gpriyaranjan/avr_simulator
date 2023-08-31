#include "../gen2/alu_ops.h"

#include "../infra/types.h"
#include "../infra/status_reg.h"
#include "../infra/environment.h"

#include "../gen2/alu_ops_impl.h"
#include "../gen2/logic_ops_impl.h"

class AddTwoFlags {
public:
    static bool NF(uchar_t result);
    static bool ZF(uchar_t result);
    static bool VF(uchar_t target, uchar_t source, uchar_t result);
    static bool CF(uchar_t target, uchar_t source, uchar_t result);
    static bool SF(uchar_t target, uchar_t source, uchar_t result);
    static bool HF(uchar_t target, uchar_t source, uchar_t result);

    static void statusFlags(uchar_t target, uchar_t source, uchar_t result, SReg &status);
};

class SubTwoFlags {
public:
    static bool NF(uchar_t result);
    static bool ZF(uchar_t result);
    static bool VF(uchar_t target, uchar_t source, uchar_t result);
    static bool CF(uchar_t target, uchar_t source, uchar_t result);
    static bool SF(uchar_t target, uchar_t source, uchar_t result);
    static bool HF(uchar_t target, uchar_t source, uchar_t result);

    static void statusFlags(uchar_t target, uchar_t source, uchar_t result, SReg &status);
};

void AluOpsImpl::ADD(Environ &env, FiveBit tgtAddr, FiveBit srcAddr) {
    uchar_t tgtVal = env.read_reg_byte(tgtAddr);
    uchar_t srcVal = env.read_reg_byte(srcAddr);

    uchar_t result = (srcVal + tgtVal) & 0x100;

    AddTwoFlags::statusFlags(tgtVal, srcVal, result, env.sReg);
    env.write_reg_byte(tgtAddr, result);
}

void AluOpsImpl::ADC(Environ &env, FiveBit tgtAddr, FiveBit srcAddr) {
    uchar_t tgtVal = env.read_reg_byte(tgtAddr);
    uchar_t srcVal = env.read_reg_byte(srcAddr);

    uchar_t result = (srcVal + tgtVal + 1) % 0x100;

    AddTwoFlags::statusFlags(tgtVal, srcVal, result, env.sReg);
    env.write_reg_byte(tgtAddr, result);
}

void AluOpsImpl::ADIW(Environ& env, TwoBit tgtId, SixBit immData) {

    FiveBit tgtAddr = (tgtId << 1) | 0x18;
    uchar_t tgtVal = env.read_reg_byte(tgtAddr);
    uchar_t result1 = (immData + tgtVal) & 0xFF;

    OneBit carry = AddTwoFlags::CF(tgtVal, immData, result1);
    uchar_t tgtVal2 = env.read_reg_byte(tgtAddr + 1);
    uchar_t result2 = (tgtVal2 + carry);

    env.sReg
        .setC(is_b7(result2) && is_nb7(tgtVal2))
        .setZ((result1 == 0) && (result2 == 0))
        .setN(is_b7(result2))
        .setV(is_nb7(result2) && is_b7(result2))
        .setS();

    env.write_reg_byte(tgtAddr, result1);
    env.write_reg_byte(tgtAddr + 1, result2);
}

void AluOpsImpl::SUB(Environ &env, FiveBit tgtAddr, FiveBit srcAddr) {
    uchar_t tgtVal = env.read_reg_byte(tgtAddr);
    uchar_t srcVal = env.read_reg_byte(srcAddr);

    uchar_t result = (~srcVal + tgtVal + 1) % 0x100;

    SubTwoFlags::statusFlags(tgtVal, srcVal, result, env.sReg);
    env.write_reg_byte(tgtAddr, result);
}

void AluOpsImpl::SBC(Environ &env, FiveBit tgtAddr, FiveBit srcAddr) {

    uchar_t tgtVal = env.read_reg_byte(tgtAddr);
    uchar_t srcVal = env.read_reg_byte(srcAddr);

    uchar_t result = (~srcVal + tgtVal) & 0xFF;

    SubTwoFlags::statusFlags(tgtVal, srcVal, result, env.sReg);
    env.write_reg_byte(tgtAddr, result);
}

void AluOpsImpl::SUBI(Environ& env, FourBit tgtId, EightBit immData) {
    FiveBit tgtAddr = tgtId | 0x10;
    uchar_t tgtVal = env.read_reg_byte(tgtAddr);
    uchar_t result = (~immData + tgtVal + 1) % 0x100;

    SubTwoFlags::statusFlags(tgtVal, immData, result, env.sReg);
    env.write_reg_byte(tgtAddr, result);
}

void AluOpsImpl::SBCI(Environ& env, FourBit tgtId, EightBit immData) {

    FiveBit tgtAddr = tgtId | 0x10;

    uchar_t tgtVal = env.read_reg_byte(tgtAddr);
    uchar_t result = (~immData + tgtVal) & 0xFF;

    AddTwoFlags::statusFlags(tgtVal, immData, result, env.sReg);
    env.write_reg_byte(tgtAddr, result);
}

void AluOpsImpl::SBIW(Environ& env, TwoBit tgtRegId, SixBit immData) {

    FiveBit tgtAddr = (tgtRegId << 1) | 0x18;
    uchar_t tgtVal1 = env.read_reg_byte(tgtAddr);
    uchar_t result1 = (~immData + tgtVal1 + 1) & 0xFF;

    bool carry = SubTwoFlags::CF(tgtVal1, immData, result1);
    uchar_t tgtVal2 = env.read_reg_byte(tgtAddr + 1);
    uchar_t result2 = (tgtVal2 - carry);

    env.sReg
        .setC(is_b7(result2) && is_nb7(tgtVal1))
        .setZ(is_zero(result2) && is_zero(result1))
        .setN(is_b7(result2))
        .setV(is_b7(result2) && is_nb7(tgtVal1))
        .setS();

    env.write_reg_byte(tgtAddr, result1);
    env.write_reg_byte(tgtAddr + 1, result2);
}

void AluOpsImpl::NEG(Environ& env, FiveBit tgtAddr) {
    uchar_t tgtVal = env.read_reg_byte(tgtAddr);
    uchar_t result = (~tgtVal + 1) & 0xFF;

    env.sReg
        .setC(result == 0xFF)
        .setZ(is_zero(result))
        .setN(is_b7(result))
        .setV(result == 0x80)
        .setH(is_nb3(tgtVal) && is_b3(result))
        .setS();

    env.write_reg_byte(tgtAddr, result);
}

void AluOpsImpl::INC(Environ& env, FiveBit tgtAddr) {
    uchar_t tgtVal = env.read_reg_byte(tgtAddr);
    uchar_t result = (tgtVal + 1) & 0xFF;

    env.sReg
        .setZ(is_zero(result))
        .setN(is_b7(result))
        .setV(result == 0x7F)
        .setS();

    env.write_reg_byte(tgtAddr, result);
}

void AluOpsImpl::DEC(Environ& env, FiveBit tgtAddr) {
    uchar_t tgtVal = env.read_reg_byte(tgtAddr);
    uchar_t result = (tgtVal - 1) & 0xFF;

    env.sReg
            .setZ(is_zero(result))
            .setN(is_b7(result))
            .setV(result == 0x7F)
            .setS();

    env.write_reg_byte(tgtAddr, result);
}

void AluOpsImpl::ASR(Environ& env, FiveBit tgtAddr) {
    uchar_t tgtVal = env.read_reg_byte(tgtAddr);
    uchar_t result = (tgtVal & 0x80) | (tgtVal >> 1);

    env.sReg
            .setC(is_b0(tgtVal))
            .setZ(is_zero(result))
            .setN(is_b7(result))
            .setV(result == 0x7F)
            .setS();

    env.write_reg_byte(tgtAddr, result);
}

void AluOpsImpl::MUL(Environ& env, FiveBit tgtAddr, FiveBit srcAddr) {
    uchar_t tgtVal = env.read_reg_byte(tgtAddr);
    uchar_t srcVal = env.read_reg_byte(srcAddr);

    unsigned short result = tgtVal * srcVal;

    env.write_reg_byte(M::R0, lo_byte(result));
    env.write_reg_byte(M::R1, hi_byte(result));
}

void AluOpsImpl::MULS(Environ& env, FourBit tgtRegId, FourBit srcRegId) {
    FiveBit tgtAddr = tgtRegId | 0x10;
    FiveBit srcAddr = srcRegId | 0x10;

    auto tgtVal = (schar_t) env.read_reg_byte(tgtAddr);
    auto srcVal = (schar_t) env.read_reg_byte(srcAddr);

    auto result = (short)(tgtVal * srcVal);

    env.sReg
        .setC( (result & 0x8000) == 0x8000)
        .setZ( result == 0x0000);

    env.write_reg_byte(M::R0, lo_byte(result));
    env.write_reg_byte(M::R1, hi_byte(result));
}

void AluOpsImpl::MULSU(Environ& env, ThreeBit tgtRegId, ThreeBit srcRegId) {
    FiveBit tgtAddr = tgtRegId | 0x10;
    FiveBit srcAddr = srcRegId | 0x10;

    auto tgtVal = (schar_t) env.read_reg_byte(tgtAddr);
    auto srcVal = (uchar_t) env.read_reg_byte(srcAddr);
    auto result = (short)(tgtVal * srcVal);

    env.sReg
            .setC( (result & 0x8000) == 0x8000)
            .setZ( result == 0x0000);

    env.write_reg_byte(M::R0, hi_byte(result));
    env.write_reg_byte(M::R1, lo_byte(result));
}

void AluOpsImpl::FMUL(Environ& env, ThreeBit tgtRegId, ThreeBit srcRegId) {
    FiveBit tgtAddr = tgtRegId | 0x10;
    FiveBit srcAddr = srcRegId | 0x10;

    uchar_t tgtVal = env.read_reg_byte(tgtAddr);
    uchar_t srcVal = env.read_reg_byte(srcAddr);
    unsigned short result = tgtVal * srcVal;
        result = result << 1;

    env.write_reg_byte(M::R0, lo_byte(result));
    env.write_reg_byte(M::R1, hi_byte(result));
}

void AluOpsImpl::FMULS(Environ& env, ThreeBit tgtRegId, ThreeBit srcRegId) {
    FiveBit tgtAddr = tgtRegId | 0x10;
    FiveBit srcAddr = srcRegId | 0x10;

    auto tgtVal = (schar_t) env.read_reg_byte(tgtAddr);
    auto srcVal = (schar_t) env.read_reg_byte(srcAddr);
    auto result = (unsigned short)(tgtVal * srcVal);
         result = result << 1;

    env.sReg
            .setC( (result & 0x8000) == 0x8000)
            .setZ( result == 0x0000);

    env.write_reg_byte(M::R0, lo_byte(result));
    env.write_reg_byte(M::R1, hi_byte(result));
}

void AluOpsImpl::FMULSU(Environ& env, ThreeBit tgtRegId, ThreeBit srcRegId) {
    FiveBit tgtAddr = tgtRegId | 0x10;
    FiveBit srcAddr = srcRegId | 0x10;

    auto tgtVal = (schar_t) env.read_reg_byte(tgtAddr);
    auto srcVal = (uchar_t) env.read_reg_byte(srcAddr);
    auto result = (uint16_t)(tgtVal * srcVal);
         result = result << 1;

    env.sReg
            .setC( (result & 0x8000) == 0x8000)
            .setZ( result == 0x0000);

    env.write_reg_pair(M::R0, result);
    env.write_reg_byte(M::R1, hi_byte(result));
}

void AluOpsImpl::TST(Environ &env, FiveBit tgtAddr) {
    LogicOpsImpl::AND(env, tgtAddr, tgtAddr);
}

void AluOpsImpl::CP(Environ &env, FiveBit tgtAddr, FiveBit srcAddr) {
    uchar_t tgtVal = env.read_reg_byte(tgtAddr);
    uchar_t srcVal = env.read_reg_byte(srcAddr);
    uchar_t result = (tgtVal + ~srcVal + 1) & 0xFF;
    SubTwoFlags::statusFlags(tgtVal, srcVal, result, env.sReg);
}

void AluOpsImpl::CPC(Environ &env, FiveBit tgtAddr, FiveBit srcAddr) {
    uchar_t tgtVal = env.read_reg_byte(tgtAddr);
    uchar_t srcVal = env.read_reg_byte(srcAddr);
    uchar_t carry = env.sReg.C();
    uchar_t result = (tgtVal + ~srcVal + carry) & 0xFF;
    SubTwoFlags::statusFlags(tgtVal, srcVal, result, env.sReg);
}

void AluOpsImpl::CPI(Environ &env, FourBit tgtRegId, EightBit immData) {
    FiveBit tgtAddr = tgtRegId | 0x10;
    uchar_t tgtVal = env.read_reg_byte(tgtAddr);
    uchar_t result = (tgtVal + ~immData + 1) & 0xFF;
    SubTwoFlags::statusFlags(tgtVal, immData, result, env.sReg);
}

bool AddTwoFlags::CF(uchar_t target, uchar_t source, uchar_t result) {
    return
            (is_b7(source) && is_b7(target)) ||
            (is_b7(source) && is_nb7(result)) ||
            (is_b7(target) && is_nb7(result));
}

bool AddTwoFlags::ZF(uchar_t result) {
    return is_zero(result);
}

bool AddTwoFlags::NF(uchar_t result) {
    return is_nb7(result);
}

bool AddTwoFlags::VF(uchar_t target, uchar_t source, uchar_t result) {
    return
        (is_b7(source) && is_b7(target) && is_nb7(result)) ||
        (is_nb7(source) && is_nb7(target) && is_b7(result));
}

bool AddTwoFlags::SF(uchar_t target, uchar_t source, uchar_t result) {
    return NF(result) ^ VF(target, source, result);
}

bool AddTwoFlags::HF(uchar_t target, uchar_t source, uchar_t result) {
    return (is_b3(source) && is_b3(target))  ||
           (is_b3(source) && is_nb3(result)) ||
           (is_b3(target) && is_nb3(result));
}

void AddTwoFlags::statusFlags(uchar_t target, uchar_t source, uchar_t result, SReg &status) {
    status.setN(NF(result));
    status.setZ(ZF(result));
    status.setV(VF(target, source, result));
    status.setC(CF(target, source, result));
    status.setS(SF(target, source, result));
    status.setH(HF(target, source, result));
}

bool SubTwoFlags::CF(uchar_t target, uchar_t source, uchar_t result) {
    // Rd7' • Rr7 + Rr7 • R7 + R7 • Rd7'
    return
        (is_b7(source) && is_nb7(target)) ||
        (is_b7(source) && is_b7(result)) ||
        (is_nb7(target) && is_b7(result));
}

bool SubTwoFlags::NF(uchar_t result) {
    return is_nb7(result);
}

bool SubTwoFlags::ZF(uchar_t result) {
    return is_zero(result);
}

bool SubTwoFlags::VF(uchar_t target, uchar_t source, uchar_t result) {
    // Rd7 • Rr7' • R7' + Rd7' • Rr7 • R7
    return
        (is_b7(target) && is_nb7(source) && is_nb7(result)) ||
        (is_nb7(target) && is_b7(source) && is_b7(result));
}

bool SubTwoFlags::SF(uchar_t target, uchar_t source, uchar_t result) {
    return NF(result) ^ VF(target, source, result);
}

bool SubTwoFlags::HF(uchar_t target, uchar_t source, uchar_t result) {
    return
        (is_nb3(target) && is_b3(source)) ||
        (is_b3(source) && is_b3(result)) ||
        (is_nb3(target) && is_b3(result));
}

void SubTwoFlags::statusFlags(uchar_t target, uchar_t source, uchar_t result, SReg &status) {

    status.setN(NF(result));
    status.setZ(ZF(result));
    status.setV(VF(target, source, result));
    status.setC(CF(target, source, result));
    status.setS(SF(target, source, result));
    status.setH(HF(target, source, result));
}