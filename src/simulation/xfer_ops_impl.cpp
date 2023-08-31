//
// Created by MAC BOOK on 28/08/23.
//

#include "v1/xfer_ops.h"
#include "decoder.h"
#include "types.h"
#include "v1/xfer_ops_impl.h"

bool XferOpsImpl::MOV(Environ &env, FiveBit tgtAddr, FiveBit srcAddr) {
    uchar_t srcVal = env.read_reg_byte(srcAddr);
    env.write_reg_byte(tgtAddr, srcVal);
    return false;
}

bool XferOpsImpl::MOVW(Environ &env, FiveBit tgtAddr, FiveBit srcAddr) {
    uchar_t srcWord = env.read_reg_pair(srcAddr);
    env.write_reg_pair(tgtAddr, srcWord);
    return false;
}

bool XferOpsImpl::LDI(Environ &env, FiveBit tgtAddr, EightBit immData) {
    env.write_reg_byte(tgtAddr, immData);
    return false;
}

bool XferOpsImpl::LD(
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

bool XferOpsImpl::LDD(
    Environ &env, FiveBit tgtAddr, OneBit flag, SixBit offset) {

    uchar_t srcAddr = flag ? M::Y : M::Z;

    uint16_t memAddr = env.read_reg_pair(srcAddr);
    memAddr = memAddr + offset;

    uchar_t value = env.read_mem_byte(memAddr);
    env.write_reg_byte(tgtAddr, value);

    return false;
}

bool XferOpsImpl::STS(Environ &env, FiveBit srcAddr, SixteenBit memAddr) {
    uchar_t value = env.read_reg_byte(srcAddr);
    env.write_mem_byte(memAddr, value);
    return false;
}

bool XferOpsImpl::ST(Environ &env, FiveBit srcAddr, TwoBit flag, TwoBit mode) {

    uchar_t tgtRegAddr;
    switch(flag) {
        case 0x00: tgtRegAddr = M::Z; break;
        case 0x01: tgtRegAddr = M::Y; break;
        case 0x02: tgtRegAddr = M::X; break;
        default: throw InvalidEnum(0x00, env.PC);
    }
    bool postIncr = (mode == 0x01);
    bool preDecr  = (mode == 0x02);

    SixteenBit tgtMemAddr = env.read_reg_pair(tgtRegAddr);
    if (preDecr) tgtMemAddr--;

    uchar_t value = env.read_reg_byte(srcAddr);
    env.write_mem_byte(tgtMemAddr, value);

    if (postIncr) tgtMemAddr++;
    env.write_reg_pair(tgtRegAddr, value);
    return false;
}

bool XferOpsImpl::STD(
    Environ &env, FiveBit srcRegAddr, OneBit flag, SixBit offset) {

    uchar_t srcAddr = flag ? M::Y : M::Z;

    uint16_t memAddr = env.read_reg_pair(srcAddr);
    memAddr = memAddr + offset;

    uchar_t value = env.read_reg_byte(srcRegAddr);
    env.write_mem_byte(memAddr, value);

    return false;
}

bool XferOpsImpl::LPM(Environ &env, FiveBit regAddr, OneBit postIncr) {
    uint16_t memAddr = env.read_reg_pair(M::Z);

    uchar_t value = env.read_mem_byte(memAddr);
    env.write_reg_byte(regAddr, value);

    if (postIncr) {
        memAddr++;
        env.write_reg_pair(M::Z, memAddr);
    }
    return false;
}

bool XferOpsImpl::ELPM(Environ &env, FiveBit regAddr, OneBit postIncr) {
    uint16_t memOffAddr = env.read_reg_pair(M::Z);
    uchar_t memSegAddr = env.read_reg_byte(M::RAMPZ);
    CPUAddr memAddr = (memSegAddr >> 16) | memOffAddr;

    uchar_t value = env.read_mem_byte(memAddr);
    env.write_reg_byte(regAddr, value);

    if (postIncr) {
        memAddr++;
        env.write_reg_pair(M::Z, memAddr);
    }
    return false;
}

bool XferOpsImpl::SPM(Environ &env, OneBit postIncr) {
    uint16_t memOffAddr = env.read_reg_pair(M::Z);
    uchar_t memSegAddr = env.read_reg_byte(M::RAMPZ);
    CPUAddr memAddr = (memSegAddr >> 16) | memOffAddr;

    SixteenBit value = env.read_reg_pair(M::R0);
    env.write_mem_pair(memAddr, value);

    if (postIncr) {
        memAddr++;
        env.write_reg_pair(M::Z, memAddr & 0xFFFF);
        env.write_reg_byte(M::RAMPZ, (memAddr>>16)&0xFF);
    }

    return false;
}

bool XferOpsImpl::XCH(Environ &env, FiveBit regAddr) {
    uint16_t memAddr = env.read_reg_pair(M::X);
    uchar_t memValue = env.read_mem_byte(memAddr);
    uchar_t regValue = env.read_reg_byte(regAddr);
    env.write_mem_byte(memAddr, regValue);
    env.write_reg_byte(regAddr, memValue);
    return false;
}

bool XferOpsImpl::LAS(Environ &env, FiveBit regAddr) {
    uint16_t memAddr = env.read_reg_pair(M::X);
    uchar_t memValue = env.read_mem_byte(memAddr);
    uchar_t regValue = env.read_reg_byte(regAddr);
    memValue |= regValue;
    env.write_mem_byte(memAddr, regValue);
    env.write_reg_byte(regAddr, memValue);
    return false;
}

bool XferOpsImpl::LAC(Environ &env, FiveBit regAddr) {
    uint16_t memAddr = env.read_reg_pair(M::X);
    uchar_t memValue = env.read_mem_byte(memAddr);
    uchar_t regValue = env.read_reg_byte(regAddr);
    memValue = ~regValue & memValue;
    env.write_mem_byte(memAddr, regValue);
    env.write_reg_byte(regAddr, memValue);
    return false;
}

bool XferOpsImpl::LAT(Environ &env, FiveBit regAddr) {
    uint16_t memAddr = env.read_reg_pair(M::X);
    uchar_t memValue = env.read_mem_byte(memAddr);
    uchar_t regValue = env.read_reg_byte(regAddr);
    memValue = regValue ^ memValue;
    env.write_mem_byte(memAddr, regValue);
    env.write_reg_byte(regAddr, memValue);
    return false;
}