#ifndef ATMEGASIM_SRC_BRANCH_OPS_MC_H
#define ATMEGASIM_SRC_BRANCH_OPS_MC_H


#include "../infra/environment.h"
#include "../ops/instrn_enum.h"

class BranchOpsImpl {

public:
    static void CPSE(Environ& env, FiveBit reg1Addr, FiveBit reg2Addr, InstrnEnum nextInstrn);

    static void SBRC(Environ& env, FiveBit regAddr, ThreeBit bitNum, InstrnEnum nextInstrn);
    static void SBRS(Environ& env, FiveBit regAddr, ThreeBit bitNum, InstrnEnum nextInstrn);

    static void SBIC(Environ& env, FiveBit portAddr, ThreeBit bitNum, InstrnEnum nextInstrn);
    static void SBIS(Environ& env, FiveBit portAddr, ThreeBit bitNum, InstrnEnum nextInstrn);

    static void BRBS(Environ& env, SevenBit offset, ThreeBit regBit);
    static void BRBC(Environ& env, SevenBit offset, ThreeBit regBit);

    static void BREQ(Environ& env, SevenBit offset);
    static void BRNE(Environ& env, SevenBit offset);

    static void BRCS(Environ& env, SevenBit offset);
    static void BRCC(Environ& env, SevenBit offset);

    static void BRLO(Environ& env, SevenBit offset);
    static void BRSH(Environ& env, SevenBit offset);

    static void BRMI(Environ& env, SevenBit offset);
    static void BRPL(Environ& env, SevenBit offset);

    static void BRVS(Environ& env, SevenBit offset);
    static void BRVC(Environ& env, SevenBit offset);

    static void BRLT(Environ& env, SevenBit offset);
    static void BRGE(Environ& env, SevenBit offset);

    static void BRHS(Environ& env, SevenBit offset);
    static void BRHC(Environ& env, SevenBit offset);

    static void BRTS(Environ& env, SevenBit offset);
    static void BRTC(Environ& env, SevenBit offset);

    static void BRIE(Environ& env, SevenBit offset);
    static void BRID(Environ& env, SevenBit offset);
};


#endif //ATMEGASIM_SRC_BRANCH_OPS_MC_H
