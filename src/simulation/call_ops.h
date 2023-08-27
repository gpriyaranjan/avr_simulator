#ifndef ATMEGASIM_SRC_CALL_OPS_H
#define ATMEGASIM_SRC_CALL_OPS_H

#include <cstdint>
#include "types.h"
#include "environment.h"

class CallOps {
public:

    static void RJMP(Environ& env, uint32_t instrn);
    static void RJMP(Environ& env, TwelveBit tgtOffset, bool dummy);

    static void JMP(Environ& env, uint64_t instrn);
    static void JMP(Environ &env, TwentyTwoBit instrn, bool dummy);

    static void IJMP(Environ& env);
    static void IJMP(Environ& env, bool dummy);

    static void EIJMP(Environ& env);
    static void EIJMP(Environ& env, bool dummy);

    static void PUSH(Environ& env, uint32_t instrn);
    static void PUSH(Environ& env, FiveBit regAddr, bool dummy);

    static void POP(Environ& env, uint32_t instrn);
    static void POP(Environ& env, FiveBit regAddr, bool dummy);

    static void RCALL(Environ& env, uint32_t instrn);
    static void RCALL(Environ& env, TwelveBit tgtOffset, bool dummy);

    static void CALL(Environ& env, uint64_t instrn);
    static void CALL(Environ &env, TwentyTwoBit instrn, bool dummy);

    static void ICALL(Environ& env);
    static void ICALL(Environ& env, bool dummy);

    static void EICALL(Environ& env);
    static void EICALL(Environ& env, bool dummy);

    static void RET(Environ& env);
    static void RET(Environ& env, bool dummy);

    static void RETI(Environ& env);
    static void RETI(Environ& env, bool dummy);

    static void Push1Byte(Environ& env, uchar_t value);
    static void Pop1Byte(Environ& env, uchar_t& value);

    static void Push3Bytes(Environ& env, TwentyTwoBit pcValue);
    static void Pop3Bytes(Environ& env, TwentyTwoBit& pcValue);

};

#endif //ATMEGASIM_SRC_CALL_OPS_H
