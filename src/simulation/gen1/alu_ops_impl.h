#ifndef ATMEGASIM_SRC_ALU_OPS_MC_H
#define ATMEGASIM_SRC_ALU_OPS_MC_H


#include "../infra/environment.h"
#include "../infra/types.h"
#include <cstdint>

class AluOpsImpl {

public:
    static void ADD(Environ &env, FiveBit tgtAddr, FiveBit srcAddr);
    static void ADC(Environ &env, FiveBit tgtAddr, FiveBit srcAddr);
    static void ADIW(Environ& env, FiveBit tgtAddr, SixBit immData);

    static void SUB(Environ &env, FiveBit tgtAddr, FiveBit srcAddr);
    static void SBC(Environ &env, FiveBit tgtAddr, FiveBit srcAddr);
    static void SUBI(Environ& env, FiveBit tgtAddr, EightBit immData);
    static void SBCI(Environ& env, FiveBit tgtAddr, EightBit immData);
    static void SBIW(Environ& env, FiveBit tgtAddr, SixBit immData);

    static void NEG(Environ& env, FiveBit tgtAddr);
    static void INC(Environ& env, FiveBit tgtAddr);
    static void DEC(Environ& env, FiveBit tgtAddr);
    static void ASR(Environ& env, FiveBit tgtAddr);

    static void MUL(Environ& env, FiveBit tgtAddr, FiveBit srcAddr);
    static void MULS(Environ& env, FiveBit tgtAddr, FiveBit srcAddr);
    static void MULSU(Environ& env, FiveBit tgtAddr, FiveBit srcAddr);

    static void FMUL(Environ& env, FiveBit tgtAddr, FiveBit srcAddr);
    static void FMULS(Environ& env, FiveBit tgtAddr, FiveBit srcAddr);
    static void FMULSU(Environ& env, FiveBit tgtAddr, FiveBit srcAddr);

    static void TST(Environ& env, FiveBit tgtAddr);
    static void CP(Environ& env, FiveBit tgtAddr, FiveBit srcAddr);

    static void CPC(Environ& env, FiveBit tgtAddr, FiveBit srcAddr);
    static void CPI(Environ& env, FiveBit tgtAddr, EightBit immData);
};

#endif //ATMEGASIM_SRC_ALU_OPS_MC_H
