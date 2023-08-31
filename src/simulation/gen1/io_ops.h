#ifndef ATMEGASIM_SRC_IO_OPS_H
#define ATMEGASIM_SRC_IO_OPS_H

#include "../infra/types.h"
#include "../infra/environment.h"

class IoOps {

    static void IN(Environ& env, ShortInstrn instrn);
    static void OUT(Environ& env, ShortInstrn instrn);

    static void SBI(Environ& env, ShortInstrn instrn);
    static void CBI(Environ& env, ShortInstrn instrn);

    static void SEI(Environ& env, ShortInstrn instrn);
    static void CLI(Environ& env, ShortInstrn instrn);

};


#endif //ATMEGASIM_SRC_IO_OPS_H
