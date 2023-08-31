#ifndef ATMEGASIM_SRC_BRANCH_OPS_MC_H
#define ATMEGASIM_SRC_BRANCH_OPS_MC_H


#include "../environment.h"
#include "../instructions.h"

class BranchOpsImpl {

public:
    static bool CPSE(Environ& env, FiveBit reg1Addr, FiveBit reg2Addr, InstrnEnum nextInstrn);

    static bool SBRC(Environ& env, FiveBit regAddr, ThreeBit bitNum, InstrnEnum nextInstrn);
    static bool SBRS(Environ& env, FiveBit regAddr, ThreeBit bitNum, InstrnEnum nextInstrn);

    static bool SBIC(Environ& env, FiveBit portAddr, ThreeBit bitNum, InstrnEnum nextInstrn);
    static bool SBIS(Environ& env, FiveBit portAddr, ThreeBit bitNum, InstrnEnum nextInstrn);

    static bool BRBS(Environ& env, SevenBit offset, ThreeBit regBit);
    static bool BRBC(Environ& env, SevenBit offset, ThreeBit regBit);

    static bool BREQ(Environ& env, SevenBit offset);
    static bool BRNE(Environ& env, SevenBit offset);

    static bool BRCS(Environ& env, SevenBit offset);
    static bool BRCC(Environ& env, SevenBit offset);

    static bool BRLO(Environ& env, SevenBit offset);
    static bool BRSH(Environ& env, SevenBit offset);

    static bool BRMI(Environ& env, SevenBit offset);
    static bool BRPL(Environ& env, SevenBit offset);

    static bool BRVS(Environ& env, SevenBit offset);
    static bool BRVC(Environ& env, SevenBit offset);

    static bool BRLT(Environ& env, SevenBit offset);
    static bool BRGE(Environ& env, SevenBit offset);

    static bool BRHS(Environ& env, SevenBit offset);
    static bool BRHC(Environ& env, SevenBit offset);

    static bool BRTS(Environ& env, SevenBit offset);
    static bool BRTC(Environ& env, SevenBit offset);

    static bool BRIE(Environ& env, SevenBit offset);
    static bool BRID(Environ& env, SevenBit offset);
};


#endif //ATMEGASIM_SRC_BRANCH_OPS_MC_H
