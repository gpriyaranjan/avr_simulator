#ifndef ATMEGASIM_SRC_SREG_OPS_H
#define ATMEGASIM_SRC_SREG_OPS_H

#include <cstdint>
#include "../types.h"
#include "../environment.h"

class SRegOps {
public:

    static bool BSET(Environ& env, ShortInstrn instrn);
    static bool BCLR(Environ& env, ShortInstrn instrn);

    static bool SEC(Environ& env, ShortInstrn instrn);
    static bool CLC(Environ& env, ShortInstrn instrn);

    static bool SEZ(Environ& env, ShortInstrn instrn);
    static bool CLZ(Environ& env, ShortInstrn instrn);

    static bool SEN(Environ& env, ShortInstrn instrn);
    static bool CLN(Environ& env, ShortInstrn instrn);

    static bool SEV(Environ& env, ShortInstrn instrn);
    static bool CLV(Environ& env, ShortInstrn instrn);

    static bool SES(Environ& env, ShortInstrn instrn);
    static bool CLS(Environ& env, ShortInstrn instrn);

    static bool SEH(Environ& env, ShortInstrn instrn);
    static bool CLH(Environ& env, ShortInstrn instrn);

    static bool SET(Environ& env, ShortInstrn instrn);
    static bool CLT(Environ& env, ShortInstrn instrn);

    static bool BST(Environ& env, ShortInstrn instrn);
    static bool BLD(Environ& env, ShortInstrn instrn);


};


#endif //ATMEGASIM_SRC_SREG_OPS_H
