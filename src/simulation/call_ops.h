#ifndef ATMEGASIM_SRC_CALL_OPS_H
#define ATMEGASIM_SRC_CALL_OPS_H

#include <cstdint>
#include "types.h"
#include "environment.h"

class CallOps {
public:

    static bool RJMP(Environ& env, uint32_t instrn);
    static bool RJMP(Environ& env, TwelveBit tgtOffset, bool dummy);

    static bool JMP(Environ& env, uint64_t instrn);
    static bool JMP(Environ &env, TwentyTwoBit instrn, bool dummy);

    static bool IJMP(Environ& env);
    static bool IJMP(Environ& env, bool dummy);

    static bool EIJMP(Environ& env);
    static bool EIJMP(Environ& env, bool dummy);

    static bool PUSH(Environ& env, uint32_t instrn);
    static bool PUSH(Environ& env, FiveBit regAddr, bool dummy);

    static bool POP(Environ& env, uint32_t instrn);
    static bool POP(Environ& env, FiveBit regAddr, bool dummy);

    static bool RCALL(Environ& env, uint32_t instrn);
    static bool RCALL(Environ& env, TwelveBit tgtOffset, bool dummy);

    static bool CALL(Environ& env, uint64_t instrn);
    static bool CALL(Environ &env, TwentyTwoBit instrn, bool dummy);

    static bool ICALL(Environ& env);
    static bool ICALL(Environ& env, bool dummy);

    static bool EICALL(Environ& env);
    static bool EICALL(Environ& env, bool dummy);

    static bool RET(Environ& env);
    static bool RET(Environ& env, bool dummy);

    static bool RETI(Environ& env);
    static bool RETI(Environ& env, bool dummy);

    static void Push1Byte(Environ& env, uchar_t value);
    static void Pop1Byte(Environ& env, uchar_t& value);

    static void Push3Bytes(Environ& env, TwentyTwoBit pcValue);
    static void Pop3Bytes(Environ& env, TwentyTwoBit& pcValue);

};

#endif //ATMEGASIM_SRC_CALL_OPS_H
