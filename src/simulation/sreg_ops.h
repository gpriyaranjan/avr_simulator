#ifndef ATMEGASIM_SRC_SREG_OPS_H
#define ATMEGASIM_SRC_SREG_OPS_H

#include "simple_utils.h"
#include "environment.h"

class SRegOps {
public:

    static void BSET(Environ& env, unsigned int instrn);
    static void BSET_(Environ& env, ThreeBit regNum);

    static void BCLR(Environ& env, unsigned int instrn);
    static void BCLR_(Environ& env, ThreeBit regNum);

    static void SEC(Environ& env, unsigned int instrn);
    static void SEC_(Environ& env);
    static void CLC(Environ& env, unsigned int instrn);
    static void CLC_(Environ& env);

    static void SEZ(Environ& env, unsigned int instrn);
    static void SEZ_(Environ& env);
    static void CLZ(Environ& env, unsigned int instrn);
    static void CLZ_(Environ& env);

    static void SEN(Environ& env, unsigned int instrn);
    static void SEN_(Environ& env);
    static void CLN(Environ& env, unsigned int instrn);
    static void CLN_(Environ& env);

    static void SEV(Environ& env, unsigned int instrn);
    static void SEV_(Environ& env);
    static void CLV(Environ& env, unsigned int instrn);
    static void CLV_(Environ& env);

    static void SES(Environ& env, unsigned int instrn);
    static void SES_(Environ& env);
    static void CLS(Environ& env, unsigned int instrn);
    static void CLS_(Environ& env);

    static void SEH(Environ& env, unsigned int instrn);
    static void SEH_(Environ& env);
    static void CLH(Environ& env, unsigned int instrn);
    static void CLH_(Environ& env);


    static void SET(Environ& env, unsigned int instrn);
    static void SET_(Environ& env);
    static void CLT(Environ& env, unsigned int instrn);
    static void CLT_(Environ& env);

    static void BST(Environ& env, unsigned int instrn);
    static void BST_(Environ& env, FiveBit tgtAddr, ThreeBit regNum);

    static void BLD(Environ& env, unsigned int instrn);
    static void BLD_(Environ& env, FiveBit tgtAddr, ThreeBit regNum);


    static void WriteBit(Environ& env, ThreeBit regNum, bool value);

};


#endif //ATMEGASIM_SRC_SREG_OPS_H
