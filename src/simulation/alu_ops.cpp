#include "types.h"
#include "decoder.h"
#include "alu_ops.h"
#include "log_ops.h"

void AluOps::ADD(Environ& env, u_int32_t instrn) {
    FiveBit srcAddr, tgtAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    ADD(env, tgtAddr, srcAddr);
}

void AluOps::ADD(Environ &env, FiveBit tgtAddr, FiveBit srcAddr) {
    uchar_t tgtVal = env.read_register(tgtAddr);
    uchar_t srcVal = env.read_register(srcAddr);

    uchar_t result = (srcVal + tgtVal) & 0x100;

    AddTwoFlags::statusFlags(tgtVal, srcVal, result, env.sReg);
    env.write_register(tgtAddr, result);
}

void AluOps::ADC(Environ& env, uint32_t instrn) {
    FiveBit srcAddr, tgtAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    ADC(env, tgtAddr, srcAddr);
}

void AluOps::ADC(Environ &env, FiveBit tgtAddr, FiveBit srcAddr) {
    uchar_t tgtVal = env.read_register(tgtAddr);
    uchar_t srcVal = env.read_register(srcAddr);

    uchar_t result = (srcVal + tgtVal + 1) % 0x100;

    AddTwoFlags::statusFlags(tgtVal, srcVal, result, env.sReg);
    env.write_register(tgtAddr, result);
}

void AluOps::ADIW(Environ& env, uint32_t instrn) {
    TwoBit tgtId;
    SixBit immData;
    ArgsDecode::Reg2Imm6(instrn, tgtId, immData);
    FiveBit tgtAddr = 24 + 2 * tgtId;
    ADIW(env, tgtAddr, immData);
}

void AluOps::ADIW(Environ& env, FiveBit tgtAddr, SixBit immData) {

    uchar_t tgtVal = env.read_register(tgtAddr);
    uchar_t result1 = (immData + tgtVal) & 0xFF;

    OneBit carry = AddTwoFlags::CF(tgtVal, immData, result1);
    uchar_t tgtVal2 = env.read_register(tgtAddr + 1);
    uchar_t result2 = (tgtVal2 + carry);

    env.sReg
        .setC(is_b7(result2) && is_nb7(tgtVal2))
        .setZ((result1 == 0) && (result2 == 0))
        .setN(is_b7(result2))
        .setV(is_nb7(result2) && is_b7(result2))
        .setS();

    env.write_register(tgtAddr, result1);
    env.write_register(tgtAddr+1, result2);
}

void AluOps::SUB(Environ& env, uint32_t instrn) {
    FiveBit srcAddr, tgtAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    SUB(env, tgtAddr, srcAddr);
}

void AluOps::SUB(Environ &env, FiveBit tgtAddr, FiveBit srcAddr) {
    uchar_t tgtVal = env.read_register(tgtAddr);
    uchar_t srcVal = env.read_register(srcAddr);

    uchar_t result = (~srcVal + tgtVal + 1) % 0x100;

    SubTwoFlags::statusFlags(tgtVal, srcVal, result, env.sReg);
    env.write_register(tgtAddr, result);
}

void AluOps::SBC(Environ& env, uint32_t instrn) {
    FiveBit srcAddr, tgtAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    SBC(env, tgtAddr, srcAddr);
}

void AluOps::SBC(Environ &env, FiveBit tgtAddr, FiveBit srcAddr) {

    uchar_t tgtVal = env.read_register(tgtAddr);
    uchar_t srcVal = env.read_register(srcAddr);

    uchar_t result = (~srcVal + tgtVal) & 0xFF;

    SubTwoFlags::statusFlags(tgtVal, srcVal, result, env.sReg);
    env.write_register(tgtAddr, result);
}

void AluOps::SUBI(Environ& env, uint32_t instrn) {
    FourBit tgtId;
    EightBit immData;
    ArgsDecode::Reg4Imm8(instrn, tgtId, immData);
    FiveBit tgtAddr = tgtId + 0x10;
    SUBI(env, tgtAddr, immData);
}

void AluOps::SUBI(Environ& env, FiveBit tgtAddr, EightBit immData) {
    uchar_t tgtVal = env.read_register(tgtAddr);
    uchar_t result = (~immData + tgtVal + 1) % 0x100;

    SubTwoFlags::statusFlags(tgtVal, immData, result, env.sReg);
    env.write_register(tgtAddr, result);
}

void AluOps::SBCI(Environ& env, uint32_t instrn) {
    FourBit tgtId;
    EightBit immData;
    ArgsDecode::Reg4Imm8(instrn, tgtId, immData);
    FiveBit tgtAddr = tgtId + 0x10;
    SBCI(env, tgtAddr, immData);
}

void AluOps::SBCI(Environ& env, FiveBit tgtAddr, EightBit immData) {
    uchar_t tgtVal = env.read_register(tgtAddr);
    uchar_t result = (~immData + tgtVal) & 0xFF;

    AddTwoFlags::statusFlags(tgtVal, immData, result, env.sReg);
    env.write_register(tgtAddr, result);
}

