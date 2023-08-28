//
// Created by MAC BOOK on 28/08/23.
//

#ifndef ATMEGASIM_SRC_IO_OPS_MC_H
#define ATMEGASIM_SRC_IO_OPS_MC_H


#include "environment.h"
#include "types.h"
#include <cstdint>

class IoOpsMc {

public:

    static bool AND(Environ &env, FiveBit tgtAddr, FiveBit srcAddr);
    static bool ANDI(Environ &env, FiveBit tgtAddr, uchar_t immData);

    static bool OR(Environ &env, FiveBit tgtAddr, FiveBit srcAddr);
    static bool ORI(Environ &env, FiveBit tgtAddr, EightBit immData);

    static bool EOR(Environ &env, FiveBit tgtAddr, FiveBit srcAddr);
    static bool COM(Environ &env, FiveBit tgtAddr);

    static bool SBR(Environ &env, FiveBit tgtAddr, EightBit immData);
    static bool CBR(Environ &env, FiveBit tgtAddr, EightBit immData);

    static bool SER(Environ &env, FiveBit tgtAddr);
    static bool CLR(Environ &env, FiveBit tgtAddr);

    static bool LSL(Environ &env, FiveBit tgtAddr);
    static bool LSR(Environ &env, FiveBit tgtAddr);

    static bool ROL(Environ &env, FiveBit tgtAddr);
    static bool ROR(Environ &env, FiveBit tgtAddr);
};


#endif //ATMEGASIM_SRC_IO_OPS_MC_H
