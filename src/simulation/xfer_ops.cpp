#include "decoder.h"
#include "xfer_ops.h"

bool XferOps::MOV(Environ &env, uint16_t instrn) {
    FiveBit tgtAddr, srcAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    return MOV(env, tgtAddr, srcAddr);
}

bool XferOps::MOV(Environ &env, FiveBit tgtAddr, FiveBit srcAddr) {
    uchar_t srcVal = env.read_reg_byte(srcAddr);
    env.write_reg_byte(tgtAddr, srcVal);
    return false;
}

bool XferOps::MOVW(Environ &env, uint16_t instrn) {
    FourBit tgtNum, srcNum;
    ArgsDecode::TwoReg4(instrn, tgtNum, srcNum);
    FiveBit tgtAddr = tgtNum << 1;
    FiveBit srcAddr = srcNum << 1;
    return MOVW(env, tgtAddr, srcAddr);
}

bool XferOps::MOVW(Environ &env, FiveBit tgtAddr, FiveBit srcAddr) {
    uchar_t srcWord = env.read_reg_pair(srcAddr);
    env.write_reg_pair(tgtAddr, srcWord);
    return false;
}

bool XferOps::LDI(Environ &env, uint16_t instrn) {
    FourBit regNum; EightBit immData;
    ArgsDecode::Reg4Imm8(instrn, regNum, immData);
    FiveBit regAddr = regNum + 0x100;
    return LDI(env, regAddr, immData);
}

bool XferOps::LDI(Environ &env, FiveBit tgtAddr, EightBit immData) {
    env.write_reg_byte(tgtAddr, immData);
    return false;
}

bool XferOps::LD(Environ &env, uint16_t instrn) {
    FiveBit tgtAddr;
    TwoBit flag;
    TwoBit mode;

    ArgsDecode::Reg5FlagMode(instrn, tgtAddr, flag, mode);
    return LD(env, tgtAddr, flag, mode);
}

bool XferOps::LD(
    Environ &env, FiveBit tgtAddr, TwoBit flag, TwoBit mode) {

    uchar_t srcAddr;
    switch(flag) {
        case 0x00: srcAddr = M::Z; break;
        case 0x01: srcAddr = M::Y; break;
        case 0x02: srcAddr = M::X; break;
        default: throw InvalidEnum(0x00, env.PC);
    }
    bool postIncr = (mode == 0x01);
    bool preDecr  = (mode == 0x02);

    uint16_t memAddr = env.read_reg_pair(srcAddr);

    if (preDecr) memAddr--;

    uchar_t value = env.read_mem_byte(memAddr);
    env.write_reg_byte(tgtAddr, value);

    if (postIncr) memAddr++;
    if (preDecr || postIncr)
        env.write_reg_pair(srcAddr, memAddr);
    return false;
}

bool XferOps::LDD(Environ &env, uint16_t instrn) {
    FiveBit tgtAddr;
    OneBit flag;
    SixBit offset;

    ArgsDecode::Reg5FlagOffset(instrn, tgtAddr, flag, offset);
    return LDD(env, tgtAddr, flag, offset);
}

bool XferOps::LDD(
    Environ &env, FiveBit tgtAddr, OneBit flag, SixBit offset) {

    uchar_t srcAddr = flag ? M::Y : M::Z;

    uint16_t memAddr = env.read_reg_pair(srcAddr);
    memAddr = memAddr + offset;

    uchar_t value = env.read_mem_byte(memAddr);
    env.write_reg_byte(tgtAddr, value);

    return false;
}

bool XferOps::XCH(Environ &env, uint16_t instrn) {
    FiveBit regAddr;
    ArgsDecode::Reg5(instrn, regAddr);
    return XCH(env, regAddr);
}

bool XferOps::XCH(Environ &env, FiveBit regAddr) {
    uint16_t memAddr = env.read_reg_pair(M::X);
    uchar_t memValue = env.read_mem_byte(memAddr);
    uchar_t regValue = env.read_reg_byte(regAddr);
    env.write_mem_byte(memAddr, regValue);
    env.write_reg_byte(regAddr, memValue);
    return false;
}

bool XferOps::LAS(Environ &env, uint16_t instrn) {
    FiveBit regAddr;
    ArgsDecode::Reg5(instrn, regAddr);
    return LAS(env, regAddr);
}

bool XferOps::LAS(Environ &env, FiveBit regAddr) {
    uint16_t memAddr = env.read_reg_pair(M::X);
    uchar_t memValue = env.read_mem_byte(memAddr);
    uchar_t regValue = env.read_reg_byte(regAddr);
    memValue |= regValue;
    env.write_mem_byte(memAddr, regValue);
    env.write_reg_byte(regAddr, memValue);
    return false;
}

bool XferOps::LAC(Environ &env, uint16_t instrn) {
    FiveBit regAddr;
    ArgsDecode::Reg5(instrn, regAddr);
    return LAC(env, regAddr);
}

bool XferOps::LAC(Environ &env, FiveBit regAddr) {
    uint16_t memAddr = env.read_reg_pair(M::X);
    uchar_t memValue = env.read_mem_byte(memAddr);
    uchar_t regValue = env.read_reg_byte(regAddr);
    memValue = ~regValue & memValue;
    env.write_mem_byte(memAddr, regValue);
    env.write_reg_byte(regAddr, memValue);
    return false;
}

bool XferOps::LAT(Environ &env, uint16_t instrn) {
    FiveBit regAddr;
    ArgsDecode::Reg5(instrn, regAddr);
    return LAC(env, regAddr);
}

bool XferOps::LAT(Environ &env, FiveBit regAddr) {
    uint16_t memAddr = env.read_reg_pair(M::X);
    uchar_t memValue = env.read_mem_byte(memAddr);
    uchar_t regValue = env.read_reg_byte(regAddr);
    memValue = regValue ^ memValue;
    env.write_mem_byte(memAddr, regValue);
    env.write_reg_byte(regAddr, memValue);
    return false;
}


