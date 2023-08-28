#include "types.h"
#include "decoder.h"
#include "xfer_ops.h"
#include "xfer_ops_mc.h"

bool XferOps::MOV(Environ &env, ShortInstrn instrn) {
    FiveBit tgtAddr, srcAddr;
    ArgsDecode::TwoReg5(instrn, tgtAddr, srcAddr);
    return XferOpsMc::MOV(env, tgtAddr, srcAddr);
}

bool XferOps::MOVW(Environ &env, ShortInstrn instrn) {
    FourBit tgtNum, srcNum;
    ArgsDecode::TwoReg4(instrn, tgtNum, srcNum);
    FiveBit tgtAddr = tgtNum << 1;
    FiveBit srcAddr = srcNum << 1;
    return XferOpsMc::MOVW(env, tgtAddr, srcAddr);
}

bool XferOps::LDI(Environ &env, ShortInstrn instrn) {
    FourBit regNum; EightBit immData;
    ArgsDecode::Reg4Imm8(instrn, regNum, immData);
    FiveBit regAddr = regNum + 0x100;
    return XferOpsMc::LDI(env, regAddr, immData);
}

bool XferOps::LD(Environ &env, ShortInstrn instrn) {
    FiveBit tgtAddr;
    TwoBit flag;
    TwoBit mode;

    ArgsDecode::Reg5FlagMode(instrn, tgtAddr, flag, mode);
    return XferOpsMc::LD(env, tgtAddr, flag, mode);
}

bool XferOps::LDD(Environ &env, ShortInstrn instrn) {
    FiveBit tgtAddr;
    OneBit flag;
    SixBit offset;

    ArgsDecode::Reg5FlagOffset(instrn, tgtAddr, flag, offset);
    return XferOpsMc::LDD(env, tgtAddr, flag, offset);
}

bool XferOps::STS(Environ &env, LongInstrn instrn) {
    FiveBit regAddr; SixteenBit immData;
    ArgsDecode::Reg5Addr16(instrn, regAddr, immData);
    return XferOpsMc::STS(env, regAddr, immData);
}

bool XferOps::ST(Environ &env, ShortInstrn instrn) {
    FiveBit srcAddr;
    TwoBit flag;
    TwoBit mode;

    ArgsDecode::Reg5FlagMode(instrn, srcAddr, flag, mode);
    return XferOpsMc::ST(env, srcAddr, flag, mode);
}

bool XferOps::STD(Environ &env, ShortInstrn instrn) {
    FiveBit srcAddr;
    OneBit flag;
    SixBit offset;

    ArgsDecode::Reg5FlagOffset(instrn, srcAddr, flag, offset);
    return XferOpsMc::LDD(env, srcAddr, flag, offset);
}

bool XferOps::LPM(Environ &env, ShortInstrn instrn) {
    FiveBit regAddr; OneBit postIncr;
    ArgsDecode::Reg5Flag(instrn, regAddr, postIncr);
    return XferOpsMc::LPM(env, regAddr, postIncr);
}

bool XferOps::ELPM(Environ &env, ShortInstrn instrn) {
    FiveBit regAddr; OneBit postIncr;
    ArgsDecode::Reg5Flag(instrn, regAddr, postIncr);
    return XferOpsMc::ELPM(env, regAddr, postIncr);
}

bool XferOps::SPM(Environ &env, ShortInstrn instrn) {
    OneBit flag;
    ArgsDecode::FlagOnly(instrn, flag);
    return XferOpsMc::SPM(env, flag);
}

bool XferOps::XCH(Environ &env, ShortInstrn instrn) {
    FiveBit regAddr;
    ArgsDecode::Reg5(instrn, regAddr);
    return XferOpsMc::XCH(env, regAddr);
}

bool XferOps::LAS(Environ &env, ShortInstrn instrn) {
    FiveBit regAddr;
    ArgsDecode::Reg5(instrn, regAddr);
    return XferOpsMc::LAS(env, regAddr);
}

bool XferOps::LAC(Environ &env, ShortInstrn instrn) {
    FiveBit regAddr;
    ArgsDecode::Reg5(instrn, regAddr);
    return XferOpsMc::LAC(env, regAddr);
}

bool XferOps::LAT(Environ &env, ShortInstrn instrn) {
    FiveBit regAddr;
    ArgsDecode::Reg5(instrn, regAddr);
    return XferOpsMc::LAC(env, regAddr);
}


