#ifndef ATMEGASIM_SRC_LOG_OPS_H
#define ATMEGASIM_SRC_LOG_OPS_H

#include <cstdint>
#include "types.h"
#include "environment.h"

class LogOps {
public:

    static bool AND(Environ& env, ShortInstrn instrn);
    static bool AND(Environ &env, FiveBit tgtAddr, FiveBit srcAddr);

    static bool ANDI(Environ& env, ShortInstrn instrn);
    static bool ANDI(Environ &env, FiveBit tgtAddr, uchar_t immData);

    static bool OR(Environ& env, ShortInstrn instrn);
    static bool OR(Environ &env, FiveBit tgtAddr, FiveBit srcAddr);

    static bool ORI(Environ& env, ShortInstrn instrn);
    static bool ORI(Environ &env, FiveBit tgtAddr, EightBit immData);

    static bool EOR(Environ& env, ShortInstrn instrn);
    static bool EOR(Environ &env, FiveBit tgtAddr, FiveBit srcAddr);

    static bool COM(Environ& env, ShortInstrn instrn);
    static bool COM(Environ &env, FiveBit tgtAddr);

    static bool SBR(Environ& env, ShortInstrn instrn);
    static bool SBR(Environ &env, FiveBit tgtAddr, EightBit immData);

    static bool CBR(Environ& env, ShortInstrn instrn);
    static bool CBR(Environ &env, FiveBit tgtAddr, EightBit immData);

    static bool SER(Environ& env, ShortInstrn instrn);
    static bool SER(Environ &env, FiveBit tgtAddr);

    static bool CLR(Environ& env, ShortInstrn instrn);
    static bool CLR(Environ &env, FiveBit tgtAddr);

    static bool LSL(Environ& env, ShortInstrn instrn);
    static bool LSL(Environ &env, FiveBit tgtAddr);

    static bool LSR(Environ& env, ShortInstrn instrn);
    static bool LSR(Environ &env, FiveBit tgtAddr);

    static bool ROL(Environ& env, ShortInstrn instrn);
    static bool ROL(Environ &env, FiveBit tgtAddr);

    static bool ROR(Environ& env, ShortInstrn instrn);
    static bool ROR(Environ &env, FiveBit tgtAddr);

};


#endif //ATMEGASIM_SRC_LOG_OPS_H
