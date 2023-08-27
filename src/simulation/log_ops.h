#ifndef ATMEGASIM_SRC_LOG_OPS_H
#define ATMEGASIM_SRC_LOG_OPS_H

#include <cstdint>
#include "types.h"
#include "environment.h"

class LogOps {
public:

    static bool AND(Environ& env, uint32_t instrn);
    static bool AND(Environ &env, FiveBit tgtAddr, FiveBit srcAddr);

    static bool ANDI(Environ& env, uint32_t instrn);
    static bool ANDI(Environ &env, FiveBit tgtAddr, uchar_t immData);

    static bool OR(Environ& env, uint32_t instrn);
    static bool OR(Environ &env, FiveBit tgtAddr, FiveBit srcAddr);

    static bool ORI(Environ& env, uint32_t instrn);
    static bool ORI(Environ &env, FiveBit tgtAddr, EightBit immData);

    static bool EOR(Environ& env, uint32_t instrn);
    static bool EOR(Environ &env, FiveBit tgtAddr, FiveBit srcAddr);

    static bool COM(Environ& env, uint32_t instrn);
    static bool COM(Environ &env, FiveBit tgtAddr);

    static bool SBR(Environ& env, uint32_t instrn);
    static bool SBR(Environ &env, FiveBit tgtAddr, EightBit immData);

    static bool CBR(Environ& env, uint32_t instrn);
    static bool CBR(Environ &env, FiveBit tgtAddr, EightBit immData);

    static bool SER(Environ& env, uint32_t instrn);
    static bool SER(Environ &env, FiveBit tgtAddr);

    static bool CLR(Environ& env, uint32_t instrn);
    static bool CLR(Environ &env, FiveBit tgtAddr);

    static bool LSL(Environ& env, uint32_t instrn);
    static bool LSL(Environ &env, FiveBit tgtAddr);

    static bool LSR(Environ& env, uint32_t instrn);
    static bool LSR(Environ &env, FiveBit tgtAddr);

    static bool ROL(Environ& env, uint32_t instrn);
    static bool ROL(Environ &env, FiveBit tgtAddr);

    static bool ROR(Environ& env, uint32_t instrn);
    static bool ROR(Environ &env, FiveBit tgtAddr);

};


#endif //ATMEGASIM_SRC_LOG_OPS_H
