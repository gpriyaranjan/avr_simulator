#ifndef ATMEGASIM_ALUOPS_H
#define ATMEGASIM_ALUOPS_H

#include <cstdint>
#include "types.h"
#include "environment.h"

class AluOps {
public:

    static bool ADD(Environ& env, ShortInstrn instrn);
    static bool ADD(Environ &env, FiveBit tgtAddr, FiveBit srcAddr);

    static bool ADC(Environ& env, ShortInstrn instrn);
    static bool ADC(Environ &env, FiveBit tgtAddr, FiveBit srcAddr);

    static bool ADIW(Environ& env, ShortInstrn instrn);
    static bool ADIW(Environ& env, FiveBit tgtAddr, SixBit immData);

    static bool SUB(Environ& env, ShortInstrn instrn);
    static bool SUB(Environ &env, FiveBit tgtAddr, FiveBit srcAddr);

    static bool SBC(Environ& env, ShortInstrn instrn);
    static bool SBC(Environ &env, FiveBit tgtAddr, FiveBit srcAddr);

    static bool SUBI(Environ& env, ShortInstrn instrn);
    static bool SUBI(Environ& env, FiveBit tgtAddr, EightBit immData);

    static bool SBCI(Environ& env, ShortInstrn instrn);
    static bool SBCI(Environ& env, FiveBit tgtAddr, EightBit immData);

    static bool SBIW(Environ& env, ShortInstrn instrn);
    static bool SBIW(Environ& env, FiveBit tgtAddr, SixBit immData);

    static bool NEG(Environ& env, ShortInstrn instrn);
    static bool NEG(Environ& env, FiveBit tgtAddr);

    static bool INC(Environ& env, ShortInstrn instrn);
    static bool INC(Environ& env, FiveBit tgtAddr);

    static bool DEC(Environ& env, ShortInstrn instrn);
    static bool DEC(Environ& env, FiveBit tgtAddr);

    static bool ASR(Environ& env, ShortInstrn instrn);
    static bool ASR(Environ& env, FiveBit tgtAddr);

    static bool MUL(Environ& env, ShortInstrn instrn);
    static bool MUL(Environ& env, FiveBit tgtAddr, FiveBit srcAddr);

    static bool MULS(Environ& env, ShortInstrn instrn);
    static bool MULS(Environ& env, FiveBit tgtAddr, FiveBit srcAddr);

    static bool MULSU(Environ& env, ShortInstrn instrn);
    static bool MULSU(Environ& env, FiveBit tgtAddr, FiveBit srcAddr);

    static bool FMUL(Environ& env, ShortInstrn instrn);
    static bool FMUL(Environ& env, FiveBit tgtAddr, FiveBit srcAddr);

    static bool FMULS(Environ& env, ShortInstrn instrn);
    static bool FMULS(Environ& env, FiveBit tgtAddr, FiveBit srcAddr);

    static bool FMULSU(Environ& env, ShortInstrn instrn);
    static bool FMULSU(Environ& env, FiveBit tgtAddr, FiveBit srcAddr);

    static bool TST(Environ& env, ShortInstrn instrn);
    static bool TST(Environ& env, FiveBit tgtAddr);

    static bool CP(Environ& env, ShortInstrn instrn);
    static bool CP(Environ& env, FiveBit tgtAddr, FiveBit srcAddr);

    static bool CPC(Environ& env, ShortInstrn instrn);
    static bool CPC(Environ& env, FiveBit tgtAddr, FiveBit srcAddr);

    static bool CPI(Environ& env, ShortInstrn instrn);
    static bool CPI(Environ& env, FiveBit tgtAddr, EightBit immData);

};


class AddTwoFlags {
public:
    static bool NF(uchar_t result);
    static bool ZF(uchar_t result);
    static bool VF(uchar_t target, uchar_t source, uchar_t result);
    static bool CF(uchar_t target, uchar_t source, uchar_t result);
    static bool SF(uchar_t target, uchar_t source, uchar_t result);
    static bool HF(uchar_t target, uchar_t source, uchar_t result);

    static void statusFlags(uchar_t target, uchar_t source, uchar_t result, SReg &status);
};

class SubTwoFlags {
public:
    static bool NF(uchar_t result);
    static bool ZF(uchar_t result);
    static bool VF(uchar_t target, uchar_t source, uchar_t result);
    static bool CF(uchar_t target, uchar_t source, uchar_t result);
    static bool SF(uchar_t target, uchar_t source, uchar_t result);
    static bool HF(uchar_t target, uchar_t source, uchar_t result);

    static void statusFlags(uchar_t target, uchar_t source, uchar_t result, SReg &status);
};

#endif //ATMEGASIM_ALUOPS_H
