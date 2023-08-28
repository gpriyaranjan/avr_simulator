#ifndef ATMEGASIM_SRC_XFER_OPS_H
#define ATMEGASIM_SRC_XFER_OPS_H

#include "environment.h"

class XferOps {
public:

    static bool MOV(Environ& env, uint16_t instrn);
    static bool MOV(Environ &env, FiveBit tgtAddr, FiveBit srcAddr);

    static bool MOVW(Environ& env, uint16_t instrn);
    static bool MOVW(Environ &env, FiveBit tgtAddr, FiveBit srcAddr);

    static bool LDI(Environ& env, uint16_t instrn);
    static bool LDI(Environ &env, FiveBit tgtAddr, EightBit immData);

    static bool LD(Environ& env, uint16_t instrn);
    static bool LD(Environ &env,FiveBit tgtAddr, TwoBit flag, TwoBit mode);

    static bool LDD(Environ& env, uint16_t instrn);
    static bool LDD(Environ &env,FiveBit tgtAddr, OneBit flag, SixBit offset);

    static bool XCH(Environ& env, uint16_t instrn);
    static bool XCH(Environ &env, FiveBit regAddr);

    static bool LAS(Environ& env, uint16_t instrn);
    static bool LAS(Environ &env, FiveBit regAddr);

    static bool LAC(Environ& env, uint16_t instrn);
    static bool LAC(Environ &env, FiveBit regAddr);

    static bool LAT(Environ& env, uint16_t instrn);
    static bool LAT(Environ &env, FiveBit regAddr);

};


#endif //ATMEGASIM_SRC_XFER_OPS_H