void AluOps::SBIW(Environ& env, uint32_t instrn) {
    TwoBit tgtId;
    SixBit immData;
    ArgsDecode::Reg2Imm6(instrn, tgtId, immData);
    FiveBit tgtAddr = 24 + 2 * tgtId;
    SBIW(env, tgtAddr, immData);
}

void AluOps::SBIW(Environ& env, FiveBit tgtAddr, SixBit immData) {
    uchar_t tgtVal1 = env.read_register(tgtAddr);
    uchar_t result1 = (~immData + tgtVal1 + 1) & 0xFF;

    bool carry = SubTwoFlags::CF(tgtVal1, immData, result1);
    uchar_t tgtVal2 = env.read_register(tgtAddr + 1);
    uchar_t result2 = (tgtVal2 - carry);

    env.sReg
        .setC(is_b7(result2) && is_nb7(tgtVal1))
        .setZ(is_zero(result2) && is_zero(result1))
        .setN(is_b7(result2))
        .setV(is_b7(result2) && is_nb7(tgtVal1))
        .setS();

    env.write_register(tgtAddr, result1);
    env.write_register(tgtAddr+1, result2);
}

void AluOps::NEG(Environ& env, uint32_t instrn) {
    FiveBit tgtAddr;
    ArgsDecode::Reg5(instrn, tgtAddr);
    NEG(env, tgtAddr);
}

void AluOps::NEG(Environ& env, FiveBit tgtAddr) {
    uchar_t tgtVal = env.read_register(tgtAddr);
    uchar_t result = (~tgtVal + 1) & 0xFF;

    env.sReg
        .setC(result == 0xFF)
        .setZ(is_zero(result))
        .setN(is_b7(result))
        .setV(result == 0x80)
        .setH(is_nb3(tgtVal) && is_b3(result))
        .setS();

    env.write_register(tgtAddr, result);
}

void AluOps::INC(Environ& env, uint32_t instrn) {
    FiveBit tgtAddr;
    ArgsDecode::Reg5(instrn, tgtAddr);
    INC(env, tgtAddr);
}

void AluOps::INC(Environ& env, FiveBit tgtAddr) {
    uchar_t tgtVal = env.read_register(tgtAddr);
    uchar_t result = (tgtVal + 1) & 0xFF;

    env.sReg
        .setZ(is_zero(result))
        .setN(is_b7(result))
        .setV(result == 0x7F)
        .setS();

    env.write_register(tgtAddr, result);
}

void AluOps::DEC(Environ& env, uint32_t instrn) {
    FiveBit tgtAddr;
    ArgsDecode::Reg5(instrn, tgtAddr);
    DEC(env, tgtAddr);
}

void AluOps::DEC(Environ& env, FiveBit tgtAddr) {
    uchar_t tgtVal = env.read_register(tgtAddr);
    uchar_t result = (tgtVal - 1) & 0xFF;

    env.sReg
            .setZ(is_zero(result))
            .setN(is_b7(result))
            .setV(result == 0x7F)
            .setS();

    env.write_register(tgtAddr, result);
}

void AluOps::ASR(Environ& env, uint32_t instrn) {
    FiveBit tgtAddr;
    ArgsDecode::Reg5(instrn, tgtAddr);
    ASR(env, tgtAddr);
}

void AluOps::ASR(Environ& env, FiveBit tgtAddr) {
    uchar_t tgtVal = env.read_register(tgtAddr);
    uchar_t result = (tgtVal & 0x80) | (tgtVal >> 1);

    env.sReg
            .setC(is_b0(tgtVal))
            .setZ(is_zero(result))
            .setN(is_b7(result))
            .setV(result == 0x7F)
            .setS();

    env.write_register(tgtAddr, result);
}

void AluOps::MUL(Environ& env, uint32_t instrn) {
    FiveBit srcAddr, tgtAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    MUL(env, tgtAddr, srcAddr);
}

void AluOps::MUL(Environ& env, FiveBit tgtAddr, FiveBit srcAddr) {
    uchar_t tgtVal = env.read_register(tgtAddr);
    uchar_t srcVal = env.read_register(srcAddr);

    unsigned short result = tgtVal * srcVal;

    env.write_register(R0, result & 0xFF);
    env.write_register(R1, (result >> 8) & 0xFF);
}

void AluOps::MULS(Environ& env, uint32_t instrn) {
    FiveBit srcAddr, tgtAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    MULS(env, tgtAddr, srcAddr);
}

void AluOps::MULS(Environ& env, FiveBit tgtAddr, FiveBit srcAddr) {
    auto tgtVal = (schar_t)env.read_register(tgtAddr);
    auto srcVal = (schar_t)env.read_register(srcAddr);

    auto result = (short)(tgtVal * srcVal);

    env.sReg
        .setC( (result & 0x8000) == 0x8000)
        .setZ( result == 0x0000);

    env.write_register(R0, result & 0xFF);
    env.write_register(R1, (result >> 8) & 0xFF);
}


void AluOps::MULSU(Environ& env, uint32_t instrn) {
    FiveBit srcAddr, tgtAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    MULSU(env, tgtAddr, srcAddr);
}

