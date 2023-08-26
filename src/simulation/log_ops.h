#ifndef ATMEGASIM_SRC_LOG_OPS_H
#define ATMEGASIM_SRC_LOG_OPS_H

#include "simple_utils.h"
#include "environment.h"

class LogOps {
public:

    static void AND(Environ& env, unsigned int instrn);
    static void AND_(Environ &env, FiveBit tgtAddr, FiveBit srcAddr);

    static void ANDI(Environ& env, unsigned int instrn);
    static void ANDI_(Environ &env, FiveBit tgtAddr, UChar immData);

    static void OR(Environ& env, unsigned int instrn);
    static void OR_(Environ &env, FiveBit tgtAddr, FiveBit srcAddr);

    static void ORI(Environ& env, unsigned int instrn);
    static void ORI_(Environ &env, FiveBit tgtAddr, EightBit immData);

    static void EOR(Environ& env, unsigned int instrn);
    static void EOR_(Environ &env, FiveBit tgtAddr, FiveBit srcAddr);

    static void COM(Environ& env, unsigned int instrn);
    static void COM_(Environ &env, FiveBit tgtAddr);

    static void SBR(Environ& env, unsigned int instrn);
    static void SBR_(Environ &env, FiveBit tgtAddr, EightBit immData);

    static void CBR(Environ& env, unsigned int instrn);
    static void CBR_(Environ &env, FiveBit tgtAddr, EightBit immData);

    static void SER(Environ& env, unsigned int instrn);
    static void SER_(Environ &env, FiveBit tgtAddr);

    static void CLR(Environ& env, unsigned int instrn);
    static void CLR_(Environ &env, FiveBit tgtAddr);

    static void LSL(Environ& env, unsigned int instrn);
    static void LSL_(Environ &env, FiveBit tgtAddr);

    static void LSR(Environ& env, unsigned int instrn);
    static void LSR_(Environ &env, FiveBit tgtAddr);

    static void ROL(Environ& env, unsigned int instrn);
    static void ROL_(Environ &env, FiveBit tgtAddr);

    static void ROR(Environ& env, unsigned int instrn);
    static void ROR_(Environ &env, FiveBit tgtAddr);

};


#endif //ATMEGASIM_SRC_LOG_OPS_H
