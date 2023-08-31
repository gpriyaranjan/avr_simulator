#include "../gen1/logic_ops.h"
#include "../gen1/alu_ops.h"
#include "../decoder.h"
#include "../types.h"
#include "../gen1/alu_ops_impl.h"
#include "../gen1/io_ops_impl.h"

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

bool AluOpsImpl::ADD(Environ &env, FiveBit tgtAddr, FiveBit srcAddr) {
    uchar_t tgtVal = env.read_reg_byte(tgtAddr);
    uchar_t srcVal = env.read_reg_byte(srcAddr);

    uchar_t result = (srcVal + tgtVal) & 0x100;

    AddTwoFlags::statusFlags(tgtVal, srcVal, result, env.sReg);
    env.write_reg_byte(tgtAddr, result);
    return false;
}

bool AluOpsImpl::ADC(Environ &env, FiveBit tgtAddr, FiveBit srcAddr) {
    uchar_t tgtVal = env.read_reg_byte(tgtAddr);
    uchar_t srcVal = env.read_reg_byte(srcAddr);

    uchar_t result = (srcVal + tgtVal + 1) % 0x100;

    AddTwoFlags::statusFlags(tgtVal, srcVal, result, env.sReg);
    env.write_reg_byte(tgtAddr, result);
    return false;
}

bool AluOpsImpl::ADIW(Environ& env, FiveBit tgtAddr, SixBit immData) {

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

    return false;
}

bool AluOpsImpl::SUB(Environ &env, FiveBit tgtAddr, FiveBit srcAddr) {
    uchar_t tgtVal = env.read_reg_byte(tgtAddr);
    uchar_t srcVal = env.read_reg_byte(srcAddr);

    uchar_t result = (~srcVal + tgtVal + 1) % 0x100;

    SubTwoFlags::statusFlags(tgtVal, srcVal, result, env.sReg);
    env.write_reg_byte(tgtAddr, result);
    return false;
}

bool AluOpsImpl::SBC(Environ &env, FiveBit tgtAddr, FiveBit srcAddr) {

    uchar_t tgtVal = env.read_reg_byte(tgtAddr);
    uchar_t srcVal = env.read_reg_byte(srcAddr);

    uchar_t result = (~srcVal + tgtVal) & 0xFF;

    SubTwoFlags::statusFlags(tgtVal, srcVal, result, env.sReg);
    env.write_reg_byte(tgtAddr, result);
    return false;
}

bool AluOpsImpl::SUBI(Environ& env, FiveBit tgtAddr, EightBit immData) {
    uchar_t tgtVal = env.read_reg_byte(tgtAddr);
    uchar_t result = (~immData + tgtVal + 1) % 0x100;

    SubTwoFlags::statusFlags(tgtVal, immData, result, env.sReg);
    env.write_reg_byte(tgtAddr, result);
    return false;
}

bool AluOpsImpl::SBCI(Environ& env, FiveBit tgtAddr, EightBit immData) {
    uchar_t tgtVal = env.read_reg_byte(tgtAddr);
    uchar_t result = (~immData + tgtVal) & 0xFF;

    AddTwoFlags::statusFlags(tgtVal, immData, result, env.sReg);
    env.write_reg_byte(tgtAddr, result);
    return false;
}

bool AluOpsImpl::SBIW(Environ& env, FiveBit tgtAddr, SixBit immData) {
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
    return false;
}

bool AluOpsImpl::NEG(Environ& env, FiveBit tgtAddr) {
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
    return false;
}

bool AluOpsImpl::INC(Environ& env, FiveBit tgtAddr) {
    uchar_t tgtVal = env.read_reg_byte(tgtAddr);
    uchar_t result = (tgtVal + 1) & 0xFF;

    env.sReg
        .setZ(is_zero(result))
        .setN(is_b7(result))
        .setV(result == 0x7F)
        .setS();

    env.write_reg_byte(tgtAddr, result);
    return false;
}

bool AluOpsImpl::DEC(Environ& env, FiveBit tgtAddr) {
    uchar_t tgtVal = env.read_reg_byte(tgtAddr);
    uchar_t result = (tgtVal - 1) & 0xFF;

    env.sReg
            .setZ(is_zero(result))
            .setN(is_b7(result))
            .setV(result == 0x7F)
            .setS();

    env.write_reg_byte(tgtAddr, result);
    return false;
}

bool AluOpsImpl::ASR(Environ& env, FiveBit tgtAddr) {
    uchar_t tgtVal = env.read_reg_byte(tgtAddr);
    uchar_t result = (tgtVal & 0x80) | (tgtVal >> 1);

    env.sReg
            .setC(is_b0(tgtVal))
            .setZ(is_zero(result))
            .setN(is_b7(result))
            .setV(result == 0x7F)
            .setS();

    env.write_reg_byte(tgtAddr, result);
    return false;
}

