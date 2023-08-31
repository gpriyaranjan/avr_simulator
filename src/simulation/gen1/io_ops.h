#ifndef ATMEGASIM_SRC_IO_OPS_H
#define ATMEGASIM_SRC_IO_OPS_H

#include "../types.h"
#include "../environment.h"

class IoOps {

    static bool IN(Environ& env, ShortInstrn instrn);
    static bool IN(Environ& env, FiveBit tgtAddr, SixBit srcIoAddr);

    static bool OUT(Environ& env, ShortInstrn instrn);
    static bool OUT(Environ& env, FiveBit srcAddr, SixBit tgtIoAddr);

    static bool SBI(Environ& env, ShortInstrn instrn);
    static bool SBI(Environ& env, FiveBit tgtIoPort, ThreeBit bitNum);

    static bool CBI(Environ& env, ShortInstrn instrn);
    static bool CBI(Environ& env, FiveBit tgtIoPort, ThreeBit bitNum);

    static bool SEI(Environ& env, ShortInstrn instrn);
    static bool SEI(Environ& env);

    static bool CLI(Environ& env, ShortInstrn instrn);
    static bool CLI(Environ& env);

};


#endif //ATMEGASIM_SRC_IO_OPS_H
