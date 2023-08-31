#ifndef ATMEGASIM_SRC_BRANCH_OPS_H
#define ATMEGASIM_SRC_BRANCH_OPS_H

#include "../ops/instrn_enum.h"
#include "../infra/environment.h"

class BranchOps {
public:

    static bool CPSE(Environ& env, ShortInstrn instrn, InstrnEnum nextInstrn);

    static bool SBRC(Environ& env, ShortInstrn instrn, InstrnEnum nextInstrn);
    static bool SBRS(Environ& env, ShortInstrn instrn, InstrnEnum nextInstrn);

    static bool SBIC(Environ& env, ShortInstrn instrn, InstrnEnum nextInstrn);
    static bool SBIS(Environ& env, ShortInstrn instrn, InstrnEnum nextInstrn);

public:

    static bool BRBS(Environ& env, ShortInstrn instrn);
    static bool BRBC(Environ& env, ShortInstrn instrn);

    static bool BREQ(Environ& env, ShortInstrn instrn);
    static bool BRNE(Environ& env, ShortInstrn instrn);

    static bool BRCS(Environ& env, ShortInstrn instrn);
    static bool BRCC(Environ& env, ShortInstrn instrn);

    static bool BRLO(Environ& env, ShortInstrn instrn);
    static bool BRSH(Environ& env, ShortInstrn instrn);

    static bool BRMI(Environ& env, ShortInstrn instrn);
    static bool BRPL(Environ& env, ShortInstrn instrn);

    static bool BRVS(Environ& env, ShortInstrn instrn);
    static bool BRVC(Environ& env, ShortInstrn instrn);

    static bool BRLT(Environ& env, ShortInstrn instrn);
    static bool BRGE(Environ& env, ShortInstrn instrn);

    static bool BRHS(Environ& env, ShortInstrn instrn);
    static bool BRHC(Environ& env, ShortInstrn instrn);

    static bool BRTS(Environ& env, ShortInstrn instrn);
    static bool BRTC(Environ& env, ShortInstrn instrn);

    static bool BRIE(Environ& env, ShortInstrn instrn);
    static bool BRID(Environ& env, ShortInstrn instrn);

};


#endif //ATMEGASIM_SRC_BRANCH_OPS_H
