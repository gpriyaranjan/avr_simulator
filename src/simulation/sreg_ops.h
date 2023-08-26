#ifndef ATMEGASIM_SRC_SREG_OPS_H
#define ATMEGASIM_SRC_SREG_OPS_H

#include <cstdint>
#include "simple_utils.h"
#include "environment.h"

class SRegOps {
public:

    static void BSET(Environ& env, u_int32_t instrn);
    static void BSET_(Environ& env, ThreeBit regNum);

    static void BCLR(Environ& env, u_int32_t instrn);
    static void BCLR_(Environ& env, ThreeBit regNum);

    static void SEC(Environ& env, u_int32_t instrn);
    static void SEC_(Environ& env);
    static void CLC(Environ& env, u_int32_t instrn);
    static void CLC_(Environ& env);

    static void SEZ(Environ& env, u_int32_t instrn);
    static void SEZ_(Environ& env);
    static void CLZ(Environ& env, u_int32_t instrn);
    static void CLZ_(Environ& env);

    static void SEN(Environ& env, u_int32_t instrn);
    static void SEN_(Environ& env);
    static void CLN(Environ& env, u_int32_t instrn);
    static void CLN_(Environ& env);

    static void SEV(Environ& env, uint32_t instrn);
    static void SEV_(Environ& env);
    static void CLV(Environ& env, uint32_t instrn);
    static void CLV_(Environ& env);

    static void SES(Environ& env, uint32_t instrn);
    static void SES_(Environ& env);
    static void CLS(Environ& env, uint32_t instrn);
    static void CLS_(Environ& env);

    static void SEH(Environ& env, uint32_t instrn);
    static void SEH_(Environ& env);
    static void CLH(Environ& env, uint32_t instrn);
    static void CLH_(Environ& env);


    static void SET(Environ& env, uint32_t instrn);
    static void SET_(Environ& env);
    static void CLT(Environ& env, uint32_t instrn);
    static void CLT_(Environ& env);

    static void BST(Environ& env, uint32_t instrn);
    static void BST_(Environ& env, FiveBit tgtAddr, ThreeBit regNum);

    static void BLD(Environ& env, uint32_t instrn);
    static void BLD_(Environ& env, FiveBit tgtAddr, ThreeBit regNum);


    static void WriteBit(Environ& env, ThreeBit regNum, bool value);

};


#endif //ATMEGASIM_SRC_SREG_OPS_H
