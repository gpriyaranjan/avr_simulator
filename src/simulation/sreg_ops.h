#ifndef ATMEGASIM_SRC_SREG_OPS_H
#define ATMEGASIM_SRC_SREG_OPS_H

#include <cstdint>
#include "types.h"
#include "environment.h"

class SRegOps {
public:

    static bool BSET(Environ& env, ShortInstrn instrn);
    static bool BSET(Environ& env, ThreeBit regNum, bool dummy);

    static bool BCLR(Environ& env, ShortInstrn instrn);
    static bool BCLR(Environ& env, ThreeBit regNum, bool dummy);

    static bool SEC(Environ& env, ShortInstrn instrn);
    static bool SEC(Environ& env);
    static bool CLC(Environ& env, ShortInstrn instrn);
    static bool CLC(Environ& env);

    static bool SEZ(Environ& env, ShortInstrn instrn);
    static bool SEZ(Environ& env);
    static bool CLZ(Environ& env, ShortInstrn instrn);
    static bool CLZ(Environ& env);

    static bool SEN(Environ& env, ShortInstrn instrn);
    static bool SEN(Environ& env);
    static bool CLN(Environ& env, ShortInstrn instrn);
    static bool CLN(Environ& env);

    static bool SEV(Environ& env, ShortInstrn instrn);
    static bool SEV(Environ& env);
    static bool CLV(Environ& env, ShortInstrn instrn);
    static bool CLV(Environ& env);

    static bool SES(Environ& env, ShortInstrn instrn);
    static bool SES(Environ& env);
    static bool CLS(Environ& env, ShortInstrn instrn);
    static bool CLS(Environ& env);

    static bool SEH(Environ& env, ShortInstrn instrn);
    static bool SEH(Environ& env);
    static bool CLH(Environ& env, ShortInstrn instrn);
    static bool CLH(Environ& env);

    static bool SET(Environ& env, ShortInstrn instrn);
    static bool SET(Environ& env);
    static bool CLT(Environ& env, ShortInstrn instrn);
    static bool CLT(Environ& env);

    static bool BST(Environ& env, ShortInstrn instrn);
    static bool BST(Environ& env, FiveBit tgtAddr, ThreeBit regNum);

    static bool BLD(Environ& env, ShortInstrn instrn);
    static bool BLD(Environ& env, FiveBit tgtAddr, ThreeBit regNum);


    static bool WriteBit(Environ& env, ThreeBit regNum, bool value);

};


#endif //ATMEGASIM_SRC_SREG_OPS_H
