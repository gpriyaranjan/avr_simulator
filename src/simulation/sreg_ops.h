#ifndef ATMEGASIM_SRC_SREG_OPS_H
#define ATMEGASIM_SRC_SREG_OPS_H

#include <cstdint>
#include "types.h"
#include "environment.h"

class SRegOps {
public:

    static void BSET(Environ& env, u_int32_t instrn);
    static void BSET(Environ& env, ThreeBit regNum, bool dummy);

    static void BCLR(Environ& env, u_int32_t instrn);
    static void BCLR(Environ& env, ThreeBit regNum, bool dummy);

    static void SEC(Environ& env, u_int32_t instrn);
    static void SEC(Environ& env);
    static void CLC(Environ& env, u_int32_t instrn);
    static void CLC(Environ& env);

    static void SEZ(Environ& env, u_int32_t instrn);
    static void SEZ(Environ& env);
    static void CLZ(Environ& env, u_int32_t instrn);
    static void CLZ(Environ& env);

    static void SEN(Environ& env, u_int32_t instrn);
    static void SEN(Environ& env);
    static void CLN(Environ& env, u_int32_t instrn);
    static void CLN(Environ& env);

    static void SEV(Environ& env, uint32_t instrn);
    static void SEV(Environ& env);
    static void CLV(Environ& env, uint32_t instrn);
    static void CLV(Environ& env);

    static void SES(Environ& env, uint32_t instrn);
    static void SES(Environ& env);
    static void CLS(Environ& env, uint32_t instrn);
    static void CLS(Environ& env);

    static void SEH(Environ& env, uint32_t instrn);
    static void SEH(Environ& env);
    static void CLH(Environ& env, uint32_t instrn);
    static void CLH(Environ& env);


    static void SET(Environ& env, uint32_t instrn);
    static void SET(Environ& env);
    static void CLT(Environ& env, uint32_t instrn);
    static void CLT(Environ& env);

    static void BST(Environ& env, uint32_t instrn);
    static void BST(Environ& env, FiveBit tgtAddr, ThreeBit regNum);

    static void BLD(Environ& env, uint32_t instrn);
    static void BLD(Environ& env, FiveBit tgtAddr, ThreeBit regNum);


    static void WriteBit(Environ& env, ThreeBit regNum, bool value);

};


#endif //ATMEGASIM_SRC_SREG_OPS_H
