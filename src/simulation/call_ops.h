#ifndef ATMEGASIM_SRC_CALL_OPS_H
#define ATMEGASIM_SRC_CALL_OPS_H

#include <cstdint>
#include "types.h"
#include "environment.h"

class CallOps {
public:

    static bool RJMP(Environ& env, ShortInstrn instrn);

    static bool JMP(Environ& env, LongInstrn instrn);

    static bool IJMP(Environ& env);

    static bool EIJMP(Environ& env);

    static bool PUSH(Environ& env, ShortInstrn instrn);

    static bool POP(Environ& env, ShortInstrn instrn);

    static bool RCALL(Environ& env, ShortInstrn instrn);

    static bool CALL(Environ& env, LongInstrn instrn);

    static bool ICALL(Environ& env);

    static bool EICALL(Environ& env);

    static bool RET(Environ& env);

    static bool RETI(Environ& env);

};

#endif //ATMEGASIM_SRC_CALL_OPS_H
