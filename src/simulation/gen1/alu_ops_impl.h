#ifndef ATMEGASIM_SRC_ALU_OPS_MC_H
#define ATMEGASIM_SRC_ALU_OPS_MC_H


#include "../environment.h"
#include "../types.h"
#include <cstdint>

class AluOpsImpl {

public:
    static bool ADD(Environ &env, FiveBit tgtAddr, FiveBit srcAddr);
    static bool ADC(Environ &env, FiveBit tgtAddr, FiveBit srcAddr);
    static bool ADIW(Environ& env, FiveBit tgtAddr, SixBit immData);

    static bool SUB(Environ &env, FiveBit tgtAddr, FiveBit srcAddr);
    static bool SBC(Environ &env, FiveBit tgtAddr, FiveBit srcAddr);
    static bool SUBI(Environ& env, FiveBit tgtAddr, EightBit immData);
    static bool SBCI(Environ& env, FiveBit tgtAddr, EightBit immData);
    static bool SBIW(Environ& env, FiveBit tgtAddr, SixBit immData);

    static bool NEG(Environ& env, FiveBit tgtAddr);
    static bool INC(Environ& env, FiveBit tgtAddr);
    static bool DEC(Environ& env, FiveBit tgtAddr);
    static bool ASR(Environ& env, FiveBit tgtAddr);

    static bool MUL(Environ& env, FiveBit tgtAddr, FiveBit srcAddr);
    static bool MULS(Environ& env, FiveBit tgtAddr, FiveBit srcAddr);
    static bool MULSU(Environ& env, FiveBit tgtAddr, FiveBit srcAddr);

    static bool FMUL(Environ& env, FiveBit tgtAddr, FiveBit srcAddr);
    static bool FMULS(Environ& env, FiveBit tgtAddr, FiveBit srcAddr);
    static bool FMULSU(Environ& env, FiveBit tgtAddr, FiveBit srcAddr);

    static bool TST(Environ& env, FiveBit tgtAddr);
    static bool CP(Environ& env, FiveBit tgtAddr, FiveBit srcAddr);

    static bool CPC(Environ& env, FiveBit tgtAddr, FiveBit srcAddr);
    static bool CPI(Environ& env, FiveBit tgtAddr, EightBit immData);
};

#endif //ATMEGASIM_SRC_ALU_OPS_MC_H