bool AluOpsImpl::MUL(Environ& env, FiveBit tgtAddr, FiveBit srcAddr) {
    uchar_t tgtVal = env.read_reg_byte(tgtAddr);
    uchar_t srcVal = env.read_reg_byte(srcAddr);

    unsigned short result = tgtVal * srcVal;

    env.write_reg_byte(M::R0, lo_byte(result));
    env.write_reg_byte(M::R1, hi_byte(result));
    return false;
}

bool AluOpsImpl::MULS(Environ& env, FiveBit tgtAddr, FiveBit srcAddr) {
    auto tgtVal = (schar_t) env.read_reg_byte(tgtAddr);
    auto srcVal = (schar_t) env.read_reg_byte(srcAddr);

    auto result = (short)(tgtVal * srcVal);

    env.sReg
        .setC( (result & 0x8000) == 0x8000)
        .setZ( result == 0x0000);

    env.write_reg_byte(M::R0, lo_byte(result));
    env.write_reg_byte(M::R1, hi_byte(result));
    return false;
}

bool AluOpsImpl::MULSU(Environ& env, FiveBit tgtAddr, FiveBit srcAddr) {
    auto tgtVal = (schar_t) env.read_reg_byte(tgtAddr);
    auto srcVal = (uchar_t) env.read_reg_byte(srcAddr);
    auto result = (short)(tgtVal * srcVal);

    env.sReg
            .setC( (result & 0x8000) == 0x8000)
            .setZ( result == 0x0000);

    env.write_reg_byte(M::R0, hi_byte(result));
    env.write_reg_byte(M::R1, lo_byte(result));
    return false;
}

bool AluOpsImpl::FMUL(Environ& env, FiveBit tgtAddr, FiveBit srcAddr) {
    uchar_t tgtVal = env.read_reg_byte(tgtAddr);
    uchar_t srcVal = env.read_reg_byte(srcAddr);
    unsigned short result = tgtVal * srcVal;
        result = result << 1;

    env.write_reg_byte(M::R0, lo_byte(result));
    env.write_reg_byte(M::R1, hi_byte(result));
    return false;
}

bool AluOpsImpl::FMULS(Environ& env, FiveBit tgtAddr, FiveBit srcAddr) {
    auto tgtVal = (schar_t) env.read_reg_byte(tgtAddr);
    auto srcVal = (schar_t) env.read_reg_byte(srcAddr);
    auto result = (unsigned short)(tgtVal * srcVal);
         result = result << 1;

    env.sReg
            .setC( (result & 0x8000) == 0x8000)
            .setZ( result == 0x0000);

    env.write_reg_byte(M::R0, lo_byte(result));
    env.write_reg_byte(M::R1, hi_byte(result));
    return false;
}

bool AluOpsImpl::FMULSU(Environ& env, FiveBit tgtAddr, FiveBit srcAddr) {
    auto tgtVal = (schar_t) env.read_reg_byte(tgtAddr);
    auto srcVal = (uchar_t) env.read_reg_byte(srcAddr);
    auto result = (uint16_t)(tgtVal * srcVal);
         result = result << 1;

    env.sReg
            .setC( (result & 0x8000) == 0x8000)
            .setZ( result == 0x0000);

    env.write_reg_byte(M::R0, lo_byte(result));
    env.write_reg_byte(M::R1, hi_byte(result));
    return false;
}

bool AluOpsImpl::TST(Environ &env, FiveBit tgtAddr) {
    IoOpsImpl::AND(env, tgtAddr, tgtAddr);
    return false;
}

bool AluOpsImpl::CP(Environ &env, FiveBit tgtAddr, FiveBit srcAddr) {
    uchar_t tgtVal = env.read_reg_byte(tgtAddr);
    uchar_t srcVal = env.read_reg_byte(srcAddr);
    uchar_t result = (tgtVal + ~srcVal + 1) & 0xFF;
    SubTwoFlags::statusFlags(tgtVal, srcVal, result, env.sReg);
    return false;
}

bool AluOpsImpl::CPC(Environ &env, FiveBit tgtAddr, FiveBit srcAddr) {
    uchar_t tgtVal = env.read_reg_byte(tgtAddr);
    uchar_t srcVal = env.read_reg_byte(srcAddr);
    uchar_t carry = env.sReg.C();
    uchar_t result = (tgtVal + ~srcVal + carry) & 0xFF;
    SubTwoFlags::statusFlags(tgtVal, srcVal, result, env.sReg);
    return false;
}

bool AluOpsImpl::CPI(Environ &env, FiveBit tgtAddr, EightBit immData) {
    uchar_t tgtVal = env.read_reg_byte(tgtAddr);
    uchar_t result = (tgtVal + ~immData + 1) & 0xFF;
    SubTwoFlags::statusFlags(tgtVal, immData, result, env.sReg);
    return false;
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