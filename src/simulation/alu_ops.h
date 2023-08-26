#ifndef ATMEGASIM_ALUOPS_H
#define ATMEGASIM_ALUOPS_H

#include <cstdint>
#include "simple_utils.h"
#include "environment.h"

class AluOps {
public:

    static void ADD(Environ& env, u_int32_t instrn);
    static void ADD(Environ &env, FiveBit tgtAddr, FiveBit srcAddr);

    static void ADC(Environ& env, uint32_t instrn);
    static void ADC(Environ &env, FiveBit tgtAddr, FiveBit srcAddr);

    static void ADIW(Environ& env, uint32_t instrn);
    static void ADIW(Environ& env, FiveBit tgtAddr, SixBit immData);

    static void SUB(Environ& env, uint32_t instrn);
    static void SUB(Environ &env, FiveBit tgtAddr, FiveBit srcAddr);

    static void SBC(Environ& env, uint32_t instrn);
    static void SBC(Environ &env, FiveBit tgtAddr, FiveBit srcAddr);

    static void SUBI(Environ& env, uint32_t instrn);
    static void SUBI(Environ& env, FiveBit tgtAddr, EightBit immData);

    static void SBCI(Environ& env, uint32_t instrn);
    static void SBCI(Environ& env, FiveBit tgtAddr, EightBit immData);

    static void SBIW(Environ& env, uint32_t instrn);
    static void SBIW(Environ& env, FiveBit tgtAddr, SixBit immData);

    static void NEG(Environ& env, uint32_t instrn);
    static void NEG(Environ& env, FiveBit tgtAddr);

    static void INC(Environ& env, uint32_t instrn);
    static void INC(Environ& env, FiveBit tgtAddr);

    static void DEC(Environ& env, uint32_t instrn);
    static void DEC(Environ& env, FiveBit tgtAddr);

    static void ASR(Environ& env, uint32_t instrn);
    static void ASR(Environ& env, FiveBit tgtAddr);

    static void MUL(Environ& env, uint32_t instrn);
    static void MUL(Environ& env, FiveBit tgtAddr, FiveBit srcAddr);

    static void MULS(Environ& env, uint32_t instrn);
    static void MULS(Environ& env, FiveBit tgtAddr, FiveBit srcAddr);

    static void MULSU(Environ& env, uint32_t instrn);
    static void MULSU(Environ& env, FiveBit tgtAddr, FiveBit srcAddr);

    static void FMUL(Environ& env, uint32_t instrn);
    static void FMUL(Environ& env, FiveBit tgtAddr, FiveBit srcAddr);

    static void FMULS(Environ& env, uint32_t instrn);
    static void FMULS(Environ& env, FiveBit tgtAddr, FiveBit srcAddr);

    static void FMULSU(Environ& env, uint32_t instrn);
    static void FMULSU(Environ& env, FiveBit tgtAddr, FiveBit srcAddr);

    static void TST(Environ& env, uint32_t instrn);
    static void TST(Environ& env, FiveBit tgtAddr);

    static void CP(Environ& env, uint32_t instrn);
    static void CP(Environ& env, FiveBit tgtAddr, FiveBit srcAddr);

    static void CPC(Environ& env, uint32_t instrn);
    static void CPC(Environ& env, FiveBit tgtAddr, FiveBit srcAddr);

    static void CPCI(Environ& env, uint32_t instrn);
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
