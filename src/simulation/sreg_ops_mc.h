#ifndef ATMEGASIM_SRC_SREG_OPS_MC_H
#define ATMEGASIM_SRC_SREG_OPS_MC_H


#include "environment.h"
#include "types.h"
#include <cstdint>

class SRegOpsMc {

public:
    static bool WriteBit(Environ& env, ThreeBit regNum, bool value);

    static bool BSET(Environ& env, ThreeBit regNum, bool dummy);
    static bool BCLR(Environ& env, ThreeBit regNum, bool dummy);

    static bool SEC(Environ& env);
    static bool CLC(Environ& env);

    static bool SEZ(Environ& env);
    static bool CLZ(Environ& env);

    static bool SEN(Environ& env);
    static bool CLN(Environ& env);

    static bool SEV(Environ& env);
    static bool CLV(Environ& env);

    static bool SES(Environ& env);
    static bool CLS(Environ& env);

    static bool SEH(Environ& env);
    static bool CLH(Environ& env);

    static bool SET(Environ& env);
    static bool CLT(Environ& env);

    static bool BST(Environ& env, FiveBit tgtAddr, ThreeBit regNum);
    static bool BLD(Environ& env, FiveBit tgtAddr, ThreeBit regNum);
};


#endif //ATMEGASIM_SRC_SREG_OPS_MC_H