void AluOps::MULSU(Environ& env, FiveBit tgtAddr, FiveBit srcAddr) {
    auto tgtVal = (schar_t)env.read_register(tgtAddr);
    auto srcVal = (uchar_t)env.read_register(srcAddr);
    auto result = (short)(tgtVal * srcVal);

    env.sReg
            .setC( (result & 0x8000) == 0x8000)
            .setZ( result == 0x0000);

    env.write_register(R0, result & 0xFF);
    env.write_register(R1, (result >> 8) & 0xFF);
}

void AluOps::FMUL(Environ& env, uint32_t instrn) {
    FiveBit srcAddr, tgtAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    MUL(env, tgtAddr, srcAddr);
}

void AluOps::FMUL(Environ& env, FiveBit tgtAddr, FiveBit srcAddr) {
    uchar_t tgtVal = env.read_register(tgtAddr);
    uchar_t srcVal = env.read_register(srcAddr);
    unsigned short result = tgtVal * srcVal;
        result = result << 1;

    env.write_register(R0, result & 0xFF);
    env.write_register(R1, (result >> 8) & 0xFF);
}

void AluOps::FMULS(Environ& env, uint32_t instrn) {
    FiveBit srcAddr, tgtAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    MULS(env, tgtAddr, srcAddr);
}

void AluOps::FMULS(Environ& env, FiveBit tgtAddr, FiveBit srcAddr) {
    auto tgtVal = (schar_t)env.read_register(tgtAddr);
    auto srcVal = (schar_t)env.read_register(srcAddr);
    auto result = (unsigned short)(tgtVal * srcVal);
         result = result << 1;

    env.sReg
            .setC( (result & 0x8000) == 0x8000)
            .setZ( result == 0x0000);

    env.write_register(R0, result & 0xFF);
    env.write_register(R1, (result >> 8) & 0xFF);
}


void AluOps::FMULSU(Environ& env, uint32_t instrn) {
    FiveBit srcAddr, tgtAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    MULSU(env, tgtAddr, srcAddr);
}

void AluOps::FMULSU(Environ& env, FiveBit tgtAddr, FiveBit srcAddr) {
    auto tgtVal = (schar_t)env.read_register(tgtAddr);
    auto srcVal = (uchar_t)env.read_register(srcAddr);
    auto result = (unsigned short)(tgtVal * srcVal);
         result = result << 1;

    env.sReg
            .setC( (result & 0x8000) == 0x8000)
            .setZ( result == 0x0000);

    env.write_register(R0, result & 0xFF);
    env.write_register(R1, (result >> 8) & 0xFF);
}

void AluOps::TST(Environ &env, uint32_t instrn) {
    FiveBit srcAddr, tgtAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    TST(env, tgtAddr);
}

void AluOps::TST(Environ &env, FiveBit tgtAddr) {
    LogOps::AND(env, tgtAddr, tgtAddr);
}

void AluOps::CP(Environ &env, uint32_t instrn) {
    FiveBit tgtAddr, srcAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    CP(env, tgtAddr, srcAddr);
}

void AluOps::CP(Environ &env, FiveBit tgtAddr, FiveBit srcAddr) {
    uchar_t tgtVal = env.read_register(tgtAddr);
    uchar_t srcVal = env.read_register(srcAddr);
    uchar_t result = (tgtVal + ~srcVal + 1) & 0xFF;
    SubTwoFlags::statusFlags(tgtVal, srcVal, result, env.sReg);
}

void AluOps::CPC(Environ &env, uint32_t instrn) {
    FiveBit tgtAddr, srcAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    CPC(env, tgtAddr, srcAddr);
}

void AluOps::CPC(Environ &env, FiveBit tgtAddr, FiveBit srcAddr) {
    uchar_t tgtVal = env.read_register(tgtAddr);
    uchar_t srcVal = env.read_register(srcAddr);
    uchar_t carry = env.sReg.C ? 0 : 1;
    uchar_t result = (tgtVal + ~srcVal + carry) & 0xFF;
    SubTwoFlags::statusFlags(tgtVal, srcVal, result, env.sReg);
}

void AluOps::CPCI(Environ &env, uint32_t instrn) {
    FourBit tgtId; EightBit immData;
    ArgsDecode::Reg4Imm8(instrn, tgtId, immData);
    FiveBit tgtAddr = tgtId + 0x100;
    CPCI(env, tgtAddr, immData);
}

void AluOps::CPCI(Environ &env, FiveBit tgtAddr, EightBit immData) {
    uchar_t tgtVal = env.read_register(tgtAddr);
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
    status.init();
    status.N = NF(result);
    status.Z = ZF(result);
    status.V = VF(target, source, result);
    status.C = CF(target, source, result);
    status.S = SF(target, source, result);
    status.H = HF(target, source, result);
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
    status.init();
    status.N = NF(result);
    status.Z = ZF(result);
    status.V = VF(target, source, result);
    status.C = CF(target, source, result);
    status.S = SF(target, source, result);
    status.H = HF(target, source, result);
}