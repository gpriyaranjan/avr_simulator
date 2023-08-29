#ifndef ATMEGASIM_EXECCOMMON_H
#define ATMEGASIM_EXECCOMMON_H

#include <strings.h>
#include "types.h"
#include "environment.h"

class ArgsDecode {
public:

    /* XXXX	XXrd dddd rrrr */
    inline static void TwoReg5(ShortInstrn instrn, FiveBit& tgtReg, FiveBit& srcReg) {
        tgtReg = (instrn >> 4) & 0x1F;
        srcReg = ( (instrn & 0x0200) >> 5 ) | (instrn & 0xF);
    }

    /* XXXX	XXXX KKdd KKKK */
    inline static void Reg2Imm6(ShortInstrn instrn, TwoBit& tgtReg, SixBit& immItem) {
        tgtReg = (instrn >> 4) & 0x03;
        immItem = ((instrn >> 2) & 0x30) | (instrn & 0xF);
    }

    /* XXXX KKKK dddd KKKK */
    inline static void Reg4Imm8(ShortInstrn instrn, FourBit& tgtReg, EightBit& immItem) {
        tgtReg = (instrn & 0xF0) >> 4;
        immItem = ((instrn & 0xF00)>>4) | (instrn & 0xF);
    }

    /* XXXX	XXXd dddd XXXX */
    inline static void Reg5(ShortInstrn instrn, FiveBit& tgtReg) {
        tgtReg = (instrn >> 4) & 0x1F;
    }

    /* XXXX	XXXX dddd XXXX */
    inline static void Reg4(ShortInstrn instrn, FourBit& tgtReg) {
        tgtReg = (instrn >> 4) & 0x0F;
    }

    /* XXXX XXXX Xsss XXXX */
    inline static void SBit3(ShortInstrn instrn, ThreeBit& tgtBit) {
        tgtBit = (instrn >> 4) & 0x7;
    }

    /* XXXX	XXXd dddd Xbbb */
    inline static void Reg5SBit3(ShortInstrn instrn, FiveBit& tgtReg, ThreeBit& regNum) {
        regNum = instrn & 0x7;
        tgtReg = (instrn >> 4) & 0x1F;
    }

    /* 1100	kkkk kkkk kkkk */
    inline static void Addr12(ShortInstrn instrn, TwelveBit& offset) {
        offset = offset & 0x0FFF;
    }

    /* 1001	010k kkkk 110k kkkk	kkkk kkkk kkkk */
    inline static void Addr22(LongInstrn instrn, TwentyTwoBit& tgtAddr) {
        uint32_t additionalBits;
        tgtAddr = instrn & 0x1FFFF;
        additionalBits = (instrn & 0x1F00000) >> 3;
        tgtAddr = tgtAddr | additionalBits;
    }

    /* XXXX	XXXX AAAA Abbb */
    inline static void IO5Bit3(ShortInstrn instrn, FiveBit& tgtReg, ThreeBit& bitNum) {
        bitNum = instrn & 0x7;
        tgtReg = (instrn >> 3) & 0x1F;
    }

    /* 1111-00kk-kkkk-ksss */
    inline static void Addr7Bit3(ShortInstrn instrn, SevenBit& addr, ThreeBit& regBits) {
        addr = (instrn >> 3) & 0x7F;
        regBits = instrn & 0x07;
    }

    /* XXXX-XXXX-dddd-rrrr */
    inline static void TwoReg4(ShortInstrn instrn, FourBit& tgtNum, FourBit& srcNum) {
        srcNum = instrn & 0x0F;
        tgtNum = (instrn>>4) & 0x0F;
    }

    /* 1000-000d-dddd-ffmm */
    inline static void Reg5FlagMode(
        ShortInstrn instrn, FiveBit& regAddr, TwoBit& srcFlag, TwoBit& dispMode) {

        regAddr = (instrn >> 4) & 0x0F;
        srcFlag = (instrn >> 2) & 0x03;
        dispMode = instrn & 0x03;
    }

    /* 10q0-qq0d-dddd-fqqq*/
    inline static void Reg5FlagOffset(
        ShortInstrn instrn, FiveBit& regAddr, OneBit& srcFlag, SixBit& offset) {

        regAddr = (instrn >> 4) & 0x0F;
        srcFlag = (instrn >> 1) & 0x01;
        offset = ( (instrn >> 3) & 0x07 ) | ( (instrn >> 7) & 0x1F) | ( (instrn >> 6) & 0x40 );
    }

    /* XXXX-XXXr-rrrr-XXXX-kkkk-kkkk-kkkk-kkkk */
    inline static void Reg5Addr16(
        LongInstrn instrn, FiveBit& regAddr, SixteenBit& immData) {

        immData = instrn & 0xFFFF;
        regAddr = (instrn>>16) & 0x1F;
    }

    /* XXXX-XXXd-dddd-XXXf */
    inline static void Reg5Flag(ShortInstrn instrn, FiveBit& regAddr, OneBit& flag) {
        regAddr = (instrn >> 4) & 0x1F;
        flag = instrn & 0x1;
    }

    /* XXXX-XXXX-XXXXf-XXXX */
    inline static void FlagOnly(ShortInstrn instrn, OneBit& flag) {
        flag = ( instrn >> 4 ) & 0x1;
    }

    /* XXXX-XAAd-dddd-AAAA */
    inline static void Reg5IO6(ShortInstrn instrn, FiveBit& regAddr, SixBit& ioPort) {
        regAddr = (instrn >> 4) & 0x1F;
        ioPort = (instrn & 0x0F) | ((instrn >> 5) & 0x30);
    }

};

#endif //ATMEGASIM_EXECCOMMON_H
