#ifndef ATMEGASIM_EXECCOMMON_H
#define ATMEGASIM_EXECCOMMON_H

#include <strings.h>
#include "simple_utils.h"
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
    inline static void TwoReg5(unsigned int instrn, FiveBit& tgtReg, FiveBit& srcReg) {
        tgtReg = (instrn >> 4) & 0x1F;
        srcReg = ( (instrn & 0x0200) >> 5 ) | (instrn & 0xF);
    }

    /* XXXX	XXXX KKdd KKKK */
    inline static void Reg2Imm6(unsigned int instrn, TwoBit& tgtReg, SixBit& immItem) {
        tgtReg = (instrn & 0x30) >> 4;
        immItem = ((instrn & 0xC0)>>4) | (instrn & 0xF);
    }

    /* XXXX KKKK dddd KKKK */
    inline static void Reg4Imm8(unsigned int instrn, FourBit& tgtReg, EightBit& immItem) {
        tgtReg = (instrn & 0xF0) >> 4;
        immItem = ((instrn & 0xF00)>>4) | (instrn & 0xF);
    }

    /* XXXX	XXXd dddd XXXX */
    inline static void Reg5(unsigned int instrn, FiveBit& tgtReg) {
        tgtReg = (instrn >> 4) & 0x1F;
    }

    /* XXXX	XXXX dddd XXXX */
    inline static void Reg4(unsigned int instrn, FourBit& tgtReg) {
        tgtReg = (instrn >> 4) & 0x0F;
    }

    /* XXXX XXXX Xsss XXXX */
    inline static void SBit3(unsigned int instrn, ThreeBit& tgtBit) {
        tgtBit = (instrn >> 4) & 0x7;
    }

    /* XXXX	XXXd dddd Xbbb */
    inline static void Reg5SBit3(unsigned int instrn, FiveBit& tgtReg, ThreeBit& regNum) {
        regNum = instrn & 0x7;
        tgtReg = (instrn >> 4) & 0x1F;
    }
};

#endif //ATMEGASIM_EXECCOMMON_H
