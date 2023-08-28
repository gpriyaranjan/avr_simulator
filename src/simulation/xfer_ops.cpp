#include "types.h"
#include "decoder.h"
#include "xfer_ops.h"

bool XferOps::MOV(Environ &env, ShortInstrn instrn) {
    FiveBit tgtAddr, srcAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    return MOV(env, tgtAddr, srcAddr);
}

bool XferOps::MOV(Environ &env, FiveBit tgtAddr, FiveBit srcAddr) {
    uchar_t srcVal = env.read_reg_byte(srcAddr);
    env.write_reg_byte(tgtAddr, srcVal);
    return false;
}

bool XferOps::MOVW(Environ &env, ShortInstrn instrn) {
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

bool XferOps::LDI(Environ &env, ShortInstrn instrn) {
    FourBit regNum; EightBit immData;
    ArgsDecode::Reg4Imm8(instrn, regNum, immData);
    FiveBit regAddr = regNum + 0x100;
    return LDI(env, regAddr, immData);
}

bool XferOps::LDI(Environ &env, FiveBit tgtAddr, EightBit immData) {
    env.write_reg_byte(tgtAddr, immData);
    return false;
}

bool XferOps::LD(Environ &env, ShortInstrn instrn) {
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

bool XferOps::LDD(Environ &env, ShortInstrn instrn) {
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

bool XferOps::STS(Environ &env, LongInstrn instrn) {
    FiveBit regAddr; SixteenBit immData;
    ArgsDecode::Reg5Addr16(instrn, regAddr, immData);
    return STS(env, regAddr, immData);
}

bool XferOps::STS(Environ &env, FiveBit srcAddr, SixteenBit memAddr) {
    uchar_t value = env.read_reg_byte(srcAddr);
    env.write_mem_byte(memAddr, value);
    return false;
}

bool XferOps::ST(Environ &env, ShortInstrn instrn) {
    FiveBit srcAddr;
    TwoBit flag;
    TwoBit mode;

    ArgsDecode::Reg5FlagMode(instrn, srcAddr, flag, mode);
    return ST(env, srcAddr, flag, mode);
}

bool XferOps::ST(Environ &env, FiveBit srcAddr, TwoBit flag, TwoBit mode) {

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

bool XferOps::STD(Environ &env, ShortInstrn instrn) {
    FiveBit srcAddr;
    OneBit flag;
    SixBit offset;

    ArgsDecode::Reg5FlagOffset(instrn, srcAddr, flag, offset);
    return LDD(env, srcAddr, flag, offset);
}

bool XferOps::STD(
    Environ &env, FiveBit srcRegAddr, OneBit flag, SixBit offset) {

    uchar_t srcAddr = flag ? M::Y : M::Z;

    uint16_t memAddr = env.read_reg_pair(srcAddr);
    memAddr = memAddr + offset;

    uchar_t value = env.read_reg_byte(srcRegAddr);
    env.write_mem_byte(memAddr, value);

    return false;
}

bool XferOps::LPM(Environ &env, ShortInstrn instrn) {
    FiveBit regAddr; OneBit postIncr;
    ArgsDecode::Reg5Flag(instrn, regAddr, postIncr);
    return LPM(env, regAddr, postIncr);
}

bool XferOps::LPM(Environ &env, FiveBit regAddr, OneBit postIncr) {
    uint16_t memAddr = env.read_reg_pair(M::Z);

    uchar_t value = env.read_mem_byte(memAddr);
    env.write_reg_byte(regAddr, value);

    if (postIncr) {
        memAddr++;
        env.write_reg_pair(M::Z, memAddr);
    }
    return false;
}

bool XferOps::ELPM(Environ &env, ShortInstrn instrn) {
    FiveBit regAddr; OneBit postIncr;
    ArgsDecode::Reg5Flag(instrn, regAddr, postIncr);
    return ELPM(env, regAddr, postIncr);
}

bool XferOps::ELPM(Environ &env, FiveBit regAddr, OneBit postIncr) {
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

bool XferOps::SPM(Environ &env, ShortInstrn instrn) {
    OneBit flag;
    ArgsDecode::FlagOnly(instrn, flag);
    return SPM(env, flag);
}

bool XferOps::SPM(Environ &env, OneBit postIncr) {
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

bool XferOps::XCH(Environ &env, ShortInstrn instrn) {
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

bool XferOps::LAS(Environ &env, ShortInstrn instrn) {
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

bool XferOps::LAC(Environ &env, ShortInstrn instrn) {
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

bool XferOps::LAT(Environ &env, ShortInstrn instrn) {
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


