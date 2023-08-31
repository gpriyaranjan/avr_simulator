#ifndef ATMEGASIM_SRC_CALL_OPS_MC_H
#define ATMEGASIM_SRC_CALL_OPS_MC_H


#include "../environment.h"
#include "../types.h"
#include <cstdint>

class CallOpsImpl {

public:
    static bool RJMP(Environ &env, TwelveBit tgtOffset);
    static bool JMP(Environ &env, TwentyTwoBit instrn);
    static bool IJMP(Environ &env);
    static bool EIJMP(Environ &env);

    static bool PUSH(Environ &env, FiveBit regAddr);
    static bool POP(Environ &env, FiveBit regAddr);

    static bool RCALL(Environ &env, TwelveBit tgtOffset);
    static bool CALL(Environ &env, TwentyTwoBit instrn);
    static bool ICALL(Environ &env);
    static bool EICALL(Environ &env);

    static bool RET(Environ &env);
    static bool RETI(Environ &env);

};


#endif //ATMEGASIM_SRC_CALL_OPS_MC_H
