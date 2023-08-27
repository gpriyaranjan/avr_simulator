#ifndef ATMEGASIM_EXECCOMMON_H
#define ATMEGASIM_EXECCOMMON_H

#include <strings.h>
#include "types.h"
#include "environment.h"

enum Cmds {
    // Arithmetic Operations
    ADD,
    ADC,
    ADIW,

    SUB,
    SBC,
    SUBI,
    SBCI,
    SBIW,

    NEG,
    INC,
    DEC,
    ASR,

    MUL,
    MULS,
    MULSU,

    FMUL,
    FMULS,
    FMULSU,

    // Logical Operations
    AND,
    ANDI,
    OR,
    ORI,
    EOR,

    COM,

    SBR,
    CBR,
    SER,
    CLR,

    LSL,
    LSR,

    ROL,
    ROR

};

class ArgsDecode {
public:

    /* XXXX	XXrd dddd rrrr */
    inline static void TwoReg5(uint32_t instrn, FiveBit& tgtReg, FiveBit& srcReg) {
        tgtReg = (instrn >> 4) & 0x1F;
        srcReg = ( (instrn & 0x0200) >> 5 ) | (instrn & 0xF);
    }

    /* XXXX	XXXX KKdd KKKK */
    inline static void Reg2Imm6(uint32_t instrn, TwoBit& tgtReg, SixBit& immItem) {
        tgtReg = (instrn & 0x30) >> 4;
        immItem = ((instrn & 0xC0)>>4) | (instrn & 0xF);
    }

    /* XXXX KKKK dddd KKKK */
    inline static void Reg4Imm8(uint32_t instrn, FourBit& tgtReg, EightBit& immItem) {
        tgtReg = (instrn & 0xF0) >> 4;
        immItem = ((instrn & 0xF00)>>4) | (instrn & 0xF);
    }

    /* XXXX	XXXd dddd XXXX */
    inline static void Reg5(uint32_t instrn, FiveBit& tgtReg) {
        tgtReg = (instrn >> 4) & 0x1F;
    }

    /* XXXX	XXXX dddd XXXX */
    inline static void Reg4(uint32_t instrn, FourBit& tgtReg) {
        tgtReg = (instrn >> 4) & 0x0F;
    }

    /* XXXX XXXX Xsss XXXX */
    inline static void SBit3(uint32_t instrn, ThreeBit& tgtBit) {
        tgtBit = (instrn >> 4) & 0x7;
    }

    /* XXXX	XXXd dddd Xbbb */
    inline static void Reg5SBit3(uint32_t instrn, FiveBit& tgtReg, ThreeBit& regNum) {
        regNum = instrn & 0x7;
        tgtReg = (instrn >> 4) & 0x1F;
    }

    /* 1100	kkkk kkkk kkkk */
    inline static void Addr12(uint32_t instrn, TwelveBit& offset) {
        offset = offset & 0x0FFF;
    }

    /* 1001	010k kkkk 110k kkkk	kkkk kkkk kkkk */
    inline static void Addr22(uint64_t instrn, TwentyTwoBit& tgtAddr) {
        uint32_t additionalBits;
        tgtAddr = instrn & 0x1FFFF;
        additionalBits = (instrn & 0x1F00000) >> 3;
        tgtAddr = tgtAddr | additionalBits;
    }


    /* XXXX	XXXX AAAA Abbb */
    inline static void IO5Bit3(uint32_t instrn, FiveBit& tgtReg, ThreeBit& bitNum) {
        bitNum = instrn & 0x7;
        tgtReg = (instrn >> 3) & 0x1F;
    }

    /* 1111-00kk-kkkk-ksss */
    inline static void Addr7Bit3(uint32_t instrn, SevenBit& addr, ThreeBit& regBits) {
        addr = (instrn >> 3) & 0x7F;
        regBits = instrn & 0x07;
    }

};

#endif //ATMEGASIM_EXECCOMMON_H
