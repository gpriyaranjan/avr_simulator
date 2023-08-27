#ifndef ATMEGASIM_SRC_REGS_MEMS_H
#define ATMEGASIM_SRC_REGS_MEMS_H

#include "types.h"

namespace M {

    constexpr uchar_t R0 = 0x00;
    constexpr uchar_t R1 = 0x01;
    constexpr uchar_t R2 = 0x02;
    constexpr uchar_t R3 = 0x03;
    constexpr uchar_t R4 = 0x04;
    constexpr uchar_t R5 = 0x05;
    constexpr uchar_t R6 = 0x06;
    constexpr uchar_t R7 = 0x07;

    constexpr uchar_t R8 = 0x08;
    constexpr uchar_t R9 = 0x09;
    constexpr uchar_t R10 = 0x0A;
    constexpr uchar_t R11 = 0x0B;
    constexpr uchar_t R12 = 0x0C;
    constexpr uchar_t R13 = 0x0D;
    constexpr uchar_t R14 = 0x0E;
    constexpr uchar_t R15 = 0x0F;

    constexpr uchar_t R16 = 0x10;
    constexpr uchar_t R17 = 0x11;
    constexpr uchar_t R18 = 0x12;
    constexpr uchar_t R19 = 0x13;
    constexpr uchar_t R20 = 0x14;
    constexpr uchar_t R21 = 0x15;
    constexpr uchar_t R22 = 0x16;
    constexpr uchar_t R23 = 0x17;

    constexpr uchar_t R24 = 0x18;
    constexpr uchar_t R25 = 0x19;
    constexpr uchar_t R26 = 0x1A;
    constexpr uchar_t R27 = 0x1B;
    constexpr uchar_t R28 = 0x1C;
    constexpr uchar_t R29 = 0x1D;
    constexpr uchar_t R30 = 0x1E;
    constexpr uchar_t R31 = 0x1F;

    // Pointer registers (points to lower word)

    constexpr uchar_t X = 0x1A;
    constexpr uchar_t XL = 0x1A;
    constexpr uchar_t XH = 0x1B;

    constexpr uchar_t Y = 0x1C;
    constexpr uchar_t YL = 0x1C;
    constexpr uchar_t YH = 0x1D;

    constexpr uchar_t Z = 0x1E;
    constexpr uchar_t ZL = 0x1E;
    constexpr uchar_t ZH = 0x1F;

    constexpr uchar_t RAMPD = 0x58;
    constexpr uchar_t RAMPX = 0x59;
    constexpr uchar_t RAMPY = 0x5A;
    constexpr uchar_t RAMPZ = 0x5B;
    constexpr uchar_t EIND  = 0x5C;

    constexpr uchar_t SP    = 0x5D;
    constexpr uchar_t SPL   = 0x5D;
    constexpr uchar_t SPH   = 0x5E;

    constexpr uchar_t SREG  = 0x5F;
};

#endif //ATMEGASIM_SRC_REGS_MEMS_H
