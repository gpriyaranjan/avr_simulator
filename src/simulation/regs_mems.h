#ifndef ATMEGASIM_SRC_REGS_MEMS_H
#define ATMEGASIM_SRC_REGS_MEMS_H

#include "types.h"

enum GPRegs {
    R0 = 0,  R1,  R2,  R3,  R4,  R5,  R6,  R7,
        R8,  R9, R10, R11, R12, R13, R14, R15,
       R16, R17, R18, R19, R20, R21, R22, R23,
       R24, R25, R26, R27, R28, R29, R30, R31
};

enum PtrRegs {
    X = R26, Y = R28, Z = R30
};


#endif //ATMEGASIM_SRC_REGS_MEMS_H
