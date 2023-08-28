#ifndef ATMEGASIM_SRC_XFER_OPS_H
#define ATMEGASIM_SRC_XFER_OPS_H

#include "environment.h"

class XferOps {
public:

    static bool MOV(Environ& env, ShortInstrn instrn);
    static bool MOV(Environ &env, FiveBit tgtAddr, FiveBit srcAddr);

    static bool MOVW(Environ& env, ShortInstrn instrn);
    static bool MOVW(Environ &env, FiveBit tgtAddr, FiveBit srcAddr);

    static bool LDI(Environ& env, ShortInstrn instrn);
    static bool LDI(Environ &env, FiveBit tgtAddr, EightBit immData);

    static bool LD(Environ& env, ShortInstrn instrn);
    static bool LD(Environ &env,FiveBit tgtAddr, TwoBit flag, TwoBit mode);

    static bool LDD(Environ& env, ShortInstrn instrn);
    static bool LDD(Environ &env, FiveBit tgtAddr, OneBit flag, SixBit offset);

    static bool STS(Environ& env, LongInstrn instrn);
    static bool STS(Environ &env, FiveBit srcAddr, SixteenBit memAddr);

    static bool ST(Environ& env, ShortInstrn instrn);
    static bool ST(Environ &env,FiveBit srcAddr, TwoBit flag, TwoBit mode);

    static bool STD(Environ& env, ShortInstrn instrn);
    static bool STD(Environ &env, FiveBit srcRegAddr, OneBit flag, SixBit offset);

    static bool LPM(Environ& env, ShortInstrn instrn);
    static bool LPM(Environ& env, FiveBit regAddr, OneBit postIncr);

    static bool ELPM(Environ& env, ShortInstrn instrn);
    static bool ELPM(Environ& env, FiveBit regAddr, OneBit postIncr);

    static bool SPM(Environ& env, ShortInstrn instrn);
    static bool SPM(Environ& env, OneBit postIncr);

    static bool XCH(Environ& env, ShortInstrn instrn);
    static bool XCH(Environ &env, FiveBit regAddr);

    static bool LAS(Environ& env, ShortInstrn instrn);
    static bool LAS(Environ &env, FiveBit regAddr);

    static bool LAC(Environ& env, ShortInstrn instrn);
    static bool LAC(Environ &env, FiveBit regAddr);

    static bool LAT(Environ& env, ShortInstrn instrn);
    static bool LAT(Environ &env, FiveBit regAddr);

};


#endif //ATMEGASIM_SRC_XFER_OPS_H
