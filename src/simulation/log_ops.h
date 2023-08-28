#ifndef ATMEGASIM_SRC_LOG_OPS_H
#define ATMEGASIM_SRC_LOG_OPS_H

#include <cstdint>
#include "types.h"
#include "environment.h"

class LogOps {
public:

    static bool AND(Environ& env, ShortInstrn instrn);
    static bool ANDI(Environ& env, ShortInstrn instrn);

    static bool OR(Environ& env, ShortInstrn instrn);
    static bool ORI(Environ& env, ShortInstrn instrn);

    static bool EOR(Environ& env, ShortInstrn instrn);
    static bool COM(Environ& env, ShortInstrn instrn);

    static bool SBR(Environ& env, ShortInstrn instrn);
    static bool CBR(Environ& env, ShortInstrn instrn);

    static bool SER(Environ& env, ShortInstrn instrn);
    static bool CLR(Environ& env, ShortInstrn instrn);

    static bool LSL(Environ& env, ShortInstrn instrn);
    static bool LSR(Environ& env, ShortInstrn instrn);

    static bool ROL(Environ& env, ShortInstrn instrn);
    static bool ROR(Environ& env, ShortInstrn instrn);

};


#endif //ATMEGASIM_SRC_LOG_OPS_H
