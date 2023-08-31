#ifndef ATMEGASIM_SRC_CALL_OPS_MC_H
#define ATMEGASIM_SRC_CALL_OPS_MC_H


#include "../infra/environment.h"
#include "../infra/types.h"
#include <cstdint>

class CallOpsImpl {

public:
    static void RJMP(Environ &env, TwelveBit tgtOffset);
    static void JMP(Environ &env, TwentyTwoBit instrn);
    static void IJMP(Environ &env);
    static void EIJMP(Environ &env);

    static void PUSH(Environ &env, FiveBit regAddr);
    static void POP(Environ &env, FiveBit regAddr);

    static void RCALL(Environ &env, TwelveBit tgtOffset);
    static void CALL(Environ &env, TwentyTwoBit instrn);
    static void ICALL(Environ &env);
    static void EICALL(Environ &env);

    static void RET(Environ &env);
    static void RETI(Environ &env);

};


#endif //ATMEGASIM_SRC_CALL_OPS_MC_H
