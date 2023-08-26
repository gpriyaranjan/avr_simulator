#ifndef ATMEGASIM_ALUOPS_H
#define ATMEGASIM_ALUOPS_H

#include "simple_utils.h"
#include "environment.h"

class AluOps {
public:

    static void ADD(Environ& env, unsigned int instrn);
    static void ADD(Environ &env, FiveBit tgtAddr, FiveBit srcAddr);

    static void ADC(Environ& env, unsigned int instrn);
    static void ADC(Environ &env, FiveBit tgtAddr, FiveBit srcAddr);

    static void ADIW(Environ& env, unsigned int instrn);
    static void ADIW(Environ& env, FiveBit tgtAddr, SixBit immData);

    static void SUB(Environ& env, unsigned int instrn);
    static void SUB(Environ &env, FiveBit tgtAddr, FiveBit srcAddr);

    static void SBC(Environ& env, unsigned int instrn);
    static void SBC(Environ &env, FiveBit tgtAddr, FiveBit srcAddr);

    static void SUBI(Environ& env, unsigned int instrn);
    static void SUBI(Environ& env, FiveBit tgtAddr, EightBit immData);

    static void SBCI(Environ& env, unsigned int instrn);
    static void SBCI(Environ& env, FiveBit tgtAddr, EightBit immData);

    static void SBIW(Environ& env, unsigned int instrn);
    static void SBIW(Environ& env, FiveBit tgtAddr, SixBit immData);

    static void NEG(Environ& env, unsigned int instrn);
    static void NEG(Environ& env, FiveBit tgtAddr);

    static void INC(Environ& env, unsigned int instrn);
    static void INC(Environ& env, FiveBit tgtAddr);

    static void DEC(Environ& env, unsigned int instrn);
    static void DEC(Environ& env, FiveBit tgtAddr);

    static void ASR(Environ& env, unsigned int instrn);
    static void ASR(Environ& env, FiveBit tgtAddr);

    static void MUL(Environ& env, unsigned int instrn);
    static void MUL(Environ& env, FiveBit tgtAddr, FiveBit srcAddr);

    static void MULS(Environ& env, unsigned int instrn);
    static void MULS(Environ& env, FiveBit tgtAddr, FiveBit srcAddr);

    static void MULSU(Environ& env, unsigned int instrn);
    static void MULSU(Environ& env, FiveBit tgtAddr, FiveBit srcAddr);

    static void FMUL(Environ& env, unsigned int instrn);
    static void FMUL(Environ& env, FiveBit tgtAddr, FiveBit srcAddr);

    static void FMULS(Environ& env, unsigned int instrn);
    static void FMULS(Environ& env, FiveBit tgtAddr, FiveBit srcAddr);

    static void FMULSU(Environ& env, unsigned int instrn);
    static void FMULSU(Environ& env, FiveBit tgtAddr, FiveBit srcAddr);

    static void TST(Environ& env, unsigned int instrn);
    static void TST(Environ& env, FiveBit tgtAddr);

    static void CP(Environ& env, unsigned int instrn);
    static void CP(Environ& env, FiveBit tgtAddr, FiveBit srcAddr);

    static void CPC(Environ& env, unsigned int instrn);
    static void CPC(Environ& env, FiveBit tgtAddr, FiveBit srcAddr);

    static void CPCI(Environ& env, unsigned int instrn);
    static void CPCI(Environ& env, FiveBit tgtAddr, EightBit immData);

};


class AddTwoFlags {
public:
    static bool NF(UChar result);
    static bool ZF(UChar result);
    static bool VF(UChar target, UChar source, UChar result);
    static bool CF(UChar target, UChar source, UChar result);
    static bool SF(UChar target, UChar source, UChar result);
    static bool HF(UChar target, UChar source, UChar result);

    static void statusFlags(UChar target, UChar source, UChar result, SReg &status);
};

class SubTwoFlags {
public:
    static bool NF(UChar result);
    static bool ZF(UChar result);
    static bool VF(UChar target, UChar source, UChar result);
    static bool CF(UChar target, UChar source, UChar result);
    static bool SF(UChar target, UChar source, UChar result);
    static bool HF(UChar target, UChar source, UChar result);

    static void statusFlags(UChar target, UChar source, UChar result, SReg &status);
};

#endif //ATMEGASIM_ALUOPS_H
