#ifndef ATMEGASIM_SRC_LOG_OPS_H
#define ATMEGASIM_SRC_LOG_OPS_H

#include <cstdint>
#include "types.h"
#include "environment.h"

class LogOps {
public:

    static void AND(Environ& env, uint32_t instrn);
    static void AND(Environ &env, FiveBit tgtAddr, FiveBit srcAddr);

    static void ANDI(Environ& env, uint32_t instrn);
    static void ANDI(Environ &env, FiveBit tgtAddr, uchar_t immData);

    static void OR(Environ& env, uint32_t instrn);
    static void OR(Environ &env, FiveBit tgtAddr, FiveBit srcAddr);

    static void ORI(Environ& env, uint32_t instrn);
    static void ORI(Environ &env, FiveBit tgtAddr, EightBit immData);

    static void EOR(Environ& env, uint32_t instrn);
    static void EOR(Environ &env, FiveBit tgtAddr, FiveBit srcAddr);

    static void COM(Environ& env, uint32_t instrn);
    static void COM(Environ &env, FiveBit tgtAddr);

    static void SBR(Environ& env, uint32_t instrn);
    static void SBR(Environ &env, FiveBit tgtAddr, EightBit immData);

    static void CBR(Environ& env, uint32_t instrn);
    static void CBR(Environ &env, FiveBit tgtAddr, EightBit immData);

    static void SER(Environ& env, uint32_t instrn);
    static void SER(Environ &env, FiveBit tgtAddr);

    static void CLR(Environ& env, uint32_t instrn);
    static void CLR(Environ &env, FiveBit tgtAddr);

    static void LSL(Environ& env, uint32_t instrn);
    static void LSL(Environ &env, FiveBit tgtAddr);

    static void LSR(Environ& env, uint32_t instrn);
    static void LSR(Environ &env, FiveBit tgtAddr);

    static void ROL(Environ& env, uint32_t instrn);
    static void ROL(Environ &env, FiveBit tgtAddr);

    static void ROR(Environ& env, uint32_t instrn);
    static void ROR(Environ &env, FiveBit tgtAddr);

};


#endif //ATMEGASIM_SRC_LOG_OPS_H
